import rclpy
from rclpy.node import Node

from std_msgs.msg import Float64MultiArray


class MinimalSubscriber(Node):
    def __init__(self):
        super().__init__('minimal_subscriber')

        self.subscription = self.create_subscription(
            Float64MultiArray, '/joint_commands', self.listener_callback, 10)

    def listener_callback(self, msg):
        # msgの中身を標準出力にログ
        self.get_logger().info(str(msg.data))


def main(args=None):
    rclpy.init(args=args)
    minimal_subscriber = MinimalSubscriber()
    rclpy.spin(minimal_subscriber)
    minimal_subscriber.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
