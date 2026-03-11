/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ENVIRONMENTALIMPACTFACTORS_IMPL_HPP
#define EPMODEL_ENVIRONMENTALIMPACTFACTORS_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API EnvironmentalImpactFactors_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~EnvironmentalImpactFactors_Impl() override = default;

  double districtHeatingWaterEfficiency() const;
  double districtCoolingCOP() const;
  double districtHeatingSteamConversionEfficiency() const;
  double totalCarbonEquivalentEmissionFactorFromN2O() const;
  double totalCarbonEquivalentEmissionFactorFromCH4() const;
  double totalCarbonEquivalentEmissionFactorFromCO2() const;

  bool setDistrictHeatingWaterEfficiency(double districtHeatingWaterEfficiency);
  bool setDistrictCoolingCOP(double districtCoolingCOP);
  bool setDistrictHeatingSteamConversionEfficiency(double districtHeatingSteamConversionEfficiency);
  bool setTotalCarbonEquivalentEmissionFactorFromN2O(double totalCarbonEquivalentEmissionFactorFromN2O);
  bool setTotalCarbonEquivalentEmissionFactorFromCH4(double totalCarbonEquivalentEmissionFactorFromCH4);
  bool setTotalCarbonEquivalentEmissionFactorFromCO2(double totalCarbonEquivalentEmissionFactorFromCO2);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
