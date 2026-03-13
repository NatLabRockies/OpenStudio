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
      bool setRatedCondensingTemperature(double ratedCondensingTemperature);

      double ratedApproachTemperatureDifference() const;
      bool isRatedApproachTemperatureDifferenceDefaulted() const;
      bool setRatedApproachTemperatureDifference(double ratedApproachTemperatureDifference);
      void resetRatedApproachTemperatureDifference();

      double ratedEffectiveTotalHeatRejectionRate() const;
      bool setRatedEffectiveTotalHeatRejectionRate(double ratedEffectiveTotalHeatRejectionRate);

      std::string condensingTemperatureControlType() const;
      bool isCondensingTemperatureControlTypeDefaulted() const;
      bool setCondensingTemperatureControlType(const std::string& condensingTemperatureControlType);
      void resetCondensingTemperatureControlType();

      boost::optional<double> condenserRefrigerantOperatingChargeInventory() const;
      bool setCondenserRefrigerantOperatingChargeInventory(double condenserRefrigerantOperatingChargeInventory);
      void resetCondenserRefrigerantOperatingChargeInventory();

      boost::optional<double> condensateReceiverRefrigerantInventory() const;
      bool setCondensateReceiverRefrigerantInventory(double condensateReceiverRefrigerantInventory);
      void resetCondensateReceiverRefrigerantInventory();

      boost::optional<double> condensatePipingRefrigerantInventory() const;
      bool setCondensatePipingRefrigerantInventory(double condensatePipingRefrigerantInventory);
      void resetCondensatePipingRefrigerantInventory();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_REFRIGERATIONCONDENSERCASCADE_IMPL_HPP
