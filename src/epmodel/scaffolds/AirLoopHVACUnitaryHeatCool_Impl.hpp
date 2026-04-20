/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACUNITARYHEATCOOL_IMPL_HPP
#define EPMODEL_AIRLOOPHVACUNITARYHEATCOOL_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API AirLoopHVACUnitaryHeatCool_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~AirLoopHVACUnitaryHeatCool_Impl() override = default;

      boost::optional<double> maximumSupplyAirTemperature() const;
      bool setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature);
      bool isMaximumSupplyAirTemperatureDefaulted() const;
      bool isMaximumSupplyAirTemperatureAutosized() const;
      void resetMaximumSupplyAirTemperature();
      void autosizeMaximumSupplyAirTemperature();

      boost::optional<double> coolingSupplyAirFlowRate() const;
      bool setCoolingSupplyAirFlowRate(double coolingSupplyAirFlowRate);
      bool isCoolingSupplyAirFlowRateAutosized() const;
      void autosizeCoolingSupplyAirFlowRate();

      boost::optional<double> heatingSupplyAirFlowRate() const;
      bool setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate);
      bool isHeatingSupplyAirFlowRateAutosized() const;
      void autosizeHeatingSupplyAirFlowRate();

      boost::optional<double> noLoadSupplyAirFlowRate() const;
      bool setNoLoadSupplyAirFlowRate(double noLoadSupplyAirFlowRate);
      bool isNoLoadSupplyAirFlowRateAutosized() const;
      void resetNoLoadSupplyAirFlowRate();
      void autosizeNoLoadSupplyAirFlowRate();

      std::string supplyFanObjectType() const;
      bool setSupplyFanObjectType(const std::string& supplyFanObjectType);

      std::string fanPlacement() const;
      bool setFanPlacement(const std::string& fanPlacement);
      bool isFanPlacementDefaulted() const;
      void resetFanPlacement();

      std::string heatingCoilObjectType() const;
      bool setHeatingCoilObjectType(const std::string& heatingCoilObjectType);

      std::string coolingCoilObjectType() const;
      bool setCoolingCoilObjectType(const std::string& coolingCoilObjectType);

      std::string dehumidificationControlType() const;
      bool setDehumidificationControlType(const std::string& dehumidificationControlType);
      bool isDehumidificationControlTypeDefaulted() const;
      void resetDehumidificationControlType();

      boost::optional<std::string> reheatCoilObjectType() const;
      bool setReheatCoilObjectType(const std::string& reheatCoilObjectType);
      void resetReheatCoilObjectType();

      std::vector<std::string> supplyFanObjectTypeValues() const;
      std::vector<std::string> fanPlacementValues() const;
      std::vector<std::string> heatingCoilObjectTypeValues() const;
      std::vector<std::string> coolingCoilObjectTypeValues() const;
      std::vector<std::string> dehumidificationControlTypeValues() const;
      std::vector<std::string> reheatCoilObjectTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
