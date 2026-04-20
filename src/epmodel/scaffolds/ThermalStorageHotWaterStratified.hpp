/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMALSTORAGEHOTWATERSTRATIFIED_HPP
#define EPMODEL_THERMALSTORAGEHOTWATERSTRATIFIED_HPP

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
    class ThermalStorageHotWaterStratified_Impl;
  }

  class EPMODEL_API ThermalStorageHotWaterStratified : public ModelObject
  {
   public:
    explicit ThermalStorageHotWaterStratified(const Model& model);

    virtual ~ThermalStorageHotWaterStratified() override = default;
    ThermalStorageHotWaterStratified(const ThermalStorageHotWaterStratified& other) = default;
    ThermalStorageHotWaterStratified(ThermalStorageHotWaterStratified&& other) = default;
    ThermalStorageHotWaterStratified& operator=(const ThermalStorageHotWaterStratified&) = default;
    ThermalStorageHotWaterStratified& operator=(ThermalStorageHotWaterStratified&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> tankShapeValues();
    static std::vector<std::string> ambientTemperatureIndicatorValues();
    static std::vector<std::string> inletModeValues();

    // Schema Alignment Notes:
    // - API: No openstudio::model counterpart exists, so we honor the IDD-derived ThermalStorageHotWaterStratified naming.
    // - Field Mapping: Simple scalar accessors map directly to the scalar ThermalStorage:HotWater:Stratified fields.
    // - Field Mapping: Schedule, zone, and node relationships (ambient setpoint schedules, availability schedules, and inlet/outlet nodes)
    //   remain relationship-like and are intentionally excluded from this scalar-only scaffolding.
    // - TODO(parity): Add non-scalar helpers once scalar saturation for this type is complete.

    double tankVolume() const;
    bool setTankVolume(double tankVolume);

    double tankHeight() const;
    bool setTankHeight(double tankHeight);

    std::string tankShape() const;
    bool setTankShape(const std::string& tankShape);
    bool isTankShapeDefaulted() const;
    void resetTankShape();

    boost::optional<double> tankPerimeter() const;
    bool setTankPerimeter(double tankPerimeter);
    void resetTankPerimeter();

    double deadbandTemperatureDifference() const;
    bool setDeadbandTemperatureDifference(double deadbandTemperatureDifference);
    bool isDeadbandTemperatureDifferenceDefaulted() const;
    void resetDeadbandTemperatureDifference();

    boost::optional<double> topTemperatureSensorHeight() const;
    bool setTopTemperatureSensorHeight(double topTemperatureSensorHeight);
    void resetTopTemperatureSensorHeight();

    boost::optional<double> bottomTemperatureSensorHeight() const;
    bool setBottomTemperatureSensorHeight(double bottomTemperatureSensorHeight);
    void resetBottomTemperatureSensorHeight();

    boost::optional<double> maximumTemperatureLimit() const;
    bool setMaximumTemperatureLimit(double maximumTemperatureLimit);
    void resetMaximumTemperatureLimit();

    boost::optional<double> nominalHeatingCapacity() const;
    bool setNominalHeatingCapacity(double nominalHeatingCapacity);
    bool isNominalHeatingCapacityDefaulted() const;
    bool isNominalHeatingCapacityAutosized() const;
    void resetNominalHeatingCapacity();
    void autosizeNominalHeatingCapacity();

    std::string ambientTemperatureIndicator() const;
    bool setAmbientTemperatureIndicator(const std::string& ambientTemperatureIndicator);

    boost::optional<double> uniformSkinLossCoefficientPerUnitAreaToAmbientTemperature() const;
    bool setUniformSkinLossCoefficientPerUnitAreaToAmbientTemperature(double uniformSkinLossCoefficientPerUnitAreaToAmbientTemperature);
    void resetUniformSkinLossCoefficientPerUnitAreaToAmbientTemperature();

    boost::optional<std::string> useSideFlowDirectionSchedule() const;
    bool setUseSideFlowDirectionSchedule(const std::string& useSideFlowDirectionSchedule);
    void resetUseSideFlowDirectionSchedule();

    double useSideHeatTransferEffectiveness() const;
    bool setUseSideHeatTransferEffectiveness(double useSideHeatTransferEffectiveness);
    bool isUseSideHeatTransferEffectivenessDefaulted() const;
    void resetUseSideHeatTransferEffectiveness();

    boost::optional<double> useSideInletHeight() const;
    bool setUseSideInletHeight(double useSideInletHeight);
    bool isUseSideInletHeightDefaulted() const;
    bool isUseSideInletHeightAutocalculated() const;
    void resetUseSideInletHeight();
    void autocalculateUseSideInletHeight();

    double useSideOutletHeight() const;
    bool setUseSideOutletHeight(double useSideOutletHeight);
    bool isUseSideOutletHeightDefaulted() const;
    void resetUseSideOutletHeight();

    boost::optional<double> useSideDesignFlowRate() const;
    bool setUseSideDesignFlowRate(double useSideDesignFlowRate);
    bool isUseSideDesignFlowRateDefaulted() const;
    bool isUseSideDesignFlowRateAutosized() const;
    void resetUseSideDesignFlowRate();
    void autosizeUseSideDesignFlowRate();

    boost::optional<std::string> sourceSideFlowDirectionSchedule() const;
    bool setSourceSideFlowDirectionSchedule(const std::string& sourceSideFlowDirectionSchedule);
    void resetSourceSideFlowDirectionSchedule();

    double sourceSideHeatTransferEffectiveness() const;
    bool setSourceSideHeatTransferEffectiveness(double sourceSideHeatTransferEffectiveness);
    bool isSourceSideHeatTransferEffectivenessDefaulted() const;
    void resetSourceSideHeatTransferEffectiveness();

    boost::optional<double> sourceSideInletHeight() const;
    bool setSourceSideInletHeight(double sourceSideInletHeight);
    bool isSourceSideInletHeightDefaulted() const;
    void resetSourceSideInletHeight();

    boost::optional<double> sourceSideOutletHeight() const;
    bool setSourceSideOutletHeight(double sourceSideOutletHeight);
    bool isSourceSideOutletHeightDefaulted() const;
    bool isSourceSideOutletHeightAutocalculated() const;
    void resetSourceSideOutletHeight();
    void autocalculateSourceSideOutletHeight();

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

    std::string inletMode() const;
    bool setInletMode(const std::string& inletMode);
    bool isInletModeDefaulted() const;
    void resetInletMode();

    int numberOfNodes() const;
    bool setNumberOfNodes(int numberOfNodes);
    bool isNumberOfNodesDefaulted() const;
    void resetNumberOfNodes();

    double additionalDestratificationConductivity() const;
    bool setAdditionalDestratificationConductivity(double additionalDestratificationConductivity);
    bool isAdditionalDestratificationConductivityDefaulted() const;
    void resetAdditionalDestratificationConductivity();

    double node1AdditionalLossCoefficient() const;
    bool setNode1AdditionalLossCoefficient(double node1AdditionalLossCoefficient);
    bool isNode1AdditionalLossCoefficientDefaulted() const;
    void resetNode1AdditionalLossCoefficient();

    double node2AdditionalLossCoefficient() const;
    bool setNode2AdditionalLossCoefficient(double node2AdditionalLossCoefficient);
    bool isNode2AdditionalLossCoefficientDefaulted() const;
    void resetNode2AdditionalLossCoefficient();

    double node3AdditionalLossCoefficient() const;
    bool setNode3AdditionalLossCoefficient(double node3AdditionalLossCoefficient);
    bool isNode3AdditionalLossCoefficientDefaulted() const;
    void resetNode3AdditionalLossCoefficient();

    double node4AdditionalLossCoefficient() const;
    bool setNode4AdditionalLossCoefficient(double node4AdditionalLossCoefficient);
    bool isNode4AdditionalLossCoefficientDefaulted() const;
    void resetNode4AdditionalLossCoefficient();

    double node5AdditionalLossCoefficient() const;
    bool setNode5AdditionalLossCoefficient(double node5AdditionalLossCoefficient);
    bool isNode5AdditionalLossCoefficientDefaulted() const;
    void resetNode5AdditionalLossCoefficient();

    double node6AdditionalLossCoefficient() const;
    bool setNode6AdditionalLossCoefficient(double node6AdditionalLossCoefficient);
    bool isNode6AdditionalLossCoefficientDefaulted() const;
    void resetNode6AdditionalLossCoefficient();

    double node7AdditionalLossCoefficient() const;
    bool setNode7AdditionalLossCoefficient(double node7AdditionalLossCoefficient);
    bool isNode7AdditionalLossCoefficientDefaulted() const;
    void resetNode7AdditionalLossCoefficient();

    double node8AdditionalLossCoefficient() const;
    bool setNode8AdditionalLossCoefficient(double node8AdditionalLossCoefficient);
    bool isNode8AdditionalLossCoefficientDefaulted() const;
    void resetNode8AdditionalLossCoefficient();

    double node9AdditionalLossCoefficient() const;
    bool setNode9AdditionalLossCoefficient(double node9AdditionalLossCoefficient);
    bool isNode9AdditionalLossCoefficientDefaulted() const;
    void resetNode9AdditionalLossCoefficient();

    double node10AdditionalLossCoefficient() const;
    bool setNode10AdditionalLossCoefficient(double node10AdditionalLossCoefficient);
    bool isNode10AdditionalLossCoefficientDefaulted() const;
    void resetNode10AdditionalLossCoefficient();

   protected:
    using ImplType = detail::ThermalStorageHotWaterStratified_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ThermalStorageHotWaterStratified(std::shared_ptr<detail::ThermalStorageHotWaterStratified_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
