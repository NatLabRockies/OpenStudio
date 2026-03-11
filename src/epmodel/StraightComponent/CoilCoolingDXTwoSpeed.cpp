/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilCoolingDXTwoSpeed.hpp"
#include "StraightComponent/CoilCoolingDXTwoSpeed_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "Model.hpp"
#include "Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Cooling_DX_TwoSpeed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

CoilCoolingDXTwoSpeed::CoilCoolingDXTwoSpeed(const Model& model) : StraightComponent(CoilCoolingDXTwoSpeed::iddObjectType(), model) {
  bool ok = true;

  autosizeRatedHighSpeedTotalCoolingCapacity();
  autosizeRatedHighSpeedSensibleHeatRatio();
  ok = setRatedHighSpeedCOP(3.0);
  OS_ASSERT(ok);
  autosizeRatedHighSpeedAirFlowRate();
  ok = setRatedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017(773.3);
  OS_ASSERT(ok);
  ok = setRatedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023(934.4);
  OS_ASSERT(ok);

  autosizeRatedLowSpeedTotalCoolingCapacity();
  ok = setRatedLowSpeedSensibleHeatRatio(0.69);
  OS_ASSERT(ok);
  ok = setRatedLowSpeedCOP(3.0);
  OS_ASSERT(ok);
  autosizeRatedLowSpeedAirFlowRate();
  ok = setRatedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017(773.3);
  OS_ASSERT(ok);
  ok = setRatedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023(934.4);
  OS_ASSERT(ok);

  ok = setCondenserType("AirCooled");
  OS_ASSERT(ok);

  ok = setHighSpeedEvaporativeCondenserEffectiveness(0.9);
  OS_ASSERT(ok);
  autosizeHighSpeedEvaporativeCondenserAirFlowRate();
  autosizeHighSpeedEvaporativeCondenserPumpRatedPowerConsumption();

  ok = setLowSpeedEvaporativeCondenserEffectiveness(0.9);
  OS_ASSERT(ok);
  autosizeLowSpeedEvaporativeCondenserAirFlowRate();
  autosizeLowSpeedEvaporativeCondenserPumpRatedPowerConsumption();

  ok = setBasinHeaterCapacity(0.0);
  OS_ASSERT(ok);
  ok = setBasinHeaterSetpointTemperature(2.0);
  OS_ASSERT(ok);

  ok = setMinimumOutdoorDryBulbTemperatureforCompressorOperation(-25.0);
  OS_ASSERT(ok);
  ok = setUnitInternalStaticAirPressure(773.3);
  OS_ASSERT(ok);
}

CoilCoolingDXTwoSpeed::CoilCoolingDXTwoSpeed(std::shared_ptr<detail::CoilCoolingDXTwoSpeed_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType CoilCoolingDXTwoSpeed::iddObjectType() {
  return IddObjectType::Coil_Cooling_DX_TwoSpeed;
}

std::vector<std::string> CoilCoolingDXTwoSpeed::condenserTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Coil_Cooling_DX_TwoSpeedFields::CondenserType);
}

#define EPMODEL_IMPL_FORWARD_0(ret, name) \
  ret CoilCoolingDXTwoSpeed::name() const { return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->name(); }
#define EPMODEL_IMPL_FORWARD_1(ret, name, t1, a1) \
  ret CoilCoolingDXTwoSpeed::name(t1 a1) { return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->name(a1); }
#define EPMODEL_IMPL_FORWARD_V(name) \
  void CoilCoolingDXTwoSpeed::name() { getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->name(); }

EPMODEL_IMPL_FORWARD_0(boost::optional<double>, ratedHighSpeedTotalCoolingCapacity)
EPMODEL_IMPL_FORWARD_0(bool, isRatedHighSpeedTotalCoolingCapacityAutosized)
EPMODEL_IMPL_FORWARD_1(bool, setRatedHighSpeedTotalCoolingCapacity, double, ratedHighSpeedTotalCoolingCapacity)
EPMODEL_IMPL_FORWARD_V(autosizeRatedHighSpeedTotalCoolingCapacity)

