/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "DesignSpecificationOutdoorAir.hpp"
#include "DesignSpecificationOutdoorAir_Impl.hpp"

#include "Model.hpp"
#include "ModelObject.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/DesignSpecification_OutdoorAir_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idf/IdfObject_Impl.hpp>

namespace openstudio {
namespace epmodel {

  DesignSpecificationOutdoorAir::DesignSpecificationOutdoorAir(const Model& model)
    : ModelObject(DesignSpecificationOutdoorAir::iddObjectType(), model) {}

  DesignSpecificationOutdoorAir::DesignSpecificationOutdoorAir(std::shared_ptr<detail::DesignSpecificationOutdoorAir_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType DesignSpecificationOutdoorAir::iddObjectType() {
    return IddObjectType::DesignSpecification_OutdoorAir;
  }

  std::vector<std::string> DesignSpecificationOutdoorAir::outdoorAirMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirMethod);
  }

  std::vector<std::string> DesignSpecificationOutdoorAir::validOutdoorAirMethodValues() {
    return outdoorAirMethodValues();
  }

  std::string DesignSpecificationOutdoorAir::outdoorAirMethod() const {
    return getImpl<detail::DesignSpecificationOutdoorAir_Impl>()->outdoorAirMethod();
  }

  bool DesignSpecificationOutdoorAir::isOutdoorAirMethodDefaulted() const {
    return getImpl<detail::DesignSpecificationOutdoorAir_Impl>()->isOutdoorAirMethodDefaulted();
  }

  bool DesignSpecificationOutdoorAir::setOutdoorAirMethod(const std::string& value) {
    return getImpl<detail::DesignSpecificationOutdoorAir_Impl>()->setOutdoorAirMethod(value);
  }

  void DesignSpecificationOutdoorAir::resetOutdoorAirMethod() {
    getImpl<detail::DesignSpecificationOutdoorAir_Impl>()->resetOutdoorAirMethod();
  }

  double DesignSpecificationOutdoorAir::outdoorAirFlowperPerson() const {
    return getImpl<detail::DesignSpecificationOutdoorAir_Impl>()->outdoorAirFlowperPerson();
  }

  bool DesignSpecificationOutdoorAir::isOutdoorAirFlowperPersonDefaulted() const {
    return getImpl<detail::DesignSpecificationOutdoorAir_Impl>()->isOutdoorAirFlowperPersonDefaulted();
  }

  bool DesignSpecificationOutdoorAir::setOutdoorAirFlowperPerson(double value) {
    return getImpl<detail::DesignSpecificationOutdoorAir_Impl>()->setOutdoorAirFlowperPerson(value);
  }

  void DesignSpecificationOutdoorAir::resetOutdoorAirFlowperPerson() {
    getImpl<detail::DesignSpecificationOutdoorAir_Impl>()->resetOutdoorAirFlowperPerson();
  }

  double DesignSpecificationOutdoorAir::outdoorAirFlowperFloorArea() const {
    return getImpl<detail::DesignSpecificationOutdoorAir_Impl>()->outdoorAirFlowperFloorArea();
  }

  bool DesignSpecificationOutdoorAir::isOutdoorAirFlowperFloorAreaDefaulted() const {
    return getImpl<detail::DesignSpecificationOutdoorAir_Impl>()->isOutdoorAirFlowperFloorAreaDefaulted();
  }

  bool DesignSpecificationOutdoorAir::setOutdoorAirFlowperFloorArea(double value) {
    return getImpl<detail::DesignSpecificationOutdoorAir_Impl>()->setOutdoorAirFlowperFloorArea(value);
  }

  void DesignSpecificationOutdoorAir::resetOutdoorAirFlowperFloorArea() {
    getImpl<detail::DesignSpecificationOutdoorAir_Impl>()->resetOutdoorAirFlowperFloorArea();
  }

  double DesignSpecificationOutdoorAir::outdoorAirFlowRate() const {
    return getImpl<detail::DesignSpecificationOutdoorAir_Impl>()->outdoorAirFlowRate();
  }

