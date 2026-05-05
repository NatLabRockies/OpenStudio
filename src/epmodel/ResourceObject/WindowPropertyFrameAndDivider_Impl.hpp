/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WINDOWPROPERTYFRAMEANDDIVIDER_IMPL_HPP
#define EPMODEL_WINDOWPROPERTYFRAMEANDDIVIDER_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API WindowPropertyFrameAndDivider_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~WindowPropertyFrameAndDivider_Impl() override = default;

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
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_WINDOWPROPERTYFRAMEANDDIVIDER_IMPL_HPP
