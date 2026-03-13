/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ResourceObject/ShadingControl.hpp"
#include "ResourceObject/ShadingControl_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/WindowShadingControl_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ShadingControl::ShadingControl(const Model& model) : ModelObject(ShadingControl::iddObjectType(), model) {
    OS_ASSERT(setShadingType("InteriorShade"));
    OS_ASSERT(setShadingControlType("AlwaysOn"));
    OS_ASSERT(setShadingControlSequenceNumber(1));
    OS_ASSERT(setTypeofSlatAngleControlforBlinds("FixedSlatAngle"));
    OS_ASSERT(setMultipleSurfaceControlType("Sequential"));
    OS_ASSERT(setGlareControlIsActive(false));
  }

  ShadingControl::ShadingControl(std::shared_ptr<detail::ShadingControl_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ShadingControl::iddObjectType() {
    return IddObjectType::WindowShadingControl;
  }

  std::vector<std::string> ShadingControl::shadingTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WindowShadingControlFields::ShadingType);
  }

  std::vector<std::string> ShadingControl::shadingControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WindowShadingControlFields::ShadingControlType);
  }

  std::vector<std::string> ShadingControl::typeofSlatAngleControlforBlindsValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::WindowShadingControlFields::TypeofSlatAngleControlforBlinds);
  }

  std::vector<std::string> ShadingControl::multipleSurfaceControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::WindowShadingControlFields::MultipleSurfaceControlType);
  }

  std::string ShadingControl::shadingType() const {
    return getImpl<detail::ShadingControl_Impl>()->shadingType();
  }

  bool ShadingControl::setShadingType(const std::string& shadingType) {
    return getImpl<detail::ShadingControl_Impl>()->setShadingType(shadingType);
  }

  int ShadingControl::shadingControlSequenceNumber() const {
    return getImpl<detail::ShadingControl_Impl>()->shadingControlSequenceNumber();
  }

  bool ShadingControl::setShadingControlSequenceNumber(int shadingControlSequenceNumber) {
    return getImpl<detail::ShadingControl_Impl>()->setShadingControlSequenceNumber(shadingControlSequenceNumber);
  }

  bool ShadingControl::isShadingControlSequenceNumberDefaulted() const {
    return getImpl<detail::ShadingControl_Impl>()->isShadingControlSequenceNumberDefaulted();
  }

  void ShadingControl::resetShadingControlSequenceNumber() {
    getImpl<detail::ShadingControl_Impl>()->resetShadingControlSequenceNumber();
  }

  std::string ShadingControl::shadingControlType() const {
    return getImpl<detail::ShadingControl_Impl>()->shadingControlType();
  }

  bool ShadingControl::isShadingControlTypeDefaulted() const {
    return getImpl<detail::ShadingControl_Impl>()->isShadingControlTypeDefaulted();
  }

  bool ShadingControl::setShadingControlType(const std::string& shadingControlType) {
    return getImpl<detail::ShadingControl_Impl>()->setShadingControlType(shadingControlType);
  }

  void ShadingControl::resetShadingControlType() {
    getImpl<detail::ShadingControl_Impl>()->resetShadingControlType();
  }

  boost::optional<double> ShadingControl::setpoint() const {
    return getImpl<detail::ShadingControl_Impl>()->setpoint();
  }

  bool ShadingControl::setSetpoint(double setpoint) {
    return getImpl<detail::ShadingControl_Impl>()->setSetpoint(setpoint);
  }

  void ShadingControl::resetSetpoint() {
    getImpl<detail::ShadingControl_Impl>()->resetSetpoint();
  }

  bool ShadingControl::isSetpointDefaulted() const {
    return getImpl<detail::ShadingControl_Impl>()->isSetpointDefaulted();
  }

  bool ShadingControl::glareControlIsActive() const {
    return getImpl<detail::ShadingControl_Impl>()->glareControlIsActive();
  }

  bool ShadingControl::setGlareControlIsActive(bool glareControlIsActive) {
    return getImpl<detail::ShadingControl_Impl>()->setGlareControlIsActive(glareControlIsActive);
  }

  void ShadingControl::resetGlareControlIsActive() {
    getImpl<detail::ShadingControl_Impl>()->resetGlareControlIsActive();
  }

  std::string ShadingControl::typeofSlatAngleControlforBlinds() const {
    return getImpl<detail::ShadingControl_Impl>()->typeofSlatAngleControlforBlinds();
  }

  bool ShadingControl::isTypeofSlatAngleControlforBlindsDefaulted() const {
    return getImpl<detail::ShadingControl_Impl>()->isTypeofSlatAngleControlforBlindsDefaulted();
  }

  bool ShadingControl::setTypeofSlatAngleControlforBlinds(const std::string& typeofSlatAngleControlforBlinds) {
    return getImpl<detail::ShadingControl_Impl>()->setTypeofSlatAngleControlforBlinds(typeofSlatAngleControlforBlinds);
  }

  void ShadingControl::resetTypeofSlatAngleControlforBlinds() {
    getImpl<detail::ShadingControl_Impl>()->resetTypeofSlatAngleControlforBlinds();
  }

  boost::optional<double> ShadingControl::setpoint2() const {
    return getImpl<detail::ShadingControl_Impl>()->setpoint2();
  }

  bool ShadingControl::setSetpoint2(double setpoint2) {
    return getImpl<detail::ShadingControl_Impl>()->setSetpoint2(setpoint2);
  }

  std::string ShadingControl::multipleSurfaceControlType() const {
    return getImpl<detail::ShadingControl_Impl>()->multipleSurfaceControlType();
  }

  bool ShadingControl::setMultipleSurfaceControlType(const std::string& multipleSurfaceControlType) {
    return getImpl<detail::ShadingControl_Impl>()->setMultipleSurfaceControlType(multipleSurfaceControlType);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {

      bool getBooleanFieldValue(const ModelObject_Impl& impl, int fieldIndex) {
        const auto value = impl.getString(fieldIndex, true);
        OS_ASSERT(value);
        return openstudio::istringEqual(*value, "Yes");
      }

      bool setBooleanFieldValue(ModelObject_Impl& impl, int fieldIndex, bool value) {
        return impl.setString(fieldIndex, value ? "Yes" : "No");
      }

    }  // namespace

    std::string ShadingControl_Impl::shadingType() const {
      const auto value = getString(openstudio::WindowShadingControlFields::ShadingType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ShadingControl_Impl::setShadingType(const std::string& shadingType) {
      return setString(openstudio::WindowShadingControlFields::ShadingType, shadingType);
    }

    int ShadingControl_Impl::shadingControlSequenceNumber() const {
      const auto value = getInt(openstudio::WindowShadingControlFields::ShadingControlSequenceNumber, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ShadingControl_Impl::setShadingControlSequenceNumber(int shadingControlSequenceNumber) {
      return setInt(openstudio::WindowShadingControlFields::ShadingControlSequenceNumber, shadingControlSequenceNumber);
    }

    bool ShadingControl_Impl::isShadingControlSequenceNumberDefaulted() const {
      return isEmpty(openstudio::WindowShadingControlFields::ShadingControlSequenceNumber);
    }

    void ShadingControl_Impl::resetShadingControlSequenceNumber() {
      OS_ASSERT(setString(openstudio::WindowShadingControlFields::ShadingControlSequenceNumber, ""));
    }

    std::string ShadingControl_Impl::shadingControlType() const {
      const auto value = getString(openstudio::WindowShadingControlFields::ShadingControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ShadingControl_Impl::setShadingControlType(const std::string& shadingControlType) {
      return setString(openstudio::WindowShadingControlFields::ShadingControlType, shadingControlType);
    }

    bool ShadingControl_Impl::isShadingControlTypeDefaulted() const {
      return isEmpty(openstudio::WindowShadingControlFields::ShadingControlType);
    }

    void ShadingControl_Impl::resetShadingControlType() {
      OS_ASSERT(setString(openstudio::WindowShadingControlFields::ShadingControlType, ""));
    }

    boost::optional<double> ShadingControl_Impl::setpoint() const {
      return getDouble(openstudio::WindowShadingControlFields::Setpoint, true);
    }

    bool ShadingControl_Impl::setSetpoint(double setpoint) {
      return setDouble(openstudio::WindowShadingControlFields::Setpoint, setpoint);
    }

    bool ShadingControl_Impl::isSetpointDefaulted() const {
      return isEmpty(openstudio::WindowShadingControlFields::Setpoint);
    }

    void ShadingControl_Impl::resetSetpoint() {
      OS_ASSERT(setString(openstudio::WindowShadingControlFields::Setpoint, ""));
    }

    bool ShadingControl_Impl::glareControlIsActive() const {
      return getBooleanFieldValue(*this, openstudio::WindowShadingControlFields::GlareControlIsActive);
    }

    bool ShadingControl_Impl::setGlareControlIsActive(bool glareControlIsActive) {
      const bool result = setBooleanFieldValue(*this, openstudio::WindowShadingControlFields::GlareControlIsActive, glareControlIsActive);
      OS_ASSERT(result);
      return result;
    }

    void ShadingControl_Impl::resetGlareControlIsActive() {
      OS_ASSERT(setString(openstudio::WindowShadingControlFields::GlareControlIsActive, ""));
    }

    std::string ShadingControl_Impl::typeofSlatAngleControlforBlinds() const {
      const auto value = getString(openstudio::WindowShadingControlFields::TypeofSlatAngleControlforBlinds, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ShadingControl_Impl::setTypeofSlatAngleControlforBlinds(const std::string& typeofSlatAngleControlforBlinds) {
      return setString(openstudio::WindowShadingControlFields::TypeofSlatAngleControlforBlinds, typeofSlatAngleControlforBlinds);
    }

    bool ShadingControl_Impl::isTypeofSlatAngleControlforBlindsDefaulted() const {
      return isEmpty(openstudio::WindowShadingControlFields::TypeofSlatAngleControlforBlinds);
    }

    void ShadingControl_Impl::resetTypeofSlatAngleControlforBlinds() {
      OS_ASSERT(setString(openstudio::WindowShadingControlFields::TypeofSlatAngleControlforBlinds, ""));
    }

    boost::optional<double> ShadingControl_Impl::setpoint2() const {
      return getDouble(openstudio::WindowShadingControlFields::Setpoint2, true);
    }

    bool ShadingControl_Impl::setSetpoint2(double setpoint2) {
      return setDouble(openstudio::WindowShadingControlFields::Setpoint2, setpoint2);
    }

    std::string ShadingControl_Impl::multipleSurfaceControlType() const {
      const auto value = getString(openstudio::WindowShadingControlFields::MultipleSurfaceControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ShadingControl_Impl::setMultipleSurfaceControlType(const std::string& multipleSurfaceControlType) {
      return setString(openstudio::WindowShadingControlFields::MultipleSurfaceControlType, multipleSurfaceControlType);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
