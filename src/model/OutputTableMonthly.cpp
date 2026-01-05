/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OutputTableMonthly.hpp"
#include "OutputTableMonthly_Impl.hpp"

#include "ModelExtensibleGroup.hpp"

#include "../utilities/core/Assert.hpp"

#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/OS_Output_Table_Monthly_FieldEnums.hxx>

#include <fmt/format.h>
#include <fmt/ranges.h>

namespace openstudio {
namespace model {

  MonthlyVariableGroup::MonthlyVariableGroup(std::string variableOrMeterName, std::string aggregationType)
    : m_variableOrMeterName(std::move(variableOrMeterName)), m_aggregationType(std::move(aggregationType)) {
    if (m_variableOrMeterName.empty()) {
      LOG_AND_THROW("Variable or Meter Name can't be empty");
    }
    if (!OutputTableMonthly::isAggregationTypeValid(m_aggregationType)) {
      LOG_AND_THROW(fmt::format("Invalid aggregation type '{}': {}", m_aggregationType, OutputTableMonthly::aggregationTypeValues()));
    }
  }

  std::string MonthlyVariableGroup::variableOrMeterName() const {
    return m_variableOrMeterName;
  }

  std::string MonthlyVariableGroup::aggregationType() const {
    return m_aggregationType;
  }

  bool MonthlyVariableGroup::operator==(const MonthlyVariableGroup& other) const {
    return openstudio::istringEqual(variableOrMeterName(), other.variableOrMeterName())
           && openstudio::istringEqual(aggregationType(), other.aggregationType());
  }

  bool MonthlyVariableGroup::operator!=(const MonthlyVariableGroup& other) const {
    return (!operator==(other));
  }

  bool MonthlyVariableGroup::isAggregationTypeAdvanced() const {
    return OutputTableMonthly::isAggregationTypeAdvanced(m_aggregationType);
  }

  std::ostream& operator<<(std::ostream& out, const openstudio::model::MonthlyVariableGroup& monthlyVariableGroup) {
    out << "(Output Variable or Meter = '" << monthlyVariableGroup.variableOrMeterName() << "', Aggregation Type = '"
        << monthlyVariableGroup.aggregationType() << "')";
    return out;
  }

  namespace detail {

