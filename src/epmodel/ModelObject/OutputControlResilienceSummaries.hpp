/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTCONTROLRESILIENCESUMMARIES_HPP
#define EPMODEL_OUTPUTCONTROLRESILIENCESUMMARIES_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class OutputControlResilienceSummaries_Impl;
}

class EPMODEL_API OutputControlResilienceSummaries : public ModelObject
{
 public:
  explicit OutputControlResilienceSummaries(const Model& model);

  virtual ~OutputControlResilienceSummaries() override = default;
  OutputControlResilienceSummaries(const OutputControlResilienceSummaries& other) = default;
  OutputControlResilienceSummaries(OutputControlResilienceSummaries&& other) = default;
  OutputControlResilienceSummaries& operator=(const OutputControlResilienceSummaries&) = default;
  OutputControlResilienceSummaries& operator=(OutputControlResilienceSummaries&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> heatIndexAlgorithmValues();
  static std::vector<std::string> validHeatIndexAlgorithmValues();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model::OutputControlResilienceSummaries accessor names/signatures.
  // - Field Mapping: heatIndexAlgorithm maps directly to E+ OutputControl:ResilienceSummaries Heat Index Algorithm.
  // - ForwardTranslator evidence: model ForwardTranslateOutputControlResilienceSummaries.cpp maps this same scalar API
  //   directly to OutputControl:ResilienceSummaries Heat Index Algorithm.
  // - TODO(parity): Keep scalar API stable while broader epmodel parity is developed.
  std::string heatIndexAlgorithm() const;
  bool setHeatIndexAlgorithm(const std::string& heatIndexAlgorithm);

 protected:
  using ImplType = detail::OutputControlResilienceSummaries_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit OutputControlResilienceSummaries(std::shared_ptr<detail::OutputControlResilienceSummaries_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