  bool DesignSpecificationOutdoorAir::isOutdoorAirFlowRateDefaulted() const {
    return getImpl<detail::DesignSpecificationOutdoorAir_Impl>()->isOutdoorAirFlowRateDefaulted();
  }

  bool DesignSpecificationOutdoorAir::setOutdoorAirFlowRate(double value) {
    return getImpl<detail::DesignSpecificationOutdoorAir_Impl>()->setOutdoorAirFlowRate(value);
  }

  void DesignSpecificationOutdoorAir::resetOutdoorAirFlowRate() {
    getImpl<detail::DesignSpecificationOutdoorAir_Impl>()->resetOutdoorAirFlowRate();
  }

  double DesignSpecificationOutdoorAir::outdoorAirFlowAirChangesperHour() const {
    return getImpl<detail::DesignSpecificationOutdoorAir_Impl>()->outdoorAirFlowAirChangesperHour();
  }

  bool DesignSpecificationOutdoorAir::isOutdoorAirFlowAirChangesperHourDefaulted() const {
    return getImpl<detail::DesignSpecificationOutdoorAir_Impl>()->isOutdoorAirFlowAirChangesperHourDefaulted();
  }

  bool DesignSpecificationOutdoorAir::setOutdoorAirFlowAirChangesperHour(double value) {
    return getImpl<detail::DesignSpecificationOutdoorAir_Impl>()->setOutdoorAirFlowAirChangesperHour(value);
  }

  void DesignSpecificationOutdoorAir::resetOutdoorAirFlowAirChangesperHour() {
    getImpl<detail::DesignSpecificationOutdoorAir_Impl>()->resetOutdoorAirFlowAirChangesperHour();
  }

  boost::optional<Schedule> DesignSpecificationOutdoorAir::outdoorAirFlowRateFractionSchedule() const {
    return getImpl<detail::DesignSpecificationOutdoorAir_Impl>()->outdoorAirFlowRateFractionSchedule();
  }

  bool DesignSpecificationOutdoorAir::setOutdoorAirFlowRateFractionSchedule(Schedule& schedule) {
    return getImpl<detail::DesignSpecificationOutdoorAir_Impl>()->setOutdoorAirFlowRateFractionSchedule(schedule);
  }

