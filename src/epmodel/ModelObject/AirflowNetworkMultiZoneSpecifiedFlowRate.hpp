/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKMULTIZONESPECIFIEDFLOWRATE_HPP
#define EPMODEL_AIRFLOWNETWORKMULTIZONESPECIFIEDFLOWRATE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirflowNetworkMultiZoneSpecifiedFlowRate_Impl;
  }

  class EPMODEL_API AirflowNetworkMultiZoneSpecifiedFlowRate : public ModelObject
  {
   public:
    explicit AirflowNetworkMultiZoneSpecifiedFlowRate(const Model& model);

    virtual ~AirflowNetworkMultiZoneSpecifiedFlowRate() override = default;
    AirflowNetworkMultiZoneSpecifiedFlowRate(const AirflowNetworkMultiZoneSpecifiedFlowRate& other) = default;
    AirflowNetworkMultiZoneSpecifiedFlowRate(AirflowNetworkMultiZoneSpecifiedFlowRate&& other) = default;
    AirflowNetworkMultiZoneSpecifiedFlowRate& operator=(const AirflowNetworkMultiZoneSpecifiedFlowRate&) = default;
    AirflowNetworkMultiZoneSpecifiedFlowRate& operator=(AirflowNetworkMultiZoneSpecifiedFlowRate&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> airFlowUnitsValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
    // - Field Mapping: airFlowValue and airFlowUnits map directly to EnergyPlus
    //   AirflowNetwork:MultiZone:SpecifiedFlowRate scalar fields.
    // - Field Mapping: Name remains provided by base ModelObject naming APIs.
    // - ForwardTranslator evidence: translateAirflowNetworkSpecifiedFlowRate writes Name,
    //   Air Flow Value, and Air Flow Units directly.
    // - TODO(parity): Add relationship APIs only if future schema evolution introduces linked fields.
    double airFlowValue() const;
    bool setAirFlowValue(double airFlowValue);

    std::string airFlowUnits() const;
    bool setAirFlowUnits(const std::string& airFlowUnits);
    bool isAirFlowUnitsDefaulted() const;
    void resetAirFlowUnits();

   protected:
    using ImplType = detail::AirflowNetworkMultiZoneSpecifiedFlowRate_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirflowNetworkMultiZoneSpecifiedFlowRate(std::shared_ptr<detail::AirflowNetworkMultiZoneSpecifiedFlowRate_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
