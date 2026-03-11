/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACECONVECTIONALGORITHMOUTSIDEADAPTIVEMODELSELECTIONS_IMPL_HPP
#define EPMODEL_SURFACECONVECTIONALGORITHMOUTSIDEADAPTIVEMODELSELECTIONS_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl() override = default;

      // Wind Convection fields
      std::string windConvectionWindwardVerticalWallEquationSource() const;
      bool setWindConvectionWindwardVerticalWallEquationSource(const std::string& windConvectionWindwardVerticalWallEquationSource);
      bool isWindConvectionWindwardVerticalWallEquationSourceDefaulted() const;
      void resetWindConvectionWindwardVerticalWallEquationSource();

      std::string windConvectionLeewardVerticalWallEquationSource() const;
      bool setWindConvectionLeewardVerticalWallEquationSource(const std::string& windConvectionLeewardVerticalWallEquationSource);
      bool isWindConvectionLeewardVerticalWallEquationSourceDefaulted() const;
      void resetWindConvectionLeewardVerticalWallEquationSource();

      std::string windConvectionHorizontalRoofEquationSource() const;
      bool setWindConvectionHorizontalRoofEquationSource(const std::string& windConvectionHorizontalRoofEquationSource);
      bool isWindConvectionHorizontalRoofEquationSourceDefaulted() const;
      void resetWindConvectionHorizontalRoofEquationSource();

      // Natural Convection fields
      std::string naturalConvectionVerticalWallEquationSource() const;
      bool setNaturalConvectionVerticalWallEquationSource(const std::string& naturalConvectionVerticalWallEquationSource);
      bool isNaturalConvectionVerticalWallEquationSourceDefaulted() const;
      void resetNaturalConvectionVerticalWallEquationSource();

      std::string naturalConvectionStableHorizontalEquationSource() const;
      bool setNaturalConvectionStableHorizontalEquationSource(const std::string& naturalConvectionStableHorizontalEquationSource);
      bool isNaturalConvectionStableHorizontalEquationSourceDefaulted() const;
      void resetNaturalConvectionStableHorizontalEquationSource();

      std::string naturalConvectionUnstableHorizontalEquationSource() const;
      bool setNaturalConvectionUnstableHorizontalEquationSource(const std::string& naturalConvectionUnstableHorizontalEquationSource);
      bool isNaturalConvectionUnstableHorizontalEquationSourceDefaulted() const;
      void resetNaturalConvectionUnstableHorizontalEquationSource();

      // Choice values helpers (instance delegates to static)
      std::vector<std::string> windConvectionWindwardVerticalWallEquationSourceValues() const;
      std::vector<std::string> windConvectionLeewardVerticalWallEquationSourceValues() const;
      std::vector<std::string> windConvectionHorizontalRoofEquationSourceValues() const;
      std::vector<std::string> naturalConvectionVerticalWallEquationSourceValues() const;
      std::vector<std::string> naturalConvectionStableHorizontalEquationSourceValues() const;
      std::vector<std::string> naturalConvectionUnstableHorizontalEquationSourceValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
