/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORFUELCELLINVERTER_HPP
#define EPMODEL_GENERATORFUELCELLINVERTER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GeneratorFuelCellInverter_Impl;
  }

  class EPMODEL_API GeneratorFuelCellInverter : public ModelObject
  {
   public:
    explicit GeneratorFuelCellInverter(const Model& model);

    virtual ~GeneratorFuelCellInverter() override = default;
    GeneratorFuelCellInverter(const GeneratorFuelCellInverter& other) = default;
    GeneratorFuelCellInverter(GeneratorFuelCellInverter&& other) = default;
    GeneratorFuelCellInverter& operator=(const GeneratorFuelCellInverter&) = default;
    GeneratorFuelCellInverter& operator=(GeneratorFuelCellInverter&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> inverterEfficiencyCalculationModeValues();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model scalar accessor naming/signatures for counterpart parity.
    // - Field Mapping: inverterEfficiencyCalculationMode and inverterEfficiency map directly to
    //   Generator:FuelCell:Inverter fields Inverter Efficiency Calculation Mode and Inverter Efficiency.
    // - ForwardTranslator evidence: ForwardTranslateGeneratorFuelCellInverter writes these scalar fields directly,
    //   while Efficiency Function of DC Power Curve Name is handled as a relationship field.
    // - TODO(parity): Add preserved relationship APIs incrementally for efficiencyFunctionofDCPowerCurve and parent linkage.
    std::string inverterEfficiencyCalculationMode() const;
    bool setInverterEfficiencyCalculationMode(const std::string& inverterEfficiencyCalculationMode);
    void resetInverterEfficiencyCalculationMode();

    double inverterEfficiency() const;
    bool setInverterEfficiency(double inverterEfficiency);
    void resetInverterEfficiency();

   protected:
    using ImplType = detail::GeneratorFuelCellInverter_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GeneratorFuelCellInverter(std::shared_ptr<detail::GeneratorFuelCellInverter_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
