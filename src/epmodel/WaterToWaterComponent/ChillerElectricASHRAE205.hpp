/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CHILLERELECTRICASHRAE205_HPP
#define EPMODEL_CHILLERELECTRICASHRAE205_HPP

#include "EPModelAPI.hpp"
#include "WaterToWaterComponent/WaterToWaterComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ChillerElectricASHRAE205_Impl;
}

class EPMODEL_API ChillerElectricASHRAE205 : public WaterToWaterComponent
{
 public:
  explicit ChillerElectricASHRAE205(const Model& model);

  virtual ~ChillerElectricASHRAE205() override = default;
  ChillerElectricASHRAE205(const ChillerElectricASHRAE205& other) = default;
  ChillerElectricASHRAE205(ChillerElectricASHRAE205&& other) = default;
  ChillerElectricASHRAE205& operator=(const ChillerElectricASHRAE205&) = default;
  ChillerElectricASHRAE205& operator=(ChillerElectricASHRAE205&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> performanceInterpolationMethodValues();
  static std::vector<std::string> ambientTemperatureIndicatorValues();
  static std::vector<std::string> chillerFlowModeValues();

  // Schema Alignment Notes:
  // - Status: Scalar Parity. The ASHRAE205 chiller scalar surface is aligned, while representation-file and node/link behavior remains excluded.
  // - Canonical Counterpart: openstudio::model::ChillerElectricASHRAE205.
  // - Implemented Parity: Scalar accessors for capacity, COP, flow rates, PLR limits, condenser behavior, heat recovery, and sizing preserve the canonical model API shape.
  // - Documented Delta: Representation-file, ambient schedule/zone, and node-link APIs are intentionally excluded in this pass.
  // - Field/Storage Mapping: Scalar wrappers target EnergyPlus `Chiller:Electric:ASHRAE205` fields directly; external-file linkage stays in separate storage-aware handling.
  // - Evidence: `src/model/ChillerElectricASHRAE205.hpp`, `src/model/ChillerElectricASHRAE205.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateChillerElectricASHRAE205.cpp`.
  // - Remaining Parity Work: Add the excluded relationship and external-file APIs only if the family advances beyond scalar parity.
  std::string performanceInterpolationMethod() const;
  bool setPerformanceInterpolationMethod(const std::string& performanceInterpolationMethod);

  boost::optional<double> ratedCapacity() const;
  bool isRatedCapacityAutosized() const;
  bool setRatedCapacity(double ratedCapacity);
  void autosizeRatedCapacity();

  double sizingFactor() const;
  bool setSizingFactor(double sizingFactor);

  std::string ambientTemperatureIndicator() const;

  boost::optional<std::string> ambientTemperatureOutdoorAirNodeName() const;
  bool setAmbientTemperatureOutdoorAirNodeName(const std::string& ambientTemperatureOutdoorAirNodeName);
  void resetAmbientTemperatureOutdoorAirNodeName();

  boost::optional<double> chilledWaterMaximumRequestedFlowRate() const;
  bool isChilledWaterMaximumRequestedFlowRateAutosized() const;
  bool setChilledWaterMaximumRequestedFlowRate(double chilledWaterMaximumRequestedFlowRate);
  void autosizeChilledWaterMaximumRequestedFlowRate();

  boost::optional<double> condenserMaximumRequestedFlowRate() const;
  bool isCondenserMaximumRequestedFlowRateAutosized() const;
  bool setCondenserMaximumRequestedFlowRate(double condenserMaximumRequestedFlowRate);
  void autosizeCondenserMaximumRequestedFlowRate();

  std::string chillerFlowMode() const;
  bool setChillerFlowMode(const std::string& chillerFlowMode);

  boost::optional<double> oilCoolerDesignFlowRate() const;
  bool setOilCoolerDesignFlowRate(double oilCoolerDesignFlowRate);
  void resetOilCoolerDesignFlowRate();

  boost::optional<double> auxiliaryCoolingDesignFlowRate() const;
  bool setAuxiliaryCoolingDesignFlowRate(double auxiliaryCoolingDesignFlowRate);
  void resetAuxiliaryCoolingDesignFlowRate();

  std::string endUseSubcategory() const;
  bool isEndUseSubcategoryDefaulted() const;
  bool setEndUseSubcategory(const std::string& endUseSubcategory);
  void resetEndUseSubcategory();

 protected:
  using ImplType = detail::ChillerElectricASHRAE205_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ChillerElectricASHRAE205(std::shared_ptr<detail::ChillerElectricASHRAE205_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