    const std::vector<std::pair<std::string, std::vector<MonthlyVariableGroup>>>& OutputTableMonthly_Impl::standardReports() {
      // Generated from this python code, https://github.com/NREL/EnergyPlus/blob/v25.1.0-IOFreeze/datasets/StandardReports.idf
      //
      // ```python
      // def generate_report(standard_report_name: str):
      //     wo = w.getObjectByTypeAndName('Output:Table:Monthly', standard_report_name).get()
      //     s = f'  {{"{standard_report_name}",\n    {{\n'
      //     for eg in wo.extensibleGroups():
      //         s += f'      {{"{eg.getString(0).get()}", "{eg.getString(1).get()}"}},\n'
      //     s += "    }\n  },"
      //     return s
      //
      // w = openstudio.Workspace.load('/path/to/EnergyPlus/datasets/StandardReports.idf').get()
      // reports = sorted([wo for wo in w.getObjectsByType('Output:Table:Monthly')], key=lambda wo: wo.nameString())
      //
      // print("static std::vector<std::pair<std::string, std::vector<MonthlyVariableGroup>>> standard_reports{")
      //
      // for report in reports:
      //     print(generate_report(report.nameString()))
      //
      // print("};")
      // ```

      static std::vector<std::pair<std::string, std::vector<MonthlyVariableGroup>>> standard_reports{
        {"Air Loop System Component Energy Use",
         {
           {"Air System Fan Electricity Energy", "SumOrAverage"},
           {"Air System Heating Coil Hot Water Energy", "SumOrAverage"},
           {"Air System Cooling Coil Chilled Water Energy", "SumOrAverage"},
           {"Air System DX Heating Coil Electricity Energy", "SumOrAverage"},
           {"Air System DX Cooling Coil Electricity Energy", "SumOrAverage"},
           {"Air System Heating Coil Electricity Energy", "SumOrAverage"},
           {"Air System Heating Coil NaturalGas Energy", "SumOrAverage"},
           {"Air System Heating Coil Steam Energy", "SumOrAverage"},
           {"Air System Humidifier Electricity Energy", "SumOrAverage"},
           {"Air System Evaporative Cooler Electricity Energy", "SumOrAverage"},
           {"Air System Desiccant Dehumidifier Electricity Energy", "SumOrAverage"},
         }},
        {"Air Loop System Component Loads",
         {
           {"Air System Fan Air Heating Energy", "SumOrAverage"},
           {"Air System Cooling Coil Total Cooling Energy", "SumOrAverage"},
           {"Air System Heating Coil Total Heating Energy", "SumOrAverage"},
           {"Air System Heat Exchanger Total Heating Energy", "SumOrAverage"},
           {"Air System Heat Exchanger Total Cooling Energy", "SumOrAverage"},
           {"Air System Humidifier Total Heating Energy", "SumOrAverage"},
           {"Air System Evaporative Cooler Total Cooling Energy", "SumOrAverage"},
           {"Air System Desiccant Dehumidifier Total Cooling Energy", "SumOrAverage"},
         }},
        {"Air Loop System Energy and Water Use",
         {
           {"Air System Hot Water Energy", "SumOrAverage"},
           {"Air System Steam Energy", "SumOrAverage"},
           {"Air System Chilled Water Energy", "SumOrAverage"},
           {"Air System Electricity Energy", "SumOrAverage"},
           {"Air System NaturalGas Energy", "SumOrAverage"},
           {"Air System Water Volume", "SumOrAverage"},
         }},
        {"Average Outdoor Conditions",
         {
           {"Site Outdoor Air Drybulb Temperature", "SumOrAverage"},
           {"Site Outdoor Air Wetbulb Temperature", "SumOrAverage"},
           {"Site Outdoor Air Dewpoint Temperature", "SumOrAverage"},
           {"Site Wind Speed", "SumOrAverage"},
           {"Site Sky Temperature", "SumOrAverage"},
           {"Site Diffuse Solar Radiation Rate per Area", "SumOrAverage"},
           {"Site Direct Solar Radiation Rate per Area", "SumOrAverage"},
           {"Raining", "SumOrAverage"},
         }},
        {"Boiler Report",
         {
           {"Boiler Heating Energy", "SumOrAverage"},
           {"Boiler NaturalGas Energy", "SumOrAverage"},
           {"Boiler Heating Energy", "HoursNonZero"},
           {"Boiler Heating Rate", "Maximum"},
           {"Boiler NaturalGas Rate", "Maximum"},
           {"Boiler Inlet Temperature", "SumOrAverage"},
           {"Boiler Outlet Temperature", "SumOrAverage"},
           {"Boiler Mass Flow Rate", "SumOrAverage"},
           {"Boiler Ancillary Electricity Rate", "SumOrAverage"},
         }},
        {"Chiller Report",
         {
           {"Chiller Electricity Energy", "SumOrAverage"},
           {"Chiller Electricity Rate", "Maximum"},
           {"Chiller Electricity Energy", "HoursNonZero"},
           {"Chiller Evaporator Cooling Energy", "SumOrAverage"},
           {"Chiller Condenser Heat Transfer Energy", "SumOrAverage"},
           {"Chiller COP", "SumOrAverage"},
           {"Chiller COP", "Minimum"},
           {"Chiller COP", "Maximum"},
         }},
        {"Coil Report",
         {
           {"Heating Coil Heating Energy", "SumOrAverage"},
           {"Heating Coil Heating Rate", "Maximum"},
           {"Cooling Coil Total Cooling Energy", "SumOrAverage"},
           {"Cooling Coil Sensible Cooling Energy", "SumOrAverage"},
           {"Cooling Coil Total Cooling Rate", "Maximum"},
           {"Cooling Coil Sensible Cooling Rate", "ValueWhenMaximumOrMinimum"},
           {"Cooling Coil Wetted Area Fraction", "SumOrAverage"},
         }},
        {"Comfort Report - Simple 55",
         {
           {"Zone Thermal Comfort ASHRAE 55 Simple Model Summer Clothes Not Comfortable Time", "HoursNonZero"},
           {"Zone Mean Air Temperature", "SumOrAverageDuringHoursShown"},
           {"Zone Thermal Comfort ASHRAE 55 Simple Model Winter Clothes Not Comfortable Time", "HoursNonZero"},
           {"Zone Mean Air Temperature", "SumOrAverageDuringHoursShown"},
           {"Zone Thermal Comfort ASHRAE 55 Simple Model Summer or Winter Clothes Not Comfortable Time", "HoursNonZero"},
           {"Zone Mean Air Temperature", "SumOrAverageDuringHoursShown"},
         }},
        {"Cond Loop Demand Report",
         {
           {"Plant Supply Side Cooling Demand Rate", "SumOrAverage"},
           {"Plant Supply Side Cooling Demand Rate", "Maximum"},
           {"Plant Supply Side Inlet Temperature", "ValueWhenMaximumOrMinimum"},
           {"Plant Supply Side Outlet Temperature", "ValueWhenMaximumOrMinimum"},
           {"Plant Supply Side Heating Demand Rate", "SumOrAverage"},
           {"Plant Supply Side Heating Demand Rate", "Maximum"},
         }},
        {"DX Report",
         {
           {"Cooling Coil Total Cooling Energy", "SumOrAverage"},
           {"Cooling Coil Electricity Energy", "SumOrAverage"},
           {"Cooling Coil Total Cooling Energy", "HoursNonZero"},
           {"Cooling Coil Sensible Cooling Energy", "SumOrAverage"},
           {"Cooling Coil Latent Cooling Energy", "SumOrAverage"},
           {"Cooling Coil Crankcase Heater Electricity Energy", "SumOrAverage"},
           {"Cooling Coil Runtime Fraction", "Maximum"},
           {"Cooling Coil Runtime Fraction", "Minimum"},
           {"Cooling Coil Total Cooling Rate", "Maximum"},
           {"Cooling Coil Sensible Cooling Rate", "Maximum"},
           {"Cooling Coil Latent Cooling Rate", "Maximum"},
           {"Cooling Coil Electricity Rate", "Maximum"},
           {"Cooling Coil Crankcase Heater Electricity Rate", "Maximum"},
         }},
        {"Daylighting Report",
         {
           {"Site Exterior Beam Normal Illuminance", "HoursNonZero"},
           {"Daylighting Lighting Power Multiplier", "SumOrAverageDuringHoursShown"},
           {"Daylighting Lighting Power Multiplier", "MinimumDuringHoursShown"},
           {"Daylighting Reference Point 1 Illuminance", "SumOrAverageDuringHoursShown"},
           {"Daylighting Reference Point 1 Glare Index", "SumOrAverageDuringHoursShown"},
           {"Daylighting Reference Point 2 Illuminance", "SumOrAverageDuringHoursShown"},
           {"Daylighting Reference Point 2 Glare Index", "SumOrAverageDuringHoursShown"},
         }},
        {"Electric Components of Peak Demand",
         {
           {"Electricity:Facility", "Maximum"},
           {"InteriorLights:Electricity", "ValueWhenMaximumOrMinimum"},
           {"InteriorEquipment:Electricity", "ValueWhenMaximumOrMinimum"},
           {"ExteriorLights:Electricity", "ValueWhenMaximumOrMinimum"},
           {"ExteriorEquipment:Electricity", "ValueWhenMaximumOrMinimum"},
           {"Fans:Electricity", "ValueWhenMaximumOrMinimum"},
           {"Pumps:Electricity", "ValueWhenMaximumOrMinimum"},
           {"Heating:Electricity", "ValueWhenMaximumOrMinimum"},
           {"Cooling:Electricity", "ValueWhenMaximumOrMinimum"},
           {"HeatRejection:Electricity", "ValueWhenMaximumOrMinimum"},
         }},
        {"End-Use Energy Consumption - Coal",
         {
           {"ExteriorEquipment:Coal", "SumOrAverage"},
           {"Heating:Coal", "SumOrAverage"},
           {"WaterSystems:Coal", "SumOrAverage"},
         }},
        {"End-Use Energy Consumption - Diesel",
         {
           {"ExteriorEquipment:Diesel", "SumOrAverage"},
           {"Cooling:Diesel", "SumOrAverage"},
           {"Heating:Diesel", "SumOrAverage"},
           {"WaterSystems:Diesel", "SumOrAverage"},
           {"Cogeneration:Diesel", "SumOrAverage"},
         }},
        {"End-Use Energy Consumption - Electricity",
         {
           {"InteriorLights:Electricity", "SumOrAverage"},
           {"ExteriorLights:Electricity", "SumOrAverage"},
           {"InteriorEquipment:Electricity", "SumOrAverage"},
           {"ExteriorEquipment:Electricity", "SumOrAverage"},
           {"Fans:Electricity", "SumOrAverage"},
           {"Pumps:Electricity", "SumOrAverage"},
           {"Heating:Electricity", "SumOrAverage"},
           {"Cooling:Electricity", "SumOrAverage"},
           {"HeatRejection:Electricity", "SumOrAverage"},
           {"Humidifier:Electricity", "SumOrAverage"},
           {"HeatRecovery:Electricity", "SumOrAverage"},
           {"WaterSystems:Electricity", "SumOrAverage"},
           {"Cogeneration:Electricity", "SumOrAverage"},
         }},
        {"End-Use Energy Consumption - Fuel Oil",
         {
           {"ExteriorEquipment:FuelOilNo1", "SumOrAverage"},
           {"Cooling:FuelOilNo1", "SumOrAverage"},
           {"Heating:FuelOilNo1", "SumOrAverage"},
           {"WaterSystems:FuelOilNo1", "SumOrAverage"},
           {"Cogeneration:FuelOilNo1", "SumOrAverage"},
           {"ExteriorEquipment:FuelOilNo2", "SumOrAverage"},
           {"Cooling:FuelOilNo2", "SumOrAverage"},
           {"Heating:FuelOilNo2", "SumOrAverage"},
           {"WaterSystems:FuelOilNo2", "SumOrAverage"},
           {"Cogeneration:FuelOilNo2", "SumOrAverage"},
         }},
        {"End-Use Energy Consumption - Gasoline",
         {
           {"ExteriorEquipment:Gasoline", "SumOrAverage"},
           {"Cooling:Gasoline", "SumOrAverage"},
           {"Heating:Gasoline", "SumOrAverage"},
           {"WaterSystems:Gasoline", "SumOrAverage"},
           {"Cogeneration:Gasoline", "SumOrAverage"},
         }},
        {"End-Use Energy Consumption - Natural Gas",
         {
           {"InteriorEquipment:NaturalGas", "SumOrAverage"},
           {"ExteriorEquipment:NaturalGas", "SumOrAverage"},
           {"Heating:NaturalGas", "SumOrAverage"},
           {"Cooling:NaturalGas", "SumOrAverage"},
           {"WaterSystems:NaturalGas", "SumOrAverage"},
           {"Cogeneration:NaturalGas", "SumOrAverage"},
         }},
        {"End-Use Energy Consumption - Propane",
         {
           {"ExteriorEquipment:Propane", "SumOrAverage"},
           {"Cooling:Propane", "SumOrAverage"},
           {"Heating:Propane", "SumOrAverage"},
           {"WaterSystems:Propane", "SumOrAverage"},
           {"Cogeneration:Propane", "SumOrAverage"},
         }},
        {"Energy Consumption  - Purchased Heating & Cooling",
         {
           {"DistrictCooling:Facility", "SumOrAverage"},
           {"DistrictCooling:Facility", "Maximum"},
           {"DistrictHeatingWater:Facility", "SumOrAverage"},
           {"DistrictHeatingWater:Facility", "Maximum"},
         }},
        {"Energy Consumption - Coal & Gasoline",
         {
           {"COAL:Facility", "SumOrAverage"},
           {"COAL:Facility", "Maximum"},
           {"GASOLINE:Facility", "SumOrAverage"},
           {"GASOLINE:Facility", "Maximum"},
         }},
        {"Energy Consumption - Diesel & Fuel Oil",
         {
           {"Diesel:Facility", "SumOrAverage"},
           {"Diesel:Facility", "Maximum"},
           {"FuelOilNo1:Facility", "SumOrAverage"},
           {"FuelOilNo1:Facility", "Maximum"},
           {"FuelOilNo2:Facility", "SumOrAverage"},
           {"FuelOilNo2:Facility", "Maximum"},
         }},
        {"Energy Consumption - Electricity & Natural Gas",
         {
           {"Electricity:Facility", "SumOrAverage"},
           {"Electricity:Facility", "Maximum"},
           {"NaturalGas:Facility", "SumOrAverage"},
           {"NaturalGas:Facility", "Maximum"},
         }},
        {"Energy Consumption - Electricity Generated & Propane",
         {
           {"ElectricityProduced:Facility", "SumOrAverage"},
           {"ElectricityProduced:Facility", "Maximum"},
           {"Propane:Facility", "SumOrAverage"},
           {"Propane:Facility", "Maximum"},
         }},
        {"Fan Report",
         {
           {"Fan Electricity Energy", "SumOrAverage"},
           {"Fan Rise in Air Temperature", "SumOrAverage"},
           {"Fan Electricity Rate", "Maximum"},
           {"Fan Rise in Air Temperature", "ValueWhenMaximumOrMinimum"},
         }},
        {"Generator Report",
         {
           {"Generator Produced Electricity Energy", "SumOrAverage"},
           {"Generator Diesel Energy", "SumOrAverage"},
           {"Generator NaturalGas Energy", "SumOrAverage"},
           {"Generator Produced Electricity Energy", "HoursNonZero"},
           {"Generator Total Heat Recovery", "SumOrAverage"},
           {"Generator Jacket Heat Recovery Energy", "SumOrAverage"},
           {"Generator Lube Heat Recovery Energy", "SumOrAverage"},
           {"Generator Exhaust Heat Recovery Energy", "SumOrAverage"},
           {"Generator Exhaust Air Temperature", "SumOrAverage"},
         }},
        {"Mechanical Ventilation Loads",
         {
           {"Zone Mechanical Ventilation No Load Heat Removal Energy", "SumOrAverage"},
           {"Zone Mechanical Ventilation Cooling Load Increase Energy", "SumOrAverage"},
           {"Zone Mechanical Ventilation Cooling Load Increase Due to Overheating Energy", "SumOrAverage"},
           {"Zone Mechanical Ventilation Cooling Load Decrease Energy", "SumOrAverage"},
           {"Zone Mechanical Ventilation No Load Heat Addition Energy", "SumOrAverage"},
           {"Zone Mechanical Ventilation Heating Load Increase Energy", "SumOrAverage"},
           {"Zone Mechanical Ventilation Heating Load Increase Due to Overcooling Energy", "SumOrAverage"},
           {"Zone Mechanical Ventilation Heating Load Decrease Energy", "SumOrAverage"},
           {"Zone Mechanical Ventilation Air Changes per Hour", "SumOrAverage"},
         }},
        {"Occupant Comfort Data Summary",
         {
           {"Zone People Occupant Count", "HoursNonZero"},
           {"Zone Air Temperature", "SumOrAverageDuringHoursShown"},
           {"Zone Air Relative Humidity", "SumOrAverageDuringHoursShown"},
           {"Zone Thermal Comfort Fanger Model PMV", "SumOrAverageDuringHoursShown"},
         }},
        {"Outdoor Conditions Maximum Dew Point",
         {
           {"Site Outdoor Air Dewpoint Temperature", "Maximum"},
           {"Site Outdoor Air Drybulb Temperature", "ValueWhenMaximumOrMinimum"},
           {"Site Outdoor Air Wetbulb Temperature", "ValueWhenMaximumOrMinimum"},
           {"Site Wind Speed", "ValueWhenMaximumOrMinimum"},
           {"Site Sky Temperature", "ValueWhenMaximumOrMinimum"},
           {"Site Diffuse Solar Radiation Rate per Area", "ValueWhenMaximumOrMinimum"},
           {"Site Direct Solar Radiation Rate per Area", "ValueWhenMaximumOrMinimum"},
         }},
        {"Outdoor Conditions Maximum Drybulb",
         {
           {"Site Outdoor Air Drybulb Temperature", "Maximum"},
           {"Site Outdoor Air Wetbulb Temperature", "ValueWhenMaximumOrMinimum"},
           {"Site Outdoor Air Dewpoint Temperature", "ValueWhenMaximumOrMinimum"},
           {"Site Wind Speed", "ValueWhenMaximumOrMinimum"},
           {"Site Sky Temperature", "ValueWhenMaximumOrMinimum"},
           {"Site Diffuse Solar Radiation Rate per Area", "ValueWhenMaximumOrMinimum"},
           {"Site Direct Solar Radiation Rate per Area", "ValueWhenMaximumOrMinimum"},
         }},
        {"Outdoor Conditions Maximum Wetbulb",
         {
           {"Site Outdoor Air Wetbulb Temperature", "Maximum"},
           {"Site Outdoor Air Drybulb Temperature", "ValueWhenMaximumOrMinimum"},
           {"Site Outdoor Air Dewpoint Temperature", "ValueWhenMaximumOrMinimum"},
           {"Site Wind Speed", "ValueWhenMaximumOrMinimum"},
           {"Site Sky Temperature", "ValueWhenMaximumOrMinimum"},
           {"Site Diffuse Solar Radiation Rate per Area", "ValueWhenMaximumOrMinimum"},
           {"Site Direct Solar Radiation Rate per Area", "ValueWhenMaximumOrMinimum"},
         }},
        {"Outdoor Conditions Minimum Drybulb",
         {
           {"Site Outdoor Air Drybulb Temperature", "Minimum"},
           {"Site Outdoor Air Wetbulb Temperature", "ValueWhenMaximumOrMinimum"},
           {"Site Outdoor Air Dewpoint Temperature", "ValueWhenMaximumOrMinimum"},
           {"Site Wind Speed", "ValueWhenMaximumOrMinimum"},
           {"Site Sky Temperature", "ValueWhenMaximumOrMinimum"},
           {"Site Diffuse Solar Radiation Rate per Area", "ValueWhenMaximumOrMinimum"},
           {"Site Direct Solar Radiation Rate per Area", "ValueWhenMaximumOrMinimum"},
         }},
        {"Outdoor Ground Conditions",
         {
           {"Site Ground Temperature", "SumOrAverage"},
           {"Site Surface Ground Temperature", "SumOrAverage"},
           {"Site Deep Ground Temperature", "SumOrAverage"},
           {"Site Mains Water Temperature", "SumOrAverage"},
           {"Site Ground Reflected Solar Radiation Rate per Area", "SumOrAverage"},
           {"Snow On Ground", "SumOrAverage"},
         }},
        {"Peak Energy End-Use - Coal",
         {
           {"ExteriorEquipment:Coal", "Maximum"},
           {"Heating:Coal", "Maximum"},
           {"WaterSystems:Coal", "Maximum"},
         }},
        {"Peak Energy End-Use - Diesel",
         {
           {"ExteriorEquipment:Diesel", "Maximum"},
           {"Cooling:Diesel", "Maximum"},
           {"Heating:Diesel", "Maximum"},
           {"WaterSystems:Diesel", "Maximum"},
           {"Cogeneration:Diesel", "Maximum"},
         }},
        {"Peak Energy End-Use - Electricity Part 1",
         {
           {"InteriorLights:Electricity", "Maximum"},
           {"ExteriorLights:Electricity", "Maximum"},
           {"InteriorEquipment:Electricity", "Maximum"},
           {"ExteriorEquipment:Electricity", "Maximum"},
           {"Fans:Electricity", "Maximum"},
           {"Pumps:Electricity", "Maximum"},
           {"Heating:Electricity", "Maximum"},
         }},
        {"Peak Energy End-Use - Electricity Part 2",
         {
           {"Cooling:Electricity", "Maximum"},
           {"HeatRejection:Electricity", "Maximum"},
           {"Humidifier:Electricity", "Maximum"},
           {"HeatRecovery:Electricity", "Maximum"},
           {"WaterSystems:Electricity", "Maximum"},
           {"Cogeneration:Electricity", "Maximum"},
         }},
        {"Peak Energy End-Use - Fuel Oil",
         {
           {"ExteriorEquipment:FuelOilNo1", "Maximum"},
           {"Cooling:FuelOilNo1", "Maximum"},
           {"Heating:FuelOilNo1", "Maximum"},
           {"WaterSystems:FuelOilNo1", "Maximum"},
           {"Cogeneration:FuelOilNo1", "Maximum"},
           {"ExteriorEquipment:FuelOilNo2", "Maximum"},
           {"Cooling:FuelOilNo2", "Maximum"},
           {"Heating:FuelOilNo2", "Maximum"},
           {"WaterSystems:FuelOilNo2", "Maximum"},
           {"Cogeneration:FuelOilNo2", "Maximum"},
         }},
        {"Peak Energy End-Use - Gasoline",
         {
           {"ExteriorEquipment:Gasoline", "Maximum"},
           {"Cooling:Gasoline", "Maximum"},
           {"Heating:Gasoline", "Maximum"},
           {"WaterSystems:Gasoline", "Maximum"},
           {"Cogeneration:Gasoline", "Maximum"},
         }},
        {"Peak Energy End-Use - Natural Gas",
         {
           {"InteriorEquipment:NaturalGas", "Maximum"},
           {"ExteriorEquipment:NaturalGas", "Maximum"},
           {"Heating:NaturalGas", "Maximum"},
           {"Cooling:NaturalGas", "Maximum"},
           {"WaterSystems:NaturalGas", "Maximum"},
           {"Cogeneration:NaturalGas", "Maximum"},
         }},
        {"Peak Energy End-Use - Propane",
         {
           {"ExteriorEquipment:Propane", "Maximum"},
           {"Cooling:Propane", "Maximum"},
           {"Heating:Propane", "Maximum"},
           {"WaterSystems:Propane", "Maximum"},
           {"Cogeneration:Propane", "Maximum"},
         }},
        {"Peak Space Gains",
         {
           {"Zone People Total Heating Energy", "Maximum"},
           {"Zone Lights Total Heating Energy", "Maximum"},
           {"Zone Electric Equipment Total Heating Energy", "Maximum"},
           {"Zone Gas Equipment Total Heating Energy", "Maximum"},
           {"Zone Hot Water Equipment Total Heating Energy", "Maximum"},
           {"Zone Steam Equipment Total Heating Energy", "Maximum"},
           {"Zone Other Equipment Total Heating Energy", "Maximum"},
           {"Zone Infiltration Sensible Heat Gain Energy", "Maximum"},
           {"Zone Infiltration Sensible Heat Loss Energy", "Maximum"},
         }},
        {"Plant Loop Demand Report",
         {
           {"Plant Supply Side Cooling Demand Rate", "SumOrAverage"},
           {"Plant Supply Side Cooling Demand Rate", "Maximum"},
           {"Plant Supply Side Heating Demand Rate", "SumOrAverage"},
           {"Plant Supply Side Heating Demand Rate", "Maximum"},
         }},
        {"Pump Report",
         {
           {"Pump Electricity Energy", "SumOrAverage"},
           {"Pump Fluid Heat Gain Energy", "SumOrAverage"},
           {"Pump Electricity Rate", "Maximum"},
           {"Pump Shaft Power", "ValueWhenMaximumOrMinimum"},
           {"Pump Fluid Heat Gain Rate", "ValueWhenMaximumOrMinimum"},
           {"Pump Outlet Temperature", "ValueWhenMaximumOrMinimum"},
           {"Pump Mass Flow Rate", "ValueWhenMaximumOrMinimum"},
         }},
        {"Setpoints Not Met With Temperatures",
         {
           {"Zone Heating Setpoint Not Met Time", "HoursNonZero"},
           {"Zone Mean Air Temperature", "SumOrAverageDuringHoursShown"},
           {"Zone Heating Setpoint Not Met While Occupied Time", "HoursNonZero"},
           {"Zone Mean Air Temperature", "SumOrAverageDuringHoursShown"},
           {"Zone Cooling Setpoint Not Met Time", "HoursNonZero"},
           {"Zone Mean Air Temperature", "SumOrAverageDuringHoursShown"},
           {"Zone Cooling Setpoint Not Met While Occupied Time", "HoursNonZero"},
           {"Zone Mean Air Temperature", "SumOrAverageDuringHoursShown"},
         }},
        {"Space Gain Components at Cooling Peak",
         {
           {"Zone Air System Sensible Cooling Rate", "Maximum"},
           {"Zone People Total Heating Energy", "ValueWhenMaximumOrMinimum"},
           {"Zone Lights Total Heating Energy", "ValueWhenMaximumOrMinimum"},
           {"Zone Electric Equipment Total Heating Energy", "ValueWhenMaximumOrMinimum"},
           {"Zone Gas Equipment Total Heating Energy", "ValueWhenMaximumOrMinimum"},
           {"Zone Hot Water Equipment Total Heating Energy", "ValueWhenMaximumOrMinimum"},
           {"Zone Steam Equipment Total Heating Energy", "ValueWhenMaximumOrMinimum"},
           {"Zone Other Equipment Total Heating Energy", "ValueWhenMaximumOrMinimum"},
           {"Zone Infiltration Sensible Heat Gain Energy", "ValueWhenMaximumOrMinimum"},
           {"Zone Infiltration Sensible Heat Loss Energy", "ValueWhenMaximumOrMinimum"},
         }},
        {"Space Gains",
         {
           {"Zone People Total Heating Energy", "SumOrAverage"},
           {"Zone Lights Total Heating Energy", "SumOrAverage"},
           {"Zone Electric Equipment Total Heating Energy", "SumOrAverage"},
           {"Zone Gas Equipment Total Heating Energy", "SumOrAverage"},
           {"Zone Hot Water Equipment Total Heating Energy", "SumOrAverage"},
           {"Zone Steam Equipment Total Heating Energy", "SumOrAverage"},
           {"Zone Other Equipment Total Heating Energy", "SumOrAverage"},
           {"Zone Infiltration Sensible Heat Gain Energy", "SumOrAverage"},
           {"Zone Infiltration Sensible Heat Loss Energy", "SumOrAverage"},
         }},
        {"Tower Report",
         {
           {"Cooling Tower Fan Electricity Energy", "SumOrAverage"},
           {"Cooling Tower Fan Electricity Energy", "HoursNonZero"},
           {"Cooling Tower Fan Electricity Rate", "Maximum"},
           {"Cooling Tower Heat Transfer Rate", "Maximum"},
           {"Cooling Tower Inlet Temperature", "SumOrAverage"},
           {"Cooling Tower Outlet Temperature", "SumOrAverage"},
           {"Cooling Tower Mass Flow Rate", "SumOrAverage"},
         }},
        {"Unglazed Transpired Solar Collector Summary",
         {
           {"Solar Collector System Efficiency", "HoursNonZero"},
           {"Solar Collector System Efficiency", "SumOrAverageDuringHoursShown"},
           {"Solar Collector Outside Face Suction Velocity", "SumOrAverageDuringHoursShown"},
           {"Solar Collector Sensible Heating Rate", "SumOrAverageDuringHoursShown"},
         }},
        {"Water Heater Report",
         {
           {"Water Heater Total Demand Heat Transfer Energy", "SumOrAverage"},
           {"Water Heater Use Side Heat Transfer Energy", "SumOrAverage"},
           {"Water Heater Burner Heating Energy", "SumOrAverage"},
           {"Water Heater NaturalGas Energy", "SumOrAverage"},
           {"Water Heater Total Demand Heat Transfer Energy", "HoursNonZero"},
           {"Water Heater Loss Demand Energy", "SumOrAverage"},
           {"Water Heater Heat Loss Energy", "SumOrAverage"},
           {"Water Heater Tank Temperature", "SumOrAverage"},
           {"Water Heater Heat Recovery Supply Energy", "SumOrAverage"},
           {"Water Heater Source Side Heat Transfer Energy", "SumOrAverage"},
         }},
        {"Window AC Report",
         {
           {"Zone Window Air Conditioner Total Cooling Energy", "SumOrAverage"},
           {"Zone Window Air Conditioner Electricity Energy", "SumOrAverage"},
           {"Zone Window Air Conditioner Total Cooling Energy", "HoursNonZero"},
           {"Zone Window Air Conditioner Sensible Cooling Energy", "SumOrAverage"},
           {"Zone Window Air Conditioner Latent Cooling Energy", "SumOrAverage"},
           {"Zone Window Air Conditioner Total Cooling Rate", "Maximum"},
           {"Zone Window Air Conditioner Sensible Cooling Rate", "ValueWhenMaximumOrMinimum"},
           {"Zone Window Air Conditioner Latent Cooling Rate", "ValueWhenMaximumOrMinimum"},
           {"Zone Window Air Conditioner Electricity Rate", "ValueWhenMaximumOrMinimum"},
         }},
        {"Window Energy Report",
         {
           {"Surface Window Transmitted Solar Radiation Energy", "SumOrAverage"},
           {"Surface Window Transmitted Beam Solar Radiation Energy", "SumOrAverage"},
           {"Surface Window Transmitted Diffuse Solar Radiation Energy", "SumOrAverage"},
           {"Surface Window Heat Gain Energy", "SumOrAverage"},
           {"Surface Window Heat Loss Energy", "SumOrAverage"},
         }},
        {"Window Energy Zone Summary",
         {
           {"Zone Windows Total Heat Gain Energy", "SumOrAverage"},
           {"Zone Windows Total Heat Loss Energy", "SumOrAverage"},
           {"Zone Windows Total Transmitted Solar Radiation Energy", "SumOrAverage"},
           {"Zone Exterior Windows Total Transmitted Beam Solar Radiation Energy", "SumOrAverage"},
           {"Zone Exterior Windows Total Transmitted Diffuse Solar Radiation Energy", "SumOrAverage"},
           {"Zone Interior Windows Total Transmitted Diffuse Solar Radiation Energy", "SumOrAverage"},
           {"Zone Interior Windows Total Transmitted Beam Solar Radiation Energy", "SumOrAverage"},
         }},
        {"Window Report",
         {
           {"Surface Window Transmitted Solar Radiation Rate", "SumOrAverage"},
           {"Surface Window Transmitted Beam Solar Radiation Rate", "SumOrAverage"},
           {"Surface Window Transmitted Diffuse Solar Radiation Rate", "SumOrAverage"},
           {"Surface Window Heat Gain Rate", "SumOrAverage"},
           {"Surface Window Heat Loss Rate", "SumOrAverage"},
           {"Surface Window Inside Face Glazing Condensation Status", "HoursNonZero"},
           {"Surface Shading Device Is On Time Fraction", "HoursNonZero"},
           {"Surface Storm Window On Off Status", "HoursNonZero"},
         }},
        {"Window Zone Summary",
         {
           {"Zone Windows Total Heat Gain Rate", "SumOrAverage"},
           {"Zone Windows Total Heat Loss Rate", "SumOrAverage"},
           {"Zone Windows Total Transmitted Solar Radiation Rate", "SumOrAverage"},
           {"Zone Exterior Windows Total Transmitted Beam Solar Radiation Rate", "SumOrAverage"},
           {"Zone Exterior Windows Total Transmitted Diffuse Solar Radiation Rate", "SumOrAverage"},
           {"Zone Interior Windows Total Transmitted Diffuse Solar Radiation Rate", "SumOrAverage"},
           {"Zone Interior Windows Total Transmitted Beam Solar Radiation Rate", "SumOrAverage"},
         }},
        {"Zone Cooling Summary",
         {
           {"Zone Air System Sensible Cooling Energy", "SumOrAverage"},
           {"Zone Air System Sensible Cooling Rate", "Maximum"},
           {"Site Outdoor Air Drybulb Temperature", "ValueWhenMaximumOrMinimum"},
           {"Site Outdoor Air Wetbulb Temperature", "ValueWhenMaximumOrMinimum"},
           {"Zone Total Internal Latent Gain Energy", "SumOrAverage"},
           {"Zone Total Internal Latent Gain Energy", "Maximum"},
           {"Site Outdoor Air Drybulb Temperature", "ValueWhenMaximumOrMinimum"},
           {"Site Outdoor Air Wetbulb Temperature", "ValueWhenMaximumOrMinimum"},
         }},
        {"Zone Electric Summary",
         {
           {"Zone Lights Electricity Energy", "SumOrAverage"},
           {"Zone Lights Electricity Energy", "Maximum"},
           {"Zone Electric Equipment Electricity Energy", "SumOrAverage"},
           {"Zone Electric Equipment Electricity Energy", "Maximum"},
         }},
        {"Zone Heating Summary",
         {
           {"Zone Air System Sensible Heating Energy", "SumOrAverage"},
           {"Zone Air System Sensible Heating Rate", "Maximum"},
           {"Site Outdoor Air Drybulb Temperature", "ValueWhenMaximumOrMinimum"},
         }},
        {"Zone Temperature Oscillation Report",
         {
           {"Zone Oscillating Temperatures Time", "HoursNonZero"},
           {"Zone People Occupant Count", "SumOrAverageDuringHoursShown"},
         }},
      };
      return standard_reports;
    }

