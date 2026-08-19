/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTINLETSIDEMIXER_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTINLETSIDEMIXER_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;

  namespace detail {
    class AirTerminalSingleDuctInletSideMixer_Impl;
  }

  /**
   * \brief Inlet-side mixer terminal for combining primary and secondary air streams.
   *
   * \par EnergyPlus object
   * Encapsulates \epobject{group-air-distribution-equipment.html#airterminalsingleductmixer,AirTerminal:SingleDuct:Mixer}.
   *
   * \par Important behavior
   * `addToNode` accepts only the matching epmodel AirLoopHVAC zone-branch node and rewires the splitter, terminal,
   * AirDistributionUnit, and zone-equipment references as one operation. Removal restores the original branch and
   * deletes the transient inlet node created by the terminal.
   *
   * \par OpenStudio Model API
   * Counterpart: `openstudio::model::AirTerminalSingleDuctInletSideMixer`. The mixer node, ventilation-rate mode,
   * and supported branch lifecycle are represented. The Model API additionally provides `controlForOutdoorAir` and
   * the DesignSpecificationOutdoorAir relationship.
   *
   * \par Known limitations
   * Broader local-topology insertion is not supported, and this object is not a supported implicit
   * AirLoopHVAC clone-last source when its secondary inlet is owned by downstream zone equipment.
   */
  class EPMODEL_API AirTerminalSingleDuctInletSideMixer : public StraightComponent
  {
   public:
    explicit AirTerminalSingleDuctInletSideMixer(const Model& model);

    virtual ~AirTerminalSingleDuctInletSideMixer() override = default;
    AirTerminalSingleDuctInletSideMixer(const AirTerminalSingleDuctInletSideMixer& other) = default;
    AirTerminalSingleDuctInletSideMixer(AirTerminalSingleDuctInletSideMixer&& other) = default;
    AirTerminalSingleDuctInletSideMixer& operator=(const AirTerminalSingleDuctInletSideMixer&) = default;
    AirTerminalSingleDuctInletSideMixer& operator=(AirTerminalSingleDuctInletSideMixer&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> perPersonVentilationRateModeValues();
    bool addToNode(Node& node);

    /** @name Per Person Ventilation Rate Mode */
    //@{
    std::string perPersonVentilationRateMode() const;
    bool setPerPersonVentilationRateMode(const std::string& perPersonVentilationRateMode);
    //@}

    /** @name Secondary Air */
    //@{
    unsigned secondaryAirInletPort() const;
    boost::optional<Node> secondaryAirInletNode() const;
    //@}

   protected:
    using ImplType = detail::AirTerminalSingleDuctInletSideMixer_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirTerminalSingleDuctInletSideMixer(std::shared_ptr<detail::AirTerminalSingleDuctInletSideMixer_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
