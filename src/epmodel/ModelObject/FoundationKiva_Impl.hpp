/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FOUNDATIONKIVA_IMPL_HPP
#define EPMODEL_FOUNDATIONKIVA_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API FoundationKiva_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~FoundationKiva_Impl() override = default;

      boost::optional<double> initialIndoorAirTemperature();
      bool setInitialIndoorAirTemperature(double initialIndoorAirTemperature);

      double interiorHorizontalInsulationDepth() const;
      bool isInteriorHorizontalInsulationDepthDefaulted() const;
      bool setInteriorHorizontalInsulationDepth(double interiorHorizontalInsulationDepth);
      void resetInteriorHorizontalInsulationDepth();

      boost::optional<double> interiorHorizontalInsulationWidth();
      bool setInteriorHorizontalInsulationWidth(double interiorHorizontalInsulationWidth);

      boost::optional<double> interiorVerticalInsulationDepth();
      bool setInteriorVerticalInsulationDepth(double interiorVerticalInsulationDepth);

      boost::optional<double> exteriorHorizontalInsulationDepth();
      bool setExteriorHorizontalInsulationDepth(double exteriorHorizontalInsulationDepth);

      double exteriorHorizontalInsulationWidth() const;
      bool isExteriorHorizontalInsulationWidthDefaulted() const;
      bool setExteriorHorizontalInsulationWidth(double exteriorHorizontalInsulationWidth);
      void resetExteriorHorizontalInsulationWidth();

      boost::optional<double> exteriorVerticalInsulationDepth();
      bool setExteriorVerticalInsulationDepth(double exteriorVerticalInsulationDepth);

      double wallHeightAboveGrade() const;
      bool isWallHeightAboveGradeDefaulted() const;
      bool setWallHeightAboveGrade(double wallHeightAboveGrade);
      void resetWallHeightAboveGrade();

      double wallDepthBelowSlab() const;
      bool isWallDepthBelowSlabDefaulted() const;
      bool setWallDepthBelowSlab(double wallDepthBelowSlab);
      void resetWallDepthBelowSlab();

      double footingDepth() const;
      bool isFootingDepthDefaulted() const;
      bool setFootingDepth(double footingDepth);
      void resetFootingDepth();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
