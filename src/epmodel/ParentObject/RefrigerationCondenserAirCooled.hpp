/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONCONDENSERAIRCOOLED_HPP
#define EPMODEL_REFRIGERATIONCONDENSERAIRCOOLED_HPP

#include "EPModelAPI.hpp"
#include "ParentObject/ParentObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class RefrigerationCondenserAirCooled_Impl;
  }

  class EPMODEL_API RefrigerationCondenserAirCooled : public ParentObject
  {
   public:
    explicit RefrigerationCondenserAirCooled(const Model& model);

    virtual ~RefrigerationCondenserAirCooled() override = default;
    RefrigerationCondenserAirCooled(const RefrigerationCondenserAirCooled& other) = default;
    RefrigerationCondenserAirCooled(RefrigerationCondenserAirCooled&& other) = default;
    RefrigerationCondenserAirCooled& operator=(const RefrigerationCondenserAirCooled&) = default;
    RefrigerationCondenserAirCooled& operator=(RefrigerationCondenserAirCooled&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> condenserFanSpeedControlTypeValues();

    // Schema Alignment Notes:
    // - API: preserve openstudio::model::RefrigerationCondenserAirCooled scalar accessor names/signatures for each numeric/string field that maps directly to
    //   the EnergyPlus Refrigeration:Condenser:AirCooled fields listed below.
    // - Field Mapping: ForwardTranslateRefrigerationCondenserAirCooled.cpp demonstrates that the retained scalars (subcooling difference, fan control type,
    //   fan power, minimum flow ratio, end-use subcategory, and refrigerant inventory fields) write to Refrigeration_Condenser_AirCooledFields enums.
    // - Field Mapping: the rated effective total heat rejection rate curve and air inlet node/zone reference fields describe richer relationships and are intentionally
    //   excluded from this scalar-only scaffold.

    /** @name Getters */
    //@{
    double ratedSubcoolingTemperatureDifference() const;
    bool isRatedSubcoolingTemperatureDifferenceDefaulted() const;
    bool setRatedSubcoolingTemperatureDifference(double ratedSubcoolingTemperatureDifference);
    void resetRatedSubcoolingTemperatureDifference();

    std::string condenserFanSpeedControlType() const;
    bool isCondenserFanSpeedControlTypeDefaulted() const;
    bool setCondenserFanSpeedControlType(const std::string& condenserFanSpeedControlType);
    void resetCondenserFanSpeedControlType();

    double ratedFanPower() const;
    bool isRatedFanPowerDefaulted() const;
    bool setRatedFanPower(double ratedFanPower);
    void resetRatedFanPower();

    double minimumFanAirFlowRatio() const;
    bool isMinimumFanAirFlowRatioDefaulted() const;
    bool setMinimumFanAirFlowRatio(double minimumFanAirFlowRatio);
    void resetMinimumFanAirFlowRatio();

    std::string endUseSubcategory() const;
    bool isEndUseSubcategoryDefaulted() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);
    void resetEndUseSubcategory();

    double condenserRefrigerantOperatingChargeInventory() const;
    bool isCondenserRefrigerantOperatingChargeInventoryDefaulted() const;
    bool setCondenserRefrigerantOperatingChargeInventory(double condenserRefrigerantOperatingChargeInventory);
    void resetCondenserRefrigerantOperatingChargeInventory();

    double condensateReceiverRefrigerantInventory() const;
    bool isCondensateReceiverRefrigerantInventoryDefaulted() const;
    bool setCondensateReceiverRefrigerantInventory(double condensateReceiverRefrigerantInventory);
    void resetCondensateReceiverRefrigerantInventory();

    double condensatePipingRefrigerantInventory() const;
    bool isCondensatePipingRefrigerantInventoryDefaulted() const;
    bool setCondensatePipingRefrigerantInventory(double condensatePipingRefrigerantInventory);
    void resetCondensatePipingRefrigerantInventory();
    //@}

   protected:
    using ImplType = detail::RefrigerationCondenserAirCooled_Impl;

    explicit RefrigerationCondenserAirCooled(std::shared_ptr<detail::RefrigerationCondenserAirCooled_Impl> impl);

    friend class detail::RefrigerationCondenserAirCooled_Impl;
    friend class Model;
    friend class IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

   private:
    REGISTER_LOGGER("openstudio.epmodel.RefrigerationCondenserAirCooled");
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
