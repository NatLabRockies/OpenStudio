/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GASMIXTURE_HPP
#define EPMODEL_GASMIXTURE_HPP

#include "EPModelAPI.hpp"
#include "Material/Material.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GasMixture_Impl;
  }

  class EPMODEL_API GasMixture : public Material
  {
   public:
    explicit GasMixture(const Model& model);

    virtual ~GasMixture() override = default;
    GasMixture(const GasMixture& other) = default;
    GasMixture(GasMixture&& other) = default;
    GasMixture& operator=(const GasMixture&) = default;
    GasMixture& operator=(GasMixture&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> validGasTypes();
    static std::vector<std::string> gas1TypeValues();
    static std::vector<std::string> gas2TypeValues();
    static std::vector<std::string> gas3TypeValues();
    static std::vector<std::string> gas4TypeValues();

    // Schema Alignment Notes:
    // - API: preserve openstudio::model GasMixture scalar accessor names/signatures for the EnergyPlus WindowMaterial:GasMixture counterpart.
    // - Field Mapping: Thickness, Number of Gases in Mixture, and Gas 1-4 Type/Fraction fields map directly to the EnergyPlus schema.
    // - Optionality: Gas 3 and Gas 4 Type/Fraction fields are optional, so reset helpers are provided to clear those values when needed.
    double thickness() const;
    bool setThickness(double thickness);

    int numberofGasesinMixture() const;
    bool setNumberofGasesinMixture(int numberofGasesinMixture);

    unsigned numGases() const;

    std::string gas1Type() const;
    bool setGas1Type(const std::string& gas1Type);
    void resetGas1Type();
    double gas1Fraction() const;
    bool setGas1Fraction(double gas1Fraction);
    void resetGas1Fraction();

    std::string gas2Type() const;
    bool setGas2Type(const std::string& gas2Type);
    void resetGas2Type();
    double gas2Fraction() const;
    bool setGas2Fraction(double gas2Fraction);
    void resetGas2Fraction();

    std::string gas3Type() const;
    bool setGas3Type(const std::string& gas3Type);
    void resetGas3Type();
    boost::optional<double> gas3Fraction() const;
    bool setGas3Fraction(double gas3Fraction);
    void resetGas3Fraction();

    std::string gas4Type() const;
    bool setGas4Type(const std::string& gas4Type);
    void resetGas4Type();
    boost::optional<double> gas4Fraction() const;
    bool setGas4Fraction(double gas4Fraction);
    void resetGas4Fraction();

   protected:
    using ImplType = detail::GasMixture_Impl;

    explicit GasMixture(std::shared_ptr<detail::GasMixture_Impl> impl);

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_GASMIXTURE_HPP
