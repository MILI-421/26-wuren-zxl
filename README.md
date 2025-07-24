#####C++作业1#####

代码启动命令流程
```
# 回到 工作空间
1.catkin_make 
2.source devel/setup.bash    # 刷新环境
3.roscore
4.启动.bag文件，rosbag play -l cone_detected.bag
5.rosrun cpp_pkg cpp_node
6.rviz
7.Rviz里面，Add → by Topic,选Image和MarkerArray
8.把Fixed Frame改成rslidar
```

作业完成思路
```
1.拿到.bag 文件，先运行rosbag info xxx.bag,去查看包的一些信息，如types、topics
 rosbag info cone_detected.bag后关注
**types**:       fsd_common_msgs/ConeDetections [8d208cc8d9a8d2c9f26b340c91ec270a]  #消息包名称/消息类型[哈希值]  #ConeDetections，锥体探测；这个话题包含了锥桶的检测信息，例如锥桶的坐标、颜色等
             visualization_msgs/MarkerArray [d155b9ce5188fbaf89745847fd5882d7]    # MarkerArray，标记阵列？这个话题主要用于可视化。
             
**topics**:      /fusion_visual/coneFusion        265 msgs    : visualization_msgs/MarkerArray    #话题    消息数量     类型（跟types对应）
             /perception/fusion/cone_fusion   266 msgs    : fsd_common_msgs/ConeDetections      #话题    消息数量     类型（跟types对应）
         
             
2.看作业要求
作业要求：将提供的cone_detected.bag中的锥桶的中心点投影至像素平面（会提供内外参矩阵），并发布图像话题使其能在Rviz中可视化；包中包含话题/perception/lidar/cone_detections，消息类型为fsd_common_msgs::ConeDetections(还有有个MarkerArray消息，用于在Rviz中可视化，对比观察投影结果)；读取锥桶坐标，使用给定内外参矩阵，通过eigen库进行矩阵运算，将锥桶坐标转换至像素平面坐标（宽1280高360），通过opencv作图并发布可视化结果，要求话题名称为/projected_image。投影点颜色与锥桶颜色一致，如锥桶为红色，图像中对应投影点也应为红色，投影点大小不限，能在Rviz中清晰看到即可
    >>>>明确了要用的话题和消息类型。==基本的做题步骤：读取话题，获取锥桶的雷达坐标系下的位置信息>>使用给定的内外参矩阵，通过eigen库将雷达坐标系下的点投影到像素平面 >> 使用OpenCV在图像上绘制投影点 >> 使用cv_bridge把 OpenCV 的 cv::Mat 转成 ROS 的 sensor_msgs/Image >> 将绘制好的图像发布到/projected_image话题 >> 在Rviz中订阅/projected_image话题，查看投影结果。==
    
    
3.创工作空间cpp_ws,创软件包cpp_pkg,依赖项roscpp(C++节点入口)、 fsc_common_msgs（订阅自定义消息类型，锥桶检测结果）、 eigen（坐标变换矩阵）、 OpenCV（用于cv::Mat及绘图功能）、cv_bridge（cv::Mat ↔ sensor_msgs/Image）、sensor_msgs（sensor_msgs::Image，发布投影结果）  ，把fsc_common_msgs这个包放到src下，把bag放在工作空间下


4.创订阅者节点cpp_node.cpp，
确定一些名称不要弄错：回调函数coneCallback,订阅话题：/perception/fusion/cone_fusion，自定义消息类型：fsd_common_msgs/ConeDetection（消息包/消息类型），订阅者对象：cone_sub ，发布者对象：pub,发布话题/projected_image，发布消息类型sensor_msgs::Image
完整代码：

5.修改 CMakeLists.txt


6. 修改 package.xml（确保依赖已列）


7. 编译 、运行（见代码启动命令流程）
8.查看rosrun tf view_frames 

8.在 Rviz 里 Add → Image，话题选 /projected_image 即可看到投影结果


```

