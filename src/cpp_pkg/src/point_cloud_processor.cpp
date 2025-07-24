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
    p.intensity = p.intensity * 255.0f + 1.0f; // 精确映射 0→1，1→256

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