EPMODEL_IMPL_FORWARD_0(boost::optional<double>, ratedHighSpeedSensibleHeatRatio)
EPMODEL_IMPL_FORWARD_0(bool, isRatedHighSpeedSensibleHeatRatioAutosized)
EPMODEL_IMPL_FORWARD_1(bool, setRatedHighSpeedSensibleHeatRatio, double, ratedHighSpeedSensibleHeatRatio)
EPMODEL_IMPL_FORWARD_V(autosizeRatedHighSpeedSensibleHeatRatio)

EPMODEL_IMPL_FORWARD_0(double, ratedHighSpeedCOP)
EPMODEL_IMPL_FORWARD_1(bool, setRatedHighSpeedCOP, double, ratedHighSpeedCOP)

EPMODEL_IMPL_FORWARD_0(boost::optional<double>, ratedHighSpeedAirFlowRate)
EPMODEL_IMPL_FORWARD_0(bool, isRatedHighSpeedAirFlowRateAutosized)
EPMODEL_IMPL_FORWARD_1(bool, setRatedHighSpeedAirFlowRate, double, ratedHighSpeedAirFlowRate)
EPMODEL_IMPL_FORWARD_V(autosizeRatedHighSpeedAirFlowRate)

EPMODEL_IMPL_FORWARD_0(double, ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017)
EPMODEL_IMPL_FORWARD_1(bool, setRatedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017, double,
                       ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017)
EPMODEL_IMPL_FORWARD_0(double, ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023)
EPMODEL_IMPL_FORWARD_1(bool, setRatedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023, double,
                       ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023)

EPMODEL_IMPL_FORWARD_0(boost::optional<double>, ratedLowSpeedTotalCoolingCapacity)
EPMODEL_IMPL_FORWARD_0(bool, isRatedLowSpeedTotalCoolingCapacityAutosized)
EPMODEL_IMPL_FORWARD_1(bool, setRatedLowSpeedTotalCoolingCapacity, double, ratedLowSpeedTotalCoolingCapacity)
EPMODEL_IMPL_FORWARD_V(autosizeRatedLowSpeedTotalCoolingCapacity)

EPMODEL_IMPL_FORWARD_0(boost::optional<double>, ratedLowSpeedSensibleHeatRatio)
EPMODEL_IMPL_FORWARD_0(bool, isRatedLowSpeedSensibleHeatRatioAutosized)
EPMODEL_IMPL_FORWARD_1(bool, setRatedLowSpeedSensibleHeatRatio, double, ratedLowSpeedSensibleHeatRatio)
EPMODEL_IMPL_FORWARD_V(autosizeRatedLowSpeedSensibleHeatRatio)

EPMODEL_IMPL_FORWARD_0(double, ratedLowSpeedCOP)
EPMODEL_IMPL_FORWARD_1(bool, setRatedLowSpeedCOP, double, ratedLowSpeedCOP)

EPMODEL_IMPL_FORWARD_0(boost::optional<double>, ratedLowSpeedAirFlowRate)
EPMODEL_IMPL_FORWARD_0(bool, isRatedLowSpeedAirFlowRateAutosized)
EPMODEL_IMPL_FORWARD_1(bool, setRatedLowSpeedAirFlowRate, double, ratedLowSpeedAirFlowRate)
EPMODEL_IMPL_FORWARD_V(autosizeRatedLowSpeedAirFlowRate)

EPMODEL_IMPL_FORWARD_0(double, ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017)
EPMODEL_IMPL_FORWARD_1(bool, setRatedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017, double,
                       ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017)
EPMODEL_IMPL_FORWARD_0(double, ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023)
EPMODEL_IMPL_FORWARD_1(bool, setRatedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023, double,
                       ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023)

EPMODEL_IMPL_FORWARD_0(std::string, condenserType)
EPMODEL_IMPL_FORWARD_1(bool, setCondenserType, const std::string&, condenserType)

