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

  /** \brief Represents the EnergyPlus AirflowNetwork:MultiZone:SpecifiedFlowRate object.
   *
   * \par EnergyPlus object
   * \epobject{group-airflow-network.html#airflownetworkmultizonespecifiedflow,AirflowNetwork:MultiZone:SpecifiedFlowRate}
   *
   * \par OpenStudio Model API
   * OpenStudio Model has no public wrapper for this EnergyPlus object. This wrapper is new to the EPModel API.
   *
   * \par Known limitations
   * No known EPModel-specific limitations beyond the public fields and relationships exposed by this wrapper.
   */
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
