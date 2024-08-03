#ifndef RADIUS_OUTLIER_REMOVAL_H
#define RADIUS_OUTLIER_REMOVAL_H


#include "sample_filter.h"


namespace SampleFilter
{
class ROR : public Interface
{
 public:
  int sample_filter()
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
  void setRadiusSearch(double ri) { r = ri; }
  void setMinNeighborsInRadius(int num) { num_thre = num; }

 private:
  double r     = 0.3;
  int num_thre = 5;
};

} // namespace SampleFilter


#endif