EPMODEL_IMPL_FORWARD_0(double, highSpeedEvaporativeCondenserEffectiveness)
EPMODEL_IMPL_FORWARD_1(bool, setHighSpeedEvaporativeCondenserEffectiveness, double, highSpeedEvaporativeCondenserEffectiveness)

EPMODEL_IMPL_FORWARD_0(boost::optional<double>, highSpeedEvaporativeCondenserAirFlowRate)
EPMODEL_IMPL_FORWARD_0(bool, isHighSpeedEvaporativeCondenserAirFlowRateAutosized)
EPMODEL_IMPL_FORWARD_1(bool, setHighSpeedEvaporativeCondenserAirFlowRate, double, highSpeedEvaporativeCondenserAirFlowRate)
EPMODEL_IMPL_FORWARD_V(autosizeHighSpeedEvaporativeCondenserAirFlowRate)

EPMODEL_IMPL_FORWARD_0(boost::optional<double>, highSpeedEvaporativeCondenserPumpRatedPowerConsumption)
EPMODEL_IMPL_FORWARD_0(bool, isHighSpeedEvaporativeCondenserPumpRatedPowerConsumptionAutosized)
EPMODEL_IMPL_FORWARD_1(bool, setHighSpeedEvaporativeCondenserPumpRatedPowerConsumption, double,
                       highSpeedEvaporativeCondenserPumpRatedPowerConsumption)
EPMODEL_IMPL_FORWARD_V(autosizeHighSpeedEvaporativeCondenserPumpRatedPowerConsumption)

EPMODEL_IMPL_FORWARD_0(double, lowSpeedEvaporativeCondenserEffectiveness)
EPMODEL_IMPL_FORWARD_1(bool, setLowSpeedEvaporativeCondenserEffectiveness, double, lowSpeedEvaporativeCondenserEffectiveness)

EPMODEL_IMPL_FORWARD_0(boost::optional<double>, lowSpeedEvaporativeCondenserAirFlowRate)
EPMODEL_IMPL_FORWARD_0(bool, isLowSpeedEvaporativeCondenserAirFlowRateAutosized)
EPMODEL_IMPL_FORWARD_1(bool, setLowSpeedEvaporativeCondenserAirFlowRate, double, lowSpeedEvaporativeCondenserAirFlowRate)
EPMODEL_IMPL_FORWARD_V(autosizeLowSpeedEvaporativeCondenserAirFlowRate)

EPMODEL_IMPL_FORWARD_0(boost::optional<double>, lowSpeedEvaporativeCondenserPumpRatedPowerConsumption)
EPMODEL_IMPL_FORWARD_0(bool, isLowSpeedEvaporativeCondenserPumpRatedPowerConsumptionAutosized)
EPMODEL_IMPL_FORWARD_1(bool, setLowSpeedEvaporativeCondenserPumpRatedPowerConsumption, double,
                       lowSpeedEvaporativeCondenserPumpRatedPowerConsumption)
EPMODEL_IMPL_FORWARD_V(autosizeLowSpeedEvaporativeCondenserPumpRatedPowerConsumption)

EPMODEL_IMPL_FORWARD_0(double, basinHeaterCapacity)
EPMODEL_IMPL_FORWARD_1(bool, setBasinHeaterCapacity, double, basinHeaterCapacity)
EPMODEL_IMPL_FORWARD_0(double, basinHeaterSetpointTemperature)
EPMODEL_IMPL_FORWARD_1(bool, setBasinHeaterSetpointTemperature, double, basinHeaterSetpointTemperature)

EPMODEL_IMPL_FORWARD_0(double, minimumOutdoorDryBulbTemperatureforCompressorOperation)
EPMODEL_IMPL_FORWARD_1(bool, setMinimumOutdoorDryBulbTemperatureforCompressorOperation, double,
                       minimumOutdoorDryBulbTemperatureforCompressorOperation)
EPMODEL_IMPL_FORWARD_0(double, unitInternalStaticAirPressure)
EPMODEL_IMPL_FORWARD_1(bool, setUnitInternalStaticAirPressure, double, unitInternalStaticAirPressure)

