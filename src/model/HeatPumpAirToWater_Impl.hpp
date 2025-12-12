/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef MODEL_HEATPUMPAIRTOWATER_IMPL_HPP
#define MODEL_HEATPUMPAIRTOWATER_IMPL_HPP

#include "ModelAPI.hpp"
#include "StraightComponent_Impl.hpp"

namespace openstudio {
namespace model {

  class Schedule;
  class Curve;
  class HeatPumpAirToWaterHeating;
  class HeatPumpAirToWaterCooling;
  class PlantLoop;

  namespace detail {

    /** HeatPumpAirToWater_Impl is a StraightComponent_Impl that is the implementation class for HeatPumpAirToWater.*/
    class MODEL_API HeatPumpAirToWater_Impl : public StraightComponent_Impl
    {
     public:
      /** @name Constructors and Destructors */
      //@{

      HeatPumpAirToWater_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle);

      HeatPumpAirToWater_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle);

      HeatPumpAirToWater_Impl(const HeatPumpAirToWater_Impl& other, Model_Impl* model, bool keepHandle);

      virtual ~HeatPumpAirToWater_Impl() = default;

      //@}
      /** @name Virtual Methods */
      //@{

      virtual const std::vector<std::string>& outputVariableNames() const override;

      virtual IddObjectType iddObjectType() const override;

      virtual std::vector<ScheduleTypeKey> getScheduleTypeKeys(const Schedule& schedule) const override;

      // base is StraightComponent
      virtual ModelObject clone(Model model) const override;

      virtual std::vector<ModelObject> children() const override;
      // virtual std::vector<IddObjectType> allowableChildTypes() const override;

      virtual std::vector<IdfObject> remove() override;

      // Overrides from StraightComponent
      virtual unsigned inletPort() const override;
      virtual unsigned outletPort() const override;

      virtual bool addToNode(Node& node) override;

      virtual void autosize() override;

      virtual void applySizingValues() override;

      virtual ComponentType componentType() const override;
      virtual std::vector<FuelType> coolingFuelTypes() const override;
      virtual std::vector<FuelType> heatingFuelTypes() const override;
      virtual std::vector<AppGFuelType> appGHeatingFuelTypes() const override;

      virtual std::vector<EMSActuatorNames> emsActuatorNames() const override;
      virtual std::vector<std::string> emsInternalVariableNames() const override;

      //@}
      /** @name Getters */
      //@{

      std::string operatingModeControlMethod() const;

      std::string operatingModeControlOptionforMultipleUnit() const;

      boost::optional<Schedule> operatingModeControlSchedule() const;

      double minimumPartLoadRatio() const;

      boost::optional<std::string> airInletNodeName() const;

      boost::optional<std::string> airOutletNodeName() const;

      double maximumOutdoorDryBulbTemperatureForDefrostOperation() const;

      std::string heatPumpDefrostControl() const;

      double heatPumpDefrostTimePeriodFraction() const;

      double resistiveDefrostHeaterCapacity() const;

      boost::optional<Curve> defrostEnergyInputRatioFunctionofTemperatureCurve() const;

      int heatPumpMultiplier() const;

      std::string controlType() const;

      double crankcaseHeaterCapacity() const;

      boost::optional<Curve> crankcaseHeaterCapacityFunctionofTemperatureCurve() const;

      double maximumAmbientTemperatureforCrankcaseHeaterOperation() const;

      boost::optional<HeatPumpAirToWaterHeating> heatingOperationMode() const;

      boost::optional<HeatPumpAirToWaterCooling> coolingOperationMode() const;

      //@}
      /** @name Setters */
      //@{

      bool setOperatingModeControlMethod(const std::string& operatingModeControlMethod);

      bool setOperatingModeControlOptionforMultipleUnit(const std::string& operatingModeControlOptionforMultipleUnit);

      bool setOperatingModeControlSchedule(Schedule& operatingModeControlSchedule);

      void resetOperatingModeControlSchedule();

      bool setMinimumPartLoadRatio(double minimumPartLoadRatio);

      bool setAirInletNodeName(const std::string& airInletNodeName);

      void resetAirInletNodeName();

      bool setAirOutletNodeName(const std::string& airOutletNodeName);

      void resetAirOutletNodeName();

      bool setMaximumOutdoorDryBulbTemperatureForDefrostOperation(double maximumOutdoorDryBulbTemperatureForDefrostOperation);

      bool setHeatPumpDefrostControl(const std::string& heatPumpDefrostControl);

      bool setHeatPumpDefrostTimePeriodFraction(double heatPumpDefrostTimePeriodFraction);

      bool setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity);

      bool setDefrostEnergyInputRatioFunctionofTemperatureCurve(const Curve& defrostEnergyInputRatioFunctionofTemperatureCurve);

      void resetDefrostEnergyInputRatioFunctionofTemperatureCurve();

      bool setHeatPumpMultiplier(int heatPumpMultiplier);

      bool setControlType(const std::string& controlType);

      bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);

      bool setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& crankcaseHeaterCapacityFunctionofTemperatureCurve);

      void resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();

      bool setMaximumAmbientTemperatureforCrankcaseHeaterOperation(double maximumAmbientTemperatureforCrankcaseHeaterOperation);

      bool setHeatingOperationMode(const HeatPumpAirToWaterHeating& heatingOperationMode);

      void resetHeatingOperationMode();

      bool setCoolingOperationMode(const HeatPumpAirToWaterCooling& coolingOperationMode);

      void resetCoolingOperationMode();

      //@}
      /** @name Other */
      //@{

      boost::optional<PlantLoop> coolingLoop() const;
      boost::optional<PlantLoop> heatingLoop() const;

      // Autosize methods
      boost::optional<double> autosizedRatedAirFlowRateinHeatingMode() const;
      boost::optional<double> autosizedRatedWaterFlowRateinHeatingMode() const;
      boost::optional<double> autosizedRatedAirFlowRateinCoolingMode() const;
      boost::optional<double> autosizedRatedWaterFlowRateinCoolingMode() const;
      boost::optional<double> autosizedRatedHeatingCapacity() const;
      boost::optional<double> autosizedRatedCoolingCapacity() const;

      //@}
     protected:
     private:
      REGISTER_LOGGER("openstudio.model.HeatPumpAirToWater");
    };

  }  // namespace detail

}  // namespace model
}  // namespace openstudio

#endif  // MODEL_HEATPUMPAIRTOWATER_IMPL_HPP
