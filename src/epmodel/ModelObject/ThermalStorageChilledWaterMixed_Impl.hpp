/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMALSTORAGECHILLEDBWATERMIXED_IMPL_HPP
#define EPMODEL_THERMALSTORAGECHILLEDBWATERMIXED_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ThermalStorageChilledWaterMixed_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ThermalStorageChilledWaterMixed_Impl() override = default;

      double tankVolume() const;
      bool setTankVolume(double tankVolume);
      bool isTankVolumeDefaulted() const;
      void resetTankVolume();

      double deadbandTemperatureDifference() const;
      bool setDeadbandTemperatureDifference(double deadbandTemperatureDifference);
      bool isDeadbandTemperatureDifferenceDefaulted() const;
      void resetDeadbandTemperatureDifference();

      boost::optional<double> minimumTemperatureLimit() const;
      bool setMinimumTemperatureLimit(double minimumTemperatureLimit);
      void resetMinimumTemperatureLimit();

      boost::optional<double> nominalCoolingCapacity() const;
      bool setNominalCoolingCapacity(double nominalCoolingCapacity);
      void resetNominalCoolingCapacity();

      std::string ambientTemperatureIndicator() const;
      bool setAmbientTemperatureIndicator(const std::string& ambientTemperatureIndicator);

      boost::optional<double> heatGainCoefficientFromAmbientTemperature() const;
      bool setHeatGainCoefficientFromAmbientTemperature(double heatGainCoefficientFromAmbientTemperature);
      void resetHeatGainCoefficientFromAmbientTemperature();

      double useSideHeatTransferEffectiveness() const;
      bool setUseSideHeatTransferEffectiveness(double useSideHeatTransferEffectiveness);
      bool isUseSideHeatTransferEffectivenessDefaulted() const;
      void resetUseSideHeatTransferEffectiveness();

      boost::optional<double> useSideDesignFlowRate() const;
      bool setUseSideDesignFlowRate(double useSideDesignFlowRate);
      bool isUseSideDesignFlowRateDefaulted() const;
      bool isUseSideDesignFlowRateAutosized() const;
      void resetUseSideDesignFlowRate();
      void autosizeUseSideDesignFlowRate();

      double sourceSideHeatTransferEffectiveness() const;
      bool setSourceSideHeatTransferEffectiveness(double sourceSideHeatTransferEffectiveness);
      bool isSourceSideHeatTransferEffectivenessDefaulted() const;
      void resetSourceSideHeatTransferEffectiveness();

      boost::optional<double> sourceSideDesignFlowRate() const;
      bool setSourceSideDesignFlowRate(double sourceSideDesignFlowRate);
      bool isSourceSideDesignFlowRateDefaulted() const;
      bool isSourceSideDesignFlowRateAutosized() const;
      void resetSourceSideDesignFlowRate();
      void autosizeSourceSideDesignFlowRate();

      double tankRecoveryTime() const;
      bool setTankRecoveryTime(double tankRecoveryTime);
      bool isTankRecoveryTimeDefaulted() const;
      void resetTankRecoveryTime();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
