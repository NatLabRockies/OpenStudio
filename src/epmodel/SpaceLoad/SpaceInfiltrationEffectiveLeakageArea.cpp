/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SpaceInfiltrationEffectiveLeakageArea.hpp"
#include "SpaceInfiltrationEffectiveLeakageArea_Impl.hpp"

#include "Model.hpp"

#include <boost/optional.hpp>
#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneInfiltration_EffectiveLeakageArea_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace detail {

    SpaceInfiltrationEffectiveLeakageArea_Impl::SpaceInfiltrationEffectiveLeakageArea_Impl(const IdfObject& object, Model_Impl* model,
                                                                                           bool keepHandle)
      : ModelObject_Impl(object, model, keepHandle) {
      OS_ASSERT(object.iddObject().type() == SpaceInfiltrationEffectiveLeakageArea::iddObjectType());
    }

    SpaceInfiltrationEffectiveLeakageArea_Impl::SpaceInfiltrationEffectiveLeakageArea_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                                                                           Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(other, model, keepHandle) {
      OS_ASSERT(other.iddObject().type() == SpaceInfiltrationEffectiveLeakageArea::iddObjectType());
    }

    SpaceInfiltrationEffectiveLeakageArea_Impl::SpaceInfiltrationEffectiveLeakageArea_Impl(const SpaceInfiltrationEffectiveLeakageArea_Impl& other,
                                                                                           Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(other, model, keepHandle) {}

    double SpaceInfiltrationEffectiveLeakageArea_Impl::effectiveAirLeakageArea() const {
      boost::optional<double> value = getDouble(ZoneInfiltration_EffectiveLeakageAreaFields::EffectiveAirLeakageArea, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SpaceInfiltrationEffectiveLeakageArea_Impl::setEffectiveAirLeakageArea(double effectiveAirLeakageArea) {
      if (effectiveAirLeakageArea <= 0) {
        return false;
      }
      return setDouble(ZoneInfiltration_EffectiveLeakageAreaFields::EffectiveAirLeakageArea, effectiveAirLeakageArea);
    }

    double SpaceInfiltrationEffectiveLeakageArea_Impl::stackCoefficient() const {
      boost::optional<double> value = getDouble(ZoneInfiltration_EffectiveLeakageAreaFields::StackCoefficient, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SpaceInfiltrationEffectiveLeakageArea_Impl::setStackCoefficient(double stackCoefficient) {
      if (stackCoefficient <= 0) {
        return false;
      }
      return setDouble(ZoneInfiltration_EffectiveLeakageAreaFields::StackCoefficient, stackCoefficient);
    }

    double SpaceInfiltrationEffectiveLeakageArea_Impl::windCoefficient() const {
      boost::optional<double> value = getDouble(ZoneInfiltration_EffectiveLeakageAreaFields::WindCoefficient, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SpaceInfiltrationEffectiveLeakageArea_Impl::setWindCoefficient(double windCoefficient) {
      if (windCoefficient <= 0) {
        return false;
      }
      return setDouble(ZoneInfiltration_EffectiveLeakageAreaFields::WindCoefficient, windCoefficient);
    }

  }  // namespace detail

  SpaceInfiltrationEffectiveLeakageArea::SpaceInfiltrationEffectiveLeakageArea(const Model& model)
    : ModelObject(SpaceInfiltrationEffectiveLeakageArea::iddObjectType(), model) {
    OS_ASSERT(setEffectiveAirLeakageArea(0.1));
    OS_ASSERT(setStackCoefficient(0.1));
    OS_ASSERT(setWindCoefficient(0.1));
  }

  SpaceInfiltrationEffectiveLeakageArea::SpaceInfiltrationEffectiveLeakageArea(
    std::shared_ptr<detail::SpaceInfiltrationEffectiveLeakageArea_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SpaceInfiltrationEffectiveLeakageArea::iddObjectType() {
    return IddObjectType::ZoneInfiltration_EffectiveLeakageArea;
  }

  double SpaceInfiltrationEffectiveLeakageArea::effectiveAirLeakageArea() const {
    return getImpl<detail::SpaceInfiltrationEffectiveLeakageArea_Impl>()->effectiveAirLeakageArea();
  }

  bool SpaceInfiltrationEffectiveLeakageArea::setEffectiveAirLeakageArea(double effectiveAirLeakageArea) {
    return getImpl<detail::SpaceInfiltrationEffectiveLeakageArea_Impl>()->setEffectiveAirLeakageArea(effectiveAirLeakageArea);
  }

  double SpaceInfiltrationEffectiveLeakageArea::stackCoefficient() const {
    return getImpl<detail::SpaceInfiltrationEffectiveLeakageArea_Impl>()->stackCoefficient();
  }

  bool SpaceInfiltrationEffectiveLeakageArea::setStackCoefficient(double stackCoefficient) {
    return getImpl<detail::SpaceInfiltrationEffectiveLeakageArea_Impl>()->setStackCoefficient(stackCoefficient);
  }

  double SpaceInfiltrationEffectiveLeakageArea::windCoefficient() const {
    return getImpl<detail::SpaceInfiltrationEffectiveLeakageArea_Impl>()->windCoefficient();
  }

  bool SpaceInfiltrationEffectiveLeakageArea::setWindCoefficient(double windCoefficient) {
    return getImpl<detail::SpaceInfiltrationEffectiveLeakageArea_Impl>()->setWindCoefficient(windCoefficient);
  }

}  // namespace epmodel
}  // namespace openstudio
