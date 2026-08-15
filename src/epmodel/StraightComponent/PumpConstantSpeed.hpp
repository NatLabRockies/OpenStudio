/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PUMPCONSTANTSPEED_HPP
#define EPMODEL_PUMPCONSTANTSPEED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class ThermalZone;
  class Node;
  class Curve;
  class Schedule;

  namespace detail {
    class PumpConstantSpeed_Impl;
  }

  class EPMODEL_API PumpConstantSpeed : public StraightComponent
  {
   public:
    explicit PumpConstantSpeed(const Model& model);

    virtual ~PumpConstantSpeed() override = default;
    PumpConstantSpeed(const PumpConstantSpeed& other) = default;
    PumpConstantSpeed(PumpConstantSpeed&& other) = default;
    PumpConstantSpeed& operator=(const PumpConstantSpeed&) = default;
    PumpConstantSpeed& operator=(PumpConstantSpeed&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> pumpControlTypeValues();
    static std::vector<std::string> designPowerSizingMethodValues();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The canonical scalar pump surface, direct schedule/curve/zone relationships, and plant-loop placement contract are present.
    // - Canonical Counterpart: openstudio::model::PumpConstantSpeed.
    // - Implemented Parity: Preserved scalar accessor names/signatures cover flow, head, power, efficiency, control type, impeller/rotation,
    //   radiative fraction, design-power sizing, and end-use metadata with matching autosize semantics; direct relationships preserve canonical
    //   signatures and typed target validation; `addToNode(...)` is limited to plant-loop placement like the canonical wrapper.
    // - Documented Delta: Broader canonical behavior outside the direct EnergyPlus field surface remains deferred.
    // - Field/Storage Mapping: Scalars and relationships map directly to their EnergyPlus `Pump:ConstantSpeed` fields and object lists.
    // - Evidence: `src/model/PumpConstantSpeed.hpp`, `src/model/PumpConstantSpeed.cpp`, and the configured EnergyPlus IDD define the canonical signatures, schedule constraints, curve target object list, and direct field mappings.
    // - Remaining Parity Work: Add other canonical behavior only when demanded by a concrete workflow.

    // ratedFlowRate
    boost::optional<double> ratedFlowRate() const;
    bool isRatedFlowRateAutosized() const;
    bool setRatedFlowRate(double ratedFlowRate);
    void resetRatedFlowRate();
    void autosizeRatedFlowRate();
    boost::optional<double> autosizedRatedFlowRate() const;

    // ratedPumpHead
    double ratedPumpHead() const;
    bool isRatedPumpHeadDefaulted() const;
    bool setRatedPumpHead(double ratedPumpHead);
    void resetRatedPumpHead();

    // ratedPowerConsumption
    boost::optional<double> ratedPowerConsumption() const;
    bool isRatedPowerConsumptionAutosized() const;
    bool setRatedPowerConsumption(double ratedPowerConsumption);
    void resetRatedPowerConsumption();
    void autosizeRatedPowerConsumption();
    boost::optional<double> autosizedRatedPowerConsumption() const;

    // motorEfficiency
    double motorEfficiency() const;
    bool isMotorEfficiencyDefaulted() const;
    bool setMotorEfficiency(double motorEfficiency);
    void resetMotorEfficiency();

    // fractionofMotorInefficienciestoFluidStream
    double fractionofMotorInefficienciestoFluidStream() const;
    bool isFractionofMotorInefficienciestoFluidStreamDefaulted() const;
    bool setFractionofMotorInefficienciestoFluidStream(double fractionofMotorInefficienciestoFluidStream);
    void resetFractionofMotorInefficienciestoFluidStream();

    // pumpControlType
    std::string pumpControlType() const;
    bool isPumpControlTypeDefaulted() const;
    bool setPumpControlType(const std::string& pumpControlType);
    void resetPumpControlType();

    boost::optional<Schedule> pumpFlowRateSchedule() const;
    bool setPumpFlowRateSchedule(Schedule& schedule);
    void resetPumpFlowRateSchedule();

    boost::optional<Curve> pumpCurve() const;
    bool setPumpCurve(const Curve& curve);
    void resetPumpCurve();

    // impellerDiameter
    boost::optional<double> impellerDiameter() const;
    bool setImpellerDiameter(double impellerDiameter);
    void resetImpellerDiameter();

    // rotationalSpeed
    boost::optional<double> rotationalSpeed() const;
    bool setRotationalSpeed(double rotationalSpeed);
    void resetRotationalSpeed();

    boost::optional<ThermalZone> zone() const;
    bool setZone(const ThermalZone& thermalZone);
    void resetZone();

    // skinLossRadiativeFraction
    boost::optional<double> skinLossRadiativeFraction() const;
    bool setSkinLossRadiativeFraction(double skinLossRadiativeFraction);
    void resetSkinLossRadiativeFraction();

    // designPowerSizingMethod
    std::string designPowerSizingMethod() const;
    bool setDesignPowerSizingMethod(const std::string& designPowerSizingMethod);

    // designElectricPowerPerUnitFlowRate
    double designElectricPowerPerUnitFlowRate() const;
    bool setDesignElectricPowerPerUnitFlowRate(double designElectricPowerPerUnitFlowRate);

    // designShaftPowerPerUnitFlowRatePerUnitHead
    double designShaftPowerPerUnitFlowRatePerUnitHead() const;
    bool setDesignShaftPowerPerUnitFlowRatePerUnitHead(double designShaftPowerPerUnitFlowRatePerUnitHead);

    // endUseSubcategory
    std::string endUseSubcategory() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);

    bool addToNode(Node& node);

   protected:
    using ImplType = detail::PumpConstantSpeed_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PumpConstantSpeed(std::shared_ptr<detail::PumpConstantSpeed_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
