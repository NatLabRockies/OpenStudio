/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ResourceObject/WindowPropertyFrameAndDivider.hpp"
#include "ResourceObject/WindowPropertyFrameAndDivider_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_WindowProperty_FrameAndDivider_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace detail {

    double WindowPropertyFrameAndDivider_Impl::frameWidth() const {
      auto value = getDouble(OS_WindowProperty_FrameAndDividerFields::FrameWidth, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool WindowPropertyFrameAndDivider_Impl::isFrameWidthDefaulted() const {
      return isEmpty(OS_WindowProperty_FrameAndDividerFields::FrameWidth);
    }

    bool WindowPropertyFrameAndDivider_Impl::setFrameWidth(double frameWidth) {
      return setDouble(OS_WindowProperty_FrameAndDividerFields::FrameWidth, frameWidth);
    }

    void WindowPropertyFrameAndDivider_Impl::resetFrameWidth() {
      OS_ASSERT(setString(OS_WindowProperty_FrameAndDividerFields::FrameWidth, ""));
    }

    double WindowPropertyFrameAndDivider_Impl::frameOutsideProjection() const {
      auto value = getDouble(OS_WindowProperty_FrameAndDividerFields::FrameOutsideProjection, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool WindowPropertyFrameAndDivider_Impl::isFrameOutsideProjectionDefaulted() const {
      return isEmpty(OS_WindowProperty_FrameAndDividerFields::FrameOutsideProjection);
    }

    bool WindowPropertyFrameAndDivider_Impl::setFrameOutsideProjection(double frameOutsideProjection) {
      return setDouble(OS_WindowProperty_FrameAndDividerFields::FrameOutsideProjection, frameOutsideProjection);
    }

    void WindowPropertyFrameAndDivider_Impl::resetFrameOutsideProjection() {
      OS_ASSERT(setString(OS_WindowProperty_FrameAndDividerFields::FrameOutsideProjection, ""));
    }

    double WindowPropertyFrameAndDivider_Impl::frameInsideProjection() const {
      auto value = getDouble(OS_WindowProperty_FrameAndDividerFields::FrameInsideProjection, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool WindowPropertyFrameAndDivider_Impl::isFrameInsideProjectionDefaulted() const {
      return isEmpty(OS_WindowProperty_FrameAndDividerFields::FrameInsideProjection);
    }

    bool WindowPropertyFrameAndDivider_Impl::setFrameInsideProjection(double frameInsideProjection) {
      return setDouble(OS_WindowProperty_FrameAndDividerFields::FrameInsideProjection, frameInsideProjection);
    }

    void WindowPropertyFrameAndDivider_Impl::resetFrameInsideProjection() {
      OS_ASSERT(setString(OS_WindowProperty_FrameAndDividerFields::FrameInsideProjection, ""));
    }

    double WindowPropertyFrameAndDivider_Impl::frameConductance() const {
      auto value = getDouble(OS_WindowProperty_FrameAndDividerFields::FrameConductance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool WindowPropertyFrameAndDivider_Impl::isFrameConductanceDefaulted() const {
      return isEmpty(OS_WindowProperty_FrameAndDividerFields::FrameConductance);
    }

    bool WindowPropertyFrameAndDivider_Impl::setFrameConductance(double frameConductance) {
      return setDouble(OS_WindowProperty_FrameAndDividerFields::FrameConductance, frameConductance);
    }

    void WindowPropertyFrameAndDivider_Impl::resetFrameConductance() {
      OS_ASSERT(setString(OS_WindowProperty_FrameAndDividerFields::FrameConductance, ""));
    }

    double WindowPropertyFrameAndDivider_Impl::ratioOfFrameEdgeGlassConductanceToCenterOfGlassConductance() const {
      auto value = getDouble(OS_WindowProperty_FrameAndDividerFields::RatioofFrameEdgeGlassConductancetoCenterOfGlassConductance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool WindowPropertyFrameAndDivider_Impl::isRatioOfFrameEdgeGlassConductanceToCenterOfGlassConductanceDefaulted() const {
      return isEmpty(OS_WindowProperty_FrameAndDividerFields::RatioofFrameEdgeGlassConductancetoCenterOfGlassConductance);
    }

    bool WindowPropertyFrameAndDivider_Impl::setRatioOfFrameEdgeGlassConductanceToCenterOfGlassConductance(
      double ratioOfFrameEdgeGlassConductanceToCenterOfGlassConductance) {
      return setDouble(OS_WindowProperty_FrameAndDividerFields::RatioofFrameEdgeGlassConductancetoCenterOfGlassConductance,
                       ratioOfFrameEdgeGlassConductanceToCenterOfGlassConductance);
    }

    void WindowPropertyFrameAndDivider_Impl::resetRatioOfFrameEdgeGlassConductanceToCenterOfGlassConductance() {
      OS_ASSERT(setString(OS_WindowProperty_FrameAndDividerFields::RatioofFrameEdgeGlassConductancetoCenterOfGlassConductance, ""));
    }

    double WindowPropertyFrameAndDivider_Impl::frameSolarAbsorptance() const {
      auto value = getDouble(OS_WindowProperty_FrameAndDividerFields::FrameSolarAbsorptance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool WindowPropertyFrameAndDivider_Impl::isFrameSolarAbsorptanceDefaulted() const {
      return isEmpty(OS_WindowProperty_FrameAndDividerFields::FrameSolarAbsorptance);
    }

    bool WindowPropertyFrameAndDivider_Impl::setFrameSolarAbsorptance(double frameSolarAbsorptance) {
      return setDouble(OS_WindowProperty_FrameAndDividerFields::FrameSolarAbsorptance, frameSolarAbsorptance);
    }

    void WindowPropertyFrameAndDivider_Impl::resetFrameSolarAbsorptance() {
      OS_ASSERT(setString(OS_WindowProperty_FrameAndDividerFields::FrameSolarAbsorptance, ""));
    }

    double WindowPropertyFrameAndDivider_Impl::frameVisibleAbsorptance() const {
      auto value = getDouble(OS_WindowProperty_FrameAndDividerFields::FrameVisibleAbsorptance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool WindowPropertyFrameAndDivider_Impl::isFrameVisibleAbsorptanceDefaulted() const {
      return isEmpty(OS_WindowProperty_FrameAndDividerFields::FrameVisibleAbsorptance);
    }

    bool WindowPropertyFrameAndDivider_Impl::setFrameVisibleAbsorptance(double frameVisibleAbsorptance) {
      return setDouble(OS_WindowProperty_FrameAndDividerFields::FrameVisibleAbsorptance, frameVisibleAbsorptance);
    }

    void WindowPropertyFrameAndDivider_Impl::resetFrameVisibleAbsorptance() {
      OS_ASSERT(setString(OS_WindowProperty_FrameAndDividerFields::FrameVisibleAbsorptance, ""));
    }

    double WindowPropertyFrameAndDivider_Impl::frameThermalHemisphericalEmissivity() const {
      auto value = getDouble(OS_WindowProperty_FrameAndDividerFields::FrameThermalHemisphericalEmissivity, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool WindowPropertyFrameAndDivider_Impl::isFrameThermalHemisphericalEmissivityDefaulted() const {
      return isEmpty(OS_WindowProperty_FrameAndDividerFields::FrameThermalHemisphericalEmissivity);
    }

    bool WindowPropertyFrameAndDivider_Impl::setFrameThermalHemisphericalEmissivity(double frameThermalHemisphericalEmissivity) {
      return setDouble(OS_WindowProperty_FrameAndDividerFields::FrameThermalHemisphericalEmissivity, frameThermalHemisphericalEmissivity);
    }

    void WindowPropertyFrameAndDivider_Impl::resetFrameThermalHemisphericalEmissivity() {
      OS_ASSERT(setString(OS_WindowProperty_FrameAndDividerFields::FrameThermalHemisphericalEmissivity, ""));
    }

    std::string WindowPropertyFrameAndDivider_Impl::dividerType() const {
      auto value = getString(OS_WindowProperty_FrameAndDividerFields::DividerType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool WindowPropertyFrameAndDivider_Impl::isDividerTypeDefaulted() const {
      return isEmpty(OS_WindowProperty_FrameAndDividerFields::DividerType);
    }

    bool WindowPropertyFrameAndDivider_Impl::setDividerType(const std::string& dividerType) {
      return setString(OS_WindowProperty_FrameAndDividerFields::DividerType, dividerType);
    }

    void WindowPropertyFrameAndDivider_Impl::resetDividerType() {
      OS_ASSERT(setString(OS_WindowProperty_FrameAndDividerFields::DividerType, ""));
    }

    double WindowPropertyFrameAndDivider_Impl::dividerWidth() const {
      auto value = getDouble(OS_WindowProperty_FrameAndDividerFields::DividerWidth, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool WindowPropertyFrameAndDivider_Impl::isDividerWidthDefaulted() const {
      return isEmpty(OS_WindowProperty_FrameAndDividerFields::DividerWidth);
    }

    bool WindowPropertyFrameAndDivider_Impl::setDividerWidth(double dividerWidth) {
      return setDouble(OS_WindowProperty_FrameAndDividerFields::DividerWidth, dividerWidth);
    }

    void WindowPropertyFrameAndDivider_Impl::resetDividerWidth() {
      OS_ASSERT(setString(OS_WindowProperty_FrameAndDividerFields::DividerWidth, ""));
    }

    int WindowPropertyFrameAndDivider_Impl::numberOfHorizontalDividers() const {
      auto value = getInt(OS_WindowProperty_FrameAndDividerFields::NumberofHorizontalDividers, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool WindowPropertyFrameAndDivider_Impl::isNumberOfHorizontalDividersDefaulted() const {
      return isEmpty(OS_WindowProperty_FrameAndDividerFields::NumberofHorizontalDividers);
    }

    bool WindowPropertyFrameAndDivider_Impl::setNumberOfHorizontalDividers(int numberOfHorizontalDividers) {
      return setInt(OS_WindowProperty_FrameAndDividerFields::NumberofHorizontalDividers, numberOfHorizontalDividers);
    }

    void WindowPropertyFrameAndDivider_Impl::resetNumberOfHorizontalDividers() {
      OS_ASSERT(setString(OS_WindowProperty_FrameAndDividerFields::NumberofHorizontalDividers, ""));
    }

    int WindowPropertyFrameAndDivider_Impl::numberOfVerticalDividers() const {
      auto value = getInt(OS_WindowProperty_FrameAndDividerFields::NumberofVerticalDividers, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool WindowPropertyFrameAndDivider_Impl::isNumberOfVerticalDividersDefaulted() const {
      return isEmpty(OS_WindowProperty_FrameAndDividerFields::NumberofVerticalDividers);
    }

    bool WindowPropertyFrameAndDivider_Impl::setNumberOfVerticalDividers(int numberOfVerticalDividers) {
      return setInt(OS_WindowProperty_FrameAndDividerFields::NumberofVerticalDividers, numberOfVerticalDividers);
    }

    void WindowPropertyFrameAndDivider_Impl::resetNumberOfVerticalDividers() {
      OS_ASSERT(setString(OS_WindowProperty_FrameAndDividerFields::NumberofVerticalDividers, ""));
    }

    double WindowPropertyFrameAndDivider_Impl::dividerOutsideProjection() const {
      auto value = getDouble(OS_WindowProperty_FrameAndDividerFields::DividerOutsideProjection, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool WindowPropertyFrameAndDivider_Impl::isDividerOutsideProjectionDefaulted() const {
      return isEmpty(OS_WindowProperty_FrameAndDividerFields::DividerOutsideProjection);
    }

    bool WindowPropertyFrameAndDivider_Impl::setDividerOutsideProjection(double dividerOutsideProjection) {
      return setDouble(OS_WindowProperty_FrameAndDividerFields::DividerOutsideProjection, dividerOutsideProjection);
    }

    void WindowPropertyFrameAndDivider_Impl::resetDividerOutsideProjection() {
      OS_ASSERT(setString(OS_WindowProperty_FrameAndDividerFields::DividerOutsideProjection, ""));
    }

    double WindowPropertyFrameAndDivider_Impl::dividerInsideProjection() const {
      auto value = getDouble(OS_WindowProperty_FrameAndDividerFields::DividerInsideProjection, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool WindowPropertyFrameAndDivider_Impl::isDividerInsideProjectionDefaulted() const {
      return isEmpty(OS_WindowProperty_FrameAndDividerFields::DividerInsideProjection);
    }

    bool WindowPropertyFrameAndDivider_Impl::setDividerInsideProjection(double dividerInsideProjection) {
      return setDouble(OS_WindowProperty_FrameAndDividerFields::DividerInsideProjection, dividerInsideProjection);
    }

    void WindowPropertyFrameAndDivider_Impl::resetDividerInsideProjection() {
      OS_ASSERT(setString(OS_WindowProperty_FrameAndDividerFields::DividerInsideProjection, ""));
    }

    double WindowPropertyFrameAndDivider_Impl::dividerConductance() const {
      auto value = getDouble(OS_WindowProperty_FrameAndDividerFields::DividerConductance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool WindowPropertyFrameAndDivider_Impl::isDividerConductanceDefaulted() const {
      return isEmpty(OS_WindowProperty_FrameAndDividerFields::DividerConductance);
    }

    bool WindowPropertyFrameAndDivider_Impl::setDividerConductance(double dividerConductance) {
      return setDouble(OS_WindowProperty_FrameAndDividerFields::DividerConductance, dividerConductance);
    }

    void WindowPropertyFrameAndDivider_Impl::resetDividerConductance() {
      OS_ASSERT(setString(OS_WindowProperty_FrameAndDividerFields::DividerConductance, ""));
    }

    double WindowPropertyFrameAndDivider_Impl::ratioOfDividerEdgeGlassConductanceToCenterOfGlassConductance() const {
      auto value = getDouble(OS_WindowProperty_FrameAndDividerFields::RatioofDividerEdgeGlassConductancetoCenterOfGlassConductance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool WindowPropertyFrameAndDivider_Impl::isRatioOfDividerEdgeGlassConductanceToCenterOfGlassConductanceDefaulted() const {
      return isEmpty(OS_WindowProperty_FrameAndDividerFields::RatioofDividerEdgeGlassConductancetoCenterOfGlassConductance);
    }

    bool WindowPropertyFrameAndDivider_Impl::setRatioOfDividerEdgeGlassConductanceToCenterOfGlassConductance(
      double ratioOfDividerEdgeGlassConductanceToCenterOfGlassConductance) {
      return setDouble(OS_WindowProperty_FrameAndDividerFields::RatioofDividerEdgeGlassConductancetoCenterOfGlassConductance,
                       ratioOfDividerEdgeGlassConductanceToCenterOfGlassConductance);
    }

    void WindowPropertyFrameAndDivider_Impl::resetRatioOfDividerEdgeGlassConductanceToCenterOfGlassConductance() {
      OS_ASSERT(setString(OS_WindowProperty_FrameAndDividerFields::RatioofDividerEdgeGlassConductancetoCenterOfGlassConductance, ""));
    }

    double WindowPropertyFrameAndDivider_Impl::dividerSolarAbsorptance() const {
      auto value = getDouble(OS_WindowProperty_FrameAndDividerFields::DividerSolarAbsorptance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool WindowPropertyFrameAndDivider_Impl::isDividerSolarAbsorptanceDefaulted() const {
      return isEmpty(OS_WindowProperty_FrameAndDividerFields::DividerSolarAbsorptance);
    }

    bool WindowPropertyFrameAndDivider_Impl::setDividerSolarAbsorptance(double dividerSolarAbsorptance) {
      return setDouble(OS_WindowProperty_FrameAndDividerFields::DividerSolarAbsorptance, dividerSolarAbsorptance);
    }

    void WindowPropertyFrameAndDivider_Impl::resetDividerSolarAbsorptance() {
      OS_ASSERT(setString(OS_WindowProperty_FrameAndDividerFields::DividerSolarAbsorptance, ""));
    }

    double WindowPropertyFrameAndDivider_Impl::dividerVisibleAbsorptance() const {
      auto value = getDouble(OS_WindowProperty_FrameAndDividerFields::DividerVisibleAbsorptance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool WindowPropertyFrameAndDivider_Impl::isDividerVisibleAbsorptanceDefaulted() const {
      return isEmpty(OS_WindowProperty_FrameAndDividerFields::DividerVisibleAbsorptance);
    }

    bool WindowPropertyFrameAndDivider_Impl::setDividerVisibleAbsorptance(double dividerVisibleAbsorptance) {
      return setDouble(OS_WindowProperty_FrameAndDividerFields::DividerVisibleAbsorptance, dividerVisibleAbsorptance);
    }

    void WindowPropertyFrameAndDivider_Impl::resetDividerVisibleAbsorptance() {
      OS_ASSERT(setString(OS_WindowProperty_FrameAndDividerFields::DividerVisibleAbsorptance, ""));
    }

    double WindowPropertyFrameAndDivider_Impl::dividerThermalHemisphericalEmissivity() const {
      auto value = getDouble(OS_WindowProperty_FrameAndDividerFields::DividerThermalHemisphericalEmissivity, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool WindowPropertyFrameAndDivider_Impl::isDividerThermalHemisphericalEmissivityDefaulted() const {
      return isEmpty(OS_WindowProperty_FrameAndDividerFields::DividerThermalHemisphericalEmissivity);
    }

    bool WindowPropertyFrameAndDivider_Impl::setDividerThermalHemisphericalEmissivity(double dividerThermalHemisphericalEmissivity) {
      return setDouble(OS_WindowProperty_FrameAndDividerFields::DividerThermalHemisphericalEmissivity, dividerThermalHemisphericalEmissivity);
    }

    void WindowPropertyFrameAndDivider_Impl::resetDividerThermalHemisphericalEmissivity() {
      OS_ASSERT(setString(OS_WindowProperty_FrameAndDividerFields::DividerThermalHemisphericalEmissivity, ""));
    }

    double WindowPropertyFrameAndDivider_Impl::outsideRevealDepth() const {
      auto value = getDouble(OS_WindowProperty_FrameAndDividerFields::OutsideRevealDepth, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool WindowPropertyFrameAndDivider_Impl::isOutsideRevealDepthDefaulted() const {
      return isEmpty(OS_WindowProperty_FrameAndDividerFields::OutsideRevealDepth);
    }

    bool WindowPropertyFrameAndDivider_Impl::setOutsideRevealDepth(double outsideRevealDepth) {
      return setDouble(OS_WindowProperty_FrameAndDividerFields::OutsideRevealDepth, outsideRevealDepth);
    }

    void WindowPropertyFrameAndDivider_Impl::resetOutsideRevealDepth() {
      OS_ASSERT(setString(OS_WindowProperty_FrameAndDividerFields::OutsideRevealDepth, ""));
    }

    double WindowPropertyFrameAndDivider_Impl::outsideRevealSolarAbsorptance() const {
      auto value = getDouble(OS_WindowProperty_FrameAndDividerFields::OutsideRevealSolarAbsorptance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool WindowPropertyFrameAndDivider_Impl::isOutsideRevealSolarAbsorptanceDefaulted() const {
      return isEmpty(OS_WindowProperty_FrameAndDividerFields::OutsideRevealSolarAbsorptance);
    }

    bool WindowPropertyFrameAndDivider_Impl::setOutsideRevealSolarAbsorptance(double outsideRevealSolarAbsorptance) {
      return setDouble(OS_WindowProperty_FrameAndDividerFields::OutsideRevealSolarAbsorptance, outsideRevealSolarAbsorptance);
    }

    void WindowPropertyFrameAndDivider_Impl::resetOutsideRevealSolarAbsorptance() {
      OS_ASSERT(setString(OS_WindowProperty_FrameAndDividerFields::OutsideRevealSolarAbsorptance, ""));
    }

    double WindowPropertyFrameAndDivider_Impl::insideSillDepth() const {
      auto value = getDouble(OS_WindowProperty_FrameAndDividerFields::InsideSillDepth, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool WindowPropertyFrameAndDivider_Impl::isInsideSillDepthDefaulted() const {
      return isEmpty(OS_WindowProperty_FrameAndDividerFields::InsideSillDepth);
    }

    bool WindowPropertyFrameAndDivider_Impl::setInsideSillDepth(double insideSillDepth) {
      return setDouble(OS_WindowProperty_FrameAndDividerFields::InsideSillDepth, insideSillDepth);
    }

    void WindowPropertyFrameAndDivider_Impl::resetInsideSillDepth() {
      OS_ASSERT(setString(OS_WindowProperty_FrameAndDividerFields::InsideSillDepth, ""));
    }

    double WindowPropertyFrameAndDivider_Impl::insideSillSolarAbsorptance() const {
      auto value = getDouble(OS_WindowProperty_FrameAndDividerFields::InsideSillSolarAbsorptance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool WindowPropertyFrameAndDivider_Impl::isInsideSillSolarAbsorptanceDefaulted() const {
      return isEmpty(OS_WindowProperty_FrameAndDividerFields::InsideSillSolarAbsorptance);
    }

    bool WindowPropertyFrameAndDivider_Impl::setInsideSillSolarAbsorptance(double insideSillSolarAbsorptance) {
      return setDouble(OS_WindowProperty_FrameAndDividerFields::InsideSillSolarAbsorptance, insideSillSolarAbsorptance);
    }

    void WindowPropertyFrameAndDivider_Impl::resetInsideSillSolarAbsorptance() {
      OS_ASSERT(setString(OS_WindowProperty_FrameAndDividerFields::InsideSillSolarAbsorptance, ""));
    }

    double WindowPropertyFrameAndDivider_Impl::insideRevealDepth() const {
      auto value = getDouble(OS_WindowProperty_FrameAndDividerFields::InsideRevealDepth, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool WindowPropertyFrameAndDivider_Impl::isInsideRevealDepthDefaulted() const {
      return isEmpty(OS_WindowProperty_FrameAndDividerFields::InsideRevealDepth);
    }

    bool WindowPropertyFrameAndDivider_Impl::setInsideRevealDepth(double insideRevealDepth) {
      return setDouble(OS_WindowProperty_FrameAndDividerFields::InsideRevealDepth, insideRevealDepth);
    }

    void WindowPropertyFrameAndDivider_Impl::resetInsideRevealDepth() {
      OS_ASSERT(setString(OS_WindowProperty_FrameAndDividerFields::InsideRevealDepth, ""));
    }

    double WindowPropertyFrameAndDivider_Impl::insideRevealSolarAbsorptance() const {
      auto value = getDouble(OS_WindowProperty_FrameAndDividerFields::InsideRevealSolarAbsorptance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool WindowPropertyFrameAndDivider_Impl::isInsideRevealSolarAbsorptanceDefaulted() const {
      return isEmpty(OS_WindowProperty_FrameAndDividerFields::InsideRevealSolarAbsorptance);
    }

    bool WindowPropertyFrameAndDivider_Impl::setInsideRevealSolarAbsorptance(double insideRevealSolarAbsorptance) {
      return setDouble(OS_WindowProperty_FrameAndDividerFields::InsideRevealSolarAbsorptance, insideRevealSolarAbsorptance);
    }

    void WindowPropertyFrameAndDivider_Impl::resetInsideRevealSolarAbsorptance() {
      OS_ASSERT(setString(OS_WindowProperty_FrameAndDividerFields::InsideRevealSolarAbsorptance, ""));
    }

    std::string WindowPropertyFrameAndDivider_Impl::nfrcProductTypeforAssemblyCalculations() const {
      auto value = getString(OS_WindowProperty_FrameAndDividerFields::NFRCProductTypeforAssemblyCalculations, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool WindowPropertyFrameAndDivider_Impl::isNFRCProductTypeforAssemblyCalculationsDefaulted() const {
      return isEmpty(OS_WindowProperty_FrameAndDividerFields::NFRCProductTypeforAssemblyCalculations);
    }

    bool WindowPropertyFrameAndDivider_Impl::setNFRCProductTypeforAssemblyCalculations(const std::string& nfrcProductTypeforAssemblyCalculations) {
      return setString(OS_WindowProperty_FrameAndDividerFields::NFRCProductTypeforAssemblyCalculations, nfrcProductTypeforAssemblyCalculations);
    }

    void WindowPropertyFrameAndDivider_Impl::resetNFRCProductTypeforAssemblyCalculations() {
      OS_ASSERT(setString(OS_WindowProperty_FrameAndDividerFields::NFRCProductTypeforAssemblyCalculations, ""));
    }

  }  // namespace detail

  WindowPropertyFrameAndDivider::WindowPropertyFrameAndDivider(const Model& model)
    : ModelObject(WindowPropertyFrameAndDivider::iddObjectType(), model) {}

  WindowPropertyFrameAndDivider::WindowPropertyFrameAndDivider(std::shared_ptr<detail::WindowPropertyFrameAndDivider_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType WindowPropertyFrameAndDivider::iddObjectType() {
    return IddObjectType::WindowProperty_FrameAndDivider;
  }

  std::vector<std::string> WindowPropertyFrameAndDivider::dividerTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), OS_WindowProperty_FrameAndDividerFields::DividerType);
  }

  double WindowPropertyFrameAndDivider::frameWidth() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->frameWidth();
  }

  bool WindowPropertyFrameAndDivider::isFrameWidthDefaulted() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->isFrameWidthDefaulted();
  }

  bool WindowPropertyFrameAndDivider::setFrameWidth(double frameWidth) {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->setFrameWidth(frameWidth);
  }

  void WindowPropertyFrameAndDivider::resetFrameWidth() {
    getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->resetFrameWidth();
  }

  double WindowPropertyFrameAndDivider::frameOutsideProjection() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->frameOutsideProjection();
  }

  bool WindowPropertyFrameAndDivider::isFrameOutsideProjectionDefaulted() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->isFrameOutsideProjectionDefaulted();
  }

  bool WindowPropertyFrameAndDivider::setFrameOutsideProjection(double frameOutsideProjection) {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->setFrameOutsideProjection(frameOutsideProjection);
  }

  void WindowPropertyFrameAndDivider::resetFrameOutsideProjection() {
    getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->resetFrameOutsideProjection();
  }

  double WindowPropertyFrameAndDivider::frameInsideProjection() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->frameInsideProjection();
  }

  bool WindowPropertyFrameAndDivider::isFrameInsideProjectionDefaulted() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->isFrameInsideProjectionDefaulted();
  }

  bool WindowPropertyFrameAndDivider::setFrameInsideProjection(double frameInsideProjection) {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->setFrameInsideProjection(frameInsideProjection);
  }

  void WindowPropertyFrameAndDivider::resetFrameInsideProjection() {
    getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->resetFrameInsideProjection();
  }

  double WindowPropertyFrameAndDivider::frameConductance() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->frameConductance();
  }

  bool WindowPropertyFrameAndDivider::isFrameConductanceDefaulted() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->isFrameConductanceDefaulted();
  }

  bool WindowPropertyFrameAndDivider::setFrameConductance(double frameConductance) {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->setFrameConductance(frameConductance);
  }

  void WindowPropertyFrameAndDivider::resetFrameConductance() {
    getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->resetFrameConductance();
  }

  double WindowPropertyFrameAndDivider::ratioOfFrameEdgeGlassConductanceToCenterOfGlassConductance() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->ratioOfFrameEdgeGlassConductanceToCenterOfGlassConductance();
  }

  bool WindowPropertyFrameAndDivider::isRatioOfFrameEdgeGlassConductanceToCenterOfGlassConductanceDefaulted() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->isRatioOfFrameEdgeGlassConductanceToCenterOfGlassConductanceDefaulted();
  }

  bool WindowPropertyFrameAndDivider::setRatioOfFrameEdgeGlassConductanceToCenterOfGlassConductance(
    double ratioOfFrameEdgeGlassConductanceToCenterOfGlassConductance) {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->setRatioOfFrameEdgeGlassConductanceToCenterOfGlassConductance(
      ratioOfFrameEdgeGlassConductanceToCenterOfGlassConductance);
  }

  void WindowPropertyFrameAndDivider::resetRatioOfFrameEdgeGlassConductanceToCenterOfGlassConductance() {
    getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->resetRatioOfFrameEdgeGlassConductanceToCenterOfGlassConductance();
  }

  double WindowPropertyFrameAndDivider::frameSolarAbsorptance() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->frameSolarAbsorptance();
  }

  bool WindowPropertyFrameAndDivider::isFrameSolarAbsorptanceDefaulted() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->isFrameSolarAbsorptanceDefaulted();
  }

  bool WindowPropertyFrameAndDivider::setFrameSolarAbsorptance(double frameSolarAbsorptance) {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->setFrameSolarAbsorptance(frameSolarAbsorptance);
  }

  void WindowPropertyFrameAndDivider::resetFrameSolarAbsorptance() {
    getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->resetFrameSolarAbsorptance();
  }

  double WindowPropertyFrameAndDivider::frameVisibleAbsorptance() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->frameVisibleAbsorptance();
  }

  bool WindowPropertyFrameAndDivider::isFrameVisibleAbsorptanceDefaulted() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->isFrameVisibleAbsorptanceDefaulted();
  }

  bool WindowPropertyFrameAndDivider::setFrameVisibleAbsorptance(double frameVisibleAbsorptance) {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->setFrameVisibleAbsorptance(frameVisibleAbsorptance);
  }

  void WindowPropertyFrameAndDivider::resetFrameVisibleAbsorptance() {
    getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->resetFrameVisibleAbsorptance();
  }

  double WindowPropertyFrameAndDivider::frameThermalHemisphericalEmissivity() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->frameThermalHemisphericalEmissivity();
  }

  bool WindowPropertyFrameAndDivider::isFrameThermalHemisphericalEmissivityDefaulted() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->isFrameThermalHemisphericalEmissivityDefaulted();
  }

  bool WindowPropertyFrameAndDivider::setFrameThermalHemisphericalEmissivity(double frameThermalHemisphericalEmissivity) {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->setFrameThermalHemisphericalEmissivity(frameThermalHemisphericalEmissivity);
  }

  void WindowPropertyFrameAndDivider::resetFrameThermalHemisphericalEmissivity() {
    getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->resetFrameThermalHemisphericalEmissivity();
  }

  std::string WindowPropertyFrameAndDivider::dividerType() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->dividerType();
  }

  bool WindowPropertyFrameAndDivider::isDividerTypeDefaulted() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->isDividerTypeDefaulted();
  }

  bool WindowPropertyFrameAndDivider::setDividerType(const std::string& dividerType) {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->setDividerType(dividerType);
  }

  void WindowPropertyFrameAndDivider::resetDividerType() {
    getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->resetDividerType();
  }

  double WindowPropertyFrameAndDivider::dividerWidth() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->dividerWidth();
  }

  bool WindowPropertyFrameAndDivider::isDividerWidthDefaulted() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->isDividerWidthDefaulted();
  }

  bool WindowPropertyFrameAndDivider::setDividerWidth(double dividerWidth) {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->setDividerWidth(dividerWidth);
  }

  void WindowPropertyFrameAndDivider::resetDividerWidth() {
    getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->resetDividerWidth();
  }

  int WindowPropertyFrameAndDivider::numberOfHorizontalDividers() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->numberOfHorizontalDividers();
  }

  bool WindowPropertyFrameAndDivider::isNumberOfHorizontalDividersDefaulted() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->isNumberOfHorizontalDividersDefaulted();
  }

  bool WindowPropertyFrameAndDivider::setNumberOfHorizontalDividers(int numberOfHorizontalDividers) {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->setNumberOfHorizontalDividers(numberOfHorizontalDividers);
  }

  void WindowPropertyFrameAndDivider::resetNumberOfHorizontalDividers() {
    getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->resetNumberOfHorizontalDividers();
  }

  int WindowPropertyFrameAndDivider::numberOfVerticalDividers() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->numberOfVerticalDividers();
  }

  bool WindowPropertyFrameAndDivider::isNumberOfVerticalDividersDefaulted() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->isNumberOfVerticalDividersDefaulted();
  }

  bool WindowPropertyFrameAndDivider::setNumberOfVerticalDividers(int numberOfVerticalDividers) {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->setNumberOfVerticalDividers(numberOfVerticalDividers);
  }

  void WindowPropertyFrameAndDivider::resetNumberOfVerticalDividers() {
    getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->resetNumberOfVerticalDividers();
  }

  double WindowPropertyFrameAndDivider::dividerOutsideProjection() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->dividerOutsideProjection();
  }

  bool WindowPropertyFrameAndDivider::isDividerOutsideProjectionDefaulted() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->isDividerOutsideProjectionDefaulted();
  }

  bool WindowPropertyFrameAndDivider::setDividerOutsideProjection(double dividerOutsideProjection) {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->setDividerOutsideProjection(dividerOutsideProjection);
  }

  void WindowPropertyFrameAndDivider::resetDividerOutsideProjection() {
    getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->resetDividerOutsideProjection();
  }

  double WindowPropertyFrameAndDivider::dividerInsideProjection() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->dividerInsideProjection();
  }

  bool WindowPropertyFrameAndDivider::isDividerInsideProjectionDefaulted() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->isDividerInsideProjectionDefaulted();
  }

  bool WindowPropertyFrameAndDivider::setDividerInsideProjection(double dividerInsideProjection) {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->setDividerInsideProjection(dividerInsideProjection);
  }

  void WindowPropertyFrameAndDivider::resetDividerInsideProjection() {
    getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->resetDividerInsideProjection();
  }

  double WindowPropertyFrameAndDivider::dividerConductance() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->dividerConductance();
  }

  bool WindowPropertyFrameAndDivider::isDividerConductanceDefaulted() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->isDividerConductanceDefaulted();
  }

  bool WindowPropertyFrameAndDivider::setDividerConductance(double dividerConductance) {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->setDividerConductance(dividerConductance);
  }

  void WindowPropertyFrameAndDivider::resetDividerConductance() {
    getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->resetDividerConductance();
  }

  double WindowPropertyFrameAndDivider::ratioOfDividerEdgeGlassConductanceToCenterOfGlassConductance() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->ratioOfDividerEdgeGlassConductanceToCenterOfGlassConductance();
  }

  bool WindowPropertyFrameAndDivider::isRatioOfDividerEdgeGlassConductanceToCenterOfGlassConductanceDefaulted() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->isRatioOfDividerEdgeGlassConductanceToCenterOfGlassConductanceDefaulted();
  }

  bool WindowPropertyFrameAndDivider::setRatioOfDividerEdgeGlassConductanceToCenterOfGlassConductance(
    double ratioOfDividerEdgeGlassConductanceToCenterOfGlassConductance) {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->setRatioOfDividerEdgeGlassConductanceToCenterOfGlassConductance(
      ratioOfDividerEdgeGlassConductanceToCenterOfGlassConductance);
  }

  void WindowPropertyFrameAndDivider::resetRatioOfDividerEdgeGlassConductanceToCenterOfGlassConductance() {
    getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->resetRatioOfDividerEdgeGlassConductanceToCenterOfGlassConductance();
  }

  double WindowPropertyFrameAndDivider::dividerSolarAbsorptance() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->dividerSolarAbsorptance();
  }

  bool WindowPropertyFrameAndDivider::isDividerSolarAbsorptanceDefaulted() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->isDividerSolarAbsorptanceDefaulted();
  }

  bool WindowPropertyFrameAndDivider::setDividerSolarAbsorptance(double dividerSolarAbsorptance) {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->setDividerSolarAbsorptance(dividerSolarAbsorptance);
  }

  void WindowPropertyFrameAndDivider::resetDividerSolarAbsorptance() {
    getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->resetDividerSolarAbsorptance();
  }

  double WindowPropertyFrameAndDivider::dividerVisibleAbsorptance() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->dividerVisibleAbsorptance();
  }

  bool WindowPropertyFrameAndDivider::isDividerVisibleAbsorptanceDefaulted() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->isDividerVisibleAbsorptanceDefaulted();
  }

  bool WindowPropertyFrameAndDivider::setDividerVisibleAbsorptance(double dividerVisibleAbsorptance) {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->setDividerVisibleAbsorptance(dividerVisibleAbsorptance);
  }

  void WindowPropertyFrameAndDivider::resetDividerVisibleAbsorptance() {
    getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->resetDividerVisibleAbsorptance();
  }

  double WindowPropertyFrameAndDivider::dividerThermalHemisphericalEmissivity() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->dividerThermalHemisphericalEmissivity();
  }

  bool WindowPropertyFrameAndDivider::isDividerThermalHemisphericalEmissivityDefaulted() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->isDividerThermalHemisphericalEmissivityDefaulted();
  }

  bool WindowPropertyFrameAndDivider::setDividerThermalHemisphericalEmissivity(double dividerThermalHemisphericalEmissivity) {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->setDividerThermalHemisphericalEmissivity(dividerThermalHemisphericalEmissivity);
  }

  void WindowPropertyFrameAndDivider::resetDividerThermalHemisphericalEmissivity() {
    getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->resetDividerThermalHemisphericalEmissivity();
  }

  double WindowPropertyFrameAndDivider::outsideRevealDepth() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->outsideRevealDepth();
  }

  bool WindowPropertyFrameAndDivider::isOutsideRevealDepthDefaulted() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->isOutsideRevealDepthDefaulted();
  }

  bool WindowPropertyFrameAndDivider::setOutsideRevealDepth(double outsideRevealDepth) {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->setOutsideRevealDepth(outsideRevealDepth);
  }

  void WindowPropertyFrameAndDivider::resetOutsideRevealDepth() {
    getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->resetOutsideRevealDepth();
  }

  double WindowPropertyFrameAndDivider::outsideRevealSolarAbsorptance() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->outsideRevealSolarAbsorptance();
  }

  bool WindowPropertyFrameAndDivider::isOutsideRevealSolarAbsorptanceDefaulted() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->isOutsideRevealSolarAbsorptanceDefaulted();
  }

  bool WindowPropertyFrameAndDivider::setOutsideRevealSolarAbsorptance(double outsideRevealSolarAbsorptance) {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->setOutsideRevealSolarAbsorptance(outsideRevealSolarAbsorptance);
  }

  void WindowPropertyFrameAndDivider::resetOutsideRevealSolarAbsorptance() {
    getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->resetOutsideRevealSolarAbsorptance();
  }

  double WindowPropertyFrameAndDivider::insideSillDepth() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->insideSillDepth();
  }

  bool WindowPropertyFrameAndDivider::isInsideSillDepthDefaulted() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->isInsideSillDepthDefaulted();
  }

  bool WindowPropertyFrameAndDivider::setInsideSillDepth(double insideSillDepth) {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->setInsideSillDepth(insideSillDepth);
  }

  void WindowPropertyFrameAndDivider::resetInsideSillDepth() {
    getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->resetInsideSillDepth();
  }

  double WindowPropertyFrameAndDivider::insideSillSolarAbsorptance() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->insideSillSolarAbsorptance();
  }

  bool WindowPropertyFrameAndDivider::isInsideSillSolarAbsorptanceDefaulted() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->isInsideSillSolarAbsorptanceDefaulted();
  }

  bool WindowPropertyFrameAndDivider::setInsideSillSolarAbsorptance(double insideSillSolarAbsorptance) {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->setInsideSillSolarAbsorptance(insideSillSolarAbsorptance);
  }

  void WindowPropertyFrameAndDivider::resetInsideSillSolarAbsorptance() {
    getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->resetInsideSillSolarAbsorptance();
  }

  double WindowPropertyFrameAndDivider::insideRevealDepth() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->insideRevealDepth();
  }

  bool WindowPropertyFrameAndDivider::isInsideRevealDepthDefaulted() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->isInsideRevealDepthDefaulted();
  }

  bool WindowPropertyFrameAndDivider::setInsideRevealDepth(double insideRevealDepth) {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->setInsideRevealDepth(insideRevealDepth);
  }

  void WindowPropertyFrameAndDivider::resetInsideRevealDepth() {
    getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->resetInsideRevealDepth();
  }

  double WindowPropertyFrameAndDivider::insideRevealSolarAbsorptance() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->insideRevealSolarAbsorptance();
  }

  bool WindowPropertyFrameAndDivider::isInsideRevealSolarAbsorptanceDefaulted() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->isInsideRevealSolarAbsorptanceDefaulted();
  }

  bool WindowPropertyFrameAndDivider::setInsideRevealSolarAbsorptance(double insideRevealSolarAbsorptance) {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->setInsideRevealSolarAbsorptance(insideRevealSolarAbsorptance);
  }

  void WindowPropertyFrameAndDivider::resetInsideRevealSolarAbsorptance() {
    getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->resetInsideRevealSolarAbsorptance();
  }

  std::string WindowPropertyFrameAndDivider::nfrcProductTypeforAssemblyCalculations() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->nfrcProductTypeforAssemblyCalculations();
  }

  bool WindowPropertyFrameAndDivider::isNFRCProductTypeforAssemblyCalculationsDefaulted() const {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->isNFRCProductTypeforAssemblyCalculationsDefaulted();
  }

  bool WindowPropertyFrameAndDivider::setNFRCProductTypeforAssemblyCalculations(const std::string& nfrcProductTypeforAssemblyCalculations) {
    return getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->setNFRCProductTypeforAssemblyCalculations(nfrcProductTypeforAssemblyCalculations);
  }

  void WindowPropertyFrameAndDivider::resetNFRCProductTypeforAssemblyCalculations() {
    getImpl<detail::WindowPropertyFrameAndDivider_Impl>()->resetNFRCProductTypeforAssemblyCalculations();
  }

}  // namespace epmodel
}  // namespace openstudio
