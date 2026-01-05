/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OutputControlResilienceSummaries.hpp"
#include "OutputControlResilienceSummaries_Impl.hpp"

#include "Model.hpp"
#include "Model_Impl.hpp"

#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_OutputControl_ResilienceSummaries_FieldEnums.hxx>

#include "../utilities/idf/WorkspaceExtensibleGroup.hpp"
#include "../utilities/core/Assert.hpp"

namespace openstudio {
namespace model {

  namespace detail {

    OutputControlResilienceSummaries_Impl::OutputControlResilienceSummaries_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(idfObject, model, keepHandle) {
      OS_ASSERT(idfObject.iddObject().type() == OutputControlResilienceSummaries::iddObjectType());
    }

    OutputControlResilienceSummaries_Impl::OutputControlResilienceSummaries_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                                                                 Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(other, model, keepHandle) {
      OS_ASSERT(other.iddObject().type() == OutputControlResilienceSummaries::iddObjectType());
    }

    OutputControlResilienceSummaries_Impl::OutputControlResilienceSummaries_Impl(const OutputControlResilienceSummaries_Impl& other,
                                                                                 Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(other, model, keepHandle) {}

    const std::vector<std::string>& OutputControlResilienceSummaries_Impl::outputVariableNames() const {
      static const std::vector<std::string> result;
      return result;
    }

    IddObjectType OutputControlResilienceSummaries_Impl::iddObjectType() const {
      return OutputControlResilienceSummaries::iddObjectType();
    }

    std::string OutputControlResilienceSummaries_Impl::heatIndexAlgorithm() const {
      boost::optional<std::string> value = getString(OS_OutputControl_ResilienceSummariesFields::HeatIndexAlgorithm, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool OutputControlResilienceSummaries_Impl::setHeatIndexAlgorithm(const std::string& heatIndexAlgorithm) {
      bool result = setString(OS_OutputControl_ResilienceSummariesFields::HeatIndexAlgorithm, heatIndexAlgorithm);
      return result;
    }

  }  // namespace detail

  IddObjectType OutputControlResilienceSummaries::iddObjectType() {
    return {IddObjectType::OS_OutputControl_ResilienceSummaries};
  }

  std::vector<std::string> OutputControlResilienceSummaries::heatIndexAlgorithmValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), OS_OutputControl_ResilienceSummariesFields::HeatIndexAlgorithm);
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

  /// @cond
  OutputControlResilienceSummaries::OutputControlResilienceSummaries(std::shared_ptr<detail::OutputControlResilienceSummaries_Impl> impl)
    : ModelObject(impl) {}
  OutputControlResilienceSummaries::OutputControlResilienceSummaries(Model& model)
    : ModelObject(OutputControlResilienceSummaries::iddObjectType(), model) {
    bool ok = setHeatIndexAlgorithm("Simplified");
    OS_ASSERT(ok);
  }

  /// @endcond

}  // namespace model
}  // namespace openstudio
