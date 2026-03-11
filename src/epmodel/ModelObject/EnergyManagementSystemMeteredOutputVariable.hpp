/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ENERGYMANAGEMENTSYSTEMMETEREDOUTPUTVARIABLE_HPP
#define EPMODEL_ENERGYMANAGEMENTSYSTEMMETEREDOUTPUTVARIABLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class EnergyManagementSystemMeteredOutputVariable_Impl;
}

class EPMODEL_API EnergyManagementSystemMeteredOutputVariable : public ModelObject
{
 public:
  explicit EnergyManagementSystemMeteredOutputVariable(const Model& model, const std::string& eMSVariableName);

  virtual ~EnergyManagementSystemMeteredOutputVariable() override = default;
  EnergyManagementSystemMeteredOutputVariable(const EnergyManagementSystemMeteredOutputVariable& other) = default;
  EnergyManagementSystemMeteredOutputVariable(EnergyManagementSystemMeteredOutputVariable&& other) = default;
  EnergyManagementSystemMeteredOutputVariable& operator=(const EnergyManagementSystemMeteredOutputVariable&) = default;
  EnergyManagementSystemMeteredOutputVariable& operator=(EnergyManagementSystemMeteredOutputVariable&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> updateFrequencyValues();
  static std::vector<std::string> resourceTypeValues();
  static std::vector<std::string> groupTypeValues();
  static std::vector<std::string> endUseCategoryValues();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model::EnergyManagementSystemMeteredOutputVariable scalar accessor names/signatures.
  // - Field Mapping: updateFrequency/resourceType/groupType/endUseCategory map directly to E+ EnergyManagementSystem:MeteredOutputVariable fields.
  // - Field Mapping: endUseSubcategory and units remain optional scalar string fields with reset APIs.
  // - ForwardTranslator evidence: ForwardTranslateEnergyManagementSystemMeteredOutputVariable.cpp writes these scalar fields from the same API names.
  // - TODO(parity): Add relationship-style APIs (EMS program/subroutine and object-handle variable resolution) separately without changing scalar signatures.
  std::string emsVariableName() const;
  bool setEMSVariableName(const std::string& eMSVariableName);

  std::string updateFrequency() const;
  bool setUpdateFrequency(const std::string& updateFrequency);

  std::string resourceType() const;
  bool setResourceType(const std::string& resourceType);

  std::string groupType() const;
  bool setGroupType(const std::string& groupType);

  std::string endUseCategory() const;
  bool setEndUseCategory(const std::string& endUseCategory);

  std::string endUseSubcategory() const;
  bool setEndUseSubcategory(const std::string& endUseSubcategory);
  void resetEndUseSubcategory();

  std::string units() const;
  bool setUnits(const std::string& units);
  void resetUnits();

 protected:
  using ImplType = detail::EnergyManagementSystemMeteredOutputVariable_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit EnergyManagementSystemMeteredOutputVariable(std::shared_ptr<detail::EnergyManagementSystemMeteredOutputVariable_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
