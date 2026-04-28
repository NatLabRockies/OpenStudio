/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SPACEHVACEQUIPMENTCONNECTIONS_HPP
#define EPMODEL_SPACEHVACEQUIPMENTCONNECTIONS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class SpaceHVACEquipmentConnections_Impl;
}

class EPMODEL_API SpaceHVACEquipmentConnections : public ModelObject
{
 public:
  explicit SpaceHVACEquipmentConnections(const Model& model);

  virtual ~SpaceHVACEquipmentConnections() override = default;
  SpaceHVACEquipmentConnections(const SpaceHVACEquipmentConnections& other) = default;
  SpaceHVACEquipmentConnections(SpaceHVACEquipmentConnections&& other) = default;
  SpaceHVACEquipmentConnections& operator=(const SpaceHVACEquipmentConnections&) = default;
  SpaceHVACEquipmentConnections& operator=(SpaceHVACEquipmentConnections&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type keeps IDD-derived class/API naming.
  // - Field Mapping: Name remains available through base ModelObject scalar API.
  // - Field Mapping: Space Name, Space Air Inlet Node or NodeList Name, Space Air Exhaust Node or NodeList Name,
  //   Space Air Node Name, Space Return Air Node or NodeList Name, Space Return Air Node 1 Flow Rate Fraction Schedule Name,
  //   and Space Return Air Node 1 Flow Rate Basis Node or NodeList Name are relationship-like link fields and excluded
  //   from scalar accessors.
  // - TODO(parity): Add relationship APIs incrementally after scalar saturation.

 protected:
  using ImplType = detail::SpaceHVACEquipmentConnections_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit SpaceHVACEquipmentConnections(std::shared_ptr<detail::SpaceHVACEquipmentConnections_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
