/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPAIRTOWATER_HPP
#define EPMODEL_HEATPUMPAIRTOWATER_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;
  class Curve;

  namespace detail {
    class HeatPumpAirToWater_Impl;
  }

/** \brief An air-to-water heat pump.
 *
 * \par EnergyPlus object
 * \epobject{group-plant-equipment.html#plhp_air_to_water,HeatPump:AirToWater}
 *
 * \par Important behavior
 * Operating-mode, defrost, control, part-load, crankcase-heater, schedule, air-node, and curve fields map directly to HeatPump:AirToWater.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::HeatPumpAirToWater</code>.
 *
 * \par Known limitations
 * Heating/cooling operating-mode child wrappers and loop lookup helpers are not available.
 */
  class EPMODEL_API HeatPumpAirToWater : public StraightComponent
  {
   public:
    explicit HeatPumpAirToWater(const Model& model);

    virtual ~HeatPumpAirToWater() override = default;
    HeatPumpAirToWater(const HeatPumpAirToWater& other) = default;
    HeatPumpAirToWater(HeatPumpAirToWater&& other) = default;
    HeatPumpAirToWater& operator=(const HeatPumpAirToWater&) = default;
    HeatPumpAirToWater& operator=(HeatPumpAirToWater&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> operatingModeControlMethodValues();
    static std::vector<std::string> operatingModeControlOptionforMultipleUnitValues();
    static std::vector<std::string> heatPumpDefrostControlValues();
    static std::vector<std::string> controlTypeValues();

    std::string operatingModeControlMethod() const;
    bool setOperatingModeControlMethod(const std::string& operatingModeControlMethod);
    bool isOperatingModeControlMethodDefaulted() const;
    void resetOperatingModeControlMethod();

    std::string operatingModeControlOptionforMultipleUnit() const;
    bool setOperatingModeControlOptionforMultipleUnit(const std::string& operatingModeControlOptionforMultipleUnit);
    bool isOperatingModeControlOptionforMultipleUnitDefaulted() const;
    void resetOperatingModeControlOptionforMultipleUnit();

    boost::optional<Schedule> operatingModeControlSchedule() const;
    bool setOperatingModeControlSchedule(Schedule& operatingModeControlSchedule);
    void resetOperatingModeControlSchedule();

    double minimumPartLoadRatio() const;
    bool setMinimumPartLoadRatio(double minimumPartLoadRatio);
    bool isMinimumPartLoadRatioDefaulted() const;
    void resetMinimumPartLoadRatio();

    boost::optional<std::string> airInletNodeName() const;
    bool setAirInletNodeName(const std::string& airInletNodeName);
    void resetAirInletNodeName();

    boost::optional<std::string> airOutletNodeName() const;
    bool setAirOutletNodeName(const std::string& airOutletNodeName);
    void resetAirOutletNodeName();

    double maximumOutdoorDryBulbTemperatureForDefrostOperation() const;
    bool setMaximumOutdoorDryBulbTemperatureForDefrostOperation(double maximumOutdoorDryBulbTemperatureForDefrostOperation);
    bool isMaximumOutdoorDryBulbTemperatureForDefrostOperationDefaulted() const;
    void resetMaximumOutdoorDryBulbTemperatureForDefrostOperation();

    std::string heatPumpDefrostControl() const;
    bool setHeatPumpDefrostControl(const std::string& heatPumpDefrostControl);
    bool isHeatPumpDefrostControlDefaulted() const;
    void resetHeatPumpDefrostControl();

    double heatPumpDefrostTimePeriodFraction() const;
    bool setHeatPumpDefrostTimePeriodFraction(double heatPumpDefrostTimePeriodFraction);
    bool isHeatPumpDefrostTimePeriodFractionDefaulted() const;
    void resetHeatPumpDefrostTimePeriodFraction();

    double resistiveDefrostHeaterCapacity() const;
    bool setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity);
    bool isResistiveDefrostHeaterCapacityDefaulted() const;
    void resetResistiveDefrostHeaterCapacity();

    boost::optional<Curve> defrostEnergyInputRatioFunctionofTemperatureCurve() const;
    bool setDefrostEnergyInputRatioFunctionofTemperatureCurve(const Curve& defrostEnergyInputRatioFunctionofTemperatureCurve);
    void resetDefrostEnergyInputRatioFunctionofTemperatureCurve();

    int heatPumpMultiplier() const;
    bool setHeatPumpMultiplier(int heatPumpMultiplier);
    bool isHeatPumpMultiplierDefaulted() const;
    void resetHeatPumpMultiplier();

    std::string controlType() const;
    bool setControlType(const std::string& controlType);
    bool isControlTypeDefaulted() const;
    void resetControlType();

    double crankcaseHeaterCapacity() const;
    bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);
    bool isCrankcaseHeaterCapacityDefaulted() const;
    void resetCrankcaseHeaterCapacity();

    boost::optional<Curve> crankcaseHeaterCapacityFunctionofTemperatureCurve() const;
    bool setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& crankcaseHeaterCapacityFunctionofTemperatureCurve);
    void resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();

    double maximumAmbientTemperatureforCrankcaseHeaterOperation() const;
    bool setMaximumAmbientTemperatureforCrankcaseHeaterOperation(double maximumAmbientTemperatureforCrankcaseHeaterOperation);
    bool isMaximumAmbientTemperatureforCrankcaseHeaterOperationDefaulted() const;
    void resetMaximumAmbientTemperatureforCrankcaseHeaterOperation();

   protected:
    using ImplType = detail::HeatPumpAirToWater_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HeatPumpAirToWater(std::shared_ptr<detail::HeatPumpAirToWater_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
