
#include <pcl/filters/statistical_outlier_removal.h>

#include "statistical_outlier_removal.h"

int main(int argc, char **argv)
{
  SOR sor;
  sor.setCloudPath("../assets/cloud/fog.pcd");

  // pcl
  pcl::StatisticalOutlierRemoval<pcl::PointXYZ> osor;
  pcl::PointCloud<pcl::PointXYZ> cloud_filtered;
  osor.setInputCloud(sor.cloud);
  osor.setMeanK(30);            // 设置在进行均值和标准差计算时考虑的邻近点个数
  osor.setStddevMulThresh(0.5); // 设置标准差倍数阈值: 距离超过 整体平均距离 + 1 × 标准差 的点都会被视为离群点并被移除
  osor.filter(cloud_filtered);
  pcl::io::savePCDFileBinary("../result/filtered_point_cloud0.pcd", cloud_filtered);
  std::cout << "pcl: " << sor.cloud->size() << ", " << cloud_filtered.size() << std::endl;

  // customized
  sor.sample_filter();
  sor.saveCloud("../result/filtered_point_cloud1.pcd");
  std::cout << "nne: " << sor.cloud->size() << ", " << sor.cloud_filtered->size() << std::endl;

  return 0;
}