#include <pcl/filters/radius_outlier_removal.h>

#include "radius_outlier_removal.h"

int ROR::sample_filter()
{
  std::vector<int> pt_ind;   // save index of element from kd-tree
  std::vector<float> pt_dis; // save distance
  pcl::shared_ptr<pcl::KdTreeFLANN<pcl::PointXYZ>> searcher(new pcl::KdTreeFLANN<pcl::PointXYZ>());
  searcher->setInputCloud(cloud);
  std::cout << r << ", " << num_thre << std::endl;
  for (size_t i = 0; i < cloud->size(); ++i) // iii = input indices iterator
  {
    // Perform the nearest search
    if (searcher->radiusSearch(cloud->points[i], r, pt_ind, pt_dis) > num_thre)
    {
      cloud_filtered->push_back(cloud->points[i]);
    }
  }

  return 0;
}

int main(int argc, char **argv)
{
  ROR ror;
  ror.setCloudPath("../asserts/cloud/fog.pcd");

  // pcl
  pcl::PointCloud<pcl::PointXYZ> cloud_filtered;
  pcl::RadiusOutlierRemoval<pcl::PointXYZ> outrem;
  outrem.setInputCloud(ror.cloud);
  outrem.setRadiusSearch(0.3);       // 设置搜索半径
  outrem.setMinNeighborsInRadius(5); // 设置半径内最小邻近点数
  outrem.filter(cloud_filtered);
  pcl::io::savePCDFileBinary("../result/filtered_point_cloud0.pcd", cloud_filtered);
  std::cout << "pcl: " << ror.cloud->size() << ", " << cloud_filtered.size() << std::endl;

  // customized
  ror.sample_filter();
  ror.saveCloud("../result/filtered_point_cloud1.pcd");
  std::cout << "nne: " << ror.cloud->size() << ", " << ror.cloud_filtered->size() << std::endl;

  return 0;
}