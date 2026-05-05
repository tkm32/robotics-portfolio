#include <chrono>
#include <cstdio>
#include <memory>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include <std_srvs/srv/set_bool.hpp>

using namespace std::chrono_literals;

class GripperClient : public rclcpp::Node
{
public:
  explicit GripperClient(const std::string & topic_name)
  : Node("gripper_client")
  {
    client_ = create_client<std_srvs::srv::SetBool>(topic_name);

    while (!client_->wait_for_service(1s)) {
        if (!rclcpp::ok()) {
            return;
        }
        RCLCPP_INFO(this->get_logger(), "Service not available.");
    }

    auto request = std::make_shared<std_srvs::srv::SetBool::Request>();
    request->data = true;

    // Async
    {
        using ServiceResponseFuture = rclcpp::Client<std_srvs::srv::SetBool>::SharedFuture;
        auto response_received_callback = [this](ServiceResponseFuture future) {
            auto response = future.get();
            RCLCPP_INFO(this->get_logger(), "%s", response->success ? "true" : "false");
            rclcpp::shutdown();
        };
        auto future_result = client_->async_send_request(request, response_received_callback);
    }
  }

private:
  rclcpp::Client<std_srvs::srv::SetBool>::SharedPtr client_;
};

int main(int argc, char * argv[])
{
  // クライアントライブラリの初期化
  setvbuf(stdout, NULL, _IONBF, BUFSIZ);
  rclcpp::init(argc, argv);

  // ノードの生成とスピン開始
  auto node = std::make_shared<GripperClient>("/gripper");
  rclcpp::spin(node);
  rclcpp::shutdown();

  return 0;
}
