/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FOUNDATIONKIVASETTINGS_IMPL_HPP
#define EPMODEL_FOUNDATIONKIVASETTINGS_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API FoundationKivaSettings_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~FoundationKivaSettings_Impl() override = default;

      double soilConductivity() const;
      bool isSoilConductivityDefaulted() const;
      bool setSoilConductivity(double soilConductivity);
      void resetSoilConductivity();

      double soilDensity() const;
      bool isSoilDensityDefaulted() const;
      bool setSoilDensity(double soilDensity);
      void resetSoilDensity();

      double soilSpecificHeat() const;
      bool isSoilSpecificHeatDefaulted() const;
      bool setSoilSpecificHeat(double soilSpecificHeat);
      void resetSoilSpecificHeat();

      double groundSolarAbsorptivity() const;
      bool isGroundSolarAbsorptivityDefaulted() const;
      bool setGroundSolarAbsorptivity(double groundSolarAbsorptivity);
      void resetGroundSolarAbsorptivity();

      double groundThermalAbsorptivity() const;
      bool isGroundThermalAbsorptivityDefaulted() const;
      bool setGroundThermalAbsorptivity(double groundThermalAbsorptivity);
      void resetGroundThermalAbsorptivity();

      double groundSurfaceRoughness() const;
      bool isGroundSurfaceRoughnessDefaulted() const;
      bool setGroundSurfaceRoughness(double groundSurfaceRoughness);
      void resetGroundSurfaceRoughness();

      double farFieldWidth() const;
      bool isFarFieldWidthDefaulted() const;
      bool setFarFieldWidth(double farFieldWidth);
      void resetFarFieldWidth();

      std::string deepGroundBoundaryCondition() const;
      bool isDeepGroundBoundaryConditionAutoselected();
      bool setDeepGroundBoundaryCondition(const std::string& deepGroundBoundaryCondition);
      void resetDeepGroundBoundaryCondition();

      boost::optional<double> deepGroundDepth();
      bool isDeepGroundDepthAutocalculated();
      bool setDeepGroundDepth(double deepGroundDepth);
      void autocalculateDeepGroundDepth();

      double minimumCellDimension() const;
      bool isMinimumCellDimensionDefaulted() const;
      bool setMinimumCellDimension(double minimumCellDimension);
      void resetMinimumCellDimension();

      double maximumCellGrowthCoefficient() const;
      bool isMaximumCellGrowthCoefficientDefaulted() const;
      bool setMaximumCellGrowthCoefficient(double maximumCellGrowthCoefficient);
      void resetMaximumCellGrowthCoefficient();

      std::string simulationTimestep() const;
      bool isSimulationTimestepDefaulted() const;
      bool setSimulationTimestep(const std::string& simulationTimestep);
      void resetSimulationTimestep();

      std::vector<std::string> deepGroundBoundaryConditionValues() const;
      std::vector<std::string> simulationTimestepValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
