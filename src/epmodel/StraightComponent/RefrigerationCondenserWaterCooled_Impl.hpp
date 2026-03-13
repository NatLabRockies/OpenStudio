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
      bool setRatedEffectiveTotalHeatRejectionRate(boost::optional<double> ratedEffectiveTotalHeatRejectionRate);
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
      bool setWaterDesignFlowRate(boost::optional<double> waterDesignFlowRate);
      void resetWaterDesignFlowRate();

      boost::optional<double> waterMaximumFlowRate() const;
      bool setWaterMaximumFlowRate(boost::optional<double> waterMaximumFlowRate);
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
      bool setCondenserRefrigerantOperatingChargeInventory(boost::optional<double> condenserRefrigerantOperatingChargeInventory);
      void resetCondenserRefrigerantOperatingChargeInventory();

      boost::optional<double> condensateReceiverRefrigerantInventory() const;
      bool setCondensateReceiverRefrigerantInventory(boost::optional<double> condensateReceiverRefrigerantInventory);
      void resetCondensateReceiverRefrigerantInventory();

      boost::optional<double> condensatePipingRefrigerantInventory() const;
      bool setCondensatePipingRefrigerantInventory(boost::optional<double> condensatePipingRefrigerantInventory);
      void resetCondensatePipingRefrigerantInventory();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_REFRIGERATIONCONDENSERWATERCOOLED_IMPL_HPP
