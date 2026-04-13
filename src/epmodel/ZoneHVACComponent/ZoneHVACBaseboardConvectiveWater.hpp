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

    // Schema Alignment Notes:
    // - Status: Partial Parity. The direct EnergyPlus scalar surface and the canonical availability-schedule / heating-coil APIs are now
    //   present. epmodel preserves the canonical heating coil as a transient child view over the parent baseboard object because
    //   EnergyPlus does not persist a standalone coil object for this family.
    // - Canonical Counterpart: openstudio::model::ZoneHVACBaseboardConvectiveWater.
    // - Implemented Parity: `availabilitySchedule`, `heatingCoil`, the parent scalar fields, and the canonical thermal-zone attachment
    //   behavior are available on the wrapper. The transient child coil also preserves canonical plant-loop placement and traversal behavior.
    // - Documented Delta: The heating coil is transient in epmodel because EnergyPlus stores the real plant-side object identity on the
    //   parent `ZoneHVAC:Baseboard:Convective:Water` object rather than as a separate standalone coil object. epmodel also keeps the
    //   additive default constructor even though the canonical `openstudio::model` wrapper only exposes the schedule-and-coil constructor.
    // - Field/Storage Mapping: Availability schedule, water nodes, and the scalar sizing fields live directly on the EnergyPlus parent
    //   object. The transient child coil reads and writes those parent-owned fields rather than owning separate persisted storage.
    // - Evidence: `src/model/ZoneHVACBaseboardConvectiveWater.hpp`, `src/model/ZoneHVACBaseboardConvectiveWater.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACBaseboardConvectiveWater.cpp`, and `src/epmodel/test/ZoneHVACBaseboardConvectiveWater_GTest.cpp`.
    // - Remaining Parity Work: None beyond keeping the canonical parent and transient-child surfaces aligned with future canonical-model
    //   changes.
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
