// Copyright 2014 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <chrono>
#include <cstdio>
#include <memory>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64_multi_array.hpp>

using namespace std::chrono_literals;

class Talker : public rclcpp::Node
{
public:
  explicit Talker(const std::string & topic_name)
  : Node("talker")
  {
    // タイマー実行されるイベントハンドラー関数
    auto publish_message =
      [this]() -> void  // ラムダ式による関数オブジェクトの定義
      {
        // 送信するメッセージ
        auto msg = std::make_unique<std_msgs::msg::Float64MultiArray>();
        msg->data = {0.1, 0.2, 0.4, -0.1, -0.3, -0.5};

        RCLCPP_INFO(this->get_logger(), "Publishing %zu joints", msg->data.size());
        pub_->publish(std::move(msg));
      };

    // トピックの送信設定
    rclcpp::QoS qos(rclcpp::KeepLast(10));
    pub_ = create_publisher<std_msgs::msg::Float64MultiArray>(topic_name, qos);
    // publish_messageの100ミリ秒周期でのタイマー実行
    timer_ = create_wall_timer(100ms, publish_message);
  }

private:
  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
  // クライアントライブラリの初期化
  setvbuf(stdout, NULL, _IONBF, BUFSIZ);
  rclcpp::init(argc, argv);

  // talkerノードの生成とスピン開始
  auto node = std::make_shared<Talker>("/joint_command");
  rclcpp::spin(node);
  rclcpp::shutdown();

  return 0;
}
