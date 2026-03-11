/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACDEHUMIDIFIERDX_HPP
#define EPMODEL_ZONEHVACDEHUMIDIFIERDX_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneHVACDehumidifierDX_Impl;
  }

  class EPMODEL_API ZoneHVACDehumidifierDX : public ModelObject
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
    // - API: Preserve the openstudio::model scalar accessor names/signatures for ratedWaterRemoval, ratedEnergyFactor,
    //   ratedAirFlowRate, minimum/maximumDryBulbTemperatureforDehumidifierOperation, and offCycleParasiticElectricLoad.
    // - Field Mapping: These scalars map directly to the EnergyPlus ZoneHVAC:Dehumidifier:DX fields enumerated by
    //   OS_ZoneHVAC_Dehumidifier_DXFields and are emitted via ForwardTranslateZoneHVACDehumidifierDX.cpp.
    // - Field Mapping: Availability schedule, inlet/outlet node names, curve references, and the condensate collection
    //   water storage tank are relationship-like references and are intentionally excluded from this scalar-only API.
    // - TODO(parity): Expand the schema-alignment coverage with the remaining relationship/curve APIs once scalar
    //   saturation has stabilized.
    double ratedWaterRemoval() const;
    double ratedEnergyFactor() const;
    double ratedAirFlowRate() const;
    double minimumDryBulbTemperatureforDehumidifierOperation() const;
    double maximumDryBulbTemperatureforDehumidifierOperation() const;
    double offCycleParasiticElectricLoad() const;

    bool setRatedWaterRemoval(double ratedWaterRemoval);
    bool setRatedEnergyFactor(double ratedEnergyFactor);
    bool setRatedAirFlowRate(double ratedAirFlowRate);
    bool setMinimumDryBulbTemperatureforDehumidifierOperation(double minimumDryBulbTemperatureforDehumidifierOperation);
    bool setMaximumDryBulbTemperatureforDehumidifierOperation(double maximumDryBulbTemperatureforDehumidifierOperation);
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
