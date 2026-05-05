/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FLUIDPROPERTIESSUPERHEATED_HPP
#define EPMODEL_FLUIDPROPERTIESSUPERHEATED_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class FluidPropertiesSuperheated_Impl;
  }

  class EPMODEL_API FluidPropertiesSuperheated : public ModelObject
  {
   public:
    explicit FluidPropertiesSuperheated(const Model& model);

    virtual ~FluidPropertiesSuperheated() override = default;
    FluidPropertiesSuperheated(const FluidPropertiesSuperheated& other) = default;
    FluidPropertiesSuperheated(FluidPropertiesSuperheated&& other) = default;
    FluidPropertiesSuperheated& operator=(const FluidPropertiesSuperheated&) = default;
    FluidPropertiesSuperheated& operator=(FluidPropertiesSuperheated&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> fluidPropertyTypeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
    // - Field Mapping: fluidPropertyType and pressure map directly to EnergyPlus
    //   FluidProperties:Superheated scalar fields.
    // - Field Mapping: Fluid Name and Temperature Values Name are object-list relationship
    //   fields and are intentionally excluded from scalar accessors.
    // - Field Mapping: Extensible Property Value entries are excluded from scalar accessors.
    // - TODO(parity): Add relationship/extensible APIs after scalar saturation.
    boost::optional<std::string> fluidPropertyType() const;
    bool setFluidPropertyType(const std::string& fluidPropertyType);
    void resetFluidPropertyType();

    boost::optional<double> pressure() const;
    bool setPressure(double pressure);
    void resetPressure();

   protected:
    using ImplType = detail::FluidPropertiesSuperheated_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit FluidPropertiesSuperheated(std::shared_ptr<detail::FluidPropertiesSuperheated_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
