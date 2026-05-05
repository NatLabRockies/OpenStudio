/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACLOWTEMPRADIANTCONSTFLOW_HPP
#define EPMODEL_ZONEHVACLOWTEMPRADIANTCONSTFLOW_HPP

#include "EPModelAPI.hpp"
#include "PlanarSurface/Surface.hpp"
#include "StraightComponent/CoilCoolingLowTempRadiantConstFlow.hpp"
#include "StraightComponent/CoilHeatingLowTempRadiantConstFlow.hpp"
#include "ZoneHVACComponent/ZoneHVACComponent.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class HVACComponent;
  class Model;
  class Schedule;
  class ModelObject;
  class ZoneHVACLowTempRadiantConstFlowDesign;
  class ZoneHVACLowTemperatureRadiantSurfaceGroup;
  namespace detail {
    class ZoneHVACLowTempRadiantConstFlow_Impl;
  }

  class EPMODEL_API ZoneHVACLowTempRadiantConstFlow : public ZoneHVACComponent
  {
   public:
    explicit ZoneHVACLowTempRadiantConstFlow(const Model& model);
    ZoneHVACLowTempRadiantConstFlow(const Model& model, Schedule& availabilitySchedule, HVACComponent& heatingCoil, HVACComponent& coolingCoil,
                                    double hydronicTubingLength);
    ZoneHVACLowTempRadiantConstFlow(const Model& model, Schedule& availabilitySchedule, HVACComponent& heatingCoil, HVACComponent& coolingCoil);

    virtual ~ZoneHVACLowTempRadiantConstFlow() override = default;
    ZoneHVACLowTempRadiantConstFlow(const ZoneHVACLowTempRadiantConstFlow& other) = default;
    ZoneHVACLowTempRadiantConstFlow(ZoneHVACLowTempRadiantConstFlow&& other) = default;
    ZoneHVACLowTempRadiantConstFlow& operator=(const ZoneHVACLowTempRadiantConstFlow&) = default;
    ZoneHVACLowTempRadiantConstFlow& operator=(ZoneHVACLowTempRadiantConstFlow&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> radiantSurfaceTypeValues();
    static std::vector<std::string> numberofCircuitsValues();
    static std::vector<std::string> fluidtoRadiantSurfaceHeatTransferModelValues();
    static std::vector<std::string> temperatureControlTypeValues();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The hydronic/control scalars are aligned, epmodel exposes the canonical heating/cooling companion coils
    //   as transient child views over the parent radiant object, and the canonical radiant-surface APIs now route through the persisted
    //   EnergyPlus surface-group object.
    // - Canonical Counterpart: openstudio::model::ZoneHVACLowTempRadiantConstFlow.
    // - Why This Type Is Slightly Different: canonical OpenStudio splits this family into one parent object plus companion heating/cooling
    //   coil wrappers and a higher-level `RadiantSurfaceType` selector. EnergyPlus does not store that selector directly. It stores the
    //   flattened result as a referenced `ZoneHVAC:LowTemperatureRadiant:SurfaceGroup`, plus a persisted `...:Design` companion object.
    //   Epmodel therefore preserves the canonical API additively while staying anchored to the EnergyPlus storage shape.
    // - Implemented Parity: The constant-flow radiant scalar groups map directly to the EnergyPlus object and its companion design object.
    //   The canonical heating and cooling coil wrappers are exposed additively as transient children that write through to that parent storage.
    // - Documented Delta: `setRadiantSurfaceType(...)` currently snapshots the matching zone surfaces into the EnergyPlus surface group.
    //   Later zone/surface edits do not yet automatically re-expand that group until a future synchronization pass is added.
    // - Field/Storage Mapping: Main hydronic fields live on the EnergyPlus object, design-side controls live on the EnergyPlus design object,
    //   the surface selection lives as a referenced EnergyPlus surface group, and the transient child coils are views over those persisted
    //   parent fields rather than standalone EnergyPlus objects.
    // - Evidence: `src/model/ZoneHVACLowTempRadiantConstFlow.hpp`, `src/model/ZoneHVACLowTempRadiantConstFlow.cpp`,
    //   `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACLowTempRadiantConstFlow.cpp`,
    //   and `src/epmodel/test/ZoneHVACLowTempRadiantConstFlow_GTest.cpp`.
    // - Remaining Parity Work: Add automatic surface-group resynchronization after later zone/surface edits and close any remaining
    //   relationship gaps.

    boost::optional<Schedule> availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);
    void resetAvailabilitySchedule();

    // `radiantSurfaceType()` is a canonical convenience view, not a first-class
    // EnergyPlus field. We infer it from the persisted EnergyPlus surface-group
    // membership when that membership matches one of the canonical OpenStudio
    // buckets (`Ceilings`, `Floors`, `CeilingsandFloors`, or `AllSurfaces`).
    // If the stored group does not correspond cleanly to one of those buckets,
    // `boost::none` is returned rather than pretending the imported data is
    // more canonical than it really is.
    boost::optional<std::string> radiantSurfaceType() const;

    // This setter preserves the canonical OpenStudio API while staying anchored
    // to EnergyPlus storage. Today it is intentionally implemented as a
    // snapshot operation:
    // - resolve the current ThermalZone
    // - select the currently eligible matching surfaces
    // - rewrite the referenced EnergyPlus surface-group object
    //
    // That means later zone or surface edits do not yet automatically resync
    // the group. This is acceptable for now because epmodel does not yet have a
    // fully developed envelope-side synchronization story. When the surface and
    // surface-group domain matures, this should be revisited so the canonical
    // selector can drive resynchronization more automatically.
    bool setRadiantSurfaceType(const std::string& radiantSurfaceType);

    // Resets back to the canonical OpenStudio default (`Ceilings`) when a zone
    // is attached. Without a zone there is nothing meaningful to expand, so the
    // persisted surface-group membership is cleared instead.
    void resetRadiantSurfaceType();

    // Returns the actual surfaces currently referenced by the persisted
    // EnergyPlus surface group. In other words, this is the stored emitted
    // membership, not a freshly recomputed "what would match right now" view.
    // That makes the current storage state inspectable even before epmodel has
    // richer surface-group wrapper APIs.
    std::vector<Surface> surfaces() const;

    CoilHeatingLowTempRadiantConstFlow heatingCoil() const;
    bool setHeatingCoil(HVACComponent& heatingCoil);
    CoilCoolingLowTempRadiantConstFlow coolingCoil() const;
    bool setCoolingCoil(HVACComponent& coolingCoil);

    boost::optional<Schedule> pumpFlowRateSchedule() const;
    bool setPumpFlowRateSchedule(Schedule& schedule);
    void resetPumpFlowRateSchedule();

    boost::optional<Schedule> changeoverDelayTimePeriodSchedule() const;
    bool setChangeoverDelayTimePeriodSchedule(Schedule& schedule);
    void resetChangeoverDelayTimePeriodSchedule();

    std::vector<ModelObject> children() const;

    boost::optional<ZoneHVACLowTempRadiantConstFlowDesign> designObject() const;
    boost::optional<ZoneHVACLowTemperatureRadiantSurfaceGroup> surfaceGroup() const;

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

    double runningMeanOutdoorDryBulbTemperatureWeightingFactor() const;
    bool isRunningMeanOutdoorDryBulbTemperatureWeightingFactorDefaulted() const;
    bool setRunningMeanOutdoorDryBulbTemperatureWeightingFactor(double runningMeanOutdoorDryBulbTemperatureWeightingFactor);
    void resetRunningMeanOutdoorDryBulbTemperatureWeightingFactor();

    double motorEfficiency() const;
    bool isMotorEfficiencyDefaulted() const;
    bool setMotorEfficiency(double motorEfficiency);
    void resetMotorEfficiency();

    double fractionofMotorInefficienciestoFluidStream() const;
    bool isFractionofMotorInefficienciestoFluidStreamDefaulted() const;
    bool setFractionofMotorInefficienciestoFluidStream(double fractionofMotorInefficienciestoFluidStream);
    void resetFractionofMotorInefficienciestoFluidStream();

    boost::optional<double> hydronicTubingLength() const;
    boost::optional<double> autosizedHydronicTubingLength() const;
    bool isHydronicTubingLengthAutosized() const;
    bool setHydronicTubingLength(double hydronicTubingLength);
    void autosizeHydronicTubingLength();

    boost::optional<double> ratedFlowRate() const;
    boost::optional<double> autosizedRatedFlowRate() const;
    bool isRatedFlowRateAutosized() const;
    bool setRatedFlowRate(double ratedFlowRate);
    void autosizeRatedFlowRate();

    double ratedPumpHead() const;
    bool isRatedPumpHeadDefaulted() const;
    bool setRatedPumpHead(double ratedPumpHead);
    void resetRatedPumpHead();

    boost::optional<double> ratedPowerConsumption() const;
    bool setRatedPowerConsumption(double ratedPowerConsumption);
    void resetRatedPowerConsumption();

    std::string numberofCircuits() const;
    bool isNumberofCircuitsDefaulted() const;
    bool setNumberofCircuits(const std::string& numberofCircuits);
    void resetNumberofCircuits();

    double circuitLength() const;
    bool isCircuitLengthDefaulted() const;
    bool setCircuitLength(double circuitLength);
    void resetCircuitLength();

   protected:
    using ImplType = detail::ZoneHVACLowTempRadiantConstFlow_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACLowTempRadiantConstFlow(std::shared_ptr<detail::ZoneHVACLowTempRadiantConstFlow_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
