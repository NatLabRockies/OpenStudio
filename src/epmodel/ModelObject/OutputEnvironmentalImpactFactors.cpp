/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/OutputEnvironmentalImpactFactors.hpp"
#include "ModelObject/OutputEnvironmentalImpactFactors_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Output_EnvironmentalImpactFactors_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  OutputEnvironmentalImpactFactors::OutputEnvironmentalImpactFactors(const Model& model)
    : ModelObject(OutputEnvironmentalImpactFactors::iddObjectType(), model) {
    OS_ASSERT(setReportingFrequency("Monthly"));
  }

  OutputEnvironmentalImpactFactors::OutputEnvironmentalImpactFactors(std::shared_ptr<detail::OutputEnvironmentalImpactFactors_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType OutputEnvironmentalImpactFactors::iddObjectType() {
    return IddObjectType::Output_EnvironmentalImpactFactors;
  }

  std::vector<std::string> OutputEnvironmentalImpactFactors::reportingFrequencyValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Output_EnvironmentalImpactFactorsFields::ReportingFrequency);
  }

  std::string OutputEnvironmentalImpactFactors::reportingFrequency() const {
    return getImpl<detail::OutputEnvironmentalImpactFactors_Impl>()->reportingFrequency();
  }

  bool OutputEnvironmentalImpactFactors::setReportingFrequency(const std::string& reportingFrequency) {
    return getImpl<detail::OutputEnvironmentalImpactFactors_Impl>()->setReportingFrequency(reportingFrequency);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string OutputEnvironmentalImpactFactors_Impl::reportingFrequency() const {
      const auto value = getString(openstudio::Output_EnvironmentalImpactFactorsFields::ReportingFrequency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool OutputEnvironmentalImpactFactors_Impl::setReportingFrequency(const std::string& reportingFrequency) {
      return setString(openstudio::Output_EnvironmentalImpactFactorsFields::ReportingFrequency, reportingFrequency);
    }

    std::vector<std::string> OutputEnvironmentalImpactFactors_Impl::reportingFrequencyValues() const {
      return openstudio::epmodel::OutputEnvironmentalImpactFactors::reportingFrequencyValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
