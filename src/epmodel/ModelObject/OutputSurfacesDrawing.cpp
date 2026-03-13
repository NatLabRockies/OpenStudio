/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/OutputSurfacesDrawing.hpp"
#include "ModelObject/OutputSurfacesDrawing_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Output_Surfaces_Drawing_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

OutputSurfacesDrawing::OutputSurfacesDrawing(const Model& model) : ModelObject(OutputSurfacesDrawing::iddObjectType(), model) {}

OutputSurfacesDrawing::OutputSurfacesDrawing(std::shared_ptr<detail::OutputSurfacesDrawing_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType OutputSurfacesDrawing::iddObjectType() {
  return IddObjectType::Output_Surfaces_Drawing;
}

std::vector<std::string> OutputSurfacesDrawing::reportTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Output_Surfaces_DrawingFields::ReportType);
}

std::vector<std::string> OutputSurfacesDrawing::reportSpecifications1Values() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Output_Surfaces_DrawingFields::ReportSpecifications1);
}

std::string OutputSurfacesDrawing::reportType() const {
  return getImpl<detail::OutputSurfacesDrawing_Impl>()->reportType();
}

bool OutputSurfacesDrawing::setReportType(const std::string& reportType) {
  return getImpl<detail::OutputSurfacesDrawing_Impl>()->setReportType(reportType);
}

std::string OutputSurfacesDrawing::reportSpecifications1() const {
  return getImpl<detail::OutputSurfacesDrawing_Impl>()->reportSpecifications1();
}

bool OutputSurfacesDrawing::isReportSpecifications1Defaulted() const {
  return getImpl<detail::OutputSurfacesDrawing_Impl>()->isReportSpecifications1Defaulted();
}

bool OutputSurfacesDrawing::setReportSpecifications1(const std::string& reportSpecifications1) {
  return getImpl<detail::OutputSurfacesDrawing_Impl>()->setReportSpecifications1(reportSpecifications1);
}

void OutputSurfacesDrawing::resetReportSpecifications1() {
  getImpl<detail::OutputSurfacesDrawing_Impl>()->resetReportSpecifications1();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string OutputSurfacesDrawing_Impl::reportType() const {
  const auto value = getString(openstudio::Output_Surfaces_DrawingFields::ReportType, true);
  OS_ASSERT(value);
  return *value;
}

bool OutputSurfacesDrawing_Impl::setReportType(const std::string& reportType) {
  return setString(openstudio::Output_Surfaces_DrawingFields::ReportType, reportType);
}

std::string OutputSurfacesDrawing_Impl::reportSpecifications1() const {
  const auto value = getString(openstudio::Output_Surfaces_DrawingFields::ReportSpecifications1, true);
  OS_ASSERT(value);
  return *value;
}

bool OutputSurfacesDrawing_Impl::isReportSpecifications1Defaulted() const {
  return isEmpty(openstudio::Output_Surfaces_DrawingFields::ReportSpecifications1);
}

bool OutputSurfacesDrawing_Impl::setReportSpecifications1(const std::string& reportSpecifications1) {
  return setString(openstudio::Output_Surfaces_DrawingFields::ReportSpecifications1, reportSpecifications1);
}

void OutputSurfacesDrawing_Impl::resetReportSpecifications1() {
  const bool result = setString(openstudio::Output_Surfaces_DrawingFields::ReportSpecifications1, "");
  OS_ASSERT(result);
}

std::vector<std::string> OutputSurfacesDrawing_Impl::reportTypeValues() const {
  return openstudio::epmodel::OutputSurfacesDrawing::reportTypeValues();
}

std::vector<std::string> OutputSurfacesDrawing_Impl::reportSpecifications1Values() const {
  return openstudio::epmodel::OutputSurfacesDrawing::reportSpecifications1Values();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
