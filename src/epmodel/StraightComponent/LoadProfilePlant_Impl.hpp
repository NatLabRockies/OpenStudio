/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_LOADPROFILEPLANT_IMPL_HPP
#define EPMODEL_LOADPROFILEPLANT_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API LoadProfilePlant_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~LoadProfilePlant_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;

  double peakFlowRate() const;
  bool setPeakFlowRate(double peakFlowRate);

  std::string plantLoopFluidType() const;
  bool setPlantLoopFluidType(const std::string& plantLoopFluidType);
  bool isPlantLoopFluidTypeDefaulted() const;
  void resetPlantLoopFluidType();

  std::vector<std::string> plantLoopFluidTypeValues() const;

  double degreeofSubCooling() const;
  bool setDegreeofSubCooling(double degreeofSubCooling);
  bool isDegreeofSubCoolingDefaulted() const;
  void resetDegreeofSubCooling();

  double degreeofLoopSubCooling() const;
  bool setDegreeofLoopSubCooling(double degreeofLoopSubCooling);
  bool isDegreeofLoopSubCoolingDefaulted() const;
  void resetDegreeofLoopSubCooling();

};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
