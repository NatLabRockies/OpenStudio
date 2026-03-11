/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SITEGROUNDDOMAINSLAB_HPP
#define EPMODEL_SITEGROUNDDOMAINSLAB_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SiteGroundDomainSlab_Impl;
  }

  class EPMODEL_API SiteGroundDomainSlab : public ModelObject
  {
   public:
    explicit SiteGroundDomainSlab(const Model& model);

    virtual ~SiteGroundDomainSlab() override = default;
    SiteGroundDomainSlab(const SiteGroundDomainSlab& other) = default;
    SiteGroundDomainSlab(SiteGroundDomainSlab&& other) = default;
    SiteGroundDomainSlab& operator=(const SiteGroundDomainSlab&) = default;
    SiteGroundDomainSlab& operator=(SiteGroundDomainSlab&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> undisturbedGroundTemperatureModelTypeValues();
    static std::vector<std::string> slabLocationValues();
    static std::vector<std::string> horizontalInsulationExtentsValues();
    static std::vector<std::string> simulationTimestepValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type mirrors the EnergyPlus Site:GroundDomain:Slab scalar fields.
    // - Field Mapping: Scalar accessors delegate directly to Site:GroundDomain:Slab field enums for soils, insulation, and mesh settings.
    // - TODO(parity): Relationship/object-list fields (undisturbed ground temperature model name, slab boundary condition model name, slab material name, horizontal insulation material name) remain for a follow-up pass.
    double groundDomainDepth() const;
    bool isGroundDomainDepthDefaulted() const;
    bool setGroundDomainDepth(double groundDomainDepth);
    void resetGroundDomainDepth();

    double aspectRatio() const;
    bool isAspectRatioDefaulted() const;
    bool setAspectRatio(double aspectRatio);
    void resetAspectRatio();

    double perimeterOffset() const;
    bool isPerimeterOffsetDefaulted() const;
    bool setPerimeterOffset(double perimeterOffset);
    void resetPerimeterOffset();

    double soilThermalConductivity() const;
    bool isSoilThermalConductivityDefaulted() const;
    bool setSoilThermalConductivity(double soilThermalConductivity);
    void resetSoilThermalConductivity();

    double soilDensity() const;
    bool isSoilDensityDefaulted() const;
    bool setSoilDensity(double soilDensity);
    void resetSoilDensity();

    double soilSpecificHeat() const;
    bool isSoilSpecificHeatDefaulted() const;
    bool setSoilSpecificHeat(double soilSpecificHeat);
    void resetSoilSpecificHeat();

    double soilMoistureContentVolumeFraction() const;
    bool isSoilMoistureContentVolumeFractionDefaulted() const;
    bool setSoilMoistureContentVolumeFraction(double soilMoistureContentVolumeFraction);
    void resetSoilMoistureContentVolumeFraction();

    double soilMoistureContentVolumeFractionatSaturation() const;
    bool isSoilMoistureContentVolumeFractionatSaturationDefaulted() const;
    bool setSoilMoistureContentVolumeFractionatSaturation(double soilMoistureContentVolumeFractionatSaturation);
    void resetSoilMoistureContentVolumeFractionatSaturation();

    std::string undisturbedGroundTemperatureModelType() const;
    bool setUndisturbedGroundTemperatureModelType(const std::string& undisturbedGroundTemperatureModelType);

    double evapotranspirationGroundCoverParameter() const;
    bool isEvapotranspirationGroundCoverParameterDefaulted() const;
    bool setEvapotranspirationGroundCoverParameter(double evapotranspirationGroundCoverParameter);
    void resetEvapotranspirationGroundCoverParameter();

    std::string slabLocation() const;
    bool setSlabLocation(const std::string& slabLocation);

    bool horizontalInsulation() const;
    bool isHorizontalInsulationDefaulted() const;
    bool setHorizontalInsulation(bool horizontalInsulation);
    void resetHorizontalInsulation();

    std::string horizontalInsulationExtents() const;
    bool isHorizontalInsulationExtentsDefaulted() const;
    bool setHorizontalInsulationExtents(const std::string& horizontalInsulationExtents);
    void resetHorizontalInsulationExtents();

    boost::optional<double> perimeterInsulationWidth() const;
    bool setPerimeterInsulationWidth(double perimeterInsulationWidth);
    void resetPerimeterInsulationWidth();

    double geometricMeshCoefficient() const;
    bool isGeometricMeshCoefficientDefaulted() const;
    bool setGeometricMeshCoefficient(double geometricMeshCoefficient);
    void resetGeometricMeshCoefficient();

    boost::optional<double> verticalInsulationDepth() const;
    bool setVerticalInsulationDepth(double verticalInsulationDepth);
    void resetVerticalInsulationDepth();

    bool verticalInsulation() const;
    bool isVerticalInsulationDefaulted() const;
    bool setVerticalInsulation(bool verticalInsulation);
    void resetVerticalInsulation();

    std::string simulationTimestep() const;
    bool isSimulationTimestepDefaulted() const;
    bool setSimulationTimestep(const std::string& simulationTimestep);
    void resetSimulationTimestep();

    int meshDensityParameter() const;
    bool isMeshDensityParameterDefaulted() const;
    bool setMeshDensityParameter(int meshDensityParameter);
    void resetMeshDensityParameter();

   protected:
    using ImplType = detail::SiteGroundDomainSlab_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SiteGroundDomainSlab(std::shared_ptr<detail::SiteGroundDomainSlab_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
