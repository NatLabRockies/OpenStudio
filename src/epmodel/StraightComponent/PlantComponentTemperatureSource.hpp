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
  class Schedule;

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
    // - Status: Near Parity. The canonical temperature-source scalar surface, source-temperature schedule relationship, and inherited straight-component
    //   topology behavior are present.
    // - Canonical Counterpart: openstudio::model::PlantComponentTemperatureSource.
    // - Implemented Parity: The design-flow, temperature-specification, source-temperature, and source-temperature-schedule accessors now match the
    //   canonical wrapper alongside the inherited straight-component add/remove topology behavior.
    // - Documented Delta: epmodel still inherits the shared HVACComponent/StraightComponent base-surface gaps around broader canonical convenience such as
    //   `airLoopHVAC()` re-exposure and component/fuel-type reporting; this wrapper does not add type-local divergence.
    // - Field/Storage Mapping: These accessors map directly to the EnergyPlus `PlantComponent:TemperatureSource` scalar and schedule fields used by the
    //   forward translator.
    // - Evidence: `src/model/PlantComponentTemperatureSource.hpp`, `src/model/PlantComponentTemperatureSource.cpp`, and
    //   `src/energyplus/ForwardTranslator/ForwardTranslatePlantComponentTemperatureSource.cpp`.
    // - Remaining Parity Work: Close the remaining shared HVACComponent/StraightComponent base-surface gaps so this wrapper can inherit the missing
    //   canonical conveniences without local divergence.

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

    boost::optional<Schedule> sourceTemperatureSchedule() const;
    bool setSourceTemperatureSchedule(Schedule& schedule);
    void resetSourceTemperatureSchedule();

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
