/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEFOURPIPEBEAM_IMPL_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEFOURPIPEBEAM_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit.hpp"

namespace openstudio {
namespace epmodel {

  class HVACComponent;
  class ModelObject;
  class Node;
  class PlantLoop;
  class Schedule;

  namespace detail {

    class EPMODEL_API AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      std::vector<ModelObject> children() const override;
      std::vector<openstudio::IdfObject> remove() override;
      bool removeFromLoop() override;
      boost::optional<ZoneHVACAirDistributionUnit> zoneHVACAirDistributionUnit() const;
      bool addToNode(Node& node) override;

      Schedule primaryAirAvailabilitySchedule() const;
      bool setPrimaryAirAvailabilitySchedule(Schedule& schedule);

      Schedule coolingAvailabilitySchedule() const;
      bool setCoolingAvailabilitySchedule(Schedule& schedule);

      Schedule heatingAvailabilitySchedule() const;
      bool setHeatingAvailabilitySchedule(Schedule& schedule);

      boost::optional<Node> primaryAirInletNode() const;
      boost::optional<Node> primaryAirOutletNode() const;

      boost::optional<HVACComponent> coolingCoil() const;
      bool setCoolingCoil(const HVACComponent& coolingCoil);

      boost::optional<HVACComponent> heatingCoil() const;
      bool setHeatingCoil(const HVACComponent& heatingCoil);

      boost::optional<double> designPrimaryAirVolumeFlowRate() const;
      bool isDesignPrimaryAirVolumeFlowRateAutosized() const;
      bool setDesignPrimaryAirVolumeFlowRate(double designPrimaryAirVolumeFlowRate);
      void autosizeDesignPrimaryAirVolumeFlowRate();

      boost::optional<double> designChilledWaterVolumeFlowRate() const;
      bool isDesignChilledWaterVolumeFlowRateAutosized() const;
      bool setDesignChilledWaterVolumeFlowRate(double designChilledWaterVolumeFlowRate);
      void autosizeDesignChilledWaterVolumeFlowRate();

      boost::optional<double> designHotWaterVolumeFlowRate() const;
      bool isDesignHotWaterVolumeFlowRateAutosized() const;
      bool setDesignHotWaterVolumeFlowRate(double designHotWaterVolumeFlowRate);
      void autosizeDesignHotWaterVolumeFlowRate();

      boost::optional<double> zoneTotalBeamLength() const;
      bool isZoneTotalBeamLengthAutosized() const;
      bool setZoneTotalBeamLength(double zoneTotalBeamLength);
      void autosizeZoneTotalBeamLength();

      double ratedPrimaryAirFlowRateperBeamLength() const;
      bool isRatedPrimaryAirFlowRateperBeamLengthDefaulted() const;
      bool setRatedPrimaryAirFlowRateperBeamLength(double ratedPrimaryAirFlowRateperBeamLength);
      void resetRatedPrimaryAirFlowRateperBeamLength();

      boost::optional<PlantLoop> chilledWaterPlantLoop() const;
      boost::optional<Node> chilledWaterInletNode() const;
      boost::optional<Node> chilledWaterOutletNode() const;

      boost::optional<PlantLoop> hotWaterPlantLoop() const;
      boost::optional<Node> hotWaterInletNode() const;
      boost::optional<Node> hotWaterOutletNode() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
