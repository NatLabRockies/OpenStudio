/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONGASCOOLERAIRCOOLED_IMPL_HPP
#define EPMODEL_REFRIGERATIONGASCOOLERAIRCOOLED_IMPL_HPP

#include "ParentObject/ParentObject_Impl.hpp"

#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API RefrigerationGasCoolerAirCooled_Impl : public ParentObject_Impl
    {
     public:
      using ParentObject_Impl::ParentObject_Impl;
      virtual ~RefrigerationGasCoolerAirCooled_Impl() override = default;

      std::string gasCoolerFanSpeedControlType() const;
      bool isGasCoolerFanSpeedControlTypeDefaulted() const;
      bool setGasCoolerFanSpeedControlType(const std::string& gasCoolerFanSpeedControlType);
      void resetGasCoolerFanSpeedControlType();

      double ratedFanPower() const;
      bool isRatedFanPowerDefaulted() const;
      bool setRatedFanPower(double ratedFanPower);
      void resetRatedFanPower();

      double minimumFanAirFlowRatio() const;
      bool isMinimumFanAirFlowRatioDefaulted() const;
      bool setMinimumFanAirFlowRatio(double minimumFanAirFlowRatio);
      void resetMinimumFanAirFlowRatio();

      double transitionTemperature() const;
      bool isTransitionTemperatureDefaulted() const;
      bool setTransitionTemperature(double transitionTemperature);
      void resetTransitionTemperature();

      double transcriticalApproachTemperature() const;
      bool isTranscriticalApproachTemperatureDefaulted() const;
      bool setTranscriticalApproachTemperature(double transcriticalApproachTemperature);
      void resetTranscriticalApproachTemperature();

      double subcriticalTemperatureDifference() const;
      bool isSubcriticalTemperatureDifferenceDefaulted() const;
      bool setSubcriticalTemperatureDifference(double subcriticalTemperatureDifference);
      void resetSubcriticalTemperatureDifference();

      double minimumCondensingTemperature() const;
      bool isMinimumCondensingTemperatureDefaulted() const;
      bool setMinimumCondensingTemperature(double minimumCondensingTemperature);
      void resetMinimumCondensingTemperature();

      std::string endUseSubcategory() const;
      bool isEndUseSubcategoryDefaulted() const;
      bool setEndUseSubcategory(const std::string& endUseSubcategory);
      void resetEndUseSubcategory();

      double gasCoolerRefrigerantOperatingChargeInventory() const;
      bool isGasCoolerRefrigerantOperatingChargeInventoryDefaulted() const;
      bool setGasCoolerRefrigerantOperatingChargeInventory(double gasCoolerRefrigerantOperatingChargeInventory);
      void resetGasCoolerRefrigerantOperatingChargeInventory();

      double gasCoolerReceiverRefrigerantInventory() const;
      bool isGasCoolerReceiverRefrigerantInventoryDefaulted() const;
      bool setGasCoolerReceiverRefrigerantInventory(double gasCoolerReceiverRefrigerantInventory);
      void resetGasCoolerReceiverRefrigerantInventory();

      double gasCoolerOutletPipingRefrigerantInventory() const;
      bool isGasCoolerOutletPipingRefrigerantInventoryDefaulted() const;
      bool setGasCoolerOutletPipingRefrigerantInventory(double gasCoolerOutletPipingRefrigerantInventory);
      void resetGasCoolerOutletPipingRefrigerantInventory();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
