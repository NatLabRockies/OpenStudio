/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERSLABXFACE_HPP
#define EPMODEL_GROUNDHEATTRANSFERSLABXFACE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class GroundHeatTransferSlabXFACE_Impl;
}

class EPMODEL_API GroundHeatTransferSlabXFACE : public ModelObject
{
 public:
  explicit GroundHeatTransferSlabXFACE(const Model& model);

  virtual ~GroundHeatTransferSlabXFACE() override = default;
  GroundHeatTransferSlabXFACE(const GroundHeatTransferSlabXFACE& other) = default;
  GroundHeatTransferSlabXFACE(GroundHeatTransferSlabXFACE&& other) = default;
  GroundHeatTransferSlabXFACE& operator=(const GroundHeatTransferSlabXFACE&) = default;
  GroundHeatTransferSlabXFACE& operator=(GroundHeatTransferSlabXFACE&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class naming.
  // - Field Mapping: GroundHeatTransfer:Slab:XFACE N1..N35 entries are currently unnamed in generated IDD metadata, so no typed scalar accessors are emitted.
  // - TODO(parity): Add typed scalar APIs when XFACE field metadata is exposed in generated field-enum artifacts.

 protected:
  using ImplType = detail::GroundHeatTransferSlabXFACE_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit GroundHeatTransferSlabXFACE(std::shared_ptr<detail::GroundHeatTransferSlabXFACE_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
