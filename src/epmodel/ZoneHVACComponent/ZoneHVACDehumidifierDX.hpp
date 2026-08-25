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

/** \brief A direct-expansion dehumidifier serving a thermal zone.
 *
 * \par EnergyPlus object
 * \epobject{group-zone-forced-air-units.html#zonehvacdehumidifierdx,ZoneHVAC:Dehumidifier:DX}
 *
 * \par Important behavior
 * Availability, the three performance-curve relationships, scalar fields, and thermal-zone attachment methods are available.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::ZoneHVACDehumidifierDX</code>.
 *
 * \par Known limitations
 * No active condensate-storage-tank API is exposed; the corresponding Model declarations are not active public methods either.
 */
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
