/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMALSTORAGECHILLEDBWATERSTRATIFIED_HPP
#define EPMODEL_THERMALSTORAGECHILLEDBWATERSTRATIFIED_HPP

#include "EPModelAPI.hpp"
#include "WaterToWaterComponent/WaterToWaterComponent.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ThermalStorageChilledWaterStratified_Impl;
  }

  class EPMODEL_API ThermalStorageChilledWaterStratified : public WaterToWaterComponent
  {
   public:
    explicit ThermalStorageChilledWaterStratified(const Model& model);

    virtual ~ThermalStorageChilledWaterStratified() override = default;
    ThermalStorageChilledWaterStratified(const ThermalStorageChilledWaterStratified& other) = default;
    ThermalStorageChilledWaterStratified(ThermalStorageChilledWaterStratified&& other) = default;
    ThermalStorageChilledWaterStratified& operator=(const ThermalStorageChilledWaterStratified&) = default;
    ThermalStorageChilledWaterStratified& operator=(ThermalStorageChilledWaterStratified&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> tankShapeValues();
    static std::vector<std::string> ambientTemperatureIndicatorValues();
    static std::vector<std::string> inletModeValues();

    // Schema Alignment Notes:
    // - Status: Scalar Parity. The stratified thermal-storage scalar surface is aligned, while schedule, zone, and node-link behavior remains excluded.
    // - Canonical Counterpart: openstudio::model::ThermalStorageChilledWaterStratified.
    // - Implemented Parity: Scalar accessors for tank geometry, losses, limits, cooling capacity, effectiveness, inlet/outlet heights, flows, and destratification metadata preserve the canonical model API shape.
    // - Documented Delta: Relationship-like schedule, zone, node/object-reference, and availability APIs are intentionally excluded in this pass.
    // - Field/Storage Mapping: Scalar wrappers target EnergyPlus `ThermalStorage:ChilledWater:Stratified` fields directly, while the excluded links remain in storage-level topology.
    // - Evidence: `src/model/ThermalStorageChilledWaterStratified.hpp`, `src/model/ThermalStorageChilledWaterStratified.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateThermalStorageChilledWaterStratified.cpp`.
    // - Remaining Parity Work: Add the excluded relationship APIs only if the family moves beyond scalar parity.

    double tankVolume() const;
    bool setTankVolume(double tankVolume);

    double tankHeight() const;
    bool setTankHeight(double tankHeight);

    std::string tankShape() const;
    bool setTankShape(const std::string& tankShape);

    boost::optional<double> tankPerimeter() const;
    bool setTankPerimeter(double tankPerimeter);
    void resetTankPerimeter();

    double deadbandTemperatureDifference() const;
    bool setDeadbandTemperatureDifference(double deadbandTemperatureDifference);

    boost::optional<double> temperatureSensorHeight() const;
    bool setTemperatureSensorHeight(double temperatureSensorHeight);
    void resetTemperatureSensorHeight();

    boost::optional<double> minimumTemperatureLimit() const;
    bool setMinimumTemperatureLimit(double minimumTemperatureLimit);
    void resetMinimumTemperatureLimit();

    boost::optional<double> nominalCoolingCapacity() const;
    bool setNominalCoolingCapacity(double nominalCoolingCapacity);
    bool isNominalCoolingCapacityAutosized() const;
    void autosizeNominalCoolingCapacity();

    std::string ambientTemperatureIndicator() const;
    bool setAmbientTemperatureIndicator(const std::string& ambientTemperatureIndicator);

    boost::optional<double> uniformSkinLossCoefficientperUnitAreatoAmbientTemperature() const;
    bool setUniformSkinLossCoefficientperUnitAreatoAmbientTemperature(double uniformSkinLossCoefficientperUnitAreatoAmbientTemperature);
    void resetUniformSkinLossCoefficientperUnitAreatoAmbientTemperature();

    double useSideHeatTransferEffectiveness() const;
    bool setUseSideHeatTransferEffectiveness(double useSideHeatTransferEffectiveness);
    bool isUseSideHeatTransferEffectivenessDefaulted() const;
    void resetUseSideHeatTransferEffectiveness();

    boost::optional<double> useSideInletHeight() const;
    bool setUseSideInletHeight(double useSideInletHeight);
    bool isUseSideInletHeightAutocalculated() const;
    void autocalculateUseSideInletHeight();

    double useSideOutletHeight() const;
    bool setUseSideOutletHeight(double useSideOutletHeight);

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

    double sourceSideInletHeight() const;
    bool setSourceSideInletHeight(double sourceSideInletHeight);

    boost::optional<double> sourceSideOutletHeight() const;
    bool setSourceSideOutletHeight(double sourceSideOutletHeight);
    bool isSourceSideOutletHeightAutocalculated() const;
    void autocalculateSourceSideOutletHeight();

    boost::optional<double> sourceSideDesignFlowRate() const;
    bool setSourceSideDesignFlowRate(double sourceSideDesignFlowRate);
    bool isSourceSideDesignFlowRateDefaulted() const;
    bool isSourceSideDesignFlowRateAutosized() const;
    void resetSourceSideDesignFlowRate();
    void autosizeSourceSideDesignFlowRate();

    double tankRecoveryTime() const;
    bool setTankRecoveryTime(double tankRecoveryTime);

    std::string inletMode() const;
    bool setInletMode(const std::string& inletMode);

    int numberofNodes() const;
    bool setNumberofNodes(int numberofNodes);

    double additionalDestratificationConductivity() const;
    bool setAdditionalDestratificationConductivity(double additionalDestratificationConductivity);

    double node1AdditionalLossCoefficient() const;
    bool setNode1AdditionalLossCoefficient(double node1AdditionalLossCoefficient);

    double node2AdditionalLossCoefficient() const;
    bool setNode2AdditionalLossCoefficient(double node2AdditionalLossCoefficient);

    double node3AdditionalLossCoefficient() const;
    bool setNode3AdditionalLossCoefficient(double node3AdditionalLossCoefficient);

    double node4AdditionalLossCoefficient() const;
    bool setNode4AdditionalLossCoefficient(double node4AdditionalLossCoefficient);

    double node5AdditionalLossCoefficient() const;
    bool setNode5AdditionalLossCoefficient(double node5AdditionalLossCoefficient);

    double node6AdditionalLossCoefficient() const;
    bool setNode6AdditionalLossCoefficient(double node6AdditionalLossCoefficient);

    double node7AdditionalLossCoefficient() const;
    bool setNode7AdditionalLossCoefficient(double node7AdditionalLossCoefficient);

    double node8AdditionalLossCoefficient() const;
    bool setNode8AdditionalLossCoefficient(double node8AdditionalLossCoefficient);

    double node9AdditionalLossCoefficient() const;
    bool setNode9AdditionalLossCoefficient(double node9AdditionalLossCoefficient);

    double node10AdditionalLossCoefficient() const;
    bool setNode10AdditionalLossCoefficient(double node10AdditionalLossCoefficient);

   protected:
    using ImplType = detail::ThermalStorageChilledWaterStratified_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ThermalStorageChilledWaterStratified(std::shared_ptr<detail::ThermalStorageChilledWaterStratified_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
