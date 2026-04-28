/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "scaffolds/OutputSurfacesList.hpp"
#include "scaffolds/OutputSurfacesList_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Output_Surfaces_List_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  OutputSurfacesList::OutputSurfacesList(const Model& model) : ModelObject(OutputSurfacesList::iddObjectType(), model) {}

  OutputSurfacesList::OutputSurfacesList(std::shared_ptr<detail::OutputSurfacesList_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType OutputSurfacesList::iddObjectType() {
    return IddObjectType::Output_Surfaces_List;
  }

  std::vector<std::string> OutputSurfacesList::reportTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Output_Surfaces_ListFields::ReportType);
  }

  std::vector<std::string> OutputSurfacesList::reportSpecificationsValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Output_Surfaces_ListFields::ReportSpecifications);
  }

  std::string OutputSurfacesList::reportType() const {
    return getImpl<detail::OutputSurfacesList_Impl>()->reportType();
  }

  bool OutputSurfacesList::setReportType(const std::string& reportType) {
    return getImpl<detail::OutputSurfacesList_Impl>()->setReportType(reportType);
  }

  boost::optional<std::string> OutputSurfacesList::reportSpecifications() const {
    return getImpl<detail::OutputSurfacesList_Impl>()->reportSpecifications();
  }

  bool OutputSurfacesList::setReportSpecifications(const std::string& reportSpecifications) {
    return getImpl<detail::OutputSurfacesList_Impl>()->setReportSpecifications(reportSpecifications);
  }

  void OutputSurfacesList::resetReportSpecifications() {
    getImpl<detail::OutputSurfacesList_Impl>()->resetReportSpecifications();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string OutputSurfacesList_Impl::reportType() const {
      const auto value = getString(openstudio::Output_Surfaces_ListFields::ReportType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool OutputSurfacesList_Impl::setReportType(const std::string& reportType) {
      return setString(openstudio::Output_Surfaces_ListFields::ReportType, reportType);
    }

    boost::optional<std::string> OutputSurfacesList_Impl::reportSpecifications() const {
      return getString(openstudio::Output_Surfaces_ListFields::ReportSpecifications, true);
    }

    bool OutputSurfacesList_Impl::setReportSpecifications(const std::string& reportSpecifications) {
      return setString(openstudio::Output_Surfaces_ListFields::ReportSpecifications, reportSpecifications);
    }

    void OutputSurfacesList_Impl::resetReportSpecifications() {
      const bool result = setString(openstudio::Output_Surfaces_ListFields::ReportSpecifications, "");
      OS_ASSERT(result);
    }

    std::vector<std::string> OutputSurfacesList_Impl::reportTypeValues() const {
      return openstudio::epmodel::OutputSurfacesList::reportTypeValues();
    }

    std::vector<std::string> OutputSurfacesList_Impl::reportSpecificationsValues() const {
      return openstudio::epmodel::OutputSurfacesList::reportSpecificationsValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
