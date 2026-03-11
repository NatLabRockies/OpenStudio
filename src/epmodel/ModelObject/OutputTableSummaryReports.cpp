/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OutputTableSummaryReports.hpp"
#include "OutputTableSummaryReports_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

OutputTableSummaryReports::OutputTableSummaryReports(const Model& model)
  : ModelObject(OutputTableSummaryReports::iddObjectType(), model) {}

OutputTableSummaryReports::OutputTableSummaryReports(std::shared_ptr<detail::OutputTableSummaryReports_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType OutputTableSummaryReports::iddObjectType() {
  return IddObjectType::Output_Table_SummaryReports;
}

}  // namespace epmodel
}  // namespace openstudio
