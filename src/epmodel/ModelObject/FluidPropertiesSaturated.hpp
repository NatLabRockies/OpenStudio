/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FLUIDPROPERTIESSATURATED_HPP
#define EPMODEL_FLUIDPROPERTIESSATURATED_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class FluidPropertiesSaturated_Impl;
}

class EPMODEL_API FluidPropertiesSaturated : public ModelObject
{
 public:
  explicit FluidPropertiesSaturated(const Model& model);

  virtual ~FluidPropertiesSaturated() override = default;
  FluidPropertiesSaturated(const FluidPropertiesSaturated& other) = default;
  FluidPropertiesSaturated(FluidPropertiesSaturated&& other) = default;
  FluidPropertiesSaturated& operator=(const FluidPropertiesSaturated&) = default;
  FluidPropertiesSaturated& operator=(FluidPropertiesSaturated&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> fluidPropertyTypeValues();
  static std::vector<std::string> fluidPhaseValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: fluidPropertyType and fluidPhase map directly to EnergyPlus
  //   FluidProperties:Saturated scalar choice fields.
  // - Field Mapping: Fluid Name and Temperature Values Name are object-list relationship
  //   fields and are intentionally excluded from scalar accessors.
  // - Field Mapping: Extensible Property Value entries are excluded from scalar accessors.
  // - TODO(parity): Add relationship/extensible APIs after scalar saturation.
  boost::optional<std::string> fluidPropertyType() const;
  bool setFluidPropertyType(const std::string& fluidPropertyType);
  void resetFluidPropertyType();

  boost::optional<std::string> fluidPhase() const;
  bool setFluidPhase(const std::string& fluidPhase);
  void resetFluidPhase();

 protected:
  using ImplType = detail::FluidPropertiesSaturated_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit FluidPropertiesSaturated(std::shared_ptr<detail::FluidPropertiesSaturated_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
