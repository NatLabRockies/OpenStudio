/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SITEGROUNDDOMAINBASEMENT_IMPL_HPP
#define EPMODEL_SITEGROUNDDOMAINBASEMENT_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SiteGroundDomainBasement_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SiteGroundDomainBasement_Impl() override = default;

      std::vector<std::string> undisturbedGroundTemperatureModelTypeValues() const;
      std::vector<std::string> horizontalInsulationExtentsValues() const;
      std::vector<std::string> simulationTimestepValues() const;

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
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
