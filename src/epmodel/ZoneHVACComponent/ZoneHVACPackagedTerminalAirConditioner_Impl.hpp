/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACPACKAGEDTERMINALAIRCONDITIONER_IMPL_HPP
#define EPMODEL_ZONEHVACPACKAGEDTERMINALAIRCONDITIONER_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <utilities/idd/OS_ZoneHVAC_PackagedTerminalAirConditioner_FieldEnums.hxx>

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneHVACPackagedTerminalAirConditioner_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneHVACPackagedTerminalAirConditioner_Impl() override = default;

      boost::optional<double> supplyAirFlowRateDuringCoolingOperation() const;
      bool isSupplyAirFlowRateDuringCoolingOperationAutosized() const;
      bool setSupplyAirFlowRateDuringCoolingOperation(boost::optional<double> supplyAirFlowRateDuringCoolingOperation);
      void autosizeSupplyAirFlowRateDuringCoolingOperation();

      boost::optional<double> supplyAirFlowRateDuringHeatingOperation() const;
      bool isSupplyAirFlowRateDuringHeatingOperationAutosized() const;
      bool setSupplyAirFlowRateDuringHeatingOperation(boost::optional<double> supplyAirFlowRateDuringHeatingOperation);
      void autosizeSupplyAirFlowRateDuringHeatingOperation();

      boost::optional<double> supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
      bool isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const;
      bool setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(boost::optional<double> supplyAirFlowRateWhenNoCoolingorHeatingisNeeded);
      void resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
      void autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();

      bool noLoadSupplyAirFlowRateControlSetToLowSpeed() const;
      bool setNoLoadSupplyAirFlowRateControlSetToLowSpeed(bool noLoadSupplyAirFlowRateControlSetToLowSpeed);

      boost::optional<double> outdoorAirFlowRateDuringCoolingOperation() const;
      bool isOutdoorAirFlowRateDuringCoolingOperationAutosized() const;
      bool setOutdoorAirFlowRateDuringCoolingOperation(boost::optional<double> outdoorAirFlowRateDuringCoolingOperation);
      void autosizeOutdoorAirFlowRateDuringCoolingOperation();

      boost::optional<double> outdoorAirFlowRateDuringHeatingOperation() const;
      bool isOutdoorAirFlowRateDuringHeatingOperationAutosized() const;
      bool setOutdoorAirFlowRateDuringHeatingOperation(boost::optional<double> outdoorAirFlowRateDuringHeatingOperation);
      void autosizeOutdoorAirFlowRateDuringHeatingOperation();

      boost::optional<double> outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
      bool isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const;
      bool setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(boost::optional<double> outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded);
      void resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
      void autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();

      std::string fanPlacement() const;
      bool isFanPlacementDefaulted() const;
      bool setFanPlacement(const std::string& fanPlacement);
      void resetFanPlacement();

      boost::optional<double> autosizedSupplyAirFlowRateDuringCoolingOperation() const;
      boost::optional<double> autosizedSupplyAirFlowRateDuringHeatingOperation() const;
      boost::optional<double> autosizedSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
      boost::optional<double> autosizedOutdoorAirFlowRateDuringCoolingOperation() const;
      boost::optional<double> autosizedOutdoorAirFlowRateDuringHeatingOperation() const;
      boost::optional<double> autosizedOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
