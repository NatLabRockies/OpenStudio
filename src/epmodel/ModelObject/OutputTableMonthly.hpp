/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTTABLEMONTHLY_HPP
#define EPMODEL_OUTPUTTABLEMONTHLY_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class OutputTableMonthly_Impl;
  }

  class EPMODEL_API OutputTableMonthly : public ModelObject
  {
   public:
    explicit OutputTableMonthly(const Model& model);

    virtual ~OutputTableMonthly() override = default;
    OutputTableMonthly(const OutputTableMonthly& other) = default;
    OutputTableMonthly(OutputTableMonthly&& other) = default;
    OutputTableMonthly& operator=(const OutputTableMonthly&) = default;
    OutputTableMonthly& operator=(OutputTableMonthly&&) = default;

    static IddObjectType iddObjectType();

    /** @name Digits After Decimal */
    //@{
    // Schema Alignment Notes:
    // - API: Preserves openstudio::model::OutputTableMonthly scalar accessor names/signatures.
    // - Field Mapping: digitsAfterDecimal maps directly to E+ Output:Table:Monthly Digits After Decimal.
    // - Field Mapping: monthlyVariableGroups and related extensible-group APIs are non-scalar scope and intentionally excluded in this pass.
    // - ForwardTranslator evidence: ForwardTranslateOutputTableMonthly.cpp writes modelObject.digitsAfterDecimal() directly to Output:Table:Monthly.
    // - TODO(parity): Add extensible monthly-variable-group APIs in a non-scalar pass while preserving this scalar API.
    int digitsAfterDecimal() const;

    bool setDigitsAfterDecimal(int digitsAfterDecimal);
    //@}

   protected:
    using ImplType = detail::OutputTableMonthly_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit OutputTableMonthly(std::shared_ptr<detail::OutputTableMonthly_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
