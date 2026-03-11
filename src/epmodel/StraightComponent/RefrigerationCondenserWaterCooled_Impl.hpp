/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONCONDENSERWATERCOOLED_IMPL_HPP
#define EPMODEL_REFRIGERATIONCONDENSERWATERCOOLED_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API RefrigerationCondenserWaterCooled_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~RefrigerationCondenserWaterCooled_Impl() override = default;
      RefrigerationCondenserWaterCooled_Impl(const RefrigerationCondenserWaterCooled_Impl&) = delete;
      RefrigerationCondenserWaterCooled_Impl(RefrigerationCondenserWaterCooled_Impl&&) = delete;
      RefrigerationCondenserWaterCooled_Impl& operator=(const RefrigerationCondenserWaterCooled_Impl&) = delete;
      RefrigerationCondenserWaterCooled_Impl& operator=(RefrigerationCondenserWaterCooled_Impl&&) = delete;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

      boost::optional<double> ratedEffectiveTotalHeatRejectionRate() const;
      double ratedCondensingTemperature() const;
      double ratedSubcoolingTemperatureDifference() const;
      bool isRatedSubcoolingTemperatureDifferenceDefaulted() const;
      double ratedWaterInletTemperature() const;
      std::string waterCooledLoopFlowType() const;
      bool isWaterCooledLoopFlowTypeDefaulted() const;
      boost::optional<double> waterDesignFlowRate() const;
      boost::optional<double> waterMaximumFlowRate() const;
      double waterMaximumWaterOutletTemperature() const;
      bool isWaterMaximumWaterOutletTemperatureDefaulted() const;
      double waterMinimumWaterInletTemperature() const;
      bool isWaterMinimumWaterInletTemperatureDefaulted() const;
      std::string endUseSubcategory() const;
      bool isEndUseSubcategoryDefaulted() const;
      boost::optional<double> condenserRefrigerantOperatingChargeInventory() const;
      boost::optional<double> condensateReceiverRefrigerantInventory() const;
      boost::optional<double> condensatePipingRefrigerantInventory() const;

      bool setRatedEffectiveTotalHeatRejectionRate(boost::optional<double> ratedEffectiveTotalHeatRejectionRate);
      void resetRatedEffectiveTotalHeatRejectionRate();
      bool setRatedCondensingTemperature(double ratedCondensingTemperature);
      bool setRatedSubcoolingTemperatureDifference(double ratedSubcoolingTemperatureDifference);
      void resetRatedSubcoolingTemperatureDifference();
      bool setRatedWaterInletTemperature(double ratedWaterInletTemperature);
      bool setWaterCooledLoopFlowType(const std::string& waterCooledLoopFlowType);
      void resetWaterCooledLoopFlowType();
      bool setWaterDesignFlowRate(boost::optional<double> waterDesignFlowRate);
      void resetWaterDesignFlowRate();
      bool setWaterMaximumFlowRate(boost::optional<double> waterMaximumFlowRate);
      void resetWaterMaximumFlowRate();
      bool setWaterMaximumWaterOutletTemperature(double waterMaximumWaterOutletTemperature);
      void resetWaterMaximumWaterOutletTemperature();
      bool setWaterMinimumWaterInletTemperature(double waterMinimumWaterInletTemperature);
      void resetWaterMinimumWaterInletTemperature();
      bool setEndUseSubcategory(const std::string& endUseSubcategory);
      void resetEndUseSubcategory();
      bool setCondenserRefrigerantOperatingChargeInventory(boost::optional<double> condenserRefrigerantOperatingChargeInventory);
      void resetCondenserRefrigerantOperatingChargeInventory();
      bool setCondensateReceiverRefrigerantInventory(boost::optional<double> condensateReceiverRefrigerantInventory);
      void resetCondensateReceiverRefrigerantInventory();
      bool setCondensatePipingRefrigerantInventory(boost::optional<double> condensatePipingRefrigerantInventory);
      void resetCondensatePipingRefrigerantInventory();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_REFRIGERATIONCONDENSERWATERCOOLED_IMPL_HPP
