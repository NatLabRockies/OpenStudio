/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PARAMETRICFILENAMESUFFIX_HPP
#define EPMODEL_PARAMETRICFILENAMESUFFIX_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ParametricFileNameSuffix_Impl;
}

class EPMODEL_API ParametricFileNameSuffix : public ModelObject
{
 public:
  explicit ParametricFileNameSuffix(const Model& model);

  virtual ~ParametricFileNameSuffix() override = default;
  ParametricFileNameSuffix(const ParametricFileNameSuffix& other) = default;
  ParametricFileNameSuffix(ParametricFileNameSuffix&& other) = default;
  ParametricFileNameSuffix& operator=(const ParametricFileNameSuffix&) = default;
  ParametricFileNameSuffix& operator=(ParametricFileNameSuffix&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type keeps IDD-derived class/API naming.
  // - Field Mapping: Fixed scalar field Name remains available through base ModelObject scalar APIs.
  // - Field Mapping: Extensible "Suffix for File Name in Run" entries are intentionally excluded from scalar accessors in this scaffold pass.
  // - TODO(parity): Add non-scalar extensible-group APIs for per-run suffix management in a future pass.

 protected:
  using ImplType = detail::ParametricFileNameSuffix_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ParametricFileNameSuffix(std::shared_ptr<detail::ParametricFileNameSuffix_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
