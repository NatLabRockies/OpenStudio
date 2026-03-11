/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORFUELSUPPLY_HPP
#define EPMODEL_GENERATORFUELSUPPLY_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class GeneratorFuelSupply_Impl;
}

class EPMODEL_API GeneratorFuelSupply : public ModelObject
{
 public:
  explicit GeneratorFuelSupply(const Model& model);

  virtual ~GeneratorFuelSupply() override = default;
  GeneratorFuelSupply(const GeneratorFuelSupply& other) = default;
  GeneratorFuelSupply(GeneratorFuelSupply&& other) = default;
  GeneratorFuelSupply& operator=(const GeneratorFuelSupply&) = default;
  GeneratorFuelSupply& operator=(GeneratorFuelSupply&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> fuelTemperatureModelingModeValues();
  static std::vector<std::string> fuelTypeValues();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model scalar accessor names/signatures for counterpart parity.
  // - Field Mapping: fuelTemperatureModelingMode, compressorHeatLossFactor, fuelType,
  //   liquidGenericFuelLowerHeatingValue, liquidGenericFuelHigherHeatingValue,
  //   liquidGenericFuelMolecularWeight, liquidGenericFuelCO2EmissionFactor map directly
  //   to Generator:FuelSupply scalar fields.
  // - Field Mapping: numberofConstituentsinGaseousConstituentFuelSupply follows existing
  //   model behavior and reflects extensible group count.
  // - ForwardTranslator evidence: ForwardTranslateGeneratorFuelSupply writes these scalar
  //   fields directly and handles node/schedule/curve/extensible constituent relationships separately.
  // - TODO(parity): Add excluded relationship/extensible APIs incrementally.
  std::string fuelTemperatureModelingMode() const;
  bool setFuelTemperatureModelingMode(const std::string& fuelTemperatureModelingMode);
  void resetFuelTemperatureModelingMode();

  double compressorHeatLossFactor() const;
  bool setCompressorHeatLossFactor(double compressorHeatLossFactor);
  void resetCompressorHeatLossFactor();

  std::string fuelType() const;
  bool setFuelType(const std::string& fuelType);
  void resetFuelType();

  boost::optional<double> liquidGenericFuelLowerHeatingValue() const;
  bool setLiquidGenericFuelLowerHeatingValue(double liquidGenericFuelLowerHeatingValue);
  void resetLiquidGenericFuelLowerHeatingValue();

  boost::optional<double> liquidGenericFuelHigherHeatingValue() const;
  bool setLiquidGenericFuelHigherHeatingValue(double liquidGenericFuelHigherHeatingValue);
  void resetLiquidGenericFuelHigherHeatingValue();

  boost::optional<double> liquidGenericFuelMolecularWeight() const;
  bool setLiquidGenericFuelMolecularWeight(double liquidGenericFuelMolecularWeight);
  void resetLiquidGenericFuelMolecularWeight();

  boost::optional<double> liquidGenericFuelCO2EmissionFactor() const;
  bool setLiquidGenericFuelCO2EmissionFactor(double liquidGenericFuelCO2EmissionFactor);
  void resetLiquidGenericFuelCO2EmissionFactor();

  boost::optional<unsigned int> numberofConstituentsinGaseousConstituentFuelSupply() const;

 protected:
  using ImplType = detail::GeneratorFuelSupply_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit GeneratorFuelSupply(std::shared_ptr<detail::GeneratorFuelSupply_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
