/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ParentObject/Building.hpp"
#include "ParentObject/Building_Impl.hpp"

#include "Model.hpp"
#include "ResourceObject/ConstructionAssignmentSet.hpp"
#include "ResourceObject/ConstructionAssignmentSet_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/geometry/Geometry.hpp>
#include <utilities/geometry/Transformation.hpp>
#include <utilities/geometry/Vector3d.hpp>
#include <utilities/idd/Building_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  Building::Building(const Model& model) : ModelObject(Building::iddObjectType(), model) {}

  Building::Building(std::shared_ptr<detail::Building_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType Building::iddObjectType() {
    return IddObjectType::Building;
  }

  double Building::northAxis() const {
    return getImpl<detail::Building_Impl>()->northAxis();
  }

  bool Building::isNorthAxisDefaulted() const {
    return getImpl<detail::Building_Impl>()->isNorthAxisDefaulted();
  }

  bool Building::setNorthAxis(double northAxis) {
    return getImpl<detail::Building_Impl>()->setNorthAxis(northAxis);
  }

  void Building::resetNorthAxis() {
    getImpl<detail::Building_Impl>()->resetNorthAxis();
  }

  Transformation Building::transformation() const {
    return getImpl<detail::Building_Impl>()->transformation();
  }

  boost::optional<ConstructionAssignmentSet> Building::constructionAssignmentSet() const {
    return getImpl<detail::Building_Impl>()->constructionAssignmentSet();
  }

  bool Building::setConstructionAssignmentSet(const ConstructionAssignmentSet& constructionAssignmentSet) {
    return getImpl<detail::Building_Impl>()->setConstructionAssignmentSet(constructionAssignmentSet);
  }

  void Building::resetConstructionAssignmentSet() {
    getImpl<detail::Building_Impl>()->resetConstructionAssignmentSet();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double Building_Impl::northAxis() const {
      const auto value = getDouble(openstudio::BuildingFields::NorthAxis, true);
      OS_ASSERT(value);
      return *value;
    }

    bool Building_Impl::isNorthAxisDefaulted() const {
      return !getDouble(openstudio::BuildingFields::NorthAxis, false);
    }

    bool Building_Impl::setNorthAxis(double northAxis) {
      return setDouble(openstudio::BuildingFields::NorthAxis, northAxis);
    }

    void Building_Impl::resetNorthAxis() {
      OS_ASSERT(setString(openstudio::BuildingFields::NorthAxis, ""));
    }

    Transformation Building_Impl::transformation() const {
      // rotate negative amount around the z axis, EnergyPlus defines rotation clockwise
      return Transformation::rotation(Vector3d(0, 0, 1), -degToRad(this->northAxis()));
    }

    boost::optional<ConstructionAssignmentSet> Building_Impl::constructionAssignmentSet() const {
      return getObject<ModelObject>().getModelObjectTarget<ConstructionAssignmentSet>(openstudio::BuildingFields::ConstructionAssignmentSetName);
    }

    bool Building_Impl::setConstructionAssignmentSet(const ConstructionAssignmentSet& constructionAssignmentSet) {
      return setPointer(openstudio::BuildingFields::ConstructionAssignmentSetName, constructionAssignmentSet.handle());
    }

    void Building_Impl::resetConstructionAssignmentSet() {
      OS_ASSERT(setString(openstudio::BuildingFields::ConstructionAssignmentSetName, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
