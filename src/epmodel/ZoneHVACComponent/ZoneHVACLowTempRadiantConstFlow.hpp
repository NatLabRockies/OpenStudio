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

/** \brief A constant-flow low-temperature radiant system serving a thermal zone.
 *
 * \par EnergyPlus object
 * \epobject{group-radiative-convective-units.html#zonehvaclowtemperatureradiantconstantflow,ZoneHVAC:LowTemperatureRadiant:ConstantFlow},
 * \epobject{group-radiative-convective-units.html#ConstFlowDesign,ZoneHVAC:LowTemperatureRadiant:ConstantFlow:Design}, and
 * \epobject{group-radiative-convective-units.html#zonehvaclowtemperatureradiantsurfacegroup,ZoneHVAC:LowTemperatureRadiant:SurfaceGroup}
 *
 * \par Important behavior
 * Heating and cooling coil children are transient views over parent and design fields; setRadiantSurfaceType() snapshots matching zone surfaces into the persisted surface group.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::ZoneHVACLowTempRadiantConstFlow</code>.
 * EPModel exposes the design companion and surface-group views, plus
 * EnergyPlus default/reset helpers; Model instead provides its thermal-zone
 * convenience methods and deprecated compatibility surface.
 *
 * \par Known limitations
 * Later zone or surface edits do not automatically resynchronize the persisted surface group; autosized results remain unavailable without SQL sizing data.
 */
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