    const std::vector<std::string>& OutputTableMonthly_Impl::validStandardReportNames() {
      static std::vector<std::string> result = [] {
        std::vector<std::string> result;
        auto const& standard_reports = OutputTableMonthly_Impl::standardReports();
        result.reserve(standard_reports.size());
        std::transform(standard_reports.cbegin(), standard_reports.cend(), std::back_inserter(result), [](const auto& x) { return x.first; });
        return result;
      }();
      return result;
    }

    const std::vector<MonthlyVariableGroup>& OutputTableMonthly_Impl::getGroupsForStandardReport(const std::string& standardReportName) {
      auto const& standard_reports = OutputTableMonthly_Impl::standardReports();
      auto it = std::find_if(standard_reports.cbegin(), standard_reports.cend(),
                             [&standardReportName](const auto& x) { return openstudio::istringEqual(standardReportName, x.first); });
      if (it == standard_reports.cend()) {
        LOG_AND_THROW("Could not find " << standardReportName << ", check OutputTableMonthly::standardReportNames");
      }
      return it->second;
    }

    OutputTableMonthly_Impl::OutputTableMonthly_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(idfObject, model, keepHandle) {
      OS_ASSERT(idfObject.iddObject().type() == OutputTableMonthly::iddObjectType());
    }

    OutputTableMonthly_Impl::OutputTableMonthly_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(other, model, keepHandle) {
      OS_ASSERT(other.iddObject().type() == OutputTableMonthly::iddObjectType());
    }

