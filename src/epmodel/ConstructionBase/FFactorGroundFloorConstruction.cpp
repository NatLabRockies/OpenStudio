/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ConstructionBase/FFactorGroundFloorConstruction.hpp"
#include "ConstructionBase/FFactorGroundFloorConstruction_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Construction_FfactorGroundFloor_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  FFactorGroundFloorConstruction::FFactorGroundFloorConstruction(const Model& model, double fFactor, double area, double perimeterExposed)
    : ModelObject(FFactorGroundFloorConstruction::iddObjectType(), model) {
    const bool okFFactor = setFFactor(fFactor);
    OS_ASSERT(okFFactor);
    const bool okArea = setArea(area);
    OS_ASSERT(okArea);
    const bool okPerimeterExposed = setPerimeterExposed(perimeterExposed);
    OS_ASSERT(okPerimeterExposed);
  }

  FFactorGroundFloorConstruction::FFactorGroundFloorConstruction(std::shared_ptr<detail::FFactorGroundFloorConstruction_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType FFactorGroundFloorConstruction::iddObjectType() {
    return IddObjectType::Construction_FfactorGroundFloor;
  }

  // F-Factor field
  double FFactorGroundFloorConstruction::fFactor() const {
    return getImpl<detail::FFactorGroundFloorConstruction_Impl>()->fFactor();
  }

  bool FFactorGroundFloorConstruction::setFFactor(double fFactor) {
    return getImpl<detail::FFactorGroundFloorConstruction_Impl>()->setFFactor(fFactor);
  }

  // Area field
  double FFactorGroundFloorConstruction::area() const {
    return getImpl<detail::FFactorGroundFloorConstruction_Impl>()->area();
  }

  bool FFactorGroundFloorConstruction::setArea(double area) {
    return getImpl<detail::FFactorGroundFloorConstruction_Impl>()->setArea(area);
  }

  // Perimeter Exposed field
  double FFactorGroundFloorConstruction::perimeterExposed() const {
    return getImpl<detail::FFactorGroundFloorConstruction_Impl>()->perimeterExposed();
  }

  bool FFactorGroundFloorConstruction::setPerimeterExposed(double perimeterExposed) {
    return getImpl<detail::FFactorGroundFloorConstruction_Impl>()->setPerimeterExposed(perimeterExposed);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double FFactorGroundFloorConstruction_Impl::fFactor() const {
      const auto value = getDouble(openstudio::Construction_FfactorGroundFloorFields::FFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FFactorGroundFloorConstruction_Impl::setFFactor(double fFactor) {
      const bool result = setDouble(openstudio::Construction_FfactorGroundFloorFields::FFactor, fFactor);
      return result;
    }

    // Area field
    double FFactorGroundFloorConstruction_Impl::area() const {
      const auto value = getDouble(openstudio::Construction_FfactorGroundFloorFields::Area, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FFactorGroundFloorConstruction_Impl::setArea(double area) {
      const bool result = setDouble(openstudio::Construction_FfactorGroundFloorFields::Area, area);
      return result;
    }

    // Perimeter Exposed field
    double FFactorGroundFloorConstruction_Impl::perimeterExposed() const {
      const auto value = getDouble(openstudio::Construction_FfactorGroundFloorFields::PerimeterExposed, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FFactorGroundFloorConstruction_Impl::setPerimeterExposed(double perimeterExposed) {
      const bool result = setDouble(openstudio::Construction_FfactorGroundFloorFields::PerimeterExposed, perimeterExposed);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
