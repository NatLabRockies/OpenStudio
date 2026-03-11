/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MATERIALPROPERTYVARIABLEABSORPTANCE_HPP
#define EPMODEL_MATERIALPROPERTYVARIABLEABSORPTANCE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class MaterialPropertyVariableAbsorptance_Impl;
}

/** MaterialPropertyVariableAbsorptance is a ModelObject that wraps the EnergyPlus IDD object
 * 'MaterialProperty:VariableAbsorptance'. */
class EPMODEL_API MaterialPropertyVariableAbsorptance : public ModelObject
{
 public:
  explicit MaterialPropertyVariableAbsorptance(const Model& model);

  virtual ~MaterialPropertyVariableAbsorptance() override = default;
  MaterialPropertyVariableAbsorptance(const MaterialPropertyVariableAbsorptance& other) = default;
  MaterialPropertyVariableAbsorptance(MaterialPropertyVariableAbsorptance&& other) = default;
  MaterialPropertyVariableAbsorptance& operator=(const MaterialPropertyVariableAbsorptance&) = default;
  MaterialPropertyVariableAbsorptance& operator=(MaterialPropertyVariableAbsorptance&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> controlSignalValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived scalar accessor names.
  // - Field Mapping: Scalar APIs map directly to EnergyPlus MaterialProperty:VariableAbsorptance fields.
  // - Field Mapping: Name is available through the base ModelObject scalar API.
  // - Field Mapping: Reference Material Name is an object-list relationship and is excluded from scalar accessors.
  // - TODO(parity): Add relationship APIs for the excluded object-list field in a dedicated relationship pass.
  std::string controlSignal() const;
  bool isControlSignalDefaulted() const;
  bool setControlSignal(const std::string& controlSignal);
  void resetControlSignal();

  boost::optional<std::string> thermalAbsorptanceFunctionName() const;
  bool setThermalAbsorptanceFunctionName(const std::string& thermalAbsorptanceFunctionName);
  void resetThermalAbsorptanceFunctionName();

  boost::optional<std::string> thermalAbsorptanceScheduleName() const;
  bool setThermalAbsorptanceScheduleName(const std::string& thermalAbsorptanceScheduleName);
  void resetThermalAbsorptanceScheduleName();

  boost::optional<std::string> solarAbsorptanceFunctionName() const;
  bool setSolarAbsorptanceFunctionName(const std::string& solarAbsorptanceFunctionName);
  void resetSolarAbsorptanceFunctionName();

  boost::optional<std::string> solarAbsorptanceScheduleName() const;
  bool setSolarAbsorptanceScheduleName(const std::string& solarAbsorptanceScheduleName);
  void resetSolarAbsorptanceScheduleName();

 protected:
  using ImplType = detail::MaterialPropertyVariableAbsorptance_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit MaterialPropertyVariableAbsorptance(std::shared_ptr<detail::MaterialPropertyVariableAbsorptance_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
