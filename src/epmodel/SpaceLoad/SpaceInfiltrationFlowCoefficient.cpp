/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SpaceInfiltrationFlowCoefficient.hpp"
#include "SpaceInfiltrationFlowCoefficient_Impl.hpp"

#include "Model.hpp"

#include <boost/optional.hpp>
#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneInfiltration_FlowCoefficient_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace detail {

    SpaceInfiltrationFlowCoefficient_Impl::SpaceInfiltrationFlowCoefficient_Impl(const IdfObject& object, Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(object, model, keepHandle) {
      OS_ASSERT(object.iddObject().type() == SpaceInfiltrationFlowCoefficient::iddObjectType());
    }

    SpaceInfiltrationFlowCoefficient_Impl::SpaceInfiltrationFlowCoefficient_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                                                                 Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(other, model, keepHandle) {
      OS_ASSERT(other.iddObject().type() == SpaceInfiltrationFlowCoefficient::iddObjectType());
    }

    SpaceInfiltrationFlowCoefficient_Impl::SpaceInfiltrationFlowCoefficient_Impl(const SpaceInfiltrationFlowCoefficient_Impl& other,
                                                                                 Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(other, model, keepHandle) {}

    double SpaceInfiltrationFlowCoefficient_Impl::flowCoefficient() const {
      boost::optional<double> value = getDouble(ZoneInfiltration_FlowCoefficientFields::FlowCoefficient, true);
      OS_ASSERT(value);
      return value.get();
    }

    double SpaceInfiltrationFlowCoefficient_Impl::stackCoefficient() const {
      boost::optional<double> value = getDouble(ZoneInfiltration_FlowCoefficientFields::StackCoefficient, true);
      OS_ASSERT(value);
      return value.get();
    }

    double SpaceInfiltrationFlowCoefficient_Impl::pressureExponent() const {
      boost::optional<double> value = getDouble(ZoneInfiltration_FlowCoefficientFields::PressureExponent, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SpaceInfiltrationFlowCoefficient_Impl::isPressureExponentDefaulted() const {
      return isEmpty(ZoneInfiltration_FlowCoefficientFields::PressureExponent);
    }

    double SpaceInfiltrationFlowCoefficient_Impl::windCoefficient() const {
      boost::optional<double> value = getDouble(ZoneInfiltration_FlowCoefficientFields::WindCoefficient, true);
      OS_ASSERT(value);
      return value.get();
    }

    double SpaceInfiltrationFlowCoefficient_Impl::shelterFactor() const {
      boost::optional<double> value = getDouble(ZoneInfiltration_FlowCoefficientFields::ShelterFactor, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SpaceInfiltrationFlowCoefficient_Impl::setFlowCoefficient(double flowCoefficient) {
      if (flowCoefficient <= 0) {
        return false;
      }
      return setDouble(ZoneInfiltration_FlowCoefficientFields::FlowCoefficient, flowCoefficient);
    }

    bool SpaceInfiltrationFlowCoefficient_Impl::setStackCoefficient(double stackCoefficient) {
      if (stackCoefficient <= 0) {
        return false;
      }
      return setDouble(ZoneInfiltration_FlowCoefficientFields::StackCoefficient, stackCoefficient);
    }

    bool SpaceInfiltrationFlowCoefficient_Impl::setPressureExponent(double pressureExponent) {
      if (pressureExponent <= 0) {
        return false;
      }
      return setDouble(ZoneInfiltration_FlowCoefficientFields::PressureExponent, pressureExponent);
    }

    void SpaceInfiltrationFlowCoefficient_Impl::resetPressureExponent() {
      const bool result = setString(ZoneInfiltration_FlowCoefficientFields::PressureExponent, "");
      OS_ASSERT(result);
    }

    bool SpaceInfiltrationFlowCoefficient_Impl::setWindCoefficient(double windCoefficient) {
      if (windCoefficient <= 0) {
        return false;
      }
      return setDouble(ZoneInfiltration_FlowCoefficientFields::WindCoefficient, windCoefficient);
    }

    bool SpaceInfiltrationFlowCoefficient_Impl::setShelterFactor(double shelterFactor) {
      if (shelterFactor <= 0) {
        return false;
      }
      return setDouble(ZoneInfiltration_FlowCoefficientFields::ShelterFactor, shelterFactor);
    }

  }  // namespace detail

  SpaceInfiltrationFlowCoefficient::SpaceInfiltrationFlowCoefficient(const Model& model)
    : ModelObject(SpaceInfiltrationFlowCoefficient::iddObjectType(), model) {
    OS_ASSERT(setFlowCoefficient(0.2));
    OS_ASSERT(setStackCoefficient(0.2));
    OS_ASSERT(setPressureExponent(0.67));
    OS_ASSERT(setWindCoefficient(0.4));
    OS_ASSERT(setShelterFactor(1.0));
  }

  SpaceInfiltrationFlowCoefficient::SpaceInfiltrationFlowCoefficient(std::shared_ptr<detail::SpaceInfiltrationFlowCoefficient_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SpaceInfiltrationFlowCoefficient::iddObjectType() {
    return IddObjectType::ZoneInfiltration_FlowCoefficient;
  }

  double SpaceInfiltrationFlowCoefficient::flowCoefficient() const {
    return getImpl<detail::SpaceInfiltrationFlowCoefficient_Impl>()->flowCoefficient();
  }

  double SpaceInfiltrationFlowCoefficient::stackCoefficient() const {
    return getImpl<detail::SpaceInfiltrationFlowCoefficient_Impl>()->stackCoefficient();
  }

  double SpaceInfiltrationFlowCoefficient::pressureExponent() const {
    return getImpl<detail::SpaceInfiltrationFlowCoefficient_Impl>()->pressureExponent();
  }

  bool SpaceInfiltrationFlowCoefficient::isPressureExponentDefaulted() const {
    return getImpl<detail::SpaceInfiltrationFlowCoefficient_Impl>()->isPressureExponentDefaulted();
  }

  double SpaceInfiltrationFlowCoefficient::windCoefficient() const {
    return getImpl<detail::SpaceInfiltrationFlowCoefficient_Impl>()->windCoefficient();
  }

  double SpaceInfiltrationFlowCoefficient::shelterFactor() const {
    return getImpl<detail::SpaceInfiltrationFlowCoefficient_Impl>()->shelterFactor();
  }

  bool SpaceInfiltrationFlowCoefficient::setFlowCoefficient(double flowCoefficient) {
    return getImpl<detail::SpaceInfiltrationFlowCoefficient_Impl>()->setFlowCoefficient(flowCoefficient);
  }

  bool SpaceInfiltrationFlowCoefficient::setStackCoefficient(double stackCoefficient) {
    return getImpl<detail::SpaceInfiltrationFlowCoefficient_Impl>()->setStackCoefficient(stackCoefficient);
  }

  bool SpaceInfiltrationFlowCoefficient::setPressureExponent(double pressureExponent) {
    return getImpl<detail::SpaceInfiltrationFlowCoefficient_Impl>()->setPressureExponent(pressureExponent);
  }

  void SpaceInfiltrationFlowCoefficient::resetPressureExponent() {
    getImpl<detail::SpaceInfiltrationFlowCoefficient_Impl>()->resetPressureExponent();
  }

  bool SpaceInfiltrationFlowCoefficient::setWindCoefficient(double windCoefficient) {
    return getImpl<detail::SpaceInfiltrationFlowCoefficient_Impl>()->setWindCoefficient(windCoefficient);
  }

  bool SpaceInfiltrationFlowCoefficient::setShelterFactor(double shelterFactor) {
    return getImpl<detail::SpaceInfiltrationFlowCoefficient_Impl>()->setShelterFactor(shelterFactor);
  }

}  // namespace epmodel
}  // namespace openstudio
