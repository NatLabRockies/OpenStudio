/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GAS_HPP
#define EPMODEL_GAS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class Gas_Impl;
  }

  class EPMODEL_API Gas : public ModelObject
  {
   public:
    explicit Gas(const Model& model);

    virtual ~Gas() override = default;
    Gas(const Gas& other) = default;
    Gas(Gas&& other) = default;
    Gas& operator=(const Gas&) = default;
    Gas& operator=(Gas&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> validGasTypes();
    static std::vector<std::string> gasTypeValues();

    // Schema Alignment Notes:
    // - API: preserve openstudio::model Gas scalar accessor names/signatures for the Gas Layer counterpart.
    // - Field Mapping: Gas Type, Thickness, conductivity/viscosity/specific heat coefficients, and molecular weight/specific heat ratio map directly to EnergyPlus WindowMaterial:Gas fields.
    // - Field Mapping: Custom coefficient setters are provided because they are only used when Gas Type==Custom.
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

   protected:
    using ImplType = detail::Gas_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit Gas(std::shared_ptr<detail::Gas_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_GAS_HPP
