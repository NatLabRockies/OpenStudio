/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERSLABYFACE_HPP
#define EPMODEL_GROUNDHEATTRANSFERSLABYFACE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class GroundHeatTransferSlabYFACE_Impl;
}

class EPMODEL_API GroundHeatTransferSlabYFACE : public ModelObject
{
 public:
  explicit GroundHeatTransferSlabYFACE(const Model& model);

  virtual ~GroundHeatTransferSlabYFACE() override = default;
  GroundHeatTransferSlabYFACE(const GroundHeatTransferSlabYFACE& other) = default;
  GroundHeatTransferSlabYFACE(GroundHeatTransferSlabYFACE&& other) = default;
  GroundHeatTransferSlabYFACE& operator=(const GroundHeatTransferSlabYFACE&) = default;
  GroundHeatTransferSlabYFACE& operator=(GroundHeatTransferSlabYFACE&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class naming.
  // - Field Mapping: GroundHeatTransfer:Slab:YFACE N1..N40 entries are currently unnamed in generated IDD metadata, so no typed scalar accessors are emitted.
  // - TODO(parity): Add typed scalar APIs when YFACE field metadata is exposed in generated field-enum artifacts.

 protected:
  using ImplType = detail::GroundHeatTransferSlabYFACE_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit GroundHeatTransferSlabYFACE(std::shared_ptr<detail::GroundHeatTransferSlabYFACE_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
