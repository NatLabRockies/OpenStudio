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

  /**
   * \brief Constant-volume cooled beam terminal with a typed chilled-water coil and beam sizing fields.
   *
   * \par EnergyPlus object
   * Encapsulates `OS:AirTerminal:SingleDuct:ConstantVolume:CooledBeam`. This is an OpenStudio schema object,
   * not a direct EnergyPlus object.
   *
   * \par Important behavior
   * The cooling coil and terminal share the zone-branch and chilled-water topology. `addToNode` prepares that
   * topology, and removal cleans the owned coil only after the parent and plant references can be removed safely.
   *
   * \par OpenStudio Model API
   * Counterpart: `openstudio::model::AirTerminalSingleDuctConstantVolumeCooledBeam`. Beam sizing fields, availability,
   * cooling-coil relationships, and zone/plant insertion are represented. The epmodel constructor is also available
   * without the Model API's required coil relationship.
   *
   * \par Known limitations
   * The OS-prefixed object and coil do not round-trip through the EnergyPlus-schema `epmodel::Model::load` path.
   * Deep cloning and family-specific autosized-result queries are not exposed.
   */
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
