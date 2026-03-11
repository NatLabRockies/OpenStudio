/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SPACE_HPP
#define EPMODEL_SPACE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;
class ThermalZone;
class DesignSpecificationOutdoorAir;

namespace detail {
class Space_Impl;
}

class EPMODEL_API Space : public ModelObject
{
 public:
  // Schema Alignment Notes:
  // - API: designSpecificationOutdoorAir()/setDesignSpecificationOutdoorAir()
  //   currently route through ThermalZone -> Sizing:Zone ->
  //   DesignSpecification:OutdoorAir:SpaceList in epmodel.
  // - Field Mapping: openstudio::model stores Space DSOA directly on
  //   OS:Space, while epmodel stores zone-scoped DSOA assignment in
  //   Sizing:Zone (DesignSpecification Outdoor Air Object Name).
  // - Current behavior: setDesignSpecificationOutdoorAir(...) is supported for
  //   both zoned and unzoned spaces.
  //   Zoned spaces write through ThermalZone -> Sizing:Zone -> DSOA:SpaceList.
  //   Unzoned spaces write to an orphan DSOA:SpaceList owned by the Model.
  explicit Space(const Model& model);

  virtual ~Space() override = default;
  Space(const Space& other) = default;
  Space(Space&& other) = default;
  Space& operator=(const Space&) = default;
  Space& operator=(Space&&) = default;

  static IddObjectType iddObjectType();

  boost::optional<ThermalZone> thermalZone() const;
  bool setThermalZone(const ThermalZone& thermalZone);
  void resetThermalZone();
  boost::optional<DesignSpecificationOutdoorAir> designSpecificationOutdoorAir() const;
  bool setDesignSpecificationOutdoorAir(const DesignSpecificationOutdoorAir& designSpecificationOutdoorAir);

 protected:
  using ImplType = detail::Space_Impl;

  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;
  friend class openstudio::epmodel::Model;

  explicit Space(std::shared_ptr<detail::Space_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