EPMODEL_IMPL_FORWARD_1(bool, addToNode, Node&, node)

#undef EPMODEL_IMPL_FORWARD_0
#undef EPMODEL_IMPL_FORWARD_1
#undef EPMODEL_IMPL_FORWARD_V

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

namespace {

bool isAutosized(const ModelObject_Impl& impl, int fieldIndex) {
  if (const auto value = impl.getString(fieldIndex, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

}  // namespace

unsigned CoilCoolingDXTwoSpeed_Impl::inletPort() const {
  return openstudio::Coil_Cooling_DX_TwoSpeedFields::AirInletNodeName;
}

unsigned CoilCoolingDXTwoSpeed_Impl::outletPort() const {
  return openstudio::Coil_Cooling_DX_TwoSpeedFields::AirOutletNodeName;
}

boost::optional<double> CoilCoolingDXTwoSpeed_Impl::ratedHighSpeedTotalCoolingCapacity() const {
  return getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedGrossRatedTotalCoolingCapacity, true);
}

bool CoilCoolingDXTwoSpeed_Impl::isRatedHighSpeedTotalCoolingCapacityAutosized() const {
  return isAutosized(*this, openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedGrossRatedTotalCoolingCapacity);
}

bool CoilCoolingDXTwoSpeed_Impl::setRatedHighSpeedTotalCoolingCapacity(double ratedHighSpeedTotalCoolingCapacity) {
  return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedGrossRatedTotalCoolingCapacity, ratedHighSpeedTotalCoolingCapacity);
}

void CoilCoolingDXTwoSpeed_Impl::autosizeRatedHighSpeedTotalCoolingCapacity() {
  const bool result = setString(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedGrossRatedTotalCoolingCapacity, "autosize");
  OS_ASSERT(result);
}

boost::optional<double> CoilCoolingDXTwoSpeed_Impl::ratedHighSpeedSensibleHeatRatio() const {
  return getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedRatedSensibleHeatRatio, true);
}

bool CoilCoolingDXTwoSpeed_Impl::isRatedHighSpeedSensibleHeatRatioAutosized() const {
  return isAutosized(*this, openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedRatedSensibleHeatRatio);
}

bool CoilCoolingDXTwoSpeed_Impl::setRatedHighSpeedSensibleHeatRatio(double ratedHighSpeedSensibleHeatRatio) {
  return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedRatedSensibleHeatRatio, ratedHighSpeedSensibleHeatRatio);
}

void CoilCoolingDXTwoSpeed_Impl::autosizeRatedHighSpeedSensibleHeatRatio() {
  const bool result = setString(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedRatedSensibleHeatRatio, "autosize");
  OS_ASSERT(result);
}

double CoilCoolingDXTwoSpeed_Impl::ratedHighSpeedCOP() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedGrossRatedCoolingCOP, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXTwoSpeed_Impl::setRatedHighSpeedCOP(double ratedHighSpeedCOP) {
  return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedGrossRatedCoolingCOP, ratedHighSpeedCOP);
}

boost::optional<double> CoilCoolingDXTwoSpeed_Impl::ratedHighSpeedAirFlowRate() const {
  return getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedRatedAirFlowRate, true);
}

bool CoilCoolingDXTwoSpeed_Impl::isRatedHighSpeedAirFlowRateAutosized() const {
  return isAutosized(*this, openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedRatedAirFlowRate);
}

bool CoilCoolingDXTwoSpeed_Impl::setRatedHighSpeedAirFlowRate(double ratedHighSpeedAirFlowRate) {
  return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedRatedAirFlowRate, ratedHighSpeedAirFlowRate);
}

void CoilCoolingDXTwoSpeed_Impl::autosizeRatedHighSpeedAirFlowRate() {
  const bool result = setString(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedRatedAirFlowRate, "autosize");
  OS_ASSERT(result);
}

