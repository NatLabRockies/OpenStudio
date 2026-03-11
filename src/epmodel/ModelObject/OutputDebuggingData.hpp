/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTDEBUGGINGDATA_HPP
#define EPMODEL_OUTPUTDEBUGGINGDATA_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class OutputDebuggingData_Impl;
}

class EPMODEL_API OutputDebuggingData : public ModelObject
{
 public:
  explicit OutputDebuggingData(const Model& model);

  virtual ~OutputDebuggingData() override = default;
  OutputDebuggingData(const OutputDebuggingData& other) = default;
  OutputDebuggingData(OutputDebuggingData&& other) = default;
  OutputDebuggingData& operator=(const OutputDebuggingData&) = default;
  OutputDebuggingData& operator=(OutputDebuggingData&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model::OutputDebuggingData scalar accessor names/signatures.
  // - Field Mapping: reportDebuggingData/reportDuringWarmup map directly to E+ Output:DebuggingData Report Debugging Data/Report During Warmup.
  // - ForwardTranslator evidence: ForwardTranslateOutputDebuggingData.cpp writes these two boolean fields directly as Yes/No.
  // - TODO(parity): Keep scalar-only scope for this pass and extend later without breaking preserved API signatures.
  bool reportDebuggingData() const;
  bool reportDuringWarmup() const;

  bool setReportDebuggingData(bool reportDebuggingData);
  bool setReportDuringWarmup(bool reportDuringWarmup);

 protected:
  using ImplType = detail::OutputDebuggingData_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit OutputDebuggingData(std::shared_ptr<detail::OutputDebuggingData_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
