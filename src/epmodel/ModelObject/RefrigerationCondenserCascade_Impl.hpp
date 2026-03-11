/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONCONDENSERCASCADE_IMPL_HPP
#define EPMODEL_REFRIGERATIONCONDENSERCASCADE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>
#include <string>

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API RefrigerationCondenserCascade_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~RefrigerationCondenserCascade_Impl() override = default;

      double ratedCondensingTemperature() const;
      double ratedApproachTemperatureDifference() const;
      bool isRatedApproachTemperatureDifferenceDefaulted() const;
      double ratedEffectiveTotalHeatRejectionRate() const;
      std::string condensingTemperatureControlType() const;
      bool isCondensingTemperatureControlTypeDefaulted() const;
      boost::optional<double> condenserRefrigerantOperatingChargeInventory() const;
      boost::optional<double> condensateReceiverRefrigerantInventory() const;
      boost::optional<double> condensatePipingRefrigerantInventory() const;

      bool setRatedCondensingTemperature(double ratedCondensingTemperature);
      bool setRatedApproachTemperatureDifference(double ratedApproachTemperatureDifference);
      void resetRatedApproachTemperatureDifference();
      bool setRatedEffectiveTotalHeatRejectionRate(double ratedEffectiveTotalHeatRejectionRate);
      bool setCondensingTemperatureControlType(const std::string& condensingTemperatureControlType);
      void resetCondensingTemperatureControlType();
      bool setCondenserRefrigerantOperatingChargeInventory(double condenserRefrigerantOperatingChargeInventory);
      void resetCondenserRefrigerantOperatingChargeInventory();
      bool setCondensateReceiverRefrigerantInventory(double condensateReceiverRefrigerantInventory);
      void resetCondensateReceiverRefrigerantInventory();
      bool setCondensatePipingRefrigerantInventory(double condensatePipingRefrigerantInventory);
      void resetCondensatePipingRefrigerantInventory();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_REFRIGERATIONCONDENSERCASCADE_IMPL_HPP
