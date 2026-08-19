/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKDISTRIBUTIONLINKAGE_HPP
#define EPMODEL_AIRFLOWNETWORKDISTRIBUTIONLINKAGE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirflowNetworkDistributionLinkage_Impl;
  }

  /** \brief Represents the EnergyPlus AirflowNetwork:Distribution:Linkage object.
   *
   * \par EnergyPlus object
   * \epobject{group-airflow-network.html#airflownetworkdistributionlinkage,AirflowNetwork:Distribution:Linkage}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::AirflowNetworkDistributionLinkage</code>. <b>Not yet available:</b> typed <code>node1()</code>, <code>node2()</code>, <code>component()</code>, and <code>thermalZone()</code> accessors and their setter/resetter methods.
   *
   * \par Known limitations
   * Node, component, and thermal-zone links are stored as EnergyPlus object-list fields; use the owning AirflowNetwork topology to maintain them.
   */
  class EPMODEL_API AirflowNetworkDistributionLinkage : public ModelObject
  {
   public:
    explicit AirflowNetworkDistributionLinkage(const Model& model);

    virtual ~AirflowNetworkDistributionLinkage() override = default;
    AirflowNetworkDistributionLinkage(const AirflowNetworkDistributionLinkage& other) = default;
    AirflowNetworkDistributionLinkage(AirflowNetworkDistributionLinkage&& other) = default;
    AirflowNetworkDistributionLinkage& operator=(const AirflowNetworkDistributionLinkage&) = default;
    AirflowNetworkDistributionLinkage& operator=(AirflowNetworkDistributionLinkage&&) = default;

    static IddObjectType iddObjectType();


   protected:
    using ImplType = detail::AirflowNetworkDistributionLinkage_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirflowNetworkDistributionLinkage(std::shared_ptr<detail::AirflowNetworkDistributionLinkage_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