学习笔记
```
1..bag文件：替代了实时发布者的角色，提供录制的消息流。
订阅者节点：从.bag文件中读取消息，处理数据，并发布结果。
bag包原理：一、录制bag包：rosbag record -O cone_detected.bag /perception/fusion/cone_fusion /fusion_visual/coneFusion 将指定的话题消息录制到文件中，在这里，文件是cone_detected.bag，主题是/perception/fusion/cone_fusion和/fusion_visual/coneFusion    二、回放bag包：rosbag play cone_detected.bag  将.bag文件中的消息重新发布到ROS网络中。 三、订阅者节点： 订阅/perception/fusion/cone_fusion话题，进行所需操作
        处理数据：节点接收到消息后，进行坐标变换和投影。
        发布结果：将处理后的图像发布到/projected_image话题。
2.这个订阅者节点要同时处理 ROS 消息、自定义消息类型、Eigen 矩阵运算、OpenCV 图像绘制 和 cv_bridge 图像转换，以此判断创包时需要的依赖项
3.订阅者节点的通用框架：
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
4.头文件：（1） 系统库 / 标准库头文件：名称固定且由标准规定、（2）自定义头文件：需与文件名严格一致
5.相机原理：小孔成像>>>映射、函数>>>物点与像点的空间位置一一对应。镜头充当小孔的作用，将物点投射到图像传感器，而图像传感器，常见的有CCD和CMOS，都是将光强信号转化为电流信号的装置，再由运算电路转化成数字信号，合成数字图像，得到数码照片。
这个映射的具体形式是什么（数学关系）：二维相机坐标系，三维世界坐标系；无论是二维还是三维，刚体的运动只有旋转和平移。
-对于旋转，在二维平面内，求旋转后点的坐标，可以根据“旋转不改变长度”，利用三角函数和角公式可以求出对应点的坐标，将等式两边写成矩阵，即P'=RP，是一个二维的线性变换；如果是点不变，坐标系旋转，可以即P'=AP，是一个坐标基变换。可以发现AR=I（I 是单位矩阵）>>>可知变换点和变换坐标系的操作是相反的
---所以，已知相机运动，求表示相机运动的矩阵R，通过这个矩阵的逆R^(-1)=A，可以求得空间点在运动后的相机的坐标系下的表达。即世界坐标系中的P点在运动了的相机的相机坐标系的坐标为P'=AP
-对于平移，在二维平面内，点平移，例如：x'=x+a,y'=y+b。但是平移不是线性变换，无法表达成2x2矩阵的相乘形式，但是发现3x3矩阵可以实现表达，即升维->齐次坐标（让第三维，即z=1） 。假设初始点为(0,0)平移后，在z=1上的点变化为：(0,0,1)->(a,b,1),发现可以用矩阵相乘表示。P'=TP（？）z坐标的值是比例因子w，称w=1的平面为归一化平面；齐次坐标z值不同的点在笛卡尔坐标下是同一个点>>>透视投影/中心投影变换。>>>通过高维的剪切变换实现低维的平移变换，从而解决平移运动的矩阵表示问题。同样的，对于相机坐标系的平移，P'=AP,AT=I(I为单位矩阵)
-把平移（3x3矩阵）和旋转（2x2矩阵）放进一个矩阵（用自定义排列：将较小的矩阵嵌入到较大的矩阵里，用覆盖的形式），记为E，称为相机的外参矩阵，表征相机自身的运动
-内参矩阵是 3×3 的矩阵，记录相机自身的物理特性，负责把相机坐标系的 3D 点转换为像素坐标系的 2D 点，多次用两个三角形相似可求得坐标。但实际上相机成像会有很多误差因素：图像传感器的尺寸和形状误差、相机实际生产中的公差和不确定因素、工艺问题>>>本质也是坐标基变换的问题，得到一个矩阵，就是相机的内参矩阵，定义为K
-把内参矩阵和外参矩阵写在一起，即P'=KEP，但还不准确，还需要归一化像平面，然后才得到透视投影（发生三维到二维的维度丢失）
6.常见误区：ROS 中 OpenCV 的引用原则
很多人会混淆 “ROS 组件” 和 “外部库”，这里用表格明确区别：
类型	示例	引用方式
ROS 组件	roscpp、std_msgs	作为find_package(catkin REQUIRED COMPONENTS)的参数
外部库	OpenCV、Eigen	单独使用find_package(库名 REQUIRED)

OpenCV 属于外部库，因此必须用find_package(OpenCV REQUIRED)，而非作为 catkin 组件。
7.什么情况下需要修改 package.xml？如果你使用的是某个 ROS 封装的 OpenCV 功能包（如cv_bridge），则需要在package.xml中添加相应依赖：<build_depend>cv_bridge</build_depend>、<exec_depend>cv_bridge</exec_depend>。OpenCV 属于系统依赖，而非 ROS 包依赖
8.catkin_create_pkg 时指定的依赖包本质上就是 ROS 包依赖，这些依赖会被自动写入 package.xml 和 CMakeLists.txt 中，用于告诉 ROS 构建系统当前包需要哪些其他 ROS 包的支持。
9.Eigen 作为独立的线性代数库，其头文件通常安装在/usr/include/eigen3目录下，但默认情况下编译器可能不会自动搜索这个路径，需要手动配置。# 查找Eigen/Dense文件
find /usr/include -name "Dense" | grep "Eigen"
10.eigen_conversions是 ROS 提供的官方功能包
11. std_msgs::String是 ROS 定义的消息类型，其内部通过data字段存储实际的字符串内容（类型为std::string）。
    因此，访问cone.color.data才能得到可与"yellow"等字符串常量比较的std::string类型数据。
    
12.在 RViz 中，“固定坐标系（Fixed Frame）” 是所有可视化数据的 “参考原点”。代码发布的图像消息（/projected_image）里，藏着一个 “坐标系标签”（header.frame_id），Fixed Frame需要与它保持一致。代码中pub.publish(cv_bridge::CvImage(msg->header, "bgr8", img).toImageMsg());复用了锥桶消息的msg->header，所以图像的坐标系标签和msg->header.frame_id一致。通过rostopic echo /perception/fusion/cone_fusion/header/frame_id，终端会输出类似base_link或lidar_link的结果，这就是图像消息的坐标系标签。
    

```


