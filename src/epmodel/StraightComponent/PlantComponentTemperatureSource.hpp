/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANTCOMPONENTTEMPERATURESOURCE_HPP
#define EPMODEL_PLANTCOMPONENTTEMPERATURESOURCE_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class PlantComponentTemperatureSource_Impl;
}

class EPMODEL_API PlantComponentTemperatureSource : public StraightComponent
{
 public:
  explicit PlantComponentTemperatureSource(const Model& model);

  virtual ~PlantComponentTemperatureSource() override = default;
  PlantComponentTemperatureSource(const PlantComponentTemperatureSource& other) = default;
  PlantComponentTemperatureSource(PlantComponentTemperatureSource&& other) = default;
  PlantComponentTemperatureSource& operator=(const PlantComponentTemperatureSource&) = default;
  PlantComponentTemperatureSource& operator=(PlantComponentTemperatureSource&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> temperatureSpecificationTypeValues();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model::PlantComponentTemperatureSource scalar accessor names/signatures.
  // - Field Mapping: designVolumeFlowRate/isDesignVolumeFlowRateAutosized/set/autosize map to E+ Design Volume Flow Rate.
  // - Field Mapping: temperatureSpecificationType maps to E+ Temperature Specification Type.
  // - Field Mapping: sourceTemperature/set/resetSourceTemperature map to E+ Source Temperature.
  // - ForwardTranslator evidence: ForwardTranslatePlantComponentTemperatureSource.cpp uses the same mappings and autosize semantics.
  // - Field Mapping: inlet/outlet node names and sourceTemperatureSchedule are relationship fields and excluded from this scalar pass.
  // - TODO(parity): Add excluded relationship APIs without changing preserved scalar signatures.
  boost::optional<double> designVolumeFlowRate() const;
  bool isDesignVolumeFlowRateAutosized() const;

  std::string temperatureSpecificationType() const;

  boost::optional<double> sourceTemperature() const;

  bool setDesignVolumeFlowRate(double designVolumeFlowRate);
  void autosizeDesignVolumeFlowRate();

  bool setTemperatureSpecificationType(const std::string& temperatureSpecificationType);

  bool setSourceTemperature(double sourceTemperature);
  void resetSourceTemperature();

  boost::optional<double> autosizedDesignVolumeFlowRate() const;

 protected:
  using ImplType = detail::PlantComponentTemperatureSource_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit PlantComponentTemperatureSource(std::shared_ptr<detail::PlantComponentTemperatureSource_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
