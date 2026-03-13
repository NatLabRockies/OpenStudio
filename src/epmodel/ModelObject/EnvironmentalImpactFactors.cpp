/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "EnvironmentalImpactFactors.hpp"
#include "EnvironmentalImpactFactors_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/EnvironmentalImpactFactors_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  EnvironmentalImpactFactors::EnvironmentalImpactFactors(const Model& model) : ModelObject(EnvironmentalImpactFactors::iddObjectType(), model) {
    // Keep required scalar fields populated for strict non-optional getters.
    OS_ASSERT(setDistrictHeatingWaterEfficiency(0.3));
    OS_ASSERT(setDistrictCoolingCOP(3.0));
    OS_ASSERT(setDistrictHeatingSteamConversionEfficiency(0.25));
    OS_ASSERT(setTotalCarbonEquivalentEmissionFactorFromN2O(80.7272));
    OS_ASSERT(setTotalCarbonEquivalentEmissionFactorFromCH4(6.2727));
    OS_ASSERT(setTotalCarbonEquivalentEmissionFactorFromCO2(0.2727));
  }

  EnvironmentalImpactFactors::EnvironmentalImpactFactors(std::shared_ptr<detail::EnvironmentalImpactFactors_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType EnvironmentalImpactFactors::iddObjectType() {
    return IddObjectType::EnvironmentalImpactFactors;
  }

  double EnvironmentalImpactFactors::districtHeatingWaterEfficiency() const {
    return getImpl<detail::EnvironmentalImpactFactors_Impl>()->districtHeatingWaterEfficiency();
  }

  bool EnvironmentalImpactFactors::setDistrictHeatingWaterEfficiency(double districtHeatingWaterEfficiency) {
    return getImpl<detail::EnvironmentalImpactFactors_Impl>()->setDistrictHeatingWaterEfficiency(districtHeatingWaterEfficiency);
  }

  double EnvironmentalImpactFactors::districtHeatingEfficiency() const {
    return getImpl<detail::EnvironmentalImpactFactors_Impl>()->districtHeatingWaterEfficiency();
  }

  bool EnvironmentalImpactFactors::setDistrictHeatingEfficiency(double districtHeatingEfficiency) {
    return getImpl<detail::EnvironmentalImpactFactors_Impl>()->setDistrictHeatingWaterEfficiency(districtHeatingEfficiency);
  }

  double EnvironmentalImpactFactors::districtCoolingCOP() const {
    return getImpl<detail::EnvironmentalImpactFactors_Impl>()->districtCoolingCOP();
  }

  bool EnvironmentalImpactFactors::setDistrictCoolingCOP(double districtCoolingCOP) {
    return getImpl<detail::EnvironmentalImpactFactors_Impl>()->setDistrictCoolingCOP(districtCoolingCOP);
  }

  double EnvironmentalImpactFactors::districtHeatingSteamConversionEfficiency() const {
    return getImpl<detail::EnvironmentalImpactFactors_Impl>()->districtHeatingSteamConversionEfficiency();
  }

  bool EnvironmentalImpactFactors::setDistrictHeatingSteamConversionEfficiency(double districtHeatingSteamConversionEfficiency) {
    return getImpl<detail::EnvironmentalImpactFactors_Impl>()->setDistrictHeatingSteamConversionEfficiency(districtHeatingSteamConversionEfficiency);
  }

  double EnvironmentalImpactFactors::steamConversionEfficiency() const {
    return getImpl<detail::EnvironmentalImpactFactors_Impl>()->districtHeatingSteamConversionEfficiency();
  }

  bool EnvironmentalImpactFactors::setSteamConversionEfficiency(double steamConversionEfficiency) {
    return getImpl<detail::EnvironmentalImpactFactors_Impl>()->setDistrictHeatingSteamConversionEfficiency(steamConversionEfficiency);
  }

  double EnvironmentalImpactFactors::totalCarbonEquivalentEmissionFactorFromN2O() const {
    return getImpl<detail::EnvironmentalImpactFactors_Impl>()->totalCarbonEquivalentEmissionFactorFromN2O();
  }

  bool EnvironmentalImpactFactors::setTotalCarbonEquivalentEmissionFactorFromN2O(double totalCarbonEquivalentEmissionFactorFromN2O) {
    return getImpl<detail::EnvironmentalImpactFactors_Impl>()->setTotalCarbonEquivalentEmissionFactorFromN2O(
      totalCarbonEquivalentEmissionFactorFromN2O);
  }

  double EnvironmentalImpactFactors::totalCarbonEquivalentEmissionFactorFromCH4() const {
    return getImpl<detail::EnvironmentalImpactFactors_Impl>()->totalCarbonEquivalentEmissionFactorFromCH4();
  }

  bool EnvironmentalImpactFactors::setTotalCarbonEquivalentEmissionFactorFromCH4(double totalCarbonEquivalentEmissionFactorFromCH4) {
    return getImpl<detail::EnvironmentalImpactFactors_Impl>()->setTotalCarbonEquivalentEmissionFactorFromCH4(
      totalCarbonEquivalentEmissionFactorFromCH4);
  }

  double EnvironmentalImpactFactors::totalCarbonEquivalentEmissionFactorFromCO2() const {
    return getImpl<detail::EnvironmentalImpactFactors_Impl>()->totalCarbonEquivalentEmissionFactorFromCO2();
  }

  bool EnvironmentalImpactFactors::setTotalCarbonEquivalentEmissionFactorFromCO2(double totalCarbonEquivalentEmissionFactorFromCO2) {
    return getImpl<detail::EnvironmentalImpactFactors_Impl>()->setTotalCarbonEquivalentEmissionFactorFromCO2(
      totalCarbonEquivalentEmissionFactorFromCO2);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double EnvironmentalImpactFactors_Impl::districtHeatingWaterEfficiency() const {
      const auto value = getDouble(openstudio::EnvironmentalImpactFactorsFields::DistrictHeatingWaterEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    double EnvironmentalImpactFactors_Impl::districtCoolingCOP() const {
      const auto value = getDouble(openstudio::EnvironmentalImpactFactorsFields::DistrictCoolingCOP, true);
      OS_ASSERT(value);
      return *value;
    }

    double EnvironmentalImpactFactors_Impl::districtHeatingSteamConversionEfficiency() const {
      const auto value = getDouble(openstudio::EnvironmentalImpactFactorsFields::DistrictHeatingSteamConversionEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    double EnvironmentalImpactFactors_Impl::totalCarbonEquivalentEmissionFactorFromN2O() const {
      const auto value = getDouble(openstudio::EnvironmentalImpactFactorsFields::TotalCarbonEquivalentEmissionFactorFromN2O, true);
      OS_ASSERT(value);
      return *value;
    }

    double EnvironmentalImpactFactors_Impl::totalCarbonEquivalentEmissionFactorFromCH4() const {
      const auto value = getDouble(openstudio::EnvironmentalImpactFactorsFields::TotalCarbonEquivalentEmissionFactorFromCH4, true);
      OS_ASSERT(value);
      return *value;
    }

    double EnvironmentalImpactFactors_Impl::totalCarbonEquivalentEmissionFactorFromCO2() const {
      const auto value = getDouble(openstudio::EnvironmentalImpactFactorsFields::TotalCarbonEquivalentEmissionFactorFromCO2, true);
      OS_ASSERT(value);
      return *value;
    }

    bool EnvironmentalImpactFactors_Impl::setDistrictHeatingWaterEfficiency(double districtHeatingWaterEfficiency) {
      return setDouble(openstudio::EnvironmentalImpactFactorsFields::DistrictHeatingWaterEfficiency, districtHeatingWaterEfficiency);
    }

    bool EnvironmentalImpactFactors_Impl::setDistrictCoolingCOP(double districtCoolingCOP) {
      return setDouble(openstudio::EnvironmentalImpactFactorsFields::DistrictCoolingCOP, districtCoolingCOP);
    }

    bool EnvironmentalImpactFactors_Impl::setDistrictHeatingSteamConversionEfficiency(double districtHeatingSteamConversionEfficiency) {
      return setDouble(openstudio::EnvironmentalImpactFactorsFields::DistrictHeatingSteamConversionEfficiency,
                       districtHeatingSteamConversionEfficiency);
    }

    bool EnvironmentalImpactFactors_Impl::setTotalCarbonEquivalentEmissionFactorFromN2O(double totalCarbonEquivalentEmissionFactorFromN2O) {
      const bool result = setDouble(openstudio::EnvironmentalImpactFactorsFields::TotalCarbonEquivalentEmissionFactorFromN2O,
                                    totalCarbonEquivalentEmissionFactorFromN2O);
      OS_ASSERT(result);
      return result;
    }

    bool EnvironmentalImpactFactors_Impl::setTotalCarbonEquivalentEmissionFactorFromCH4(double totalCarbonEquivalentEmissionFactorFromCH4) {
      const bool result = setDouble(openstudio::EnvironmentalImpactFactorsFields::TotalCarbonEquivalentEmissionFactorFromCH4,
                                    totalCarbonEquivalentEmissionFactorFromCH4);
      OS_ASSERT(result);
      return result;
    }

    bool EnvironmentalImpactFactors_Impl::setTotalCarbonEquivalentEmissionFactorFromCO2(double totalCarbonEquivalentEmissionFactorFromCO2) {
      const bool result = setDouble(openstudio::EnvironmentalImpactFactorsFields::TotalCarbonEquivalentEmissionFactorFromCO2,
                                    totalCarbonEquivalentEmissionFactorFromCO2);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
