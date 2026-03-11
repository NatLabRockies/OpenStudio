/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANTLOOP_HPP
#define EPMODEL_PLANTLOOP_HPP

#include "EPModelAPI.hpp"
#include "Loop/Loop.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class PlantLoop_Impl;
}

class EPMODEL_API PlantLoop : public Loop
{
 public:
  explicit PlantLoop(const Model& model);

  virtual ~PlantLoop() override = default;
  PlantLoop(const PlantLoop& other) = default;
  PlantLoop(PlantLoop&& other) = default;
  PlantLoop& operator=(const PlantLoop&) = default;
  PlantLoop& operator=(PlantLoop&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model class naming for this model-counterpart type (PlantLoop).
  // - Field Mapping: This Connector:Mixer cycle maps Connector:Mixer linkage to PlantLoop relationship behavior,
  //   not scalar accessors.
  // - Field Mapping: Connector:Mixer Outlet Branch Name / extensible Inlet Branch Name are represented through
  //   loop topology and branch connectivity APIs (for example supplyComponents/demandComponents), and are excluded from scalar APIs.
  // - Field Mapping: Name remains available through base ModelObject scalar API.
  // - TODO(parity): Add additional PlantLoop scalar/accessor parity incrementally in dedicated PlantLoop cycles.

 protected:
  using ImplType = detail::PlantLoop_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit PlantLoop(std::shared_ptr<detail::PlantLoop_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
