/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGEROUTDOORAIRRESET_HPP
#define EPMODEL_SETPOINTMANAGEROUTDOORAIRRESET_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;

  namespace detail {
    class SetpointManagerOutdoorAirReset_Impl;
  }

  /** \brief Resets a setpoint across outdoor-air temperature conditions.
   *
   * \par EnergyPlus object
   * \epobject{group-setpoint-managers.html#setpointmanageroutdoorairreset,SetpointManager:OutdoorAirReset}
   *
   * \par Important behavior
   * The optional second reset pair and schedule are represented as optional
   * fields; reset methods remove those fields rather than writing placeholder
   * values.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::SetpointManagerOutdoorAirReset</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API SetpointManagerOutdoorAirReset : public SetpointManager
  {
   public:
    explicit SetpointManagerOutdoorAirReset(const Model& model);

    virtual ~SetpointManagerOutdoorAirReset() override = default;
    SetpointManagerOutdoorAirReset(const SetpointManagerOutdoorAirReset& other) = default;
    SetpointManagerOutdoorAirReset(SetpointManagerOutdoorAirReset&& other) = default;
    SetpointManagerOutdoorAirReset& operator=(const SetpointManagerOutdoorAirReset&) = default;
    SetpointManagerOutdoorAirReset& operator=(SetpointManagerOutdoorAirReset&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlVariableValues();


    bool isControlVariableDefaulted() const;
    void resetControlVariable();

    double setpointatOutdoorLowTemperature() const;
    bool setSetpointatOutdoorLowTemperature(double setpointatOutdoorLowTemperature);

    double outdoorLowTemperature() const;
    bool setOutdoorLowTemperature(double outdoorLowTemperature);

    double setpointatOutdoorHighTemperature() const;
    bool setSetpointatOutdoorHighTemperature(double setpointatOutdoorHighTemperature);

    double outdoorHighTemperature() const;
    bool setOutdoorHighTemperature(double outdoorHighTemperature);

    boost::optional<Schedule> schedule() const;
    bool setSchedule(Schedule& schedule);
    void resetSchedule();

    boost::optional<double> setpointatOutdoorLowTemperature2() const;
    bool setSetpointatOutdoorLowTemperature2(double setpointatOutdoorLowTemperature2);
    void resetSetpointatOutdoorLowTemperature2();

    boost::optional<double> outdoorLowTemperature2() const;
    bool setOutdoorLowTemperature2(double outdoorLowTemperature2);
    void resetOutdoorLowTemperature2();

    boost::optional<double> setpointatOutdoorHighTemperature2() const;
    bool setSetpointatOutdoorHighTemperature2(double setpointatOutdoorHighTemperature2);
    void resetSetpointatOutdoorHighTemperature2();

    boost::optional<double> outdoorHighTemperature2() const;
    bool setOutdoorHighTemperature2(double outdoorHighTemperature2);
    void resetOutdoorHighTemperature2();

   protected:
    using ImplType = detail::SetpointManagerOutdoorAirReset_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerOutdoorAirReset(std::shared_ptr<detail::SetpointManagerOutdoorAirReset_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
