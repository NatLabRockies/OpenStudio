/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_METERCUSTOM_HPP
#define EPMODEL_METERCUSTOM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class MeterCustom_Impl;
}

class EPMODEL_API MeterCustom : public ModelObject
{
 public:
  explicit MeterCustom(const Model& model);

  virtual ~MeterCustom() override = default;
  MeterCustom(const MeterCustom& other) = default;
  MeterCustom(MeterCustom&& other) = default;
  MeterCustom& operator=(const MeterCustom&) = default;
  MeterCustom& operator=(MeterCustom&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> fuelTypeValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::MeterCustom scalar accessor naming/signatures for counterpart parity.
  // - Field Mapping: API fuelType maps to EnergyPlus Meter:Custom field Resource Type.
  // - Field Mapping: Extensible Key Name / Output Variable or Meter Name pairs are relationship-like and excluded from scalar scope.
  // - ForwardTranslator evidence: ForwardTranslateMeterCustom.cpp writes modelObject.fuelType() to Meter_CustomFields::ResourceType.
  // - TODO(parity): Add non-scalar extensible key/variable group APIs without changing these scalar signatures.
  boost::optional<std::string> fuelType() const;
  bool setFuelType(const std::string& fuelType);
  void resetFuelType();

 protected:
  using ImplType = detail::MeterCustom_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit MeterCustom(std::shared_ptr<detail::MeterCustom_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
