/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACLOWTEMPRADIANTVARFLOW_HPP
#define EPMODEL_ZONEHVACLOWTEMPRADIANTVARFLOW_HPP

#include "EPModelAPI.hpp"
#include "PlanarSurface/Surface.hpp"
#include "StraightComponent/CoilCoolingLowTempRadiantVarFlow.hpp"
#include "StraightComponent/CoilHeatingLowTempRadiantVarFlow.hpp"
#include "ZoneHVACComponent/ZoneHVACComponent.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class HVACComponent;
  class Model;
  class ModelObject;
  class Schedule;
  class ZoneHVACLowTempRadiantVarFlowDesign;
  class ZoneHVACLowTemperatureRadiantSurfaceGroup;

  namespace detail {
    class ZoneHVACLowTempRadiantVarFlow_Impl;
  }

  class EPMODEL_API ZoneHVACLowTempRadiantVarFlow : public ZoneHVACComponent
  {
   public:
    explicit ZoneHVACLowTempRadiantVarFlow(const Model& model);
    ZoneHVACLowTempRadiantVarFlow(const Model& model, Schedule& availabilitySchedule, HVACComponent& heatingCoil,
                                  HVACComponent& coolingCoil);

    virtual ~ZoneHVACLowTempRadiantVarFlow() override = default;
    ZoneHVACLowTempRadiantVarFlow(const ZoneHVACLowTempRadiantVarFlow& other) = default;
    ZoneHVACLowTempRadiantVarFlow(ZoneHVACLowTempRadiantVarFlow&& other) = default;
    ZoneHVACLowTempRadiantVarFlow& operator=(const ZoneHVACLowTempRadiantVarFlow&) = default;
    ZoneHVACLowTempRadiantVarFlow& operator=(ZoneHVACLowTempRadiantVarFlow&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> radiantSurfaceTypeValues();
    static std::vector<std::string> numberofCircuitsValues();
    static std::vector<std::string> fluidtoRadiantSurfaceHeatTransferModelValues();
    static std::vector<std::string> temperatureControlTypeValues();
    static std::vector<std::string> setpointControlTypeValues();
    static std::vector<std::string> heatingDesignCapacityMethodValues();
    static std::vector<std::string> coolingDesignCapacityMethodValues();
    static std::vector<std::string> condensationControlTypeValues();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The hydronic and control scalars are aligned, epmodel preserves the canonical optional
    //   heating/cooling companion coils as transient child views, and the canonical radiant-surface APIs now route through
    //   the persisted EnergyPlus surface-group object and design companion object.
    // - Canonical Counterpart: openstudio::model::ZoneHVACLowTempRadiantVarFlow.
    // - Why This Type Is Slightly Different: canonical OpenStudio splits this family into one parent object plus optional
    //   heating/cooling coil wrappers and a higher-level `RadiantSurfaceType` selector. EnergyPlus does not persist those
    //   child coil objects or that selector directly. It stores the flattened result on the parent radiant object, the
    //   persisted `...:Design` object, and a referenced `ZoneHVAC:LowTemperatureRadiant:SurfaceGroup`.
    // - Implemented Parity: The canonical availability schedule, optional heating/cooling companion coils, radiant-surface
    //   APIs, and changeover schedule are preserved additively while staying anchored to that EnergyPlus storage shape.
    // - Documented Delta: `setRadiantSurfaceType(...)` currently snapshots the matching zone surfaces into the EnergyPlus
    //   surface group. Later zone/surface edits do not yet automatically resynchronize that group.
    // - Field/Storage Mapping: Main hydronic fields live on the EnergyPlus object, design-side controls live on the
    //   EnergyPlus design object, the surface selection lives as a referenced EnergyPlus surface group, and the transient
    //   child coils are views over those persisted parent fields rather than standalone EnergyPlus objects.
    // - Evidence: `src/model/ZoneHVACLowTempRadiantVarFlow.hpp`, `src/model/ZoneHVACLowTempRadiantVarFlow.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACLowTempRadiantVarFlow.cpp`, and `src/epmodel/test/ZoneHVACLowTempRadiantVarFlow_GTest.cpp`.
    // - Remaining Parity Work: Add automatic surface-group resynchronization after later zone/surface edits and close any
    //   remaining relationship gaps.

    boost::optional<Schedule> availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);
    void resetAvailabilitySchedule();

    // This preserves the canonical higher-level selector even though EnergyPlus stores the actual persisted
    // surface membership in a referenced `ZoneHVAC:LowTemperatureRadiant:SurfaceGroup`.
    boost::optional<std::string> radiantSurfaceType() const;
    // For now this snapshots the current matching zone surfaces into the persisted EnergyPlus surface-group object.
    // Later zone or surface edits do not yet automatically resynchronize that group.
    bool setRadiantSurfaceType(const std::string& radiantSurfaceType);
    // Reset follows the canonical default of `Ceilings` when the parent is attached to a zone. Without a zone, there
    // is no canonical surface selection to materialize, so the persisted surface-group membership is simply cleared.
    void resetRadiantSurfaceType();

    // This returns the actual surfaces currently referenced by the persisted EnergyPlus surface-group object, not a
    // live recomputation from the attached thermal zone.
    std::vector<Surface> surfaces() const;

    boost::optional<HVACComponent> heatingCoil() const;
    bool setHeatingCoil(HVACComponent& heatingCoil);
    void resetHeatingCoil();

    boost::optional<HVACComponent> coolingCoil() const;
    bool setCoolingCoil(HVACComponent& coolingCoil);
    void resetCoolingCoil();

    boost::optional<Schedule> changeoverDelayTimePeriodSchedule() const;
    bool setChangeoverDelayTimePeriodSchedule(Schedule& schedule);
    void resetChangeoverDelayTimePeriodSchedule();

    std::vector<ModelObject> children() const;

    boost::optional<ZoneHVACLowTempRadiantVarFlowDesign> designObject() const;
    boost::optional<ZoneHVACLowTemperatureRadiantSurfaceGroup> surfaceGroup() const;

    boost::optional<double> hydronicTubingLength() const;
    boost::optional<double> autosizedHydronicTubingLength() const;
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
