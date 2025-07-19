#!/usr/bin/env python3
import rospy
from geometry_msgs.msg import Twist  # 导入Twist消息类型用于发布速度指令

def pub_turtle_speed():
    rospy.init_node('turtle_speed_pub') # 初始化ROS节点，命名为"turtle_speed_pub"
    pub = rospy.Publisher('/turtle1/cmd_vel', Twist, queue_size=10)  
     # 创建发布者对象，向/turtle1/cmd_vel话题发布Twist消息，队列大小10
    rate = rospy.Rate(10)   # 设置发布频率为10Hz

    while not rospy.is_shutdown():# 主循环，直到节点被手动关闭
        msg = Twist()  # 创建Twist消息实例
        msg.linear.x = 1.0  # 设置线速度在x轴上为1.0m/s（前进）
        msg.angular.z = 0.5 # 设置角速度在z轴上为0.5rad/s（顺时针旋转）
        pub.publish(msg)  # 发布消息
        rate.sleep()  # 休眠，以保持频率

if __name__ == '__main__':
    try:
        pub_turtle_speed()  #  调用主函数
    except rospy.ROSInterruptException:  # 捕获Ctrl+C等中断异常
        pass  # 退出

