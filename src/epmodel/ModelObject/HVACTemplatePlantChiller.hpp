/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEPLANTCHILLER_HPP
#define EPMODEL_HVACTEMPLATEPLANTCHILLER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class HVACTemplatePlantChiller_Impl;
}

class EPMODEL_API HVACTemplatePlantChiller : public ModelObject
{
 public:
  explicit HVACTemplatePlantChiller(const Model& model);

  virtual ~HVACTemplatePlantChiller() override = default;
  HVACTemplatePlantChiller(const HVACTemplatePlantChiller& other) = default;
  HVACTemplatePlantChiller(HVACTemplatePlantChiller&& other) = default;
  HVACTemplatePlantChiller& operator=(const HVACTemplatePlantChiller&) = default;
  HVACTemplatePlantChiller& operator=(HVACTemplatePlantChiller&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> chillerTypeValues();
  static std::vector<std::string> condenserTypeValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to HVACTemplate:Plant:Chiller non-name scalar fields.
  // - TODO(parity): Keep object-reference and loop-relationship behavior in dedicated parity passes.
  std::string chillerType() const;
  boost::optional<double> capacity() const;
  double nominalCOP() const;
  std::string condenserType() const;
  boost::optional<std::string> priority() const;
  double sizingFactor() const;
  double minimumPartLoadRatio() const;
  double maximumPartLoadRatio() const;
  double optimumPartLoadRatio() const;
  double minimumUnloadingRatio() const;
  double leavingChilledWaterLowerTemperatureLimit() const;

  bool isCapacityDefaulted() const;
  bool isCapacityAutosized() const;
  bool isCondenserTypeDefaulted() const;
  bool isSizingFactorDefaulted() const;
  bool isMinimumPartLoadRatioDefaulted() const;
  bool isMaximumPartLoadRatioDefaulted() const;
  bool isOptimumPartLoadRatioDefaulted() const;
  bool isMinimumUnloadingRatioDefaulted() const;
  bool isLeavingChilledWaterLowerTemperatureLimitDefaulted() const;

  bool setChillerType(const std::string& chillerType);
  bool setCapacity(double capacity);
  bool setNominalCOP(double nominalCOP);
  bool setCondenserType(const std::string& condenserType);
  bool setPriority(const std::string& priority);
  bool setSizingFactor(double sizingFactor);
  bool setMinimumPartLoadRatio(double minimumPartLoadRatio);
  bool setMaximumPartLoadRatio(double maximumPartLoadRatio);
  bool setOptimumPartLoadRatio(double optimumPartLoadRatio);
  bool setMinimumUnloadingRatio(double minimumUnloadingRatio);
  bool setLeavingChilledWaterLowerTemperatureLimit(double leavingChilledWaterLowerTemperatureLimit);

  void resetCapacity();
  void autosizeCapacity();
  void resetCondenserType();
  void resetPriority();
  void resetSizingFactor();
  void resetMinimumPartLoadRatio();
  void resetMaximumPartLoadRatio();
  void resetOptimumPartLoadRatio();
  void resetMinimumUnloadingRatio();
  void resetLeavingChilledWaterLowerTemperatureLimit();

 protected:
  using ImplType = detail::HVACTemplatePlantChiller_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit HVACTemplatePlantChiller(std::shared_ptr<detail::HVACTemplatePlantChiller_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
