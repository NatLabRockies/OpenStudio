/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FUELFACTORS_IMPL_HPP
#define EPMODEL_FUELFACTORS_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API FuelFactors_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~FuelFactors_Impl() override = default;

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

  std::vector<std::string> existingFuelResourceNameValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
