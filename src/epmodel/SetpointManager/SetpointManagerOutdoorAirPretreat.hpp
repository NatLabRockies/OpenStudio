/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGEROUTDOORAIRPRETREAT_HPP
#define EPMODEL_SETPOINTMANAGEROUTDOORAIRPRETREAT_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;

  namespace detail {
    class SetpointManagerOutdoorAirPretreat_Impl;
  }

  /** \brief Sets pretreatment air conditions from outdoor-air, return-air, and mixed-air stream nodes.
   *
   * \par EnergyPlus object
   * \epobject{group-setpoint-managers.html#setpointmanageroutdoorairpretreat,SetpointManager:OutdoorAirPretreat}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::SetpointManagerOutdoorAirPretreat</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API SetpointManagerOutdoorAirPretreat : public SetpointManager
  {
   public:
    explicit SetpointManagerOutdoorAirPretreat(const Model& model);

    virtual ~SetpointManagerOutdoorAirPretreat() override = default;
    SetpointManagerOutdoorAirPretreat(const SetpointManagerOutdoorAirPretreat& other) = default;
    SetpointManagerOutdoorAirPretreat(SetpointManagerOutdoorAirPretreat&& other) = default;
    SetpointManagerOutdoorAirPretreat& operator=(const SetpointManagerOutdoorAirPretreat&) = default;
    SetpointManagerOutdoorAirPretreat& operator=(SetpointManagerOutdoorAirPretreat&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlVariableValues();

    double minimumSetpointTemperature() const;
    bool isMinimumSetpointTemperatureDefaulted() const;
    bool setMinimumSetpointTemperature(double minimumSetpointTemperature);
    void resetMinimumSetpointTemperature();

    double maximumSetpointTemperature() const;
    bool isMaximumSetpointTemperatureDefaulted() const;
    bool setMaximumSetpointTemperature(double maximumSetpointTemperature);
    void resetMaximumSetpointTemperature();

    double minimumSetpointHumidityRatio() const;
    bool isMinimumSetpointHumidityRatioDefaulted() const;
    bool setMinimumSetpointHumidityRatio(double minimumSetpointHumidityRatio);
    void resetMinimumSetpointHumidityRatio();

    double maximumSetpointHumidityRatio() const;
    bool isMaximumSetpointHumidityRatioDefaulted() const;
    bool setMaximumSetpointHumidityRatio(double maximumSetpointHumidityRatio);
    void resetMaximumSetpointHumidityRatio();

    boost::optional<Node> referenceSetpointNode() const;
    bool setReferenceSetpointNode(const Node& node);
    void resetReferenceSetpointNode();

    boost::optional<Node> mixedAirStreamNode() const;
    bool setMixedAirStreamNode(const Node& node);
    void resetMixedAirStreamNode();

    boost::optional<Node> outdoorAirStreamNode() const;
    bool setOutdoorAirStreamNode(const Node& node);
    void resetOutdoorAirStreamNode();

    boost::optional<Node> returnAirStreamNode() const;
    bool setReturnAirStreamNode(const Node& node);
    void resetReturnAirStreamNode();

    void resetControlVariable();

   protected:
    using ImplType = detail::SetpointManagerOutdoorAirPretreat_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerOutdoorAirPretreat(std::shared_ptr<detail::SetpointManagerOutdoorAirPretreat_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
