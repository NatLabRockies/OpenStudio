/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONCONDENSEREVAPORATIVECOOLED_HPP
#define EPMODEL_REFRIGERATIONCONDENSEREVAPORATIVECOOLED_HPP

#include "EPModelAPI.hpp"
#include "ParentObject/ParentObject.hpp"

#include <string>
#include <vector>

namespace boost {
template <typename T>
class optional;
}
namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class RefrigerationCondenserEvaporativeCooled_Impl;
  }

  class EPMODEL_API RefrigerationCondenserEvaporativeCooled : public ParentObject
  {
   public:
    explicit RefrigerationCondenserEvaporativeCooled(const Model& model);

    virtual ~RefrigerationCondenserEvaporativeCooled() override = default;
    RefrigerationCondenserEvaporativeCooled(const RefrigerationCondenserEvaporativeCooled& other) = default;
    RefrigerationCondenserEvaporativeCooled(RefrigerationCondenserEvaporativeCooled&& other) = default;
    RefrigerationCondenserEvaporativeCooled& operator=(const RefrigerationCondenserEvaporativeCooled&) = default;
    RefrigerationCondenserEvaporativeCooled& operator=(RefrigerationCondenserEvaporativeCooled&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> fanSpeedControlTypeValues();

    // Schema Alignment Notes:
    // - API: preserves the openstudio::model RefrigerationCondenserEvaporativeCooled scalar accessors and maps them
    //   to the EnergyPlus Refrigeration:Condenser:EvaporativeCooled fields listed below.
    // - Field Mapping: ForwardTranslateRefrigerationCondenserEvaporativeCooled.cpp writes these scalars via
    //   Refrigeration_Condenser_EvaporativeCooledFields enums while omitting the relationship-like air inlet node,
    //   schedule, and tank references that remain outside the scalar-only scaffold.

    /** @name Getters */
    //@{
    double ratedEffectiveTotalHeatRejectionRate() const;

    double ratedSubcoolingTemperatureDifference() const;
    bool isRatedSubcoolingTemperatureDifferenceDefaulted() const;

    std::string fanSpeedControlType() const;
    bool isFanSpeedControlTypeDefaulted() const;

    double ratedFanPower() const;

    double minimumFanAirFlowRatio() const;
    bool isMinimumFanAirFlowRatioDefaulted() const;

    double approachTemperatureConstantTerm() const;
    bool isApproachTemperatureConstantTermDefaulted() const;

    double approachTemperatureCoefficient2() const;
    bool isApproachTemperatureCoefficient2Defaulted() const;

    double approachTemperatureCoefficient3() const;
    bool isApproachTemperatureCoefficient3Defaulted() const;

    double approachTemperatureCoefficient4() const;
    bool isApproachTemperatureCoefficient4Defaulted() const;

    double minimumCapacityFactor() const;
    bool isMinimumCapacityFactorDefaulted() const;

    double maximumCapacityFactor() const;
    bool isMaximumCapacityFactorDefaulted() const;

    boost::optional<double> ratedAirFlowRate() const;
    bool isRatedAirFlowRateDefaulted() const;
    bool isRatedAirFlowRateAutocalculated() const;

    double basinHeaterCapacity() const;
    bool isBasinHeaterCapacityDefaulted() const;

    double basinHeaterSetpointTemperature() const;
    bool isBasinHeaterSetpointTemperatureDefaulted() const;

    boost::optional<double> ratedWaterPumpPower() const;
    bool isRatedWaterPumpPowerDefaulted() const;
    bool isRatedWaterPumpPowerAutocalculated() const;

    std::string endUseSubcategory() const;
    bool isEndUseSubcategoryDefaulted() const;

    double condenserRefrigerantOperatingChargeInventory() const;
    bool isCondenserRefrigerantOperatingChargeInventoryDefaulted() const;

    double condensateReceiverRefrigerantInventory() const;
    bool isCondensateReceiverRefrigerantInventoryDefaulted() const;

    double condensatePipingRefrigerantInventory() const;
    bool isCondensatePipingRefrigerantInventoryDefaulted() const;
    //@}

    /** @name Setters */
    //@{
    bool setRatedEffectiveTotalHeatRejectionRate(double ratedEffectiveTotalHeatRejectionRate);

    bool setRatedSubcoolingTemperatureDifference(double ratedSubcoolingTemperatureDifference);
    void resetRatedSubcoolingTemperatureDifference();

    bool setFanSpeedControlType(const std::string& fanSpeedControlType);
    void resetFanSpeedControlType();

    bool setRatedFanPower(double ratedFanPower);

    bool setMinimumFanAirFlowRatio(double minimumFanAirFlowRatio);
    void resetMinimumFanAirFlowRatio();

    bool setApproachTemperatureConstantTerm(double approachTemperatureConstantTerm);
    void resetApproachTemperatureConstantTerm();

    bool setApproachTemperatureCoefficient2(double approachTemperatureCoefficient2);
    void resetApproachTemperatureCoefficient2();

    bool setApproachTemperatureCoefficient3(double approachTemperatureCoefficient3);
    void resetApproachTemperatureCoefficient3();

    bool setApproachTemperatureCoefficient4(double approachTemperatureCoefficient4);
    void resetApproachTemperatureCoefficient4();

    bool setMinimumCapacityFactor(double minimumCapacityFactor);
    void resetMinimumCapacityFactor();

    bool setMaximumCapacityFactor(double maximumCapacityFactor);
    void resetMaximumCapacityFactor();

    bool setRatedAirFlowRate(double ratedAirFlowRate);
    void resetRatedAirFlowRate();
    void autocalculateRatedAirFlowRate();

    bool setBasinHeaterCapacity(double basinHeaterCapacity);
    void resetBasinHeaterCapacity();

    bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);
    void resetBasinHeaterSetpointTemperature();

    bool setRatedWaterPumpPower(double ratedWaterPumpPower);
    void resetRatedWaterPumpPower();
    void autocalculateRatedWaterPumpPower();

    bool setEndUseSubcategory(const std::string& endUseSubcategory);
    void resetEndUseSubcategory();

    bool setCondenserRefrigerantOperatingChargeInventory(double condenserRefrigerantOperatingChargeInventory);
    void resetCondenserRefrigerantOperatingChargeInventory();

    bool setCondensateReceiverRefrigerantInventory(double condensateReceiverRefrigerantInventory);
    void resetCondensateReceiverRefrigerantInventory();

    bool setCondensatePipingRefrigerantInventory(double condensatePipingRefrigerantInventory);
    void resetCondensatePipingRefrigerantInventory();
    //@}

   protected:
    using ImplType = detail::RefrigerationCondenserEvaporativeCooled_Impl;

    explicit RefrigerationCondenserEvaporativeCooled(std::shared_ptr<detail::RefrigerationCondenserEvaporativeCooled_Impl> impl);

    friend class detail::RefrigerationCondenserEvaporativeCooled_Impl;
    friend class Model;
    friend class IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

   private:
    REGISTER_LOGGER("openstudio.epmodel.RefrigerationCondenserEvaporativeCooled");
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
