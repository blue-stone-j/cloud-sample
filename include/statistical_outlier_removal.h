#ifndef STATISTICAL_OUTLIER_REMOVAL_H
#define STATISTICAL_OUTLIER_REMOVAL_H

#include "sample_filter.h"

// StatisticalOutlierRemoval
class SOR : public Interface
{
 public:
  SOR();
  void setMeanK(int nni) { nn = nni; }
  void setStddevMulThresh(double smt) { mul = smt; }
  int sample_filter();

 private:
  int nn     = 30; // num of neighbors
  double mul = 0.5;
};

#endif