遇到的问题和困难（记录）
```
1.catkin_make时遇到很多问题：依赖项的问题，不能用OpenCV,要用opencv4，我安装的是opencv4版本；不能用eigen,Eigen 是一个独立的线性代数库，并非 ROS 专属包，因此在catkin的find_package中直接写eigen是错误的。ROS 中与 Eigen 相关的标准组件是eigen_conversions（用于 ROS 消息与 Eigen 数据结构的转换），而 Eigen 库本身需要通过单独的find_package(Eigen3)来引用；没有意识到系统要先安装eigen等，忘记把bag和fsc_common_msgs放到工作空间;创包时输错了fsd_common_msgs。以上问题解决后，编译在98%时报错,还是编译器无法找到 OpenCV 4 的头文件。# 查找opencv.hpp文件find /usr/include -name "opencv.hpp"# 查找OpenCV版本信息pkg-config --modversion opencv4、pkg-config --cflags opencv4  # 显示编译选项（包括头文件路径）发现应该是#include <opencv2/opencv.hpp>  // 对应实际路径/usr/include/opencv4/opencv2/opencv.hpp。随后eigen又出了问题，eigen_conversions发现未安装，安装后发现我的文件不同，不能写#include <eigen_conversions/eigen_msg_conversion.h> ，要写#include <eigen_conversions/eigen_msg.h>。然后是 “fsd_common_msgs功能包定义的ConeDetections.msg文件中，并没有名为cones的字段，而你的代码错误地引用了该字段。”；又改了一个cone.color.data的问题，终于基本编译成功.后面eigen_conversions的问题在配置文件里加了绝对路径/opt/ros/noetic/lib/libeigen_conversions.so 才最终成功编译。
2.我没有分清什么是ROS的依赖包，什么不是，全都写进了package.xml里
3.我有点怀疑我是不是把问题搞复杂了，做一个作业要花好久，一直报错报错报错
4.打开rviz后没有图像（一片空白），rostopic echo -n1 /projected_image > image_data.txt打开后发现全是255
5.ppt上说的话题没有，包里只有 /fusion_visual/coneFusion        265 msgs    : visualization_msgs/MarkerArray    #话题    消息数量     类型（跟types对应）
             /perception/fusion/cone_fusion   266 msgs    : fsd_common_msgs/ConeDetections      #话题    消息数量     类型（跟types对应）
6.发现所有锥桶的投影坐标（尤其是 v 值）都超出了图像的高度范围（360 像素）
7.在查了很多资料后发现，需要把Fixed Frame改成rslidar
8.代码里面一些语法还是不太熟练


```


