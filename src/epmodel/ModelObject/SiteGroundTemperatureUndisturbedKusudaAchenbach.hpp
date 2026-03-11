/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SITEGROUNDTEMPERATUREUNDISTURBEDKUSUDAACHENBACH_HPP
#define EPMODEL_SITEGROUNDTEMPERATUREUNDISTURBEDKUSUDAACHENBACH_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl;
}

class EPMODEL_API SiteGroundTemperatureUndisturbedKusudaAchenbach : public ModelObject
{
 public:
  explicit SiteGroundTemperatureUndisturbedKusudaAchenbach(const Model& model);

  virtual ~SiteGroundTemperatureUndisturbedKusudaAchenbach() override = default;
  SiteGroundTemperatureUndisturbedKusudaAchenbach(const SiteGroundTemperatureUndisturbedKusudaAchenbach& other) = default;
  SiteGroundTemperatureUndisturbedKusudaAchenbach(SiteGroundTemperatureUndisturbedKusudaAchenbach&& other) = default;
  SiteGroundTemperatureUndisturbedKusudaAchenbach& operator=(const SiteGroundTemperatureUndisturbedKusudaAchenbach&) = default;
  SiteGroundTemperatureUndisturbedKusudaAchenbach& operator=(SiteGroundTemperatureUndisturbedKusudaAchenbach&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserved openstudio::model accessor names/signatures for model-counterpart parity.
  // - Field Mapping: Scalar APIs map directly to Site:GroundTemperature:Undisturbed:KusudaAchenbach numeric fields.
  // - Translator Evidence: ForwardTranslateSiteGroundTemperatureUndisturbedKusudaAchenbach.cpp writes these same six scalar fields.
  // - Field Mapping: Name is a reference-provider field (UndisturbedGroundTempModels) and is excluded from scalar APIs.
  // - TODO(parity): Keep relationship/link convenience APIs out of scalar scaffold scope.
  double soilThermalConductivity() const;
  double soilDensity() const;
  double soilSpecificHeat() const;
  boost::optional<double> averageSoilSurfaceTemperature() const;
  boost::optional<double> averageAmplitudeofSurfaceTemperature() const;
  boost::optional<double> phaseShiftofMinimumSurfaceTemperature() const;

  bool setSoilThermalConductivity(double soilThermalConductivity);
  bool setSoilDensity(double soilDensity);
  bool setSoilSpecificHeat(double soilSpecificHeat);
  bool setAverageSoilSurfaceTemperature(double averageSoilSurfaceTemperature);
  void resetAverageSoilSurfaceTemperature();
  bool setAverageAmplitudeofSurfaceTemperature(double averageAmplitudeofSurfaceTemperature);
  void resetAverageAmplitudeofSurfaceTemperature();
  bool setPhaseShiftofMinimumSurfaceTemperature(double phaseShiftofMinimumSurfaceTemperature);
  void resetPhaseShiftofMinimumSurfaceTemperature();

 protected:
  using ImplType = detail::SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit SiteGroundTemperatureUndisturbedKusudaAchenbach(
    std::shared_ptr<detail::SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
