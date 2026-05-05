/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SITEGROUNDDOMAINBASEMENT_HPP
#define EPMODEL_SITEGROUNDDOMAINBASEMENT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SiteGroundDomainBasement_Impl;
  }

  class EPMODEL_API SiteGroundDomainBasement : public ModelObject
  {
   public:
    explicit SiteGroundDomainBasement(const Model& model);

    virtual ~SiteGroundDomainBasement() override = default;
    SiteGroundDomainBasement(const SiteGroundDomainBasement& other) = default;
    SiteGroundDomainBasement(SiteGroundDomainBasement&& other) = default;
    SiteGroundDomainBasement& operator=(const SiteGroundDomainBasement&) = default;
    SiteGroundDomainBasement& operator=(SiteGroundDomainBasement&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> undisturbedGroundTemperatureModelTypeValues();
    static std::vector<std::string> horizontalInsulationExtentsValues();
    static std::vector<std::string> simulationTimestepValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to EnergyPlus Site:GroundDomain:Basement scalar fields.
    // - TODO(parity): Add relationship-like APIs for object-list fields in a follow-up parity pass.
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

    bool horizontalInsulation() const;
    bool isHorizontalInsulationDefaulted() const;
    bool setHorizontalInsulation(bool horizontalInsulation);
    void resetHorizontalInsulation();

    std::string horizontalInsulationExtents() const;
    bool isHorizontalInsulationExtentsDefaulted() const;
    bool setHorizontalInsulationExtents(const std::string& horizontalInsulationExtents);
    void resetHorizontalInsulationExtents();

    boost::optional<double> perimeterHorizontalInsulationWidth() const;
    bool setPerimeterHorizontalInsulationWidth(double perimeterHorizontalInsulationWidth);
    void resetPerimeterHorizontalInsulationWidth();

    boost::optional<double> basementWallDepth() const;
    bool setBasementWallDepth(double basementWallDepth);
    void resetBasementWallDepth();

    bool verticalInsulation() const;
    bool isVerticalInsulationDefaulted() const;
    bool setVerticalInsulation(bool verticalInsulation);
    void resetVerticalInsulation();

    boost::optional<double> verticalInsulationDepth() const;
    bool setVerticalInsulationDepth(double verticalInsulationDepth);
    void resetVerticalInsulationDepth();

    std::string simulationTimestep() const;
    bool isSimulationTimestepDefaulted() const;
    bool setSimulationTimestep(const std::string& simulationTimestep);
    void resetSimulationTimestep();

    int meshDensityParameter() const;
    bool isMeshDensityParameterDefaulted() const;
    bool setMeshDensityParameter(int meshDensityParameter);
    void resetMeshDensityParameter();

   protected:
    using ImplType = detail::SiteGroundDomainBasement_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SiteGroundDomainBasement(std::shared_ptr<detail::SiteGroundDomainBasement_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
