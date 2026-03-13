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
      bool setLatentHeatduringtheEntirePhaseChangeProcess(double latentHeatduringtheEntirePhaseChangeProcess);

      double liquidStateThermalConductivity() const;
      bool setLiquidStateThermalConductivity(double liquidStateThermalConductivity);

      double liquidStateDensity() const;
      bool setLiquidStateDensity(double liquidStateDensity);

      double liquidStateSpecificHeat() const;
      bool setLiquidStateSpecificHeat(double liquidStateSpecificHeat);

      double highTemperatureDifferenceofMeltingCurve() const;
      bool setHighTemperatureDifferenceofMeltingCurve(double highTemperatureDifferenceofMeltingCurve);

      double peakMeltingTemperature() const;
      bool setPeakMeltingTemperature(double peakMeltingTemperature);

      double lowTemperatureDifferenceofMeltingCurve() const;
      bool setLowTemperatureDifferenceofMeltingCurve(double lowTemperatureDifferenceofMeltingCurve);

      double solidStateThermalConductivity() const;
      bool setSolidStateThermalConductivity(double solidStateThermalConductivity);

      double solidStateDensity() const;
      bool setSolidStateDensity(double solidStateDensity);

      double solidStateSpecificHeat() const;
      bool setSolidStateSpecificHeat(double solidStateSpecificHeat);

      double highTemperatureDifferenceofFreezingCurve() const;
      bool setHighTemperatureDifferenceofFreezingCurve(double highTemperatureDifferenceofFreezingCurve);

      double peakFreezingTemperature() const;
      bool setPeakFreezingTemperature(double peakFreezingTemperature);

      double lowTemperatureDifferenceofFreezingCurve() const;
      bool setLowTemperatureDifferenceofFreezingCurve(double lowTemperatureDifferenceofFreezingCurve);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
