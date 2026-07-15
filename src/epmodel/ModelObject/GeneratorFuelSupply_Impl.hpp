/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORFUELSUPPLY_IMPL_HPP
#define EPMODEL_GENERATORFUELSUPPLY_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API GeneratorFuelSupply_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~GeneratorFuelSupply_Impl() override = default;

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

      std::vector<std::string> fuelTemperatureModelingModeValues() const;
      std::vector<std::string> fuelTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
