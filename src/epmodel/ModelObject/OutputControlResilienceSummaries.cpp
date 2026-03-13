/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OutputControlResilienceSummaries.hpp"
#include "OutputControlResilienceSummaries_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/OutputControl_ResilienceSummaries_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  OutputControlResilienceSummaries::OutputControlResilienceSummaries(const Model& model)
    : ModelObject(OutputControlResilienceSummaries::iddObjectType(), model) {
    const bool ok = setHeatIndexAlgorithm("Simplified");
    OS_ASSERT(ok);
  }

  OutputControlResilienceSummaries::OutputControlResilienceSummaries(std::shared_ptr<detail::OutputControlResilienceSummaries_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType OutputControlResilienceSummaries::iddObjectType() {
    return IddObjectType::OutputControl_ResilienceSummaries;
  }

  std::vector<std::string> OutputControlResilienceSummaries::heatIndexAlgorithmValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::OutputControl_ResilienceSummariesFields::HeatIndexAlgorithm);
  }

  std::vector<std::string> OutputControlResilienceSummaries::validHeatIndexAlgorithmValues() {
    return heatIndexAlgorithmValues();
  }

  std::string OutputControlResilienceSummaries::heatIndexAlgorithm() const {
    return getImpl<detail::OutputControlResilienceSummaries_Impl>()->heatIndexAlgorithm();
  }

  bool OutputControlResilienceSummaries::setHeatIndexAlgorithm(const std::string& heatIndexAlgorithm) {
    return getImpl<detail::OutputControlResilienceSummaries_Impl>()->setHeatIndexAlgorithm(heatIndexAlgorithm);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::vector<std::string> OutputControlResilienceSummaries_Impl::heatIndexAlgorithmValues() const {
      return openstudio::epmodel::OutputControlResilienceSummaries::heatIndexAlgorithmValues();
    }

    std::vector<std::string> OutputControlResilienceSummaries_Impl::validHeatIndexAlgorithmValues() const {
      return openstudio::epmodel::OutputControlResilienceSummaries::validHeatIndexAlgorithmValues();
    }

    std::string OutputControlResilienceSummaries_Impl::heatIndexAlgorithm() const {
      const auto value = getString(openstudio::OutputControl_ResilienceSummariesFields::HeatIndexAlgorithm, true);
      OS_ASSERT(value);
      return *value;
    }

    bool OutputControlResilienceSummaries_Impl::setHeatIndexAlgorithm(const std::string& heatIndexAlgorithm) {
      return setString(openstudio::OutputControl_ResilienceSummariesFields::HeatIndexAlgorithm, heatIndexAlgorithm);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
