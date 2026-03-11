/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DESIGNSPECIFICATIONOUTDOORAIRSPACELIST_HPP
#define EPMODEL_DESIGNSPECIFICATIONOUTDOORAIRSPACELIST_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;
class Space;
class DesignSpecificationOutdoorAir;

namespace detail {
class DesignSpecificationOutdoorAirSpaceList_Impl;
}

class EPMODEL_API DesignSpecificationOutdoorAirSpaceList : public ModelObject
{
 public:
  explicit DesignSpecificationOutdoorAirSpaceList(const Model& model);

  virtual ~DesignSpecificationOutdoorAirSpaceList() override = default;
  DesignSpecificationOutdoorAirSpaceList(const DesignSpecificationOutdoorAirSpaceList& other) = default;
  DesignSpecificationOutdoorAirSpaceList(DesignSpecificationOutdoorAirSpaceList&& other) = default;
  DesignSpecificationOutdoorAirSpaceList& operator=(const DesignSpecificationOutdoorAirSpaceList&) = default;
  DesignSpecificationOutdoorAirSpaceList& operator=(DesignSpecificationOutdoorAirSpaceList&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type keeps IDD-derived class/API naming.
  // - Field Mapping: This object has no simple non-name scalar fields; only relationship-like extensible links.
  // - Field Mapping: Space/DESIGNSPECIFICATION references remain impl-only via extensible-group APIs.
  // - TODO(parity): Add public relationship APIs incrementally after scalar saturation.
  std::vector<Space> spaces() const;
  boost::optional<DesignSpecificationOutdoorAir> designSpecificationOutdoorAir(const Space& space) const;

 protected:
  using ImplType = detail::DesignSpecificationOutdoorAirSpaceList_Impl;

  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;
  friend class openstudio::epmodel::Model;

  explicit DesignSpecificationOutdoorAirSpaceList(std::shared_ptr<detail::DesignSpecificationOutdoorAirSpaceList_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
