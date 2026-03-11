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
    // - API: Preserve openstudio::model::RefrigerationCondenserWaterCooled scalar accessor names/signatures for this counterpart.
    // - Field Mapping: Each scalar maps to OS_Refrigeration_Condenser_WaterCooledFields tracked by translateRefrigerationCondenserWaterCooled.
    // - Field Mapping: Water outlet temperature schedule remains a relationship-only reference and is intentionally omitted from this scalar scaffold.
    // - TODO(parity): Follow-up passes should add loop topology helpers once StraightComponent plumbing parity completes.

    boost::optional<double> ratedEffectiveTotalHeatRejectionRate() const;
    bool setRatedEffectiveTotalHeatRejectionRate(double ratedEffectiveTotalHeatRejectionRate);
    void resetRatedEffectiveTotalHeatRejectionRate();

    double ratedCondensingTemperature() const;
    bool setRatedCondensingTemperature(double ratedCondensingTemperature);

    double ratedSubcoolingTemperatureDifference() const;
    bool isRatedSubcoolingTemperatureDifferenceDefaulted() const;
    bool setRatedSubcoolingTemperatureDifference(double ratedSubcoolingTemperatureDifference);
    void resetRatedSubcoolingTemperatureDifference();

    double ratedWaterInletTemperature() const;
    bool setRatedWaterInletTemperature(double ratedWaterInletTemperature);

    std::string waterCooledLoopFlowType() const;
    bool isWaterCooledLoopFlowTypeDefaulted() const;
    bool setWaterCooledLoopFlowType(const std::string& waterCooledLoopFlowType);
    void resetWaterCooledLoopFlowType();

    boost::optional<double> waterDesignFlowRate() const;
    bool setWaterDesignFlowRate(double waterDesignFlowRate);
    void resetWaterDesignFlowRate();

    boost::optional<double> waterMaximumFlowRate() const;
    bool setWaterMaximumFlowRate(double waterMaximumFlowRate);
    void resetWaterMaximumFlowRate();

    double waterMaximumWaterOutletTemperature() const;
    bool isWaterMaximumWaterOutletTemperatureDefaulted() const;
    bool setWaterMaximumWaterOutletTemperature(double waterMaximumWaterOutletTemperature);
    void resetWaterMaximumWaterOutletTemperature();

    double waterMinimumWaterInletTemperature() const;
    bool isWaterMinimumWaterInletTemperatureDefaulted() const;
    bool setWaterMinimumWaterInletTemperature(double waterMinimumWaterInletTemperature);
    void resetWaterMinimumWaterInletTemperature();

    std::string endUseSubcategory() const;
    bool isEndUseSubcategoryDefaulted() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);
    void resetEndUseSubcategory();

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
