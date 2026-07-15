/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTTABLEANNUAL_HPP
#define EPMODEL_OUTPUTTABLEANNUAL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class OutputTableAnnual_Impl;
  }

  class EPMODEL_API OutputTableAnnual : public ModelObject
  {
   public:
    explicit OutputTableAnnual(const Model& model);

    virtual ~OutputTableAnnual() override = default;
    OutputTableAnnual(const OutputTableAnnual& other) = default;
    OutputTableAnnual(OutputTableAnnual&& other) = default;
    OutputTableAnnual& operator=(const OutputTableAnnual&) = default;
    OutputTableAnnual& operator=(OutputTableAnnual&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model::OutputTableAnnual scalar accessor names/signatures for counterpart parity.
    // - Field Mapping: filter maps directly to E+ Output:Table:Annual Filter.
    // - Field Mapping: schedule and extensible annual-variable-group fields are relationship/extensible scope and intentionally excluded in this scalar-only pass.
    // - ForwardTranslator evidence: ForwardTranslateOutputTableAnnual.cpp maps modelObject.filter() directly to Output:Table:Annual Filter.
    // - TODO(parity): Add schedule/extensible-group APIs in a later non-scalar pass without breaking this preserved scalar API.
    boost::optional<std::string> filter() const;

    bool setFilter(const std::string& filter);
    void resetFilter();

   protected:
    using ImplType = detail::OutputTableAnnual_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit OutputTableAnnual(std::shared_ptr<detail::OutputTableAnnual_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
