/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WINDOWMATERIALGAPEQUIVALENTLAYER_IMPL_HPP
#define EPMODEL_WINDOWMATERIALGAPEQUIVALENTLAYER_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API WindowMaterialGapEquivalentLayer_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~WindowMaterialGapEquivalentLayer_Impl() override = default;

      double thickness() const;
      bool setThickness(double thickness);

      std::string gasType() const;
      bool setGasType(const std::string& gasType);

      std::string gapVentType() const;
      bool setGapVentType(const std::string& gapVentType);

      boost::optional<double> conductivityCoefficientA() const;
      bool setConductivityCoefficientA(double conductivityCoefficientA);

      boost::optional<double> conductivityCoefficientB() const;
      bool setConductivityCoefficientB(double conductivityCoefficientB);

      boost::optional<double> conductivityCoefficientC() const;
      bool setConductivityCoefficientC(double conductivityCoefficientC);

      boost::optional<double> viscosityCoefficientA() const;
      bool setViscosityCoefficientA(double viscosityCoefficientA);

      boost::optional<double> viscosityCoefficientB() const;
      bool setViscosityCoefficientB(double viscosityCoefficientB);

      boost::optional<double> viscosityCoefficientC() const;
      bool setViscosityCoefficientC(double viscosityCoefficientC);

      boost::optional<double> specificHeatCoefficientA() const;
      bool setSpecificHeatCoefficientA(double specificHeatCoefficientA);

      boost::optional<double> specificHeatCoefficientB() const;
      bool setSpecificHeatCoefficientB(double specificHeatCoefficientB);

      boost::optional<double> specificHeatCoefficientC() const;
      bool setSpecificHeatCoefficientC(double specificHeatCoefficientC);

      boost::optional<double> molecularWeight() const;
      bool setMolecularWeight(double molecularWeight);

      boost::optional<double> specificHeatRatio() const;
      bool setSpecificHeatRatio(double specificHeatRatio);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
