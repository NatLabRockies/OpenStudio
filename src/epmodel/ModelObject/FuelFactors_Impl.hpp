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
      bool setExistingFuelResourceName(const std::string& existingFuelResourceName);

      double sourceEnergyFactor() const;
      bool setSourceEnergyFactor(double sourceEnergyFactor);

      double cO2EmissionFactor() const;
      bool setCO2EmissionFactor(double cO2EmissionFactor);

      double cOEmissionFactor() const;
      bool setCOEmissionFactor(double cOEmissionFactor);

      double cH4EmissionFactor() const;
      bool setCH4EmissionFactor(double cH4EmissionFactor);

      double nOxEmissionFactor() const;
      bool setNOxEmissionFactor(double nOxEmissionFactor);

      double n2OEmissionFactor() const;
      bool setN2OEmissionFactor(double n2OEmissionFactor);

      double sO2EmissionFactor() const;
      bool setSO2EmissionFactor(double sO2EmissionFactor);

      double pMEmissionFactor() const;
      bool setPMEmissionFactor(double pMEmissionFactor);

      double pM10EmissionFactor() const;
      bool setPM10EmissionFactor(double pM10EmissionFactor);

      double pM25EmissionFactor() const;
      bool setPM25EmissionFactor(double pM25EmissionFactor);

      double nH3EmissionFactor() const;
      bool setNH3EmissionFactor(double nH3EmissionFactor);

      double nMVOCEmissionFactor() const;
      bool setNMVOCEmissionFactor(double nMVOCEmissionFactor);

      double hgEmissionFactor() const;
      bool setHgEmissionFactor(double hgEmissionFactor);

      double pbEmissionFactor() const;
      bool setPbEmissionFactor(double pbEmissionFactor);

      double waterEmissionFactor() const;
      bool setWaterEmissionFactor(double waterEmissionFactor);

      double nuclearHighLevelEmissionFactor() const;
      bool setNuclearHighLevelEmissionFactor(double nuclearHighLevelEmissionFactor);

      double nuclearLowLevelEmissionFactor() const;
      bool setNuclearLowLevelEmissionFactor(double nuclearLowLevelEmissionFactor);

      std::vector<std::string> existingFuelResourceNameValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
