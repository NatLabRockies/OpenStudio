/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACLOWTEMPRADIANTCONSTFLOWDESIGN_HPP
#define EPMODEL_ZONEHVACLOWTEMPRADIANTCONSTFLOWDESIGN_HPP

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
    class ZoneHVACLowTempRadiantConstFlowDesign_Impl;
  }

  class EPMODEL_API ZoneHVACLowTempRadiantConstFlowDesign : public ModelObject
  {
   public:
    explicit ZoneHVACLowTempRadiantConstFlowDesign(const Model& model);

    virtual ~ZoneHVACLowTempRadiantConstFlowDesign() override = default;
    ZoneHVACLowTempRadiantConstFlowDesign(const ZoneHVACLowTempRadiantConstFlowDesign& other) = default;
    ZoneHVACLowTempRadiantConstFlowDesign(ZoneHVACLowTempRadiantConstFlowDesign&& other) = default;
    ZoneHVACLowTempRadiantConstFlowDesign& operator=(const ZoneHVACLowTempRadiantConstFlowDesign&) = default;
    ZoneHVACLowTempRadiantConstFlowDesign& operator=(ZoneHVACLowTempRadiantConstFlowDesign&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> fluidtoRadiantSurfaceHeatTransferModelValues();
    static std::vector<std::string> temperatureControlTypeValues();

    // Schema Alignment Notes:
    // - Status: Scalar Parity. This is the real persisted EnergyPlus design-side companion object for
    //   `ZoneHVAC:LowTemperatureRadiant:ConstantFlow`.
    // - Canonical Counterpart: openstudio::model::ZoneHVACLowTempRadiantConstFlow.
    // - Why This Wrapper Exists: canonical OpenStudio keeps these fields on the parent radiant wrapper, but EnergyPlus stores them on a
    //   separate `...:Design` object. Epmodel exposes this split object directly so the parent and transient companion coils can stop
    //   tunneling through a generic `ModelObject`.
    // - Documented Delta: there is no same-name canonical `openstudio::model` type. This is an EnergyPlus-facing companion wrapper whose
    //   main job is to hold persisted design/control storage honestly and transparently.

    // This is an EnergyPlus-only companion type with no canonical public peer.
    // For now, epmodel keeps the public wrapper read-oriented and reserves
    // mutation for the owning parent and `*_Impl` code paths.
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

    double runningMeanOutdoorDryBulbTemperatureWeightingFactor() const;
    bool isRunningMeanOutdoorDryBulbTemperatureWeightingFactorDefaulted() const;

    double motorEfficiency() const;
    bool isMotorEfficiencyDefaulted() const;

    double fractionofMotorInefficienciestoFluidStream() const;
    bool isFractionofMotorInefficienciestoFluidStreamDefaulted() const;

    std::string condensationControlType() const;
    bool isCondensationControlTypeDefaulted() const;

    double condensationControlDewpointOffset() const;
    bool isCondensationControlDewpointOffsetDefaulted() const;

   protected:
    using ImplType = detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACLowTempRadiantConstFlowDesign(std::shared_ptr<detail::ZoneHVACLowTempRadiantConstFlowDesign_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
