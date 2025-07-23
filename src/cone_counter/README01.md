#####进阶作业1######
仓库地址：http://github.com/MILI-421/26-wuren-zxl.git

代码启动命令流程
```
1.roscore
2.启动.bag文件，rosbag play -l ~/ros_cone/bag/cone.bag
3.运行订阅节点，rosrun cone_counter count_cones

```
ros学习笔记（图片版,发到邮箱了）



作业完成思路
```
1.明确宏观流程：不需要自定义发布节点和话题，.bag文件就相当于发布节点和话题，只需要编写订阅节点

2.创订阅节点的工作空间ros_cone,把fsd_common_msgs复制到src下，把bag文件移动到工作空间目录下，创软件包cone_counter，创节点count_cones.cpp

3.先了解.bag的情况，用rosbag info 'lidar_cone_Side_\_&_slam_state.bag',可以看到这个.bag文件的信息，看types和topics部分，根据作业内容，需要的消息类型是：ConeDetections.msg和话题：/perception/lidar/cone_side。查看Cone.msg,发现锥桶有黄、蓝、橙三种颜色，表示为y、b、o(后面发现是错的，是红色和蓝色)

4.编写count_cones.cpp，写出普通订阅节点的大致框架
#include <ros/ros.h>
void 回调函数名(const 消息包::消息类型::ConstPtr& msg)
{
    
}

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"节点名");

    ros::NodeHandle nh;

    ros::Subscriber sub=nh.subscribe("话题",队列长度,回调函数名);

    while(ros::ok())
    {
        ros::spinOnce();
    }
    ROS_INFO();
    return 0;

}

5.填充内容：fsd_common_msgs头文件引入、创建用于计数的三个变量、解析ConeDetections消息、历遍判断锥桶颜色并计数、输出计数结果
6.改进：添加实时输出：ROS_INFO("Current count - yellow=%d, blue=%d, orange=%d", g_yellow, g_blue, g_orange);添加频率和休眠，防止cpu占用率过高，ros::Rate rate(10);rate.sleep();  
    }
```


完成作业遇到的困难
```
1.启动.bag文件时路径一直报错，调整了好久,以为是路径问题，后来发现是特殊符号的问题，需要用转义符，如：ls ~/ros_cone/bag/lidar_cone_side_\&_slam_state.bag，于是我改了它的名:cone.bag
2.运行订阅节点，rosrun cone_counter count_cones也一直报错说找不到文件,后来发现是CMakelists.txt文件的add_executable(count_cones src/count_cones.cpp)和target_link_libraries(count_cones
  ${catkin_LIBRARIES}
)的问题，我把映射名字当成要填的是包名
3.运行ros作业我的电脑直接关机了好多次,重启后之前正常的又报错了。想办法让程序运行时cpu占用率不那么高
4.运行时无法可视化，不知道运行进度，于是改进
5.会在运行到[INFO] [1753255499.296726724]: Current count - yellow=0, blue=1365, orange=0的时候就卡住，改了一下代码，使用 ros::spin() 替代 ros::spinOnce() 和 rate.sleep()后，卡在了[INFO] [1753255868.051957817]: Current count - yellow=0, blue=1803, orange=0，尝试缩小队列后，卡在了[INFO] [1753256091.184636912]: Current count - yellow=0, blue=1235, orange=0.又尝试了几次后，发现是rosbag play ~/ros_cone/bag/cone.bag的程序停止之后，就无法计数了.然后尝试设置循环播放把rosbag play ~/ros_cone/bag/cone.bag改成rosbag play -l ~/ros_cone/bag/cone.bag,能够一直计数
6.但奇怪的是只有一种颜色的锥桶，不知道是我哪里搞错了,我更感觉它就是在死循环。后来运行了rostopic echo /perception/lidar/cone_side -n1，发现确实是搞错了，就是题目里说的红色和蓝色，表示为r和b.我却看了Cone.msg,觉得锥桶有黄、蓝、橙三种颜色，表示为y、b、o，觉得不能这么死板（因为我cmake就是非常相信ppt上的内容，然后死磕了好长时间，结果去问学长，学长说“孩子你不要那么一板一眼”）。更正之后就正常了。一想到我眼睁睁看着蓝色运行到几万而其他的还是0我却毫无怀疑直到做rviz才发现，我就心梗。而且我发现改了之后计数的速度非常快，一下子就到了一万.
7.运行到十几万还没结束，我有些不理解了，但我决定不理它了
}


```
