#ifndef FAR_OUTLIERS_REMOVAL_H
#define FAR_OUTLIERS_REMOVAL_H

#include "interface.h"

namespace SampleFilter
{
struct FaroutliersRemovalParams
{
  float ratio  = 0.2;
  float minDis = 5, maxDis = 100, thrDis = 3;
};

class FaroutliersRemoval : public Interface
{};
} // namespace SampleFilter

#endif