最终代码
```
#include <ros/ros.h>   // ROS节点初始化、订阅发布等核心功能
#include <fsd_common_msgs/ConeDetections.h>    // 锥桶检测消息类型（自定义）
#include <sensor_msgs/Image.h>  // ROS图像消息类型（用于发布结果）
#include <cv_bridge/cv_bridge.h>   // OpenCV图像与ROS图像的转换工具

#include <opencv2/opencv.hpp>

#include <Eigen/Dense>
#include <string>
#include <eigen_conversions/eigen_msg.h>  // 包含 eigen_conversions 头文件

// 全局发布器：用于发布投影后的图像消息（避免在回调函数中重复创建）
ros::Publisher pub;

//相机内参矩阵（3×3，const修饰确保不可修改）：将相机坐标系转换为像素坐标系
const Eigen::Matrix3d intrinsic = (Eigen::Matrix3d() <<
    532.795, 0.0,      632.15,                // 第1行：fx（x轴焦距）、0、cx（x轴主点）
    0.0,     532.72,   363.428,                // 第2行：0、fy（y轴焦距）、cy（y轴主点）
    0.0,     0.0,      1.0).finished();      // 第3行：齐次坐标归一化参数

// 相机外参矩阵（3×4，const修饰）：将雷达坐标系转换为相机坐标系
const Eigen::Matrix<double, 3, 4> extrinsic = (Eigen::Matrix<double, 3, 4>() <<
     3.5594209875121074e-03, -9.9987761481865733e-01, -1.5234365979146680e-02, 8.9277270417879417e-02,            // 第1行：旋转+平移分量
     1.9781062410225703e-03,  1.5241472820252011e-02, -9.9988188532544631e-01, 9.1100499695349946e-01,            // 第2行：旋转+平移分量
     9.9999170877459420e-01,  3.5288653732390984e-03,  2.0321149683686368e-03, 1.9154049062915668e+00).finished(); // 第3行：旋转+平移分量

// 回调函数：当订阅的锥桶消息到达时触发，处理数据并生成投影图像
void coneCallback(const fsd_common_msgs::ConeDetections::ConstPtr& msg)
{   
    // 创建空白图像：尺寸360（高）×1280（宽），3通道8位无符号整数，初始为白色（BGR格式）
    cv::Mat img(360, 1280, CV_8UC3, cv::Scalar(255, 255, 255));

    for (const auto& cone : msg->cone_detections)
    {
        // 1. 雷达坐标
        Eigen::Vector4d radar(cone.position.x, cone.position.y, cone.position.z, 1.0);

        // 2. 投影
        Eigen::Vector3d pxh = intrinsic * extrinsic * radar;
        
        // 透视除法：转换为像素坐标（u,v），+0.5用于四舍五入取整
        int u = static_cast<int>(pxh(0) / pxh(2) + 0.5);
        int v = static_cast<int>(pxh(1) / pxh(2) + 0.5);
        ROS_INFO("锥桶投影坐标：u=%d, v=%d", u, v);  // 新增：打印坐标
       // 3.越界检查
        if (u < 0 || u >= 1280 || v < 0 || v >= 360) {
           ROS_WARN("锥桶坐标越界：u=%d, v=%d", u, v);  // 新增：越界警告
           continue;
        }

        // 4. 颜色 
        cv::Scalar color;
        if (cone.color.data == "yellow")      color = cv::Scalar(0, 255, 255);
        else if (cone.color.data == "blue")   color = cv::Scalar(255, 0, 0);
        else                             color = cv::Scalar(0, 0, 255);   // 默认红

        cv::circle(img, cv::Point(u, v), 5, color, -1);
    }

    // 5. 发布
    pub.publish(cv_bridge::CvImage(msg->header, "bgr8", img).toImageMsg());
}

// 主函数：初始化节点，创建订阅器和发布器
int main(int argc, char** argv)
{
    ros::init(argc, argv, "cpp_node");
    ros::NodeHandle nh;

    // 初始化发布器：发布话题"/projected_image"，消息类型sensor_msgs::Image，队列长度10
    pub = nh.advertise<sensor_msgs::Image>("/projected_image", 10);

    ros::Subscriber sub = nh.subscribe("/perception/fusion/cone_fusion", 10, coneCallback);

    // 进入ROS事件循环：持续等待消息并调用回调函数
    ros::spin();
    return 0;
}

```


#####c++作业2#####

代码启动流程
```
1.catkin_make
# 新终端
2.roscore
# 新终端
3.rosbag play -l carla_test.bag   # 把提供的 bag 放在当前目录
# 新终端
4.source ~/cpp_ws/devel/setup.bash
5.启动节点：rosrun cpp_pkg point_cloud_processor 
6.rviz
7.选择正确的 frame_id，手动选择着色方式以正确显示强度信息（“Add” → 选择 “By topic” → 找到/lidar_points → 选择 “PointCloud2”，Fixed Frames改成：go_vehicle/lidar_mid
```



