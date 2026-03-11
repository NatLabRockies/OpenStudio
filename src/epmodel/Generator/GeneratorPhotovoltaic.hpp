/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORPHOTOVOLTAIC_HPP
#define EPMODEL_GENERATORPHOTOVOLTAIC_HPP

#include "EPModelAPI.hpp"
#include "ModelObject/ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class GeneratorPhotovoltaic_Impl;
}

class EPMODEL_API GeneratorPhotovoltaic : public ModelObject
{
 public:
  explicit GeneratorPhotovoltaic(const Model& model);

  virtual ~GeneratorPhotovoltaic() override = default;
  GeneratorPhotovoltaic(const GeneratorPhotovoltaic& other) = default;
  GeneratorPhotovoltaic(GeneratorPhotovoltaic&& other) = default;
  GeneratorPhotovoltaic& operator=(const GeneratorPhotovoltaic&) = default;
  GeneratorPhotovoltaic& operator=(GeneratorPhotovoltaic&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> heatTransferIntegrationModeValues();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model::GeneratorPhotovoltaic scalar accessor names/signatures for counterpart parity.
  // - Field Mapping: API numberOfModulesInParallel maps to E+ field NumberofSeriesStringsinParallel.
  // - Field Mapping: API numberOfModulesInSeries maps to E+ field NumberofModulesinSeries.
  // - ForwardTranslator evidence: ForwardTranslateGeneratorPhotovoltaic writes NumberofSeriesStringsinParallel from
  //   modelObject.numberOfModulesInParallel() and NumberofModulesinSeries from modelObject.numberOfModulesInSeries().
  // - ForwardTranslator evidence: model::ratedElectricPowerOutput is not translated for Generator:Photovoltaic in E+
  //   and is intentionally excluded from this scalar scaffold.
  // - TODO(parity): Add preserved relationship APIs (surface, photovoltaicPerformance, availabilitySchedule) in a
  //   dedicated relationship pass.
  std::string heatTransferIntegrationMode() const;
  bool isHeatTransferIntegrationModeDefaulted() const;
  bool setHeatTransferIntegrationMode(const std::string& heatTransferIntegrationMode);
  void resetHeatTransferIntegrationMode();

  double numberOfModulesInParallel() const;
  bool isNumberOfModulesInParallelDefaulted() const;
  bool setNumberOfModulesInParallel(double numberOfModulesInParallel);
  void resetNumberOfModulesInParallel();

  double numberOfModulesInSeries() const;
  bool isNumberOfModulesInSeriesDefaulted() const;
  bool setNumberOfModulesInSeries(double numberOfModulesInSeries);
  void resetNumberOfModulesInSeries();

 protected:
  using ImplType = detail::GeneratorPhotovoltaic_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit GeneratorPhotovoltaic(std::shared_ptr<detail::GeneratorPhotovoltaic_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
