/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKINTRAZONELINKAGE_HPP
#define EPMODEL_AIRFLOWNETWORKINTRAZONELINKAGE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirflowNetworkIntraZoneLinkage_Impl;
}

class EPMODEL_API AirflowNetworkIntraZoneLinkage : public ModelObject
{
 public:
  explicit AirflowNetworkIntraZoneLinkage(const Model& model);

  virtual ~AirflowNetworkIntraZoneLinkage() override = default;
  AirflowNetworkIntraZoneLinkage(const AirflowNetworkIntraZoneLinkage& other) = default;
  AirflowNetworkIntraZoneLinkage(AirflowNetworkIntraZoneLinkage&& other) = default;
  AirflowNetworkIntraZoneLinkage& operator=(const AirflowNetworkIntraZoneLinkage&) = default;
  AirflowNetworkIntraZoneLinkage& operator=(AirflowNetworkIntraZoneLinkage&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/API naming.
  // - Field Mapping: Name remains available via base ModelObject scalar API.
  // - Field Mapping: Node 1 Name, Node 2 Name, Component Name, and AirflowNetwork:MultiZone:Surface Name are
  //   relationship-like object-list links and excluded from scalar accessors.
  // - TODO(parity): Add typed relationship APIs if/when non-scalar parity work is prioritized.

 protected:
  using ImplType = detail::AirflowNetworkIntraZoneLinkage_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirflowNetworkIntraZoneLinkage(std::shared_ptr<detail::AirflowNetworkIntraZoneLinkage_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
