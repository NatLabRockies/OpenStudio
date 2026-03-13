/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACComponent/CoilWaterHeatingAirToWaterHeatPumpVariableSpeed.hpp"
#include "HVACComponent/CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed(const Model& model)
    : HVACComponent(CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::iddObjectType(), model) {}

  CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed(
    std::shared_ptr<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl> impl)
    : HVACComponent(std::move(impl)) {}

  IddObjectType CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::iddObjectType() {
    return IddObjectType::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed;
  }

  std::vector<std::string> CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::evaporatorAirTemperatureTypeforCurveObjectsValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::EvaporatorAirTemperatureTypeforCurveObjects);
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

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    int CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::nominalSpeedLevel() const {
      const auto value = getInt(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::NominalSpeedLevel, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::setNominalSpeedLevel(int nominalSpeedLevel) {
      return setInt(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::NominalSpeedLevel, nominalSpeedLevel);
    }

    double CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::ratedWaterHeatingCapacity() const {
      const auto value = getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedWaterHeatingCapacity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::setRatedWaterHeatingCapacity(double ratedWaterHeatingCapacity) {
      return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedWaterHeatingCapacity, ratedWaterHeatingCapacity);
    }

    double CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::ratedEvaporatorInletAirDryBulbTemperature() const {
      const auto value =
        getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedEvaporatorInletAirDryBulbTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::setRatedEvaporatorInletAirDryBulbTemperature(
      double ratedEvaporatorInletAirDryBulbTemperature) {
      return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedEvaporatorInletAirDryBulbTemperature,
                       ratedEvaporatorInletAirDryBulbTemperature);
    }

    double CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::ratedEvaporatorInletAirWetBulbTemperature() const {
      const auto value =
        getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedEvaporatorInletAirWetBulbTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::setRatedEvaporatorInletAirWetBulbTemperature(
      double ratedEvaporatorInletWetDryBulbTemperature) {
      return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedEvaporatorInletAirWetBulbTemperature,
                       ratedEvaporatorInletWetDryBulbTemperature);
    }

    double CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::ratedCondenserInletWaterTemperature() const {
      const auto value = getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedCondenserInletWaterTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::setRatedCondenserInletWaterTemperature(double ratedCondenserInletWaterTemperature) {
      return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedCondenserInletWaterTemperature,
                       ratedCondenserInletWaterTemperature);
    }

    boost::optional<double> CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::ratedEvaporatorAirFlowRate() const {
      return getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedEvaporatorAirFlowRate, true);
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::setRatedEvaporatorAirFlowRate(double ratedEvaporatorAirFlowRate) {
      return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedEvaporatorAirFlowRate, ratedEvaporatorAirFlowRate);
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::isRatedEvaporatorAirFlowRateAutocalculated() const {
      if (const auto value = getString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedEvaporatorAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    void CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::autocalculateRatedEvaporatorAirFlowRate() {
      const bool result =
        setString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedEvaporatorAirFlowRate, "autocalculate");
      OS_ASSERT(result);
    }

    boost::optional<double> CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::ratedCondenserWaterFlowRate() const {
      return getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedCondenserWaterFlowRate, true);
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::setRatedCondenserWaterFlowRate(double ratedCondenserWaterFlowRate) {
      return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedCondenserWaterFlowRate,
                       ratedCondenserWaterFlowRate);
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::isRatedCondenserWaterFlowRateAutocalculated() const {
      if (const auto value = getString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedCondenserWaterFlowRate, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    void CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::autocalculateRatedCondenserWaterFlowRate() {
      const bool result =
        setString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedCondenserWaterFlowRate, "autocalculate");
      OS_ASSERT(result);
    }

    std::string CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::evaporatorFanPowerIncludedinRatedCOP() const {
      const auto value = getString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::EvaporatorFanPowerIncludedinRatedCOP, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::setEvaporatorFanPowerIncludedinRatedCOP(
      const std::string& evaporatorFanPowerIncludedinRatedCOP) {
      return setString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::EvaporatorFanPowerIncludedinRatedCOP,
                       evaporatorFanPowerIncludedinRatedCOP);
    }

    std::string CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::condenserPumpPowerIncludedinRatedCOP() const {
      const auto value = getString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::CondenserPumpPowerIncludedinRatedCOP, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::setCondenserPumpPowerIncludedinRatedCOP(
      const std::string& condenserPumpPowerIncludedinRatedCOP) {
      return setString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::CondenserPumpPowerIncludedinRatedCOP,
                       condenserPumpPowerIncludedinRatedCOP);
    }

    std::string CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP() const {
      const auto value = getString(
        openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::CondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::setCondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP(
      const std::string& condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP) {
      return setString(
        openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::CondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP,
        condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP);
    }

    double CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::fractionofCondenserPumpHeattoWater() const {
      const auto value = getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::FractionofCondenserPumpHeattoWater, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::setFractionofCondenserPumpHeattoWater(double fractionofCondenserPumpHeattoWater) {
      return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::FractionofCondenserPumpHeattoWater,
                       fractionofCondenserPumpHeattoWater);
    }

    double CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::crankcaseHeaterCapacity() const {
      const auto value = getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::CrankcaseHeaterCapacity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity) {
      return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::CrankcaseHeaterCapacity, crankcaseHeaterCapacity);
    }

    double CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::maximumAmbientTemperatureforCrankcaseHeaterOperation() const {
      const auto value =
        getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::MaximumAmbientTemperatureforCrankcaseHeaterOperation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::setMaximumAmbientTemperatureforCrankcaseHeaterOperation(
      double maximumAmbientTemperatureforCrankcaseHeaterOperation) {
      return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::MaximumAmbientTemperatureforCrankcaseHeaterOperation,
                       maximumAmbientTemperatureforCrankcaseHeaterOperation);
    }

    std::string CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::evaporatorAirTemperatureTypeforCurveObjects() const {
      const auto value =
        getString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::EvaporatorAirTemperatureTypeforCurveObjects, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::setEvaporatorAirTemperatureTypeforCurveObjects(
      const std::string& evaporatorAirTemperatureTypeforCurveObjects) {
      return setString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::EvaporatorAirTemperatureTypeforCurveObjects,
                       evaporatorAirTemperatureTypeforCurveObjects);
    }

    std::vector<std::string> CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl::evaporatorAirTemperatureTypeforCurveObjectsValues() const {
      return openstudio::epmodel::CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::evaporatorAirTemperatureTypeforCurveObjectsValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
