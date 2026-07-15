/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORFUELCELLAUXILIARYHEATER_HPP
#define EPMODEL_GENERATORFUELCELLAUXILIARYHEATER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GeneratorFuelCellAuxiliaryHeater_Impl;
  }

  class EPMODEL_API GeneratorFuelCellAuxiliaryHeater : public ModelObject
  {
   public:
    explicit GeneratorFuelCellAuxiliaryHeater(const Model& model);

    virtual ~GeneratorFuelCellAuxiliaryHeater() override = default;
    GeneratorFuelCellAuxiliaryHeater(const GeneratorFuelCellAuxiliaryHeater& other) = default;
    GeneratorFuelCellAuxiliaryHeater(GeneratorFuelCellAuxiliaryHeater&& other) = default;
    GeneratorFuelCellAuxiliaryHeater& operator=(const GeneratorFuelCellAuxiliaryHeater&) = default;
    GeneratorFuelCellAuxiliaryHeater& operator=(GeneratorFuelCellAuxiliaryHeater&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> skinLossDestinationValues();
    static std::vector<std::string> heatingCapacityUnitsValues();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model scalar accessor names/signatures for counterpart parity.
    // - Field Mapping: Scalar APIs map directly to Generator:FuelCell:AuxiliaryHeater scalar fields.
    // - Field Mapping: maximumHeatingCapacityinKmolperSecond and minimumHeatingCapacityinKmolperSecond preserve
    //   model API names and are mapped directly to the matching E+ fields.
    // - ForwardTranslator evidence: ForwardTranslateGeneratorFuelCellAuxiliaryHeater writes these scalar fields
    //   directly and handles Zone Name to Receive Skin Losses as a relationship target.
    // - TODO(parity): Add preserved relationship APIs incrementally for zone linkage and parent fuel-cell references.
    double excessAirRatio() const;
    bool setExcessAirRatio(double excessAirRatio);
    void resetExcessAirRatio();

    double ancillaryPowerConstantTerm() const;
    bool setAncillaryPowerConstantTerm(double ancillaryPowerConstantTerm);
    void resetAncillaryPowerConstantTerm();

    double ancillaryPowerLinearTerm() const;
    bool setAncillaryPowerLinearTerm(double ancillaryPowerLinearTerm);
    void resetAncillaryPowerLinearTerm();

    double skinLossUFactorTimesAreaValue() const;
    bool setSkinLossUFactorTimesAreaValue(double skinLossUFactorTimesAreaValue);
    void resetSkinLossUFactorTimesAreaValue();

    std::string skinLossDestination() const;
    bool setSkinLossDestination(const std::string& skinLossDestination);
    void resetSkinLossDestination();

    std::string heatingCapacityUnits() const;
    bool setHeatingCapacityUnits(const std::string& heatingCapacityUnits);
    void resetHeatingCapacityUnits();

    double maximumHeatingCapacityinWatts() const;
    bool setMaximumHeatingCapacityinWatts(double maximumHeatingCapacityinWatts);
    void resetMaximumHeatingCapacityinWatts();

    double minimumHeatingCapacityinWatts() const;
    bool setMinimumHeatingCapacityinWatts(double minimumHeatingCapacityinWatts);
    void resetMinimumHeatingCapacityinWatts();

    double maximumHeatingCapacityinKmolperSecond() const;
    bool setMaximumHeatingCapacityinKmolperSecond(double maximumHeatingCapacityinKmolperSecond);
    void resetMaximumHeatingCapacityinKmolperSecond();

    double minimumHeatingCapacityinKmolperSecond() const;
    bool setMinimumHeatingCapacityinKmolperSecond(double minimumHeatingCapacityinKmolperSecond);
    void resetMinimumHeatingCapacityinKmolperSecond();

   protected:
    using ImplType = detail::GeneratorFuelCellAuxiliaryHeater_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GeneratorFuelCellAuxiliaryHeater(std::shared_ptr<detail::GeneratorFuelCellAuxiliaryHeater_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
