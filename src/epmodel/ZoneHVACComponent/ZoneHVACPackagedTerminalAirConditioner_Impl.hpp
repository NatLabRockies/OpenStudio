/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACPACKAGEDTERMINALAIRCONDITIONER_IMPL_HPP
#define EPMODEL_ZONEHVACPACKAGEDTERMINALAIRCONDITIONER_IMPL_HPP

#include "ZoneHVACComponent_Impl.hpp"

#include <utilities/idd/ZoneHVAC_PackagedTerminalAirConditioner_FieldEnums.hxx>

#include <boost/optional.hpp>
#include <vector>

namespace openstudio {
namespace epmodel {

  class HVACComponent;
  class ModelObject;

  namespace detail {

    class EPMODEL_API ZoneHVACPackagedTerminalAirConditioner_Impl : public ZoneHVACComponent_Impl
    {
     public:
      using ZoneHVACComponent_Impl::ZoneHVACComponent_Impl;
      virtual ~ZoneHVACPackagedTerminalAirConditioner_Impl() override = default;

      boost::optional<double> supplyAirFlowRateDuringCoolingOperation() const;
      bool setSupplyAirFlowRateDuringCoolingOperation(boost::optional<double> supplyAirFlowRateDuringCoolingOperation);
      bool isSupplyAirFlowRateDuringCoolingOperationAutosized() const;
      void autosizeSupplyAirFlowRateDuringCoolingOperation();
      boost::optional<double> autosizedSupplyAirFlowRateDuringCoolingOperation() const;

      boost::optional<double> supplyAirFlowRateDuringHeatingOperation() const;
      bool setSupplyAirFlowRateDuringHeatingOperation(boost::optional<double> supplyAirFlowRateDuringHeatingOperation);
      bool isSupplyAirFlowRateDuringHeatingOperationAutosized() const;
      void autosizeSupplyAirFlowRateDuringHeatingOperation();
      boost::optional<double> autosizedSupplyAirFlowRateDuringHeatingOperation() const;

      boost::optional<double> supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
      bool setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(boost::optional<double> supplyAirFlowRateWhenNoCoolingorHeatingisNeeded);
      void resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
      bool isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const;
      void autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
      boost::optional<double> autosizedSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const;

      bool noLoadSupplyAirFlowRateControlSetToLowSpeed() const;
      bool setNoLoadSupplyAirFlowRateControlSetToLowSpeed(bool noLoadSupplyAirFlowRateControlSetToLowSpeed);

      boost::optional<double> outdoorAirFlowRateDuringCoolingOperation() const;
      bool setOutdoorAirFlowRateDuringCoolingOperation(boost::optional<double> outdoorAirFlowRateDuringCoolingOperation);
      bool isOutdoorAirFlowRateDuringCoolingOperationAutosized() const;
      void autosizeOutdoorAirFlowRateDuringCoolingOperation();
      boost::optional<double> autosizedOutdoorAirFlowRateDuringCoolingOperation() const;

      boost::optional<double> outdoorAirFlowRateDuringHeatingOperation() const;
      bool setOutdoorAirFlowRateDuringHeatingOperation(boost::optional<double> outdoorAirFlowRateDuringHeatingOperation);
      bool isOutdoorAirFlowRateDuringHeatingOperationAutosized() const;
      void autosizeOutdoorAirFlowRateDuringHeatingOperation();
      boost::optional<double> autosizedOutdoorAirFlowRateDuringHeatingOperation() const;

      boost::optional<double> outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
      bool setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(boost::optional<double> outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded);
      void resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
      bool isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const;
      void autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
      boost::optional<double> autosizedOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const;

      std::string fanPlacement() const;
      bool isFanPlacementDefaulted() const;
      bool setFanPlacement(const std::string& fanPlacement);
      void resetFanPlacement();

      std::vector<ModelObject> children() const override;
      unsigned inletPort() const override;
      unsigned outletPort() const override;

      HVACComponent supplyAirFan() const;
      bool setSupplyAirFan(HVACComponent& fan);

      HVACComponent heatingCoil() const;
      bool setHeatingCoil(HVACComponent& heatingCoil);

      HVACComponent coolingCoil() const;
      bool setCoolingCoil(HVACComponent& coolingCoil);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
