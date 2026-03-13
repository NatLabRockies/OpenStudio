/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEAIRMASSFLOWCONSERVATION_HPP
#define EPMODEL_ZONEAIRMASSFLOWCONSERVATION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneAirMassFlowConservation_Impl;
  }

  class EPMODEL_API ZoneAirMassFlowConservation : public ModelObject
  {
   public:
    explicit ZoneAirMassFlowConservation(const Model& model);

    virtual ~ZoneAirMassFlowConservation() override = default;
    ZoneAirMassFlowConservation(const ZoneAirMassFlowConservation& other) = default;
    ZoneAirMassFlowConservation(ZoneAirMassFlowConservation&& other) = default;
    ZoneAirMassFlowConservation& operator=(const ZoneAirMassFlowConservation&) = default;
    ZoneAirMassFlowConservation& operator=(ZoneAirMassFlowConservation&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> adjustZoneMixingandReturnForAirMassFlowBalanceValues();
    static std::vector<std::string> infiltrationBalancingMethodValues();
    static std::vector<std::string> infiltrationBalancingZonesValues();

    // Schema Alignment Notes:
    // - API: preserve the openstudio::model scalar accessor names/signatures for the adjust-zone-mixing/return and infiltration
    //   balancing choices.
    // - Field Mapping: these getters/setters map directly to the EnergyPlus ZoneAirMassFlowConservation fields documented by
    //   ForwardTranslateZoneAirMassFlowConservation.cpp.
    // - TODO(parity): expose any relationship-like connections (mixer/infiltration sources) once scalar saturation is complete.
    std::string adjustZoneMixingandReturnForAirMassFlowBalance() const;
    bool isAdjustZoneMixingandReturnForAirMassFlowBalanceDefaulted() const;
    bool setAdjustZoneMixingandReturnForAirMassFlowBalance(const std::string& adjustZoneMixingandReturnForAirMassFlowBalance);
    void resetAdjustZoneMixingandReturnForAirMassFlowBalance();

    std::string infiltrationBalancingMethod() const;
    bool isInfiltrationBalancingMethodDefaulted() const;
    bool setInfiltrationBalancingMethod(const std::string& infiltrationBalancingMethod);
    void resetInfiltrationBalancingMethod();

    std::string infiltrationBalancingZones() const;
    bool isInfiltrationBalancingZonesDefaulted() const;
    bool setInfiltrationBalancingZones(const std::string& infiltrationBalancingZones);
    void resetInfiltrationBalancingZones();

   protected:
    using ImplType = detail::ZoneAirMassFlowConservation_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneAirMassFlowConservation(std::shared_ptr<detail::ZoneAirMassFlowConservation_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_ZONEAIRMASSFLOWCONSERVATION_HPP
