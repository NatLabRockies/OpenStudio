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
  class ModelObject;
  class Node;
  class Schedule;

  namespace detail {
    class AirTerminalSingleDuctConstantVolumeCooledBeam_Impl;
  }

  class EPMODEL_API AirTerminalSingleDuctConstantVolumeCooledBeam : public StraightComponent
  {
   public:
    explicit AirTerminalSingleDuctConstantVolumeCooledBeam(const Model& model);
    AirTerminalSingleDuctConstantVolumeCooledBeam(const Model& model, Schedule& availabilitySchedule, ModelObject& coilCoolingCooledBeam);

    virtual ~AirTerminalSingleDuctConstantVolumeCooledBeam() override = default;
    AirTerminalSingleDuctConstantVolumeCooledBeam(const AirTerminalSingleDuctConstantVolumeCooledBeam& other) = default;
    AirTerminalSingleDuctConstantVolumeCooledBeam(AirTerminalSingleDuctConstantVolumeCooledBeam&& other) = default;
    AirTerminalSingleDuctConstantVolumeCooledBeam& operator=(const AirTerminalSingleDuctConstantVolumeCooledBeam&) = default;
    AirTerminalSingleDuctConstantVolumeCooledBeam& operator=(AirTerminalSingleDuctConstantVolumeCooledBeam&&) = default;

    static IddObjectType iddObjectType();

    bool addToNode(Node& node);

    static std::vector<std::string> cooledBeamTypeValues();

    // Schema Alignment Notes:
    // - Status: Connectivity Parity. The cooled-beam scalar surface is aligned, and the availability schedule, cooling coil, zone-branch
    //   insertion, and remove-time cleanup path are exposed, while the family-specific autosized-result query helpers remain omitted
    //   from the public epmodel API.
    // - Canonical Counterpart: openstudio::model::AirTerminalSingleDuctConstantVolumeCooledBeam.
    // - Implemented Parity: `availabilitySchedule`, `coilCoolingCooledBeam`, `setAvailabilitySchedule`, `setCoolingCoil`, `addToNode`,
    //   remove-time loop cleanup, `cooledBeamType`, `supplyAirVolumetricFlowRate`, `maximumTotalChilledWaterVolumetricFlowRate`,
    //   `numberofBeams`, `beamLength`, `designInletWaterTemperature`, `designOutletWaterTemperature`, and `coefficientofInductionKin`
    //   are exposed while keeping connectivity behavior focused on the canonical zone-branch and chilled-water plant paths.
    // - Documented Delta: The public cooling-coil target remains surfaced as a raw epmodel `ModelObject` for existing API compatibility; epmodel now provides
    //   a dedicated cooled-beam coil wrapper for plant connectivity and this terminal validates the underlying IDD target type.
    // - Documented Delta: The epmodel-only default constructor is retained, and the family-specific autosized-result query helpers are still not surfaced in the
    //   public API until shared sizing-result infrastructure exists.
    // - Field/Storage Mapping: The availability-schedule pointer, cooling-coil pointer, and preserved scalars map directly to the OpenStudio
    //   `OS:AirTerminal:SingleDuct:ConstantVolume:CooledBeam` fields.
    // - Evidence: `src/model/AirTerminalSingleDuctConstantVolumeCooledBeam.hpp`, `src/model/AirTerminalSingleDuctConstantVolumeCooledBeam.cpp`,
    //   `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctConstantVolumeCooledBeam.cpp`, and
    //   `src/epmodel/test/AirTerminalSingleDuctConstantVolumeCooledBeam_GTest.cpp`.
    // - Remaining Parity Work: Expose the family-specific autosized-result query helpers once shared sizing-result plumbing exists.
    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    ModelObject coilCoolingCooledBeam() const;
    bool setCoolingCoil(ModelObject& coilCoolingCooledBeam);

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
