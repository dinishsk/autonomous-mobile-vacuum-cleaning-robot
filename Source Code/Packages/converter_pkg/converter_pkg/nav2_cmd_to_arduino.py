#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist

class Nav2ToArduinoConverter(Node):
    def __init__(self):
        super().__init__("arduino_cmd_vel")
        self.nav2_cmd_subscriber_ = self.create_subscription(Twist,"cmd_vel_nav",self.callback_nav2_cmd_vel,10)
        self.arduino_cmd_publisher = self.create_publisher(Twist,"/diffbot_base_controller/cmd_vel_unstamped",10)

    def callback_nav2_cmd_vel(self,cmd_data):
        self.arduino_cmd_publisher.publish(cmd_data)
        




def main(args = None):
    rclpy.init(args = args)
    node = Nav2ToArduinoConverter()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()