工作空间cpp_ws
-src
--软件包cpp_pkg
---src
----point_cloud_processor.cpp



一些指令
```
rostopic list  # 查看活跃话题
rostopic info 话题   #查看消息信息 (例子：rostopic info /lidar_points）  可以看到消息类型，发布者等信息
rostopic echo -n1 话题  # 查看点云消息内容（例子：rostopic echo -n1 /lidar_points） 在输出中找到intensities字段，确认取值范围
rostopic echo -n1 话题/header/frame_id  #验证 frame_id（例子：rostopic echo -n1 /lidar_points/header/frame_id）



```


作业完成思路
```
1.拿到.bag 文件，先运行rosbag info xxx.bag,去查看包的一些信息，如types、topics
 rosbag info carla_test.bag后关注
types:       sensor_msgs/PointCloud2 [1158d486dd51d683ce2f1be655c3c181]
topics:      /carla/ego_vehicle/lidar_down   167 msgs    : sensor_msgs/PointCloud2
             /carla/ego_vehicle/lidar_mid    167 msgs    : sensor_msgs/PointCloud2
             /carla/ego_vehicle/lidar_up     167 msgs    : sensor_msgs/PointCloud2
             
2.作业要求：将提供的carla_test.bag中的点云拼接，将其强度范围从0~1修改至1~256，发布拼接并修改强度后的点云。要求发布的点云frame_id为lidar，话题名称为/lidar_points
考什么？（1）考融合，点云是 “三维坐标的集合，要将三个不同视角的雷达（lidar_down、lidar_mid、lidar_up）的点云拼接，得到更完整的环境图像。考察“时间戳匹配” 和 “ROS 消息同步工具”，时间戳方面：多个激光雷达（或传感器）的更新频率可能不同（比如 A 雷达 10Hz、B 雷达 20Hz），发布数据的时间戳会有差异；同步策略——message_filters::sync_policies::ApproximateTime，通过时间戳差值最小化实现对齐
（2） PCL 处理 ROS 点云数据,云格式转换,掌握pcl::fromROSMsg（ROS→PCL）和pcl::toROSMsg（PCL→ROS）的转换  // ROS 中点云消息是sensor_msgs::PointCloud2，而 PCL 库（点云处理的主流库）使用pcl::PointCloud格式。


3.安装：
# 安装PCL核心库
sudo apt-get install libpcl-dev=1.10.0* pcl-tools=1.10.0*
# 安装ROS与PCL的接口包（用于消息转换）
sudo apt-get install ros-noetic-pcl-ros ros-noetic-pcl-conversions
验证安装：ls /usr/lib/x86_64-linux-gnu/libpcl_common.so  或  pkg-config --modversion pcl_common-1.10（Ubuntu 20.04 下 用 pcl_common-1.10 而不是 pcl_common）

在CMakeLists.txt中链接 PCL 库


4.在作业1的包下
#配置新依赖
 roscpp sensor_msgs pcl_ros pcl_conversions——————修改package.xml和CMakeLists.txt
 
cd ~/catkin_ws
catkin_make  # 编译功能包
source devel/setup.bash  # 刷新环境

5. 编写点云处理代码（订阅节点）
在~/catkin_ws/src/point_cloud_utils/src目录下新建point_cloud_processor.cpp
先写框架：
#include <ros/ros.h> 
int main(int argc, char *argv[])
{
    ros::init(argc,argv,"point_cloud_processor");
    ros::NodeHandle nh;
   
    while(ros::ok())
    {
        ros::spinOnce();
    }
    
    return 0;
} 

填充内容


6.配置编译规则

7.编译与运行

8.查询rostopic echo /carla/ego_vehicle/lidar_down/header/frame_id  是"ego_vehicle/lidar_down"
rostopic echo /carla/ego_vehicle/lidar_mid/header/frame_id 是"ego_vehicle/lidar_mid"
rostopic echo /carla/ego_vehicle/lidar_up/header/frame_id 是"ego_vehicle/lidar_up"

mi@XL:~/cpp_ws$ rostopic echo -n1 /lidar_points/header/frame_id
"ego_vehicle/lidar_mid"
---

9.RViz 可视化设置



```

