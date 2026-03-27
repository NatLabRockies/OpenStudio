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

    // Schema Alignment Notes:
    // - Status: Partial Parity. The scalar inlet-side mixer controls are aligned, but the outdoor-air control and target-link surface is still intentionally narrower.
    // - Canonical Counterpart: openstudio::model::AirTerminalSingleDuctInletSideMixer.
    // - Implemented Parity: `perPersonVentilationRateMode` preserves the canonical scalar contract.
    // - Documented Delta: `controlForOutdoorAir` is modeled through translator behavior rather than a dedicated public wrapper here, and zone/unit-object type, mixer connection, and node/DSOA fields are not exposed as public methods yet.
    // - Field/Storage Mapping: The preserved scalar maps directly to EnergyPlus `AirTerminal:SingleDuct:Mixer` fields; the translator wires the outdoor-air and zone links separately.
    // - Evidence: `src/model/AirTerminalSingleDuctInletSideMixer.hpp`, `src/model/AirTerminalSingleDuctInletSideMixer.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctInletSideMixer.cpp`, and `src/epmodel/test/AirTerminalSingleDuctInletSideMixer_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted outdoor-air, unit-object, mixer-connection, and node/DSOA helpers when relationship parity expands.

    /** @name Per Person Ventilation Rate Mode */
    //@{
    std::string perPersonVentilationRateMode() const;
    bool setPerPersonVentilationRateMode(const std::string& perPersonVentilationRateMode);
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
