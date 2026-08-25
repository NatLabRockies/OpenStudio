/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilHeatingGasMultiStage.hpp"
#include "StraightComponent/CoilHeatingGasMultiStage_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/Coil_Heating_Gas_MultiStage_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idf/IdfObject_Impl.hpp>

namespace openstudio {
namespace epmodel {

  CoilHeatingGasMultiStage::CoilHeatingGasMultiStage(const Model& model) : StraightComponent(CoilHeatingGasMultiStage::iddObjectType(), model) {
    auto availabilitySchedule = model.alwaysOnDiscreteSchedule();
    OS_ASSERT(getImpl<detail::CoilHeatingGasMultiStage_Impl>()->setAvailabilitySchedule(availabilitySchedule));
    OS_ASSERT(getImpl<detail::CoilHeatingGasMultiStage_Impl>()->setNumberOfStages(1u));
  }

  CoilHeatingGasMultiStage::CoilHeatingGasMultiStage(std::shared_ptr<detail::CoilHeatingGasMultiStage_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType CoilHeatingGasMultiStage::iddObjectType() {
    return IddObjectType::Coil_Heating_Gas_MultiStage;
  }

  bool CoilHeatingGasMultiStage::addToNode(Node& node) {
    return getImpl<detail::CoilHeatingGasMultiStage_Impl>()->addToNode(node);
  }

  Schedule CoilHeatingGasMultiStage::availabilitySchedule() const {
    return getImpl<detail::CoilHeatingGasMultiStage_Impl>()->availabilitySchedule();
  }

  bool CoilHeatingGasMultiStage::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::CoilHeatingGasMultiStage_Impl>()->setAvailabilitySchedule(schedule);
  }

  boost::optional<Curve> CoilHeatingGasMultiStage::partLoadFractionCorrelationCurve() const {
    return getImpl<detail::CoilHeatingGasMultiStage_Impl>()->partLoadFractionCorrelationCurve();
  }

  bool CoilHeatingGasMultiStage::setPartLoadFractionCorrelationCurve(const Curve& curve) {
    return getImpl<detail::CoilHeatingGasMultiStage_Impl>()->setPartLoadFractionCorrelationCurve(curve);
  }

  void CoilHeatingGasMultiStage::resetPartLoadFractionCorrelationCurve() {
    getImpl<detail::CoilHeatingGasMultiStage_Impl>()->resetPartLoadFractionCorrelationCurve();
  }

  boost::optional<double> CoilHeatingGasMultiStage::parasiticGasLoad() const {
    return getImpl<detail::CoilHeatingGasMultiStage_Impl>()->offCycleParasiticGasLoad();
  }

  bool CoilHeatingGasMultiStage::setParasiticGasLoad(double parasiticGasLoad) {
    return getImpl<detail::CoilHeatingGasMultiStage_Impl>()->setOffCycleParasiticGasLoad(parasiticGasLoad);
  }

  void CoilHeatingGasMultiStage::resetParasiticGasLoad() {
    getImpl<detail::CoilHeatingGasMultiStage_Impl>()->resetOffCycleParasiticGasLoad();
  }

  boost::optional<double> CoilHeatingGasMultiStage::offCycleParasiticGasLoad() const {
    return getImpl<detail::CoilHeatingGasMultiStage_Impl>()->offCycleParasiticGasLoad();
  }

  bool CoilHeatingGasMultiStage::setOffCycleParasiticGasLoad(double offCycleParasiticGasLoad) {
    return getImpl<detail::CoilHeatingGasMultiStage_Impl>()->setOffCycleParasiticGasLoad(offCycleParasiticGasLoad);
  }

  void CoilHeatingGasMultiStage::resetOffCycleParasiticGasLoad() {
    getImpl<detail::CoilHeatingGasMultiStage_Impl>()->resetOffCycleParasiticGasLoad();
  }

  unsigned CoilHeatingGasMultiStage::numberOfStages() const {
    return getImpl<detail::CoilHeatingGasMultiStage_Impl>()->numberOfStages();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned CoilHeatingGasMultiStage_Impl::inletPort() const {
      return openstudio::Coil_Heating_Gas_MultiStageFields::AirInletNodeName;
    }

    unsigned CoilHeatingGasMultiStage_Impl::outletPort() const {
      return openstudio::Coil_Heating_Gas_MultiStageFields::AirOutletNodeName;
    }

    std::vector<ModelObject> CoilHeatingGasMultiStage_Impl::children() const {
      std::vector<ModelObject> result;
      if (auto curve = partLoadFractionCorrelationCurve()) {
        result.push_back(*curve);
      }
      return result;
    }

    bool CoilHeatingGasMultiStage_Impl::addToNode(Node& node) {
      return false;
    }

    Schedule CoilHeatingGasMultiStage_Impl::availabilitySchedule() const {
      constexpr auto field = openstudio::Coil_Heating_Gas_MultiStageFields::AvailabilityScheduleName;
      const auto managedValue = getObject<ModelObject>().getField(field, false);
      OS_ASSERT(managedValue && !managedValue->empty());
      const auto targetHandle = openstudio::toUUID(*managedValue);
      OS_ASSERT(!targetHandle.isNull());
      const auto value = model().getModelObject<Schedule>(targetHandle);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingGasMultiStage_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::Coil_Heating_Gas_MultiStageFields::AvailabilityScheduleName, "CoilHeatingGasMultiStage",
                                           "Availability Schedule", schedule);
    }

