/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PHOTOVOLTAICPERFORMANCESIMPLE_HPP
#define EPMODEL_PHOTOVOLTAICPERFORMANCESIMPLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PhotovoltaicPerformanceSimple_Impl;
  }

  class EPMODEL_API PhotovoltaicPerformanceSimple : public ModelObject
  {
   public:
    explicit PhotovoltaicPerformanceSimple(const Model& model);

    virtual ~PhotovoltaicPerformanceSimple() override = default;
    PhotovoltaicPerformanceSimple(const PhotovoltaicPerformanceSimple& other) = default;
    PhotovoltaicPerformanceSimple(PhotovoltaicPerformanceSimple&& other) = default;
    PhotovoltaicPerformanceSimple& operator=(const PhotovoltaicPerformanceSimple&) = default;
    PhotovoltaicPerformanceSimple& operator=(PhotovoltaicPerformanceSimple&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> conversionEfficiencyInputModeValues();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model PhotovoltaicPerformanceSimple scalar accessor naming/signatures.
    // - Field Mapping: Preserved APIs map directly to EnergyPlus PhotovoltaicPerformance:Simple scalar fields.
    // - Field Mapping: Relationship field EfficiencyScheduleName is intentionally excluded from scalar-only scaffold scope.
    // - TODO(parity): Add non-scalar schedule relationship APIs only if/when parity scope expands.
    double fractionOfSurfaceAreaWithActiveSolarCells() const;
    bool isfractionOfSurfaceAreaWithActiveSolarCellsDefaulted() const;
    bool setFractionOfSurfaceAreaWithActiveSolarCells(double fractionOfSurfaceAreaWithActiveSolarCells);
    void resetFractionOfSurfaceAreaWithActiveSolarCells();

    std::string conversionEfficiencyInputMode() const;
    bool setConversionEfficiencyInputMode(const std::string& conversionEfficiencyInputMode);

    boost::optional<double> fixedEfficiency() const;
    bool setFixedEfficiency(double fixedEfficiency);
    void resetFixedEfficiency();

   protected:
    using ImplType = detail::PhotovoltaicPerformanceSimple_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PhotovoltaicPerformanceSimple(std::shared_ptr<detail::PhotovoltaicPerformanceSimple_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
