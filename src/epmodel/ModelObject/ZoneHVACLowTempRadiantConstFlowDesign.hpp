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

  /** \brief ZoneHVACLowTempRadiantConstFlowDesign.
   *
   * \par EnergyPlus object
   * \epobject{group-radiative-convective-units.html#ConstFlowDesign,ZoneHVAC:LowTemperatureRadiant:ConstantFlow:Design}.
   *
   * \par OpenStudio Model API
   * There is no same-name OpenStudio Model class; this is the EnergyPlus design companion for <code>openstudio::model::ZoneHVACLowTempRadiantConstFlow</code>. It is a read-oriented projection whose lifecycle is owned by the corresponding radiant equipment wrapper.
   *
   * \par Known limitations
   * Design fields remain owner-managed by the radiant equipment wrapper.
   */
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
