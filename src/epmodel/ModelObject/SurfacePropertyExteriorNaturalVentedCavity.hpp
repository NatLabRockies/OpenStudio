/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACEPROPERTYEXTERIORNATURALVENTEDCAVITY_HPP
#define EPMODEL_SURFACEPROPERTYEXTERIORNATURALVENTEDCAVITY_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SurfacePropertyExteriorNaturalVentedCavity_Impl;
  }

  class EPMODEL_API SurfacePropertyExteriorNaturalVentedCavity : public ModelObject
  {
   public:
    explicit SurfacePropertyExteriorNaturalVentedCavity(const Model& model);

    virtual ~SurfacePropertyExteriorNaturalVentedCavity() override = default;
    SurfacePropertyExteriorNaturalVentedCavity(const SurfacePropertyExteriorNaturalVentedCavity& other) = default;
    SurfacePropertyExteriorNaturalVentedCavity(SurfacePropertyExteriorNaturalVentedCavity&& other) = default;
    SurfacePropertyExteriorNaturalVentedCavity& operator=(const SurfacePropertyExteriorNaturalVentedCavity&) = default;
    SurfacePropertyExteriorNaturalVentedCavity& operator=(SurfacePropertyExteriorNaturalVentedCavity&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> roughnessOfExteriorSurfaceValues();

    // Schema Alignment Notes:
    // - API: Scalar accessors represent the EnergyPlus SurfaceProperty:ExteriorNaturalVentedCavity numeric and choice fields.
    // - Field Mapping: The numeric getters map to Area Fraction of Openings, Thermal Emissivity of Exterior Baffle Material,
    //   Solar Absorbtivity of Exterior Baffle, Height Scale for Buoyancy-Driven Ventilation, Effective Thickness of Cavity Behind Exterior Baffle,
    //   Ratio of Actual Surface Area to Projected Surface Area, Effectiveness for Perforations with Respect to Wind, and Discharge Coefficient for Openings with Respect to Buoyancy Driven Flow.
    // - Field Mapping: Boundary Conditions Model Name and the extensible Surface 1 Name fields remain excluded because they serve as relationship/navigation targets.
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

   protected:
    using ImplType = detail::SurfacePropertyExteriorNaturalVentedCavity_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SurfacePropertyExteriorNaturalVentedCavity(std::shared_ptr<detail::SurfacePropertyExteriorNaturalVentedCavity_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
