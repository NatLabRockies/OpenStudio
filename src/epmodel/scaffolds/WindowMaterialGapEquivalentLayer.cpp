/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WindowMaterialGapEquivalentLayer.hpp"
#include "WindowMaterialGapEquivalentLayer_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/WindowMaterial_Gap_EquivalentLayer_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  WindowMaterialGapEquivalentLayer::WindowMaterialGapEquivalentLayer(const Model& model)
    : ModelObject(WindowMaterialGapEquivalentLayer::iddObjectType(), model) {
    OS_ASSERT(setThickness(0.0127));
    OS_ASSERT(setGasType("AIR"));
    OS_ASSERT(setGapVentType("Sealed"));
  }

  WindowMaterialGapEquivalentLayer::WindowMaterialGapEquivalentLayer(std::shared_ptr<detail::WindowMaterialGapEquivalentLayer_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType WindowMaterialGapEquivalentLayer::iddObjectType() {
    return IddObjectType::WindowMaterial_Gap_EquivalentLayer;
  }

  std::vector<std::string> WindowMaterialGapEquivalentLayer::gasTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WindowMaterial_Gap_EquivalentLayerFields::GasType);
  }

  std::vector<std::string> WindowMaterialGapEquivalentLayer::gapVentTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WindowMaterial_Gap_EquivalentLayerFields::GapVentType);
  }

  double WindowMaterialGapEquivalentLayer::thickness() const {
    return getImpl<detail::WindowMaterialGapEquivalentLayer_Impl>()->thickness();
  }

  bool WindowMaterialGapEquivalentLayer::setThickness(double thickness) {
    return getImpl<detail::WindowMaterialGapEquivalentLayer_Impl>()->setThickness(thickness);
  }

  std::string WindowMaterialGapEquivalentLayer::gasType() const {
    return getImpl<detail::WindowMaterialGapEquivalentLayer_Impl>()->gasType();
  }

  bool WindowMaterialGapEquivalentLayer::setGasType(const std::string& gasType) {
    return getImpl<detail::WindowMaterialGapEquivalentLayer_Impl>()->setGasType(gasType);
  }

  std::string WindowMaterialGapEquivalentLayer::gapVentType() const {
    return getImpl<detail::WindowMaterialGapEquivalentLayer_Impl>()->gapVentType();
  }

  bool WindowMaterialGapEquivalentLayer::setGapVentType(const std::string& gapVentType) {
    return getImpl<detail::WindowMaterialGapEquivalentLayer_Impl>()->setGapVentType(gapVentType);
  }

  boost::optional<double> WindowMaterialGapEquivalentLayer::conductivityCoefficientA() const {
    return getImpl<detail::WindowMaterialGapEquivalentLayer_Impl>()->conductivityCoefficientA();
  }

  bool WindowMaterialGapEquivalentLayer::setConductivityCoefficientA(double conductivityCoefficientA) {
    return getImpl<detail::WindowMaterialGapEquivalentLayer_Impl>()->setConductivityCoefficientA(conductivityCoefficientA);
  }

  boost::optional<double> WindowMaterialGapEquivalentLayer::conductivityCoefficientB() const {
    return getImpl<detail::WindowMaterialGapEquivalentLayer_Impl>()->conductivityCoefficientB();
  }

  bool WindowMaterialGapEquivalentLayer::setConductivityCoefficientB(double conductivityCoefficientB) {
    return getImpl<detail::WindowMaterialGapEquivalentLayer_Impl>()->setConductivityCoefficientB(conductivityCoefficientB);
  }

  boost::optional<double> WindowMaterialGapEquivalentLayer::conductivityCoefficientC() const {
    return getImpl<detail::WindowMaterialGapEquivalentLayer_Impl>()->conductivityCoefficientC();
  }

  bool WindowMaterialGapEquivalentLayer::setConductivityCoefficientC(double conductivityCoefficientC) {
    return getImpl<detail::WindowMaterialGapEquivalentLayer_Impl>()->setConductivityCoefficientC(conductivityCoefficientC);
  }

  boost::optional<double> WindowMaterialGapEquivalentLayer::viscosityCoefficientA() const {
    return getImpl<detail::WindowMaterialGapEquivalentLayer_Impl>()->viscosityCoefficientA();
  }

  bool WindowMaterialGapEquivalentLayer::setViscosityCoefficientA(double viscosityCoefficientA) {
    return getImpl<detail::WindowMaterialGapEquivalentLayer_Impl>()->setViscosityCoefficientA(viscosityCoefficientA);
  }

  boost::optional<double> WindowMaterialGapEquivalentLayer::viscosityCoefficientB() const {
    return getImpl<detail::WindowMaterialGapEquivalentLayer_Impl>()->viscosityCoefficientB();
  }

  bool WindowMaterialGapEquivalentLayer::setViscosityCoefficientB(double viscosityCoefficientB) {
    return getImpl<detail::WindowMaterialGapEquivalentLayer_Impl>()->setViscosityCoefficientB(viscosityCoefficientB);
  }

  boost::optional<double> WindowMaterialGapEquivalentLayer::viscosityCoefficientC() const {
    return getImpl<detail::WindowMaterialGapEquivalentLayer_Impl>()->viscosityCoefficientC();
  }

  bool WindowMaterialGapEquivalentLayer::setViscosityCoefficientC(double viscosityCoefficientC) {
    return getImpl<detail::WindowMaterialGapEquivalentLayer_Impl>()->setViscosityCoefficientC(viscosityCoefficientC);
  }

  boost::optional<double> WindowMaterialGapEquivalentLayer::specificHeatCoefficientA() const {
    return getImpl<detail::WindowMaterialGapEquivalentLayer_Impl>()->specificHeatCoefficientA();
  }

  bool WindowMaterialGapEquivalentLayer::setSpecificHeatCoefficientA(double specificHeatCoefficientA) {
    return getImpl<detail::WindowMaterialGapEquivalentLayer_Impl>()->setSpecificHeatCoefficientA(specificHeatCoefficientA);
  }

  boost::optional<double> WindowMaterialGapEquivalentLayer::specificHeatCoefficientB() const {
    return getImpl<detail::WindowMaterialGapEquivalentLayer_Impl>()->specificHeatCoefficientB();
  }

  bool WindowMaterialGapEquivalentLayer::setSpecificHeatCoefficientB(double specificHeatCoefficientB) {
    return getImpl<detail::WindowMaterialGapEquivalentLayer_Impl>()->setSpecificHeatCoefficientB(specificHeatCoefficientB);
  }

  boost::optional<double> WindowMaterialGapEquivalentLayer::specificHeatCoefficientC() const {
    return getImpl<detail::WindowMaterialGapEquivalentLayer_Impl>()->specificHeatCoefficientC();
  }

  bool WindowMaterialGapEquivalentLayer::setSpecificHeatCoefficientC(double specificHeatCoefficientC) {
    return getImpl<detail::WindowMaterialGapEquivalentLayer_Impl>()->setSpecificHeatCoefficientC(specificHeatCoefficientC);
  }

  boost::optional<double> WindowMaterialGapEquivalentLayer::molecularWeight() const {
    return getImpl<detail::WindowMaterialGapEquivalentLayer_Impl>()->molecularWeight();
  }

  bool WindowMaterialGapEquivalentLayer::setMolecularWeight(double molecularWeight) {
    return getImpl<detail::WindowMaterialGapEquivalentLayer_Impl>()->setMolecularWeight(molecularWeight);
  }

  boost::optional<double> WindowMaterialGapEquivalentLayer::specificHeatRatio() const {
    return getImpl<detail::WindowMaterialGapEquivalentLayer_Impl>()->specificHeatRatio();
  }

  bool WindowMaterialGapEquivalentLayer::setSpecificHeatRatio(double specificHeatRatio) {
    return getImpl<detail::WindowMaterialGapEquivalentLayer_Impl>()->setSpecificHeatRatio(specificHeatRatio);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double WindowMaterialGapEquivalentLayer_Impl::thickness() const {
      const auto value = getDouble(openstudio::WindowMaterial_Gap_EquivalentLayerFields::Thickness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialGapEquivalentLayer_Impl::setThickness(double thickness) {
      const bool result = setDouble(openstudio::WindowMaterial_Gap_EquivalentLayerFields::Thickness, thickness);
      OS_ASSERT(result);
      return result;
    }

    std::string WindowMaterialGapEquivalentLayer_Impl::gasType() const {
      const auto value = getString(openstudio::WindowMaterial_Gap_EquivalentLayerFields::GasType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialGapEquivalentLayer_Impl::setGasType(const std::string& gasType) {
      return setString(openstudio::WindowMaterial_Gap_EquivalentLayerFields::GasType, gasType);
    }

    std::string WindowMaterialGapEquivalentLayer_Impl::gapVentType() const {
      const auto value = getString(openstudio::WindowMaterial_Gap_EquivalentLayerFields::GapVentType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialGapEquivalentLayer_Impl::setGapVentType(const std::string& gapVentType) {
      return setString(openstudio::WindowMaterial_Gap_EquivalentLayerFields::GapVentType, gapVentType);
    }

    boost::optional<double> WindowMaterialGapEquivalentLayer_Impl::conductivityCoefficientA() const {
      return getDouble(openstudio::WindowMaterial_Gap_EquivalentLayerFields::ConductivityCoefficientA, true);
    }

    bool WindowMaterialGapEquivalentLayer_Impl::setConductivityCoefficientA(double conductivityCoefficientA) {
      return setDouble(openstudio::WindowMaterial_Gap_EquivalentLayerFields::ConductivityCoefficientA, conductivityCoefficientA);
    }

    boost::optional<double> WindowMaterialGapEquivalentLayer_Impl::conductivityCoefficientB() const {
      return getDouble(openstudio::WindowMaterial_Gap_EquivalentLayerFields::ConductivityCoefficientB, true);
    }

    bool WindowMaterialGapEquivalentLayer_Impl::setConductivityCoefficientB(double conductivityCoefficientB) {
      return setDouble(openstudio::WindowMaterial_Gap_EquivalentLayerFields::ConductivityCoefficientB, conductivityCoefficientB);
    }

    boost::optional<double> WindowMaterialGapEquivalentLayer_Impl::conductivityCoefficientC() const {
      return getDouble(openstudio::WindowMaterial_Gap_EquivalentLayerFields::ConductivityCoefficientC, true);
    }

    bool WindowMaterialGapEquivalentLayer_Impl::setConductivityCoefficientC(double conductivityCoefficientC) {
      return setDouble(openstudio::WindowMaterial_Gap_EquivalentLayerFields::ConductivityCoefficientC, conductivityCoefficientC);
    }

    boost::optional<double> WindowMaterialGapEquivalentLayer_Impl::viscosityCoefficientA() const {
      return getDouble(openstudio::WindowMaterial_Gap_EquivalentLayerFields::ViscosityCoefficientA, true);
    }

    bool WindowMaterialGapEquivalentLayer_Impl::setViscosityCoefficientA(double viscosityCoefficientA) {
      return setDouble(openstudio::WindowMaterial_Gap_EquivalentLayerFields::ViscosityCoefficientA, viscosityCoefficientA);
    }

    boost::optional<double> WindowMaterialGapEquivalentLayer_Impl::viscosityCoefficientB() const {
      return getDouble(openstudio::WindowMaterial_Gap_EquivalentLayerFields::ViscosityCoefficientB, true);
    }

    bool WindowMaterialGapEquivalentLayer_Impl::setViscosityCoefficientB(double viscosityCoefficientB) {
      return setDouble(openstudio::WindowMaterial_Gap_EquivalentLayerFields::ViscosityCoefficientB, viscosityCoefficientB);
    }

    boost::optional<double> WindowMaterialGapEquivalentLayer_Impl::viscosityCoefficientC() const {
      return getDouble(openstudio::WindowMaterial_Gap_EquivalentLayerFields::ViscosityCoefficientC, true);
    }

    bool WindowMaterialGapEquivalentLayer_Impl::setViscosityCoefficientC(double viscosityCoefficientC) {
      return setDouble(openstudio::WindowMaterial_Gap_EquivalentLayerFields::ViscosityCoefficientC, viscosityCoefficientC);
    }

    boost::optional<double> WindowMaterialGapEquivalentLayer_Impl::specificHeatCoefficientA() const {
      return getDouble(openstudio::WindowMaterial_Gap_EquivalentLayerFields::SpecificHeatCoefficientA, true);
    }

    bool WindowMaterialGapEquivalentLayer_Impl::setSpecificHeatCoefficientA(double specificHeatCoefficientA) {
      return setDouble(openstudio::WindowMaterial_Gap_EquivalentLayerFields::SpecificHeatCoefficientA, specificHeatCoefficientA);
    }

    boost::optional<double> WindowMaterialGapEquivalentLayer_Impl::specificHeatCoefficientB() const {
      return getDouble(openstudio::WindowMaterial_Gap_EquivalentLayerFields::SpecificHeatCoefficientB, true);
    }

    bool WindowMaterialGapEquivalentLayer_Impl::setSpecificHeatCoefficientB(double specificHeatCoefficientB) {
      return setDouble(openstudio::WindowMaterial_Gap_EquivalentLayerFields::SpecificHeatCoefficientB, specificHeatCoefficientB);
    }

    boost::optional<double> WindowMaterialGapEquivalentLayer_Impl::specificHeatCoefficientC() const {
      return getDouble(openstudio::WindowMaterial_Gap_EquivalentLayerFields::SpecificHeatCoefficientC, true);
    }

    bool WindowMaterialGapEquivalentLayer_Impl::setSpecificHeatCoefficientC(double specificHeatCoefficientC) {
      return setDouble(openstudio::WindowMaterial_Gap_EquivalentLayerFields::SpecificHeatCoefficientC, specificHeatCoefficientC);
    }

    boost::optional<double> WindowMaterialGapEquivalentLayer_Impl::molecularWeight() const {
      return getDouble(openstudio::WindowMaterial_Gap_EquivalentLayerFields::MolecularWeight, true);
    }

    bool WindowMaterialGapEquivalentLayer_Impl::setMolecularWeight(double molecularWeight) {
      return setDouble(openstudio::WindowMaterial_Gap_EquivalentLayerFields::MolecularWeight, molecularWeight);
    }

    boost::optional<double> WindowMaterialGapEquivalentLayer_Impl::specificHeatRatio() const {
      return getDouble(openstudio::WindowMaterial_Gap_EquivalentLayerFields::SpecificHeatRatio, true);
    }

    bool WindowMaterialGapEquivalentLayer_Impl::setSpecificHeatRatio(double specificHeatRatio) {
      return setDouble(openstudio::WindowMaterial_Gap_EquivalentLayerFields::SpecificHeatRatio, specificHeatRatio);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
