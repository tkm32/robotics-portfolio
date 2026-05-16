#include <feetech_driver/communication_protocol.hpp>
#include <spdlog/spdlog.h>
#include <iostream>
#include <fstream>
#include <poll.h>
#include <thread>
#include <climits>

using namespace std::chrono_literals;
using namespace feetech_driver;

bool enter_pressed() {
    struct pollfd pfd = {.fd = 0, .events = POLLIN};  // fd=0 は stdin
    return poll(&pfd, 1, 0) > 0;  // タイムアウト0ms = ノンブロッキング
}


struct JointRange {
    int min_pos;
    int max_pos;
};

int main(int argc, char** argv) {
    if (argc != 3) {
        spdlog::error("Usage: {} <port_name> <output_json_path>", argv[0]);
        return EXIT_FAILURE;
    }

    const std::string port_name = argv[1];
    const std::string output_path = argv[2];

    // TODO: SerialPortを作り、開く
    auto serial_port = std::make_unique<SerialPort>(port_name);
    std::ignore =
      serial_port->configure()
        .and_then([&] { return serial_port->open(); })
        .or_else([](const std::string& error) {
        throw std::runtime_error(error);
      });

    // TODO: CommunicationProtocolを作る
    auto communication_protocol = CommunicationProtocol(std::move(serial_port));
  
    // 全サーボのトルクをOFFにする
    for (int i = 0; i < 6; i++) {
        uint8_t servo_id = i + 1;
        communication_protocol.set_torque(servo_id, false);
    }

    // Phase 1: ホームポジションの記録
    std::cout << "全関節をホームポジションに合わせてEnterを押してください" << std::endl;
    std::cin.get();
    std::array<int, 6> home_positions;
    for (int i = 0; i < 6; i++) {
        int servo_id = i + 1;
        home_positions[i] = communication_protocol.read_position(servo_id)
            .or_else([](const std::string& error) { throw std::runtime_error(error); })
            .value();
        std::cout << "  Joint " << servo_id << " home raw: " << home_positions[i] << std::endl;
    }

    // Phase 2: 各関節の可動域を測定（累積変位方式）
    struct JointResult {
        int home_raw;
        int min_cum;  // ホームからの最小変位
        int max_cum;  // ホームからの最大変位
        bool zero_crossed;
    };
    std::array<JointResult, 6> results;

    for (int i = 0; i < 6; i++) {
        int servo_id = i + 1;
        std::cout << "Joint " << servo_id << ": 両方向に限界まで動かしてEnterを押してください" << std::endl;
        while (enter_pressed()) { std::cin.get(); }

        int prev = communication_protocol.read_position(servo_id)
            .or_else([](const std::string& error) { throw std::runtime_error(error); })
            .value();
        int cumulative = 0;
        int min_cum = 0, max_cum = 0;
        bool zero_crossed = false;

        while (!enter_pressed()) {
            int current = communication_protocol.read_position(servo_id)
                .or_else([](const std::string& error) { throw std::runtime_error(error); })
                .value();

            int diff = current - prev;
            if (diff > 2048) {
                diff -= 4096;
                zero_crossed = true;
            }
            if (diff < -2048) {
                diff += 4096;
                zero_crossed = true;
            }

            cumulative += diff;
            prev = current;

            if (cumulative < min_cum) min_cum = cumulative;
            if (cumulative > max_cum) max_cum = cumulative;

            std::cout << "\r  raw: " << current << "  cum: " << cumulative
                      << "  [min=" << min_cum << ", max=" << max_cum << "]"
                      << (zero_crossed ? " *ZERO CROSSED*" : "")
                      << "    " << std::flush;
            std::this_thread::sleep_for(100ms);
        }
        results[i] = {home_positions[i], min_cum, max_cum, zero_crossed};
        std::cout << "\n  => home=" << home_positions[i]
                  << ", min=" << min_cum << ", max=" << max_cum
                  << (zero_crossed ? " [ZERO CROSSED]" : "") << std::endl;
    }

    // 結果サマリ
    std::cout << "\n=== Summary ===" << std::endl;
    for (int i = 0; i < 6; i++) {
        std::cout << "Joint " << (i + 1)
                  << ": home_raw=" << results[i].home_raw
                  << ", range=[" << results[i].min_cum << ", " << results[i].max_cum << "]"
                  << (results[i].zero_crossed ? " *ZERO CROSSED*" : "")
                  << std::endl;
    }
    return 0;
}