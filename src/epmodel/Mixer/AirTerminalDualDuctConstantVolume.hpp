/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALDUALDUCTCONSTANTVOLUME_HPP
#define EPMODEL_AIRTERMINALDUALDUCTCONSTANTVOLUME_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirTerminalDualDuctConstantVolume_Impl;
  }

  class EPMODEL_API AirTerminalDualDuctConstantVolume : public ModelObject
  {
   public:
    explicit AirTerminalDualDuctConstantVolume(const Model& model);

    virtual ~AirTerminalDualDuctConstantVolume() override = default;
    AirTerminalDualDuctConstantVolume(const AirTerminalDualDuctConstantVolume& other) = default;
    AirTerminalDualDuctConstantVolume(AirTerminalDualDuctConstantVolume&& other) = default;
    AirTerminalDualDuctConstantVolume& operator=(const AirTerminalDualDuctConstantVolume&) = default;
    AirTerminalDualDuctConstantVolume& operator=(AirTerminalDualDuctConstantVolume&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model scalar accessor names for this model-counterpart class.
    // - Field Mapping: maximumAirFlowRate maps directly to EnergyPlus AirTerminal:DualDuct:ConstantVolume Maximum Air Flow Rate.
    // - Field Mapping: Availability Schedule Name, Air Outlet Node Name, Hot Air Inlet Node Name, and Cold Air Inlet Node Name are relationship fields and are
    //   intentionally excluded from scalar accessors.
    // - ForwardTranslator evidence: translateAirTerminalDualDuctConstantVolume writes only those relationship fields plus Maximum Air Flow Rate scalar.
    // - TODO(parity): Add relationship APIs incrementally after scalar scaffold saturation.
    boost::optional<double> maximumAirFlowRate() const;
    bool setMaximumAirFlowRate(double maximumAirFlowRate);
    bool isMaximumAirFlowRateAutosized() const;
    void autosizeMaximumAirFlowRate();

   protected:
    using ImplType = detail::AirTerminalDualDuctConstantVolume_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirTerminalDualDuctConstantVolume(std::shared_ptr<detail::AirTerminalDualDuctConstantVolume_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
