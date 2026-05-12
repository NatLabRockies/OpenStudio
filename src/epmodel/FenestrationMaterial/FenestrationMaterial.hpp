/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FENESTRATIONMATERIAL_HPP
#define EPMODEL_FENESTRATIONMATERIAL_HPP

#include "EPModelAPI.hpp"
#include "Material/Material.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {
    class FenestrationMaterial_Impl;
  }

  /** A FenestrationMaterial is a Material that serves as a base class for all materials used in
   *  fenestration (window/door) constructions, including glazing layers, gas layers, and shading
   *  materials. It also provides gas property coefficients used by EnergyPlus for U-factor
   *  calculations. */
  class EPMODEL_API FenestrationMaterial : public Material
  {
   public:
    virtual ~FenestrationMaterial() override = default;
    FenestrationMaterial(const FenestrationMaterial& other) = default;
    FenestrationMaterial(FenestrationMaterial&& other) = default;
    FenestrationMaterial& operator=(const FenestrationMaterial&) = default;
    FenestrationMaterial& operator=(FenestrationMaterial&&) = default;

    /** @name Static Methods */
    //@{

    /** Returns the inside air temperature used by EnergyPlus for calculating fenestration
     *  U-factors (K). */
    static double ufactorInsideAirTemperature();

    /** Returns the outside air temperature used by EnergyPlus for calculating fenestration
     *  U-factors (K). */
    static double ufactorOutsideAirTemperature();

    /** Returns the conductivity coefficients for air. */
    static std::vector<double> airThermalConductivityCoefficients();

    /** Returns the viscosity coefficients for air. */
    static std::vector<double> airViscosityCoefficients();

    /** Returns the specific heat coefficients for air. */
    static std::vector<double> airSpecificHeatCoefficients();

    /** The molecular weight of air (u). */
    static double airMolecularWeight();

    /** Returns the conductivity coefficients for argon. */
    static std::vector<double> argonThermalConductivityCoefficients();

    /** Returns the viscosity coefficients for argon. */
    static std::vector<double> argonViscosityCoefficients();

    /** Returns the specific heat coefficients for argon. */
    static std::vector<double> argonSpecificHeatCoefficients();

    /** The molecular weight of argon (u). */
    static double argonMolecularWeight();

    /** Returns the conductivity coefficients for krypton. */
    static std::vector<double> kryptonThermalConductivityCoefficients();

    /** Returns the viscosity coefficients for krypton. */
    static std::vector<double> kryptonViscosityCoefficients();

    /** Returns the specific heat coefficients for krypton. */
    static std::vector<double> kryptonSpecificHeatCoefficients();

    /** The molecular weight of krypton (u). */
    static double kryptonMolecularWeight();

    /** Returns the conductivity coefficients for xenon. */
    static std::vector<double> xenonThermalConductivityCoefficients();

    /** Returns the viscosity coefficients for xenon. */
    static std::vector<double> xenonViscosityCoefficients();

    /** Returns the specific heat coefficients for xenon. */
    static std::vector<double> xenonSpecificHeatCoefficients();

    /** The molecular weight of xenon (u). */
    static double xenonMolecularWeight();

    //@}

   protected:
    using ImplType = detail::FenestrationMaterial_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    FenestrationMaterial(IddObjectType type, const Model& model);

    explicit FenestrationMaterial(std::shared_ptr<detail::FenestrationMaterial_Impl> impl);

   private:
    REGISTER_LOGGER("openstudio.epmodel.FenestrationMaterial");
  };

  using OptionalFenestrationMaterial = boost::optional<FenestrationMaterial>;
  using FenestrationMaterialVector = std::vector<FenestrationMaterial>;

}  // namespace epmodel
}  // namespace openstudio

#endif
