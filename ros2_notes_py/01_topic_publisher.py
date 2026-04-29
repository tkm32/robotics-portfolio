import rclpy
from rclpy.node import Node

from std_msgs.msg import Float64MultiArray


class MinimalPublisher(Node):
    def __init__(self):
        super().__init__('minimal_publisher')

        self.publisher = self.create_publisher(Float64MultiArray, '/joint_commands', 10)
        # 送信周期毎にtimer_callbackを呼び出し（送信周期は0.5秒）
        self.timer = self.create_timer(0.5, self.timer_callback)
        self.i = 0

    def timer_callback(self):
        msg = Float64MultiArray()
        msg.data = [0.1, 0.2, 0.4, -0.1, -0.3, -0.5]

        self.publisher.publish(msg)
        # msgの中身を標準出力にログ
        self.get_logger().info(str(msg.data))
        self.i += 1


def main(args=None):
    # Pythonクライアントライブラリの初期化
    rclpy.init(args=args)
    # minimal_publisherノードの作成
    minimal_publisher = MinimalPublisher()
    # minimal_publisherノードの実行開始
    rclpy.spin(minimal_publisher)
    # minimal_publisherノードの削除
    minimal_publisher.destroy_node()
    # Pythonクライアントライブラリの終了
    rclpy.shutdown()


if __name__ == '__main__':
    main()
