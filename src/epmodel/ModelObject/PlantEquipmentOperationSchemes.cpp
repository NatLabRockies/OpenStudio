/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "ModelObject/PlantEquipmentOperationSchemes.hpp"
#include "ModelObject/PlantEquipmentOperationSchemes_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/PlantEquipmentOperationSchemes_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  PlantEquipmentOperationSchemes::PlantEquipmentOperationSchemes(const Model& model)
    : ModelObject(PlantEquipmentOperationSchemes::iddObjectType(), model) {}

  PlantEquipmentOperationSchemes::PlantEquipmentOperationSchemes(std::shared_ptr<detail::PlantEquipmentOperationSchemes_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType PlantEquipmentOperationSchemes::iddObjectType() {
    return IddObjectType::PlantEquipmentOperationSchemes;
  }

  std::vector<std::string> PlantEquipmentOperationSchemes::controlSchemeObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PlantEquipmentOperationSchemesExtensibleFields::ControlSchemeObjectType);
  }

  std::string PlantEquipmentOperationSchemes::controlScheme1ObjectType() const {
    return getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->controlScheme1ObjectType();
  }

  bool PlantEquipmentOperationSchemes::setControlScheme1ObjectType(const std::string& controlScheme1ObjectType) {
    return getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->setControlScheme1ObjectType(controlScheme1ObjectType);
  }

  boost::optional<std::string> PlantEquipmentOperationSchemes::controlScheme2ObjectType() const {
    return getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->controlScheme2ObjectType();
  }

  bool PlantEquipmentOperationSchemes::setControlScheme2ObjectType(const std::string& controlScheme2ObjectType) {
    return getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->setControlScheme2ObjectType(controlScheme2ObjectType);
  }

  void PlantEquipmentOperationSchemes::resetControlScheme2ObjectType() {
    getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->resetControlScheme2ObjectType();
  }

  boost::optional<std::string> PlantEquipmentOperationSchemes::controlScheme3ObjectType() const {
    return getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->controlScheme3ObjectType();
  }

  bool PlantEquipmentOperationSchemes::setControlScheme3ObjectType(const std::string& controlScheme3ObjectType) {
    return getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->setControlScheme3ObjectType(controlScheme3ObjectType);
  }

  void PlantEquipmentOperationSchemes::resetControlScheme3ObjectType() {
    getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->resetControlScheme3ObjectType();
  }

  boost::optional<std::string> PlantEquipmentOperationSchemes::controlScheme4ObjectType() const {
    return getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->controlScheme4ObjectType();
  }

  bool PlantEquipmentOperationSchemes::setControlScheme4ObjectType(const std::string& controlScheme4ObjectType) {
    return getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->setControlScheme4ObjectType(controlScheme4ObjectType);
  }

  void PlantEquipmentOperationSchemes::resetControlScheme4ObjectType() {
    getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->resetControlScheme4ObjectType();
  }

  boost::optional<std::string> PlantEquipmentOperationSchemes::controlScheme5ObjectType() const {
    return getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->controlScheme5ObjectType();
  }

  bool PlantEquipmentOperationSchemes::setControlScheme5ObjectType(const std::string& controlScheme5ObjectType) {
    return getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->setControlScheme5ObjectType(controlScheme5ObjectType);
  }

  void PlantEquipmentOperationSchemes::resetControlScheme5ObjectType() {
    getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->resetControlScheme5ObjectType();
  }

  boost::optional<std::string> PlantEquipmentOperationSchemes::controlScheme6ObjectType() const {
    return getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->controlScheme6ObjectType();
  }

  bool PlantEquipmentOperationSchemes::setControlScheme6ObjectType(const std::string& controlScheme6ObjectType) {
    return getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->setControlScheme6ObjectType(controlScheme6ObjectType);
  }

  void PlantEquipmentOperationSchemes::resetControlScheme6ObjectType() {
    getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->resetControlScheme6ObjectType();
  }

  boost::optional<std::string> PlantEquipmentOperationSchemes::controlScheme7ObjectType() const {
    return getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->controlScheme7ObjectType();
  }

  bool PlantEquipmentOperationSchemes::setControlScheme7ObjectType(const std::string& controlScheme7ObjectType) {
    return getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->setControlScheme7ObjectType(controlScheme7ObjectType);
  }

  void PlantEquipmentOperationSchemes::resetControlScheme7ObjectType() {
    getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->resetControlScheme7ObjectType();
  }

  boost::optional<std::string> PlantEquipmentOperationSchemes::controlScheme8ObjectType() const {
    return getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->controlScheme8ObjectType();
  }

  bool PlantEquipmentOperationSchemes::setControlScheme8ObjectType(const std::string& controlScheme8ObjectType) {
    return getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->setControlScheme8ObjectType(controlScheme8ObjectType);
  }

  void PlantEquipmentOperationSchemes::resetControlScheme8ObjectType() {
    getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->resetControlScheme8ObjectType();
  }

}  // namespace epmodel
}  // namespace openstudio
