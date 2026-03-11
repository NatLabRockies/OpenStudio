/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GAS_IMPL_HPP
#define EPMODEL_GAS_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API Gas_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~Gas_Impl() override = default;

      std::string gasType() const;
      bool setGasType(const std::string& gasType);

      double thickness() const;
      bool setThickness(double thickness);

      boost::optional<double> customConductivityCoefficientA() const;
      boost::optional<double> customConductivityCoefficientB() const;
      boost::optional<double> customConductivityCoefficientC() const;
      bool setCustomConductivity(double A, double B, double C);

      boost::optional<double> customViscosityCoefficientA() const;
      boost::optional<double> customViscosityCoefficientB() const;
      boost::optional<double> customViscosityCoefficientC() const;
      bool setCustomViscosity(double A, double B, double C);

      boost::optional<double> customSpecificHeatCoefficientA() const;
      boost::optional<double> customSpecificHeatCoefficientB() const;
      boost::optional<double> customSpecificHeatCoefficientC() const;
      bool setCustomSpecificHeat(double A, double B, double C);

      boost::optional<double> customMolecularWeight() const;
      bool setCustomMolecularWeight(double value);

      boost::optional<double> conductivityCoefficientA() const;
      boost::optional<double> conductivityCoefficientB() const;
      boost::optional<double> conductivityCoefficientC() const;
      bool setConductivityCoefficientA(double conductivityCoefficientA);
      bool setConductivityCoefficientB(double conductivityCoefficientB);
      bool setConductivityCoefficientC(double conductivityCoefficientC);

      boost::optional<double> viscosityCoefficientA() const;
      boost::optional<double> viscosityCoefficientB() const;
      boost::optional<double> viscosityCoefficientC() const;
      bool setViscosityCoefficientA(double viscosityCoefficientA);
      bool setViscosityCoefficientB(double viscosityCoefficientB);
      bool setViscosityCoefficientC(double viscosityCoefficientC);

      boost::optional<double> specificHeatCoefficientA() const;
      boost::optional<double> specificHeatCoefficientB() const;
      boost::optional<double> specificHeatCoefficientC() const;
      bool setSpecificHeatCoefficientA(double specificHeatCoefficientA);
      bool setSpecificHeatCoefficientB(double specificHeatCoefficientB);
      bool setSpecificHeatCoefficientC(double specificHeatCoefficientC);

      boost::optional<double> molecularWeight() const;
      bool setMolecularWeight(double molecularWeight);

      boost::optional<double> specificHeatRatio() const;
      bool setSpecificHeatRatio(double specificHeatRatio);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_GAS_IMPL_HPP
