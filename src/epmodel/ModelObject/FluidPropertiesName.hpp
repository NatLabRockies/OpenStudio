/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FLUIDPROPERTIESNAME_HPP
#define EPMODEL_FLUIDPROPERTIESNAME_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class FluidPropertiesName_Impl;
  }

  class EPMODEL_API FluidPropertiesName : public ModelObject
  {
   public:
    explicit FluidPropertiesName(const Model& model);

    virtual ~FluidPropertiesName() override = default;
    FluidPropertiesName(const FluidPropertiesName& other) = default;
    FluidPropertiesName(FluidPropertiesName&& other) = default;
    FluidPropertiesName& operator=(const FluidPropertiesName&) = default;
    FluidPropertiesName& operator=(FluidPropertiesName&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> fluidTypeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
    // - Field Mapping: fluidName and fluidType map directly to EnergyPlus FluidProperties:Name scalar fields.
    // - ForwardTranslator evidence: ForwardTranslator::createFluidProperties writes FluidProperties_NameFields::FluidName and
    //   FluidProperties_NameFields::FluidType directly, including "Glycol" for glycol-backed generated fluids.
    // - TODO(parity): Add helper APIs for translator-managed fluid datasets if needed after scalar saturation.
    std::string fluidName() const;
    bool setFluidName(const std::string& fluidName);

    std::string fluidType() const;
    bool setFluidType(const std::string& fluidType);

   protected:
    using ImplType = detail::FluidPropertiesName_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit FluidPropertiesName(std::shared_ptr<detail::FluidPropertiesName_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
