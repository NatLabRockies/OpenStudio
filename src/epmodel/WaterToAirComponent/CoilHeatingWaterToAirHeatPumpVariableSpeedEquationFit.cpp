/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToAirComponent/CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit.hpp"
#include "WaterToAirComponent/CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Curve/CurveQuadratic.hpp"
#include "Model.hpp"
#include "ModelObject/AirflowNetworkDistributionComponentCoil.hpp"
#include "ModelObject/AirflowNetworkDistributionComponentCoil_Impl.hpp"
#include "ParentObject/CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData.hpp"
#include "ParentObject/CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirflowNetwork_Distribution_Component_Coil_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFit_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

namespace openstudio {
namespace epmodel {

  CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit(const Model& model)
    : WaterToAirComponent(CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::iddObjectType(), model) {
    auto alwaysOn = model.alwaysOnDiscreteSchedule();
    OS_ASSERT(setAvailabilitySchedule(alwaysOn));
    getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->setConstructorFieldDefaults();

    CurveQuadratic partLoadFraction(model);
    partLoadFraction.setCoefficient1Constant(0.85);
    partLoadFraction.setCoefficient2x(0.15);
    partLoadFraction.setCoefficient3xPOW2(0.0);
    partLoadFraction.setMinimumValueofx(0.0);
    partLoadFraction.setMaximumValueofx(1.0);
    OS_ASSERT(setEnergyPartLoadFractionCurve(partLoadFraction));
  }

  CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit(const Model& model,
                                                                                                               const Curve& partLoadFraction)
    : WaterToAirComponent(CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::iddObjectType(), model) {
    auto alwaysOn = model.alwaysOnDiscreteSchedule();
    OS_ASSERT(setAvailabilitySchedule(alwaysOn));
    getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->setConstructorFieldDefaults();
    OS_ASSERT(setEnergyPartLoadFractionCurve(partLoadFraction));
  }

  CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit(
    std::shared_ptr<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl> impl)
    : WaterToAirComponent(std::move(impl)) {}

  IddObjectType CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::iddObjectType() {
    return IddObjectType::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFit;
  }

  Schedule CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::availabilitySchedule() const {
    return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->availabilitySchedule();
  }

  bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->setAvailabilitySchedule(schedule);
  }

  int CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::nominalSpeedLevel() const {
    return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->nominalSpeedLevel();
  }

  bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::setNominalSpeedLevel(int nominalSpeedLevel) {
    return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->setNominalSpeedLevel(nominalSpeedLevel);
  }

  boost::optional<double> CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::ratedHeatingCapacityAtSelectedNominalSpeedLevel() const {
    return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->ratedHeatingCapacityAtSelectedNominalSpeedLevel();
  }

  bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::setRatedHeatingCapacityAtSelectedNominalSpeedLevel(
    double ratedHeatingCapacityAtSelectedNominalSpeedLevel) {
    return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->setRatedHeatingCapacityAtSelectedNominalSpeedLevel(
      ratedHeatingCapacityAtSelectedNominalSpeedLevel);
  }

  bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::isRatedHeatingCapacityAtSelectedNominalSpeedLevelAutosized() const {
    return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()
      ->isRatedHeatingCapacityAtSelectedNominalSpeedLevelAutosized();
  }

  void CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::autosizeRatedHeatingCapacityAtSelectedNominalSpeedLevel() {
    getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->autosizeRatedHeatingCapacityAtSelectedNominalSpeedLevel();
  }

  boost::optional<double> CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::autosizedRatedHeatingCapacityAtSelectedNominalSpeedLevel() const {
    return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->autosizedRatedHeatingCapacityAtSelectedNominalSpeedLevel();
  }

  boost::optional<double> CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::ratedAirFlowRateAtSelectedNominalSpeedLevel() const {
    return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->ratedAirFlowRateAtSelectedNominalSpeedLevel();
  }

  bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::setRatedAirFlowRateAtSelectedNominalSpeedLevel(
    double ratedAirFlowRateAtSelectedNominalSpeedLevel) {
    return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->setRatedAirFlowRateAtSelectedNominalSpeedLevel(
      ratedAirFlowRateAtSelectedNominalSpeedLevel);
  }

  bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized() const {
    return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized();
  }

  void CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel() {
    getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel();
  }

  boost::optional<double> CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::autosizedRatedAirFlowRateAtSelectedNominalSpeedLevel() const {
    return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->autosizedRatedAirFlowRateAtSelectedNominalSpeedLevel();
  }

