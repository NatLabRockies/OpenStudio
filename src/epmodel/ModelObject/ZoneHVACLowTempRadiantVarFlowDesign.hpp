/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACLOWTEMPRADIANTVARFLOWDESIGN_HPP
#define EPMODEL_ZONEHVACLOWTEMPRADIANTVARFLOWDESIGN_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;

  namespace detail {
    class ZoneHVACLowTempRadiantVarFlowDesign_Impl;
  }

  class EPMODEL_API ZoneHVACLowTempRadiantVarFlowDesign : public ModelObject
  {
   public:
    explicit ZoneHVACLowTempRadiantVarFlowDesign(const Model& model);

    virtual ~ZoneHVACLowTempRadiantVarFlowDesign() override = default;
    ZoneHVACLowTempRadiantVarFlowDesign(const ZoneHVACLowTempRadiantVarFlowDesign& other) = default;
    ZoneHVACLowTempRadiantVarFlowDesign(ZoneHVACLowTempRadiantVarFlowDesign&& other) = default;
    ZoneHVACLowTempRadiantVarFlowDesign& operator=(const ZoneHVACLowTempRadiantVarFlowDesign&) = default;
    ZoneHVACLowTempRadiantVarFlowDesign& operator=(ZoneHVACLowTempRadiantVarFlowDesign&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> fluidtoRadiantSurfaceHeatTransferModelValues();
    static std::vector<std::string> temperatureControlTypeValues();
    static std::vector<std::string> setpointControlTypeValues();
    static std::vector<std::string> heatingDesignCapacityMethodValues();
    static std::vector<std::string> coolingDesignCapacityMethodValues();
    static std::vector<std::string> condensationControlTypeValues();

    // Schema Alignment Notes:
    // - Status: Scalar Parity. This is the real persisted EnergyPlus design-side companion object for
    //   `ZoneHVAC:LowTemperatureRadiant:VariableFlow`.
    // - Canonical Counterpart: openstudio::model::ZoneHVACLowTempRadiantVarFlow.
    // - Why This Wrapper Exists: canonical OpenStudio keeps these controls and design-side relationships on the parent
    //   and transient companion coils, while EnergyPlus stores them on a separate `...:Design` object.
    // - Implemented Parity: The read-side schedule, design-method, control-type, throttling, tubing, and
    //   condensation-control accessors needed by the canonical parent and transient child views are available.
    // - Documented Delta: there is no same-name canonical `openstudio::model` type. This is an EnergyPlus-facing
    //   companion wrapper whose public API is intentionally read-oriented.

    boost::optional<Schedule> heatingControlTemperatureSchedule() const;
    boost::optional<Schedule> coolingControlTemperatureSchedule() const;
    boost::optional<Schedule> changeoverDelayTimePeriodSchedule() const;

    std::string fluidtoRadiantSurfaceHeatTransferModel() const;
    bool isFluidtoRadiantSurfaceHeatTransferModelDefaulted() const;

    double hydronicTubingInsideDiameter() const;
    bool isHydronicTubingInsideDiameterDefaulted() const;

    double hydronicTubingOutsideDiameter() const;
    bool isHydronicTubingOutsideDiameterDefaulted() const;

    double hydronicTubingConductivity() const;
    bool isHydronicTubingConductivityDefaulted() const;

    std::string temperatureControlType() const;
    bool isTemperatureControlTypeDefaulted() const;

    std::string setpointControlType() const;
    bool isSetpointControlTypeDefaulted() const;

    std::string heatingDesignCapacityMethod() const;
    bool isHeatingDesignCapacityMethodDefaulted() const;

    boost::optional<double> heatingDesignCapacityPerFloorArea() const;

    double fractionofAutosizedHeatingDesignCapacity() const;
    bool isFractionofAutosizedHeatingDesignCapacityDefaulted() const;

    double heatingControlThrottlingRange() const;
    bool isHeatingControlThrottlingRangeDefaulted() const;

    std::string coolingDesignCapacityMethod() const;
    bool isCoolingDesignCapacityMethodDefaulted() const;

    boost::optional<double> coolingDesignCapacityPerFloorArea() const;

    boost::optional<double> fractionofAutosizedCoolingDesignCapacity() const;

    double coolingControlThrottlingRange() const;
    bool isCoolingControlThrottlingRangeDefaulted() const;

    std::string condensationControlType() const;
    bool isCondensationControlTypeDefaulted() const;

    double condensationControlDewpointOffset() const;
    bool isCondensationControlDewpointOffsetDefaulted() const;

   protected:
    using ImplType = detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACLowTempRadiantVarFlowDesign(std::shared_ptr<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
