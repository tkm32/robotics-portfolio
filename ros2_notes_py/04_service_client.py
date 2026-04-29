from std_srvs.srv import SetBool

import rclpy
from rclpy.node import Node


class MinimalClient(Node):
    def __init__(self):
        super().__init__('minimal_client')

        self.cli = self.create_client(SetBool, '/gripper')
        # サービスの起動待機
        while not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('waiting...')
        
        self.request = SetBool.Request()

    def call_async(self):
        self.request.data = True
        # サービスの非同期実行
        return self.cli.call_async(self.request)


def main(args=None):
    rclpy.init(args=args)
    minimal_client = MinimalClient()
    future = minimal_client.call_async()
    # サービスの非同期実行が完了するまで待機
    rclpy.spin_until_future_complete(minimal_client, future)

    # 返り値を正常に得られたか判別
    if future.done() and future.result() is not None:
        # 返り値の取得
        response = future.result()
        # 計算結果を標準出力にログ
        minimal_client.get_logger().info(f"Server: success={response.success}, message='{response.message}'")

    minimal_client.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
