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

/** \brief A plant component that supplies a specified temperature.
 *
 * \par EnergyPlus object
 * \epobject{group-plant-equipment.html#plantcomponenttemperaturesource,PlantComponent:TemperatureSource}
 *
 * \par Important behavior
 * Design-flow, source-temperature, and source-temperature schedule fields map directly to PlantComponent:TemperatureSource.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::PlantComponentTemperatureSource</code>.
 *
 * \par Known limitations
 * Broader shared HVACComponent conveniences are not exposed.
 */
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
