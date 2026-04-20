/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_UTILITYCOSTCOMPUTATION_HPP
#define EPMODEL_UTILITYCOSTCOMPUTATION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <string>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class UtilityCostComputation_Impl;
  }

  class EPMODEL_API UtilityCostComputation : public ModelObject
  {
   public:
    explicit UtilityCostComputation(const Model& model);

    virtual ~UtilityCostComputation() override = default;
    UtilityCostComputation(const UtilityCostComputation& other) = default;
    UtilityCostComputation(UtilityCostComputation&& other) = default;
    UtilityCostComputation& operator=(const UtilityCostComputation&) = default;
    UtilityCostComputation& operator=(UtilityCostComputation&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: No openstudio::model counterpart exists, so IDD-derived naming is conserved for the generated type.
    // - Field Mapping: Tariff Name is an object-list reference; the relationship helper is deferred until future parity.
    // - Field Mapping: Compute Step is part of the extensible series of statements and is intentionally excluded from this scalar-only pass.

   protected:
    using ImplType = detail::UtilityCostComputation_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit UtilityCostComputation(std::shared_ptr<detail::UtilityCostComputation_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
