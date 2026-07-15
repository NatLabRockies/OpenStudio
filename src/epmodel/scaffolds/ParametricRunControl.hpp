/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PARAMETRICRUNCONTROL_HPP
#define EPMODEL_PARAMETRICRUNCONTROL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ParametricRunControl_Impl;
  }

  class EPMODEL_API ParametricRunControl : public ModelObject
  {
   public:
    explicit ParametricRunControl(const Model& model);

    virtual ~ParametricRunControl() override = default;
    ParametricRunControl(const ParametricRunControl& other) = default;
    ParametricRunControl(ParametricRunControl&& other) = default;
    ParametricRunControl& operator=(const ParametricRunControl&) = default;
    ParametricRunControl& operator=(ParametricRunControl&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type keeps IDD-derived class/API naming.
    // - Field Mapping: Fixed scalar field Name remains available through base ModelObject scalar APIs.
    // - Field Mapping: Extensible "Perform Run N" entries are intentionally excluded from scalar accessors in this scaffold pass.
    // - TODO(parity): Add non-scalar extensible-group APIs for run-control lists in a future pass.

   protected:
    using ImplType = detail::ParametricRunControl_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ParametricRunControl(std::shared_ptr<detail::ParametricRunControl_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