double CoilCoolingDXTwoSpeed_Impl::ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedRatedEvaporatorFanPowerPerVolumeFlowRate2017, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXTwoSpeed_Impl::setRatedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017(
  double ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017) {
  return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedRatedEvaporatorFanPowerPerVolumeFlowRate2017,
                   ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017);
}

double CoilCoolingDXTwoSpeed_Impl::ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedRatedEvaporatorFanPowerPerVolumeFlowRate2023, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXTwoSpeed_Impl::setRatedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023(
  double ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023) {
  return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedRatedEvaporatorFanPowerPerVolumeFlowRate2023,
                   ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023);
}

boost::optional<double> CoilCoolingDXTwoSpeed_Impl::ratedLowSpeedTotalCoolingCapacity() const {
  return getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedGrossRatedTotalCoolingCapacity, true);
}

bool CoilCoolingDXTwoSpeed_Impl::isRatedLowSpeedTotalCoolingCapacityAutosized() const {
  return isAutosized(*this, openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedGrossRatedTotalCoolingCapacity);
}

bool CoilCoolingDXTwoSpeed_Impl::setRatedLowSpeedTotalCoolingCapacity(double ratedLowSpeedTotalCoolingCapacity) {
  return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedGrossRatedTotalCoolingCapacity, ratedLowSpeedTotalCoolingCapacity);
}

void CoilCoolingDXTwoSpeed_Impl::autosizeRatedLowSpeedTotalCoolingCapacity() {
  const bool result = setString(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedGrossRatedTotalCoolingCapacity, "autosize");
  OS_ASSERT(result);
}

boost::optional<double> CoilCoolingDXTwoSpeed_Impl::ratedLowSpeedSensibleHeatRatio() const {
  return getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedGrossRatedSensibleHeatRatio, true);
}

bool CoilCoolingDXTwoSpeed_Impl::isRatedLowSpeedSensibleHeatRatioAutosized() const {
  return isAutosized(*this, openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedGrossRatedSensibleHeatRatio);
}

bool CoilCoolingDXTwoSpeed_Impl::setRatedLowSpeedSensibleHeatRatio(double ratedLowSpeedSensibleHeatRatio) {
  return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedGrossRatedSensibleHeatRatio, ratedLowSpeedSensibleHeatRatio);
}

void CoilCoolingDXTwoSpeed_Impl::autosizeRatedLowSpeedSensibleHeatRatio() {
  const bool result = setString(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedGrossRatedSensibleHeatRatio, "autosize");
  OS_ASSERT(result);
}

double CoilCoolingDXTwoSpeed_Impl::ratedLowSpeedCOP() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedGrossRatedCoolingCOP, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXTwoSpeed_Impl::setRatedLowSpeedCOP(double ratedLowSpeedCOP) {
  return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedGrossRatedCoolingCOP, ratedLowSpeedCOP);
}

boost::optional<double> CoilCoolingDXTwoSpeed_Impl::ratedLowSpeedAirFlowRate() const {
  return getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedRatedAirFlowRate, true);
}

bool CoilCoolingDXTwoSpeed_Impl::isRatedLowSpeedAirFlowRateAutosized() const {
  return isAutosized(*this, openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedRatedAirFlowRate);
}

bool CoilCoolingDXTwoSpeed_Impl::setRatedLowSpeedAirFlowRate(double ratedLowSpeedAirFlowRate) {
  return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedRatedAirFlowRate, ratedLowSpeedAirFlowRate);
}

void CoilCoolingDXTwoSpeed_Impl::autosizeRatedLowSpeedAirFlowRate() {
  const bool result = setString(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedRatedAirFlowRate, "autosize");
  OS_ASSERT(result);
}

double CoilCoolingDXTwoSpeed_Impl::ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedRatedEvaporatorFanPowerPerVolumeFlowRate2017, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXTwoSpeed_Impl::setRatedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017(
  double ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017) {
  return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedRatedEvaporatorFanPowerPerVolumeFlowRate2017,
                   ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017);
}

