#ifndef FARTHEST_POINT_SAMPLE_H
#define FARTHEST_POINT_SAMPLE_H

#include <cmath>
#include <iostream>
#include <vector>

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
void farthest_point_sampling_cpu(int b, int n, int m, const float *dataset, float *temp, int *idxs)
{
  const float *const dataset_start = dataset;
  float *const temp_start          = temp;
  int *const idxs_start            = idxs;
  // traverse batches
  for (int i = 0; i < b; ++i)
  {
    dataset = dataset_start + i * n * 3;
    temp    = temp_start + i * n;
    idxs    = idxs_start + i * m;
    int old = 0;
    idxs[0] = old;
    //! it seems that here is a bug
    for (int j = 1; j < m; ++j) // m is num of points that we want
    {
      int besti  = 0;
      float best = -1;
      float x1   = dataset[old * 3 + 0]; // point in A
      float y1   = dataset[old * 3 + 1];
      float z1   = dataset[old * 3 + 2];
      for (int k = 0; k < n; ++k)
      {
        float x2, y2, z2;
        x2 = dataset[k * 3 + 0]; // point in B
        y2 = dataset[k * 3 + 1];
        z2 = dataset[k * 3 + 2];

        float d  = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) + (z2 - z1) * (z2 - z1);
        float d2 = std::min(d, temp[k]);
        temp[k]  = d2; // distance betweeen kth point and set A
        besti    = d2 > best ? k : besti;
        best     = d2 > best ? d2 : best;
      }
      old     = besti;
      idxs[j] = old;
    }
  }
}

typedef struct point
{
  int x;
  int y;
  int z;
} Point;

float GetDistance(Point &p1, Point &p2)
{
  return std::sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
}

std::vector<Point> GetFPS(std::vector<Point> &input, const int num)
{
  std::vector<Point> output;
  output.emplace_back(input[0]);
  auto tmp = input;
  tmp.erase(tmp.begin());
  while (output.size() <= num)
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

#endif