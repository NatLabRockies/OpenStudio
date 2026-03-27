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
  // - Status: Near Parity. The canonical type-specific surface is already minimal and remains aligned through inherited `StraightComponent` topology behavior.
  // - Canonical Counterpart: openstudio::model::Duct.
  // - Implemented Parity: The wrapper preserves the canonical API shape, with no extra type-specific scalar surface beyond inherited straight-component topology behavior.
  // - Field/Storage Mapping: EnergyPlus `Duct` stores only inlet/outlet node links, and epmodel keeps those links implicit through inherited topology helpers rather than adding new duct-local scalar APIs.
  // - Evidence: `src/model/Duct.hpp` shows the canonical type-specific surface is empty, and `src/energyplus/ForwardTranslator/ForwardTranslateDuct.cpp` maps inherited inlet/outlet topology to EnergyPlus node-name fields.
  // - Remaining Parity Work: Confirm whether any additional type-local convenience beyond inherited `StraightComponent` behavior is needed as broader relationship coverage matures.

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
