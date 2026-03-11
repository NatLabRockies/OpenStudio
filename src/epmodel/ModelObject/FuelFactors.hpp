/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FUELFACTORS_HPP
#define EPMODEL_FUELFACTORS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class FuelFactors_Impl;
}

class EPMODEL_API FuelFactors : public ModelObject
{
 public:
  explicit FuelFactors(const Model& model);

  virtual ~FuelFactors() override = default;
  FuelFactors(const FuelFactors& other) = default;
  FuelFactors(FuelFactors&& other) = default;
  FuelFactors& operator=(const FuelFactors&) = default;
  FuelFactors& operator=(FuelFactors&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> existingFuelResourceNameValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::FuelFactors scalar accessor names/signatures for counterpart parity.
  // - Field Mapping: existingFuelResourceName and scalar emission/source factors map directly to matching E+ FuelFactors fields.
  // - Field Mapping: All schedule name fields are relationship-like object-list references and are intentionally excluded from scalar scope.
  // - ForwardTranslator evidence: ForwardTranslateFuelFactors.cpp writes these preserved scalar APIs directly to FuelFactors field enums.
  // - TODO(parity): Add excluded schedule relationship APIs later without changing these preserved scalar signatures.
  std::string existingFuelResourceName() const;
  double sourceEnergyFactor() const;
  double cO2EmissionFactor() const;
  double cOEmissionFactor() const;
  double cH4EmissionFactor() const;
  double nOxEmissionFactor() const;
  double n2OEmissionFactor() const;
  double sO2EmissionFactor() const;
  double pMEmissionFactor() const;
  double pM10EmissionFactor() const;
  double pM25EmissionFactor() const;
  double nH3EmissionFactor() const;
  double nMVOCEmissionFactor() const;
  double hgEmissionFactor() const;
  double pbEmissionFactor() const;
  double waterEmissionFactor() const;
  double nuclearHighLevelEmissionFactor() const;
  double nuclearLowLevelEmissionFactor() const;

  bool setExistingFuelResourceName(const std::string& existingFuelResourceName);
  bool setSourceEnergyFactor(double sourceEnergyFactor);
  bool setCO2EmissionFactor(double cO2EmissionFactor);
  bool setCOEmissionFactor(double cOEmissionFactor);
  bool setCH4EmissionFactor(double cH4EmissionFactor);
  bool setNOxEmissionFactor(double nOxEmissionFactor);
  bool setN2OEmissionFactor(double n2OEmissionFactor);
  bool setSO2EmissionFactor(double sO2EmissionFactor);
  bool setPMEmissionFactor(double pMEmissionFactor);
  bool setPM10EmissionFactor(double pM10EmissionFactor);
  bool setPM25EmissionFactor(double pM25EmissionFactor);
  bool setNH3EmissionFactor(double nH3EmissionFactor);
  bool setNMVOCEmissionFactor(double nMVOCEmissionFactor);
  bool setHgEmissionFactor(double hgEmissionFactor);
  bool setPbEmissionFactor(double pbEmissionFactor);
  bool setWaterEmissionFactor(double waterEmissionFactor);
  bool setNuclearHighLevelEmissionFactor(double nuclearHighLevelEmissionFactor);
  bool setNuclearLowLevelEmissionFactor(double nuclearLowLevelEmissionFactor);

 protected:
  using ImplType = detail::FuelFactors_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit FuelFactors(std::shared_ptr<detail::FuelFactors_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
