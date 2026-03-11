/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACEPROPERTYEXTERIORNATURALVENTEDCAVITY_IMPL_HPP
#define EPMODEL_SURFACEPROPERTYEXTERIORNATURALVENTEDCAVITY_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SurfacePropertyExteriorNaturalVentedCavity_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SurfacePropertyExteriorNaturalVentedCavity_Impl() override = default;

      boost::optional<double> areaFractionOfOpenings() const;
      bool setAreaFractionOfOpenings(double areaFractionOfOpenings);
      void resetAreaFractionOfOpenings();

      boost::optional<double> thermalEmissivityOfExteriorBaffleMaterial() const;
      bool setThermalEmissivityOfExteriorBaffleMaterial(double thermalEmissivityOfExteriorBaffleMaterial);
      void resetThermalEmissivityOfExteriorBaffleMaterial();

      boost::optional<double> solarAbsorbtivityOfExteriorBaffle() const;
      bool setSolarAbsorbtivityOfExteriorBaffle(double solarAbsorbtivityOfExteriorBaffle);
      void resetSolarAbsorbtivityOfExteriorBaffle();

      boost::optional<double> heightScaleForBuoyancyDrivenVentilation() const;
      bool setHeightScaleForBuoyancyDrivenVentilation(double heightScaleForBuoyancyDrivenVentilation);
      void resetHeightScaleForBuoyancyDrivenVentilation();

      boost::optional<double> effectiveThicknessOfCavityBehindExteriorBaffle() const;
      bool setEffectiveThicknessOfCavityBehindExteriorBaffle(double effectiveThicknessOfCavityBehindExteriorBaffle);
      void resetEffectiveThicknessOfCavityBehindExteriorBaffle();

      double ratioOfActualSurfaceAreaToProjectedSurfaceArea() const;
      bool setRatioOfActualSurfaceAreaToProjectedSurfaceArea(double ratioOfActualSurfaceAreaToProjectedSurfaceArea);
      bool isRatioOfActualSurfaceAreaToProjectedSurfaceAreaDefaulted() const;
      void resetRatioOfActualSurfaceAreaToProjectedSurfaceArea();

      std::string roughnessOfExteriorSurface() const;
      bool setRoughnessOfExteriorSurface(const std::string& roughnessOfExteriorSurface);

      double effectivenessForPerforationsWithRespectToWind() const;
      bool setEffectivenessForPerforationsWithRespectToWind(double effectivenessForPerforationsWithRespectToWind);
      bool isEffectivenessForPerforationsWithRespectToWindDefaulted() const;
      void resetEffectivenessForPerforationsWithRespectToWind();

      double dischargeCoefficientForOpeningsWithRespectToBuoyancyDrivenFlow() const;
      bool setDischargeCoefficientForOpeningsWithRespectToBuoyancyDrivenFlow(double dischargeCoefficientForOpeningsWithRespectToBuoyancyDrivenFlow);
      bool isDischargeCoefficientForOpeningsWithRespectToBuoyancyDrivenFlowDefaulted() const;
      void resetDischargeCoefficientForOpeningsWithRespectToBuoyancyDrivenFlow();

      std::vector<std::string> roughnessOfExteriorSurfaceValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
