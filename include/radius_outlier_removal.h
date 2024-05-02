#ifndef RADIUS_OUTLIER_REMOVAL_H
#define RADIUS_OUTLIER_REMOVAL_H


#include "sample_filter.h"

class ROR : public Interface
{
 public:
  int sample_filter();
  void setRadiusSearch(double ri) { r = ri; }
  void setMinNeighborsInRadius(int num) { num_thre = num; }

 private:
  double r     = 0.3;
  int num_thre = 5;
};

#endif