/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKDISTRIBUTIONNODE_HPP
#define EPMODEL_AIRFLOWNETWORKDISTRIBUTIONNODE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirflowNetworkDistributionNode_Impl;
  }

  /** \brief Represents the EnergyPlus AirflowNetwork:Distribution:Node object.
   *
   * \par EnergyPlus object
   * \epobject{group-airflow-network.html#airflownetworkdistributionnode,AirflowNetwork:Distribution:Node}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::AirflowNetworkDistributionNode</code>.
   * <b>Changed:</b> EPModel exposes the EnergyPlus <code>Component Object Type or Node Type</code> choice directly;
   * Model instead provides typed <code>node()</code>, <code>airLoopHVACZoneMixer()</code>,
   * <code>airLoopHVACZoneSplitter()</code>, and <code>airLoopHVACOutdoorAirSystem()</code> getters.
   *
   * \par Known limitations
   * The component-or-node target is an EnergyPlus object-list relationship and is not exposed as a typed EPModel mutator.
   */
  class EPMODEL_API AirflowNetworkDistributionNode : public ModelObject
  {
   public:
    explicit AirflowNetworkDistributionNode(const Model& model);

    virtual ~AirflowNetworkDistributionNode() override = default;
    AirflowNetworkDistributionNode(const AirflowNetworkDistributionNode& other) = default;
    AirflowNetworkDistributionNode(AirflowNetworkDistributionNode&& other) = default;
    AirflowNetworkDistributionNode& operator=(const AirflowNetworkDistributionNode&) = default;
    AirflowNetworkDistributionNode& operator=(AirflowNetworkDistributionNode&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> componentObjectTypeorNodeTypeValues();


    // Component Object Type or Node Type accessors.
    std::string componentObjectTypeorNodeType() const;
    bool isComponentObjectTypeorNodeTypeDefaulted() const;
    bool setComponentObjectTypeorNodeType(const std::string& componentObjectTypeorNodeType);
    void resetComponentObjectTypeorNodeType();

    // Node Height accessors.
    double nodeHeight() const;
    bool isNodeHeightDefaulted() const;
    bool setNodeHeight(double nodeHeight);
    void resetNodeHeight();

   protected:
    using ImplType = detail::AirflowNetworkDistributionNode_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirflowNetworkDistributionNode(std::shared_ptr<detail::AirflowNetworkDistributionNode_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
