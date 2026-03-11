/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MATERIALPROPERTYPHASECHANGEHYSTERESIS_IMPL_HPP
#define EPMODEL_MATERIALPROPERTYPHASECHANGEHYSTERESIS_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API MaterialPropertyPhaseChangeHysteresis_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~MaterialPropertyPhaseChangeHysteresis_Impl() override = default;

  double latentHeatduringtheEntirePhaseChangeProcess() const;
  double liquidStateThermalConductivity() const;
  double liquidStateDensity() const;
  double liquidStateSpecificHeat() const;
  double highTemperatureDifferenceofMeltingCurve() const;
  double peakMeltingTemperature() const;
  double lowTemperatureDifferenceofMeltingCurve() const;
  double solidStateThermalConductivity() const;
  double solidStateDensity() const;
  double solidStateSpecificHeat() const;
  double highTemperatureDifferenceofFreezingCurve() const;
  double peakFreezingTemperature() const;
  double lowTemperatureDifferenceofFreezingCurve() const;

  bool setLatentHeatduringtheEntirePhaseChangeProcess(double latentHeatduringtheEntirePhaseChangeProcess);
  bool setLiquidStateThermalConductivity(double liquidStateThermalConductivity);
  bool setLiquidStateDensity(double liquidStateDensity);
  bool setLiquidStateSpecificHeat(double liquidStateSpecificHeat);
  bool setHighTemperatureDifferenceofMeltingCurve(double highTemperatureDifferenceofMeltingCurve);
  bool setPeakMeltingTemperature(double peakMeltingTemperature);
  bool setLowTemperatureDifferenceofMeltingCurve(double lowTemperatureDifferenceofMeltingCurve);
  bool setSolidStateThermalConductivity(double solidStateThermalConductivity);
  bool setSolidStateDensity(double solidStateDensity);
  bool setSolidStateSpecificHeat(double solidStateSpecificHeat);
  bool setHighTemperatureDifferenceofFreezingCurve(double highTemperatureDifferenceofFreezingCurve);
  bool setPeakFreezingTemperature(double peakFreezingTemperature);
  bool setLowTemperatureDifferenceofFreezingCurve(double lowTemperatureDifferenceofFreezingCurve);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
