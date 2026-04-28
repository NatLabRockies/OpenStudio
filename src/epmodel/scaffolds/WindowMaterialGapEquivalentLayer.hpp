/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WINDOWMATERIALGAPEQUIVALENTLAYER_HPP
#define EPMODEL_WINDOWMATERIALGAPEQUIVALENTLAYER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class WindowMaterialGapEquivalentLayer_Impl;
  }

  class EPMODEL_API WindowMaterialGapEquivalentLayer : public ModelObject
  {
   public:
    explicit WindowMaterialGapEquivalentLayer(const Model& model);

    virtual ~WindowMaterialGapEquivalentLayer() override = default;
    WindowMaterialGapEquivalentLayer(const WindowMaterialGapEquivalentLayer& other) = default;
    WindowMaterialGapEquivalentLayer(WindowMaterialGapEquivalentLayer&& other) = default;
    WindowMaterialGapEquivalentLayer& operator=(const WindowMaterialGapEquivalentLayer&) = default;
    WindowMaterialGapEquivalentLayer& operator=(WindowMaterialGapEquivalentLayer&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> gasTypeValues();
    static std::vector<std::string> gapVentTypeValues();

    // Schema Alignment Notes:
    // - API: WindowMaterial:Gap:EquivalentLayer choice fields (Gas Type / Gap Vent Type) and optional custom-property scalars map directly to the numeric/choice IDD fields below.
    // - Field Mapping: Required Name/GasType/GapVentType fields seed default thickness/gas selections so required getters stay satisfied, while optional conductivity/viscosity/specific heat coefficients, molecular weight, and specific heat ratio mirror the custom-gas metadata.
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

   protected:
    using ImplType = detail::WindowMaterialGapEquivalentLayer_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit WindowMaterialGapEquivalentLayer(std::shared_ptr<detail::WindowMaterialGapEquivalentLayer_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
