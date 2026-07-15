/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERBASEMENTYFACE_HPP
#define EPMODEL_GROUNDHEATTRANSFERBASEMENTYFACE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GroundHeatTransferBasementYFACE_Impl;
  }

  class EPMODEL_API GroundHeatTransferBasementYFACE : public ModelObject
  {
   public:
    explicit GroundHeatTransferBasementYFACE(const Model& model);

    virtual ~GroundHeatTransferBasementYFACE() override = default;
    GroundHeatTransferBasementYFACE(const GroundHeatTransferBasementYFACE& other) = default;
    GroundHeatTransferBasementYFACE(GroundHeatTransferBasementYFACE&& other) = default;
    GroundHeatTransferBasementYFACE& operator=(const GroundHeatTransferBasementYFACE&) = default;
    GroundHeatTransferBasementYFACE& operator=(GroundHeatTransferBasementYFACE&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class naming.
    // - Field Mapping: GroundHeatTransfer:Basement:YFACE N1..N44 entries are currently unnamed in generated IDD metadata, so no typed scalar accessors are emitted.
    // - TODO(parity): Add typed scalar APIs when YFACE field metadata is exposed in generated field-enum artifacts.

   protected:
    using ImplType = detail::GroundHeatTransferBasementYFACE_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GroundHeatTransferBasementYFACE(std::shared_ptr<detail::GroundHeatTransferBasementYFACE_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
