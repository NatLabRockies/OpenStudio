/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMECOOLEDBEAM_IMPL_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMECOOLEDBEAM_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

class AirLoopHVAC;
class ModelObject;
class Schedule;

namespace detail {

    class EPMODEL_API AirTerminalSingleDuctConstantVolumeCooledBeam_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~AirTerminalSingleDuctConstantVolumeCooledBeam_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      bool addToNode(Node& node) override;

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

  std::vector<std::string> cooledBeamTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
