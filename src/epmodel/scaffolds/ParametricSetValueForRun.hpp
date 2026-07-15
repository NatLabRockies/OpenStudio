/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PARAMETRICSETVALUEFORRUN_HPP
#define EPMODEL_PARAMETRICSETVALUEFORRUN_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ParametricSetValueForRun_Impl;
  }

  class EPMODEL_API ParametricSetValueForRun : public ModelObject
  {
   public:
    explicit ParametricSetValueForRun(const Model& model);

    virtual ~ParametricSetValueForRun() override = default;
    ParametricSetValueForRun(const ParametricSetValueForRun& other) = default;
    ParametricSetValueForRun(ParametricSetValueForRun&& other) = default;
    ParametricSetValueForRun& operator=(const ParametricSetValueForRun&) = default;
    ParametricSetValueForRun& operator=(ParametricSetValueForRun&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type keeps IDD-derived class/API naming.
    // - Field Mapping: Fixed scalar field Name remains available through base ModelObject scalar APIs.
    // - Field Mapping: Extensible run-value entries are intentionally excluded from scalar accessors in this scaffold pass.
    // - TODO(parity): Add non-scalar extensible-group APIs for per-run value entries in a future pass.

   protected:
    using ImplType = detail::ParametricSetValueForRun_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ParametricSetValueForRun(std::shared_ptr<detail::ParametricSetValueForRun_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
