/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTTABLESUMMARYREPORTS_HPP
#define EPMODEL_OUTPUTTABLESUMMARYREPORTS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class OutputTableSummaryReports_Impl;
}

class EPMODEL_API OutputTableSummaryReports : public ModelObject
{
 public:
  static constexpr bool is_unique = true;  // This is a Unique ModelObject

  explicit OutputTableSummaryReports(const Model& model);

  virtual ~OutputTableSummaryReports() override = default;
  OutputTableSummaryReports(const OutputTableSummaryReports& other) = default;
  OutputTableSummaryReports(OutputTableSummaryReports&& other) = default;
  OutputTableSummaryReports& operator=(const OutputTableSummaryReports&) = default;
  OutputTableSummaryReports& operator=(OutputTableSummaryReports&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model::OutputTableSummaryReports class naming for counterpart parity.
  // - Field Mapping: Output:Table:SummaryReports currently exposes only extensible Report Name fields (no simple scalar non-extensible fields).
  // - Field Mapping: Extensible summary-report list APIs are non-scalar and intentionally excluded in this scalar-only scaffold pass.
  // - ForwardTranslator evidence: ForwardTranslateOutputTableSummaryReports.cpp writes each summary report via extensible ReportName groups.
  // - TODO(parity): Add non-scalar extensible-group APIs incrementally without breaking class identity and base scalar behavior.

 protected:
  using ImplType = detail::OutputTableSummaryReports_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit OutputTableSummaryReports(std::shared_ptr<detail::OutputTableSummaryReports_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
