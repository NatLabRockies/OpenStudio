/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTVARIABLE_HPP
#define EPMODEL_OUTPUTVARIABLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class OutputVariable_Impl;
  }

  class EPMODEL_API OutputVariable : public ModelObject
  {
   public:
    explicit OutputVariable(const std::string& variableName, const Model& model);

    virtual ~OutputVariable() override = default;
    OutputVariable(const OutputVariable& other) = default;
    OutputVariable(OutputVariable&& other) = default;
    OutputVariable& operator=(const OutputVariable&) = default;
    OutputVariable& operator=(OutputVariable&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> reportingFrequencyValues();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model::OutputVariable scalar accessor names/signatures.
    // - Field Mapping: keyValue/variableName/reportingFrequency map directly to E+ Output:Variable Key Value/Variable Name/Reporting Frequency.
    // - API Semantics: variableName is required (strict getter); keyValue/reportingFrequency are defaultable with reset/isDefaulted helpers.
    // - Field Mapping: schedule() APIs are relationship-like (Schedule Name object target) and are intentionally excluded from scalar scaffold.
    // - Field Mapping: exportToBCVTB APIs are OS-only and not present on E+ Output:Variable, so excluded from this epmodel scalar class.
    // - ForwardTranslator evidence: ForwardTranslateOutputVariable.cpp writes Key Value, Variable Name, and Reporting Frequency from these preserved APIs.
    // - TODO(parity): Add relationship and OS-side parity behavior incrementally without changing these scalar signatures.
    // Key Value
    std::string keyValue() const;
    bool isKeyValueDefaulted() const;
    bool setKeyValue(const std::string& keyValue);
    void resetKeyValue();

    // Variable Name
    std::string variableName() const;
    bool setVariableName(const std::string& variableName);

    // Reporting Frequency
    std::string reportingFrequency() const;
    bool isReportingFrequencyDefaulted() const;
    bool setReportingFrequency(const std::string& reportingFrequency);
    void resetReportingFrequency();

   protected:
    using ImplType = detail::OutputVariable_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit OutputVariable(std::shared_ptr<detail::OutputVariable_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
