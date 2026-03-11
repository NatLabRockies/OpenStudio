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

  // Schema Alignment Notes:
  // - API: This type currently keeps IDD-derived class/API naming in epmodel.
  // - Field Mapping: Name remains available via base ModelObject scalar API.
  // - Field Mapping: Node 1 Name, Node 2 Name, Component Name, and Thermal Zone Name are
  //   relationship-like object-list links and excluded from scalar accessors.
  // - TODO(parity): Add typed relationship APIs if/when non-scalar parity work is prioritized.

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
