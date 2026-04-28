/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GlobalGeometryRules.hpp"
#include "GlobalGeometryRules_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/GlobalGeometryRules_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  GlobalGeometryRules::GlobalGeometryRules(const Model& model) : ModelObject(GlobalGeometryRules::iddObjectType(), model) {}

  GlobalGeometryRules::GlobalGeometryRules(std::shared_ptr<detail::GlobalGeometryRules_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType GlobalGeometryRules::iddObjectType() {
    return IddObjectType::GlobalGeometryRules;
  }

  std::vector<std::string> GlobalGeometryRules::startingVertexPositionValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::GlobalGeometryRulesFields::StartingVertexPosition);
  }

  std::vector<std::string> GlobalGeometryRules::vertexEntryDirectionValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::GlobalGeometryRulesFields::VertexEntryDirection);
  }

  std::vector<std::string> GlobalGeometryRules::coordinateSystemValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::GlobalGeometryRulesFields::CoordinateSystem);
  }

  std::vector<std::string> GlobalGeometryRules::daylightingReferencePointCoordinateSystemValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::GlobalGeometryRulesFields::DaylightingReferencePointCoordinateSystem);
  }

  std::vector<std::string> GlobalGeometryRules::rectangularSurfaceCoordinateSystemValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::GlobalGeometryRulesFields::RectangularSurfaceCoordinateSystem);
  }

  std::string GlobalGeometryRules::startingVertexPosition() const {
    return getImpl<detail::GlobalGeometryRules_Impl>()->startingVertexPosition();
  }

  bool GlobalGeometryRules::setStartingVertexPosition(const std::string& startingVertexPosition) {
    return getImpl<detail::GlobalGeometryRules_Impl>()->setStartingVertexPosition(startingVertexPosition);
  }

  std::string GlobalGeometryRules::vertexEntryDirection() const {
    return getImpl<detail::GlobalGeometryRules_Impl>()->vertexEntryDirection();
  }

  bool GlobalGeometryRules::setVertexEntryDirection(const std::string& vertexEntryDirection) {
    return getImpl<detail::GlobalGeometryRules_Impl>()->setVertexEntryDirection(vertexEntryDirection);
  }

  std::string GlobalGeometryRules::coordinateSystem() const {
    return getImpl<detail::GlobalGeometryRules_Impl>()->coordinateSystem();
  }

  bool GlobalGeometryRules::setCoordinateSystem(const std::string& coordinateSystem) {
    return getImpl<detail::GlobalGeometryRules_Impl>()->setCoordinateSystem(coordinateSystem);
  }

  std::string GlobalGeometryRules::daylightingReferencePointCoordinateSystem() const {
    return getImpl<detail::GlobalGeometryRules_Impl>()->daylightingReferencePointCoordinateSystem();
  }

  bool GlobalGeometryRules::setDaylightingReferencePointCoordinateSystem(const std::string& daylightingReferencePointCoordinateSystem) {
    return getImpl<detail::GlobalGeometryRules_Impl>()->setDaylightingReferencePointCoordinateSystem(daylightingReferencePointCoordinateSystem);
  }

  bool GlobalGeometryRules::isDaylightingReferencePointCoordinateSystemDefaulted() const {
    return getImpl<detail::GlobalGeometryRules_Impl>()->isDaylightingReferencePointCoordinateSystemDefaulted();
  }

  void GlobalGeometryRules::resetDaylightingReferencePointCoordinateSystem() {
    getImpl<detail::GlobalGeometryRules_Impl>()->resetDaylightingReferencePointCoordinateSystem();
  }

  std::string GlobalGeometryRules::rectangularSurfaceCoordinateSystem() const {
    return getImpl<detail::GlobalGeometryRules_Impl>()->rectangularSurfaceCoordinateSystem();
  }

  bool GlobalGeometryRules::setRectangularSurfaceCoordinateSystem(const std::string& rectangularSurfaceCoordinateSystem) {
    return getImpl<detail::GlobalGeometryRules_Impl>()->setRectangularSurfaceCoordinateSystem(rectangularSurfaceCoordinateSystem);
  }

  bool GlobalGeometryRules::isRectangularSurfaceCoordinateSystemDefaulted() const {
    return getImpl<detail::GlobalGeometryRules_Impl>()->isRectangularSurfaceCoordinateSystemDefaulted();
  }

  void GlobalGeometryRules::resetRectangularSurfaceCoordinateSystem() {
    getImpl<detail::GlobalGeometryRules_Impl>()->resetRectangularSurfaceCoordinateSystem();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string GlobalGeometryRules_Impl::startingVertexPosition() const {
      const auto value = getString(openstudio::GlobalGeometryRulesFields::StartingVertexPosition, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GlobalGeometryRules_Impl::setStartingVertexPosition(const std::string& startingVertexPosition) {
      return setString(openstudio::GlobalGeometryRulesFields::StartingVertexPosition, startingVertexPosition);
    }

    std::string GlobalGeometryRules_Impl::vertexEntryDirection() const {
      const auto value = getString(openstudio::GlobalGeometryRulesFields::VertexEntryDirection, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GlobalGeometryRules_Impl::setVertexEntryDirection(const std::string& vertexEntryDirection) {
      return setString(openstudio::GlobalGeometryRulesFields::VertexEntryDirection, vertexEntryDirection);
    }

    std::string GlobalGeometryRules_Impl::coordinateSystem() const {
      const auto value = getString(openstudio::GlobalGeometryRulesFields::CoordinateSystem, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GlobalGeometryRules_Impl::setCoordinateSystem(const std::string& coordinateSystem) {
      return setString(openstudio::GlobalGeometryRulesFields::CoordinateSystem, coordinateSystem);
    }

    std::string GlobalGeometryRules_Impl::daylightingReferencePointCoordinateSystem() const {
      const auto value = getString(openstudio::GlobalGeometryRulesFields::DaylightingReferencePointCoordinateSystem, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GlobalGeometryRules_Impl::setDaylightingReferencePointCoordinateSystem(const std::string& daylightingReferencePointCoordinateSystem) {
      return setString(openstudio::GlobalGeometryRulesFields::DaylightingReferencePointCoordinateSystem, daylightingReferencePointCoordinateSystem);
    }

    bool GlobalGeometryRules_Impl::isDaylightingReferencePointCoordinateSystemDefaulted() const {
      return isEmpty(openstudio::GlobalGeometryRulesFields::DaylightingReferencePointCoordinateSystem);
    }

    void GlobalGeometryRules_Impl::resetDaylightingReferencePointCoordinateSystem() {
      OS_ASSERT(setString(openstudio::GlobalGeometryRulesFields::DaylightingReferencePointCoordinateSystem, ""));
    }

    std::string GlobalGeometryRules_Impl::rectangularSurfaceCoordinateSystem() const {
      const auto value = getString(openstudio::GlobalGeometryRulesFields::RectangularSurfaceCoordinateSystem, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GlobalGeometryRules_Impl::setRectangularSurfaceCoordinateSystem(const std::string& rectangularSurfaceCoordinateSystem) {
      return setString(openstudio::GlobalGeometryRulesFields::RectangularSurfaceCoordinateSystem, rectangularSurfaceCoordinateSystem);
    }

    bool GlobalGeometryRules_Impl::isRectangularSurfaceCoordinateSystemDefaulted() const {
      return isEmpty(openstudio::GlobalGeometryRulesFields::RectangularSurfaceCoordinateSystem);
    }

    void GlobalGeometryRules_Impl::resetRectangularSurfaceCoordinateSystem() {
      OS_ASSERT(setString(openstudio::GlobalGeometryRulesFields::RectangularSurfaceCoordinateSystem, ""));
    }

    std::vector<std::string> GlobalGeometryRules_Impl::startingVertexPositionValues() const {
      return openstudio::epmodel::GlobalGeometryRules::startingVertexPositionValues();
    }

    std::vector<std::string> GlobalGeometryRules_Impl::vertexEntryDirectionValues() const {
      return openstudio::epmodel::GlobalGeometryRules::vertexEntryDirectionValues();
    }

    std::vector<std::string> GlobalGeometryRules_Impl::coordinateSystemValues() const {
      return openstudio::epmodel::GlobalGeometryRules::coordinateSystemValues();
    }

    std::vector<std::string> GlobalGeometryRules_Impl::daylightingReferencePointCoordinateSystemValues() const {
      return openstudio::epmodel::GlobalGeometryRules::daylightingReferencePointCoordinateSystemValues();
    }

    std::vector<std::string> GlobalGeometryRules_Impl::rectangularSurfaceCoordinateSystemValues() const {
      return openstudio::epmodel::GlobalGeometryRules::rectangularSurfaceCoordinateSystemValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
