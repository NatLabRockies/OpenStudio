/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EVAPORATIVECOOLERINDIRECTWETCOIL_IMPL_HPP
#define EPMODEL_EVAPORATIVECOOLERINDIRECTWETCOIL_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API EvaporativeCoolerIndirectWetCoil_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~EvaporativeCoolerIndirectWetCoil_Impl() override = default;

  double coilMaximumEfficiency() const;
  bool setCoilMaximumEfficiency(double coilMaximumEfficiency);

  boost::optional<double> coilFlowRatio() const;
  bool setCoilFlowRatio(double coilFlowRatio);
  void resetCoilFlowRatio();

  double recirculatingWaterPumpPowerConsumption() const;
  bool setRecirculatingWaterPumpPowerConsumption(double recirculatingWaterPumpPowerConsumption);

  double secondaryAirFanFlowRate() const;
  bool setSecondaryAirFanFlowRate(double secondaryAirFanFlowRate);

  double secondaryAirFanTotalEfficiency() const;
  bool setSecondaryAirFanTotalEfficiency(double secondaryAirFanTotalEfficiency);

  double secondaryAirFanDeltaPressure() const;
  bool setSecondaryAirFanDeltaPressure(double secondaryAirFanDeltaPressure);

  boost::optional<std::string> controlType() const;
  bool setControlType(const std::string& controlType);
  void resetControlType();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