    boost::optional<Curve> CoilHeatingGasMultiStage_Impl::partLoadFractionCorrelationCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Heating_Gas_MultiStageFields::PartLoadFractionCorrelationCurveName);
    }

    bool CoilHeatingGasMultiStage_Impl::setPartLoadFractionCorrelationCurve(const Curve& curve) {
      constexpr auto field = openstudio::Coil_Heating_Gas_MultiStageFields::PartLoadFractionCorrelationCurveName;
      if (curve.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.CoilHeatingGasMultiStage",
                 "Cannot set the part-load fraction correlation curve because the curve belongs to a different model.");
        return false;
      }
      if (!model().canBeTarget(curve.handle(), iddObject().objectLists(field))) {
        LOG_FREE(Warn, "openstudio.epmodel.CoilHeatingGasMultiStage",
                 "Cannot set the part-load fraction correlation curve because curve type '" << curve.iddObject().type().valueName()
                                                                                            << "' is not accepted by Coil:Heating:Gas:MultiStage.");
        return false;
      }
      return setPointer(field, curve.handle(), false);
    }

    void CoilHeatingGasMultiStage_Impl::resetPartLoadFractionCorrelationCurve() {
      constexpr auto field = openstudio::Coil_Heating_Gas_MultiStageFields::PartLoadFractionCorrelationCurveName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<double> CoilHeatingGasMultiStage_Impl::offCycleParasiticGasLoad() const {
      return getDouble(openstudio::Coil_Heating_Gas_MultiStageFields::OffCycleParasiticGasLoad, true);
    }

    bool CoilHeatingGasMultiStage_Impl::setOffCycleParasiticGasLoad(double offCycleParasiticGasLoad) {
      return setDouble(openstudio::Coil_Heating_Gas_MultiStageFields::OffCycleParasiticGasLoad, offCycleParasiticGasLoad);
    }

    void CoilHeatingGasMultiStage_Impl::resetOffCycleParasiticGasLoad() {
      const bool result = setString(openstudio::Coil_Heating_Gas_MultiStageFields::OffCycleParasiticGasLoad, "");
      OS_ASSERT(result);
    }

    unsigned CoilHeatingGasMultiStage_Impl::numberOfStages() const {
      const auto value = getUnsigned(openstudio::Coil_Heating_Gas_MultiStageFields::NumberofStages, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingGasMultiStage_Impl::setNumberOfStages(unsigned numberOfStages) {
      return setUnsigned(openstudio::Coil_Heating_Gas_MultiStageFields::NumberofStages, numberOfStages);
    }

    void CoilHeatingGasMultiStage_Impl::doCanonicalize(LoadContext& context) {
      StraightComponent_Impl::doCanonicalize(context);

      const auto coil = getObject<ModelObject>();
      const auto coilName = coil.nameString();

      {
        constexpr auto field = openstudio::Coil_Heating_Gas_MultiStageFields::AvailabilityScheduleName;
        const auto managedValue = coil.getField(field, false);
        const auto managedHandle = managedValue ? openstudio::toUUID(*managedValue) : Handle{};
        if (!managedHandle.isNull()) {
          auto schedule = model().getModelObject<Schedule>(managedHandle);
          boost::optional<Schedule> uniqueEligibleSchedule;
          bool ambiguous = false;
          if (schedule) {
            for (const auto& candidate : model().getObjectsByName(schedule->nameString(), true)) {
              if (auto namedSchedule = candidate.optionalCast<Schedule>()) {
                if (!model().canBeTarget(namedSchedule->handle(), iddObject().objectLists(field))) {
                  continue;
                }
                if (uniqueEligibleSchedule) {
                  ambiguous = true;
                  break;
                }
                uniqueEligibleSchedule = *namedSchedule;
              }
            }
          }

          if (schedule && !ambiguous && uniqueEligibleSchedule && (uniqueEligibleSchedule->handle() == schedule->handle())
              && setAvailabilitySchedule(*schedule)) {
            // The managed relationship is already canonical.
          } else {
            detail::addLoadWarning(context, "Preserved an unresolved, ambiguous, ineligible, or incompatible availability schedule on "
                                            "Coil:Heating:Gas:MultiStage '"
                                              + coilName + "'.");
          }
        } else {
          const auto rawName = openstudio::detail::IdfObject_Impl::getString(field, false, true);
          if (rawName && !rawName->empty()) {
            boost::optional<Schedule> uniqueEligibleSchedule;
            bool ambiguous = false;
            for (const auto& candidate : model().getObjectsByName(*rawName, true)) {
              if (auto schedule = candidate.optionalCast<Schedule>()) {
                if (!model().canBeTarget(schedule->handle(), iddObject().objectLists(field))) {
                  continue;
                }
                if (uniqueEligibleSchedule) {
                  ambiguous = true;
                  break;
                }
                uniqueEligibleSchedule = *schedule;
              }
            }

            if (uniqueEligibleSchedule && !ambiguous) {
              if (setAvailabilitySchedule(*uniqueEligibleSchedule)) {
                detail::addLoadInfo(context, "Reattached availability schedule '" + uniqueEligibleSchedule->nameString()
                                               + "' to Coil:Heating:Gas:MultiStage '" + coilName + "'.");
              } else {
                detail::addLoadWarning(context, "Preserved incompatible availability schedule reference '" + *rawName
                                                  + "' on Coil:Heating:Gas:MultiStage '" + coilName + "'.");
              }
            } else {
              detail::addLoadWarning(context, "Preserved unresolved or ambiguous availability schedule reference '" + *rawName
                                                + "' on Coil:Heating:Gas:MultiStage '" + coilName + "'.");
            }
          } else if (context.repairEnabled()) {
            auto alwaysOn = model().alwaysOnDiscreteSchedule();
            if (setAvailabilitySchedule(alwaysOn)) {
              detail::addLoadInfo(context, "Attached the always-on availability schedule to Coil:Heating:Gas:MultiStage '" + coilName + "'.");
            } else {
              detail::addLoadError(context,
                                   "Failed to attach the always-on availability schedule to Coil:Heating:Gas:MultiStage '" + coilName + "'.");
            }
          } else {
            detail::addLoadWarning(context, "Coil:Heating:Gas:MultiStage '" + coilName + "' has a blank availability schedule.");
          }
        }
      }

      {
        constexpr auto field = openstudio::Coil_Heating_Gas_MultiStageFields::PartLoadFractionCorrelationCurveName;
        const auto managedValue = coil.getField(field, false);
        const auto managedHandle = managedValue ? openstudio::toUUID(*managedValue) : Handle{};
        if (!managedHandle.isNull()) {
          const auto curve = model().getModelObject<Curve>(managedHandle);
          boost::optional<Curve> uniqueEligibleCurve;
          bool ambiguous = false;
          if (curve) {
            for (const auto& candidate : model().getObjectsByName(curve->nameString(), true)) {
              if (auto namedCurve = candidate.optionalCast<Curve>()) {
                if (!model().canBeTarget(namedCurve->handle(), iddObject().objectLists(field))) {
                  continue;
                }
                if (uniqueEligibleCurve) {
                  ambiguous = true;
                  break;
                }
                uniqueEligibleCurve = *namedCurve;
              }
            }
          }

          if (curve && !ambiguous && uniqueEligibleCurve && (uniqueEligibleCurve->handle() == curve->handle())
              && setPartLoadFractionCorrelationCurve(*curve)) {
            return;
          }
          detail::addLoadWarning(context, "Preserved an unresolved, ambiguous, or ineligible part-load fraction correlation curve on "
                                          "Coil:Heating:Gas:MultiStage '"
                                            + coilName + "'.");
          return;
        }

        const auto rawName = openstudio::detail::IdfObject_Impl::getString(field, false, true);
        if (!(rawName && !rawName->empty())) {
          return;
        }

        boost::optional<Curve> uniqueEligibleCurve;
        bool ambiguous = false;
        for (const auto& candidate : model().getObjectsByName(*rawName, true)) {
          if (auto curve = candidate.optionalCast<Curve>()) {
            if (!model().canBeTarget(curve->handle(), iddObject().objectLists(field))) {
              continue;
            }
            if (uniqueEligibleCurve) {
              ambiguous = true;
              break;
            }
            uniqueEligibleCurve = *curve;
          }
        }

        if (uniqueEligibleCurve && !ambiguous) {
          if (setPartLoadFractionCorrelationCurve(*uniqueEligibleCurve)) {
            detail::addLoadInfo(context, "Reattached part-load fraction correlation curve '" + uniqueEligibleCurve->nameString()
                                           + "' to Coil:Heating:Gas:MultiStage '" + coilName + "'.");
          } else {
            detail::addLoadWarning(context, "Preserved incompatible part-load fraction correlation curve reference '" + *rawName
                                              + "' on Coil:Heating:Gas:MultiStage '" + coilName + "'.");
          }
        } else {
          detail::addLoadWarning(context, "Preserved unresolved, ambiguous, or ineligible part-load fraction correlation curve reference '" + *rawName
                                            + "' on Coil:Heating:Gas:MultiStage '" + coilName + "'.");
        }
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
