/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRCONDITIONERVARIABLEREFRIGERANTFLOW_IMPL_HPP
#define EPMODEL_AIRCONDITIONERVARIABLEREFRIGERANTFLOW_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  class ModelObject;
  class Schedule;
  class ThermalZone;
  class ZoneHVACTerminalUnitVariableRefrigerantFlow;

  namespace detail {

    class EPMODEL_API AirConditionerVariableRefrigerantFlow_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~AirConditionerVariableRefrigerantFlow_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      bool addToNode(Node& node) override;
      std::vector<IdfObject> remove() override;
      void doCanonicalize(LoadContext& context) override;

      bool addTerminal(ZoneHVACTerminalUnitVariableRefrigerantFlow& terminal);
      void removeTerminal(ZoneHVACTerminalUnitVariableRefrigerantFlow& terminal);
      void removeAllTerminals();
      std::vector<ZoneHVACTerminalUnitVariableRefrigerantFlow> terminals() const;

      boost::optional<ModelObject> ensureTerminalUnitList();

      Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);

      boost::optional<ThermalZone> zoneforMasterThermostatLocation() const;
      bool setZoneforMasterThermostatLocation(const ThermalZone& zone);
      void resetZoneforMasterThermostatLocation();

      boost::optional<Schedule> thermostatPrioritySchedule() const;
      bool setThermostatPrioritySchedule(Schedule& schedule);
      void resetThermostatPrioritySchedule();

      boost::optional<Schedule> basinHeaterOperatingSchedule() const;
      bool setBasinHeaterOperatingSchedule(Schedule& schedule);
      void resetBasinHeaterOperatingSchedule();

      boost::optional<double> grossRatedTotalCoolingCapacity() const;
      bool isGrossRatedTotalCoolingCapacityAutosized() const;
      bool setGrossRatedTotalCoolingCapacity(double grossRatedTotalCoolingCapacity);
      void autosizeGrossRatedTotalCoolingCapacity();

      double grossRatedCoolingCOP() const;
      bool setGrossRatedCoolingCOP(double grossRatedCoolingCOP);

      boost::optional<double> grossRatedHeatingCapacity() const;
      bool isGrossRatedHeatingCapacityAutosized() const;
      bool setGrossRatedHeatingCapacity(double grossRatedHeatingCapacity);
      void autosizeGrossRatedHeatingCapacity();

      double ratedHeatingCapacitySizingRatio() const;
      bool setRatedHeatingCapacitySizingRatio(double ratedHeatingCapacitySizingRatio);

      std::string heatingPerformanceCurveOutdoorTemperatureType() const;
      bool setHeatingPerformanceCurveOutdoorTemperatureType(const std::string& heatingPerformanceCurveOutdoorTemperatureType);

      bool heatPumpWasteHeatRecovery() const;
      bool setHeatPumpWasteHeatRecovery(bool heatPumpWasteHeatRecovery);

      int numberofCompressors() const;
      bool setNumberofCompressors(int numberofCompressors);

      std::string defrostStrategy() const;
      bool setDefrostStrategy(const std::string& defrostStrategy);

      std::string condenserType() const;
      bool setCondenserType(const std::string& condenserType);
      bool isCondenserTypeDefaulted() const;
      void resetCondenserType();

      std::vector<std::string> heatingPerformanceCurveOutdoorTemperatureTypeValues() const;
      std::vector<std::string> defrostStrategyValues() const;
      std::vector<std::string> condenserTypeValues() const;

     private:
      boost::optional<ModelObject> terminalUnitList() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
