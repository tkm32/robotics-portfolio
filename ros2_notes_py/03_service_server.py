from std_srvs.srv import SetBool

import rclpy
from rclpy.node import Node


class MinimalService(Node):
    def __init__(self):
        super().__init__('minimal_service')

        self.srv = self.create_service(SetBool, '/gripper',
                                       self.set_gripper)

    def set_gripper(self, request, response):
        response.success = True
        if request.data == True:
            response.message = "Gripper opened"
        else:
            response.message = "Gripper closed"
        self.get_logger().info(f"Server: success={response.success}, message='{response.message}'")
        return response


def main(args=None):
    rclpy.init(args=args)
    minimal_service = MinimalService()
    rclpy.spin(minimal_service)
    minimal_service.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
