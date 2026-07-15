/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERBASEMENTXFACE_HPP
#define EPMODEL_GROUNDHEATTRANSFERBASEMENTXFACE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GroundHeatTransferBasementXFACE_Impl;
  }

  class EPMODEL_API GroundHeatTransferBasementXFACE : public ModelObject
  {
   public:
    explicit GroundHeatTransferBasementXFACE(const Model& model);

    virtual ~GroundHeatTransferBasementXFACE() override = default;
    GroundHeatTransferBasementXFACE(const GroundHeatTransferBasementXFACE& other) = default;
    GroundHeatTransferBasementXFACE(GroundHeatTransferBasementXFACE&& other) = default;
    GroundHeatTransferBasementXFACE& operator=(const GroundHeatTransferBasementXFACE&) = default;
    GroundHeatTransferBasementXFACE& operator=(GroundHeatTransferBasementXFACE&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class naming.
    // - Field Mapping: GroundHeatTransfer:Basement:XFACE N1..N44 entries are currently unnamed in generated IDD metadata, so no typed scalar accessors are emitted.
    // - TODO(parity): Add typed scalar APIs when XFACE field metadata is exposed in generated field-enum artifacts.

   protected:
    using ImplType = detail::GroundHeatTransferBasementXFACE_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GroundHeatTransferBasementXFACE(std::shared_ptr<detail::GroundHeatTransferBasementXFACE_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
