/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Gas.hpp"
#include "Gas_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/WindowMaterial_Gas_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  Gas::Gas(const Model& model) : Material(Gas::iddObjectType(), model) {
    OS_ASSERT(setGasType("Air"));
    OS_ASSERT(setThickness(0.003));
  }

  Gas::Gas(std::shared_ptr<detail::Gas_Impl> impl) : Material(std::move(impl)) {}

  IddObjectType Gas::iddObjectType() {
    return IddObjectType::WindowMaterial_Gas;
  }

  std::vector<std::string> Gas::validGasTypes() {
    static const StringVector result =
      getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WindowMaterial_GasFields::GasType);
    OS_ASSERT(!result.empty());
    return result;
  }

  std::vector<std::string> Gas::gasTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WindowMaterial_GasFields::GasType);
  }

  std::string Gas::gasType() const {
    return getImpl<detail::Gas_Impl>()->gasType();
  }

  bool Gas::setGasType(const std::string& gasType) {
    return getImpl<detail::Gas_Impl>()->setGasType(gasType);
  }

  double Gas::thickness() const {
    return getImpl<detail::Gas_Impl>()->thickness();
  }

  bool Gas::setThickness(double thickness) {
    return getImpl<detail::Gas_Impl>()->setThickness(thickness);
  }

  boost::optional<double> Gas::customConductivityCoefficientA() const {
    return getImpl<detail::Gas_Impl>()->customConductivityCoefficientA();
  }

  boost::optional<double> Gas::customConductivityCoefficientB() const {
    return getImpl<detail::Gas_Impl>()->customConductivityCoefficientB();
  }

  boost::optional<double> Gas::customConductivityCoefficientC() const {
    return getImpl<detail::Gas_Impl>()->customConductivityCoefficientC();
  }

  bool Gas::setCustomConductivity(double A, double B, double C) {
    return getImpl<detail::Gas_Impl>()->setCustomConductivity(A, B, C);
  }

  boost::optional<double> Gas::customViscosityCoefficientA() const {
    return getImpl<detail::Gas_Impl>()->customViscosityCoefficientA();
  }

  boost::optional<double> Gas::customViscosityCoefficientB() const {
    return getImpl<detail::Gas_Impl>()->customViscosityCoefficientB();
  }

  boost::optional<double> Gas::customViscosityCoefficientC() const {
    return getImpl<detail::Gas_Impl>()->customViscosityCoefficientC();
  }

  bool Gas::setCustomViscosity(double A, double B, double C) {
    return getImpl<detail::Gas_Impl>()->setCustomViscosity(A, B, C);
  }

  boost::optional<double> Gas::customSpecificHeatCoefficientA() const {
    return getImpl<detail::Gas_Impl>()->customSpecificHeatCoefficientA();
  }

  boost::optional<double> Gas::customSpecificHeatCoefficientB() const {
    return getImpl<detail::Gas_Impl>()->customSpecificHeatCoefficientB();
  }

  boost::optional<double> Gas::customSpecificHeatCoefficientC() const {
    return getImpl<detail::Gas_Impl>()->customSpecificHeatCoefficientC();
  }

  bool Gas::setCustomSpecificHeat(double A, double B, double C) {
    return getImpl<detail::Gas_Impl>()->setCustomSpecificHeat(A, B, C);
  }

  boost::optional<double> Gas::customMolecularWeight() const {
    return getImpl<detail::Gas_Impl>()->customMolecularWeight();
  }

  bool Gas::setCustomMolecularWeight(double value) {
    return getImpl<detail::Gas_Impl>()->setCustomMolecularWeight(value);
  }

  boost::optional<double> Gas::conductivityCoefficientA() const {
    return getImpl<detail::Gas_Impl>()->conductivityCoefficientA();
  }

  bool Gas::setConductivityCoefficientA(double conductivityCoefficientA) {
    return getImpl<detail::Gas_Impl>()->setConductivityCoefficientA(conductivityCoefficientA);
  }

  boost::optional<double> Gas::conductivityCoefficientB() const {
    return getImpl<detail::Gas_Impl>()->conductivityCoefficientB();
  }

  bool Gas::setConductivityCoefficientB(double conductivityCoefficientB) {
    return getImpl<detail::Gas_Impl>()->setConductivityCoefficientB(conductivityCoefficientB);
  }

  boost::optional<double> Gas::conductivityCoefficientC() const {
    return getImpl<detail::Gas_Impl>()->conductivityCoefficientC();
  }

  bool Gas::setConductivityCoefficientC(double conductivityCoefficientC) {
    return getImpl<detail::Gas_Impl>()->setConductivityCoefficientC(conductivityCoefficientC);
  }

  boost::optional<double> Gas::viscosityCoefficientA() const {
    return getImpl<detail::Gas_Impl>()->viscosityCoefficientA();
  }

  bool Gas::setViscosityCoefficientA(double viscosityCoefficientA) {
    return getImpl<detail::Gas_Impl>()->setViscosityCoefficientA(viscosityCoefficientA);
  }

  boost::optional<double> Gas::viscosityCoefficientB() const {
    return getImpl<detail::Gas_Impl>()->viscosityCoefficientB();
  }

  bool Gas::setViscosityCoefficientB(double viscosityCoefficientB) {
    return getImpl<detail::Gas_Impl>()->setViscosityCoefficientB(viscosityCoefficientB);
  }

  boost::optional<double> Gas::viscosityCoefficientC() const {
    return getImpl<detail::Gas_Impl>()->viscosityCoefficientC();
  }

  bool Gas::setViscosityCoefficientC(double viscosityCoefficientC) {
    return getImpl<detail::Gas_Impl>()->setViscosityCoefficientC(viscosityCoefficientC);
  }

  boost::optional<double> Gas::specificHeatCoefficientA() const {
    return getImpl<detail::Gas_Impl>()->specificHeatCoefficientA();
  }

  bool Gas::setSpecificHeatCoefficientA(double specificHeatCoefficientA) {
    return getImpl<detail::Gas_Impl>()->setSpecificHeatCoefficientA(specificHeatCoefficientA);
  }

  boost::optional<double> Gas::specificHeatCoefficientB() const {
    return getImpl<detail::Gas_Impl>()->specificHeatCoefficientB();
  }

  bool Gas::setSpecificHeatCoefficientB(double specificHeatCoefficientB) {
    return getImpl<detail::Gas_Impl>()->setSpecificHeatCoefficientB(specificHeatCoefficientB);
  }

  boost::optional<double> Gas::specificHeatCoefficientC() const {
    return getImpl<detail::Gas_Impl>()->specificHeatCoefficientC();
  }

  bool Gas::setSpecificHeatCoefficientC(double specificHeatCoefficientC) {
    return getImpl<detail::Gas_Impl>()->setSpecificHeatCoefficientC(specificHeatCoefficientC);
  }

  boost::optional<double> Gas::molecularWeight() const {
    return getImpl<detail::Gas_Impl>()->molecularWeight();
  }

  bool Gas::setMolecularWeight(double molecularWeight) {
    return getImpl<detail::Gas_Impl>()->setMolecularWeight(molecularWeight);
  }

  boost::optional<double> Gas::specificHeatRatio() const {
    return getImpl<detail::Gas_Impl>()->specificHeatRatio();
  }

  bool Gas::setSpecificHeatRatio(double specificHeatRatio) {
    return getImpl<detail::Gas_Impl>()->setSpecificHeatRatio(specificHeatRatio);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string Gas_Impl::gasType() const {
      const auto value = getString(openstudio::WindowMaterial_GasFields::GasType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool Gas_Impl::setGasType(const std::string& gasType) {
      const bool result = setString(openstudio::WindowMaterial_GasFields::GasType, gasType);
      OS_ASSERT(result);
      return result;
    }

    double Gas_Impl::thickness() const {
      const auto value = getDouble(openstudio::WindowMaterial_GasFields::Thickness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool Gas_Impl::setThickness(double thickness) {
      const bool result = setDouble(openstudio::WindowMaterial_GasFields::Thickness, thickness);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> Gas_Impl::customConductivityCoefficientA() const {
      return getDouble(openstudio::WindowMaterial_GasFields::ConductivityCoefficientA, true);
    }

    boost::optional<double> Gas_Impl::customConductivityCoefficientB() const {
      return getDouble(openstudio::WindowMaterial_GasFields::ConductivityCoefficientB, true);
    }

    boost::optional<double> Gas_Impl::customConductivityCoefficientC() const {
      return getDouble(openstudio::WindowMaterial_GasFields::ConductivityCoefficientC, true);
    }

    bool Gas_Impl::setCustomConductivity(double A, double B, double C) {
      boost::optional<double> oldAValue = customConductivityCoefficientA();
      bool result = setDouble(openstudio::WindowMaterial_GasFields::ConductivityCoefficientA, A);
      if (!result) {
        return false;
      }

      result = setDouble(openstudio::WindowMaterial_GasFields::ConductivityCoefficientB, B);
      if (!result) {
        if (oldAValue) {
          setDouble(openstudio::WindowMaterial_GasFields::ConductivityCoefficientA, *oldAValue);
        } else {
          setString(openstudio::WindowMaterial_GasFields::ConductivityCoefficientA, "");
        }
      }

      setDouble(openstudio::WindowMaterial_GasFields::ConductivityCoefficientC, C);
      return result;
    }

    boost::optional<double> Gas_Impl::customViscosityCoefficientA() const {
      return getDouble(openstudio::WindowMaterial_GasFields::ViscosityCoefficientA, true);
    }

    boost::optional<double> Gas_Impl::customViscosityCoefficientB() const {
      return getDouble(openstudio::WindowMaterial_GasFields::ViscosityCoefficientB, true);
    }

    boost::optional<double> Gas_Impl::customViscosityCoefficientC() const {
      return getDouble(openstudio::WindowMaterial_GasFields::ViscosityCoefficientC, true);
    }

    bool Gas_Impl::setCustomViscosity(double A, double B, double C) {
      boost::optional<double> oldAValue = customViscosityCoefficientA();
      bool result = setDouble(openstudio::WindowMaterial_GasFields::ViscosityCoefficientA, A);
      if (!result) {
        return false;
      }

      result = setDouble(openstudio::WindowMaterial_GasFields::ViscosityCoefficientB, B);
      if (!result) {
        if (oldAValue) {
          setDouble(openstudio::WindowMaterial_GasFields::ViscosityCoefficientA, *oldAValue);
        } else {
          setString(openstudio::WindowMaterial_GasFields::ViscosityCoefficientA, "");
        }
      }

      setDouble(openstudio::WindowMaterial_GasFields::ViscosityCoefficientC, C);
      return result;
    }

    boost::optional<double> Gas_Impl::customSpecificHeatCoefficientA() const {
      return getDouble(openstudio::WindowMaterial_GasFields::SpecificHeatCoefficientA, true);
    }

    boost::optional<double> Gas_Impl::customSpecificHeatCoefficientB() const {
      return getDouble(openstudio::WindowMaterial_GasFields::SpecificHeatCoefficientB, true);
    }

    boost::optional<double> Gas_Impl::customSpecificHeatCoefficientC() const {
      return getDouble(openstudio::WindowMaterial_GasFields::SpecificHeatCoefficientC, true);
    }

    bool Gas_Impl::setCustomSpecificHeat(double A, double B, double C) {
      boost::optional<double> oldAValue = customSpecificHeatCoefficientA();
      bool result = setDouble(openstudio::WindowMaterial_GasFields::SpecificHeatCoefficientA, A);
      if (!result) {
        return false;
      }

      result = setDouble(openstudio::WindowMaterial_GasFields::SpecificHeatCoefficientB, B);
      if (!result) {
        if (oldAValue) {
          setDouble(openstudio::WindowMaterial_GasFields::SpecificHeatCoefficientA, *oldAValue);
        } else {
          setString(openstudio::WindowMaterial_GasFields::SpecificHeatCoefficientA, "");
        }
      }

      setDouble(openstudio::WindowMaterial_GasFields::SpecificHeatCoefficientC, C);
      return result;
    }

    boost::optional<double> Gas_Impl::customMolecularWeight() const {
      return getDouble(openstudio::WindowMaterial_GasFields::MolecularWeight, true);
    }

    bool Gas_Impl::setCustomMolecularWeight(double value) {
      return setDouble(openstudio::WindowMaterial_GasFields::MolecularWeight, value);
    }

    boost::optional<double> Gas_Impl::conductivityCoefficientA() const {
      return getDouble(openstudio::WindowMaterial_GasFields::ConductivityCoefficientA, true);
    }

    bool Gas_Impl::setConductivityCoefficientA(double conductivityCoefficientA) {
      return setDouble(openstudio::WindowMaterial_GasFields::ConductivityCoefficientA, conductivityCoefficientA);
    }

    boost::optional<double> Gas_Impl::conductivityCoefficientB() const {
      return getDouble(openstudio::WindowMaterial_GasFields::ConductivityCoefficientB, true);
    }

    bool Gas_Impl::setConductivityCoefficientB(double conductivityCoefficientB) {
      return setDouble(openstudio::WindowMaterial_GasFields::ConductivityCoefficientB, conductivityCoefficientB);
    }

    boost::optional<double> Gas_Impl::conductivityCoefficientC() const {
      return getDouble(openstudio::WindowMaterial_GasFields::ConductivityCoefficientC, true);
    }

    bool Gas_Impl::setConductivityCoefficientC(double conductivityCoefficientC) {
      return setDouble(openstudio::WindowMaterial_GasFields::ConductivityCoefficientC, conductivityCoefficientC);
    }

    boost::optional<double> Gas_Impl::viscosityCoefficientA() const {
      return getDouble(openstudio::WindowMaterial_GasFields::ViscosityCoefficientA, true);
    }

    bool Gas_Impl::setViscosityCoefficientA(double viscosityCoefficientA) {
      return setDouble(openstudio::WindowMaterial_GasFields::ViscosityCoefficientA, viscosityCoefficientA);
    }

    boost::optional<double> Gas_Impl::viscosityCoefficientB() const {
      return getDouble(openstudio::WindowMaterial_GasFields::ViscosityCoefficientB, true);
    }

    bool Gas_Impl::setViscosityCoefficientB(double viscosityCoefficientB) {
      return setDouble(openstudio::WindowMaterial_GasFields::ViscosityCoefficientB, viscosityCoefficientB);
    }

    boost::optional<double> Gas_Impl::viscosityCoefficientC() const {
      return getDouble(openstudio::WindowMaterial_GasFields::ViscosityCoefficientC, true);
    }

    bool Gas_Impl::setViscosityCoefficientC(double viscosityCoefficientC) {
      return setDouble(openstudio::WindowMaterial_GasFields::ViscosityCoefficientC, viscosityCoefficientC);
    }

    boost::optional<double> Gas_Impl::specificHeatCoefficientA() const {
      return getDouble(openstudio::WindowMaterial_GasFields::SpecificHeatCoefficientA, true);
    }

    bool Gas_Impl::setSpecificHeatCoefficientA(double specificHeatCoefficientA) {
      return setDouble(openstudio::WindowMaterial_GasFields::SpecificHeatCoefficientA, specificHeatCoefficientA);
    }

    boost::optional<double> Gas_Impl::specificHeatCoefficientB() const {
      return getDouble(openstudio::WindowMaterial_GasFields::SpecificHeatCoefficientB, true);
    }

    bool Gas_Impl::setSpecificHeatCoefficientB(double specificHeatCoefficientB) {
      return setDouble(openstudio::WindowMaterial_GasFields::SpecificHeatCoefficientB, specificHeatCoefficientB);
    }

    boost::optional<double> Gas_Impl::specificHeatCoefficientC() const {
      return getDouble(openstudio::WindowMaterial_GasFields::SpecificHeatCoefficientC, true);
    }

    bool Gas_Impl::setSpecificHeatCoefficientC(double specificHeatCoefficientC) {
      return setDouble(openstudio::WindowMaterial_GasFields::SpecificHeatCoefficientC, specificHeatCoefficientC);
    }

    boost::optional<double> Gas_Impl::molecularWeight() const {
      return getDouble(openstudio::WindowMaterial_GasFields::MolecularWeight, true);
    }

    bool Gas_Impl::setMolecularWeight(double molecularWeight) {
      return setDouble(openstudio::WindowMaterial_GasFields::MolecularWeight, molecularWeight);
    }

    boost::optional<double> Gas_Impl::specificHeatRatio() const {
      return getDouble(openstudio::WindowMaterial_GasFields::SpecificHeatRatio, true);
    }

    bool Gas_Impl::setSpecificHeatRatio(double specificHeatRatio) {
      return setDouble(openstudio::WindowMaterial_GasFields::SpecificHeatRatio, specificHeatRatio);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
