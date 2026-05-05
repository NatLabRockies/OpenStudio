/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERSLABZFACE_HPP
#define EPMODEL_GROUNDHEATTRANSFERSLABZFACE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GroundHeatTransferSlabZFACE_Impl;
  }

  class EPMODEL_API GroundHeatTransferSlabZFACE : public ModelObject
  {
   public:
    explicit GroundHeatTransferSlabZFACE(const Model& model);

    virtual ~GroundHeatTransferSlabZFACE() override = default;
    GroundHeatTransferSlabZFACE(const GroundHeatTransferSlabZFACE& other) = default;
    GroundHeatTransferSlabZFACE(GroundHeatTransferSlabZFACE&& other) = default;
    GroundHeatTransferSlabZFACE& operator=(const GroundHeatTransferSlabZFACE&) = default;
    GroundHeatTransferSlabZFACE& operator=(GroundHeatTransferSlabZFACE&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class naming.
    // - Field Mapping: GroundHeatTransfer:Slab:ZFACE N1..N25 entries are currently unnamed in generated IDD metadata, so no typed scalar accessors are emitted.
    // - TODO(parity): Add typed scalar APIs when ZFACE field metadata is exposed in generated field-enum artifacts.

   protected:
    using ImplType = detail::GroundHeatTransferSlabZFACE_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GroundHeatTransferSlabZFACE(std::shared_ptr<detail::GroundHeatTransferSlabZFACE_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
