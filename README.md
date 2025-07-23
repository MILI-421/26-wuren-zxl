#####基础作业######

代码启动命令流程
```
catkin_make
source devel/setup.bash(已经写入了.bashrc)
roscore
(换一个终端)
roslaunch lir_pkg turtle_control.launch
```
ros学习笔记（图片版,发到邮箱了）

作业完成思路
```
1.作业的基础是发布——订阅话题，需要自定义消息
2.创建一个tur_msgs消息包，编写了一个.msg文件
3.创建一个lir_pkg软件包，用python编写发布者节点，发布线速度的消息；用yaml文件定义角速度和半径；用launch文件上传yaml文件到参数服务器，启动python节点和cpp节点
4.创建一个control_pkg软件包，用cpp编写订阅者节点，从python中订阅线速度，从参数服务器中获取角速度，用geometry_msgs将线速度和角速度合并，并用回调函数启动ros自带的小乌龟界面
5.运行调试
```
完成作业遇到的困难
```
我的发布消息没有打印内容，交的是运行了rostopic echo/turtle1/cmd_vel后的打印结果
学得太慢了
参数服务器还只学了皮毛
ppt上还有一些ros的指令没学到，非常慌，后来发现根本没用上多少
```
