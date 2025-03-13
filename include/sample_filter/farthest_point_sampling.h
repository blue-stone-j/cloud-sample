#ifndef FARTHEST_POINT_SAMPLE_H
#define FARTHEST_POINT_SAMPLE_H

#include <cmath>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>

namespace SampleFilter
{
/*
total: n in one batch
set A: m
set B: n-m
b: batch
dataset: (b, n, 3)
temp: (b, n)
idxs: (b, m)
*/
void farthest_point_sampling_cpu(int b, int n, int m,
                                 const pcl::PointCloud<pcl::PointXYZ> &dataset,
                                 std::vector<float> &temp, std::vector<int> &idxs);

float GetDistance(pcl::PointXYZ &p1, pcl::PointXYZ &p2);

pcl::PointCloud<pcl::PointXYZ> GetFPS(pcl::PointCloud<pcl::PointXYZ> &input, const int num);
} // namespace SampleFilter

#endif