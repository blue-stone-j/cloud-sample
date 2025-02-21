#ifndef GRID_SAMPLE_H
#define GRID_SAMPLE_H

#include "interface.h"

namespace SampleFilter
{
struct GridSampleParams
{
  float ratio  = 0.2;
  float minDis = 5, maxDis = 100, thrDis = 3;
};

class GridSample : public Interface
{};

} // namespace SampleFilter

#endif