  boost::optional<double> CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::ratedWaterFlowRateAtSelectedNominalSpeedLevel() const {
    return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->ratedWaterFlowRateAtSelectedNominalSpeedLevel();
  }

  bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::setRatedWaterFlowRateAtSelectedNominalSpeedLevel(
    double ratedWaterFlowRateAtSelectedNominalSpeedLevel) {
    return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->setRatedWaterFlowRateAtSelectedNominalSpeedLevel(
      ratedWaterFlowRateAtSelectedNominalSpeedLevel);
  }

  bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::isRatedWaterFlowRateAtSelectedNominalSpeedLevelAutosized() const {
    return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->isRatedWaterFlowRateAtSelectedNominalSpeedLevelAutosized();
  }

  void CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::autosizeRatedWaterFlowRateAtSelectedNominalSpeedLevel() {
    getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->autosizeRatedWaterFlowRateAtSelectedNominalSpeedLevel();
  }

  boost::optional<double> CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::autosizedRatedWaterFlowRateAtSelectedNominalSpeedLevel() const {
    return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->autosizedRatedWaterFlowRateAtSelectedNominalSpeedLevel();
  }

  Curve CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::energyPartLoadFractionCurve() const {
    return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->energyPartLoadFractionCurve();
  }

  bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::setEnergyPartLoadFractionCurve(const Curve& curve) {
    return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->setEnergyPartLoadFractionCurve(curve);
  }

  std::vector<CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData> CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::speeds() const {
    return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->speeds();
  }

  bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::addSpeed(const CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData& speed) {
    return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->addSpeed(speed);
  }

  void
    CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::removeSpeed(const CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData& speed) {
    getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->removeSpeed(speed);
  }

  void CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::removeAllSpeeds() {
    getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->removeAllSpeeds();
  }

  AirflowNetworkDistributionComponentCoil CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::getAirflowNetworkEquivalentDuct(double length,
                                                                                                                                 double diameter) {
    return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->getAirflowNetworkEquivalentDuct(length, diameter);
  }

  boost::optional<AirflowNetworkDistributionComponentCoil>
    CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::airflowNetworkEquivalentDuct() const {
    return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->airflowNetworkEquivalentDuct();
  }

