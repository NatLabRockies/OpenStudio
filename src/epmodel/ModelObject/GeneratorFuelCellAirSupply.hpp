/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORFUELCELLAIRSUPPLY_HPP
#define EPMODEL_GENERATORFUELCELLAIRSUPPLY_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GeneratorFuelCellAirSupply_Impl;
  }

  class EPMODEL_API GeneratorFuelCellAirSupply : public ModelObject
  {
   public:
    explicit GeneratorFuelCellAirSupply(const Model& model);

    virtual ~GeneratorFuelCellAirSupply() override = default;
    GeneratorFuelCellAirSupply(const GeneratorFuelCellAirSupply& other) = default;
    GeneratorFuelCellAirSupply(GeneratorFuelCellAirSupply&& other) = default;
    GeneratorFuelCellAirSupply& operator=(const GeneratorFuelCellAirSupply&) = default;
    GeneratorFuelCellAirSupply& operator=(GeneratorFuelCellAirSupply&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> airSupplyRateCalculationModeValues();
    static std::vector<std::string> airIntakeHeatRecoveryModeValues();
    static std::vector<std::string> airSupplyConstituentModeValues();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model scalar accessor naming/signatures for counterpart parity.
    // - Field Mapping: Scalar APIs map directly to Generator:FuelCell:AirSupply fields Blower Heat Loss Factor,
    //   Air Supply Rate Calculation Mode, Stoichiometric Ratio, Air Rate Air Temperature Coefficient,
    //   Air Intake Heat Recovery Mode, and Air Supply Constituent Mode.
    // - Field Mapping: numberofUserDefinedConstituents follows existing model behavior and reflects extensible group count.
    // - ForwardTranslator evidence: ForwardTranslateGeneratorFuelCellAirSupply writes these scalar fields and handles
    //   air-node/curve/extensible relationships separately.
    // - TODO(parity): Add preserved relationship APIs incrementally for air inlet node, curve references, and constituents.
    // Blower Heat Loss Factor accessors
    double blowerHeatLossFactor() const;
    bool setBlowerHeatLossFactor(double blowerHeatLossFactor);
    void resetBlowerHeatLossFactor();

    // Air Supply Rate Calculation Mode accessors
    std::string airSupplyRateCalculationMode() const;
    bool setAirSupplyRateCalculationMode(const std::string& airSupplyRateCalculationMode);

    // Stoichiometric Ratio accessors
    boost::optional<double> stoichiometricRatio() const;
    bool setStoichiometricRatio(double stoichiometricRatio);
    void resetStoichiometricRatio();

    // Air Rate Air Temperature Coefficient accessors
    boost::optional<double> airRateAirTemperatureCoefficient() const;
    bool setAirRateAirTemperatureCoefficient(double airRateAirTemperatureCoefficient);
    void resetAirRateAirTemperatureCoefficient();

    // Air Intake Heat Recovery Mode accessors
    std::string airIntakeHeatRecoveryMode() const;
    bool setAirIntakeHeatRecoveryMode(const std::string& airIntakeHeatRecoveryMode);

    // Air Supply Constituent Mode accessors
    std::string airSupplyConstituentMode() const;
    bool setAirSupplyConstituentMode(const std::string& airSupplyConstituentMode);

    // User defined constituent group count
    boost::optional<unsigned int> numberofUserDefinedConstituents() const;

   protected:
    using ImplType = detail::GeneratorFuelCellAirSupply_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GeneratorFuelCellAirSupply(std::shared_ptr<detail::GeneratorFuelCellAirSupply_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
