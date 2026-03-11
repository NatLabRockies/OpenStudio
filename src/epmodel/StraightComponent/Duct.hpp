/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DUCT_HPP
#define EPMODEL_DUCT_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class Duct_Impl;
}

class EPMODEL_API Duct : public StraightComponent
{
 public:
  explicit Duct(const Model& model);

  virtual ~Duct() override = default;
  Duct(const Duct& other) = default;
  Duct(Duct&& other) = default;
  Duct& operator=(const Duct&) = default;
  Duct& operator=(Duct&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::Duct API shape; counterpart class has no Duct-specific scalar accessors.
  // - Field Mapping: EnergyPlus Duct fields are Inlet Node Name / Outlet Node Name and are relationship-like node links, excluded from scalar pass.
  // - ForwardTranslator evidence: ForwardTranslateDuct.cpp maps inletModelObject()/outletModelObject() to Duct Inlet/Outlet Node Name.
  // - TODO(parity): Add relationship/node-link APIs in a dedicated relationship pass without changing preserved API names/signatures.

 protected:
  using ImplType = detail::Duct_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit Duct(std::shared_ptr<detail::Duct_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
