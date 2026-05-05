/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FLUIDPROPERTIESTEMPERATURES_HPP
#define EPMODEL_FLUIDPROPERTIESTEMPERATURES_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class FluidPropertiesTemperatures_Impl;
  }

  class EPMODEL_API FluidPropertiesTemperatures : public ModelObject
  {
   public:
    explicit FluidPropertiesTemperatures(const Model& model);

    virtual ~FluidPropertiesTemperatures() override = default;
    FluidPropertiesTemperatures(const FluidPropertiesTemperatures& other) = default;
    FluidPropertiesTemperatures(FluidPropertiesTemperatures&& other) = default;
    FluidPropertiesTemperatures& operator=(const FluidPropertiesTemperatures&) = default;
    FluidPropertiesTemperatures& operator=(FluidPropertiesTemperatures&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
    // - Field Mapping: Name is provided by base ModelObject name APIs and is intentionally excluded.
    // - Field Mapping: Temperature values are extensible-only and intentionally excluded from
    //   simple scalar accessors in this scaffold cycle.
    // - TODO(parity): Add extensible list APIs for Temperature entries after scalar saturation.

   protected:
    using ImplType = detail::FluidPropertiesTemperatures_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit FluidPropertiesTemperatures(std::shared_ptr<detail::FluidPropertiesTemperatures_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
