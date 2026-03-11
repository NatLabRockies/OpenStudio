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

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/API naming.
  // - Field Mapping: Name remains available through base ModelObject scalar API.
  // - Field Mapping: Fan Name and Supply Fan Object Type are relationship-like target-link fields
  //   and are intentionally excluded from scalar accessors.
  // - ForwardTranslator evidence: translateAirflowNetworkFan writes Fan Name plus Supply Fan
  //   Object Type from linked fan objects.
  // - TODO(parity): Add relationship APIs after scalar scaffold saturation.

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
