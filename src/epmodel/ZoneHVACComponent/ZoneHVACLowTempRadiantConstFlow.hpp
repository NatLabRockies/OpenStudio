/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACLOWTEMPRADIANTCONSTFLOW_HPP
#define EPMODEL_ZONEHVACLOWTEMPRADIANTCONSTFLOW_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/CoilCoolingLowTempRadiantConstFlow.hpp"
#include "StraightComponent/CoilHeatingLowTempRadiantConstFlow.hpp"
#include "ZoneHVACComponent/ZoneHVACComponent.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;
  class ModelObject;

  namespace detail {
    class ZoneHVACLowTempRadiantConstFlow_Impl;
  }

  class EPMODEL_API ZoneHVACLowTempRadiantConstFlow : public ZoneHVACComponent
  {
   public:
    explicit ZoneHVACLowTempRadiantConstFlow(const Model& model);

    virtual ~ZoneHVACLowTempRadiantConstFlow() override = default;
    ZoneHVACLowTempRadiantConstFlow(const ZoneHVACLowTempRadiantConstFlow& other) = default;
    ZoneHVACLowTempRadiantConstFlow(ZoneHVACLowTempRadiantConstFlow&& other) = default;
    ZoneHVACLowTempRadiantConstFlow& operator=(const ZoneHVACLowTempRadiantConstFlow&) = default;
    ZoneHVACLowTempRadiantConstFlow& operator=(ZoneHVACLowTempRadiantConstFlow&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> numberofCircuitsValues();
    static std::vector<std::string> fluidtoRadiantSurfaceHeatTransferModelValues();
    static std::vector<std::string> temperatureControlTypeValues();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The hydronic/control scalars are aligned, and epmodel now exposes the canonical heating/cooling companion coils
    //   as transient child views over the parent radiant object. Surface membership behavior is still relationship-driven.
    // - Canonical Counterpart: openstudio::model::ZoneHVACLowTempRadiantConstFlow.
    // - Implemented Parity: The constant-flow radiant scalar groups map directly to the EnergyPlus object and its companion design object.
    //   The canonical heating and cooling coil wrappers are exposed additively as transient children that write through to that parent storage.
    // - Documented Delta: Surface membership and the fuller canonical surface-group behavior are still not exposed directly.
    // - Field/Storage Mapping: Main hydronic fields live on the EnergyPlus object, design-side controls live on the EnergyPlus design object,
    //   and the transient child coils are views over those persisted parent fields rather than standalone EnergyPlus objects.
    // - Evidence: `src/model/ZoneHVACLowTempRadiantConstFlow.hpp`, `src/model/ZoneHVACLowTempRadiantConstFlow.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACLowTempRadiantConstFlow.cpp`, and `src/epmodel/test/ZoneHVACLowTempRadiantConstFlow_GTest.cpp`.
    // - Remaining Parity Work: Add the canonical surface and other relationship helpers once the transient companion pattern is settled.

    boost::optional<Schedule> availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);
    void resetAvailabilitySchedule();

    CoilHeatingLowTempRadiantConstFlow heatingCoil() const;
    CoilCoolingLowTempRadiantConstFlow coolingCoil() const;

    boost::optional<Schedule> pumpFlowRateSchedule() const;
    bool setPumpFlowRateSchedule(Schedule& schedule);
    void resetPumpFlowRateSchedule();

    boost::optional<Schedule> changeoverDelayTimePeriodSchedule() const;
    bool setChangeoverDelayTimePeriodSchedule(Schedule& schedule);
    void resetChangeoverDelayTimePeriodSchedule();

    std::vector<ModelObject> children() const;

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
    bool isHydronicTubingLengthAutosized() const;
    bool setHydronicTubingLength(double hydronicTubingLength);
    void autosizeHydronicTubingLength();

    boost::optional<double> ratedFlowRate() const;
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