  void DesignSpecificationOutdoorAir::resetOutdoorAirFlowRateFractionSchedule() {
    getImpl<detail::DesignSpecificationOutdoorAir_Impl>()->resetOutdoorAirFlowRateFractionSchedule();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string DesignSpecificationOutdoorAir_Impl::outdoorAirMethod() const {
      if (auto value = getString(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirMethod, false)) {
        if (!value->empty()) {
          return *value;
        }
      }
      return "Sum";
    }

    bool DesignSpecificationOutdoorAir_Impl::isOutdoorAirMethodDefaulted() const {
      return isEmpty(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirMethod);
    }

    bool DesignSpecificationOutdoorAir_Impl::setOutdoorAirMethod(const std::string& value) {
      return setString(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirMethod, value);
    }

    void DesignSpecificationOutdoorAir_Impl::resetOutdoorAirMethod() {
      OS_ASSERT(setString(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirMethod, ""));
    }

    double DesignSpecificationOutdoorAir_Impl::outdoorAirFlowperPerson() const {
      if (auto value = getDouble(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirFlowperPerson, false)) {
        return *value;
      }
      return 0.0;
    }

    bool DesignSpecificationOutdoorAir_Impl::isOutdoorAirFlowperPersonDefaulted() const {
      return isEmpty(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirFlowperPerson);
    }

    bool DesignSpecificationOutdoorAir_Impl::setOutdoorAirFlowperPerson(double value) {
      return setDouble(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirFlowperPerson, value);
    }

    void DesignSpecificationOutdoorAir_Impl::resetOutdoorAirFlowperPerson() {
      OS_ASSERT(setString(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirFlowperPerson, ""));
    }

    double DesignSpecificationOutdoorAir_Impl::outdoorAirFlowperFloorArea() const {
      if (auto value = getDouble(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirFlowperZoneFloorArea, false)) {
        return *value;
      }
      return 0.0;
    }

    bool DesignSpecificationOutdoorAir_Impl::isOutdoorAirFlowperFloorAreaDefaulted() const {
      return isEmpty(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirFlowperZoneFloorArea);
    }

    bool DesignSpecificationOutdoorAir_Impl::setOutdoorAirFlowperFloorArea(double value) {
      return setDouble(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirFlowperZoneFloorArea, value);
    }

    void DesignSpecificationOutdoorAir_Impl::resetOutdoorAirFlowperFloorArea() {
      OS_ASSERT(setString(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirFlowperZoneFloorArea, ""));
    }

    double DesignSpecificationOutdoorAir_Impl::outdoorAirFlowRate() const {
      if (auto value = getDouble(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirFlowperZone, false)) {
        return *value;
      }
      return 0.0;
    }

    bool DesignSpecificationOutdoorAir_Impl::isOutdoorAirFlowRateDefaulted() const {
      return isEmpty(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirFlowperZone);
    }

    bool DesignSpecificationOutdoorAir_Impl::setOutdoorAirFlowRate(double value) {
      return setDouble(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirFlowperZone, value);
    }

    void DesignSpecificationOutdoorAir_Impl::resetOutdoorAirFlowRate() {
      OS_ASSERT(setString(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirFlowperZone, ""));
    }

    double DesignSpecificationOutdoorAir_Impl::outdoorAirFlowAirChangesperHour() const {
      if (auto value = getDouble(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirFlowAirChangesperHour, false)) {
        return *value;
      }
      return 0.0;
    }

    bool DesignSpecificationOutdoorAir_Impl::isOutdoorAirFlowAirChangesperHourDefaulted() const {
      return isEmpty(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirFlowAirChangesperHour);
    }

    bool DesignSpecificationOutdoorAir_Impl::setOutdoorAirFlowAirChangesperHour(double value) {
      return setDouble(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirFlowAirChangesperHour, value);
    }

    void DesignSpecificationOutdoorAir_Impl::resetOutdoorAirFlowAirChangesperHour() {
      OS_ASSERT(setString(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirFlowAirChangesperHour, ""));
    }

    boost::optional<Schedule> DesignSpecificationOutdoorAir_Impl::outdoorAirFlowRateFractionSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirScheduleName);
    }

    bool DesignSpecificationOutdoorAir_Impl::setOutdoorAirFlowRateFractionSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirScheduleName, "DesignSpecificationOutdoorAir",
                                           "Outdoor Air Flow Rate", schedule);
    }

    void DesignSpecificationOutdoorAir_Impl::resetOutdoorAirFlowRateFractionSchedule() {
      constexpr auto field = openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirScheduleName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    void DesignSpecificationOutdoorAir_Impl::doCanonicalize(LoadContext& context) {
      auto dsoa = getObject<openstudio::epmodel::DesignSpecificationOutdoorAir>();
      constexpr auto scheduleField = openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirScheduleName;
      const auto rawScheduleName = openstudio::detail::IdfObject_Impl::getString(scheduleField, false, true);
      if (rawScheduleName && !rawScheduleName->empty()) {
        boost::optional<Schedule> rawSchedule;
        bool ambiguous = false;
        for (const auto& candidate : model().getObjectsByName(*rawScheduleName, true)) {
          if (auto schedule = candidate.optionalCast<Schedule>()) {
            if (rawSchedule) {
              ambiguous = true;
              break;
            }
            rawSchedule = *schedule;
          }
        }

        if (rawSchedule && !ambiguous) {
          OS_ASSERT(setPointer(scheduleField, rawSchedule->handle(), false));
          detail::addLoadInfo(context, "Reattached schedule '" + rawSchedule->nameString() + "' to DesignSpecification:OutdoorAir '"
                                         + dsoa.nameString() + "'.");
        } else {
          detail::addLoadWarning(context, "Preserved unresolved or ambiguous outdoor air schedule reference '" + *rawScheduleName
                                            + "' on DesignSpecification:OutdoorAir '" + dsoa.nameString() + "'.");
        }
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
