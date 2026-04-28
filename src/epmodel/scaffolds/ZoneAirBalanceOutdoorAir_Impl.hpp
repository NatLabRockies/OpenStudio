/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_ZONEAIRBALANCEOUTDOORAIR_IMPL_HPP
#define EPMODEL_ZONEAIRBALANCEOUTDOORAIR_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneAirBalanceOutdoorAir_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneAirBalanceOutdoorAir_Impl() override = default;

      std::string airBalanceMethod() const;
      bool isAirBalanceMethodDefaulted() const;
      bool setAirBalanceMethod(const std::string& airBalanceMethod);
      void resetAirBalanceMethod();

      double inducedOutdoorAirDueToUnbalancedDuctLeakage() const;
      bool isInducedOutdoorAirDueToUnbalancedDuctLeakageDefaulted() const;
      bool setInducedOutdoorAirDueToUnbalancedDuctLeakage(double inducedOutdoorAirDueToUnbalancedDuctLeakage);
      void resetInducedOutdoorAirDueToUnbalancedDuctLeakage();

      std::vector<std::string> airBalanceMethodValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
