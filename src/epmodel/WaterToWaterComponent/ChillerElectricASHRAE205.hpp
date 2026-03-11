/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CHILLERELECTRICASHRAE205_HPP
#define EPMODEL_CHILLERELECTRICASHRAE205_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ChillerElectricASHRAE205_Impl;
}

class EPMODEL_API ChillerElectricASHRAE205 : public ModelObject
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
  // - API: Preserve openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
  // - Field Mapping: Preserved scalar APIs map directly to EnergyPlus Chiller:Electric:ASHRAE205 fields.
  // - Field Mapping: representationFile/ambient schedule+zone and all node-link fields are excluded from this scalar-only scaffold phase.
  // - TODO(parity): Add excluded relationship APIs and rich loop behavior in a dedicated parity pass.
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
