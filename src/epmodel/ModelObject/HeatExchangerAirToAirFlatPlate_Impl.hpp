/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATEXCHANGERAIRTOAIRFLATPLATE_IMPL_HPP
#define EPMODEL_HEATEXCHANGERAIRTOAIRFLATPLATE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API HeatExchangerAirToAirFlatPlate_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~HeatExchangerAirToAirFlatPlate_Impl() override = default;

      boost::optional<std::string> flowArrangementType() const;
      bool setFlowArrangementType(const std::string& flowArrangementType);
      void resetFlowArrangementType();

      bool economizerLockout() const;
      bool setEconomizerLockout(bool economizerLockout);
      void resetEconomizerLockout();
      bool isEconomizerLockoutDefaulted() const;

      boost::optional<double> ratioofSupplytoSecondaryhAValues() const;
      bool setRatioofSupplytoSecondaryhAValues(double ratioofSupplytoSecondaryhAValues);
      void resetRatioofSupplytoSecondaryhAValues();

      boost::optional<double> nominalSupplyAirFlowRate() const;
      bool setNominalSupplyAirFlowRate(double nominalSupplyAirFlowRate);
      void resetNominalSupplyAirFlowRate();
      void autosizeNominalSupplyAirFlowRate();
      bool isNominalSupplyAirFlowRateAutosized() const;

      double nominalSupplyAirInletTemperature() const;
      bool setNominalSupplyAirInletTemperature(double nominalSupplyAirInletTemperature);

      double nominalSupplyAirOutletTemperature() const;
      bool setNominalSupplyAirOutletTemperature(double nominalSupplyAirOutletTemperature);

      boost::optional<double> nominalSecondaryAirFlowRate() const;
      bool setNominalSecondaryAirFlowRate(double nominalSecondaryAirFlowRate);
      void autosizeNominalSecondaryAirFlowRate();
      bool isNominalSecondaryAirFlowRateAutosized() const;

      double nominalSecondaryAirInletTemperature() const;
      bool setNominalSecondaryAirInletTemperature(double nominalSecondaryAirInletTemperature);

      boost::optional<double> nominalElectricPower() const;
      bool setNominalElectricPower(double nominalElectricPower);
      void resetNominalElectricPower();

     private:
      std::vector<std::string> flowArrangementTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
