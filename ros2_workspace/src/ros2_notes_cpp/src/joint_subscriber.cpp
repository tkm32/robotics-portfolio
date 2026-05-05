#include <chrono>
#include <cstdio>
#include <memory>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64_multi_array.hpp>

using namespace std::chrono_literals;

class JointSubscriber : public rclcpp::Node
{
public:
  explicit JointSubscriber(const std::string & topic_name)
  : Node("joint_subscriber")
  {
    // メッセージを受信したら呼ばれるコールバック関数
    auto callback =
      [this](const std_msgs::msg::Float64MultiArray::UniquePtr msg) -> void  // ラムダ式による関数オブジェクトの定義
      {
        RCLCPP_INFO(this->get_logger(), "Receiving %zu joints", msg->data.size());
    };

    // トピックの受信設定
    rclcpp::QoS qos(rclcpp::KeepLast(10));
    sub_ = create_subscription<std_msgs::msg::Float64MultiArray>(topic_name, qos, callback);
  }

private:
  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr sub_;
};

int main(int argc, char * argv[])
{
  // クライアントライブラリの初期化
  setvbuf(stdout, NULL, _IONBF, BUFSIZ);
  rclcpp::init(argc, argv);

  // ノードの生成とスピン開始
  auto node = std::make_shared<JointSubscriber>("/joint_command");
  rclcpp::spin(node);
  rclcpp::shutdown();

  return 0;
}
