/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SurfacePropertyConvectionCoefficientsMultipleSurface.hpp"
#include "SurfacePropertyConvectionCoefficientsMultipleSurface_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/SurfaceProperty_ConvectionCoefficients_MultipleSurface_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  SurfacePropertyConvectionCoefficientsMultipleSurface::SurfacePropertyConvectionCoefficientsMultipleSurface(const Model& model)
    : ModelObject(SurfacePropertyConvectionCoefficientsMultipleSurface::iddObjectType(), model) {}

  SurfacePropertyConvectionCoefficientsMultipleSurface::SurfacePropertyConvectionCoefficientsMultipleSurface(
    std::shared_ptr<detail::SurfacePropertyConvectionCoefficientsMultipleSurface_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SurfacePropertyConvectionCoefficientsMultipleSurface::iddObjectType() {
    return IddObjectType::SurfaceProperty_ConvectionCoefficients_MultipleSurface;
  }

  std::vector<std::string> SurfacePropertyConvectionCoefficientsMultipleSurface::surfaceTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::SurfaceType);
  }

  std::vector<std::string> SurfacePropertyConvectionCoefficientsMultipleSurface::convectionCoefficient1LocationValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::ConvectionCoefficient1Location);
  }

  std::vector<std::string> SurfacePropertyConvectionCoefficientsMultipleSurface::convectionCoefficient1TypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::ConvectionCoefficient1Type);
  }

  std::vector<std::string> SurfacePropertyConvectionCoefficientsMultipleSurface::convectionCoefficient2LocationValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::ConvectionCoefficient2Location);
  }

  std::vector<std::string> SurfacePropertyConvectionCoefficientsMultipleSurface::convectionCoefficient2TypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::ConvectionCoefficient2Type);
  }

  boost::optional<std::string> SurfacePropertyConvectionCoefficientsMultipleSurface::surfaceType() const {
    return getImpl<detail::SurfacePropertyConvectionCoefficientsMultipleSurface_Impl>()->surfaceType();
  }

  bool SurfacePropertyConvectionCoefficientsMultipleSurface::setSurfaceType(const std::string& surfaceType) {
    return getImpl<detail::SurfacePropertyConvectionCoefficientsMultipleSurface_Impl>()->setSurfaceType(surfaceType);
  }

  void SurfacePropertyConvectionCoefficientsMultipleSurface::resetSurfaceType() {
    getImpl<detail::SurfacePropertyConvectionCoefficientsMultipleSurface_Impl>()->resetSurfaceType();
  }

  boost::optional<std::string> SurfacePropertyConvectionCoefficientsMultipleSurface::convectionCoefficient1Location() const {
    return getImpl<detail::SurfacePropertyConvectionCoefficientsMultipleSurface_Impl>()->convectionCoefficient1Location();
  }

  bool SurfacePropertyConvectionCoefficientsMultipleSurface::setConvectionCoefficient1Location(const std::string& convectionCoefficient1Location) {
    return getImpl<detail::SurfacePropertyConvectionCoefficientsMultipleSurface_Impl>()->setConvectionCoefficient1Location(
      convectionCoefficient1Location);
  }

  void SurfacePropertyConvectionCoefficientsMultipleSurface::resetConvectionCoefficient1Location() {
    getImpl<detail::SurfacePropertyConvectionCoefficientsMultipleSurface_Impl>()->resetConvectionCoefficient1Location();
  }

  boost::optional<std::string> SurfacePropertyConvectionCoefficientsMultipleSurface::convectionCoefficient1Type() const {
    return getImpl<detail::SurfacePropertyConvectionCoefficientsMultipleSurface_Impl>()->convectionCoefficient1Type();
  }

  bool SurfacePropertyConvectionCoefficientsMultipleSurface::setConvectionCoefficient1Type(const std::string& convectionCoefficient1Type) {
    return getImpl<detail::SurfacePropertyConvectionCoefficientsMultipleSurface_Impl>()->setConvectionCoefficient1Type(convectionCoefficient1Type);
  }

  void SurfacePropertyConvectionCoefficientsMultipleSurface::resetConvectionCoefficient1Type() {
    getImpl<detail::SurfacePropertyConvectionCoefficientsMultipleSurface_Impl>()->resetConvectionCoefficient1Type();
  }

  boost::optional<double> SurfacePropertyConvectionCoefficientsMultipleSurface::convectionCoefficient1() const {
    return getImpl<detail::SurfacePropertyConvectionCoefficientsMultipleSurface_Impl>()->convectionCoefficient1();
  }

  bool SurfacePropertyConvectionCoefficientsMultipleSurface::setConvectionCoefficient1(double convectionCoefficient1) {
    return getImpl<detail::SurfacePropertyConvectionCoefficientsMultipleSurface_Impl>()->setConvectionCoefficient1(convectionCoefficient1);
  }

  void SurfacePropertyConvectionCoefficientsMultipleSurface::resetConvectionCoefficient1() {
    getImpl<detail::SurfacePropertyConvectionCoefficientsMultipleSurface_Impl>()->resetConvectionCoefficient1();
  }

  boost::optional<std::string> SurfacePropertyConvectionCoefficientsMultipleSurface::convectionCoefficient2Location() const {
    return getImpl<detail::SurfacePropertyConvectionCoefficientsMultipleSurface_Impl>()->convectionCoefficient2Location();
  }

  bool SurfacePropertyConvectionCoefficientsMultipleSurface::setConvectionCoefficient2Location(const std::string& convectionCoefficient2Location) {
    return getImpl<detail::SurfacePropertyConvectionCoefficientsMultipleSurface_Impl>()->setConvectionCoefficient2Location(
      convectionCoefficient2Location);
  }

  void SurfacePropertyConvectionCoefficientsMultipleSurface::resetConvectionCoefficient2Location() {
    getImpl<detail::SurfacePropertyConvectionCoefficientsMultipleSurface_Impl>()->resetConvectionCoefficient2Location();
  }

  boost::optional<std::string> SurfacePropertyConvectionCoefficientsMultipleSurface::convectionCoefficient2Type() const {
    return getImpl<detail::SurfacePropertyConvectionCoefficientsMultipleSurface_Impl>()->convectionCoefficient2Type();
  }

  bool SurfacePropertyConvectionCoefficientsMultipleSurface::setConvectionCoefficient2Type(const std::string& convectionCoefficient2Type) {
    return getImpl<detail::SurfacePropertyConvectionCoefficientsMultipleSurface_Impl>()->setConvectionCoefficient2Type(convectionCoefficient2Type);
  }

  void SurfacePropertyConvectionCoefficientsMultipleSurface::resetConvectionCoefficient2Type() {
    getImpl<detail::SurfacePropertyConvectionCoefficientsMultipleSurface_Impl>()->resetConvectionCoefficient2Type();
  }

  boost::optional<double> SurfacePropertyConvectionCoefficientsMultipleSurface::convectionCoefficient2() const {
    return getImpl<detail::SurfacePropertyConvectionCoefficientsMultipleSurface_Impl>()->convectionCoefficient2();
  }

  bool SurfacePropertyConvectionCoefficientsMultipleSurface::setConvectionCoefficient2(double convectionCoefficient2) {
    return getImpl<detail::SurfacePropertyConvectionCoefficientsMultipleSurface_Impl>()->setConvectionCoefficient2(convectionCoefficient2);
  }

  void SurfacePropertyConvectionCoefficientsMultipleSurface::resetConvectionCoefficient2() {
    getImpl<detail::SurfacePropertyConvectionCoefficientsMultipleSurface_Impl>()->resetConvectionCoefficient2();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<std::string> SurfacePropertyConvectionCoefficientsMultipleSurface_Impl::surfaceType() const {
      return getString(openstudio::SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::SurfaceType, true);
    }

    bool SurfacePropertyConvectionCoefficientsMultipleSurface_Impl::setSurfaceType(const std::string& surfaceType) {
      return setString(openstudio::SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::SurfaceType, surfaceType);
    }

    void SurfacePropertyConvectionCoefficientsMultipleSurface_Impl::resetSurfaceType() {
      OS_ASSERT(setString(openstudio::SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::SurfaceType, ""));
    }

    boost::optional<std::string> SurfacePropertyConvectionCoefficientsMultipleSurface_Impl::convectionCoefficient1Location() const {
      return getString(openstudio::SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::ConvectionCoefficient1Location, true);
    }

    bool SurfacePropertyConvectionCoefficientsMultipleSurface_Impl::setConvectionCoefficient1Location(
      const std::string& convectionCoefficient1Location) {
      return setString(openstudio::SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::ConvectionCoefficient1Location,
                       convectionCoefficient1Location);
    }

    void SurfacePropertyConvectionCoefficientsMultipleSurface_Impl::resetConvectionCoefficient1Location() {
      OS_ASSERT(setString(openstudio::SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::ConvectionCoefficient1Location, ""));
    }

    boost::optional<std::string> SurfacePropertyConvectionCoefficientsMultipleSurface_Impl::convectionCoefficient1Type() const {
      return getString(openstudio::SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::ConvectionCoefficient1Type, true);
    }

    bool SurfacePropertyConvectionCoefficientsMultipleSurface_Impl::setConvectionCoefficient1Type(const std::string& convectionCoefficient1Type) {
      return setString(openstudio::SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::ConvectionCoefficient1Type,
                       convectionCoefficient1Type);
    }

    void SurfacePropertyConvectionCoefficientsMultipleSurface_Impl::resetConvectionCoefficient1Type() {
      OS_ASSERT(setString(openstudio::SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::ConvectionCoefficient1Type, ""));
    }

    boost::optional<double> SurfacePropertyConvectionCoefficientsMultipleSurface_Impl::convectionCoefficient1() const {
      return getDouble(openstudio::SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::ConvectionCoefficient1, true);
    }

    bool SurfacePropertyConvectionCoefficientsMultipleSurface_Impl::setConvectionCoefficient1(double convectionCoefficient1) {
      const bool result =
        setDouble(openstudio::SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::ConvectionCoefficient1, convectionCoefficient1);
      OS_ASSERT(result);
      return result;
    }

    void SurfacePropertyConvectionCoefficientsMultipleSurface_Impl::resetConvectionCoefficient1() {
      OS_ASSERT(setString(openstudio::SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::ConvectionCoefficient1, ""));
    }

    boost::optional<std::string> SurfacePropertyConvectionCoefficientsMultipleSurface_Impl::convectionCoefficient2Location() const {
      return getString(openstudio::SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::ConvectionCoefficient2Location, true);
    }

    bool SurfacePropertyConvectionCoefficientsMultipleSurface_Impl::setConvectionCoefficient2Location(
      const std::string& convectionCoefficient2Location) {
      return setString(openstudio::SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::ConvectionCoefficient2Location,
                       convectionCoefficient2Location);
    }

    void SurfacePropertyConvectionCoefficientsMultipleSurface_Impl::resetConvectionCoefficient2Location() {
      OS_ASSERT(setString(openstudio::SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::ConvectionCoefficient2Location, ""));
    }

    boost::optional<std::string> SurfacePropertyConvectionCoefficientsMultipleSurface_Impl::convectionCoefficient2Type() const {
      return getString(openstudio::SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::ConvectionCoefficient2Type, true);
    }

    bool SurfacePropertyConvectionCoefficientsMultipleSurface_Impl::setConvectionCoefficient2Type(const std::string& convectionCoefficient2Type) {
      return setString(openstudio::SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::ConvectionCoefficient2Type,
                       convectionCoefficient2Type);
    }

    void SurfacePropertyConvectionCoefficientsMultipleSurface_Impl::resetConvectionCoefficient2Type() {
      OS_ASSERT(setString(openstudio::SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::ConvectionCoefficient2Type, ""));
    }

    boost::optional<double> SurfacePropertyConvectionCoefficientsMultipleSurface_Impl::convectionCoefficient2() const {
      return getDouble(openstudio::SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::ConvectionCoefficient2, true);
    }

    bool SurfacePropertyConvectionCoefficientsMultipleSurface_Impl::setConvectionCoefficient2(double convectionCoefficient2) {
      const bool result =
        setDouble(openstudio::SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::ConvectionCoefficient2, convectionCoefficient2);
      OS_ASSERT(result);
      return result;
    }

    void SurfacePropertyConvectionCoefficientsMultipleSurface_Impl::resetConvectionCoefficient2() {
      OS_ASSERT(setString(openstudio::SurfaceProperty_ConvectionCoefficients_MultipleSurfaceFields::ConvectionCoefficient2, ""));
    }

    std::vector<std::string> SurfacePropertyConvectionCoefficientsMultipleSurface_Impl::surfaceTypeValues() const {
      return openstudio::epmodel::SurfacePropertyConvectionCoefficientsMultipleSurface::surfaceTypeValues();
    }

    std::vector<std::string> SurfacePropertyConvectionCoefficientsMultipleSurface_Impl::convectionCoefficient1LocationValues() const {
      return openstudio::epmodel::SurfacePropertyConvectionCoefficientsMultipleSurface::convectionCoefficient1LocationValues();
    }

    std::vector<std::string> SurfacePropertyConvectionCoefficientsMultipleSurface_Impl::convectionCoefficient1TypeValues() const {
      return openstudio::epmodel::SurfacePropertyConvectionCoefficientsMultipleSurface::convectionCoefficient1TypeValues();
    }

    std::vector<std::string> SurfacePropertyConvectionCoefficientsMultipleSurface_Impl::convectionCoefficient2LocationValues() const {
      return openstudio::epmodel::SurfacePropertyConvectionCoefficientsMultipleSurface::convectionCoefficient2LocationValues();
    }

    std::vector<std::string> SurfacePropertyConvectionCoefficientsMultipleSurface_Impl::convectionCoefficient2TypeValues() const {
      return openstudio::epmodel::SurfacePropertyConvectionCoefficientsMultipleSurface::convectionCoefficient2TypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
