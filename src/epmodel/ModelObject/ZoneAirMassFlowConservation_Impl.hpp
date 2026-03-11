/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEAIRMASSFLOWCONSERVATION_IMPL_HPP
#define EPMODEL_ZONEAIRMASSFLOWCONSERVATION_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneAirMassFlowConservation_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneAirMassFlowConservation_Impl() override = default;

      std::string adjustZoneMixingandReturnForAirMassFlowBalance() const;
      bool isAdjustZoneMixingandReturnForAirMassFlowBalanceDefaulted() const;

      std::string infiltrationBalancingMethod() const;
      bool isInfiltrationBalancingMethodDefaulted() const;

      std::string infiltrationBalancingZones() const;
      bool isInfiltrationBalancingZonesDefaulted() const;

      bool setAdjustZoneMixingandReturnForAirMassFlowBalance(const std::string& adjustZoneMixingandReturnForAirMassFlowBalance);
      void resetAdjustZoneMixingandReturnForAirMassFlowBalance();

      bool setInfiltrationBalancingMethod(const std::string& infiltrationBalancingMethod);
      void resetInfiltrationBalancingMethod();

      bool setInfiltrationBalancingZones(const std::string& infiltrationBalancingZones);
      void resetInfiltrationBalancingZones();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_ZONEAIRMASSFLOWCONSERVATION_IMPL_HPP
