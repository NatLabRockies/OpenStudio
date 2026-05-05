/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORFUELCELLWATERSUPPLY_HPP
#define EPMODEL_GENERATORFUELCELLWATERSUPPLY_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GeneratorFuelCellWaterSupply_Impl;
  }

  class EPMODEL_API GeneratorFuelCellWaterSupply : public ModelObject
  {
   public:
    explicit GeneratorFuelCellWaterSupply(const Model& model);

    virtual ~GeneratorFuelCellWaterSupply() override = default;
    GeneratorFuelCellWaterSupply(const GeneratorFuelCellWaterSupply& other) = default;
    GeneratorFuelCellWaterSupply(GeneratorFuelCellWaterSupply&& other) = default;
    GeneratorFuelCellWaterSupply& operator=(const GeneratorFuelCellWaterSupply&) = default;
    GeneratorFuelCellWaterSupply& operator=(GeneratorFuelCellWaterSupply&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> waterTemperatureModelingModeValues();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model scalar accessor names/signatures for counterpart parity.
    // - Field Mapping: pumpHeatLossFactor and waterTemperatureModelingMode map directly to
    //   Generator:FuelCell:WaterSupply fields Pump Heat Loss Factor and Water Temperature Modeling Mode.
    // - ForwardTranslator evidence: ForwardTranslateGeneratorFuelCellWaterSupply writes these scalar fields directly,
    //   while curve/node/schedule references are handled as relationship targets.
    // - TODO(parity): Add preserved relationship APIs incrementally for reformer curve references and water node/schedule linkage.
    double pumpHeatLossFactor() const;
    bool setPumpHeatLossFactor(double pumpHeatLossFactor);
    void resetPumpHeatLossFactor();

    std::string waterTemperatureModelingMode() const;
    bool setWaterTemperatureModelingMode(const std::string& waterTemperatureModelingMode);
    void resetWaterTemperatureModelingMode();

   protected:
    using ImplType = detail::GeneratorFuelCellWaterSupply_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GeneratorFuelCellWaterSupply(std::shared_ptr<detail::GeneratorFuelCellWaterSupply_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
