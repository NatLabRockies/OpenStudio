/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEADEREDPUMPSCONSTANTSPEED_HPP
#define EPMODEL_HEADEREDPUMPSCONSTANTSPEED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;
  class ThermalZone;

  namespace detail {
    class HeaderedPumpsConstantSpeed_Impl;
  }

/** \brief A bank of constant-speed headered pumps.
 *
 * \par EnergyPlus object
 * \epobject{group-pumps.html#headeredpumpsconstantspeed,HeaderedPumps:ConstantSpeed}
 *
 * \par Important behavior
 * Pump-bank scalars, flow-rate schedule, thermal-zone relationship, and plant placement map to HeaderedPumps:ConstantSpeed.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::HeaderedPumpsConstantSpeed</code>.
 *
 * \par Known limitations
 * No additional type-specific limitation is known beyond shared straight-component topology.
 */
  class EPMODEL_API HeaderedPumpsConstantSpeed : public StraightComponent
  {
   public:
    explicit HeaderedPumpsConstantSpeed(const Model& model);

    virtual ~HeaderedPumpsConstantSpeed() override = default;
    HeaderedPumpsConstantSpeed(const HeaderedPumpsConstantSpeed& other) = default;
    HeaderedPumpsConstantSpeed(HeaderedPumpsConstantSpeed&& other) = default;
    HeaderedPumpsConstantSpeed& operator=(const HeaderedPumpsConstantSpeed&) = default;
    HeaderedPumpsConstantSpeed& operator=(HeaderedPumpsConstantSpeed&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> flowSequencingControlSchemeValues();
    static std::vector<std::string> pumpControlTypeValues();
    static std::vector<std::string> designPowerSizingMethodValues();


    boost::optional<double> totalRatedFlowRate() const;
    bool isTotalRatedFlowRateAutosized() const;
    bool setTotalRatedFlowRate(double totalRatedFlowRate);
    void autosizeTotalRatedFlowRate();
    boost::optional<double> autosizedTotalRatedFlowRate() const;

    int numberofPumpsinBank() const;
    bool setNumberofPumpsinBank(int numberofPumpsinBank);

    std::string flowSequencingControlScheme() const;
    bool setFlowSequencingControlScheme(const std::string& flowSequencingControlScheme);

    double ratedPumpHead() const;
    bool setRatedPumpHead(double ratedPumpHead);

    boost::optional<double> ratedPowerConsumption() const;
    bool isRatedPowerConsumptionAutosized() const;
    bool setRatedPowerConsumption(double ratedPowerConsumption);
    void autosizeRatedPowerConsumption();
    boost::optional<double> autosizedRatedPowerConsumption() const;

    double motorEfficiency() const;
    bool setMotorEfficiency(double motorEfficiency);

    double fractionofMotorInefficienciestoFluidStream() const;
    bool setFractionofMotorInefficienciestoFluidStream(double fractionofMotorInefficienciestoFluidStream);

    std::string pumpControlType() const;
    bool setPumpControlType(const std::string& pumpControlType);

    boost::optional<Schedule> pumpFlowRateSchedule() const;
    bool setPumpFlowRateSchedule(Schedule& schedule);
    void resetPumpFlowRateSchedule();

    boost::optional<ThermalZone> thermalZone() const;
    bool setThermalZone(const ThermalZone& thermalZone);
    void resetThermalZone();

    double skinLossRadiativeFraction() const;
    bool setSkinLossRadiativeFraction(double skinLossRadiativeFraction);

    std::string designPowerSizingMethod() const;
    bool setDesignPowerSizingMethod(const std::string& designPowerSizingMethod);

    double designElectricPowerPerUnitFlowRate() const;
    bool setDesignElectricPowerPerUnitFlowRate(double designElectricPowerPerUnitFlowRate);

    double designShaftPowerPerUnitFlowRatePerUnitHead() const;
    bool setDesignShaftPowerPerUnitFlowRatePerUnitHead(double designShaftPowerPerUnitFlowRatePerUnitHead);

    std::string endUseSubcategory() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);

    bool addToNode(Node& node);

   protected:
    using ImplType = detail::HeaderedPumpsConstantSpeed_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HeaderedPumpsConstantSpeed(std::shared_ptr<detail::HeaderedPumpsConstantSpeed_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
