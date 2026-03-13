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
      bool setDistrictHeatingWaterEfficiency(double districtHeatingWaterEfficiency);

      double districtCoolingCOP() const;
      bool setDistrictCoolingCOP(double districtCoolingCOP);

      double districtHeatingSteamConversionEfficiency() const;
      bool setDistrictHeatingSteamConversionEfficiency(double districtHeatingSteamConversionEfficiency);

      double totalCarbonEquivalentEmissionFactorFromN2O() const;
      bool setTotalCarbonEquivalentEmissionFactorFromN2O(double totalCarbonEquivalentEmissionFactorFromN2O);

      double totalCarbonEquivalentEmissionFactorFromCH4() const;
      bool setTotalCarbonEquivalentEmissionFactorFromCH4(double totalCarbonEquivalentEmissionFactorFromCH4);

      double totalCarbonEquivalentEmissionFactorFromCO2() const;
      bool setTotalCarbonEquivalentEmissionFactorFromCO2(double totalCarbonEquivalentEmissionFactorFromCO2);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
