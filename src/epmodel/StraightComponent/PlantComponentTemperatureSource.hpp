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
    // - Status: Scalar Parity. The canonical temperature-source scalar surface is present, while node and schedule helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::PlantComponentTemperatureSource.
    // - Implemented Parity: The preserved scalar API matches the design-flow, temperature-specification, and source-temperature accessors with matching autosize/default behavior.
    // - Documented Delta: Inlet/outlet node names and the source-temperature schedule remain intentionally excluded from this scalar pass.
    // - Field/Storage Mapping: These accessors map directly to EnergyPlus `PlantComponent:TemperatureSource` scalar fields used by the forward translator.
    // - Evidence: `src/model/PlantComponentTemperatureSource.hpp`, `src/model/PlantComponentTemperatureSource.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslatePlantComponentTemperatureSource.cpp`.
    // - Remaining Parity Work: Add the omitted relationship helpers without changing the preserved scalar signatures.

    boost::optional<double> designVolumeFlowRate() const;
    bool isDesignVolumeFlowRateAutosized() const;
    bool setDesignVolumeFlowRate(double designVolumeFlowRate);
    void autosizeDesignVolumeFlowRate();
    boost::optional<double> autosizedDesignVolumeFlowRate() const;

    std::string temperatureSpecificationType() const;
    bool setTemperatureSpecificationType(const std::string& temperatureSpecificationType);

    boost::optional<double> sourceTemperature() const;
    bool setSourceTemperature(double sourceTemperature);
    void resetSourceTemperature();

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
