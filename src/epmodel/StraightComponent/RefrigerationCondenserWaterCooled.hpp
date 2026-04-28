/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONCONDENSERWATERCOOLED_HPP
#define EPMODEL_REFRIGERATIONCONDENSERWATERCOOLED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;

  namespace detail {
    class RefrigerationCondenserWaterCooled_Impl;
  }

  class EPMODEL_API RefrigerationCondenserWaterCooled : public StraightComponent
  {
   public:
    explicit RefrigerationCondenserWaterCooled(const Model& model);

    virtual ~RefrigerationCondenserWaterCooled() override = default;
    RefrigerationCondenserWaterCooled(const RefrigerationCondenserWaterCooled& other) = default;
    RefrigerationCondenserWaterCooled(RefrigerationCondenserWaterCooled&& other) = default;
    RefrigerationCondenserWaterCooled& operator=(const RefrigerationCondenserWaterCooled&) = default;
    RefrigerationCondenserWaterCooled& operator=(RefrigerationCondenserWaterCooled&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> waterCooledLoopFlowTypeValues();

    // Schema Alignment Notes:
    // - Status: Parity with documented deltas. The canonical public wrapper surface is aligned, with only the parent-system convenience lookup and model-side impl hooks documented as deltas.
    // - Canonical Counterpart: openstudio::model::RefrigerationCondenserWaterCooled.
    // - Implemented Parity: Constructor defaults, plant-demand-only `addToNode(...)`, the water-outlet-temperature schedule helper, and the rated heat-rejection, condensing-temperature, subcooling, loop-flow, flow-rate, temperature-limit, and inventory wrapper accessors all match canonical behavior.
    // - Documented Delta: The canonical `system()` convenience lookup is still omitted because epmodel's `RefrigerationSystem` relationship surface has not yet been expanded to expose refrigeration-condenser ownership through typed APIs. Canonical model-side impl hooks such as output-variable reporting and fuel-type classification are also not mirrored as epmodel wrapper contracts today.
    // - Field/Storage Mapping: These accessors map directly to EnergyPlus `Refrigeration:Condenser:WaterCooled` fields, including the water-outlet schedule and plant node pointers used for persisted topology.
    // - Evidence: `src/model/RefrigerationCondenserWaterCooled.hpp`, `src/model/RefrigerationCondenserWaterCooled.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateRefrigerationCondenserWaterCooled.cpp`.
    // - Remaining Parity Work: Add the canonical `system()` convenience lookup once epmodel's refrigeration-system relationship APIs are in place, and revisit the omitted model-side impl hooks only if epmodel grows equivalent wrapper-facing reporting or fuel-classification interfaces.

    boost::optional<double> ratedEffectiveTotalHeatRejectionRate() const;
    bool setRatedEffectiveTotalHeatRejectionRate(double ratedEffectiveTotalHeatRejectionRate);
    void resetRatedEffectiveTotalHeatRejectionRate();

    double ratedCondensingTemperature() const;
    bool setRatedCondensingTemperature(double ratedCondensingTemperature);

    double ratedSubcoolingTemperatureDifference() const;
    bool setRatedSubcoolingTemperatureDifference(double ratedSubcoolingTemperatureDifference);
    void resetRatedSubcoolingTemperatureDifference();
    bool isRatedSubcoolingTemperatureDifferenceDefaulted() const;

    double ratedWaterInletTemperature() const;
    bool setRatedWaterInletTemperature(double ratedWaterInletTemperature);

    std::string waterCooledLoopFlowType() const;
    bool setWaterCooledLoopFlowType(const std::string& waterCooledLoopFlowType);
    void resetWaterCooledLoopFlowType();
    bool isWaterCooledLoopFlowTypeDefaulted() const;

    boost::optional<Schedule> waterOutletTemperatureSchedule() const;
    bool setWaterOutletTemperatureSchedule(Schedule& waterOutletTemperatureSchedule);
    void resetWaterOutletTemperatureSchedule();

    boost::optional<double> waterDesignFlowRate() const;
    bool setWaterDesignFlowRate(double waterDesignFlowRate);
    void resetWaterDesignFlowRate();

    boost::optional<double> waterMaximumFlowRate() const;
    bool setWaterMaximumFlowRate(double waterMaximumFlowRate);
    void resetWaterMaximumFlowRate();

    double waterMaximumWaterOutletTemperature() const;
    bool setWaterMaximumWaterOutletTemperature(double waterMaximumWaterOutletTemperature);
    void resetWaterMaximumWaterOutletTemperature();
    bool isWaterMaximumWaterOutletTemperatureDefaulted() const;

    double waterMinimumWaterInletTemperature() const;
    bool setWaterMinimumWaterInletTemperature(double waterMinimumWaterInletTemperature);
    void resetWaterMinimumWaterInletTemperature();
    bool isWaterMinimumWaterInletTemperatureDefaulted() const;

    std::string endUseSubcategory() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);
    void resetEndUseSubcategory();
    bool isEndUseSubcategoryDefaulted() const;

    boost::optional<double> condenserRefrigerantOperatingChargeInventory() const;
    bool setCondenserRefrigerantOperatingChargeInventory(double condenserRefrigerantOperatingChargeInventory);
    void resetCondenserRefrigerantOperatingChargeInventory();

    boost::optional<double> condensateReceiverRefrigerantInventory() const;
    bool setCondensateReceiverRefrigerantInventory(double condensateReceiverRefrigerantInventory);
    void resetCondensateReceiverRefrigerantInventory();

    boost::optional<double> condensatePipingRefrigerantInventory() const;
    bool setCondensatePipingRefrigerantInventory(double condensatePipingRefrigerantInventory);
    void resetCondensatePipingRefrigerantInventory();

   protected:
    using ImplType = detail::RefrigerationCondenserWaterCooled_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit RefrigerationCondenserWaterCooled(std::shared_ptr<detail::RefrigerationCondenserWaterCooled_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_REFRIGERATIONCONDENSERWATERCOOLED_HPP
