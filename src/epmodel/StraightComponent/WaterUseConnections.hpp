/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WATERUSECONNECTIONS_HPP
#define EPMODEL_WATERUSECONNECTIONS_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class WaterUseConnections_Impl;
  }

  class EPMODEL_API WaterUseConnections : public StraightComponent
  {
   public:
    explicit WaterUseConnections(const Model& model);

    virtual ~WaterUseConnections() override = default;
    WaterUseConnections(const WaterUseConnections& other) = default;
    WaterUseConnections(WaterUseConnections&& other) = default;
    WaterUseConnections& operator=(const WaterUseConnections&) = default;
    WaterUseConnections& operator=(WaterUseConnections&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> drainWaterHeatExchangerTypeValues();
    static std::vector<std::string> drainWaterHeatExchangerDestinationValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::WaterUseConnections scalar accessor names/signatures for counterpart parity.
    // - Field Mapping: drainWaterHeatExchangerType/destination map directly to EnergyPlus WaterUse:Connections Drain Water Heat Exchanger Type/Destination fields.
    // - Field Mapping: drainWaterHeatExchangerUFactorTimesArea maps to OS_WaterUse_ConnectionsFields::DrainWaterHeatExchangerUFactorTimesArea with optional real semantics.
    // - ForwardTranslator evidence: ForwardTranslateWaterUseConnections.cpp keeps these scalars mapped while excluding relationship fields.
    // - TODO(parity): Relationship-like node, schedule, storage, and equipment references still need a dedicated pass.
    std::string drainWaterHeatExchangerType() const;
    bool setDrainWaterHeatExchangerType(const std::string& drainWaterHeatExchangerType);

    std::string drainWaterHeatExchangerDestination() const;
    bool setDrainWaterHeatExchangerDestination(const std::string& drainWaterHeatExchangerDestination);

    boost::optional<double> drainWaterHeatExchangerUFactorTimesArea() const;
    bool setDrainWaterHeatExchangerUFactorTimesArea(double drainWaterHeatExchangerUFactorTimesArea);
    void resetDrainWaterHeatExchangerUFactorTimesArea();

   protected:
    using ImplType = detail::WaterUseConnections_Impl;

    friend class Model;
    explicit WaterUseConnections(std::shared_ptr<detail::WaterUseConnections_Impl> impl);
  };

  using OptionalWaterUseConnections = boost::optional<WaterUseConnections>;
  using WaterUseConnectionsVector = std::vector<WaterUseConnections>;

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_WATERUSECONNECTIONS_HPP
