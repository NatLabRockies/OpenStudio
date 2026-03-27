/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACDEHUMIDIFIERDX_HPP
#define EPMODEL_ZONEHVACDEHUMIDIFIERDX_HPP

#include "EPModelAPI.hpp"
#include "ZoneHVACComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneHVACDehumidifierDX_Impl;
  }

  class EPMODEL_API ZoneHVACDehumidifierDX : public ZoneHVACComponent
  {
   public:
    explicit ZoneHVACDehumidifierDX(const Model& model);

    virtual ~ZoneHVACDehumidifierDX() override = default;
    ZoneHVACDehumidifierDX(const ZoneHVACDehumidifierDX& other) = default;
    ZoneHVACDehumidifierDX(ZoneHVACDehumidifierDX&& other) = default;
    ZoneHVACDehumidifierDX& operator=(const ZoneHVACDehumidifierDX&) = default;
    ZoneHVACDehumidifierDX& operator=(ZoneHVACDehumidifierDX&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Scalar Parity. The scalar dehumidifier fields are aligned, and the relationship-bearing references remain intentionally out of the public surface.
    // - Canonical Counterpart: openstudio::model::ZoneHVACDehumidifierDX.
    // - Implemented Parity: `ratedWaterRemoval`, `ratedEnergyFactor`, `ratedAirFlowRate`, the min/max dry-bulb limits, and `offCycleParasiticElectricLoad` map directly to the EnergyPlus dehumidifier fields.
    // - Documented Delta: Availability schedule, inlet/outlet nodes, curve references, and the condensate storage tank are relationship-like links and stay outside this scalar wrapper.
    // - Field/Storage Mapping: Scalar values are stored directly on the EnergyPlus object while the omitted links are modeled through topology/child-object state elsewhere.
    // - Evidence: `src/model/ZoneHVACDehumidifierDX.hpp`, `src/model/ZoneHVACDehumidifierDX.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACDehumidifierDX.cpp`, and `src/epmodel/test/ZoneHVACDehumidifierDX_GTest.cpp`.
    // - Remaining Parity Work: Add explicit relationship and curve helpers only if the canonical model surface requires them to be first-class epmodel APIs.
    double ratedWaterRemoval() const;
    bool setRatedWaterRemoval(double ratedWaterRemoval);

    double ratedEnergyFactor() const;
    bool setRatedEnergyFactor(double ratedEnergyFactor);

    double ratedAirFlowRate() const;
    bool setRatedAirFlowRate(double ratedAirFlowRate);

    double minimumDryBulbTemperatureforDehumidifierOperation() const;
    bool setMinimumDryBulbTemperatureforDehumidifierOperation(double minimumDryBulbTemperatureforDehumidifierOperation);

    double maximumDryBulbTemperatureforDehumidifierOperation() const;
    bool setMaximumDryBulbTemperatureforDehumidifierOperation(double maximumDryBulbTemperatureforDehumidifierOperation);

    double offCycleParasiticElectricLoad() const;
    bool setOffCycleParasiticElectricLoad(double offCycleParasiticElectricLoad);

   protected:
    using ImplType = detail::ZoneHVACDehumidifierDX_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACDehumidifierDX(std::shared_ptr<detail::ZoneHVACDehumidifierDX_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
