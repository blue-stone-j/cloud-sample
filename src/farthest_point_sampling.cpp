#include "sample_filter/farthest_point_sampling.h"

namespace SampleFilter
{
void farthest_point_sampling_cpu(int b, int n, int m,
                                 const pcl::PointCloud<pcl::PointXYZ> &dataset,
                                 std::vector<float> &temp, std::vector<int> &idxs)
{
  for (int i = 0; i < b; ++i)
  {
    int index   = 0;
    idxs[i * m] = index;
    for (int j = 1; j < m; ++j) // Select m points
    {
      int best_i = 0;
      float best = -1.0f;

      const pcl::PointXYZ &p1 = dataset[i * n + index];

      for (int k = 0; k < n; ++k)
      {
        const pcl::PointXYZ &p2 = dataset[i * n + k];
        float d                 = (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y) + (p2.z - p1.z) * (p2.z - p1.z);

        float d2        = std::min(d, temp[i * n + k]);
        temp[i * n + k] = d2;

        if (d2 > best)
        {
          best   = d2;
          best_i = k;
        }
      }

      index           = best_i;
      idxs[i * m + j] = index;
    }
  }
}

float GetDistance(pcl::PointXYZ &p1, pcl::PointXYZ &p2)
{
  return std::sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
}

pcl::PointCloud<pcl::PointXYZ> GetFPS(pcl::PointCloud<pcl::PointXYZ> &input, const int num)
{
  pcl::PointCloud<pcl::PointXYZ> output;
  output.emplace_back(input[0]);
  auto tmp = input;
  tmp.erase(tmp.begin());
  while (static_cast<int>(output.size()) <= num)
  {
    float max_distance = 0.f;
    int index          = 0;
    for (auto it = tmp.begin(); it != tmp.end(); ++it)
    {
      float min_distance = 0.f;
      for (auto it2 = output.begin(); it2 != output.end(); ++it2)
      {
        min_distance = std::min(GetDistance(*it, *it2), min_distance);
      }
      if (max_distance < min_distance)
      {
        max_distance = min_distance;
        index        = it - tmp.begin();
      }
    }
    output.emplace_back(tmp[index]);
    tmp.erase(tmp.begin() + index);
  }
  return output;
}
} // namespace SampleFilter