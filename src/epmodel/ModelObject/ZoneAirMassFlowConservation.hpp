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

  /** \brief ZoneAirMassFlowConservation.
   *
   * \par EnergyPlus object
   * \epobject{group-airflow.html#zoneairmassflowconservation,ZoneAirMassFlowConservation}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::ZoneAirMassFlowConservation</code>. The air-mass-flow balancing choices map directly to EnergyPlus. The deprecated Model boolean <code>adjustZoneMixingForZoneAirMassFlowBalance()</code> family is not exposed; use EPModel's string-valued replacement.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API ZoneAirMassFlowConservation : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~ZoneAirMassFlowConservation() override = default;
    ZoneAirMassFlowConservation(const ZoneAirMassFlowConservation& other) = default;
    ZoneAirMassFlowConservation(ZoneAirMassFlowConservation&& other) = default;
    ZoneAirMassFlowConservation& operator=(const ZoneAirMassFlowConservation&) = default;
    ZoneAirMassFlowConservation& operator=(ZoneAirMassFlowConservation&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> adjustZoneMixingandReturnForAirMassFlowBalanceValues();
    static std::vector<std::string> infiltrationBalancingMethodValues();
    static std::vector<std::string> infiltrationBalancingZonesValues();
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
    explicit ZoneAirMassFlowConservation(const Model& model);

    using ImplType = detail::ZoneAirMassFlowConservation_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneAirMassFlowConservation(std::shared_ptr<detail::ZoneAirMassFlowConservation_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_ZONEAIRMASSFLOWCONSERVATION_HPP
