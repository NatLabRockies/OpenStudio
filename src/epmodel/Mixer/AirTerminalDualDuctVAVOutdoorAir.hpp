/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALDUALDUCTVAVOUTDOORAIR_HPP
#define EPMODEL_AIRTERMINALDUALDUCTVAVOUTDOORAIR_HPP

#include "EPModelAPI.hpp"
#include "Mixer/Mixer.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;

  namespace detail {
    class AirTerminalDualDuctVAVOutdoorAir_Impl;
  }

  /** \brief Represents a dual-duct VAV terminal with a dedicated outdoor-air inlet.
   *
   * \par EnergyPlus object
   * \epobject{group-air-distribution-equipment.html#airterminaldualductvavoutdoorair,AirTerminal:DualDuct:VAV:OutdoorAir}.
   *
   * \par Important behavior
   * Separate terminal inlet and outlet node relationships follow the supported dual-duct air-loop insertion and removal topology.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::AirTerminalDualDuctVAVOutdoorAir</code>.
   * <b>Not yet available: <code>controlForOutdoorAir()</code>, <code>setControlForOutdoorAir()</code>, and the SQL-backed <code>autosizedMaximumTerminalAirFlowRate()</code> result helper.</b>
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API AirTerminalDualDuctVAVOutdoorAir : public Mixer
  {
   public:
    explicit AirTerminalDualDuctVAVOutdoorAir(const Model& model);

    virtual ~AirTerminalDualDuctVAVOutdoorAir() override = default;
    AirTerminalDualDuctVAVOutdoorAir(const AirTerminalDualDuctVAVOutdoorAir& other) = default;
    AirTerminalDualDuctVAVOutdoorAir(AirTerminalDualDuctVAVOutdoorAir&& other) = default;
    AirTerminalDualDuctVAVOutdoorAir& operator=(const AirTerminalDualDuctVAVOutdoorAir&) = default;
    AirTerminalDualDuctVAVOutdoorAir& operator=(AirTerminalDualDuctVAVOutdoorAir&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> perPersonVentilationRateModeValues();

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    boost::optional<double> maximumTerminalAirFlowRate() const;
    bool setMaximumTerminalAirFlowRate(double maximumTerminalAirFlowRate);
    void autosizeMaximumTerminalAirFlowRate();
    bool isMaximumTerminalAirFlowRateAutosized() const;

    std::string perPersonVentilationRateMode() const;
    bool setPerPersonVentilationRateMode(const std::string& perPersonVentilationRateMode);
    boost::optional<Node> outdoorAirInletNode() const;
    boost::optional<Node> recirculatedAirInletNode() const;
    bool addToNode(Node& node);

   protected:
    using ImplType = detail::AirTerminalDualDuctVAVOutdoorAir_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirTerminalDualDuctVAVOutdoorAir(std::shared_ptr<detail::AirTerminalDualDuctVAVOutdoorAir_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
