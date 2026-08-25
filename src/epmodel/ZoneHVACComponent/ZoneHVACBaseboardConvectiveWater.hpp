/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACBASEBOARDCONVECTIVEWATER_HPP
#define EPMODEL_ZONEHVACBASEBOARDCONVECTIVEWATER_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/CoilHeatingWaterBaseboard.hpp"
#include "ZoneHVACComponent/ZoneHVACComponent.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class ModelObject;
  class Schedule;
  class StraightComponent;
  class Model;
  namespace detail {
    class ZoneHVACBaseboardConvectiveWater_Impl;
  }

/** \brief A hot-water convective baseboard heater serving a thermal zone.
 *
 * \par EnergyPlus object
 * \epobject{group-radiative-convective-units.html#zonehvacbaseboardconvectivewater,ZoneHVAC:Baseboard:Convective:Water}
 *
 * \par Important behavior
 * heatingCoil() is a transient view over parent-owned water fields, and plant-loop attachment through it updates the parent water-node fields. EPModel also provides a default constructor.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::ZoneHVACBaseboardConvectiveWater</code>.
 * EPModel adds the design-capacity method/value surface and a no-argument
 * constructor; the Model wrapper instead requires its canonical coil inputs.
 *
 * \par Known limitations
 * The heating coil is not an independently persisted EnergyPlus object and must be used through its parent view; EPModel SQL sizing results are not available.
 */
  class EPMODEL_API ZoneHVACBaseboardConvectiveWater : public ZoneHVACComponent
  {
   public:
    explicit ZoneHVACBaseboardConvectiveWater(const Model& model);
    ZoneHVACBaseboardConvectiveWater(const Model& model, Schedule& availabilitySchedule, StraightComponent& heatingCoilBaseboard);

    virtual ~ZoneHVACBaseboardConvectiveWater() override = default;
    ZoneHVACBaseboardConvectiveWater(const ZoneHVACBaseboardConvectiveWater& other) = default;
    ZoneHVACBaseboardConvectiveWater(ZoneHVACBaseboardConvectiveWater&& other) = default;
    ZoneHVACBaseboardConvectiveWater& operator=(const ZoneHVACBaseboardConvectiveWater&) = default;
    ZoneHVACBaseboardConvectiveWater& operator=(ZoneHVACBaseboardConvectiveWater&&) = default;

    static IddObjectType iddObjectType();

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    StraightComponent heatingCoil() const;
    bool setHeatingCoil(const StraightComponent& heatingCoilBaseboard);

    std::vector<ModelObject> children() const;

    static std::vector<std::string> heatingDesignCapacityMethodValues();

    std::string heatingDesignCapacityMethod() const;
    bool setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod);

    boost::optional<double> heatingDesignCapacity() const;
    bool setHeatingDesignCapacity(double heatingDesignCapacity);
    bool isHeatingDesignCapacityAutosized() const;
    void autosizeHeatingDesignCapacity();

    double heatingDesignCapacityPerFloorArea() const;
    bool setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea);

    double fractionofAutosizedHeatingDesignCapacity() const;
    bool setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity);

    boost::optional<double> uFactorTimesAreaValue() const;
    bool setUFactorTimesAreaValue(double uFactorTimesAreaValue);
    bool isUFactorTimesAreaValueDefaulted() const;
    bool isUFactorTimesAreaValueAutosized() const;
    void resetUFactorTimesAreaValue();
    void autosizeUFactorTimesAreaValue();

    boost::optional<double> maximumWaterFlowRate() const;
    bool setMaximumWaterFlowRate(double maximumWaterFlowRate);
    bool isMaximumWaterFlowRateDefaulted() const;
    bool isMaximumWaterFlowRateAutosized() const;
    void resetMaximumWaterFlowRate();
    void autosizeMaximumWaterFlowRate();

    double convergenceTolerance() const;
    bool setConvergenceTolerance(double convergenceTolerance);
    bool isConvergenceToleranceDefaulted() const;
    void resetConvergenceTolerance();

   protected:
    using ImplType = detail::ZoneHVACBaseboardConvectiveWater_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACBaseboardConvectiveWater(std::shared_ptr<detail::ZoneHVACBaseboardConvectiveWater_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
