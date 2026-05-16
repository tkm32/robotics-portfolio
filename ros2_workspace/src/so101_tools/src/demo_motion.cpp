#include <feetech_driver/communication_protocol.hpp>
#include <feetech_driver/common.hpp>
#include <spdlog/spdlog.h>
#include <iostream>
#include <thread>
#include <cmath>
#include <vector>

using namespace std::chrono_literals;
using namespace feetech_driver;

struct JointConfig {
    int id;
    int home_raw;
    int min_cum;
    int max_cum;
};

int main(int argc, char** argv) {
    if (argc != 2) {
        spdlog::error("Usage: {} <port_name>", argv[0]);
        return EXIT_FAILURE;
    }

    const std::string port_name = argv[1];

    auto serial_port = std::make_unique<SerialPort>(port_name);
    std::ignore =
        serial_port->configure()
            .and_then([&] { return serial_port->open(); })
            .or_else([](const std::string& error) {
                throw std::runtime_error(error);
            });

    auto protocol = CommunicationProtocol(std::move(serial_port));

    // キャリブレーション結果
    std::array<JointConfig, 6> joints = {{
        {1, 2091, -310, 719},
        {2, 2069, -1638, 730},
        {3, 2023, -1200, 1002},
        {4, 2080, -1173, 1175},
        {5, 1940, -1830, 1932},
        {6, 1582, 0, 1474},
    }};

    // 全関節をホームポジションに移動
    spdlog::info("Moving to home position...");
    std::vector<uint8_t> ids;
    std::vector<int> positions;
    std::vector<int> speeds(6, 1500);
    std::vector<int> accelerations(6, 50);

    for (auto& j : joints) {
        ids.push_back(j.id);
        positions.push_back(j.home_raw);
    }
    protocol.sync_write_position(ids, positions, speeds, accelerations);
    std::this_thread::sleep_for(2s);

    // 各関節を順番に可動域全体を往復
    spdlog::info("Starting demo motion...");
    for (int i = 0; i < 6; i++) {
        auto& j = joints[i];
        int target_max = j.home_raw + j.max_cum;
        int target_min = j.home_raw + j.min_cum;
        spdlog::info("Joint {} sweep: home={}, target_max={}, target_min={}", j.id, j.home_raw, target_max, target_min);

        // max方向へ
        spdlog::info("  -> max ({})", target_max);
        positions[i] = target_max;
        protocol.sync_write_position(ids, positions, speeds, accelerations);
        std::this_thread::sleep_for(2000ms);

        // min方向へ
        spdlog::info("  -> min ({})", target_min);
        positions[i] = target_min;
        protocol.sync_write_position(ids, positions, speeds, accelerations);
        std::this_thread::sleep_for(2000ms);

        // ホームに戻る
        spdlog::info("  -> home ({})", j.home_raw);
        positions[i] = j.home_raw;
        protocol.sync_write_position(ids, positions, speeds, accelerations);
        std::this_thread::sleep_for(1500ms);
    }

    // フィナーレ: 全関節同時に波打ち動作
    spdlog::info("Wave motion...");
    for (int step = 0; step < 60; step++) {
        for (int i = 0; i < 6; i++) {
            auto& j = joints[i];
            double phase = step * 0.15 + i * 1.0;
            double ratio = std::sin(phase) * 0.4;
            int range = (ratio > 0) ? j.max_cum : -j.min_cum;
            positions[i] = j.home_raw + static_cast<int>(ratio * range);
        }
        protocol.sync_write_position(ids, positions, speeds, accelerations);
        std::this_thread::sleep_for(100ms);
    }

    // ホームに戻る
    spdlog::info("Returning to home...");
    for (int i = 0; i < 6; i++) {
        positions[i] = joints[i].home_raw;
    }
    protocol.sync_write_position(ids, positions, speeds, accelerations);
    std::this_thread::sleep_for(2s);

    spdlog::info("Done!");
    return 0;
}
