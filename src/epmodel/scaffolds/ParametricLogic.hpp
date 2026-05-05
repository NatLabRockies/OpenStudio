/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PARAMETRICLOGIC_HPP
#define EPMODEL_PARAMETRICLOGIC_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ParametricLogic_Impl;
  }

  class EPMODEL_API ParametricLogic : public ModelObject
  {
   public:
    explicit ParametricLogic(const Model& model);

    virtual ~ParametricLogic() override = default;
    ParametricLogic(const ParametricLogic& other) = default;
    ParametricLogic(ParametricLogic&& other) = default;
    ParametricLogic& operator=(const ParametricLogic&) = default;
    ParametricLogic& operator=(ParametricLogic&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type keeps IDD-derived class/API naming.
    // - Field Mapping: Fixed scalar field Name remains available through base ModelObject scalar APIs.
    // - Field Mapping: Extensible "Parametric Logic Line" entries are intentionally excluded from scalar accessors in this scaffold pass.
    // - TODO(parity): Add non-scalar extensible-group APIs for logic-line management in a future pass.

   protected:
    using ImplType = detail::ParametricLogic_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ParametricLogic(std::shared_ptr<detail::ParametricLogic_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
