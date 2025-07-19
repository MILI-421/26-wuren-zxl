
# #!/usr/bin/env python3
# import rospy
# from std_msgs.msg import String

# rospy.init_node('test_node')
# pub = rospy.Publisher('test_topic', String, queue_size=10)
# rate = rospy.Rate(1)

# while not rospy.is_shutdown():
#     pub.publish("Hello ROS!")
#     rate.sleep()



#!/usr/bin/env python3
import rospy
from std_msgs.msg import String

rospy.init_node('test_node', log_level=rospy.DEBUG)  # 设置调试级别
rospy.loginfo("节点已启动，尝试连接到 Master...")

pub = rospy.Publisher('test_topic', String, queue_size=10)
rate = rospy.Rate(1)  # 1Hz

while not rospy.is_shutdown():
    pub.publish("Hello ROS!")
    rospy.logdebug("已发布消息")
    rate.sleep()

