/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HUMIDIFIERSTEAMELECTRIC_IMPL_HPP
#define EPMODEL_HUMIDIFIERSTEAMELECTRIC_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {
  class Node;
  namespace detail {

    class EPMODEL_API HumidifierSteamElectric_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~HumidifierSteamElectric_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

      bool addToNode(Node& node) override;

      boost::optional<double> ratedCapacity() const;
      bool isRatedCapacityAutosized() const;
      bool setRatedCapacity(double ratedCapacity);
      void autosizeRatedCapacity();
      boost::optional<double> autosizedRatedCapacity() const;

      boost::optional<double> ratedPower() const;
      bool isRatedPowerAutosized() const;
      bool setRatedPower(double ratedPower);
      void resetRatedPower();
      void autosizeRatedPower();
      boost::optional<double> autosizedRatedPower() const;

      boost::optional<double> ratedFanPower() const;
      bool setRatedFanPower(double ratedFanPower);
      void resetRatedFanPower();

      boost::optional<double> standbyPower() const;
      bool setStandbyPower(double standbyPower);
      void resetStandbyPower();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
