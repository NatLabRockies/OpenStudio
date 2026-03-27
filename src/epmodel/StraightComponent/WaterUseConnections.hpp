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
    // - Status: Scalar Parity. The canonical water-use-connections scalar surface is present, while node, schedule, storage, and equipment helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::WaterUseConnections.
    // - Implemented Parity: The preserved scalar API matches the drain-water-heat-exchanger type, destination, and U-factor/area accessors with matching optional semantics.
    // - Documented Delta: Node, schedule, storage, and equipment relationship helpers remain intentionally excluded from this scalar pass.
    // - Field/Storage Mapping: These accessors map directly to EnergyPlus `WaterUse:Connections` scalar fields used by the forward translator.
    // - Evidence: `src/model/WaterUseConnections.hpp`, `src/model/WaterUseConnections.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateWaterUseConnections.cpp`.
    // - Remaining Parity Work: Add the omitted relationship helpers without changing the preserved scalar signatures.
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
