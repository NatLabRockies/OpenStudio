/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_TESTFAILUREPOINT_HPP
#define EPMODEL_TESTFAILUREPOINT_HPP

#include "EPModelAPI.hpp"

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {

    // Internal checkpoints used only by scoped EPModel test support. Production
    // object APIs must not accept or return these values.
    enum class TestFailurePoint
    {
      None,
      AirLoopAfterTerminalClonePrepared,
      AirLoopAfterFirstPlantReconnectionPrepared,
      AirLoopAfterPlantReconnectionPrepared,
      AirLoopAfterBranchReservationPrepared,
      AirLoopAfterZonePrepared,
      AirLoopAfterTerminalFirstZoneAttachmentPrepared,
      AirLoopBeforeTerminalAttachment,
      AirLoopAfterDualDuctTerminalPrepared,
      AirLoopAfterDualDuctZoneObjectsPrepared,
      SingleDuctTerminalAfterAirDistributionUnitUpdate,
      FourPipeInductionAfterTopologyPrepared,
      ParallelPIUAfterTopologyPrepared,
      SeriesPIUAfterTopologyPrepared,
      VAVReheatAfterCoilAirPathPrepared,
      ZoneEquipmentAfterTargetPrepared,
      ZoneEquipmentAfterRowAdded,
      PlantLoopAfterPipeBranchAttachmentPrepared,
      PlantLoopAfterPipeBranchRemovalPrepared,
      PlantLoopAfterWaterCoilBranchAttachmentPrepared,
      PlantLoopAfterChillerElectricEIRHeatRecoveryBranchAttachmentPrepared,
      PlantLoopAfterFluidToFluidHeatExchangerBranchAttachmentPrepared,
      PlantLoopAfterThermalStorageSourceBranchAttachmentPrepared,
      PlantLoopAfterEquationFitHeatPumpBranchAttachmentPrepared,
      SizingPlantAfterFirstCompanionPointerWritten,
    };

    EPMODEL_API bool testFailurePointReached(const Model& model, TestFailurePoint point);

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_TESTFAILUREPOINT_HPP
