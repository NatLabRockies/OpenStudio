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

  /** \brief Represents <code>EnvironmentalImpactFactors</code>.
   *
   * \par EnergyPlus object
   * \epobject{input-for-output.html#environmentalimpactfactors,EnvironmentalImpactFactors}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::EnvironmentalImpactFactors</code>.
   * The EPModel declaration exposes the EnergyPlus-backed fields shown here; Model conveniences for typed relationships, extensible groups, or OpenStudio-only fields are not available unless declared here.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API EnvironmentalImpactFactors : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~EnvironmentalImpactFactors() override = default;
    EnvironmentalImpactFactors(const EnvironmentalImpactFactors& other) = default;
    EnvironmentalImpactFactors(EnvironmentalImpactFactors&& other) = default;
    EnvironmentalImpactFactors& operator=(const EnvironmentalImpactFactors&) = default;
    EnvironmentalImpactFactors& operator=(EnvironmentalImpactFactors&&) = default;

    static IddObjectType iddObjectType();
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
    explicit EnvironmentalImpactFactors(const Model& model);

    using ImplType = detail::EnvironmentalImpactFactors_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit EnvironmentalImpactFactors(std::shared_ptr<detail::EnvironmentalImpactFactors_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
