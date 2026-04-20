/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FLUIDPROPERTIESCONCENTRATION_HPP
#define EPMODEL_FLUIDPROPERTIESCONCENTRATION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class FluidPropertiesConcentration_Impl;
  }

  class EPMODEL_API FluidPropertiesConcentration : public ModelObject
  {
   public:
    explicit FluidPropertiesConcentration(const Model& model);

    virtual ~FluidPropertiesConcentration() override = default;
    FluidPropertiesConcentration(const FluidPropertiesConcentration& other) = default;
    FluidPropertiesConcentration(FluidPropertiesConcentration&& other) = default;
    FluidPropertiesConcentration& operator=(const FluidPropertiesConcentration&) = default;
    FluidPropertiesConcentration& operator=(FluidPropertiesConcentration&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> fluidPropertyTypeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
    // - Field Mapping: fluidPropertyType and concentration map directly to EnergyPlus
    //   FluidProperties:Concentration scalar fields.
    // - Field Mapping: Fluid Name and Temperature Values Name are object-list relationship
    //   fields and are intentionally excluded from scalar accessors.
    // - Field Mapping: Extensible Property Value entries are excluded from scalar accessors.
    // - TODO(parity): Add relationship/extensible APIs after scalar saturation.

    // Fluid property type accessors
    boost::optional<std::string> fluidPropertyType() const;
    bool setFluidPropertyType(const std::string& fluidPropertyType);
    void resetFluidPropertyType();

    // Concentration accessors
    boost::optional<double> concentration() const;
    bool setConcentration(double concentration);
    void resetConcentration();

   protected:
    using ImplType = detail::FluidPropertiesConcentration_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit FluidPropertiesConcentration(std::shared_ptr<detail::FluidPropertiesConcentration_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
