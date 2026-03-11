/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WINDOWPROPERTYFRAMEANDDIVIDER_HPP
#define EPMODEL_WINDOWPROPERTYFRAMEANDDIVIDER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
  class WindowPropertyFrameAndDivider_Impl;
}

/** WindowPropertyFrameAndDivider is a ModelObject that wraps the OpenStudio IDD object 'OS:WindowProperty:FrameAndDivider'. */
class EPMODEL_API WindowPropertyFrameAndDivider : public ModelObject
{
 public:
  explicit WindowPropertyFrameAndDivider(const Model& model);

  virtual ~WindowPropertyFrameAndDivider() override = default;
  WindowPropertyFrameAndDivider(const WindowPropertyFrameAndDivider& other) = default;
  WindowPropertyFrameAndDivider(WindowPropertyFrameAndDivider&& other) = default;
  WindowPropertyFrameAndDivider& operator=(const WindowPropertyFrameAndDivider&) = default;
  WindowPropertyFrameAndDivider& operator=(WindowPropertyFrameAndDivider&&) = default;

  static IddObjectType iddObjectType();
  static std::vector<std::string> dividerTypeValues();

  // Schema Alignment Notes:
  // - API: Preserves the openstudio::model WindowPropertyFrameAndDivider scalar interface while living in the ResourceObject bucket.
  // - Field Mapping: Each getter/setter delegates to OS_WindowProperty_FrameAndDividerFields via WindowPropertyFrameAndDivider_Impl, with outsideRevealDepth feeding surface vertex offsets instead of a direct EnergyPlus field write.
  // - ForwardTranslator evidence: ForwardTranslateWindowPropertyFrameAndDivider.cpp writes the same scalars and records reveal geometry adjustments for sub-surface translation.
  // - TODO(parity): Surface-aligned reveal helpers remain to be introduced once the translator writes OutsideRevealDepth explicitly.

  double frameWidth() const;
  bool isFrameWidthDefaulted() const;
  bool setFrameWidth(double frameWidth);
  void resetFrameWidth();

  double frameOutsideProjection() const;
  bool isFrameOutsideProjectionDefaulted() const;
  bool setFrameOutsideProjection(double frameOutsideProjection);
  void resetFrameOutsideProjection();

  double frameInsideProjection() const;
  bool isFrameInsideProjectionDefaulted() const;
  bool setFrameInsideProjection(double frameInsideProjection);
  void resetFrameInsideProjection();

  double frameConductance() const;
  bool isFrameConductanceDefaulted() const;
  bool setFrameConductance(double frameConductance);
  void resetFrameConductance();

  double ratioOfFrameEdgeGlassConductanceToCenterOfGlassConductance() const;
  bool isRatioOfFrameEdgeGlassConductanceToCenterOfGlassConductanceDefaulted() const;
  bool setRatioOfFrameEdgeGlassConductanceToCenterOfGlassConductance(double ratioOfFrameEdgeGlassConductanceToCenterOfGlassConductance);
  void resetRatioOfFrameEdgeGlassConductanceToCenterOfGlassConductance();

  double frameSolarAbsorptance() const;
  bool isFrameSolarAbsorptanceDefaulted() const;
  bool setFrameSolarAbsorptance(double frameSolarAbsorptance);
  void resetFrameSolarAbsorptance();

  double frameVisibleAbsorptance() const;
  bool isFrameVisibleAbsorptanceDefaulted() const;
  bool setFrameVisibleAbsorptance(double frameVisibleAbsorptance);
  void resetFrameVisibleAbsorptance();

  double frameThermalHemisphericalEmissivity() const;
  bool isFrameThermalHemisphericalEmissivityDefaulted() const;
  bool setFrameThermalHemisphericalEmissivity(double frameThermalHemisphericalEmissivity);
  void resetFrameThermalHemisphericalEmissivity();

  std::string dividerType() const;
  bool isDividerTypeDefaulted() const;
  bool setDividerType(const std::string& dividerType);
  void resetDividerType();

  double dividerWidth() const;
  bool isDividerWidthDefaulted() const;
  bool setDividerWidth(double dividerWidth);
  void resetDividerWidth();

