/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERBASEMENTZFACE_HPP
#define EPMODEL_GROUNDHEATTRANSFERBASEMENTZFACE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GroundHeatTransferBasementZFACE_Impl;
  }

  class EPMODEL_API GroundHeatTransferBasementZFACE : public ModelObject
  {
   public:
    explicit GroundHeatTransferBasementZFACE(const Model& model);

    virtual ~GroundHeatTransferBasementZFACE() override = default;
    GroundHeatTransferBasementZFACE(const GroundHeatTransferBasementZFACE& other) = default;
    GroundHeatTransferBasementZFACE(GroundHeatTransferBasementZFACE&& other) = default;
    GroundHeatTransferBasementZFACE& operator=(const GroundHeatTransferBasementZFACE&) = default;
    GroundHeatTransferBasementZFACE& operator=(GroundHeatTransferBasementZFACE&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class naming.
    // - Field Mapping: GroundHeatTransfer:Basement:ZFACE N1..N44 entries are currently unnamed in generated IDD metadata, so no typed scalar accessors are emitted.
    // - TODO(parity): Add typed scalar APIs when ZFACE field metadata is exposed in generated field-enum artifacts.

   protected:
    using ImplType = detail::GroundHeatTransferBasementZFACE_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GroundHeatTransferBasementZFACE(std::shared_ptr<detail::GroundHeatTransferBasementZFACE_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
