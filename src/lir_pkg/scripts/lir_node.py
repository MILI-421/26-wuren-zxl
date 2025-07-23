#!/usr/bin/env python3
#coding=utf-8  

import rospy  #导入管家“rospy”
from std_msgs.msg import String  #导入消息类型
from tur_msgs.msg import lir  # 导入自定义的数据类型


if __name__ == '__main__':
    rospy.init_node("lir_node") #初始化节点
    pub = rospy.Publisher('/lir_data', lir, queue_size=10) #发布者
    rate = rospy.Rate(10) #设置循环频率
    while not rospy.is_shutdown():
        msg = lir() #创建自定义消息类型
        msg.turtle_linear = 1.0 #设置消息内容
        pub.publish(msg) #发布消息
        rate.sleep() #休眠
