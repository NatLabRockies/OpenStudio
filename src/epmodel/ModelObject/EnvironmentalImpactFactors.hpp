/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ENVIRONMENTALIMPACTFACTORS_HPP
#define EPMODEL_ENVIRONMENTALIMPACTFACTORS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/core/Deprecated.hpp>
#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class EnvironmentalImpactFactors_Impl;
  }

  class EPMODEL_API EnvironmentalImpactFactors : public ModelObject
  {
   public:
    explicit EnvironmentalImpactFactors(const Model& model);

    virtual ~EnvironmentalImpactFactors() override = default;
    EnvironmentalImpactFactors(const EnvironmentalImpactFactors& other) = default;
    EnvironmentalImpactFactors(EnvironmentalImpactFactors&& other) = default;
    EnvironmentalImpactFactors& operator=(const EnvironmentalImpactFactors&) = default;
    EnvironmentalImpactFactors& operator=(EnvironmentalImpactFactors&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::EnvironmentalImpactFactors scalar accessor names/signatures, including deprecated aliases.
    // - Field Mapping: districtHeatingWaterEfficiency, districtCoolingCOP, districtHeatingSteamConversionEfficiency, and totalCarbonEquivalentEmissionFactorFrom* map directly to matching E+ EnvironmentalImpactFactors fields.
    // - Field Mapping: Deprecated compatibility aliases districtHeatingEfficiency/steamConversionEfficiency delegate to preserved primary APIs.
    // - ForwardTranslator evidence: ForwardTranslateEnvironmentalImpactFactors.cpp writes these six scalar fields directly.
    // - TODO(parity): Keep scalar-only scope for this pass; add non-scalar behavior later if needed without changing preserved signatures.
    double districtHeatingWaterEfficiency() const;
    OS_DEPRECATED(3, 7, 0) double districtHeatingEfficiency() const;
    bool setDistrictHeatingWaterEfficiency(double districtHeatingWaterEfficiency);
    OS_DEPRECATED(3, 7, 0) bool setDistrictHeatingEfficiency(double districtHeatingEfficiency);

    double districtCoolingCOP() const;
    bool setDistrictCoolingCOP(double districtCoolingCOP);

    double districtHeatingSteamConversionEfficiency() const;
    OS_DEPRECATED(3, 7, 0) double steamConversionEfficiency() const;
    bool setDistrictHeatingSteamConversionEfficiency(double districtHeatingSteamConversionEfficiency);
    OS_DEPRECATED(3, 7, 0) bool setSteamConversionEfficiency(double steamConversionEfficiency);

    double totalCarbonEquivalentEmissionFactorFromN2O() const;
    bool setTotalCarbonEquivalentEmissionFactorFromN2O(double totalCarbonEquivalentEmissionFactorFromN2O);

    double totalCarbonEquivalentEmissionFactorFromCH4() const;
    bool setTotalCarbonEquivalentEmissionFactorFromCH4(double totalCarbonEquivalentEmissionFactorFromCH4);

    double totalCarbonEquivalentEmissionFactorFromCO2() const;
    bool setTotalCarbonEquivalentEmissionFactorFromCO2(double totalCarbonEquivalentEmissionFactorFromCO2);

   protected:
    using ImplType = detail::EnvironmentalImpactFactors_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit EnvironmentalImpactFactors(std::shared_ptr<detail::EnvironmentalImpactFactors_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
