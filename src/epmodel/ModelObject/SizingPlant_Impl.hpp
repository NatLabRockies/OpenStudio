/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SIZINGPLANT_IMPL_HPP
#define EPMODEL_SIZINGPLANT_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

class PlantLoop;

namespace detail {

class EPMODEL_API SizingPlant_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~SizingPlant_Impl() override = default;

  std::string loopType() const;
  double designLoopExitTemperature() const;
  double loopDesignTemperatureDifference() const;
  std::string sizingOption() const;
  int zoneTimestepsinAveragingWindow() const;
  std::string coincidentSizingFactorMode() const;

  bool setLoopType(const std::string& loopType);
  bool setDesignLoopExitTemperature(double designLoopExitTemperature);
  bool setLoopDesignTemperatureDifference(double loopDesignTemperatureDifference);
  bool setSizingOption(const std::string& sizingOption);
  bool setZoneTimestepsinAveragingWindow(int zoneTimestepsinAveragingWindow);
  bool setCoincidentSizingFactorMode(const std::string& coincidentSizingFactorMode);
  bool setPlantLoop(const openstudio::epmodel::PlantLoop& plantLoop);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
