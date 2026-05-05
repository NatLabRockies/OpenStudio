/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTDIAGNOSTICS_HPP
#define EPMODEL_OUTPUTDIAGNOSTICS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class OutputDiagnostics_Impl;
  }

  class EPMODEL_API OutputDiagnostics : public ModelObject
  {
   public:
    virtual ~OutputDiagnostics() override = default;
    OutputDiagnostics(const OutputDiagnostics& other) = default;
    OutputDiagnostics(OutputDiagnostics&& other) = default;
    OutputDiagnostics& operator=(const OutputDiagnostics&) = default;
    OutputDiagnostics& operator=(OutputDiagnostics&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model::OutputDiagnostics class naming for counterpart parity.
    // - Field Mapping: Output:Diagnostics has extensible Key entries only; scalar field APIs are intentionally not added in this scalar-only scaffold pass.
    // - ForwardTranslator evidence: ForwardTranslateOutputDiagnostics.cpp emits one extensible Key per model key and skips translation when no keys exist.
    // - TODO(parity): Add non-scalar key list APIs (keys/addKey/setKeys/clearKeys) in a later parity pass without breaking this class identity.

   protected:
    explicit OutputDiagnostics(const Model& model);

    using ImplType = detail::OutputDiagnostics_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit OutputDiagnostics(std::shared_ptr<detail::OutputDiagnostics_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
