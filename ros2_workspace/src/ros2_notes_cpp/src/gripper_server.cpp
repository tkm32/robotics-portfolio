#include <chrono>
#include <cstdio>
#include <memory>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include <std_srvs/srv/set_bool.hpp>

using namespace std::chrono_literals;

class GripperServer : public rclcpp::Node
{
public:
  explicit GripperServer(const std::string & topic_name)
  : Node("gripper_server")
  {
    // リクエストを受信したら呼ばれるコールバック関数
    auto callback =
      [this](
        const std::shared_ptr<rmw_request_id_t> request_header,
        const std::shared_ptr<std_srvs::srv::SetBool::Request> request,
        std::shared_ptr<std_srvs::srv::SetBool::Response> response) -> void  // ラムダ式による関数オブジェクトの定義
      {
        (void)request_header;
        response->success = true;
        response->message = request->data ? "Gripper opened" : "Gripper closed";
        RCLCPP_INFO(this->get_logger(), "%s", response->message.c_str());
    };

    srv_ = create_service<std_srvs::srv::SetBool>(topic_name, callback);
  }

private:
  rclcpp::Service<std_srvs::srv::SetBool>::SharedPtr srv_;
};

int main(int argc, char * argv[])
{
  // クライアントライブラリの初期化
  setvbuf(stdout, NULL, _IONBF, BUFSIZ);
  rclcpp::init(argc, argv);

  // ノードの生成とスピン開始
  auto node = std::make_shared<GripperServer>("/gripper");
  rclcpp::spin(node);
  rclcpp::shutdown();

  return 0;
}