  int numberOfHorizontalDividers() const;
  bool isNumberOfHorizontalDividersDefaulted() const;
  bool setNumberOfHorizontalDividers(int numberOfHorizontalDividers);
  void resetNumberOfHorizontalDividers();

  int numberOfVerticalDividers() const;
  bool isNumberOfVerticalDividersDefaulted() const;
  bool setNumberOfVerticalDividers(int numberOfVerticalDividers);
  void resetNumberOfVerticalDividers();

  double dividerOutsideProjection() const;
  bool isDividerOutsideProjectionDefaulted() const;
  bool setDividerOutsideProjection(double dividerOutsideProjection);
  void resetDividerOutsideProjection();

  double dividerInsideProjection() const;
  bool isDividerInsideProjectionDefaulted() const;
  bool setDividerInsideProjection(double dividerInsideProjection);
  void resetDividerInsideProjection();

  double dividerConductance() const;
  bool isDividerConductanceDefaulted() const;
  bool setDividerConductance(double dividerConductance);
  void resetDividerConductance();

  double ratioOfDividerEdgeGlassConductanceToCenterOfGlassConductance() const;
  bool isRatioOfDividerEdgeGlassConductanceToCenterOfGlassConductanceDefaulted() const;
  bool setRatioOfDividerEdgeGlassConductanceToCenterOfGlassConductance(double ratioOfDividerEdgeGlassConductanceToCenterOfGlassConductance);
  void resetRatioOfDividerEdgeGlassConductanceToCenterOfGlassConductance();

  double dividerSolarAbsorptance() const;
  bool isDividerSolarAbsorptanceDefaulted() const;
  bool setDividerSolarAbsorptance(double dividerSolarAbsorptance);
  void resetDividerSolarAbsorptance();

  double dividerVisibleAbsorptance() const;
  bool isDividerVisibleAbsorptanceDefaulted() const;
  bool setDividerVisibleAbsorptance(double dividerVisibleAbsorptance);
  void resetDividerVisibleAbsorptance();

  double dividerThermalHemisphericalEmissivity() const;
  bool isDividerThermalHemisphericalEmissivityDefaulted() const;
  bool setDividerThermalHemisphericalEmissivity(double dividerThermalHemisphericalEmissivity);
  void resetDividerThermalHemisphericalEmissivity();

  double outsideRevealDepth() const;
  bool isOutsideRevealDepthDefaulted() const;
  bool setOutsideRevealDepth(double outsideRevealDepth);
  void resetOutsideRevealDepth();

  double outsideRevealSolarAbsorptance() const;
  bool isOutsideRevealSolarAbsorptanceDefaulted() const;
  bool setOutsideRevealSolarAbsorptance(double outsideRevealSolarAbsorptance);
  void resetOutsideRevealSolarAbsorptance();

  double insideSillDepth() const;
  bool isInsideSillDepthDefaulted() const;
  bool setInsideSillDepth(double insideSillDepth);
  void resetInsideSillDepth();

  double insideSillSolarAbsorptance() const;
  bool isInsideSillSolarAbsorptanceDefaulted() const;
  bool setInsideSillSolarAbsorptance(double insideSillSolarAbsorptance);
  void resetInsideSillSolarAbsorptance();

  double insideRevealDepth() const;
  bool isInsideRevealDepthDefaulted() const;
  bool setInsideRevealDepth(double insideRevealDepth);
  void resetInsideRevealDepth();

  double insideRevealSolarAbsorptance() const;
  bool isInsideRevealSolarAbsorptanceDefaulted() const;
  bool setInsideRevealSolarAbsorptance(double insideRevealSolarAbsorptance);
  void resetInsideRevealSolarAbsorptance();

  std::string nfrcProductTypeforAssemblyCalculations() const;
  bool isNFRCProductTypeforAssemblyCalculationsDefaulted() const;
  bool setNFRCProductTypeforAssemblyCalculations(const std::string& nfrcProductTypeforAssemblyCalculations);
  void resetNFRCProductTypeforAssemblyCalculations();

 protected:
  using ImplType = detail::WindowPropertyFrameAndDivider_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit WindowPropertyFrameAndDivider(std::shared_ptr<detail::WindowPropertyFrameAndDivider_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_WINDOWPROPERTYFRAMEANDDIVIDER_HPP