double CoilCoolingDXTwoSpeed_Impl::ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedRatedEvaporatorFanPowerPerVolumeFlowRate2023, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXTwoSpeed_Impl::setRatedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023(
  double ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023) {
  return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedRatedEvaporatorFanPowerPerVolumeFlowRate2023,
                   ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023);
}

std::vector<std::string> CoilCoolingDXTwoSpeed_Impl::condenserTypeValues() const {
  return CoilCoolingDXTwoSpeed::condenserTypeValues();
}

std::string CoilCoolingDXTwoSpeed_Impl::condenserType() const {
  const auto value = getString(openstudio::Coil_Cooling_DX_TwoSpeedFields::CondenserType, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXTwoSpeed_Impl::setCondenserType(const std::string& condenserType) {
  return setString(openstudio::Coil_Cooling_DX_TwoSpeedFields::CondenserType, condenserType);
}

double CoilCoolingDXTwoSpeed_Impl::highSpeedEvaporativeCondenserEffectiveness() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedEvaporativeCondenserEffectiveness, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXTwoSpeed_Impl::setHighSpeedEvaporativeCondenserEffectiveness(double highSpeedEvaporativeCondenserEffectiveness) {
  return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedEvaporativeCondenserEffectiveness,
                   highSpeedEvaporativeCondenserEffectiveness);
}

boost::optional<double> CoilCoolingDXTwoSpeed_Impl::highSpeedEvaporativeCondenserAirFlowRate() const {
  return getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedEvaporativeCondenserAirFlowRate, true);
}

bool CoilCoolingDXTwoSpeed_Impl::isHighSpeedEvaporativeCondenserAirFlowRateAutosized() const {
  return isAutosized(*this, openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedEvaporativeCondenserAirFlowRate);
}

bool CoilCoolingDXTwoSpeed_Impl::setHighSpeedEvaporativeCondenserAirFlowRate(double highSpeedEvaporativeCondenserAirFlowRate) {
  return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedEvaporativeCondenserAirFlowRate,
                   highSpeedEvaporativeCondenserAirFlowRate);
}

void CoilCoolingDXTwoSpeed_Impl::autosizeHighSpeedEvaporativeCondenserAirFlowRate() {
  const bool result = setString(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedEvaporativeCondenserAirFlowRate, "autosize");
  OS_ASSERT(result);
}

boost::optional<double> CoilCoolingDXTwoSpeed_Impl::highSpeedEvaporativeCondenserPumpRatedPowerConsumption() const {
  return getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedEvaporativeCondenserPumpRatedPowerConsumption, true);
}

bool CoilCoolingDXTwoSpeed_Impl::isHighSpeedEvaporativeCondenserPumpRatedPowerConsumptionAutosized() const {
  return isAutosized(*this, openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedEvaporativeCondenserPumpRatedPowerConsumption);
}

bool CoilCoolingDXTwoSpeed_Impl::setHighSpeedEvaporativeCondenserPumpRatedPowerConsumption(
  double highSpeedEvaporativeCondenserPumpRatedPowerConsumption) {
  return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedEvaporativeCondenserPumpRatedPowerConsumption,
                   highSpeedEvaporativeCondenserPumpRatedPowerConsumption);
}

void CoilCoolingDXTwoSpeed_Impl::autosizeHighSpeedEvaporativeCondenserPumpRatedPowerConsumption() {
  const bool result =
    setString(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedEvaporativeCondenserPumpRatedPowerConsumption, "autosize");
  OS_ASSERT(result);
}

double CoilCoolingDXTwoSpeed_Impl::lowSpeedEvaporativeCondenserEffectiveness() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedEvaporativeCondenserEffectiveness, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXTwoSpeed_Impl::setLowSpeedEvaporativeCondenserEffectiveness(double lowSpeedEvaporativeCondenserEffectiveness) {
  return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedEvaporativeCondenserEffectiveness,
                   lowSpeedEvaporativeCondenserEffectiveness);
}