  std::vector<ModelObject> CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::children() const {
    return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>()->children();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {

      using Fields = openstudio::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields;
      using ExtensibleFields = openstudio::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitExtensibleFields;

      std::vector<AirflowNetworkDistributionComponentCoil> attachedAirflowNetworkDistributionComponentCoils(const ModelObject& object) {
        std::vector<AirflowNetworkDistributionComponentCoil> result;
        for (const auto& source : object.getSources(AirflowNetworkDistributionComponentCoil::iddObjectType())) {
          if (auto afnComponent = source.optionalCast<AirflowNetworkDistributionComponentCoil>()) {
            result.push_back(*afnComponent);
          }
        }
        return result;
      }

      // Transient speed-data wrappers are keyed by parent handle plus row index so
      // repeated `speeds()` calls can recover the same wrapper objects.
      std::string transientSpeedDataPrefix(const openstudio::epmodel::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit& parent) {
        return "__transient__" + openstudio::toString(parent.handle()) + "__heating_wtahp_vs_speed_";
      }

      boost::optional<CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData> transientSpeedDataByName(const Model& model,
                                                                                                               const std::string& name) {
        for (const auto& speed : model.getConcreteModelObjects<CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData>()) {
          if (const auto speedName = speed.name()) {
            if (openstudio::istringEqual(*speedName, name)) {
              return speed;
            }
          }
        }
        return boost::none;
      }

      // When rows are inserted or removed, rename the attached transient wrappers so
      // stable wrapper identity follows the current row ordering.
      void renameAttachedSpeedData(const openstudio::epmodel::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit& parent, unsigned oldIndex,
                                   unsigned newIndex) {
        if (oldIndex == newIndex) {
          return;
        }
        const auto oldName = transientSpeedDataName(parent, oldIndex);
        if (auto speed = transientSpeedDataByName(parent.model(), oldName)) {
          const bool ok = speed->setName(transientSpeedDataName(parent, newIndex)).has_value();
          OS_ASSERT(ok);
        }
      }

    }  // namespace

    std::string transientSpeedDataName(const openstudio::epmodel::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit& parent,
                                       unsigned speedIndex) {
      return transientSpeedDataPrefix(parent) + openstudio::toString(speedIndex);
    }

    unsigned CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::airInletPort() const {
      return Fields::IndoorAirInletNodeName;
    }

    unsigned CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::airOutletPort() const {
      return Fields::IndoorAirOutletNodeName;
    }

    unsigned CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::waterInletPort() const {
      return Fields::WatertoRefrigerantHXWaterInletNodeName;
    }

    unsigned CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::waterOutletPort() const {
      return Fields::WatertoRefrigerantHXWaterOutletNodeName;
    }

    Schedule CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::availabilitySchedule() const {
      auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(Fields::AvailabilityScheduleName);
      if (!schedule) {
        LOG_FREE(Error, "openstudio.epmodel.CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit",
                 "Required availability schedule not set, repairing persisted state with the model always-on discrete schedule");
        schedule = model().alwaysOnDiscreteSchedule();
        const bool ok = const_cast<CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl*>(this)->setAvailabilitySchedule(*schedule);
        OS_ASSERT(ok);
        schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(Fields::AvailabilityScheduleName);
      }
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return setSchedule(Fields::AvailabilityScheduleName, "CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit", "Availability Schedule",
                         schedule);
    }

    int CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::nominalSpeedLevel() const {
      const auto value = getInt(Fields::NominalSpeedLevel, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setNominalSpeedLevel(int nominalSpeedLevel) {
      const bool result = setInt(Fields::NominalSpeedLevel, nominalSpeedLevel);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::ratedHeatingCapacityAtSelectedNominalSpeedLevel() const {
      return getDouble(Fields::RatedHeatingCapacityAtSelectedNominalSpeedLevel, true);
    }

    bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setRatedHeatingCapacityAtSelectedNominalSpeedLevel(
      double ratedHeatingCapacityAtSelectedNominalSpeedLevel) {
      return setDouble(Fields::RatedHeatingCapacityAtSelectedNominalSpeedLevel, ratedHeatingCapacityAtSelectedNominalSpeedLevel);
    }

    bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::isRatedHeatingCapacityAtSelectedNominalSpeedLevelAutosized() const {
      if (const auto value = getString(Fields::RatedHeatingCapacityAtSelectedNominalSpeedLevel, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    void CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::autosizeRatedHeatingCapacityAtSelectedNominalSpeedLevel() {
      OS_ASSERT(setString(Fields::RatedHeatingCapacityAtSelectedNominalSpeedLevel, "autosize"));
    }

    boost::optional<double>
      CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::autosizedRatedHeatingCapacityAtSelectedNominalSpeedLevel() const {
      return boost::none;
    }

    boost::optional<double> CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::ratedAirFlowRateAtSelectedNominalSpeedLevel() const {
      return getDouble(Fields::RatedAirFlowRateAtSelectedNominalSpeedLevel, true);
    }

    bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setRatedAirFlowRateAtSelectedNominalSpeedLevel(
      double ratedAirFlowRateAtSelectedNominalSpeedLevel) {
      return setDouble(Fields::RatedAirFlowRateAtSelectedNominalSpeedLevel, ratedAirFlowRateAtSelectedNominalSpeedLevel);
    }

    bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized() const {
      if (const auto value = getString(Fields::RatedAirFlowRateAtSelectedNominalSpeedLevel, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    void CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel() {
      OS_ASSERT(setString(Fields::RatedAirFlowRateAtSelectedNominalSpeedLevel, "autosize"));
    }

    boost::optional<double> CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::autosizedRatedAirFlowRateAtSelectedNominalSpeedLevel() const {
      return boost::none;
    }

    boost::optional<double> CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::ratedWaterFlowRateAtSelectedNominalSpeedLevel() const {
      return getDouble(Fields::RatedWaterFlowRateAtSelectedNominalSpeedLevel, true);
    }

    bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setRatedWaterFlowRateAtSelectedNominalSpeedLevel(
      double ratedWaterFlowRateAtSelectedNominalSpeedLevel) {
      return setDouble(Fields::RatedWaterFlowRateAtSelectedNominalSpeedLevel, ratedWaterFlowRateAtSelectedNominalSpeedLevel);
    }

    bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::isRatedWaterFlowRateAtSelectedNominalSpeedLevelAutosized() const {
      if (const auto value = getString(Fields::RatedWaterFlowRateAtSelectedNominalSpeedLevel, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    void CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::autosizeRatedWaterFlowRateAtSelectedNominalSpeedLevel() {
      OS_ASSERT(setString(Fields::RatedWaterFlowRateAtSelectedNominalSpeedLevel, "autosize"));
    }

    boost::optional<double>
      CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::autosizedRatedWaterFlowRateAtSelectedNominalSpeedLevel() const {
      return boost::none;
    }

    Curve CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::energyPartLoadFractionCurve() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<Curve>(Fields::EnergyPartLoadFractionCurveName);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setEnergyPartLoadFractionCurve(const Curve& curve) {
      return setPointer(Fields::EnergyPartLoadFractionCurveName, curve.handle(), false);
    }

    std::vector<CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData>
      CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::speeds() const {
      std::vector<CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData> result;
      const auto parent = getObject<openstudio::epmodel::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit>();
      const auto groups = parent.extensibleGroups();
      result.reserve(groups.size());
      for (unsigned i = 0; i < groups.size(); ++i) {
        result.push_back(model().getOrCreateTransientByName<openstudio::epmodel::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData>(
          detail::transientSpeedDataName(parent, i)));
      }
      return result;
    }

    bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::addSpeed(
      const CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData& speed) {
      const auto parent = getObject<openstudio::epmodel::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit>();
      auto group = getObject<ModelObject>().pushExtensibleGroup().cast<WorkspaceExtensibleGroup>();
      bool ok = true;
      ok = group.setDouble(ExtensibleFields::SpeedReferenceUnitGrossRatedHeatingCapacity, speed.referenceUnitGrossRatedHeatingCapacity()) && ok;
      ok = group.setDouble(ExtensibleFields::SpeedReferenceUnitGrossRatedHeatingCOP, speed.referenceUnitGrossRatedHeatingCOP()) && ok;
      ok = group.setDouble(ExtensibleFields::SpeedReferenceUnitRatedAirFlowRate, speed.referenceUnitRatedAirFlow()) && ok;
      ok = group.setDouble(ExtensibleFields::SpeedReferenceUnitRatedWaterFlowRate, speed.referenceUnitRatedWaterFlowRate()) && ok;
      ok = group.setPointer(ExtensibleFields::SpeedHeatingCapacityFunctionofTemperatureCurveName,
                            speed.heatingCapacityFunctionofTemperatureCurve().handle())
           && ok;
      ok = group.setPointer(ExtensibleFields::SpeedTotalHeatingCapacityFunctionofAirFlowFractionCurveName,
                            speed.totalHeatingCapacityFunctionofAirFlowFractionCurve().handle())
           && ok;
      ok = group.setPointer(ExtensibleFields::SpeedHeatingCapacityFunctionofWaterFlowFractionCurveName,
                            speed.heatingCapacityFunctionofWaterFlowFractionCurve().handle())
           && ok;
      ok = group.setPointer(ExtensibleFields::SpeedEnergyInputRatioFunctionofTemperatureCurveName,
                            speed.energyInputRatioFunctionofTemperatureCurve().handle())
           && ok;
      ok = group.setPointer(ExtensibleFields::SpeedEnergyInputRatioFunctionofAirFlowFractionCurveName,
                            speed.energyInputRatioFunctionofAirFlowFractionCurve().handle())
           && ok;
      ok = group.setPointer(ExtensibleFields::SpeedEnergyInputRatioFunctionofWaterFlowFractionCurveName,
                            speed.energyInputRatioFunctionofWaterFlowFractionCurve().handle())
           && ok;
      ok = group.setDouble(ExtensibleFields::SpeedReferenceUnitWasteHeatFractionofInputPowerAtRatedConditions,
                           speed.referenceUnitWasteHeatFractionofInputPowerAtRatedConditions())
           && ok;
      ok =
        group.setPointer(ExtensibleFields::SpeedWasteHeatFunctionofTemperatureCurveName, speed.wasteHeatFunctionofTemperatureCurve().handle()) && ok;
      if (!ok) {
        getObject<ModelObject>().eraseExtensibleGroup(group.groupIndex());
        return false;
      }
      OS_ASSERT(setInt(Fields::NumberofSpeeds, static_cast<int>(getObject<ModelObject>().numExtensibleGroups())));
      auto attachedSpeed = speed;
      const bool renamed = attachedSpeed.setName(detail::transientSpeedDataName(parent, group.groupIndex())).has_value();
      OS_ASSERT(renamed);
      return true;
    }

    void CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::removeSpeed(
      const CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData& speed) {
      const auto parent = getObject<openstudio::epmodel::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit>();
      const auto thisName = speed.name();
      if (!thisName) {
        return;
      }

      const auto groups = parent.extensibleGroups();
      for (unsigned i = 0; i < groups.size(); ++i) {
        if (openstudio::istringEqual(*thisName, detail::transientSpeedDataName(parent, i))) {
          const auto previousCount = static_cast<unsigned>(groups.size());
          getObject<ModelObject>().eraseExtensibleGroup(i);
          const auto remainingSpeeds = static_cast<int>(getObject<ModelObject>().numExtensibleGroups());
          for (unsigned oldIndex = i + 1; oldIndex < previousCount; ++oldIndex) {
            renameAttachedSpeedData(parent, oldIndex, oldIndex - 1);
          }
          if (remainingSpeeds > 0) {
            OS_ASSERT(setInt(Fields::NumberofSpeeds, remainingSpeeds));
          } else {
            OS_ASSERT(setString(Fields::NumberofSpeeds, ""));
          }
          if (remainingSpeeds > 0 && nominalSpeedLevel() > remainingSpeeds) {
            OS_ASSERT(setNominalSpeedLevel(remainingSpeeds));
          }
          return;
        }
      }
    }

    void CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::removeAllSpeeds() {
      getObject<ModelObject>().clearExtensibleGroups();
      OS_ASSERT(setString(Fields::NumberofSpeeds, ""));
    }

    std::vector<ModelObject> CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::children() const {
      std::vector<ModelObject> result;
      for (const auto& speed : speeds()) {
        result.push_back(speed);
      }
      result.push_back(energyPartLoadFractionCurve());
      for (const auto& afnComponent : attachedAirflowNetworkDistributionComponentCoils(getObject<ModelObject>())) {
        result.push_back(afnComponent);
      }
      return result;
    }

    std::vector<IdfObject> CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::remove() {
      if (!isRemovable()) {
        return {};
      }

      auto speedWrappers = speeds();
      for (auto& speed : speedWrappers) {
        speed.remove();
      }

      for (auto& afnComponent : attachedAirflowNetworkDistributionComponentCoils(getObject<ModelObject>())) {
        afnComponent.remove();
      }

      return WaterToAirComponent_Impl::remove();
    }

    AirflowNetworkDistributionComponentCoil
      CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::getAirflowNetworkEquivalentDuct(double length, double diameter) {
      constexpr const char* coilObjectType = "Coil:Heating:WaterToAirHeatPump:VariableSpeedEquationFit";
      if (auto component = airflowNetworkEquivalentDuct()) {
        if (!openstudio::istringEqual(component->coilObjectType(), coilObjectType)) {
          OS_ASSERT(component->setCoilObjectType(coilObjectType));
        }
        if (component->airPathLength() != length) {
          component->setAirPathLength(length);
        }
        if (component->airPathHydraulicDiameter() != diameter) {
          component->setAirPathHydraulicDiameter(diameter);
        }
        return *component;
      }

      AirflowNetworkDistributionComponentCoil component(model());
      OS_ASSERT(component.setPointer(openstudio::AirflowNetwork_Distribution_Component_CoilFields::CoilName, handle()));
      OS_ASSERT(component.setCoilObjectType(coilObjectType));
      OS_ASSERT(component.setAirPathLength(length));
      OS_ASSERT(component.setAirPathHydraulicDiameter(diameter));
      return component;
    }

    boost::optional<AirflowNetworkDistributionComponentCoil>
      CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::airflowNetworkEquivalentDuct() const {
      auto afnComponents = attachedAirflowNetworkDistributionComponentCoils(getObject<ModelObject>());
      if (afnComponents.size() == 1u) {
        return afnComponents.front();
      }
      if (afnComponents.size() > 1u) {
        LOG_FREE(Warn, "openstudio.epmodel.CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit",
                 briefDescription() << " has more than one AirflowNetwork distribution component coil attached, returning first.");
        return afnComponents.front();
      }
      return boost::none;
    }

    void CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl::setConstructorFieldDefaults() {
      OS_ASSERT(setInt(Fields::NominalSpeedLevel, 1));
      autosizeRatedHeatingCapacityAtSelectedNominalSpeedLevel();
      autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel();
      autosizeRatedWaterFlowRateAtSelectedNominalSpeedLevel();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
