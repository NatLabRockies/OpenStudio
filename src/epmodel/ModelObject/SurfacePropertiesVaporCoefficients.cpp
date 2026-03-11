/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SurfacePropertiesVaporCoefficients.hpp"
#include "SurfacePropertiesVaporCoefficients_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/SurfaceProperties_VaporCoefficients_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

  SurfacePropertiesVaporCoefficients::SurfacePropertiesVaporCoefficients(const Model& model)
    : ModelObject(SurfacePropertiesVaporCoefficients::iddObjectType(), model) {}

  SurfacePropertiesVaporCoefficients::SurfacePropertiesVaporCoefficients(std::shared_ptr<detail::SurfacePropertiesVaporCoefficients_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SurfacePropertiesVaporCoefficients::iddObjectType() {
    return IddObjectType::SurfaceProperties_VaporCoefficients;
  }

  std::vector<std::string> SurfacePropertiesVaporCoefficients::constantExternalVaporTransferCoefficientValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceProperties_VaporCoefficientsFields::ConstantExternalVaporTransferCoefficient);
  }

  std::vector<std::string> SurfacePropertiesVaporCoefficients::constantInternalvaporTransferCoefficientValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceProperties_VaporCoefficientsFields::ConstantInternalvaporTransferCoefficient);
  }

  bool SurfacePropertiesVaporCoefficients::constantExternalVaporTransferCoefficient() const {
    return getImpl<detail::SurfacePropertiesVaporCoefficients_Impl>()->constantExternalVaporTransferCoefficient();
  }

  bool SurfacePropertiesVaporCoefficients::isConstantExternalVaporTransferCoefficientDefaulted() const {
    return getImpl<detail::SurfacePropertiesVaporCoefficients_Impl>()->isConstantExternalVaporTransferCoefficientDefaulted();
  }

  bool SurfacePropertiesVaporCoefficients::setConstantExternalVaporTransferCoefficient(bool constantExternalVaporTransferCoefficient) {
    return getImpl<detail::SurfacePropertiesVaporCoefficients_Impl>()->setConstantExternalVaporTransferCoefficient(
      constantExternalVaporTransferCoefficient);
  }

  void SurfacePropertiesVaporCoefficients::setConstantExternalVaporTransferCoefficientNoFail(bool constantExternalVaporTransferCoefficient) {
    const bool result = setConstantExternalVaporTransferCoefficient(constantExternalVaporTransferCoefficient);
    OS_ASSERT(result);
  }

  void SurfacePropertiesVaporCoefficients::resetConstantExternalVaporTransferCoefficient() {
    getImpl<detail::SurfacePropertiesVaporCoefficients_Impl>()->resetConstantExternalVaporTransferCoefficient();
  }

  double SurfacePropertiesVaporCoefficients::externalVaporCoefficientValue() const {
    return getImpl<detail::SurfacePropertiesVaporCoefficients_Impl>()->externalVaporCoefficientValue();
  }

  bool SurfacePropertiesVaporCoefficients::isExternalVaporCoefficientValueDefaulted() const {
    return getImpl<detail::SurfacePropertiesVaporCoefficients_Impl>()->isExternalVaporCoefficientValueDefaulted();
  }

  bool SurfacePropertiesVaporCoefficients::setExternalVaporCoefficientValue(double externalVaporCoefficientValue) {
    return getImpl<detail::SurfacePropertiesVaporCoefficients_Impl>()->setExternalVaporCoefficientValue(externalVaporCoefficientValue);
  }

  void SurfacePropertiesVaporCoefficients::resetExternalVaporCoefficientValue() {
    getImpl<detail::SurfacePropertiesVaporCoefficients_Impl>()->resetExternalVaporCoefficientValue();
  }

  bool SurfacePropertiesVaporCoefficients::constantInternalvaporTransferCoefficient() const {
    return getImpl<detail::SurfacePropertiesVaporCoefficients_Impl>()->constantInternalvaporTransferCoefficient();
  }

  bool SurfacePropertiesVaporCoefficients::isConstantInternalvaporTransferCoefficientDefaulted() const {
    return getImpl<detail::SurfacePropertiesVaporCoefficients_Impl>()->isConstantInternalvaporTransferCoefficientDefaulted();
  }

  bool SurfacePropertiesVaporCoefficients::setConstantInternalvaporTransferCoefficient(bool constantInternalvaporTransferCoefficient) {
    return getImpl<detail::SurfacePropertiesVaporCoefficients_Impl>()->setConstantInternalvaporTransferCoefficient(
      constantInternalvaporTransferCoefficient);
  }

  void SurfacePropertiesVaporCoefficients::setConstantInternalvaporTransferCoefficientNoFail(bool constantInternalvaporTransferCoefficient) {
    const bool result = setConstantInternalvaporTransferCoefficient(constantInternalvaporTransferCoefficient);
    OS_ASSERT(result);
  }

  void SurfacePropertiesVaporCoefficients::resetConstantInternalvaporTransferCoefficient() {
    getImpl<detail::SurfacePropertiesVaporCoefficients_Impl>()->resetConstantInternalvaporTransferCoefficient();
  }

  double SurfacePropertiesVaporCoefficients::internalVaporCoefficientValue() const {
    return getImpl<detail::SurfacePropertiesVaporCoefficients_Impl>()->internalVaporCoefficientValue();
  }

  bool SurfacePropertiesVaporCoefficients::isInternalVaporCoefficientValueDefaulted() const {
    return getImpl<detail::SurfacePropertiesVaporCoefficients_Impl>()->isInternalVaporCoefficientValueDefaulted();
  }

  bool SurfacePropertiesVaporCoefficients::setInternalVaporCoefficientValue(double internalVaporCoefficientValue) {
    return getImpl<detail::SurfacePropertiesVaporCoefficients_Impl>()->setInternalVaporCoefficientValue(internalVaporCoefficientValue);
  }

  void SurfacePropertiesVaporCoefficients::resetInternalVaporCoefficientValue() {
    getImpl<detail::SurfacePropertiesVaporCoefficients_Impl>()->resetInternalVaporCoefficientValue();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    bool SurfacePropertiesVaporCoefficients_Impl::constantExternalVaporTransferCoefficient() const {
      const auto value = getString(openstudio::SurfaceProperties_VaporCoefficientsFields::ConstantExternalVaporTransferCoefficient, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "Yes");
    }

    bool SurfacePropertiesVaporCoefficients_Impl::isConstantExternalVaporTransferCoefficientDefaulted() const {
      return isEmpty(openstudio::SurfaceProperties_VaporCoefficientsFields::ConstantExternalVaporTransferCoefficient);
    }

    bool SurfacePropertiesVaporCoefficients_Impl::setConstantExternalVaporTransferCoefficient(bool constantExternalVaporTransferCoefficient) {
      const bool result = setString(openstudio::SurfaceProperties_VaporCoefficientsFields::ConstantExternalVaporTransferCoefficient,
                                    constantExternalVaporTransferCoefficient ? "Yes" : "No");
      OS_ASSERT(result);
      return result;
    }

    void SurfacePropertiesVaporCoefficients_Impl::resetConstantExternalVaporTransferCoefficient() {
      OS_ASSERT(setString(openstudio::SurfaceProperties_VaporCoefficientsFields::ConstantExternalVaporTransferCoefficient, ""));
    }

    double SurfacePropertiesVaporCoefficients_Impl::externalVaporCoefficientValue() const {
      if (auto value = getDouble(openstudio::SurfaceProperties_VaporCoefficientsFields::ExternalVaporCoefficientValue, false)) {
        return *value;
      }
      return 0.0;
    }

    bool SurfacePropertiesVaporCoefficients_Impl::isExternalVaporCoefficientValueDefaulted() const {
      return isEmpty(openstudio::SurfaceProperties_VaporCoefficientsFields::ExternalVaporCoefficientValue);
    }

    bool SurfacePropertiesVaporCoefficients_Impl::setExternalVaporCoefficientValue(double externalVaporCoefficientValue) {
      const bool result =
        setDouble(openstudio::SurfaceProperties_VaporCoefficientsFields::ExternalVaporCoefficientValue, externalVaporCoefficientValue);
      return result;
    }

    void SurfacePropertiesVaporCoefficients_Impl::resetExternalVaporCoefficientValue() {
      OS_ASSERT(setString(openstudio::SurfaceProperties_VaporCoefficientsFields::ExternalVaporCoefficientValue, ""));
    }

    bool SurfacePropertiesVaporCoefficients_Impl::constantInternalvaporTransferCoefficient() const {
      const auto value = getString(openstudio::SurfaceProperties_VaporCoefficientsFields::ConstantInternalvaporTransferCoefficient, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "Yes");
    }

    bool SurfacePropertiesVaporCoefficients_Impl::isConstantInternalvaporTransferCoefficientDefaulted() const {
      return isEmpty(openstudio::SurfaceProperties_VaporCoefficientsFields::ConstantInternalvaporTransferCoefficient);
    }

    bool SurfacePropertiesVaporCoefficients_Impl::setConstantInternalvaporTransferCoefficient(bool constantInternalvaporTransferCoefficient) {
      const bool result = setString(openstudio::SurfaceProperties_VaporCoefficientsFields::ConstantInternalvaporTransferCoefficient,
                                    constantInternalvaporTransferCoefficient ? "Yes" : "No");
      OS_ASSERT(result);
      return result;
    }

    void SurfacePropertiesVaporCoefficients_Impl::resetConstantInternalvaporTransferCoefficient() {
      OS_ASSERT(setString(openstudio::SurfaceProperties_VaporCoefficientsFields::ConstantInternalvaporTransferCoefficient, ""));
    }

    double SurfacePropertiesVaporCoefficients_Impl::internalVaporCoefficientValue() const {
      if (auto value = getDouble(openstudio::SurfaceProperties_VaporCoefficientsFields::InternalVaporCoefficientValue, false)) {
        return *value;
      }
      return 0.0;
    }

    bool SurfacePropertiesVaporCoefficients_Impl::isInternalVaporCoefficientValueDefaulted() const {
      return isEmpty(openstudio::SurfaceProperties_VaporCoefficientsFields::InternalVaporCoefficientValue);
    }

    bool SurfacePropertiesVaporCoefficients_Impl::setInternalVaporCoefficientValue(double internalVaporCoefficientValue) {
      const bool result =
        setDouble(openstudio::SurfaceProperties_VaporCoefficientsFields::InternalVaporCoefficientValue, internalVaporCoefficientValue);
      return result;
    }

    void SurfacePropertiesVaporCoefficients_Impl::resetInternalVaporCoefficientValue() {
      OS_ASSERT(setString(openstudio::SurfaceProperties_VaporCoefficientsFields::InternalVaporCoefficientValue, ""));
    }

    std::vector<std::string> SurfacePropertiesVaporCoefficients_Impl::constantExternalVaporTransferCoefficientValues() const {
      return SurfacePropertiesVaporCoefficients::constantExternalVaporTransferCoefficientValues();
    }

    std::vector<std::string> SurfacePropertiesVaporCoefficients_Impl::constantInternalvaporTransferCoefficientValues() const {
      return SurfacePropertiesVaporCoefficients::constantInternalvaporTransferCoefficientValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
