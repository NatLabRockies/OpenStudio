/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEPLANTBOILER_HPP
#define EPMODEL_HVACTEMPLATEPLANTBOILER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class HVACTemplatePlantBoiler_Impl;
}

class EPMODEL_API HVACTemplatePlantBoiler : public ModelObject
{
 public:
  explicit HVACTemplatePlantBoiler(const Model& model);

  virtual ~HVACTemplatePlantBoiler() override = default;
  HVACTemplatePlantBoiler(const HVACTemplatePlantBoiler& other) = default;
  HVACTemplatePlantBoiler(HVACTemplatePlantBoiler&& other) = default;
  HVACTemplatePlantBoiler& operator=(const HVACTemplatePlantBoiler&) = default;
  HVACTemplatePlantBoiler& operator=(HVACTemplatePlantBoiler&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> boilerTypeValues();
  static std::vector<std::string> fuelTypeValues();
  static std::vector<std::string> templatePlantLoopTypeValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to HVACTemplate:Plant:Boiler non-name scalar fields.
  // - TODO(parity): Keep object-reference linkage behavior out of this scalar-only scaffold pass.
  std::string boilerType() const;
  boost::optional<double> capacity() const;
  double efficiency() const;
  boost::optional<std::string> fuelType() const;
  boost::optional<std::string> priority() const;
  double sizingFactor() const;
  double minimumPartLoadRatio() const;
  double maximumPartLoadRatio() const;
  double optimumPartLoadRatio() const;
  double waterOutletUpperTemperatureLimit() const;
  boost::optional<std::string> templatePlantLoopType() const;

  bool isCapacityDefaulted() const;
  bool isCapacityAutosized() const;
  bool isEfficiencyDefaulted() const;
  bool isSizingFactorDefaulted() const;
  bool isMinimumPartLoadRatioDefaulted() const;
  bool isMaximumPartLoadRatioDefaulted() const;
  bool isOptimumPartLoadRatioDefaulted() const;
  bool isWaterOutletUpperTemperatureLimitDefaulted() const;

  bool setBoilerType(const std::string& boilerType);
  bool setCapacity(double capacity);
  bool setEfficiency(double efficiency);
  bool setFuelType(const std::string& fuelType);
  bool setPriority(const std::string& priority);
  bool setSizingFactor(double sizingFactor);
  bool setMinimumPartLoadRatio(double minimumPartLoadRatio);
  bool setMaximumPartLoadRatio(double maximumPartLoadRatio);
  bool setOptimumPartLoadRatio(double optimumPartLoadRatio);
  bool setWaterOutletUpperTemperatureLimit(double waterOutletUpperTemperatureLimit);
  bool setTemplatePlantLoopType(const std::string& templatePlantLoopType);

  void resetCapacity();
  void autosizeCapacity();
  void resetEfficiency();
  void resetFuelType();
  void resetPriority();
  void resetSizingFactor();
  void resetMinimumPartLoadRatio();
  void resetMaximumPartLoadRatio();
  void resetOptimumPartLoadRatio();
  void resetWaterOutletUpperTemperatureLimit();
  void resetTemplatePlantLoopType();

 protected:
  using ImplType = detail::HVACTemplatePlantBoiler_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit HVACTemplatePlantBoiler(std::shared_ptr<detail::HVACTemplatePlantBoiler_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
