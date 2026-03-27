/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACLOWTEMPRADIANTVARFLOW_HPP
#define EPMODEL_ZONEHVACLOWTEMPRADIANTVARFLOW_HPP

#include "EPModelAPI.hpp"
#include "ZoneHVACComponent/ZoneHVACComponent.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneHVACLowTempRadiantVarFlow_Impl;
  }

  class EPMODEL_API ZoneHVACLowTempRadiantVarFlow : public ZoneHVACComponent
  {
   public:
    explicit ZoneHVACLowTempRadiantVarFlow(const Model& model);

    virtual ~ZoneHVACLowTempRadiantVarFlow() override = default;
    ZoneHVACLowTempRadiantVarFlow(const ZoneHVACLowTempRadiantVarFlow& other) = default;
    ZoneHVACLowTempRadiantVarFlow(ZoneHVACLowTempRadiantVarFlow&& other) = default;
    ZoneHVACLowTempRadiantVarFlow& operator=(const ZoneHVACLowTempRadiantVarFlow&) = default;
    ZoneHVACLowTempRadiantVarFlow& operator=(ZoneHVACLowTempRadiantVarFlow&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> numberofCircuitsValues();
    static std::vector<std::string> fluidtoRadiantSurfaceHeatTransferModelValues();
    static std::vector<std::string> temperatureControlTypeValues();
    static std::vector<std::string> setpointControlTypeValues();
    static std::vector<std::string> heatingDesignCapacityMethodValues();
    static std::vector<std::string> coolingDesignCapacityMethodValues();
    static std::vector<std::string> condensationControlTypeValues();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The hydronic and control scalars are aligned, but surface-group and node wiring remain relationship-driven.
    // - Canonical Counterpart: openstudio::model::ZoneHVACLowTempRadiantVarFlow.
    // - Implemented Parity: The variable-flow radiant scalar groups map directly to the EnergyPlus object and its companion design object.
    // - Documented Delta: Surface-group membership, node wiring, and other relationship-style links are not surfaced as scalar accessors.
    // - Field/Storage Mapping: Scalar values live on the EnergyPlus object and companion design object, while the omitted links are handled through topology state and child-object APIs.
    // - Evidence: `src/model/ZoneHVACLowTempRadiantVarFlow.hpp`, `src/model/ZoneHVACLowTempRadiantVarFlow.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACLowTempRadiantVarFlow.cpp`, and `src/epmodel/test/ZoneHVACLowTempRadiantVarFlow_GTest.cpp`.
    // - Remaining Parity Work: Add relationship helpers only if the canonical wrapper continues to require them directly.

    boost::optional<double> hydronicTubingLength() const;
    bool isHydronicTubingLengthAutosized() const;
    bool setHydronicTubingLength(double hydronicTubingLength);
    void autosizeHydronicTubingLength();

    boost::optional<double> heatingDesignCapacity() const;
    bool isHeatingDesignCapacityAutosized() const;
    bool setHeatingDesignCapacity(double heatingDesignCapacity);
    void autosizeHeatingDesignCapacity();

    boost::optional<double> maximumHotWaterFlow() const;
    bool isMaximumHotWaterFlowAutosized() const;
    bool setMaximumHotWaterFlow(double maximumHotWaterFlow);
    void autosizeMaximumHotWaterFlow();

    boost::optional<double> coolingDesignCapacity() const;
    bool isCoolingDesignCapacityAutosized() const;
    bool setCoolingDesignCapacity(double coolingDesignCapacity);
    void autosizeCoolingDesignCapacity();

    boost::optional<double> maximumColdWaterFlow() const;
    bool isMaximumColdWaterFlowAutosized() const;
    bool setMaximumColdWaterFlow(double maximumColdWaterFlow);
    void autosizeMaximumColdWaterFlow();

    std::string fluidtoRadiantSurfaceHeatTransferModel() const;
    bool isFluidtoRadiantSurfaceHeatTransferModelDefaulted() const;
    bool setFluidtoRadiantSurfaceHeatTransferModel(const std::string& fluidtoRadiantSurfaceHeatTransferModel);
    void resetFluidtoRadiantSurfaceHeatTransferModel();

    double hydronicTubingInsideDiameter() const;
    bool isHydronicTubingInsideDiameterDefaulted() const;
    bool setHydronicTubingInsideDiameter(double hydronicTubingInsideDiameter);
    void resetHydronicTubingInsideDiameter();

    double hydronicTubingOutsideDiameter() const;
    bool isHydronicTubingOutsideDiameterDefaulted() const;
    bool setHydronicTubingOutsideDiameter(double hydronicTubingOutsideDiameter);
    void resetHydronicTubingOutsideDiameter();

    double hydronicTubingConductivity() const;
    bool isHydronicTubingConductivityDefaulted() const;
    bool setHydronicTubingConductivity(double hydronicTubingConductivity);
    void resetHydronicTubingConductivity();

    std::string temperatureControlType() const;
    bool isTemperatureControlTypeDefaulted() const;
    bool setTemperatureControlType(const std::string& temperatureControlType);
    void resetTemperatureControlType();

    std::string setpointControlType() const;
    bool isSetpointControlTypeDefaulted() const;
    bool setSetpointControlType(const std::string& setpointControlType);
    void resetSetpointControlType();

    std::string heatingDesignCapacityMethod() const;
    bool isHeatingDesignCapacityMethodDefaulted() const;
    bool setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod);
    void resetHeatingDesignCapacityMethod();

    boost::optional<double> heatingDesignCapacityPerFloorArea() const;
    bool setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea);
    void resetHeatingDesignCapacityPerFloorArea();

    double fractionofAutosizedHeatingDesignCapacity() const;
    bool isFractionofAutosizedHeatingDesignCapacityDefaulted() const;
    bool setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity);
    void resetFractionofAutosizedHeatingDesignCapacity();

    double heatingControlThrottlingRange() const;
    bool isHeatingControlThrottlingRangeDefaulted() const;
    bool setHeatingControlThrottlingRange(double heatingControlThrottlingRange);
    void resetHeatingControlThrottlingRange();

    std::string coolingDesignCapacityMethod() const;
    bool isCoolingDesignCapacityMethodDefaulted() const;
    bool setCoolingDesignCapacityMethod(const std::string& coolingDesignCapacityMethod);
    void resetCoolingDesignCapacityMethod();

    boost::optional<double> coolingDesignCapacityPerFloorArea() const;
    bool setCoolingDesignCapacityPerFloorArea(double coolingDesignCapacityPerFloorArea);
    void resetCoolingDesignCapacityPerFloorArea();

    boost::optional<double> fractionofAutosizedCoolingDesignCapacity() const;
    bool setFractionofAutosizedCoolingDesignCapacity(double fractionofAutosizedCoolingDesignCapacity);
    void resetFractionofAutosizedCoolingDesignCapacity();

    double coolingControlThrottlingRange() const;
    bool isCoolingControlThrottlingRangeDefaulted() const;
    bool setCoolingControlThrottlingRange(double coolingControlThrottlingRange);
    void resetCoolingControlThrottlingRange();

    std::string condensationControlType() const;
    bool isCondensationControlTypeDefaulted() const;
    bool setCondensationControlType(const std::string& condensationControlType);
    void resetCondensationControlType();

    double condensationControlDewpointOffset() const;
    bool isCondensationControlDewpointOffsetDefaulted() const;
    bool setCondensationControlDewpointOffset(double condensationControlDewpointOffset);
    void resetCondensationControlDewpointOffset();

    std::string numberofCircuits() const;
    bool isNumberofCircuitsDefaulted() const;
    bool setNumberofCircuits(const std::string& numberofCircuits);
    void resetNumberofCircuits();

    double circuitLength() const;
    bool isCircuitLengthDefaulted() const;
    bool setCircuitLength(double circuitLength);
    void resetCircuitLength();

   protected:
    using ImplType = detail::ZoneHVACLowTempRadiantVarFlow_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACLowTempRadiantVarFlow(std::shared_ptr<detail::ZoneHVACLowTempRadiantVarFlow_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
