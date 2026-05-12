/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FenestrationMaterial/FenestrationMaterial.hpp"
#include "FenestrationMaterial/FenestrationMaterial_Impl.hpp"

namespace openstudio {
namespace epmodel {

  double FenestrationMaterial::ufactorInsideAirTemperature() {
    return 294.261111111;
  }

  double FenestrationMaterial::ufactorOutsideAirTemperature() {
    return 255.372222222;
  }

  std::vector<double> FenestrationMaterial::airThermalConductivityCoefficients() {
    return {2.873E-3, 7.760E-5, 0.0};
  }

  std::vector<double> FenestrationMaterial::airViscosityCoefficients() {
    return {3.723E-6, 4.940E-8, 0.0};
  }

  std::vector<double> FenestrationMaterial::airSpecificHeatCoefficients() {
    return {1002.737, 1.2324E-2, 0.0};
  }

  double FenestrationMaterial::airMolecularWeight() {
    return 28.97;
  }

  std::vector<double> FenestrationMaterial::argonThermalConductivityCoefficients() {
    return {2.285E-3, 5.149E-5, 0.0};
  }

  std::vector<double> FenestrationMaterial::argonViscosityCoefficients() {
    return {3.379E-6, 6.451E-8, 0.0};
  }

  std::vector<double> FenestrationMaterial::argonSpecificHeatCoefficients() {
    return {521.929, 0.0, 0.0};
  }

  double FenestrationMaterial::argonMolecularWeight() {
    return 39.94;
  }

  std::vector<double> FenestrationMaterial::kryptonThermalConductivityCoefficients() {
    return {9.443E-4, 2.826E-5, 0.0};
  }

  std::vector<double> FenestrationMaterial::kryptonViscosityCoefficients() {
    return {2.213E-6, 7.777E-8, 0.0};
  }

  std::vector<double> FenestrationMaterial::kryptonSpecificHeatCoefficients() {
    return {248.091, 0.0, 0.0};
  }

  double FenestrationMaterial::kryptonMolecularWeight() {
    return 83.8;
  }

  std::vector<double> FenestrationMaterial::xenonThermalConductivityCoefficients() {
    return {4.538E-4, 1.723E-5, 0.0};
  }

  std::vector<double> FenestrationMaterial::xenonViscosityCoefficients() {
    return {1.069E-6, 7.414E-8, 0.0};
  }

  std::vector<double> FenestrationMaterial::xenonSpecificHeatCoefficients() {
    return {158.34, 0.0, 0.0};
  }

  double FenestrationMaterial::xenonMolecularWeight() {
    return 131.29;
  }

  FenestrationMaterial::FenestrationMaterial(IddObjectType type, const Model& model) : Material(type, model) {}

  FenestrationMaterial::FenestrationMaterial(std::shared_ptr<detail::FenestrationMaterial_Impl> impl) : Material(std::move(impl)) {}

}  // namespace epmodel
}  // namespace openstudio
