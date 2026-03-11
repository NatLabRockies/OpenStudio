/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONCONDENSERAIRCOOLED_IMPL_HPP
#define EPMODEL_REFRIGERATIONCONDENSERAIRCOOLED_IMPL_HPP

#include "ParentObject/ParentObject_Impl.hpp"

#include <string>

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API RefrigerationCondenserAirCooled_Impl : public ParentObject_Impl
    {
     public:
      using ParentObject_Impl::ParentObject_Impl;
      virtual ~RefrigerationCondenserAirCooled_Impl() override = default;

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
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
