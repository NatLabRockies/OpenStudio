/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FOUNDATIONKIVASETTINGS_HPP
#define EPMODEL_FOUNDATIONKIVASETTINGS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class FoundationKivaSettings_Impl;
}

class EPMODEL_API FoundationKivaSettings : public ModelObject
{
 public:
  static constexpr bool is_unique = true;  // This is a Unique ModelObject

  explicit FoundationKivaSettings(const Model& model);

  virtual ~FoundationKivaSettings() override = default;
  FoundationKivaSettings(const FoundationKivaSettings& other) = default;
  FoundationKivaSettings(FoundationKivaSettings&& other) = default;
  FoundationKivaSettings& operator=(const FoundationKivaSettings&) = default;
  FoundationKivaSettings& operator=(FoundationKivaSettings&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> deepGroundBoundaryConditionValues();
  static std::vector<std::string> simulationTimestepValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model FoundationKivaSettings scalar accessor names/signatures.
  // - Field Mapping: API methods map directly to Foundation:Kiva:Settings scalar fields.
  // - Field Mapping: DeepGroundDepth preserves autocalculate behavior via string token in the same field.
  // - TODO(parity): Extend beyond scalar scope only after scalar saturation.
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

 protected:
  using ImplType = detail::FoundationKivaSettings_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit FoundationKivaSettings(std::shared_ptr<detail::FoundationKivaSettings_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
