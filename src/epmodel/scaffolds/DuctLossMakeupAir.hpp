/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DUCTLOSSMAKEUPAIR_HPP
#define EPMODEL_DUCTLOSSMAKEUPAIR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class DuctLossMakeupAir_Impl;
  }

  class EPMODEL_API DuctLossMakeupAir : public ModelObject
  {
   public:
    explicit DuctLossMakeupAir(const Model& model);

    virtual ~DuctLossMakeupAir() override = default;
    DuctLossMakeupAir(const DuctLossMakeupAir& other) = default;
    DuctLossMakeupAir(DuctLossMakeupAir&& other) = default;
    DuctLossMakeupAir& operator=(const DuctLossMakeupAir&) = default;
    DuctLossMakeupAir& operator=(DuctLossMakeupAir&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
    // - Field Mapping: Name remains available through base ModelObject scalar API.
    // - Field Mapping: AirLoopHVAC Name and AirflowNetwork:Distribution:Linkage Name are relationship-like object-list fields and are
    //   excluded from scalar accessors.
    // - TODO(parity): Add relationship APIs incrementally after scalar saturation.

   protected:
    using ImplType = detail::DuctLossMakeupAir_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit DuctLossMakeupAir(std::shared_ptr<detail::DuctLossMakeupAir_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
