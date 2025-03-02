#ifndef FARTHEST_POINT_SAMPLE_H
#define FARTHEST_POINT_SAMPLE_H

#include <cmath>
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
void farthest_point_sampling_cpu(int b, int n, int m, const float *dataset, float *temp, int *idxs);

typedef struct point
{
  int x;
  int y;
  int z;
} Point;

float GetDistance(Point &p1, Point &p2);

std::vector<Point> GetFPS(std::vector<Point> &input, const int num);
} // namespace SampleFilter

#endif