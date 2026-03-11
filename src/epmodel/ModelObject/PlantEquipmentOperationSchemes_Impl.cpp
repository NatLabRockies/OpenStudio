/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "ModelObject/PlantEquipmentOperationSchemes_Impl.hpp"

#include "ModelObject/PlantEquipmentOperationSchemes.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/PlantEquipmentOperationSchemes_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::vector<std::string> PlantEquipmentOperationSchemes_Impl::controlSchemeObjectTypeValues() const {
      return PlantEquipmentOperationSchemes::controlSchemeObjectTypeValues();
    }

    boost::optional<IdfExtensibleGroup> PlantEquipmentOperationSchemes_Impl::controlSchemeGroup(unsigned schemeIndex) const {
      if (schemeIndex < numExtensibleGroups()) {
        IdfExtensibleGroup group = getExtensibleGroup(schemeIndex);
        if (!group.empty()) {
          return group;
        }
      }
      return boost::none;
    }

    boost::optional<IdfExtensibleGroup> PlantEquipmentOperationSchemes_Impl::ensureControlSchemeGroup(unsigned schemeIndex) {
      while (numExtensibleGroups() <= schemeIndex) {
        IdfExtensibleGroup group = pushExtensibleGroup(std::vector<std::string>());
        if (group.empty()) {
          return boost::none;
        }
      }
      IdfExtensibleGroup group = getExtensibleGroup(schemeIndex);
      if (!group.empty()) {
        return group;
      }
      return boost::none;
    }

    boost::optional<std::string> PlantEquipmentOperationSchemes_Impl::controlSchemeObjectTypeField(unsigned schemeIndex) const {
      if (auto group = controlSchemeGroup(schemeIndex)) {
        if (!group->empty()) {
          return group->getString(PlantEquipmentOperationSchemesExtensibleFields::ControlSchemeObjectType);
        }
      }
      return boost::none;
    }

    std::string PlantEquipmentOperationSchemes_Impl::controlScheme1ObjectType() const {
      auto value = controlSchemeObjectTypeField(0);
      OS_ASSERT(value);
      return *value;
    }

    bool PlantEquipmentOperationSchemes_Impl::setControlScheme1ObjectType(const std::string& controlScheme1ObjectType) {
      if (auto group = ensureControlSchemeGroup(0)) {
        return group->setString(PlantEquipmentOperationSchemesExtensibleFields::ControlSchemeObjectType, controlScheme1ObjectType);
      }
      return false;
    }

    boost::optional<std::string> PlantEquipmentOperationSchemes_Impl::controlScheme2ObjectType() const {
      return controlSchemeObjectTypeField(1);
    }

    bool PlantEquipmentOperationSchemes_Impl::setControlScheme2ObjectType(const std::string& controlScheme2ObjectType) {
      if (auto group = ensureControlSchemeGroup(1)) {
        return group->setString(PlantEquipmentOperationSchemesExtensibleFields::ControlSchemeObjectType, controlScheme2ObjectType);
      }
      return false;
    }

    void PlantEquipmentOperationSchemes_Impl::resetControlScheme2ObjectType() {
      if (auto group = controlSchemeGroup(1)) {
        OS_ASSERT(group->setString(PlantEquipmentOperationSchemesExtensibleFields::ControlSchemeObjectType, ""));
      }
    }

    boost::optional<std::string> PlantEquipmentOperationSchemes_Impl::controlScheme3ObjectType() const {
      return controlSchemeObjectTypeField(2);
    }

    bool PlantEquipmentOperationSchemes_Impl::setControlScheme3ObjectType(const std::string& controlScheme3ObjectType) {
      if (auto group = ensureControlSchemeGroup(2)) {
        return group->setString(PlantEquipmentOperationSchemesExtensibleFields::ControlSchemeObjectType, controlScheme3ObjectType);
      }
      return false;
    }

    void PlantEquipmentOperationSchemes_Impl::resetControlScheme3ObjectType() {
      if (auto group = controlSchemeGroup(2)) {
        OS_ASSERT(group->setString(PlantEquipmentOperationSchemesExtensibleFields::ControlSchemeObjectType, ""));
      }
    }

    boost::optional<std::string> PlantEquipmentOperationSchemes_Impl::controlScheme4ObjectType() const {
      return controlSchemeObjectTypeField(3);
    }

    bool PlantEquipmentOperationSchemes_Impl::setControlScheme4ObjectType(const std::string& controlScheme4ObjectType) {
      if (auto group = ensureControlSchemeGroup(3)) {
        return group->setString(PlantEquipmentOperationSchemesExtensibleFields::ControlSchemeObjectType, controlScheme4ObjectType);
      }
      return false;
    }

    void PlantEquipmentOperationSchemes_Impl::resetControlScheme4ObjectType() {
      if (auto group = controlSchemeGroup(3)) {
        OS_ASSERT(group->setString(PlantEquipmentOperationSchemesExtensibleFields::ControlSchemeObjectType, ""));
      }
    }

    boost::optional<std::string> PlantEquipmentOperationSchemes_Impl::controlScheme5ObjectType() const {
      return controlSchemeObjectTypeField(4);
    }

    bool PlantEquipmentOperationSchemes_Impl::setControlScheme5ObjectType(const std::string& controlScheme5ObjectType) {
      if (auto group = ensureControlSchemeGroup(4)) {
        return group->setString(PlantEquipmentOperationSchemesExtensibleFields::ControlSchemeObjectType, controlScheme5ObjectType);
      }
      return false;
    }

    void PlantEquipmentOperationSchemes_Impl::resetControlScheme5ObjectType() {
      if (auto group = controlSchemeGroup(4)) {
        OS_ASSERT(group->setString(PlantEquipmentOperationSchemesExtensibleFields::ControlSchemeObjectType, ""));
      }
    }

    boost::optional<std::string> PlantEquipmentOperationSchemes_Impl::controlScheme6ObjectType() const {
      return controlSchemeObjectTypeField(5);
    }

    bool PlantEquipmentOperationSchemes_Impl::setControlScheme6ObjectType(const std::string& controlScheme6ObjectType) {
      if (auto group = ensureControlSchemeGroup(5)) {
        return group->setString(PlantEquipmentOperationSchemesExtensibleFields::ControlSchemeObjectType, controlScheme6ObjectType);
      }
      return false;
    }

    void PlantEquipmentOperationSchemes_Impl::resetControlScheme6ObjectType() {
      if (auto group = controlSchemeGroup(5)) {
        OS_ASSERT(group->setString(PlantEquipmentOperationSchemesExtensibleFields::ControlSchemeObjectType, ""));
      }
    }

    boost::optional<std::string> PlantEquipmentOperationSchemes_Impl::controlScheme7ObjectType() const {
      return controlSchemeObjectTypeField(6);
    }

    bool PlantEquipmentOperationSchemes_Impl::setControlScheme7ObjectType(const std::string& controlScheme7ObjectType) {
      if (auto group = ensureControlSchemeGroup(6)) {
        return group->setString(PlantEquipmentOperationSchemesExtensibleFields::ControlSchemeObjectType, controlScheme7ObjectType);
      }
      return false;
    }

    void PlantEquipmentOperationSchemes_Impl::resetControlScheme7ObjectType() {
      if (auto group = controlSchemeGroup(6)) {
        OS_ASSERT(group->setString(PlantEquipmentOperationSchemesExtensibleFields::ControlSchemeObjectType, ""));
      }
    }

    boost::optional<std::string> PlantEquipmentOperationSchemes_Impl::controlScheme8ObjectType() const {
      return controlSchemeObjectTypeField(7);
    }

    bool PlantEquipmentOperationSchemes_Impl::setControlScheme8ObjectType(const std::string& controlScheme8ObjectType) {
      if (auto group = ensureControlSchemeGroup(7)) {
        return group->setString(PlantEquipmentOperationSchemesExtensibleFields::ControlSchemeObjectType, controlScheme8ObjectType);
      }
      return false;
    }

    void PlantEquipmentOperationSchemes_Impl::resetControlScheme8ObjectType() {
      if (auto group = controlSchemeGroup(7)) {
        OS_ASSERT(group->setString(PlantEquipmentOperationSchemesExtensibleFields::ControlSchemeObjectType, ""));
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
