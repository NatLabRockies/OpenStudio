/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToAirComponent/CoilWaterHeatingAirToWaterHeatPumpVariableSpeed.hpp"
#include "WaterToAirComponent/CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/CurveQuadratic.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Model.hpp"
#include "ParentObject/CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData.hpp"
#include "ParentObject/CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

namespace openstudio {
namespace epmodel {

  CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed(const Model& model)
    : WaterToAirComponent(CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::iddObjectType(), model) {
    auto alwaysOn = model.alwaysOnDiscreteSchedule();
    OS_ASSERT(setAvailabilitySchedule(alwaysOn));
    getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->setConstructorSharedDefaults(model);
  }

  CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed(
    std::shared_ptr<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl> impl)
    : WaterToAirComponent(std::move(impl)) {}

  IddObjectType CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::iddObjectType() {
    return IddObjectType::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed;
  }

  std::vector<std::string> CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::evaporatorAirTemperatureTypeforCurveObjectsValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::EvaporatorAirTemperatureTypeforCurveObjects);
  }

  Schedule CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::availabilitySchedule() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->availabilitySchedule();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->setAvailabilitySchedule(schedule);
  }

  int CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::nominalSpeedLevel() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->nominalSpeedLevel();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::setNominalSpeedLevel(int nominalSpeedLevel) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->setNominalSpeedLevel(nominalSpeedLevel);
  }

  double CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::ratedWaterHeatingCapacity() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->ratedWaterHeatingCapacity();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::setRatedWaterHeatingCapacity(double ratedWaterHeatingCapacity) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->setRatedWaterHeatingCapacity(ratedWaterHeatingCapacity);
  }

  double CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::ratedEvaporatorInletAirDryBulbTemperature() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->ratedEvaporatorInletAirDryBulbTemperature();
  }

  bool
    CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::setRatedEvaporatorInletAirDryBulbTemperature(double ratedEvaporatorInletAirDryBulbTemperature) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->setRatedEvaporatorInletAirDryBulbTemperature(
      ratedEvaporatorInletAirDryBulbTemperature);
  }

  double CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::ratedEvaporatorInletAirWetBulbTemperature() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->ratedEvaporatorInletAirWetBulbTemperature();
  }

  bool
    CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::setRatedEvaporatorInletAirWetBulbTemperature(double ratedEvaporatorInletWetDryBulbTemperature) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->setRatedEvaporatorInletAirWetBulbTemperature(
      ratedEvaporatorInletWetDryBulbTemperature);
  }

  double CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::ratedCondenserInletWaterTemperature() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->ratedCondenserInletWaterTemperature();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::setRatedCondenserInletWaterTemperature(double ratedCondenserInletWaterTemperature) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->setRatedCondenserInletWaterTemperature(
      ratedCondenserInletWaterTemperature);
  }

  boost::optional<double> CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::ratedEvaporatorAirFlowRate() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->ratedEvaporatorAirFlowRate();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::setRatedEvaporatorAirFlowRate(double ratedEvaporatorAirFlowRate) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->setRatedEvaporatorAirFlowRate(ratedEvaporatorAirFlowRate);
  }

  bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::isRatedEvaporatorAirFlowRateAutocalculated() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->isRatedEvaporatorAirFlowRateAutocalculated();
  }

  void CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::autocalculateRatedEvaporatorAirFlowRate() {
    getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->autocalculateRatedEvaporatorAirFlowRate();
  }

  boost::optional<double> CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::autocalculatedRatedEvaporatorAirFlowRate() const {
    return boost::none;
  }

  boost::optional<double> CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::ratedCondenserWaterFlowRate() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->ratedCondenserWaterFlowRate();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::setRatedCondenserWaterFlowRate(double ratedCondenserWaterFlowRate) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->setRatedCondenserWaterFlowRate(ratedCondenserWaterFlowRate);
  }

  bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::isRatedCondenserWaterFlowRateAutocalculated() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->isRatedCondenserWaterFlowRateAutocalculated();
  }

  void CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::autocalculateRatedCondenserWaterFlowRate() {
    getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->autocalculateRatedCondenserWaterFlowRate();
  }

  boost::optional<double> CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::autocalculatedRatedCondenserWaterFlowRate() const {
    return boost::none;
  }

  std::string CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::evaporatorFanPowerIncludedinRatedCOP() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->evaporatorFanPowerIncludedinRatedCOP();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::setEvaporatorFanPowerIncludedinRatedCOP(
    const std::string& evaporatorFanPowerIncludedinRatedCOP) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->setEvaporatorFanPowerIncludedinRatedCOP(
      evaporatorFanPowerIncludedinRatedCOP);
  }

  std::string CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::condenserPumpPowerIncludedinRatedCOP() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->condenserPumpPowerIncludedinRatedCOP();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::setCondenserPumpPowerIncludedinRatedCOP(
    const std::string& condenserPumpPowerIncludedinRatedCOP) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->setCondenserPumpPowerIncludedinRatedCOP(
      condenserPumpPowerIncludedinRatedCOP);
  }

  std::string CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::setCondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP(
    const std::string& condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->setCondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP(
      condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP);
  }

  double CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::fractionofCondenserPumpHeattoWater() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->fractionofCondenserPumpHeattoWater();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::setFractionofCondenserPumpHeattoWater(double fractionofCondenserPumpHeattoWater) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->setFractionofCondenserPumpHeattoWater(
      fractionofCondenserPumpHeattoWater);
  }

  double CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::crankcaseHeaterCapacity() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->crankcaseHeaterCapacity();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->setCrankcaseHeaterCapacity(crankcaseHeaterCapacity);
  }

  boost::optional<Curve> CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::crankcaseHeaterCapacityFunctionofTemperatureCurve() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->crankcaseHeaterCapacityFunctionofTemperatureCurve();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& curve) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->setCrankcaseHeaterCapacityFunctionofTemperatureCurve(curve);
  }

  void CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::resetCrankcaseHeaterCapacityFunctionofTemperatureCurve() {
    getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();
  }

  double CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::maximumAmbientTemperatureforCrankcaseHeaterOperation() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->maximumAmbientTemperatureforCrankcaseHeaterOperation();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::setMaximumAmbientTemperatureforCrankcaseHeaterOperation(
    double maximumAmbientTemperatureforCrankcaseHeaterOperation) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->setMaximumAmbientTemperatureforCrankcaseHeaterOperation(
      maximumAmbientTemperatureforCrankcaseHeaterOperation);
  }

  std::string CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::evaporatorAirTemperatureTypeforCurveObjects() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->evaporatorAirTemperatureTypeforCurveObjects();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::setEvaporatorAirTemperatureTypeforCurveObjects(
    const std::string& evaporatorAirTemperatureTypeforCurveObjects) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->setEvaporatorAirTemperatureTypeforCurveObjects(
      evaporatorAirTemperatureTypeforCurveObjects);
  }

  Curve CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::partLoadFractionCorrelationCurve() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->partLoadFractionCorrelationCurve();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::setPartLoadFractionCorrelationCurve(const Curve& curve) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->setPartLoadFractionCorrelationCurve(curve);
  }

  std::vector<CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData> CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::speeds() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->speeds();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::addSpeed(const CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData& speed) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->addSpeed(speed);
  }

  void CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::removeSpeed(const CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData& speed) {
    getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->removeSpeed(speed);
  }

  void CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::removeAllSpeeds() {
    getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->removeAllSpeeds();
  }

  std::vector<ModelObject> CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::children() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>()->children();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {

      using Fields = openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields;
      using ExtensibleFields = openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedExtensibleFields;

      std::string transientSpeedDataPrefix(const openstudio::epmodel::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed& parent) {
        return "__transient__" + openstudio::toString(parent.handle()) + "__water_heating_air_to_water_hp_vs_speed_";
      }

      std::string detachedTransientSpeedDataName() {
        return "__transient__wh_air_to_water_hp_vs_speed_data_detached_" + openstudio::toString(openstudio::createUUID());
      }

      boost::optional<CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData> transientSpeedDataByName(const Model& model,
                                                                                                          const std::string& name) {
        for (const auto& speed : model.getConcreteModelObjects<CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData>(true)) {
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
      void renameAttachedSpeedData(const openstudio::epmodel::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed& parent, unsigned oldIndex,
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

    std::string transientSpeedDataName(const openstudio::epmodel::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed& parent,
                                       unsigned speedIndex) {
      return transientSpeedDataPrefix(parent) + openstudio::toString(speedIndex);
    }

    unsigned CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::airInletPort() const {
      return Fields::EvaporatorAirInletNodeName;
    }

    unsigned CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::airOutletPort() const {
      return Fields::EvaporatorAirOutletNodeName;
    }

    unsigned CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::waterInletPort() const {
      return Fields::CondenserWaterInletNodeName;
    }

    unsigned CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::waterOutletPort() const {
      return Fields::CondenserWaterOutletNodeName;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::addToNode(Node& node) {
      (void)node;
      return false;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::addToSplitter(Splitter& splitter) {
      (void)splitter;
      return false;
    }

    Schedule CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::availabilitySchedule() const {
      auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(Fields::AvailabilityScheduleName);
      if (!schedule) {
        LOG_FREE(Error, "openstudio.epmodel.CoilWaterHeatingAirToWaterHeatPumpVariableSpeed",
                 "Required availability schedule not set, repairing persisted state with the model always-on discrete schedule");
        schedule = model().alwaysOnDiscreteSchedule();
        const bool ok = const_cast<CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl*>(this)->setAvailabilitySchedule(*schedule);
        OS_ASSERT(ok);
        schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(Fields::AvailabilityScheduleName);
      }
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return setSchedule(Fields::AvailabilityScheduleName, "CoilWaterHeatingAirToWaterHeatPumpVariableSpeed", "Availability Schedule", schedule);
    }

    int CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::nominalSpeedLevel() const {
      const auto value = getInt(Fields::NominalSpeedLevel, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::setNominalSpeedLevel(int nominalSpeedLevel) {
      return setInt(Fields::NominalSpeedLevel, nominalSpeedLevel);
    }

    double CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::ratedWaterHeatingCapacity() const {
      const auto value = getDouble(Fields::RatedWaterHeatingCapacity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::setRatedWaterHeatingCapacity(double ratedWaterHeatingCapacity) {
      return setDouble(Fields::RatedWaterHeatingCapacity, ratedWaterHeatingCapacity);
    }

    double CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::ratedEvaporatorInletAirDryBulbTemperature() const {
      const auto value = getDouble(Fields::RatedEvaporatorInletAirDryBulbTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::setRatedEvaporatorInletAirDryBulbTemperature(
      double ratedEvaporatorInletAirDryBulbTemperature) {
      return setDouble(Fields::RatedEvaporatorInletAirDryBulbTemperature, ratedEvaporatorInletAirDryBulbTemperature);
    }

    double CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::ratedEvaporatorInletAirWetBulbTemperature() const {
      const auto value = getDouble(Fields::RatedEvaporatorInletAirWetBulbTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::setRatedEvaporatorInletAirWetBulbTemperature(
      double ratedEvaporatorInletWetDryBulbTemperature) {
      return setDouble(Fields::RatedEvaporatorInletAirWetBulbTemperature, ratedEvaporatorInletWetDryBulbTemperature);
    }

    double CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::ratedCondenserInletWaterTemperature() const {
      const auto value = getDouble(Fields::RatedCondenserInletWaterTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::setRatedCondenserInletWaterTemperature(double ratedCondenserInletWaterTemperature) {
      return setDouble(Fields::RatedCondenserInletWaterTemperature, ratedCondenserInletWaterTemperature);
    }

    boost::optional<double> CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::ratedEvaporatorAirFlowRate() const {
      return getDouble(Fields::RatedEvaporatorAirFlowRate, true);
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::setRatedEvaporatorAirFlowRate(double ratedEvaporatorAirFlowRate) {
      return setDouble(Fields::RatedEvaporatorAirFlowRate, ratedEvaporatorAirFlowRate);
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::isRatedEvaporatorAirFlowRateAutocalculated() const {
      if (const auto value = getString(Fields::RatedEvaporatorAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    void CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::autocalculateRatedEvaporatorAirFlowRate() {
      OS_ASSERT(setString(Fields::RatedEvaporatorAirFlowRate, "autocalculate"));
    }

    boost::optional<double> CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::autocalculatedRatedEvaporatorAirFlowRate() const {
      return boost::none;
    }

    boost::optional<double> CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::ratedCondenserWaterFlowRate() const {
      return getDouble(Fields::RatedCondenserWaterFlowRate, true);
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::setRatedCondenserWaterFlowRate(double ratedCondenserWaterFlowRate) {
      return setDouble(Fields::RatedCondenserWaterFlowRate, ratedCondenserWaterFlowRate);
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::isRatedCondenserWaterFlowRateAutocalculated() const {
      if (const auto value = getString(Fields::RatedCondenserWaterFlowRate, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    void CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::autocalculateRatedCondenserWaterFlowRate() {
      OS_ASSERT(setString(Fields::RatedCondenserWaterFlowRate, "autocalculate"));
    }

    boost::optional<double> CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::autocalculatedRatedCondenserWaterFlowRate() const {
      return boost::none;
    }

    std::string CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::evaporatorFanPowerIncludedinRatedCOP() const {
      const auto value = getString(Fields::EvaporatorFanPowerIncludedinRatedCOP, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::setEvaporatorFanPowerIncludedinRatedCOP(
      const std::string& evaporatorFanPowerIncludedinRatedCOP) {
      return setString(Fields::EvaporatorFanPowerIncludedinRatedCOP, evaporatorFanPowerIncludedinRatedCOP);
    }

    std::string CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::condenserPumpPowerIncludedinRatedCOP() const {
      const auto value = getString(Fields::CondenserPumpPowerIncludedinRatedCOP, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::setCondenserPumpPowerIncludedinRatedCOP(
      const std::string& condenserPumpPowerIncludedinRatedCOP) {
      return setString(Fields::CondenserPumpPowerIncludedinRatedCOP, condenserPumpPowerIncludedinRatedCOP);
    }

    std::string CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP() const {
      const auto value = getString(Fields::CondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::setCondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP(
      const std::string& condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP) {
      return setString(Fields::CondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP, condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP);
    }

    double CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::fractionofCondenserPumpHeattoWater() const {
      const auto value = getDouble(Fields::FractionofCondenserPumpHeattoWater, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::setFractionofCondenserPumpHeattoWater(double fractionofCondenserPumpHeattoWater) {
      return setDouble(Fields::FractionofCondenserPumpHeattoWater, fractionofCondenserPumpHeattoWater);
    }

    double CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::crankcaseHeaterCapacity() const {
      const auto value = getDouble(Fields::CrankcaseHeaterCapacity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity) {
      return setDouble(Fields::CrankcaseHeaterCapacity, crankcaseHeaterCapacity);
    }

    boost::optional<Curve> CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::crankcaseHeaterCapacityFunctionofTemperatureCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(Fields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName);
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& curve) {
      return setPointer(Fields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName, curve.handle(), false);
    }

    void CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::resetCrankcaseHeaterCapacityFunctionofTemperatureCurve() {
      OS_ASSERT(setPointer(Fields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName, openstudio::Handle(), false));
    }

    double CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::maximumAmbientTemperatureforCrankcaseHeaterOperation() const {
      const auto value = getDouble(Fields::MaximumAmbientTemperatureforCrankcaseHeaterOperation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::setMaximumAmbientTemperatureforCrankcaseHeaterOperation(
      double maximumAmbientTemperatureforCrankcaseHeaterOperation) {
      return setDouble(Fields::MaximumAmbientTemperatureforCrankcaseHeaterOperation, maximumAmbientTemperatureforCrankcaseHeaterOperation);
    }

    std::string CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::evaporatorAirTemperatureTypeforCurveObjects() const {
      const auto value = getString(Fields::EvaporatorAirTemperatureTypeforCurveObjects, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::setEvaporatorAirTemperatureTypeforCurveObjects(
      const std::string& evaporatorAirTemperatureTypeforCurveObjects) {
      return setString(Fields::EvaporatorAirTemperatureTypeforCurveObjects, evaporatorAirTemperatureTypeforCurveObjects);
    }

    Curve CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::partLoadFractionCorrelationCurve() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<Curve>(Fields::PartLoadFractionCorrelationCurveName);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::setPartLoadFractionCorrelationCurve(const Curve& curve) {
      return setPointer(Fields::PartLoadFractionCorrelationCurveName, curve.handle(), false);
    }

    std::vector<CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData> CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::speeds() const {
      std::vector<CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData> result;
      const auto parent = getObject<openstudio::epmodel::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed>();
      const auto groups = parent.extensibleGroups();
      result.reserve(groups.size());
      for (unsigned i = 0; i < groups.size(); ++i) {
        result.push_back(model().getOrCreateTransientByName<openstudio::epmodel::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData>(
          detail::transientSpeedDataName(parent, i)));
      }
      return result;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::addSpeed(const CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData& speed) {
      const auto parent = getObject<openstudio::epmodel::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed>();
      auto group = getObject<ModelObject>().pushExtensibleGroup().cast<WorkspaceExtensibleGroup>();
      bool ok = true;
      ok = group.setDouble(ExtensibleFields::SpeedRatedWaterHeatingCapacity, speed.ratedWaterHeatingCapacity()) && ok;
      ok = group.setDouble(ExtensibleFields::SpeedRatedWaterHeatingCOP, speed.ratedWaterHeatingCOP()) && ok;
      ok = group.setDouble(ExtensibleFields::SpeedRatedSensibleHeatRatio, speed.ratedSensibleHeatRatio()) && ok;
      ok = group.setDouble(ExtensibleFields::SpeedReferenceUnitRatedAirFlowRate, speed.referenceUnitRatedAirFlowRate()) && ok;
      ok = group.setDouble(ExtensibleFields::SpeedReferenceUnitRatedWaterFlowRate, speed.referenceUnitRatedWaterFlowRate()) && ok;
      ok = group.setDouble(ExtensibleFields::SpeedReferenceUnitWaterPumpInputPowerAtRatedConditions,
                           speed.referenceUnitWaterPumpInputPowerAtRatedConditions()) && ok;
      ok = group.setPointer(ExtensibleFields::SpeedTotalWHCapacityFunctionofTemperatureCurveName,
                            speed.totalWaterHeatingCapacityFunctionofTemperatureCurve().handle()) && ok;
      ok = group.setPointer(ExtensibleFields::SpeedTotalWHCapacityFunctionofAirFlowFractionCurveName,
                            speed.totalWaterHeatingCapacityFunctionofAirFlowFractionCurve().handle()) && ok;
      ok = group.setPointer(ExtensibleFields::SpeedTotalWHCapacityFunctionofWaterFlowFractionCurveName,
                            speed.totalWaterHeatingCapacityFunctionofWaterFlowFractionCurve().handle()) && ok;
      ok = group.setPointer(ExtensibleFields::SpeedCOPFunctionofTemperatureCurveName, speed.cOPFunctionofTemperatureCurve().handle()) && ok;
      ok = group.setPointer(ExtensibleFields::SpeedCOPFunctionofAirFlowFractionCurveName, speed.cOPFunctionofAirFlowFractionCurve().handle()) && ok;
      ok = group.setPointer(ExtensibleFields::SpeedCOPFunctionofWaterFlowFractionCurveName, speed.cOPFunctionofWaterFlowFractionCurve().handle()) && ok;
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

    void CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::removeSpeed(const CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData& speed) {
      const auto parent = getObject<openstudio::epmodel::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed>();
      const auto thisName = speed.name();
      if (!thisName) {
        return;
      }

      const auto groups = parent.extensibleGroups();
      for (unsigned i = 0; i < groups.size(); ++i) {
        if (openstudio::istringEqual(*thisName, detail::transientSpeedDataName(parent, i))) {
          const auto previousCount = static_cast<unsigned>(groups.size());
          const bool detached = speed.setName(detachedTransientSpeedDataName()).has_value();
          OS_ASSERT(detached);
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
          return;
        }
      }
    }

    void CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::removeAllSpeeds() {
      auto speedWrappers = speeds();
      getObject<ModelObject>().clearExtensibleGroups();
      OS_ASSERT(setString(Fields::NumberofSpeeds, ""));
      for (auto& speed : speedWrappers) {
        const bool renamed = speed.setName(detachedTransientSpeedDataName()).has_value();
        OS_ASSERT(renamed);
      }
    }

    std::vector<ModelObject> CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::children() const {
      std::vector<ModelObject> result;
      result.push_back(partLoadFractionCorrelationCurve());
      if (auto crankcaseCurve = crankcaseHeaterCapacityFunctionofTemperatureCurve()) {
        result.push_back(*crankcaseCurve);
      }
      for (const auto& speed : speeds()) {
        result.push_back(speed);
      }
      return result;
    }

    std::vector<IdfObject> CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::remove() {
      if (!isRemovable()) {
        return {};
      }

      auto speedWrappers = speeds();
      for (auto& speed : speedWrappers) {
        speed.remove();
      }

      return WaterToAirComponent_Impl::remove();
    }

    void CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::setConstructorSharedDefaults(const Model& model) {
      OS_ASSERT(setInt(Fields::NominalSpeedLevel, 1));
      OS_ASSERT(setDouble(Fields::RatedWaterHeatingCapacity, 4000.0));
      OS_ASSERT(setDouble(Fields::RatedEvaporatorInletAirDryBulbTemperature, 29.44));
      OS_ASSERT(setDouble(Fields::RatedEvaporatorInletAirWetBulbTemperature, 22.22));
      OS_ASSERT(setDouble(Fields::RatedCondenserInletWaterTemperature, 55.72));
      autocalculateRatedEvaporatorAirFlowRate();
      autocalculateRatedCondenserWaterFlowRate();
      OS_ASSERT(setString(Fields::EvaporatorFanPowerIncludedinRatedCOP, "Yes"));
      OS_ASSERT(setString(Fields::CondenserPumpPowerIncludedinRatedCOP, "No"));
      OS_ASSERT(setString(Fields::CondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP, "No"));
      OS_ASSERT(setDouble(Fields::FractionofCondenserPumpHeattoWater, 0.2));
      OS_ASSERT(setDouble(Fields::CrankcaseHeaterCapacity, 0.0));
      OS_ASSERT(setDouble(Fields::MaximumAmbientTemperatureforCrankcaseHeaterOperation, 10.0));
      OS_ASSERT(setString(Fields::EvaporatorAirTemperatureTypeforCurveObjects, "WetBulbTemperature"));

      CurveQuadratic partLoadFraction(model);
      OS_ASSERT(partLoadFraction.setCoefficient1Constant(0.75));
      OS_ASSERT(partLoadFraction.setCoefficient2x(0.25));
      OS_ASSERT(partLoadFraction.setCoefficient3xPOW2(0.0));
      OS_ASSERT(partLoadFraction.setMinimumValueofx(0.0));
      OS_ASSERT(partLoadFraction.setMaximumValueofx(1.0));
      OS_ASSERT(setPartLoadFractionCorrelationCurve(partLoadFraction));
    }

    std::vector<std::string> CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::evaporatorAirTemperatureTypeforCurveObjectsValues() const {
      return openstudio::epmodel::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::evaporatorAirTemperatureTypeforCurveObjectsValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