学习笔记
```
1.怎么使用近似时间同步（ApproximateTime）：
（1）引入必要头文件
#include <message_filters/subscriber.h>  // 用于订阅多个话题
#include <message_filters/sync_policies/approximate_time.h>  // 近似时间同步策略
（2）定义订阅器与同步器
// 创建3个订阅器，分别订阅3个雷达话题，语法：message_filters::Subscriber<消息类型> 订阅器名称(节点句柄, 话题名称, 队列长度);
//message_filters::Subscriber是message_filters库提供的订阅器类（区别于 ROS 基础的ros::Subscriber），支持与同步器配合使用。

message_filters::Subscriber<sensor_msgs::PointCloud2> mid_sub(nh, "/carla/ego_vehicle/lidar_mid", 10);
message_filters::Subscriber<sensor_msgs::PointCloud2> up_sub(nh, "/carla/ego_vehicle/lidar_up", 10);
message_filters::Subscriber<sensor_msgs::PointCloud2> down_sub(nh, "/carla/ego_vehicle/lidar_down", 10);


****用python的方式类比理解就是：SyncPolicy是一个函数，Synchronizer<SyncPolicy>相当于调用了这个函数，向函数的三个参数按顺序传入了三个值
using SyncPolicy = message_filters::sync_policies::ApproximateTime//定义了一个名为SyncPolicy的模板别名，等号右边是ROS 提供的近似时间同步策略类，它本身是一个模板类，需要指定要同步的消息类型。
< 
    sensor_msgs::PointCloud2, 
    sensor_msgs::PointCloud2, 
    sensor_msgs::PointCloud2
>;                //<>内有3 个参数，表示要同步 3 个点云话题

message_filters::Synchronizer<SyncPolicy> sync(SyncPolicy(20), mid_sub, up_sub, down_sub);//message_filters::Synchronizer是同步器类，它也需要一个模板参数（即前面定义的SyncPolicy）；sync是同步器类的一个实例
（3）回调函数的绑定与处理
//将回调函数（callback）注册到同步器，boost::bind用于将函数与参数绑定，&callback：指向回调函数的指针，_1, _2, _3：占位符
sync.registerCallback(boost::bind(&callback, _1, _2, _3));

// 回调函数同时接收3个同步后的消息，sensor_msgs::PointCloud2ConstPtr是 ROS 消息的常量智能指针，指向接收到的点云数据
void callback(
    const sensor_msgs::PointCloud2ConstPtr& mid_cloud,
    const sensor_msgs::PointCloud2ConstPtr& up_cloud,
    const sensor_msgs::PointCloud2ConstPtr& down_cloud
) { ... }

/*{...}中可加入一个验证调试用的函数 
    ROS_INFO("同步时间戳: %.3f, %.3f, %.3f",
           mid->header.stamp.toSec(),
           up->header.stamp.toSec(),
           down->header.stamp.toSec());*/




2.怎么实现pcl::fromROSMsg（ROS→PCL）和pcl::toROSMsg（PCL→ROS）的转换
ROS 点云（消息格式）->pcl::fromROSMsg（转换工具）-> PCL点云（数据结构）
PCL点云（数据结构） ->pcl::toROSMsg（转换工具）-> ROS 点云（消息格式）

引入头函数：
#include <sensor_msgs/PointCloud2.h>  // ROS点云消息类型
#include <pcl_conversions/pcl_conversions.h>  // 转换工具头文件
#include <pcl/point_cloud.h>  // PCL点云类
#include <pcl/point_types.h>  // 点类型定义

步骤：接收 ROS 点云消息（订阅话题）（3个不同的回调函数）---> 将 ROS 消息转换为 PCL 点云（在回调函数中，使用pcl::fromROSMsg转换）（创建PCL点云>>>转换，获得点云）----> 用 PCL 处理点云（拼接 + 调整强度）---->将 PCL 点云转换回 ROS 消息（创建ROS点云消息>>>设置消息的元数据>>>转换>>>发布消息到指定话题）

3.点云是三维空间中大量点的集合，每个点包含坐标（x,y,z）和可选属性（如强度、颜色）。在 PCL 中，最常用的点类型是pcl::PointXYZI（含坐标和强度）或pcl::PointXYZRGB（含坐标和颜色）。
PCL 用pcl::PointCloud<T>存储点云，其中T是点类型。
如：pcl::PointCloud<pcl::PointXYZI>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZI>);
语法：智能指针定义：：PCL自定义的智能指针类型 智能指针（用于动态创建对象的关键字 PCL库的点云模板类）
点云拼接的方法：使用+=运算符或insert函数，注意——拼接前需确保所有点云在同一坐标系下、频繁拼接大量点云时，+=比insert更高效（减少内存重新分配）
```



