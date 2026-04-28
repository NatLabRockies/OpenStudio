/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FANPERFORMANCENIGHTVENTILATION_IMPL_HPP
#define EPMODEL_FANPERFORMANCENIGHTVENTILATION_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API FanPerformanceNightVentilation_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~FanPerformanceNightVentilation_Impl() override = default;

  double fanTotalEfficiency() const;
  bool setFanTotalEfficiency(double fanTotalEfficiency);

  double pressureRise() const;
  bool setPressureRise(double pressureRise);

  boost::optional<double> maximumFlowRate() const;
  bool isMaximumFlowRateAutosized() const;
  bool setMaximumFlowRate(double maximumFlowRate);
  void resetMaximumFlowRate();
  void autosizeMaximumFlowRate();

  double motorEfficiency() const;
  bool setMotorEfficiency(double motorEfficiency);

  double motorinAirstreamFraction() const;
  bool isMotorinAirstreamFractionDefaulted() const;
  bool setMotorinAirstreamFraction(double motorinAirstreamFraction);
  void resetMotorinAirstreamFraction();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
