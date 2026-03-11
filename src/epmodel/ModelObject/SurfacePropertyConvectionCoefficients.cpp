/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SurfacePropertyConvectionCoefficients.hpp"
#include "SurfacePropertyConvectionCoefficients_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/SurfaceProperty_ConvectionCoefficients_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  SurfacePropertyConvectionCoefficients::SurfacePropertyConvectionCoefficients(const Model& model)
    : ModelObject(SurfacePropertyConvectionCoefficients::iddObjectType(), model) {}

  SurfacePropertyConvectionCoefficients::SurfacePropertyConvectionCoefficients(
    std::shared_ptr<detail::SurfacePropertyConvectionCoefficients_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SurfacePropertyConvectionCoefficients::iddObjectType() {
    return IddObjectType::SurfaceProperty_ConvectionCoefficients;
  }

  std::vector<std::string> SurfacePropertyConvectionCoefficients::convectionCoefficient1LocationValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient1Location);
  }

  std::vector<std::string> SurfacePropertyConvectionCoefficients::convectionCoefficient1TypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient1Type);
  }

  std::vector<std::string> SurfacePropertyConvectionCoefficients::convectionCoefficient2LocationValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient2Location);
  }

  std::vector<std::string> SurfacePropertyConvectionCoefficients::convectionCoefficient2TypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient2Type);
  }

  boost::optional<std::string> SurfacePropertyConvectionCoefficients::convectionCoefficient1Location() const {
    return getImpl<detail::SurfacePropertyConvectionCoefficients_Impl>()->convectionCoefficient1Location();
  }

  bool SurfacePropertyConvectionCoefficients::setConvectionCoefficient1Location(const std::string& convectionCoefficient1Location) {
    return getImpl<detail::SurfacePropertyConvectionCoefficients_Impl>()->setConvectionCoefficient1Location(convectionCoefficient1Location);
  }

  void SurfacePropertyConvectionCoefficients::resetConvectionCoefficient1Location() {
    getImpl<detail::SurfacePropertyConvectionCoefficients_Impl>()->resetConvectionCoefficient1Location();
  }

  boost::optional<std::string> SurfacePropertyConvectionCoefficients::convectionCoefficient1Type() const {
    return getImpl<detail::SurfacePropertyConvectionCoefficients_Impl>()->convectionCoefficient1Type();
  }

  bool SurfacePropertyConvectionCoefficients::setConvectionCoefficient1Type(const std::string& convectionCoefficient1Type) {
    return getImpl<detail::SurfacePropertyConvectionCoefficients_Impl>()->setConvectionCoefficient1Type(convectionCoefficient1Type);
  }

  void SurfacePropertyConvectionCoefficients::resetConvectionCoefficient1Type() {
    getImpl<detail::SurfacePropertyConvectionCoefficients_Impl>()->resetConvectionCoefficient1Type();
  }

  boost::optional<double> SurfacePropertyConvectionCoefficients::convectionCoefficient1() const {
    return getImpl<detail::SurfacePropertyConvectionCoefficients_Impl>()->convectionCoefficient1();
  }

  bool SurfacePropertyConvectionCoefficients::setConvectionCoefficient1(double convectionCoefficient1) {
    return getImpl<detail::SurfacePropertyConvectionCoefficients_Impl>()->setConvectionCoefficient1(convectionCoefficient1);
  }

  void SurfacePropertyConvectionCoefficients::resetConvectionCoefficient1() {
    getImpl<detail::SurfacePropertyConvectionCoefficients_Impl>()->resetConvectionCoefficient1();
  }

  boost::optional<std::string> SurfacePropertyConvectionCoefficients::convectionCoefficient2Location() const {
    return getImpl<detail::SurfacePropertyConvectionCoefficients_Impl>()->convectionCoefficient2Location();
  }

  bool SurfacePropertyConvectionCoefficients::setConvectionCoefficient2Location(const std::string& convectionCoefficient2Location) {
    return getImpl<detail::SurfacePropertyConvectionCoefficients_Impl>()->setConvectionCoefficient2Location(convectionCoefficient2Location);
  }

  void SurfacePropertyConvectionCoefficients::resetConvectionCoefficient2Location() {
    getImpl<detail::SurfacePropertyConvectionCoefficients_Impl>()->resetConvectionCoefficient2Location();
  }

  boost::optional<std::string> SurfacePropertyConvectionCoefficients::convectionCoefficient2Type() const {
    return getImpl<detail::SurfacePropertyConvectionCoefficients_Impl>()->convectionCoefficient2Type();
  }

  bool SurfacePropertyConvectionCoefficients::setConvectionCoefficient2Type(const std::string& convectionCoefficient2Type) {
    return getImpl<detail::SurfacePropertyConvectionCoefficients_Impl>()->setConvectionCoefficient2Type(convectionCoefficient2Type);
  }

  void SurfacePropertyConvectionCoefficients::resetConvectionCoefficient2Type() {
    getImpl<detail::SurfacePropertyConvectionCoefficients_Impl>()->resetConvectionCoefficient2Type();
  }

  boost::optional<double> SurfacePropertyConvectionCoefficients::convectionCoefficient2() const {
    return getImpl<detail::SurfacePropertyConvectionCoefficients_Impl>()->convectionCoefficient2();
  }

  bool SurfacePropertyConvectionCoefficients::setConvectionCoefficient2(double convectionCoefficient2) {
    return getImpl<detail::SurfacePropertyConvectionCoefficients_Impl>()->setConvectionCoefficient2(convectionCoefficient2);
  }

  void SurfacePropertyConvectionCoefficients::resetConvectionCoefficient2() {
    getImpl<detail::SurfacePropertyConvectionCoefficients_Impl>()->resetConvectionCoefficient2();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<std::string> SurfacePropertyConvectionCoefficients_Impl::convectionCoefficient1Location() const {
      return getString(openstudio::SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient1Location, true);
    }

    bool SurfacePropertyConvectionCoefficients_Impl::setConvectionCoefficient1Location(const std::string& convectionCoefficient1Location) {
      return setString(openstudio::SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient1Location, convectionCoefficient1Location);
    }

    void SurfacePropertyConvectionCoefficients_Impl::resetConvectionCoefficient1Location() {
      OS_ASSERT(setString(openstudio::SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient1Location, ""));
    }

    boost::optional<std::string> SurfacePropertyConvectionCoefficients_Impl::convectionCoefficient1Type() const {
      return getString(openstudio::SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient1Type, true);
    }

    bool SurfacePropertyConvectionCoefficients_Impl::setConvectionCoefficient1Type(const std::string& convectionCoefficient1Type) {
      return setString(openstudio::SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient1Type, convectionCoefficient1Type);
    }

    void SurfacePropertyConvectionCoefficients_Impl::resetConvectionCoefficient1Type() {
      OS_ASSERT(setString(openstudio::SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient1Type, ""));
    }

    boost::optional<double> SurfacePropertyConvectionCoefficients_Impl::convectionCoefficient1() const {
      return getDouble(openstudio::SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient1, true);
    }

    bool SurfacePropertyConvectionCoefficients_Impl::setConvectionCoefficient1(double convectionCoefficient1) {
      const bool result = setDouble(openstudio::SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient1, convectionCoefficient1);
      OS_ASSERT(result);
      return result;
    }

    void SurfacePropertyConvectionCoefficients_Impl::resetConvectionCoefficient1() {
      OS_ASSERT(setString(openstudio::SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient1, ""));
    }

    boost::optional<std::string> SurfacePropertyConvectionCoefficients_Impl::convectionCoefficient2Location() const {
      return getString(openstudio::SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient2Location, true);
    }

    bool SurfacePropertyConvectionCoefficients_Impl::setConvectionCoefficient2Location(const std::string& convectionCoefficient2Location) {
      return setString(openstudio::SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient2Location, convectionCoefficient2Location);
    }

    void SurfacePropertyConvectionCoefficients_Impl::resetConvectionCoefficient2Location() {
      OS_ASSERT(setString(openstudio::SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient2Location, ""));
    }

    boost::optional<std::string> SurfacePropertyConvectionCoefficients_Impl::convectionCoefficient2Type() const {
      return getString(openstudio::SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient2Type, true);
    }

    bool SurfacePropertyConvectionCoefficients_Impl::setConvectionCoefficient2Type(const std::string& convectionCoefficient2Type) {
      return setString(openstudio::SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient2Type, convectionCoefficient2Type);
    }

    void SurfacePropertyConvectionCoefficients_Impl::resetConvectionCoefficient2Type() {
      OS_ASSERT(setString(openstudio::SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient2Type, ""));
    }

    boost::optional<double> SurfacePropertyConvectionCoefficients_Impl::convectionCoefficient2() const {
      return getDouble(openstudio::SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient2, true);
    }

    bool SurfacePropertyConvectionCoefficients_Impl::setConvectionCoefficient2(double convectionCoefficient2) {
      const bool result = setDouble(openstudio::SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient2, convectionCoefficient2);
      OS_ASSERT(result);
      return result;
    }

    void SurfacePropertyConvectionCoefficients_Impl::resetConvectionCoefficient2() {
      OS_ASSERT(setString(openstudio::SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient2, ""));
    }

    std::vector<std::string> SurfacePropertyConvectionCoefficients_Impl::convectionCoefficient1LocationValues() const {
      return openstudio::epmodel::SurfacePropertyConvectionCoefficients::convectionCoefficient1LocationValues();
    }

    std::vector<std::string> SurfacePropertyConvectionCoefficients_Impl::convectionCoefficient1TypeValues() const {
      return openstudio::epmodel::SurfacePropertyConvectionCoefficients::convectionCoefficient1TypeValues();
    }

    std::vector<std::string> SurfacePropertyConvectionCoefficients_Impl::convectionCoefficient2LocationValues() const {
      return openstudio::epmodel::SurfacePropertyConvectionCoefficients::convectionCoefficient2LocationValues();
    }

    std::vector<std::string> SurfacePropertyConvectionCoefficients_Impl::convectionCoefficient2TypeValues() const {
      return openstudio::epmodel::SurfacePropertyConvectionCoefficients::convectionCoefficient2TypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
