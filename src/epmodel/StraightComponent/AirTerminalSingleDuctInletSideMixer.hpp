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

    // Schema Alignment Notes:
    // - Status: Partial Parity. The persisted mixer scalar/relationship fields and the current epmodel zone-branch insertion path are aligned,
    //   but the broader canonical local-topology surface remains intentionally narrower.
    // - Canonical Counterpart: openstudio::model::AirTerminalSingleDuctInletSideMixer.
    // - Implemented Parity: `perPersonVentilationRateMode`, `secondaryAirInletNode`, and `addToNode` preserve the persisted
    //   `AirTerminal:SingleDuct:Mixer` scalar/relationship contract on the current epmodel zone-branch path.
    // - Documented Delta: The wrapper preserves the epmodel-only default constructor, and the canonical public `controlForOutdoorAir`
    //   toggle is intentionally omitted because this EnergyPlus-backed wrapper has no dedicated persisted boolean field for that OS-only setting.
    // - Field/Storage Mapping: The preserved scalar and direct object links map directly to the EnergyPlus `AirTerminal:SingleDuct:Mixer` fields,
    //   and `addToNode` rewires the current epmodel zone branch by updating the same primary-air and outlet node fields.
    // - Evidence: `src/model/AirTerminalSingleDuctInletSideMixer.hpp`, `src/model/AirTerminalSingleDuctInletSideMixer.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctInletSideMixer.cpp`, and `src/epmodel/test/AirTerminalSingleDuctInletSideMixer_GTest.cpp`.
    // - Remaining Parity Work: Broaden the local-topology surface only if canonical insertion behavior needs to be mirrored more fully.

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
