/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTFAN_HPP
#define EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTFAN_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirflowNetworkDistributionComponentFan_Impl;
  }

  /** \brief Represents the EnergyPlus AirflowNetwork:Distribution:Component:Fan object.
   *
   * \par EnergyPlus object
   * \epobject{group-airflow-network.html#airflownetworkdistributioncomponentfan,AirflowNetwork:Distribution:Component:Fan}
   *
   * \par OpenStudio Model API
   * OpenStudio Model has no public wrapper for this EnergyPlus object. This wrapper is new to the EPModel API.
   *
   * \par Known limitations
   * No known EPModel-specific limitations beyond the public fields and relationships exposed by this wrapper.
   */
  class EPMODEL_API AirflowNetworkDistributionComponentFan : public ModelObject
  {
   public:
    explicit AirflowNetworkDistributionComponentFan(const Model& model);

    virtual ~AirflowNetworkDistributionComponentFan() override = default;
    AirflowNetworkDistributionComponentFan(const AirflowNetworkDistributionComponentFan& other) = default;
    AirflowNetworkDistributionComponentFan(AirflowNetworkDistributionComponentFan&& other) = default;
    AirflowNetworkDistributionComponentFan& operator=(const AirflowNetworkDistributionComponentFan&) = default;
    AirflowNetworkDistributionComponentFan& operator=(AirflowNetworkDistributionComponentFan&&) = default;

    static IddObjectType iddObjectType();


   protected:
    using ImplType = detail::AirflowNetworkDistributionComponentFan_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirflowNetworkDistributionComponentFan(std::shared_ptr<detail::AirflowNetworkDistributionComponentFan_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
