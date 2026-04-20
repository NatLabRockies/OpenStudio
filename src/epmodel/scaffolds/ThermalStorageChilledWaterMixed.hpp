/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMALSTORAGECHILLEDBWATERMIXED_HPP
#define EPMODEL_THERMALSTORAGECHILLEDBWATERMIXED_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ThermalStorageChilledWaterMixed_Impl;
  }

  class EPMODEL_API ThermalStorageChilledWaterMixed : public ModelObject
  {
   public:
    explicit ThermalStorageChilledWaterMixed(const Model& model);

    virtual ~ThermalStorageChilledWaterMixed() override = default;
    ThermalStorageChilledWaterMixed(const ThermalStorageChilledWaterMixed& other) = default;
    ThermalStorageChilledWaterMixed(ThermalStorageChilledWaterMixed&& other) = default;
    ThermalStorageChilledWaterMixed& operator=(const ThermalStorageChilledWaterMixed&) = default;
    ThermalStorageChilledWaterMixed& operator=(ThermalStorageChilledWaterMixed&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> ambientTemperatureIndicatorValues();

    // Schema Alignment Notes:
    // - API: No openstudio::model counterpart exists, so IDD-derived class and accessor names are preserved.
    // - Field Mapping: Scalar methods map directly to the non-relationship ThermalStorage:ChilledWater:Mixed fields (tank volume, deadband temperature difference, nominal cooling capacity, temperature limits, heat transfer effectiveness, design flow rates, heat gain coefficient, and tank recovery time).
    // - Field Mapping: Object-list/node fields (ambient temperature schedule/zone, ambient temperature node, use/source availability schedules, and inlet/outlet node names) are relationship-like and intentionally excluded from this scalar-only scaffold.
    // - TODO(parity): Add remaining relationship APIs once scalar saturation for this type is complete.

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

   protected:
    using ImplType = detail::ThermalStorageChilledWaterMixed_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ThermalStorageChilledWaterMixed(std::shared_ptr<detail::ThermalStorageChilledWaterMixed_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