遇到的困难
```
打开rviz没有动静，运行rostopic hz /lidar_points，一直是 “no new messages”，节点没订阅到 bag
运行mi@XL:~/cpp_ws$ rostopic info /carla/ego_vehicle/lidar_mid
Type: sensor_msgs/PointCloud2

Publishers: 
 * /play_1753359405552604988 (http://XL:44653/)

Subscribers: None
运行rostopic echo -n1 /lidar_points/header，卡住了

运行了好多个命令，没检查出什么问题
运行roswtf，报错，说明节点根本没订阅成功

后来在int和voin中分别加了一些输出语句，发现是节点启动正常，但未收到源话题数据（问题在订阅或 bag）

```


完整代码：
#pragma message("Compiling point_cloud_processor.cpp")
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <message_filters/subscriber.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <message_filters/synchronizer.h>

// PCL ↔ ROS 互转
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

// 全局发布器
ros::Publisher g_pub;

// 通用回调：每收到三条 PointCloud2 就触发
void cloudCB(const sensor_msgs::PointCloud2::ConstPtr& mid_msg, 
             const sensor_msgs::PointCloud2::ConstPtr& up_msg, 
             const sensor_msgs::PointCloud2::ConstPtr& down_msg)
{
  ROS_INFO_STREAM("Received point clouds: "
                  << "mid=" << mid_msg->header.stamp 
                  << ", up=" << up_msg->header.stamp 
                  << ", down=" << down_msg->header.stamp);
  
  // 检查frame_id是否一致
  ROS_INFO_STREAM("Frame IDs: "
                  << "mid=" << mid_msg->header.frame_id 
                  << ", up=" << up_msg->header.frame_id 
                  << ", down=" << down_msg->header.frame_id);

  pcl::PointCloud<pcl::PointXYZI> mid_pc, up_pc, down_pc, merged_pc;
  
  // 将 ROS 点云消息转换为 PCL 点云
  pcl::fromROSMsg(*mid_msg, mid_pc);
  pcl::fromROSMsg(*up_msg, up_pc);
  pcl::fromROSMsg(*down_msg, down_pc);

  ROS_INFO("Point clouds converted to PCL format");

  // 合并点云
  merged_pc += mid_pc;
  merged_pc += up_pc;
  merged_pc += down_pc;

  ROS_INFO_STREAM("Merged point cloud size: " << merged_pc.size());

  // 强度调整
  for (auto& p : merged_pc)
    p.intensity = p.intensity * 255.0f + 1.0f; // 修正为精确映射 0→1，1→256

  // 发布拼接并修改强度后的点云
  sensor_msgs::PointCloud2 out;
  pcl::toROSMsg(merged_pc, out);
  out.header.frame_id = "ego_vehicle/lidar_mid"; // 使用实际存在的坐标系
  out.header.stamp = ros::Time::now();
  g_pub.publish(out);
  
  ROS_INFO("Merged point cloud published");
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "point_cloud_processor");
  ros::NodeHandle nh;
  ROS_INFO("Point cloud processor node started!"); 

  // 发布 /lidar_points
  g_pub = nh.advertise<sensor_msgs::PointCloud2>("/lidar_points", 1);

  // 使用 message_filters 来同步三个雷达的话题
  message_filters::Subscriber<sensor_msgs::PointCloud2> mid_sub(nh, "/carla/ego_vehicle/lidar_mid", 100);
  message_filters::Subscriber<sensor_msgs::PointCloud2> up_sub(nh, "/carla/ego_vehicle/lidar_up", 100);
  message_filters::Subscriber<sensor_msgs::PointCloud2> down_sub(nh, "/carla/ego_vehicle/lidar_down", 100);

  // 使用ApproximateTime同步策略
  typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::PointCloud2, sensor_msgs::PointCloud2, sensor_msgs::PointCloud2> MySyncPolicy;
  message_filters::Synchronizer<MySyncPolicy> sync(MySyncPolicy(100), mid_sub, up_sub, down_sub);
  sync.registerCallback(boost::bind(&cloudCB, _1, _2, _3));

  ros::spin();
  return 0;
}

















