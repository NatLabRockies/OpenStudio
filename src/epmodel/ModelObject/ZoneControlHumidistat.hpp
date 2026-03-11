/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONECONTROLHUMIDISTAT_HPP
#define EPMODEL_ZONECONTROLHUMIDISTAT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneControlHumidistat_Impl;
  }

  class EPMODEL_API ZoneControlHumidistat : public ModelObject
  {
   public:
    explicit ZoneControlHumidistat(const Model& model);

    virtual ~ZoneControlHumidistat() override = default;
    ZoneControlHumidistat(const ZoneControlHumidistat& other) = default;
    ZoneControlHumidistat(ZoneControlHumidistat&& other) = default;
    ZoneControlHumidistat& operator=(const ZoneControlHumidistat&) = default;
    ZoneControlHumidistat& operator=(ZoneControlHumidistat&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve the existing openstudio::model class name for this counterpart while keeping simple scalar coverage anchored to ModelObject's base name/setName API.
    // - Field Mapping: OS:ZoneControl:Humidistat humidifying/dehumidifying relative humidity setpoint schedule names remain E+ schedule references (object-list fields) and are intentionally excluded from scalar accessor generation.
    // - TODO(parity): Add richer schedule relationship helpers once relationship APIs are required beyond scalar saturation.

   protected:
    using ImplType = detail::ZoneControlHumidistat_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneControlHumidistat(std::shared_ptr<detail::ZoneControlHumidistat_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_ZONECONTROLHUMIDISTAT_HPP
