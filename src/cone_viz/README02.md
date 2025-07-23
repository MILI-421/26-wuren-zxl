#####进阶作业2######
仓库地址：http://github.com/MILI-421/26-wuren-zxl.git

代码启动命令流程
```
1.catkin_make
2.roscore
3.source devel/setup.bash
4.rosrun cone_viz cone_viz_node
5.rosbag play -l ~/ros_cone/bag/cone.bag
6.rviz
7.Add-选topic那一栏-选viz-cones-MarkerArray
8.把Fixed Frame 改成rslidar(原本是map)
```
ros学习笔记（文字版+图片版,有图片的发到邮箱了）
```
1.rostopic echo /perception/lidar/cone_side -n1了解ConeDetections消息的具体格式，特别是颜色信息是如何存储的。是yaml格式的，有很多层级


```


作业完成思路
```
1.在ros_code的工作空间，新建功能包cone_viz，新建cpp订阅节点cone_viz_node.cpp
2.写订阅节点,订阅bag里面的ConeDetection，在回调函数里转换成把每条消息转换成  visualization_msgs/MarkerArray，然后发布一个话题/viz/cones
3.运行roscore，运行source devel/setup.bash,rosrun cone_viz cone_viz_node,运行rosbag play lidar_cone_side_\&_slam_state.bag（改名，改成cone.bag）,运行rviz
4.进入rviz界面，点Add,MarkerArray,Topic，设 Topic 为 /viz/cones，设Fixed Frame为map
```


完成作业遇到的困难
```
1.好多不会，都是查ai才知道的，比如要把bag里面的ConeDetection，在回调函数里转换成把每条消息转换成visualization_msgs/MarkerArray。。。。在哪里知道呢？可能教学视频里有可是我还没看到那里吧
2.可能是我才刚接触cpp吧，我就不太懂它的语法，我也不知道它是不是cpp的语法，比如这个ros::Publisher marker_pub;  // 声明一个发布者变量，用于发布可视化标记消息
3.cpp代码是ai的，我搞不明白怎么写，我觉得是不需要ai这么复杂的，或者说不需要把每条消息转换成  visualization_msgs/MarkerArray，但是我没搞懂怎么写
4.但起码我搞懂了自定义消息，也算一点好事吧
5.其实搞懂自定义之后，做作业花的时间不多，但是搞懂要花的时间很多，就很焦虑，沉不下心来学，我上次交的ros基础作业，就是因为事情多时间赶不想迟教作业，所以想着靠查ai一边学一边写，可以我发现ai的代码没有人类的智慧，总是会搞复杂，而且理解能力有问题，要调试ai让它做对也花了很长时间，可是我自己却没学到什么东西。后来我想了想，迟交就迟交吧，我是来学东西的，又不是来交作业的，我学会了才更重要。但是真的学得好慢啊。。。。。作业越堆越多了
```
