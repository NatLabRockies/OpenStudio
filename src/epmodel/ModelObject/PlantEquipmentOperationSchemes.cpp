/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "ModelObject/PlantEquipmentOperationSchemes.hpp"
#include "ModelObject/PlantEquipmentOperationSchemes_Impl.hpp"

#include "Model.hpp"
#include "ModelObject.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationCoolingLoad.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationCoolingLoad_Impl.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationHeatingLoad.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationHeatingLoad_Impl.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationScheme.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationScheme_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <algorithm>
#include <map>
#include <set>
#include <string>

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/PlantEquipmentOperationSchemes_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

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
    auto iddObject = IddFactory::instance().getObject(iddObjectType()).get();
    // Extensible field enums are relative to the extensible group, but
    // getIddKeyNames expects an absolute object field index.
    auto values =
      getIddKeyNames(iddObject, iddObject.numFields() + openstudio::PlantEquipmentOperationSchemesExtensibleFields::ControlSchemeObjectType);
    // We own this IDD. If the key list is empty, the generated metadata is out
    // of sync or we are asking the wrong field, and we want that to fail
    // loudly instead of silently papering over it.
    OS_ASSERT(!values.empty());
    return values;
  }

  boost::optional<PlantEquipmentOperationHeatingLoad> PlantEquipmentOperationSchemes::plantEquipmentOperationHeatingLoad() const {
    return getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->plantEquipmentOperationHeatingLoad();
  }

  boost::optional<Schedule> PlantEquipmentOperationSchemes::plantEquipmentOperationHeatingLoadSchedule() const {
    return getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->plantEquipmentOperationHeatingLoadSchedule();
  }

  boost::optional<PlantEquipmentOperationCoolingLoad> PlantEquipmentOperationSchemes::plantEquipmentOperationCoolingLoad() const {
    return getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->plantEquipmentOperationCoolingLoad();
  }

  boost::optional<Schedule> PlantEquipmentOperationSchemes::plantEquipmentOperationCoolingLoadSchedule() const {
    return getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->plantEquipmentOperationCoolingLoadSchedule();
  }

  boost::optional<PlantEquipmentOperationScheme> PlantEquipmentOperationSchemes::primaryPlantEquipmentOperationScheme() const {
    return getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->primaryPlantEquipmentOperationScheme();
  }

  boost::optional<Schedule> PlantEquipmentOperationSchemes::primaryPlantEquipmentOperationSchemeSchedule() const {
    return getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->primaryPlantEquipmentOperationSchemeSchedule();
  }

  boost::optional<Schedule> PlantEquipmentOperationSchemes::componentSetpointOperationSchemeSchedule() const {
    return getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->componentSetpointOperationSchemeSchedule();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {
      using ExtensibleFields = openstudio::PlantEquipmentOperationSchemesExtensibleFields;
    }  // namespace

    const std::string& PlantEquipmentOperationSchemes_Impl::heatingLoadControlSchemeObjectType() {
      static const std::string value{"PlantEquipmentOperation:HeatingLoad"};
      return value;
    }

    const std::string& PlantEquipmentOperationSchemes_Impl::coolingLoadControlSchemeObjectType() {
      static const std::string value{"PlantEquipmentOperation:CoolingLoad"};
      return value;
    }

    const std::string& PlantEquipmentOperationSchemes_Impl::componentSetpointControlSchemeObjectType() {
      static const std::string value{"PlantEquipmentOperation:ComponentSetpoint"};
      return value;
    }

    const std::string& PlantEquipmentOperationSchemes_Impl::defaultPrimaryControlSchemeObjectType() {
      static const std::string value{"PlantEquipmentOperation:Uncontrolled"};
      return value;
    }

    std::vector<std::string> PlantEquipmentOperationSchemes_Impl::controlSchemeObjectTypeValues() const {
      return PlantEquipmentOperationSchemes::controlSchemeObjectTypeValues();
    }

    bool PlantEquipmentOperationSchemes_Impl::isSupportedControlSchemeType(const std::string& controlSchemeObjectType) {
      const auto supportedTypes = PlantEquipmentOperationSchemes::controlSchemeObjectTypeValues();
      return std::ranges::find(supportedTypes, controlSchemeObjectType) != supportedTypes.end();
    }

    bool PlantEquipmentOperationSchemes_Impl::isPrimaryControlSchemeType(const std::string& controlSchemeObjectType) {
      return isSupportedControlSchemeType(controlSchemeObjectType) && (controlSchemeObjectType != heatingLoadControlSchemeObjectType())
             && (controlSchemeObjectType != coolingLoadControlSchemeObjectType())
             && (controlSchemeObjectType != componentSetpointControlSchemeObjectType());
    }

    boost::optional<WorkspaceExtensibleGroup> PlantEquipmentOperationSchemes_Impl::controlSchemeGroup(unsigned schemeIndex) const {
      auto schemes = getObject<openstudio::epmodel::PlantEquipmentOperationSchemes>();
      const auto groups = schemes.extensibleGroups();
      if (schemeIndex < groups.size()) {
        return groups[schemeIndex].optionalCast<WorkspaceExtensibleGroup>();
      }
      return boost::none;
    }

    boost::optional<WorkspaceExtensibleGroup> PlantEquipmentOperationSchemes_Impl::ensureControlSchemeGroup(unsigned schemeIndex) {
      auto schemes = getObject<openstudio::epmodel::PlantEquipmentOperationSchemes>();
      while (schemes.numExtensibleGroups() <= schemeIndex) {
        IdfExtensibleGroup group = schemes.pushExtensibleGroup();
        if (group.empty()) {
          return boost::none;
        }
      }
      return controlSchemeGroup(schemeIndex);
    }

    boost::optional<std::string> PlantEquipmentOperationSchemes_Impl::controlSchemeObjectTypeField(unsigned schemeIndex) const {
      if (auto group = controlSchemeGroup(schemeIndex)) {
        return group->getString(ExtensibleFields::ControlSchemeObjectType, true);
      }
      return boost::none;
    }

    boost::optional<std::string> PlantEquipmentOperationSchemes_Impl::controlSchemeRawField(unsigned schemeIndex, unsigned fieldIndex) const {
      const auto& schemes = getObject<openstudio::epmodel::PlantEquipmentOperationSchemes>();
      const unsigned absoluteIndex = schemes.numNonextensibleFields() + (schemeIndex * schemes.iddObject().properties().numExtensible) + fieldIndex;
      return openstudio::detail::IdfObject_Impl::getField(absoluteIndex, true);
    }

    boost::optional<unsigned> PlantEquipmentOperationSchemes_Impl::controlSchemeIndex(const std::string& controlSchemeObjectType) const {
      for (unsigned schemeIndex = 0; schemeIndex < numExtensibleGroups(); ++schemeIndex) {
        const auto type = controlSchemeObjectTypeField(schemeIndex);
        if (type && (*type == controlSchemeObjectType)) {
          return schemeIndex;
        }
      }
      return boost::none;
    }

    boost::optional<unsigned> PlantEquipmentOperationSchemes_Impl::primaryControlSchemeIndex() const {
      for (unsigned schemeIndex = 0; schemeIndex < numExtensibleGroups(); ++schemeIndex) {
        const auto type = controlSchemeObjectTypeField(schemeIndex);
        if (type && isPrimaryControlSchemeType(*type)) {
          return schemeIndex;
        }
      }
      return boost::none;
    }

    bool PlantEquipmentOperationSchemes_Impl::groupHasControlScheme(unsigned schemeIndex) const {
      auto group = controlSchemeGroup(schemeIndex);
      if (!group) {
        return false;
      }
      if (group->getTarget(ExtensibleFields::ControlSchemeName)) {
        return true;
      }
      return controlSchemeRawField(schemeIndex, ExtensibleFields::ControlSchemeName).is_initialized()
             && !controlSchemeRawField(schemeIndex, ExtensibleFields::ControlSchemeName)->empty();
    }

    bool PlantEquipmentOperationSchemes_Impl::groupHasControlSchemeSchedule(unsigned schemeIndex) const {
      auto group = controlSchemeGroup(schemeIndex);
      if (!group) {
        return false;
      }
      if (group->getTarget(ExtensibleFields::ControlSchemeScheduleName)) {
        return true;
      }
      return controlSchemeRawField(schemeIndex, ExtensibleFields::ControlSchemeScheduleName).is_initialized()
             && !controlSchemeRawField(schemeIndex, ExtensibleFields::ControlSchemeScheduleName)->empty();
    }

    boost::optional<openstudio::epmodel::ModelObject> PlantEquipmentOperationSchemes_Impl::controlScheme(unsigned schemeIndex) const {
      auto group = controlSchemeGroup(schemeIndex);
      if (!group) {
        return boost::none;
      }

      auto target = group->getTarget(ExtensibleFields::ControlSchemeName);
      if (target) {
        return target->optionalCast<openstudio::epmodel::ModelObject>();
      }
      return boost::none;
    }

    boost::optional<openstudio::epmodel::ModelObject> PlantEquipmentOperationSchemes_Impl::resolveAndAttachControlScheme(unsigned schemeIndex) {
      // Canonicalization-only helper. Normal API paths should already have a
      // live pointer here or should go through the typed setters that create
      // one. This exists to repair imported rows that only have raw field text.
      if (auto scheme = controlScheme(schemeIndex)) {
        return scheme;
      }

      auto group = controlSchemeGroup(schemeIndex);
      if (!group) {
        return boost::none;
      }

      const auto type = controlSchemeObjectTypeField(schemeIndex);
      // Canonicalization needs the raw stored field text here. The workspace
      // wrapper getters only reflect live linked targets for source fields,
      // which is exactly what is missing in the imported rows we are fixing.
      const auto name = controlSchemeRawField(schemeIndex, ExtensibleFields::ControlSchemeName);
      if (!type || type->empty() || !name || name->empty()) {
        return boost::none;
      }

      // This object stores scheme relationships as extensible name/type rows.
      // During ordinary API use we rely on a live pointer. During canonicalize
      // we repair raw imported rows by finding the named object and attaching
      // the pointer so later renames stay tracked.
      for (const auto& candidate : model().getObjectsByName(*name, true, true)) {
        if (auto typedCandidate = candidate.optionalCast<openstudio::epmodel::ModelObject>()) {
          if (typedCandidate->iddObject().name() != *type) {
            continue;
          }
          if (group->setPointer(ExtensibleFields::ControlSchemeName, typedCandidate->handle(), false)) {
            return typedCandidate;
          }
        }
      }

      return boost::none;
    }

    boost::optional<openstudio::epmodel::ModelObject>
      PlantEquipmentOperationSchemes_Impl::controlScheme(const std::string& controlSchemeObjectType) const {
      const auto schemeIndex = controlSchemeIndex(controlSchemeObjectType);
      if (!schemeIndex) {
        return boost::none;
      }
      return controlScheme(*schemeIndex);
    }

    bool PlantEquipmentOperationSchemes_Impl::setControlScheme(unsigned schemeIndex, const std::string& controlSchemeObjectType,
                                                               const openstudio::epmodel::ModelObject& controlScheme) {
      if ((controlScheme.model() != model()) || !isSupportedControlSchemeType(controlSchemeObjectType)
          || (controlScheme.iddObject().name() != controlSchemeObjectType)) {
        return false;
      }

      auto group = ensureControlSchemeGroup(schemeIndex);
      if (!group) {
        return false;
      }

      if (!group->setString(ExtensibleFields::ControlSchemeObjectType, controlSchemeObjectType)) {
        return false;
      }

      if (!group->setPointer(ExtensibleFields::ControlSchemeName, controlScheme.handle(), false)) {
        if (!group->setString(ExtensibleFields::ControlSchemeName, controlScheme.nameString())) {
          return false;
        }
      }

      if (!groupHasControlSchemeSchedule(schemeIndex)) {
        auto alwaysOn = model().alwaysOnDiscreteSchedule();
        if (!setControlSchemeSchedule(schemeIndex, alwaysOn)) {
          return false;
        }
      }

      return true;
    }

    bool PlantEquipmentOperationSchemes_Impl::setControlScheme(const std::string& controlSchemeObjectType,
                                                               const openstudio::epmodel::ModelObject& controlScheme) {
      boost::optional<unsigned> schemeIndex;
      if (isPrimaryControlSchemeType(controlSchemeObjectType)) {
        schemeIndex = primaryControlSchemeIndex();
      }
      if (!schemeIndex) {
        schemeIndex = controlSchemeIndex(controlSchemeObjectType);
      }
      if (!schemeIndex) {
        schemeIndex = numExtensibleGroups();
      }
      return setControlScheme(*schemeIndex, controlSchemeObjectType, controlScheme);
    }

    bool PlantEquipmentOperationSchemes_Impl::clearControlScheme(unsigned schemeIndex) {
      auto group = controlSchemeGroup(schemeIndex);
      return group && group->setString(ExtensibleFields::ControlSchemeName, "");
    }

    void PlantEquipmentOperationSchemes_Impl::resetControlScheme(const std::string& controlSchemeObjectType) {
      const auto schemeIndex = controlSchemeIndex(controlSchemeObjectType);
      if (!schemeIndex) {
        return;
      }

      OS_ASSERT(clearControlScheme(*schemeIndex));
      eraseControlSchemeGroupIfEmpty(*schemeIndex);
    }

    boost::optional<openstudio::epmodel::Schedule> PlantEquipmentOperationSchemes_Impl::controlSchemeSchedule(unsigned schemeIndex) const {
      auto group = controlSchemeGroup(schemeIndex);
      if (!group) {
        return boost::none;
      }

      auto target = group->getTarget(ExtensibleFields::ControlSchemeScheduleName);
      if (target) {
        return target->optionalCast<openstudio::epmodel::Schedule>();
      }
      return boost::none;
    }

    boost::optional<openstudio::epmodel::Schedule> PlantEquipmentOperationSchemes_Impl::resolveAndAttachControlSchemeSchedule(unsigned schemeIndex) {
      // Canonicalization-only helper. Normal API paths should already have a
      // live pointer here or should go through the typed setters that create
      // one. This exists to repair imported rows that only have raw field text.
      if (auto schedule = controlSchemeSchedule(schemeIndex)) {
        return schedule;
      }

      auto group = ensureControlSchemeGroup(schemeIndex);
      if (!group) {
        return boost::none;
      }

      const auto name = controlSchemeRawField(schemeIndex, ExtensibleFields::ControlSchemeScheduleName);
      if (!name || name->empty()) {
        return boost::none;
      }

      for (const auto& candidate : model().getObjectsByName(*name, true, true)) {
        if (auto schedule = candidate.optionalCast<openstudio::epmodel::Schedule>()) {
          if (group->setPointer(ExtensibleFields::ControlSchemeScheduleName, schedule->handle(), false)) {
            return schedule;
          }
        }
      }

      return boost::none;
    }

    boost::optional<openstudio::epmodel::Schedule>
      PlantEquipmentOperationSchemes_Impl::controlSchemeSchedule(const std::string& controlSchemeObjectType) const {
      const auto schemeIndex = controlSchemeIndex(controlSchemeObjectType);
      if (!schemeIndex) {
        return boost::none;
      }
      return controlSchemeSchedule(*schemeIndex);
    }

    bool PlantEquipmentOperationSchemes_Impl::setControlSchemeSchedule(unsigned schemeIndex, openstudio::epmodel::Schedule& schedule) {
      if (schedule.model() != model()) {
        return false;
      }

      auto group = ensureControlSchemeGroup(schemeIndex);
      if (!group) {
        return false;
      }

      if (!group->setPointer(ExtensibleFields::ControlSchemeScheduleName, schedule.handle(), false)) {
        return group->setString(ExtensibleFields::ControlSchemeScheduleName, schedule.nameString());
      }

      return true;
    }

    bool PlantEquipmentOperationSchemes_Impl::setControlSchemeSchedule(const std::string& controlSchemeObjectType,
                                                                       openstudio::epmodel::Schedule& schedule) {
      if (!isSupportedControlSchemeType(controlSchemeObjectType)) {
        return false;
      }

      auto schemeIndex = controlSchemeIndex(controlSchemeObjectType);
      if (!schemeIndex) {
        schemeIndex = numExtensibleGroups();
        auto group = ensureControlSchemeGroup(*schemeIndex);
        if (!group || !group->setString(ExtensibleFields::ControlSchemeObjectType, controlSchemeObjectType)) {
          return false;
        }
      }

      return setControlSchemeSchedule(*schemeIndex, schedule);
    }

    bool PlantEquipmentOperationSchemes_Impl::clearControlSchemeSchedule(unsigned schemeIndex) {
      auto group = controlSchemeGroup(schemeIndex);
      return group && group->setString(ExtensibleFields::ControlSchemeScheduleName, "");
    }

    void PlantEquipmentOperationSchemes_Impl::resetControlSchemeSchedule(const std::string& controlSchemeObjectType) {
      const auto schemeIndex = controlSchemeIndex(controlSchemeObjectType);
      if (!schemeIndex) {
        return;
      }

      OS_ASSERT(clearControlSchemeSchedule(*schemeIndex));
      eraseControlSchemeGroupIfEmpty(*schemeIndex);
    }

    void PlantEquipmentOperationSchemes_Impl::eraseControlSchemeGroupIfEmpty(unsigned schemeIndex) {
      const auto type = controlSchemeObjectTypeField(schemeIndex);
      if (type && !type->empty() && (groupHasControlScheme(schemeIndex) || groupHasControlSchemeSchedule(schemeIndex))) {
        return;
      }

      getObject<openstudio::epmodel::PlantEquipmentOperationSchemes>().eraseExtensibleGroup(schemeIndex);
    }

    boost::optional<openstudio::epmodel::PlantEquipmentOperationHeatingLoad>
      PlantEquipmentOperationSchemes_Impl::plantEquipmentOperationHeatingLoad() const {
      const auto scheme = controlScheme(heatingLoadControlSchemeObjectType());
      if (scheme) {
        return scheme->optionalCast<openstudio::epmodel::PlantEquipmentOperationHeatingLoad>();
      }
      return boost::none;
    }

    bool PlantEquipmentOperationSchemes_Impl::setPlantEquipmentOperationHeatingLoad(
      const openstudio::epmodel::PlantEquipmentOperationHeatingLoad& controlScheme) {
      return setControlScheme(heatingLoadControlSchemeObjectType(), controlScheme);
    }

    void PlantEquipmentOperationSchemes_Impl::resetPlantEquipmentOperationHeatingLoad() {
      resetControlScheme(heatingLoadControlSchemeObjectType());
    }

    boost::optional<openstudio::epmodel::Schedule> PlantEquipmentOperationSchemes_Impl::plantEquipmentOperationHeatingLoadSchedule() const {
      return controlSchemeSchedule(heatingLoadControlSchemeObjectType());
    }

    bool PlantEquipmentOperationSchemes_Impl::setPlantEquipmentOperationHeatingLoadSchedule(openstudio::epmodel::Schedule& schedule) {
      return setControlSchemeSchedule(heatingLoadControlSchemeObjectType(), schedule);
    }

    void PlantEquipmentOperationSchemes_Impl::resetPlantEquipmentOperationHeatingLoadSchedule() {
      resetControlSchemeSchedule(heatingLoadControlSchemeObjectType());
    }

    boost::optional<openstudio::epmodel::PlantEquipmentOperationCoolingLoad>
      PlantEquipmentOperationSchemes_Impl::plantEquipmentOperationCoolingLoad() const {
      const auto scheme = controlScheme(coolingLoadControlSchemeObjectType());
      if (scheme) {
        return scheme->optionalCast<openstudio::epmodel::PlantEquipmentOperationCoolingLoad>();
      }
      return boost::none;
    }

    bool PlantEquipmentOperationSchemes_Impl::setPlantEquipmentOperationCoolingLoad(
      const openstudio::epmodel::PlantEquipmentOperationCoolingLoad& controlScheme) {
      return setControlScheme(coolingLoadControlSchemeObjectType(), controlScheme);
    }

    void PlantEquipmentOperationSchemes_Impl::resetPlantEquipmentOperationCoolingLoad() {
      resetControlScheme(coolingLoadControlSchemeObjectType());
    }

    boost::optional<openstudio::epmodel::Schedule> PlantEquipmentOperationSchemes_Impl::plantEquipmentOperationCoolingLoadSchedule() const {
      return controlSchemeSchedule(coolingLoadControlSchemeObjectType());
    }

    bool PlantEquipmentOperationSchemes_Impl::setPlantEquipmentOperationCoolingLoadSchedule(openstudio::epmodel::Schedule& schedule) {
      return setControlSchemeSchedule(coolingLoadControlSchemeObjectType(), schedule);
    }

    void PlantEquipmentOperationSchemes_Impl::resetPlantEquipmentOperationCoolingLoadSchedule() {
      resetControlSchemeSchedule(coolingLoadControlSchemeObjectType());
    }

    boost::optional<openstudio::epmodel::PlantEquipmentOperationScheme>
      PlantEquipmentOperationSchemes_Impl::primaryPlantEquipmentOperationScheme() const {
      const auto schemeIndex = primaryControlSchemeIndex();
      if (!schemeIndex) {
        return boost::none;
      }

      const auto scheme = controlScheme(*schemeIndex);
      if (scheme) {
        return scheme->optionalCast<openstudio::epmodel::PlantEquipmentOperationScheme>();
      }
      return boost::none;
    }

    bool PlantEquipmentOperationSchemes_Impl::setPrimaryPlantEquipmentOperationScheme(
      const openstudio::epmodel::PlantEquipmentOperationScheme& controlScheme) {
      const auto controlSchemeObjectType = controlScheme.iddObject().name();
      if (!isPrimaryControlSchemeType(controlSchemeObjectType)) {
        return false;
      }
      return setControlScheme(controlSchemeObjectType, controlScheme);
    }

    void PlantEquipmentOperationSchemes_Impl::resetPrimaryPlantEquipmentOperationScheme() {
      const auto schemeIndex = primaryControlSchemeIndex();
      if (!schemeIndex) {
        return;
      }

      OS_ASSERT(clearControlScheme(*schemeIndex));
      eraseControlSchemeGroupIfEmpty(*schemeIndex);
    }

    boost::optional<openstudio::epmodel::Schedule> PlantEquipmentOperationSchemes_Impl::primaryPlantEquipmentOperationSchemeSchedule() const {
      const auto schemeIndex = primaryControlSchemeIndex();
      if (!schemeIndex) {
        return boost::none;
      }
      return controlSchemeSchedule(*schemeIndex);
    }

    bool PlantEquipmentOperationSchemes_Impl::setPrimaryPlantEquipmentOperationSchemeSchedule(openstudio::epmodel::Schedule& schedule) {
      auto schemeIndex = primaryControlSchemeIndex();
      if (!schemeIndex) {
        schemeIndex = numExtensibleGroups();
        auto group = ensureControlSchemeGroup(*schemeIndex);
        if (!group || !group->setString(ExtensibleFields::ControlSchemeObjectType, defaultPrimaryControlSchemeObjectType())) {
          return false;
        }
      }
      return setControlSchemeSchedule(*schemeIndex, schedule);
    }

    void PlantEquipmentOperationSchemes_Impl::resetPrimaryPlantEquipmentOperationSchemeSchedule() {
      const auto schemeIndex = primaryControlSchemeIndex();
      if (!schemeIndex) {
        return;
      }

      OS_ASSERT(clearControlSchemeSchedule(*schemeIndex));
      eraseControlSchemeGroupIfEmpty(*schemeIndex);
    }

    boost::optional<openstudio::epmodel::Schedule> PlantEquipmentOperationSchemes_Impl::componentSetpointOperationSchemeSchedule() const {
      return controlSchemeSchedule(componentSetpointControlSchemeObjectType());
    }

    bool PlantEquipmentOperationSchemes_Impl::setComponentSetpointOperationSchemeSchedule(openstudio::epmodel::Schedule& schedule) {
      return setControlSchemeSchedule(componentSetpointControlSchemeObjectType(), schedule);
    }

    void PlantEquipmentOperationSchemes_Impl::resetComponentSetpointOperationSchemeSchedule() {
      resetControlSchemeSchedule(componentSetpointControlSchemeObjectType());
    }

    void PlantEquipmentOperationSchemes_Impl::doCanonicalize(LoadContext& context) {
      auto schemes = getObject<openstudio::epmodel::PlantEquipmentOperationSchemes>();
      const auto ownerName = schemes.nameString().empty() ? std::string{"PlantEquipmentOperationSchemes"} : schemes.nameString();

      // Canonical form for this object is simple:
      // - each populated control-scheme slot is represented by one extensible row
      // - the row's type string matches the referenced scheme object's actual type
      // - the row carries live pointers to the scheme and schedule when those names resolve
      // - duplicate rows for the same slot are merged instead of preserved side by side
      //
      // In practice imported data can drift away from that shape. We see rows with
      // only names and no pointers, rows with a stale type string that disagrees with
      // the referenced scheme object, and duplicate rows where one has the scheme and
      // another has the schedule. This pass repairs those cases and leaves behind the
      // smallest set of rows that still represents the intended relationships.
      std::map<std::string, unsigned> keptIndexBySlot;
      std::map<std::string, int> keptScoreBySlot;
      std::vector<unsigned> groupsToErase;
      auto mergeGroupState = [this](unsigned survivorIndex, unsigned duplicateIndex) {
        // When two rows really describe the same slot, keep one row and copy over any
        // missing relationships from the weaker row before erasing it.
        if (!groupHasControlScheme(survivorIndex)) {
          if (auto duplicateScheme = controlScheme(duplicateIndex)) {
            OS_ASSERT(setControlScheme(survivorIndex, duplicateScheme->iddObject().name(), *duplicateScheme));
          }
        }
        if (!groupHasControlSchemeSchedule(survivorIndex)) {
          if (auto duplicateSchedule = controlSchemeSchedule(duplicateIndex)) {
            OS_ASSERT(setControlSchemeSchedule(survivorIndex, *duplicateSchedule));
          }
        }
      };

      for (unsigned schemeIndex = 0; schemeIndex < numExtensibleGroups(); ++schemeIndex) {
        auto group = controlSchemeGroup(schemeIndex);
        if (!group) {
          continue;
        }

        auto type = controlSchemeObjectTypeField(schemeIndex);
        // Repair name-only imports first. These helpers read the raw stored field text,
        // find the referenced objects by name, and attach live pointers so the rest of
        // canonicalization can reason about one consistent representation.
        (void)resolveAndAttachControlSchemeSchedule(schemeIndex);
        if (auto scheme = resolveAndAttachControlScheme(schemeIndex)) {
          const auto targetType = scheme->iddObject().name();
          if (isSupportedControlSchemeType(targetType) && ((!type || type->empty()) || (*type != targetType))) {
            OS_ASSERT(group->setString(ExtensibleFields::ControlSchemeObjectType, targetType));
            detail::addLoadWarning(context, "Normalized control scheme type to '" + targetType + "' in PlantEquipmentOperationSchemes '" + ownerName
                                              + "' to match the referenced scheme object.");
            type = targetType;
          }
        }

        if ((!type || type->empty()) && !groupHasControlScheme(schemeIndex) && !groupHasControlSchemeSchedule(schemeIndex)) {
          groupsToErase.push_back(schemeIndex);
          continue;
        }

        if (!type || type->empty()) {
          groupsToErase.push_back(schemeIndex);
          detail::addLoadWarning(context, "Removed PlantEquipmentOperationSchemes entry at extensible index " + std::to_string(schemeIndex)
                                            + " from '" + ownerName + "' because it had no resolvable control scheme type.");
          continue;
        }

        if (!isSupportedControlSchemeType(*type)) {
          groupsToErase.push_back(schemeIndex);
          detail::addLoadWarning(context, "Removed PlantEquipmentOperationSchemes entry with unsupported control scheme type '" + *type + "' from '"
                                            + ownerName + "'.");
          continue;
        }

        // Heating and cooling slots are unique by their explicit type. Everything else
        // behaves like a single "primary" slot, so duplicates in that broader bucket
        // need to be merged down to one surviving row.
        const std::string slotKey = isPrimaryControlSchemeType(*type) ? std::string{"__primary__"} : *type;
        const int slotScore = (groupHasControlScheme(schemeIndex) ? 2 : 0) + (groupHasControlSchemeSchedule(schemeIndex) ? 1 : 0);
        const auto keptIndex = keptIndexBySlot.find(slotKey);
        if (keptIndex == keptIndexBySlot.end()) {
          keptIndexBySlot.emplace(slotKey, schemeIndex);
          keptScoreBySlot.emplace(slotKey, slotScore);
          continue;
        }

        if (slotScore > keptScoreBySlot.at(slotKey)) {
          mergeGroupState(schemeIndex, keptIndex->second);
          groupsToErase.push_back(keptIndex->second);
          keptIndexBySlot[slotKey] = schemeIndex;
          keptScoreBySlot[slotKey] = (groupHasControlScheme(schemeIndex) ? 2 : 0) + (groupHasControlSchemeSchedule(schemeIndex) ? 1 : 0);
          detail::addLoadWarning(context, "Removed lower-fidelity duplicate PlantEquipmentOperationSchemes entry for slot '" + slotKey + "' from '"
                                            + ownerName + "'.");
        } else {
          mergeGroupState(keptIndex->second, schemeIndex);
          groupsToErase.push_back(schemeIndex);
          detail::addLoadWarning(context,
                                 "Removed duplicate PlantEquipmentOperationSchemes entry for slot '" + slotKey + "' from '" + ownerName + "'.");
        }
      }

      std::sort(groupsToErase.begin(), groupsToErase.end());
      groupsToErase.erase(std::unique(groupsToErase.begin(), groupsToErase.end()), groupsToErase.end());
      for (auto it = groupsToErase.rbegin(); it != groupsToErase.rend(); ++it) {
        schemes.eraseExtensibleGroup(*it);
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