    OutputTableMonthly_Impl::OutputTableMonthly_Impl(const OutputTableMonthly_Impl& other, Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(other, model, keepHandle) {}

    const std::vector<std::string>& OutputTableMonthly_Impl::outputVariableNames() const {
      static std::vector<std::string> result;
      if (result.empty()) {
      }
      return result;
    }

    IddObjectType OutputTableMonthly_Impl::iddObjectType() const {
      return OutputTableMonthly::iddObjectType();
    }

    int OutputTableMonthly_Impl::digitsAfterDecimal() const {
      boost::optional<int> value = getInt(OS_Output_Table_MonthlyFields::DigitsAfterDecimal, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool OutputTableMonthly_Impl::setDigitsAfterDecimal(int digitsAfterDecimal) {
      const bool result = setInt(OS_Output_Table_MonthlyFields::DigitsAfterDecimal, digitsAfterDecimal);
      return result;
    }

    unsigned int OutputTableMonthly_Impl::numberofMonthlyVariableGroups() const {
      return numExtensibleGroups();
    }

    std::vector<MonthlyVariableGroup> OutputTableMonthly_Impl::monthlyVariableGroups() const {
      std::vector<MonthlyVariableGroup> result;

      for (unsigned i = 0; i < numberofMonthlyVariableGroups(); ++i) {

        boost::optional<MonthlyVariableGroup> group_ = getMonthlyVariableGroup(i);

        // getMonthlyVariableGroup is responsible for handling error and issuing Error log messages.
        // Here we add it to the result array if it worked, and if it didn't, we keep going
        // We just issue a message about index so user can delete it easily
        if (group_) {
          result.push_back(std::move(*group_));
        } else {
          LOG(Error, briefDescription() << " has an invalid MonthlyVariableGroup group at index " << i);
        }
      }

      return result;
    }

    boost::optional<unsigned> OutputTableMonthly_Impl::monthlyVariableGroupIndex(const MonthlyVariableGroup& monthlyVariableGroup) const {
      const std::vector<MonthlyVariableGroup> groups = monthlyVariableGroups();
      auto it = std::find(groups.cbegin(), groups.cend(), monthlyVariableGroup);
      if (it != groups.end()) {
        return static_cast<unsigned>(std::distance(groups.cbegin(), it));
      }
      return boost::none;
    }

    boost::optional<MonthlyVariableGroup> OutputTableMonthly_Impl::getMonthlyVariableGroup(unsigned groupIndex) const {
      if (groupIndex >= numberofMonthlyVariableGroups()) {
        LOG(Error, "Asked to get MonthlyVariableGroup with index " << groupIndex << ", but " << briefDescription() << " has just "
                                                                   << numberofMonthlyVariableGroups() << " MonthlyVariableGroups.");
        return boost::none;
      }
      auto group = getExtensibleGroup(groupIndex).cast<ModelExtensibleGroup>();

      boost::optional<std::string> variableOrMeterName_ = group.getString(OS_Output_Table_MonthlyExtensibleFields::VariableorMeterName);
      boost::optional<std::string> aggregationType_ = group.getString(OS_Output_Table_MonthlyExtensibleFields::AggregationTypeforVariableorMeter);

      if (!variableOrMeterName_) {
        LOG(Error, "Could not retrieve VariableorMeterName_ for extensible group " << group.groupIndex() << ".");
        return boost::none;
      }
      if (!aggregationType_) {
        LOG(Error, "Could not retrieve Aggregation Type for extensible group " << group.groupIndex() << ".");
        return boost::none;
      }

      return {MonthlyVariableGroup(std::move(*variableOrMeterName_), std::move(*aggregationType_))};
    }

    bool OutputTableMonthly_Impl::addMonthlyVariableGroup(const MonthlyVariableGroup& monthlyVariableGroup) {
      if (!monthlyVariableGroup.isAggregationTypeAdvanced()) {
        boost::optional<unsigned> existingIndex_ = monthlyVariableGroupIndex(monthlyVariableGroup);
        if (existingIndex_) {
          LOG(Warn, "For " << briefDescription()
                           << ", MonthlyVariableGroup already exists and is not an Advanced Aggregation Type: " << monthlyVariableGroup);
          return false;
        }
      }
      IdfExtensibleGroup eg = pushExtensibleGroup(StringVector());
      eg.setString(OS_Output_Table_MonthlyExtensibleFields::VariableorMeterName, monthlyVariableGroup.variableOrMeterName());
      eg.setString(OS_Output_Table_MonthlyExtensibleFields::AggregationTypeforVariableorMeter, monthlyVariableGroup.aggregationType());
      return true;
    }

    bool OutputTableMonthly_Impl::addMonthlyVariableGroups(const std::vector<MonthlyVariableGroup>& monthlyVariableGroups) {
      bool result = true;

      for (const auto& monthlyVariableGroup : monthlyVariableGroups) {
        bool thisResult = addMonthlyVariableGroup(monthlyVariableGroup);
        if (!thisResult) {
          LOG(Error, "Could not add MonthlyVariableGroup " << monthlyVariableGroup << " to " << briefDescription() << ". Continuing with others.");
          // OS_ASSERT(false);
          // result = false;
        }
      }

      return result;
    }

    bool OutputTableMonthly_Impl::removeMonthlyVariableGroup(unsigned groupIndex) {
      bool result = false;

      unsigned int num = numberofMonthlyVariableGroups();
      if (groupIndex < num) {
        getObject<ModelObject>().eraseExtensibleGroup(groupIndex);
        result = true;
      }
      return result;
    }

    void OutputTableMonthly_Impl::removeAllMonthlyVariableGroups() {
      getObject<ModelObject>().clearExtensibleGroups();
    }

  }  // namespace detail

  OutputTableMonthly::OutputTableMonthly(const Model& model) : ModelObject(OutputTableMonthly::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::OutputTableMonthly_Impl>());
    bool ok = true;
    ok = setDigitsAfterDecimal(2);
    OS_ASSERT(ok);
  }

  std::vector<std::string> OutputTableMonthly::aggregationTypeValues() {
    IddObject obj = IddFactory::instance().getObject(iddObjectType()).get();
    // Return IddKeyNames in extensible portion
    return getIddKeyNames(obj, obj.numFields() + OS_Output_Table_MonthlyExtensibleFields::AggregationTypeforVariableorMeter);
  }

  std::vector<std::string> OutputTableMonthly::validAggregationTypes() {
    return aggregationTypeValues();
  }

  bool OutputTableMonthly::isAggregationTypeValid(const std::string& aggregationType) {
    const auto vals = aggregationTypeValues();
    return std::find_if(vals.cbegin(), vals.cend(),
                        [&aggregationType](const std::string& choice) { return openstudio::istringEqual(aggregationType, choice); })
           != vals.cend();
  }

  bool OutputTableMonthly::isAggregationTypeAdvanced(const std::string& aggregationType) {
    auto const& vals = advancedAggregationTypes();
    return std::find_if(vals.cbegin(), vals.cend(),
                        [&aggregationType](const std::string& choice) { return openstudio::istringEqual(aggregationType, choice); })
           != vals.cend();
  }

  const std::vector<std::string>& OutputTableMonthly::advancedAggregationTypes() {
    static std::vector<std::string> result;
    if (result.empty()) {
      result = {"ValueWhenMaximumOrMinimum", "SumOrAverageDuringHoursShown", "MaximumDuringHoursShown", "MinimumDuringHoursShown"};
    }
    return result;
  }

  IddObjectType OutputTableMonthly::iddObjectType() {
    return {IddObjectType::OS_Output_Table_Monthly};
  }

  int OutputTableMonthly::digitsAfterDecimal() const {
    return getImpl<detail::OutputTableMonthly_Impl>()->digitsAfterDecimal();
  }

  bool OutputTableMonthly::setDigitsAfterDecimal(int digitsAfterDecimal) {
    return getImpl<detail::OutputTableMonthly_Impl>()->setDigitsAfterDecimal(digitsAfterDecimal);
  }

  std::vector<MonthlyVariableGroup> OutputTableMonthly::monthlyVariableGroups() const {
    return getImpl<detail::OutputTableMonthly_Impl>()->monthlyVariableGroups();
  }

  unsigned int OutputTableMonthly::numberofMonthlyVariableGroups() const {
    return getImpl<detail::OutputTableMonthly_Impl>()->numberofMonthlyVariableGroups();
  }

  boost::optional<unsigned> OutputTableMonthly::monthlyVariableGroupIndex(const MonthlyVariableGroup& monthlyVariableGroup) const {
    return getImpl<detail::OutputTableMonthly_Impl>()->monthlyVariableGroupIndex(monthlyVariableGroup);
  }

  boost::optional<MonthlyVariableGroup> OutputTableMonthly::getMonthlyVariableGroup(unsigned groupIndex) const {
    return getImpl<detail::OutputTableMonthly_Impl>()->getMonthlyVariableGroup(groupIndex);
  }

  bool OutputTableMonthly::addMonthlyVariableGroup(const MonthlyVariableGroup& monthlyVariableGroup) {
    return getImpl<detail::OutputTableMonthly_Impl>()->addMonthlyVariableGroup(monthlyVariableGroup);
  }

  bool OutputTableMonthly::addMonthlyVariableGroup(std::string variableOrMeterName, std::string aggregationType) {
    return addMonthlyVariableGroup(MonthlyVariableGroup(std::move(variableOrMeterName), std::move(aggregationType)));
  }

  bool OutputTableMonthly::addMonthlyVariableGroups(const std::vector<MonthlyVariableGroup>& monthlyVariableGroups) {
    return getImpl<detail::OutputTableMonthly_Impl>()->addMonthlyVariableGroups(monthlyVariableGroups);
  }

  bool OutputTableMonthly::removeMonthlyVariableGroup(unsigned groupIndex) {
    return getImpl<detail::OutputTableMonthly_Impl>()->removeMonthlyVariableGroup(groupIndex);
  }

  void OutputTableMonthly::removeAllMonthlyVariableGroups() {
    getImpl<detail::OutputTableMonthly_Impl>()->removeAllMonthlyVariableGroups();
  }

  /// @cond
  OutputTableMonthly::OutputTableMonthly(std::shared_ptr<detail::OutputTableMonthly_Impl> impl) : ModelObject(std::move(impl)) {}
  /// @endcond

  const std::vector<std::string>& OutputTableMonthly::validStandardReportNames() {
    return detail::OutputTableMonthly_Impl::validStandardReportNames();
  }
  OutputTableMonthly OutputTableMonthly::fromStandardReports(const Model& model, const std::string& standardReportName) {
    const auto& groups = detail::OutputTableMonthly_Impl::getGroupsForStandardReport(standardReportName);
    OutputTableMonthly result(model);
    result.setName(standardReportName);
    result.addMonthlyVariableGroups(groups);
    return result;
  }

}  // namespace model
}  // namespace openstudio
