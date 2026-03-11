/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACHYBRIDUNITARYHVAC_IMPL_HPP
#define EPMODEL_ZONEHVACHYBRIDUNITARYHVAC_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneHVACHybridUnitaryHVAC_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneHVACHybridUnitaryHVAC_Impl() override = default;

      std::string methodToChooseControlledInputsAndPartRuntimeFraction() const;
      bool isMethodToChooseControlledInputsAndPartRuntimeFractionDefaulted() const;
      bool setMethodToChooseControlledInputsAndPartRuntimeFraction(const std::string& method);
      void resetMethodToChooseControlledInputsAndPartRuntimeFraction();
      std::vector<std::string> methodToChooseControlledInputsAndPartRuntimeFractionValues() const;

      boost::optional<double> systemMaximumSupplyAirFlowRate() const;
      bool setSystemMaximumSupplyAirFlowRate(double systemMaximumSupplyAirFlowRate);
      void resetSystemMaximumSupplyAirFlowRate();

      boost::optional<double> externalStaticPressureAtSystemMaximumSupplyAirFlowRate() const;
      bool setExternalStaticPressureAtSystemMaximumSupplyAirFlowRate(double externalStaticPressureAtSystemMaximumSupplyAirFlowRate);
      void resetExternalStaticPressureAtSystemMaximumSupplyAirFlowRate();

      std::string fanHeatIncludedInLookupTables() const;
      bool isFanHeatIncludedInLookupTablesDefaulted() const;
      bool setFanHeatIncludedInLookupTables(const std::string& fanHeatIncludedInLookupTables);
      void resetFanHeatIncludedInLookupTables();
      std::vector<std::string> fanHeatIncludedInLookupTablesValues() const;

      std::string fanHeatGainLocation() const;
      bool isFanHeatGainLocationDefaulted() const;
      bool setFanHeatGainLocation(const std::string& fanHeatGainLocation);
      void resetFanHeatGainLocation();
      std::vector<std::string> fanHeatGainLocationValues() const;

      double fanHeatInAirStreamFraction() const;
      bool setFanHeatInAirStreamFraction(double fanHeatInAirStreamFraction);
      bool isFanHeatInAirStreamFractionDefaulted() const;
      void resetFanHeatInAirStreamFraction();

      double scalingFactor() const;
      bool setScalingFactor(double scalingFactor);
      bool isScalingFactorDefaulted() const;
      void resetScalingFactor();

      double minimumTimeBetweenModeChange() const;
      bool setMinimumTimeBetweenModeChange(double minimumTimeBetweenModeChange);
      bool isMinimumTimeBetweenModeChangeDefaulted() const;
      void resetMinimumTimeBetweenModeChange();

      std::string firstFuelType() const;
      bool isFirstFuelTypeDefaulted() const;
      bool setFirstFuelType(const std::string& firstFuelType);
      void resetFirstFuelType();
      std::vector<std::string> firstFuelTypeValues() const;

      std::string secondFuelType() const;
      bool isSecondFuelTypeDefaulted() const;
      bool setSecondFuelType(const std::string& secondFuelType);
      void resetSecondFuelType();
      std::vector<std::string> secondFuelTypeValues() const;

      std::string thirdFuelType() const;
      bool isThirdFuelTypeDefaulted() const;
      bool setThirdFuelType(const std::string& thirdFuelType);
      void resetThirdFuelType();
      std::vector<std::string> thirdFuelTypeValues() const;

      std::string objectiveFunctionToMinimize() const;
      bool isObjectiveFunctionToMinimizeDefaulted() const;
      bool setObjectiveFunctionToMinimize(const std::string& objectiveFunctionToMinimize);
      void resetObjectiveFunctionToMinimize();
      std::vector<std::string> objectiveFunctionToMinimizeValues() const;

      double mode0OutdoorAirFraction() const;
      bool setMode0OutdoorAirFraction(double mode0OutdoorAirFraction);
      bool isMode0OutdoorAirFractionDefaulted() const;
      void resetMode0OutdoorAirFraction();

      double mode0SupplyAirMassFlowRateRatio() const;
      bool setMode0SupplyAirMassFlowRateRatio(double mode0SupplyAirMassFlowRateRatio);
      bool isMode0SupplyAirMassFlowRateRatioDefaulted() const;
      void resetMode0SupplyAirMassFlowRateRatio();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
