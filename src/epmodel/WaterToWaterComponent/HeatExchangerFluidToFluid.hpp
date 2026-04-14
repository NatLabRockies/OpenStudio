/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATEXCHANGERFLUIDTOFLUID_HPP
#define EPMODEL_HEATEXCHANGERFLUIDTOFLUID_HPP

#include "EPModelAPI.hpp"
#include "WaterToWaterComponent/WaterToWaterComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;
class Schedule;
class Node;

namespace detail {
class HeatExchangerFluidToFluid_Impl;
}

class EPMODEL_API HeatExchangerFluidToFluid : public WaterToWaterComponent
{
 public:
  explicit HeatExchangerFluidToFluid(const Model& model);

  virtual ~HeatExchangerFluidToFluid() override = default;
  HeatExchangerFluidToFluid(const HeatExchangerFluidToFluid& other) = default;
  HeatExchangerFluidToFluid(HeatExchangerFluidToFluid&& other) = default;
  HeatExchangerFluidToFluid& operator=(const HeatExchangerFluidToFluid&) = default;
  HeatExchangerFluidToFluid& operator=(HeatExchangerFluidToFluid&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> heatExchangeModelTypeValues();
  static std::vector<std::string> controlTypeValues();
  static std::vector<std::string> heatTransferMeteringEndUseTypeValues();
  static std::vector<std::string> componentOverrideCoolingControlTemperatureModeValues();

  // Schema Alignment Notes:
  // - Status: Parity with documented deltas. The canonical schedule and override-node relationship surface is aligned with the scalar API.
  // - Canonical Counterpart: openstudio::model::HeatExchangerFluidToFluid.
  // - Implemented Parity: Scalar accessors, availability schedule, and the two component-override inlet-node reference links preserve the
  //   canonical model API shape.
  // - Documented Delta: Broader loop-coupling behavior remains delegated to the shared water-to-water topology layer rather than adding extra
  //   wrapper-local policy here.
  // - Field/Storage Mapping: Scalar wrappers target EnergyPlus `HeatExchanger:FluidToFluid` fields directly, and the schedule/node relationships
  //   are stored as direct object references on the same object.
  // - Evidence: `src/model/HeatExchangerFluidToFluid.hpp`, `src/model/HeatExchangerFluidToFluid.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateHeatExchangerFluidToFluid.cpp`.
  // - Remaining Parity Work: Only shared water-to-water topology work should be considered next if multiple wrappers need it.
  boost::optional<Schedule> availabilitySchedule() const;
  bool setAvailabilitySchedule(Schedule& schedule);
  void resetAvailabilitySchedule();

  boost::optional<double> loopDemandSideDesignFlowRate() const;
  bool isLoopDemandSideDesignFlowRateAutosized() const;
  bool setLoopDemandSideDesignFlowRate(double loopDemandSideDesignFlowRate);
  void autosizeLoopDemandSideDesignFlowRate();

  boost::optional<double> loopSupplySideDesignFlowRate() const;
  bool isLoopSupplySideDesignFlowRateAutosized() const;
  bool setLoopSupplySideDesignFlowRate(double loopSupplySideDesignFlowRate);
  void autosizeLoopSupplySideDesignFlowRate();

  std::string heatExchangeModelType() const;
  bool isHeatExchangeModelTypeDefaulted() const;
  bool setHeatExchangeModelType(const std::string& heatExchangeModelType);
  void resetHeatExchangeModelType();

  boost::optional<double> heatExchangerUFactorTimesAreaValue() const;
  bool isHeatExchangerUFactorTimesAreaValueAutosized() const;
  bool setHeatExchangerUFactorTimesAreaValue(double heatExchangerUFactorTimesAreaValue);
  void autosizeHeatExchangerUFactorTimesAreaValue();

  std::string controlType() const;
  bool isControlTypeDefaulted() const;
  bool setControlType(const std::string& controlType);
  void resetControlType();

  double minimumTemperatureDifferencetoActivateHeatExchanger() const;
  bool isMinimumTemperatureDifferencetoActivateHeatExchangerDefaulted() const;
  bool setMinimumTemperatureDifferencetoActivateHeatExchanger(double minimumTemperatureDifferencetoActivateHeatExchanger);
  void resetMinimumTemperatureDifferencetoActivateHeatExchanger();

  std::string heatTransferMeteringEndUseType() const;
  bool isHeatTransferMeteringEndUseTypeDefaulted() const;
  bool setHeatTransferMeteringEndUseType(const std::string& heatTransferMeteringEndUseType);
  void resetHeatTransferMeteringEndUseType();

  boost::optional<Node> componentOverrideLoopSupplySideInletNode() const;
  bool setComponentOverrideLoopSupplySideInletNode(const Node& node);
  void resetComponentOverrideLoopSupplySideInletNode();

  boost::optional<Node> componentOverrideLoopDemandSideInletNode() const;
  bool setComponentOverrideLoopDemandSideInletNode(const Node& node);
  void resetComponentOverrideLoopDemandSideInletNode();

  std::string componentOverrideCoolingControlTemperatureMode() const;
  bool isComponentOverrideCoolingControlTemperatureModeDefaulted() const;
  bool setComponentOverrideCoolingControlTemperatureMode(const std::string& componentOverrideCoolingControlTemperatureMode);
  void resetComponentOverrideCoolingControlTemperatureMode();

  double sizingFactor() const;
  bool isSizingFactorDefaulted() const;
  bool setSizingFactor(double sizingFactor);
  void resetSizingFactor();

  boost::optional<double> operationMinimumTemperatureLimit() const;
  bool setOperationMinimumTemperatureLimit(double operationMinimumTemperatureLimit);
  void resetOperationMinimumTemperatureLimit();

  boost::optional<double> operationMaximumTemperatureLimit() const;
  bool setOperationMaximumTemperatureLimit(double operationMaximumTemperatureLimit);
  void resetOperationMaximumTemperatureLimit();

  boost::optional<double> autosizedLoopDemandSideDesignFlowRate() const;
  boost::optional<double> autosizedLoopSupplySideDesignFlowRate() const;
  boost::optional<double> autosizedHeatExchangerUFactorTimesAreaValue() const;

 protected:
  using ImplType = detail::HeatExchangerFluidToFluid_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit HeatExchangerFluidToFluid(std::shared_ptr<detail::HeatExchangerFluidToFluid_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
