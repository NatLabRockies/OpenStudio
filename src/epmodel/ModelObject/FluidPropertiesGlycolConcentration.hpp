/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FLUIDPROPERTIESGLYCOLCONCENTRATION_HPP
#define EPMODEL_FLUIDPROPERTIESGLYCOLCONCENTRATION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class FluidPropertiesGlycolConcentration_Impl;
}

class EPMODEL_API FluidPropertiesGlycolConcentration : public ModelObject
{
 public:
  explicit FluidPropertiesGlycolConcentration(const Model& model);

  virtual ~FluidPropertiesGlycolConcentration() override = default;
  FluidPropertiesGlycolConcentration(const FluidPropertiesGlycolConcentration& other) = default;
  FluidPropertiesGlycolConcentration(FluidPropertiesGlycolConcentration&& other) = default;
  FluidPropertiesGlycolConcentration& operator=(const FluidPropertiesGlycolConcentration&) = default;
  FluidPropertiesGlycolConcentration& operator=(FluidPropertiesGlycolConcentration&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> glycolTypeValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: glycolType and glycolConcentration map directly to EnergyPlus
  //   FluidProperties:GlycolConcentration scalar fields.
  // - Field Mapping: Name remains available through base ModelObject scalar API.
  // - Field Mapping: User Defined Glycol Name is an object-list relationship field
  //   and is intentionally excluded from scalar accessors.
  // - TODO(parity): Add relationship APIs after scalar saturation.
  std::string glycolType() const;
  bool setGlycolType(const std::string& glycolType);

  boost::optional<double> glycolConcentration() const;
  bool setGlycolConcentration(double glycolConcentration);
  void resetGlycolConcentration();

 protected:
  using ImplType = detail::FluidPropertiesGlycolConcentration_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit FluidPropertiesGlycolConcentration(std::shared_ptr<detail::FluidPropertiesGlycolConcentration_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
