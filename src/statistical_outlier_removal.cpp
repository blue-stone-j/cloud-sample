
#include <pcl/filters/statistical_outlier_removal.h>

#include "statistical_outlier_removal.h"

SOR::SOR()
{
}
int SOR::sample_filter()
{
  pcl::PointCloud<pcl::PointXYZ>().swap(*cloud_filtered);
  std::vector<double> distances(cloud->size());
  double dis_sqr = 0;
  pcl::shared_ptr<pcl::KdTreeFLANN<pcl::PointXYZ>> searcher(new pcl::KdTreeFLANN<pcl::PointXYZ>());
  searcher->setInputCloud(cloud);

  int valid_distances = 0;
  double dis_mean     = 0;
  std::vector<int> pt_ind;                   // save index of element from kd-tree
  std::vector<float> pt_dis;                 // save distance
  for (size_t i = 0; i < cloud->size(); ++i) // iii = input indices iterator
  {
    // Perform the nearest k search
    if (searcher->nearestKSearch(cloud->points[i], nn + 1, pt_ind, pt_dis) == 0)
    {
      distances[i] = 1000; // set a large value to remove this point
      continue;
    }

    // Calculate the mean distance to its neighbors
    double dist_sum = 0.0;
    for (int k = 1; k < nn + 1; ++k) // k = 0 is the query point
    {
      dist_sum += sqrt(pt_dis[k]);
    }
    distances[i] = dist_sum / nn;
    dis_sqr += distances[i] * distances[i];
    dis_mean += distances[i];
    valid_distances++;
  }
  double variance = (dis_sqr - dis_mean * dis_mean / valid_distances) / (valid_distances - 1);
  double stddev   = sqrt(variance);
  dis_mean /= valid_distances; // stdard deviation
  double thre = dis_mean + mul * stddev;

  for (size_t i = 0; i < cloud->size(); ++i)
  {
    if (distances[i] < thre)
    {
      cloud_filtered->push_back(cloud->points[i]);
    }
  }

  return 0;
}

int main(int argc, char **argv)
{
  SOR sor;
  sor.setCloudPath("../asserts/cloud/fog.pcd");

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