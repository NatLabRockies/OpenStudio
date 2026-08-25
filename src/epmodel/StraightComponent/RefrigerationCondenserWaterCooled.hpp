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

/** \brief A water-cooled refrigeration condenser.
 *
 * \par EnergyPlus object
 * \epobject{group-refrigeration.html#refrigerationcondenserwatercooled,Refrigeration:Condenser:WaterCooled}
 *
 * \par Important behavior
 * Water-outlet schedule, heat-rejection, condensing-temperature, flow, limit, inventory, and plant-node fields map directly to Refrigeration:Condenser:WaterCooled.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::RefrigerationCondenserWaterCooled</code>.
 *
 * \par Known limitations
 * The Model system() convenience and model-side reporting/fuel hooks are not available.
 */
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
