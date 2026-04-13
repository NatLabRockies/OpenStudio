/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACDEHUMIDIFIERDX_HPP
#define EPMODEL_ZONEHVACDEHUMIDIFIERDX_HPP

#include "EPModelAPI.hpp"
#include "ZoneHVACComponent.hpp"

#include <vector>
#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;
  class Curve;
  class ModelObject;

  namespace detail {
    class ZoneHVACDehumidifierDX_Impl;
  }

  class EPMODEL_API ZoneHVACDehumidifierDX : public ZoneHVACComponent
  {
   public:
    explicit ZoneHVACDehumidifierDX(const Model& model);
    explicit ZoneHVACDehumidifierDX(const Model& model, const Curve& waterRemovalCurve, const Curve& energyFactorCurve,
                                    const Curve& partLoadFractionCurve);

    virtual ~ZoneHVACDehumidifierDX() override = default;
    ZoneHVACDehumidifierDX(const ZoneHVACDehumidifierDX& other) = default;
    ZoneHVACDehumidifierDX(ZoneHVACDehumidifierDX&& other) = default;
    ZoneHVACDehumidifierDX& operator=(const ZoneHVACDehumidifierDX&) = default;
    ZoneHVACDehumidifierDX& operator=(ZoneHVACDehumidifierDX&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Parity with documented deltas. The canonical availability-schedule and curve relationships are exposed directly, while
    //   the commented-out condensate tank placeholder remains omitted here just as it is in canonical `openstudio::model`.
    // - Canonical Counterpart: openstudio::model::ZoneHVACDehumidifierDX.
    // - Implemented Parity: `availabilitySchedule`, `waterRemovalCurve`, `energyFactorCurve`, `partLoadFractionCorrelationCurve`, the
    //   canonical constructor that takes the three curves, and the scalar fields all map directly to the EnergyPlus object.
    // - Documented Delta: The commented-out condensate storage tank placeholder remains omitted because the canonical model wrapper also
    //   does not currently expose it as an active public API.
    // - Field/Storage Mapping: Availability schedule, node links, and curve references are stored directly on the EnergyPlus object.
    // - Evidence: `src/model/ZoneHVACDehumidifierDX.hpp`, `src/model/ZoneHVACDehumidifierDX.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACDehumidifierDX.cpp`, and `src/epmodel/test/ZoneHVACDehumidifierDX_GTest.cpp`.
    // - Remaining Parity Work: None on the implemented canonical surface.
    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    double ratedWaterRemoval() const;
    bool setRatedWaterRemoval(double ratedWaterRemoval);

    double ratedEnergyFactor() const;
    bool setRatedEnergyFactor(double ratedEnergyFactor);

    double ratedAirFlowRate() const;
    bool setRatedAirFlowRate(double ratedAirFlowRate);

    Curve waterRemovalCurve() const;
    bool setWaterRemovalCurve(const Curve& curve);

    Curve energyFactorCurve() const;
    bool setEnergyFactorCurve(const Curve& curve);

    Curve partLoadFractionCorrelationCurve() const;
    bool setPartLoadFractionCorrelationCurve(const Curve& curve);

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
