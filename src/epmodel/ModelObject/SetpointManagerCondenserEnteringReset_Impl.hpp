/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERCONDENSERENTERINGRESET_IMPL_HPP
#define EPMODEL_SETPOINTMANAGERCONDENSERENTERINGRESET_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API SetpointManagerCondenserEnteringReset_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~SetpointManagerCondenserEnteringReset_Impl() override = default;

  std::string controlVariable() const;
  bool isControlVariableDefaulted() const;
  bool setControlVariable(const std::string& controlVariable);
  void resetControlVariable();

  double minimumLift() const;
  bool isMinimumLiftDefaulted() const;
  bool setMinimumLift(double minimumLift);
  void resetMinimumLift();

  double maximumCondenserEnteringWaterTemperature() const;
  bool isMaximumCondenserEnteringWaterTemperatureDefaulted() const;
  bool setMaximumCondenserEnteringWaterTemperature(double maximumCondenserEnteringWaterTemperature);
  void resetMaximumCondenserEnteringWaterTemperature();

  double coolingTowerDesignInletAirWetBulbTemperature() const;
  bool isCoolingTowerDesignInletAirWetBulbTemperatureDefaulted() const;
  bool setCoolingTowerDesignInletAirWetBulbTemperature(double coolingTowerDesignInletAirWetBulbTemperature);
  void resetCoolingTowerDesignInletAirWetBulbTemperature();

  std::vector<std::string> controlVariableValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
