/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMECOOLEDBEAM_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMECOOLEDBEAM_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class HVACComponent;
  class Node;
  class Schedule;

  namespace detail {
    class AirTerminalSingleDuctConstantVolumeCooledBeam_Impl;
  }

  class EPMODEL_API AirTerminalSingleDuctConstantVolumeCooledBeam : public StraightComponent
  {
   public:
    explicit AirTerminalSingleDuctConstantVolumeCooledBeam(const Model& model);
    explicit AirTerminalSingleDuctConstantVolumeCooledBeam(const Model& model, Schedule& availabilitySchedule, HVACComponent& coilCoolingCooledBeam);

    virtual ~AirTerminalSingleDuctConstantVolumeCooledBeam() override = default;
    AirTerminalSingleDuctConstantVolumeCooledBeam(const AirTerminalSingleDuctConstantVolumeCooledBeam& other) = default;
    AirTerminalSingleDuctConstantVolumeCooledBeam(AirTerminalSingleDuctConstantVolumeCooledBeam&& other) = default;
    AirTerminalSingleDuctConstantVolumeCooledBeam& operator=(const AirTerminalSingleDuctConstantVolumeCooledBeam&) = default;
    AirTerminalSingleDuctConstantVolumeCooledBeam& operator=(AirTerminalSingleDuctConstantVolumeCooledBeam&&) = default;

    static IddObjectType iddObjectType();

    bool addToNode(Node& node);

    static std::vector<std::string> cooledBeamTypeValues();

    // Schema Alignment Notes:
    // - Status: Near Parity. The cooled-beam scalar surface is aligned, and the availability schedule, typed cooling coil, zone-branch
    //   insertion, and owner-local remove-time cleanup path are exposed, while deep-clone behavior and the family-specific autosized-result
    //   query helpers remain omitted from the public epmodel API.
    // - Canonical Counterpart: openstudio::model::AirTerminalSingleDuctConstantVolumeCooledBeam.
    // - Implemented Parity: `availabilitySchedule`, `coilCoolingCooledBeam`, `setAvailabilitySchedule`, `setCoolingCoil`, `addToNode`,
    //   remove-time loop cleanup and owned-coil deletion, `cooledBeamType`, `supplyAirVolumetricFlowRate`,
    //   `maximumTotalChilledWaterVolumetricFlowRate`,
    //   `numberofBeams`, `beamLength`, `designInletWaterTemperature`, `designOutletWaterTemperature`, and `coefficientofInductionKin`
    //   are exposed while keeping connectivity behavior focused on the canonical zone-branch and chilled-water plant paths.
    // - Field/Storage Mapping: The availability-schedule pointer, canonical `HVACComponent` cooling-coil relationship, and preserved scalars map
    //   directly to the OpenStudio `OS:AirTerminal:SingleDuct:ConstantVolume:CooledBeam` fields. `CoilCoolingCooledBeam` provides the expected
    //   plant-demand topology, and terminal removal cascades to that owned coil only after terminal topology teardown succeeds.
    // - Documented Delta: The epmodel-only default constructor is retained. Deep cloning of the owned coil and the family-specific
    //   autosized-result query helpers are not surfaced until shared clone and sizing-result infrastructure exists.
    // - Evidence: `src/model/AirTerminalSingleDuctConstantVolumeCooledBeam.hpp`, `src/model/AirTerminalSingleDuctConstantVolumeCooledBeam.cpp`,
    //   `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctConstantVolumeCooledBeam.cpp`, and
    //   `src/epmodel/test/AirTerminalSingleDuctConstantVolumeCooledBeam_GTest.cpp`.
    // - Remaining Parity Work: Add canonical deep-clone behavior for the owned coil and expose the family-specific autosized-result query
    //   helpers once shared clone and sizing-result plumbing exists.
    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    HVACComponent coilCoolingCooledBeam() const;
    bool setCoolingCoil(HVACComponent& coilCoolingCooledBeam);

    std::string cooledBeamType() const;
    bool setCooledBeamType(const std::string& cooledBeamType);

    boost::optional<double> supplyAirVolumetricFlowRate() const;
    bool isSupplyAirVolumetricFlowRateDefaulted() const;
    bool isSupplyAirVolumetricFlowRateAutosized() const;
    bool setSupplyAirVolumetricFlowRate(double supplyAirVolumetricFlowRate);
    void resetSupplyAirVolumetricFlowRate();
    void autosizeSupplyAirVolumetricFlowRate();

    boost::optional<double> maximumTotalChilledWaterVolumetricFlowRate() const;
    bool isMaximumTotalChilledWaterVolumetricFlowRateDefaulted() const;
    bool isMaximumTotalChilledWaterVolumetricFlowRateAutosized() const;
    bool setMaximumTotalChilledWaterVolumetricFlowRate(double maximumTotalChilledWaterVolumetricFlowRate);
    void resetMaximumTotalChilledWaterVolumetricFlowRate();
    void autosizeMaximumTotalChilledWaterVolumetricFlowRate();

    boost::optional<int> numberofBeams() const;
    bool isNumberofBeamsDefaulted() const;
    bool isNumberofBeamsAutosized() const;
    bool setNumberofBeams(int numberofBeams);
    void resetNumberofBeams();
    void autosizeNumberofBeams();

    boost::optional<double> beamLength() const;
    bool isBeamLengthDefaulted() const;
    bool isBeamLengthAutosized() const;
    bool setBeamLength(double beamLength);
    void resetBeamLength();
    void autosizeBeamLength();

    double designInletWaterTemperature() const;
    bool isDesignInletWaterTemperatureDefaulted() const;
    bool setDesignInletWaterTemperature(double designInletWaterTemperature);
    void resetDesignInletWaterTemperature();

    double designOutletWaterTemperature() const;
    bool isDesignOutletWaterTemperatureDefaulted() const;
    bool setDesignOutletWaterTemperature(double designOutletWaterTemperature);
    void resetDesignOutletWaterTemperature();

    boost::optional<double> coefficientofInductionKin() const;
    bool isCoefficientofInductionKinDefaulted() const;
    bool isCoefficientofInductionKinAutocalculated() const;
    bool setCoefficientofInductionKin(double coefficientofInductionKin);
    void resetCoefficientofInductionKin();
    void autocalculateCoefficientofInductionKin();

   protected:
    using ImplType = detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirTerminalSingleDuctConstantVolumeCooledBeam(std::shared_ptr<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