boost::optional<double> CoilCoolingDXTwoSpeed_Impl::lowSpeedEvaporativeCondenserAirFlowRate() const {
  return getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedEvaporativeCondenserAirFlowRate, true);
}

bool CoilCoolingDXTwoSpeed_Impl::isLowSpeedEvaporativeCondenserAirFlowRateAutosized() const {
  return isAutosized(*this, openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedEvaporativeCondenserAirFlowRate);
}

bool CoilCoolingDXTwoSpeed_Impl::setLowSpeedEvaporativeCondenserAirFlowRate(double lowSpeedEvaporativeCondenserAirFlowRate) {
  return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedEvaporativeCondenserAirFlowRate, lowSpeedEvaporativeCondenserAirFlowRate);
}

void CoilCoolingDXTwoSpeed_Impl::autosizeLowSpeedEvaporativeCondenserAirFlowRate() {
  const bool result = setString(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedEvaporativeCondenserAirFlowRate, "autosize");
  OS_ASSERT(result);
}

boost::optional<double> CoilCoolingDXTwoSpeed_Impl::lowSpeedEvaporativeCondenserPumpRatedPowerConsumption() const {
  return getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedEvaporativeCondenserPumpRatedPowerConsumption, true);
}

bool CoilCoolingDXTwoSpeed_Impl::isLowSpeedEvaporativeCondenserPumpRatedPowerConsumptionAutosized() const {
  return isAutosized(*this, openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedEvaporativeCondenserPumpRatedPowerConsumption);
}

bool CoilCoolingDXTwoSpeed_Impl::setLowSpeedEvaporativeCondenserPumpRatedPowerConsumption(
  double lowSpeedEvaporativeCondenserPumpRatedPowerConsumption) {
  return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedEvaporativeCondenserPumpRatedPowerConsumption,
                   lowSpeedEvaporativeCondenserPumpRatedPowerConsumption);
}

void CoilCoolingDXTwoSpeed_Impl::autosizeLowSpeedEvaporativeCondenserPumpRatedPowerConsumption() {
  const bool result =
    setString(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedEvaporativeCondenserPumpRatedPowerConsumption, "autosize");
  OS_ASSERT(result);
}

double CoilCoolingDXTwoSpeed_Impl::basinHeaterCapacity() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::BasinHeaterCapacity, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXTwoSpeed_Impl::setBasinHeaterCapacity(double basinHeaterCapacity) {
  return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::BasinHeaterCapacity, basinHeaterCapacity);
}

double CoilCoolingDXTwoSpeed_Impl::basinHeaterSetpointTemperature() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::BasinHeaterSetpointTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXTwoSpeed_Impl::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
  return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::BasinHeaterSetpointTemperature, basinHeaterSetpointTemperature);
}

double CoilCoolingDXTwoSpeed_Impl::minimumOutdoorDryBulbTemperatureforCompressorOperation() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXTwoSpeed_Impl::setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
  double minimumOutdoorDryBulbTemperatureforCompressorOperation) {
  return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation,
                   minimumOutdoorDryBulbTemperatureforCompressorOperation);
}

double CoilCoolingDXTwoSpeed_Impl::unitInternalStaticAirPressure() const {
  const auto value = getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::UnitInternalStaticAirPressure, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXTwoSpeed_Impl::setUnitInternalStaticAirPressure(double unitInternalStaticAirPressure) {
  return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::UnitInternalStaticAirPressure, unitInternalStaticAirPressure);
}

bool CoilCoolingDXTwoSpeed_Impl::addToNode(Node& node) {
  if (auto airLoop = node.airLoopHVAC()) {
    if (!airLoop->demandComponent(node.handle())) {
      return StraightComponent_Impl::addToNode(node);
    }
    return false;
  }

  if (node.airLoopHVACOutdoorAirSystem()) {
    // openstudio::model allows some OA-system contexts only when the OA system
    // is attached to an AirLoopHVACDedicatedOutdoorAirSystem. epmodel does not
    // yet model that object, so keep this unsupported and explicit.
    return false;
  }

  return false;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
