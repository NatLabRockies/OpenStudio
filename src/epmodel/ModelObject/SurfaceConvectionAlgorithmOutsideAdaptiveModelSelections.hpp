/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACECONVECTIONALGORITHMOUTSIDEADAPTIVEMODELSELECTIONS_HPP
#define EPMODEL_SURFACECONVECTIONALGORITHMOUTSIDEADAPTIVEMODELSELECTIONS_HPP

#include "../EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl;
  }

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to SurfaceConvectionAlgorithm:Outside:AdaptiveModelSelections choice fields.
  // - Field Mapping: User Curve Name fields (object-list UserConvectionOutsideModels) are excluded as relationship fields.
  // - TODO(parity): Add relationship APIs for user curve linkage after scalar saturation.
  class EPMODEL_API SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections : public ModelObject
  {
   public:
    explicit SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections(const Model& model);

    virtual ~SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections() override = default;
    SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections(const SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections& other) = default;
    SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections(SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections&& other) = default;
    SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections& operator=(const SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections&) = default;
    SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections& operator=(SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections&&) = default;

    static IddObjectType iddObjectType();

    // Choice values helpers
    static std::vector<std::string> windConvectionWindwardVerticalWallEquationSourceValues();
    static std::vector<std::string> windConvectionLeewardVerticalWallEquationSourceValues();
    static std::vector<std::string> windConvectionHorizontalRoofEquationSourceValues();
    static std::vector<std::string> naturalConvectionVerticalWallEquationSourceValues();
    static std::vector<std::string> naturalConvectionStableHorizontalEquationSourceValues();
    static std::vector<std::string> naturalConvectionUnstableHorizontalEquationSourceValues();

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

   protected:
    using ImplType = detail::SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections(
      std::shared_ptr<detail::SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
