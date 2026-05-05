/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRCONDITIONERVARIABLEREFRIGERANTFLOWFLUIDTEMPERATURECONTROL_IMPL_HPP
#define EPMODEL_AIRCONDITIONERVARIABLEREFRIGERANTFLOWFLUIDTEMPERATURECONTROL_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl() override = default;

      std::string refrigerantType() const;
      bool setRefrigerantType(const std::string& refrigerantType);

      boost::optional<double> ratedEvaporativeCapacity() const;
      bool isRatedEvaporativeCapacityAutosized() const;
      bool setRatedEvaporativeCapacity(double ratedEvaporativeCapacity);
      void autosizeRatedEvaporativeCapacity();

      double ratedCompressorPowerPerUnitofRatedEvaporativeCapacity() const;
      bool setRatedCompressorPowerPerUnitofRatedEvaporativeCapacity(double ratedCompressorPowerPerUnitofRatedEvaporativeCapacity);

      double minimumOutdoorAirTemperatureinCoolingMode() const;
      bool setMinimumOutdoorAirTemperatureinCoolingMode(double minimumOutdoorAirTemperatureinCoolingMode);

      double maximumOutdoorAirTemperatureinCoolingMode() const;
      bool setMaximumOutdoorAirTemperatureinCoolingMode(double maximumOutdoorAirTemperatureinCoolingMode);

      double minimumOutdoorAirTemperatureinHeatingMode() const;
      bool setMinimumOutdoorAirTemperatureinHeatingMode(double minimumOutdoorAirTemperatureinHeatingMode);

      double maximumOutdoorAirTemperatureinHeatingMode() const;
      bool setMaximumOutdoorAirTemperatureinHeatingMode(double maximumOutdoorAirTemperatureinHeatingMode);

      double referenceOutdoorUnitSuperheating() const;
      bool setReferenceOutdoorUnitSuperheating(double referenceOutdoorUnitSuperheating);

      double referenceOutdoorUnitSubcooling() const;
      bool setReferenceOutdoorUnitSubcooling(double referenceOutdoorUnitSubcooling);

      std::string refrigerantTemperatureControlAlgorithmforIndoorUnit() const;
      bool setRefrigerantTemperatureControlAlgorithmforIndoorUnit(const std::string& refrigerantTemperatureControlAlgorithmforIndoorUnit);

      double referenceEvaporatingTemperatureforIndoorUnit() const;
      bool setReferenceEvaporatingTemperatureforIndoorUnit(double referenceEvaporatingTemperatureforIndoorUnit);

      double referenceCondensingTemperatureforIndoorUnit() const;
      bool setReferenceCondensingTemperatureforIndoorUnit(double referenceCondensingTemperatureforIndoorUnit);

      double variableEvaporatingTemperatureMinimumforIndoorUnit() const;
      bool setVariableEvaporatingTemperatureMinimumforIndoorUnit(double variableEvaporatingTemperatureMinimumforIndoorUnit);

      double variableEvaporatingTemperatureMaximumforIndoorUnit() const;
      bool setVariableEvaporatingTemperatureMaximumforIndoorUnit(double variableEvaporatingTemperatureMaximumforIndoorUnit);

      double variableCondensingTemperatureMinimumforIndoorUnit() const;
      bool setVariableCondensingTemperatureMinimumforIndoorUnit(double variableCondensingTemperatureMinimumforIndoorUnit);

      double variableCondensingTemperatureMaximumforIndoorUnit() const;
      bool setVariableCondensingTemperatureMaximumforIndoorUnit(double variableCondensingTemperatureMaximumforIndoorUnit);

      double outdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity() const;
      bool setOutdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity(double outdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity);

      double outdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity() const;
      bool setOutdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity(double outdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity);

      double diameterofMainPipeConnectingOutdoorUnittotheFirstBranchJoint() const;
      bool setDiameterofMainPipeConnectingOutdoorUnittotheFirstBranchJoint(double diameterofMainPipeConnectingOutdoorUnittotheFirstBranchJoint);

      double lengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint() const;
      bool setLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint(double lengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint);

      double equivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint() const;
      bool setEquivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint(
        double equivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint);

      double heightDifferenceBetweenOutdoorUnitandIndoorUnits() const;
      bool setHeightDifferenceBetweenOutdoorUnitandIndoorUnits(double heightDifferenceBetweenOutdoorUnitandIndoorUnits);

      double mainPipeInsulationThickness() const;
      bool setMainPipeInsulationThickness(double mainPipeInsulationThickness);

      double mainPipeInsulationThermalConductivity() const;
      bool setMainPipeInsulationThermalConductivity(double mainPipeInsulationThermalConductivity);

      double crankcaseHeaterPowerperCompressor() const;
      bool setCrankcaseHeaterPowerperCompressor(double crankcaseHeaterPowerperCompressor);

      int numberofCompressors() const;
      bool setNumberofCompressors(int numberofCompressors);

      double ratioofCompressorSizetoTotalCompressorCapacity() const;
      bool setRatioofCompressorSizetoTotalCompressorCapacity(double ratioofCompressorSizetoTotalCompressorCapacity);

      double maximumOutdoorDryBulbTemperatureforCrankcaseHeater() const;
      bool setMaximumOutdoorDryBulbTemperatureforCrankcaseHeater(double maximumOutdoorDryBulbTemperatureforCrankcaseHeater);

      std::string defrostStrategy() const;
      bool setDefrostStrategy(const std::string& defrostStrategy);

      std::string defrostControl() const;
      bool setDefrostControl(const std::string& defrostControl);

      double defrostTimePeriodFraction() const;
      bool setDefrostTimePeriodFraction(double defrostTimePeriodFraction);

      boost::optional<double> resistiveDefrostHeaterCapacity() const;
      bool isResistiveDefrostHeaterCapacityAutosized() const;
      bool setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity);
      void autosizeResistiveDefrostHeaterCapacity();

      double maximumOutdoorDrybulbTemperatureforDefrostOperation() const;
      bool setMaximumOutdoorDrybulbTemperatureforDefrostOperation(double maximumOutdoorDrybulbTemperatureforDefrostOperation);

      double compressorMaximumDeltaPressure() const;
      bool setCompressorMaximumDeltaPressure(double compressorMaximumDeltaPressure);

      std::vector<std::string> refrigerantTypeValues() const;
      std::vector<std::string> refrigerantTemperatureControlAlgorithmforIndoorUnitValues() const;
      std::vector<std::string> defrostStrategyValues() const;
      std::vector<std::string> defrostControlValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
