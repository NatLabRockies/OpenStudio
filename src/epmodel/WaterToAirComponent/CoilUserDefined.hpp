/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILUSERDEFINED_HPP
#define EPMODEL_COILUSERDEFINED_HPP

#include "EPModelAPI.hpp"
#include "WaterToAirComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CoilUserDefined_Impl;
}

class EPMODEL_API CoilUserDefined : public WaterToAirComponent
{
 public:
  explicit CoilUserDefined(const Model& model);

  virtual ~CoilUserDefined() override = default;
  CoilUserDefined(const CoilUserDefined& other) = default;
  CoilUserDefined(CoilUserDefined&& other) = default;
  CoilUserDefined& operator=(const CoilUserDefined&) = default;
  CoilUserDefined& operator=(CoilUserDefined&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - Status: Scaffolded. The type exposes only the small numeric surface that is currently safe to mirror, while the canonical EMS-heavy behavior remains absent.
  // - Canonical Counterpart: openstudio::model::CoilUserDefined.
  // - Implemented Parity: `numberofAirConnections` preserves the one scalar-like field that is currently mirrored in epmodel.
  // - Documented Delta: The canonical model type also owns EMS program/calling-manager, actuator, ambient-zone, and rename behavior, none of which are exposed here yet.
  // - Field/Storage Mapping: The scalar field maps directly to the EnergyPlus `Coil:UserDefined` `Number of Air Connections` field.
  // - Evidence: `src/model/CoilUserDefined.hpp`, `src/model/CoilUserDefined.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilUserDefined.cpp`, and `src/model/test/CoilUserDefined_GTest.cpp`.
  // - Remaining Parity Work: Add the EMS companion-object APIs and rename behavior when the epmodel infrastructure for those relationships is available.
  int numberofAirConnections() const;

 protected:
  using ImplType = detail::CoilUserDefined_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CoilUserDefined(std::shared_ptr<detail::CoilUserDefined_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
