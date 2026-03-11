/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONSECONDARYSYSTEM_IMPL_HPP
#define EPMODEL_REFRIGERATIONSECONDARYSYSTEM_IMPL_HPP

#include "ParentObject/ParentObject_Impl.hpp"

#include <boost/optional.hpp>
#include <string>

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API RefrigerationSecondarySystem_Impl : public ParentObject_Impl
    {
     public:
      using ParentObject_Impl::ParentObject_Impl;
      virtual ~RefrigerationSecondarySystem_Impl() override = default;

      std::string circulatingFluidName() const;
      bool setCirculatingFluidName(const std::string& circulatingFluidName);

      boost::optional<double> evaporatorCapacity() const;
      bool setEvaporatorCapacity(double evaporatorCapacity);
      void resetEvaporatorCapacity();

      boost::optional<double> evaporatorFlowRateforSecondaryFluid() const;
      bool setEvaporatorFlowRateforSecondaryFluid(double evaporatorFlowRateforSecondaryFluid);
      void resetEvaporatorFlowRateforSecondaryFluid();

      double evaporatorEvaporatingTemperature() const;
      bool setEvaporatorEvaporatingTemperature(double evaporatorEvaporatingTemperature);
      double evaporatorApproachTemperatureDifference() const;
      bool setEvaporatorApproachTemperatureDifference(double evaporatorApproachTemperatureDifference);

      boost::optional<double> evaporatorRangeTemperatureDifference() const;
      bool setEvaporatorRangeTemperatureDifference(double evaporatorRangeTemperatureDifference);
      void resetEvaporatorRangeTemperatureDifference();

      int numberofPumpsinLoop() const;
      bool isNumberofPumpsinLoopDefaulted() const;
      bool setNumberofPumpsinLoop(int numberofPumpsinLoop);
      void resetNumberofPumpsinLoop();

      boost::optional<double> totalPumpFlowRate() const;
      bool setTotalPumpFlowRate(double totalPumpFlowRate);
      void resetTotalPumpFlowRate();

      boost::optional<double> totalPumpPower() const;
      bool setTotalPumpPower(double totalPumpPower);
      void resetTotalPumpPower();

      boost::optional<double> totalPumpHead() const;
      bool setTotalPumpHead(double totalPumpHead);
      void resetTotalPumpHead();

      double phaseChangeCirculatingRate() const;
      bool isPhaseChangeCirculatingRateDefaulted() const;
      bool setPhaseChangeCirculatingRate(double phaseChangeCirculatingRate);
      void resetPhaseChangeCirculatingRate();

      std::string pumpDriveType() const;
      bool isPumpDriveTypeDefaulted() const;
      bool setPumpDriveType(const std::string& pumpDriveType);
      void resetPumpDriveType();

      double pumpMotorHeattoFluid() const;
      bool isPumpMotorHeattoFluidDefaulted() const;
      bool setPumpMotorHeattoFluid(double pumpMotorHeattoFluid);
      void resetPumpMotorHeattoFluid();

      double sumUADistributionPiping() const;
      bool isSumUADistributionPipingDefaulted() const;
      bool setSumUADistributionPiping(double sumUADistributionPiping);
      void resetSumUADistributionPiping();

      double sumUAReceiverSeparatorShell() const;
      bool isSumUAReceiverSeparatorShellDefaulted() const;
      bool setSumUAReceiverSeparatorShell(double sumUAReceiverSeparatorShell);
      void resetSumUAReceiverSeparatorShell();

      double evaporatorRefrigerantInventory() const;
      bool isEvaporatorRefrigerantInventoryDefaulted() const;
      bool setEvaporatorRefrigerantInventory(double evaporatorRefrigerantInventory);
      void resetEvaporatorRefrigerantInventory();

      std::string endUseSubcategory() const;
      bool isEndUseSubcategoryDefaulted() const;
      bool setEndUseSubcategory(const std::string& endUseSubcategory);
      void resetEndUseSubcategory();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_REFRIGERATIONSECONDARYSYSTEM_IMPL_HPP
