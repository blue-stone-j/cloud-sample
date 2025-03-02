#ifndef RADIUS_OUTLIER_REMOVAL_H
#define RADIUS_OUTLIER_REMOVAL_H


#include "interface.h"


namespace SampleFilter
{
class ROR : public Interface
{
 public:
  int sample_filter() override;
  void setRadiusSearch(double ri);
  void setMinNeighborsInRadius(int num);

 private:
  double r          = 0.3;
  int num_threshold = 5;
};

} // namespace SampleFilter


#endif