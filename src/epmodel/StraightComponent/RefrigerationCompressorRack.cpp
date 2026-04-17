/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/RefrigerationCompressorRack.hpp"
#include "StraightComponent/RefrigerationCompressorRack_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/CurveQuadratic.hpp"
#include "Curve/Curve_Impl.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Loop/PlantLoop.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"

#include "../utilities/core/Assert.hpp"
#include "../utilities/core/StringHelpers.hpp"
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Refrigeration_CompressorRack_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  RefrigerationCompressorRack::RefrigerationCompressorRack(const Model& model)
    : StraightComponent(RefrigerationCompressorRack::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::RefrigerationCompressorRack_Impl>());

    CurveQuadratic compressorRackCOPFunctionofTemperatureCurve(model);
    OS_ASSERT(compressorRackCOPFunctionofTemperatureCurve.setCoefficient1Constant(1.7603));
    OS_ASSERT(compressorRackCOPFunctionofTemperatureCurve.setCoefficient2x(-0.0377));
    OS_ASSERT(compressorRackCOPFunctionofTemperatureCurve.setCoefficient3xPOW2(0.0004));
    OS_ASSERT(compressorRackCOPFunctionofTemperatureCurve.setMinimumValueofx(10.0));
    OS_ASSERT(compressorRackCOPFunctionofTemperatureCurve.setMaximumValueofx(35.0));

    OS_ASSERT(setHeatRejectionLocation("Outdoors"));
    OS_ASSERT(setDesignCompressorRackCOP(2.0));
    OS_ASSERT(setCompressorRackCOPFunctionofTemperatureCurve(compressorRackCOPFunctionofTemperatureCurve));
    OS_ASSERT(setDesignCondenserFanPower(250.0));
    OS_ASSERT(setCondenserType("AirCooled"));
    OS_ASSERT(setWaterCooledLoopFlowType("VariableFlow"));
    OS_ASSERT(setWaterCooledCondenserMaximumWaterOutletTemperature(55.0));
    OS_ASSERT(setWaterCooledCondenserMinimumWaterInletTemperature(10.0));
    OS_ASSERT(setEvaporativeCondenserEffectiveness(0.9));
    OS_ASSERT(autocalculateEvaporativeCondenserAirFlowRate());
    OS_ASSERT(setBasinHeaterCapacity(200.0));
    OS_ASSERT(setBasinHeaterSetpointTemperature(2.0));
    OS_ASSERT(setDesignEvaporativeCondenserWaterPumpPower(1000.0));
  }

  RefrigerationCompressorRack::RefrigerationCompressorRack(std::shared_ptr<detail::RefrigerationCompressorRack_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType RefrigerationCompressorRack::iddObjectType() {
    return IddObjectType::Refrigeration_CompressorRack;
  }

  std::vector<std::string> RefrigerationCompressorRack::condenserTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Refrigeration_CompressorRackFields::CondenserType);
  }

  std::vector<std::string> RefrigerationCompressorRack::waterCooledLoopFlowTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Refrigeration_CompressorRackFields::WaterCooledLoopFlowType);
  }

  std::string RefrigerationCompressorRack::heatRejectionLocation() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->heatRejectionLocation();
  }

  bool RefrigerationCompressorRack::setHeatRejectionLocation(const std::string& heatRejectionLocation) {
    bool result = getImpl<detail::RefrigerationCompressorRack_Impl>()->setHeatRejectionLocation(heatRejectionLocation);
    OS_ASSERT(result);
    return result;
  }

  double RefrigerationCompressorRack::designCompressorRackCOP() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->designCompressorRackCOP();
  }

  bool RefrigerationCompressorRack::setDesignCompressorRackCOP(double designCompressorRackCOP) {
    bool result = getImpl<detail::RefrigerationCompressorRack_Impl>()->setDesignCompressorRackCOP(designCompressorRackCOP);
    OS_ASSERT(result);
    return result;
  }

  Curve RefrigerationCompressorRack::compressorRackCOPFunctionofTemperatureCurve() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->compressorRackCOPFunctionofTemperatureCurve();
  }

  bool RefrigerationCompressorRack::setCompressorRackCOPFunctionofTemperatureCurve(const Curve& curve) {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->setCompressorRackCOPFunctionofTemperatureCurve(curve);
  }

  double RefrigerationCompressorRack::designCondenserFanPower() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->designCondenserFanPower();
  }

  bool RefrigerationCompressorRack::setDesignCondenserFanPower(double designCondenserFanPower) {
    bool result = getImpl<detail::RefrigerationCompressorRack_Impl>()->setDesignCondenserFanPower(designCondenserFanPower);
    OS_ASSERT(result);
    return result;
  }

  boost::optional<Curve> RefrigerationCompressorRack::condenserFanPowerFunctionofTemperatureCurve() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->condenserFanPowerFunctionofTemperatureCurve();
  }

  bool RefrigerationCompressorRack::setCondenserFanPowerFunctionofTemperatureCurve(const Curve& curve) {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->setCondenserFanPowerFunctionofTemperatureCurve(curve);
  }

  void RefrigerationCompressorRack::resetCondenserFanPowerFunctionofTemperatureCurve() {
    getImpl<detail::RefrigerationCompressorRack_Impl>()->resetCondenserFanPowerFunctionofTemperatureCurve();
  }

  std::string RefrigerationCompressorRack::condenserType() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->condenserType();
  }

  bool RefrigerationCompressorRack::setCondenserType(const std::string& condenserType) {
    bool result = getImpl<detail::RefrigerationCompressorRack_Impl>()->setCondenserType(condenserType);
    OS_ASSERT(result);
    return result;
  }

  std::string RefrigerationCompressorRack::waterCooledLoopFlowType() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->waterCooledLoopFlowType();
  }

  bool RefrigerationCompressorRack::setWaterCooledLoopFlowType(const std::string& waterCooledLoopFlowType) {
    bool result = getImpl<detail::RefrigerationCompressorRack_Impl>()->setWaterCooledLoopFlowType(waterCooledLoopFlowType);
    OS_ASSERT(result);
    return result;
  }

  boost::optional<Schedule> RefrigerationCompressorRack::waterCooledCondenserOutletTemperatureSchedule() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->waterCooledCondenserOutletTemperatureSchedule();
  }

  bool RefrigerationCompressorRack::setWaterCooledCondenserOutletTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->setWaterCooledCondenserOutletTemperatureSchedule(schedule);
  }

  void RefrigerationCompressorRack::resetWaterCooledCondenserOutletTemperatureSchedule() {
    getImpl<detail::RefrigerationCompressorRack_Impl>()->resetWaterCooledCondenserOutletTemperatureSchedule();
  }

  boost::optional<double> RefrigerationCompressorRack::waterCooledCondenserDesignFlowRate() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->waterCooledCondenserDesignFlowRate();
  }

  bool RefrigerationCompressorRack::setWaterCooledCondenserDesignFlowRate(double waterCooledCondenserDesignFlowRate) {
    bool result = getImpl<detail::RefrigerationCompressorRack_Impl>()->setWaterCooledCondenserDesignFlowRate(waterCooledCondenserDesignFlowRate);
    OS_ASSERT(result);
    return result;
  }

  void RefrigerationCompressorRack::resetWaterCooledCondenserDesignFlowRate() {
    getImpl<detail::RefrigerationCompressorRack_Impl>()->resetWaterCooledCondenserDesignFlowRate();
  }

  boost::optional<double> RefrigerationCompressorRack::waterCooledCondenserMaximumFlowRate() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->waterCooledCondenserMaximumFlowRate();
  }

  bool RefrigerationCompressorRack::setWaterCooledCondenserMaximumFlowRate(double waterCooledCondenserMaximumFlowRate) {
    bool result = getImpl<detail::RefrigerationCompressorRack_Impl>()->setWaterCooledCondenserMaximumFlowRate(waterCooledCondenserMaximumFlowRate);
    OS_ASSERT(result);
    return result;
  }

  void RefrigerationCompressorRack::resetWaterCooledCondenserMaximumFlowRate() {
    getImpl<detail::RefrigerationCompressorRack_Impl>()->resetWaterCooledCondenserMaximumFlowRate();
  }

  double RefrigerationCompressorRack::waterCooledCondenserMaximumWaterOutletTemperature() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->waterCooledCondenserMaximumWaterOutletTemperature();
  }

  bool RefrigerationCompressorRack::setWaterCooledCondenserMaximumWaterOutletTemperature(double waterCooledCondenserMaximumWaterOutletTemperature) {
    bool result = getImpl<detail::RefrigerationCompressorRack_Impl>()->setWaterCooledCondenserMaximumWaterOutletTemperature(
      waterCooledCondenserMaximumWaterOutletTemperature);
    OS_ASSERT(result);
    return result;
  }

  double RefrigerationCompressorRack::waterCooledCondenserMinimumWaterInletTemperature() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->waterCooledCondenserMinimumWaterInletTemperature();
  }

  bool RefrigerationCompressorRack::setWaterCooledCondenserMinimumWaterInletTemperature(double waterCooledCondenserMinimumWaterInletTemperature) {
    bool result = getImpl<detail::RefrigerationCompressorRack_Impl>()->setWaterCooledCondenserMinimumWaterInletTemperature(
      waterCooledCondenserMinimumWaterInletTemperature);
    OS_ASSERT(result);
    return result;
  }

  boost::optional<Schedule> RefrigerationCompressorRack::evaporativeCondenserAvailabilitySchedule() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->evaporativeCondenserAvailabilitySchedule();
  }

  bool RefrigerationCompressorRack::setEvaporativeCondenserAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->setEvaporativeCondenserAvailabilitySchedule(schedule);
  }

  void RefrigerationCompressorRack::resetEvaporativeCondenserAvailabilitySchedule() {
    getImpl<detail::RefrigerationCompressorRack_Impl>()->resetEvaporativeCondenserAvailabilitySchedule();
  }

  double RefrigerationCompressorRack::evaporativeCondenserEffectiveness() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->evaporativeCondenserEffectiveness();
  }

  bool RefrigerationCompressorRack::setEvaporativeCondenserEffectiveness(double evaporativeCondenserEffectiveness) {
    bool result = getImpl<detail::RefrigerationCompressorRack_Impl>()->setEvaporativeCondenserEffectiveness(evaporativeCondenserEffectiveness);
    OS_ASSERT(result);
    return result;
  }

  boost::optional<double> RefrigerationCompressorRack::evaporativeCondenserAirFlowRate() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->evaporativeCondenserAirFlowRate();
  }

  bool RefrigerationCompressorRack::setEvaporativeCondenserAirFlowRate(double evaporativeCondenserAirFlowRate) {
    bool result = getImpl<detail::RefrigerationCompressorRack_Impl>()->setEvaporativeCondenserAirFlowRate(evaporativeCondenserAirFlowRate);
    OS_ASSERT(result);
    return result;
  }

  bool RefrigerationCompressorRack::isEvaporativeCondenserAirFlowRateAutocalculated() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->isEvaporativeCondenserAirFlowRateAutocalculated();
  }

  bool RefrigerationCompressorRack::autocalculateEvaporativeCondenserAirFlowRate() {
    bool result = getImpl<detail::RefrigerationCompressorRack_Impl>()->autocalculateEvaporativeCondenserAirFlowRate();
    OS_ASSERT(result);
    return result;
  }

  double RefrigerationCompressorRack::basinHeaterCapacity() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->basinHeaterCapacity();
  }

  bool RefrigerationCompressorRack::setBasinHeaterCapacity(double basinHeaterCapacity) {
    bool result = getImpl<detail::RefrigerationCompressorRack_Impl>()->setBasinHeaterCapacity(basinHeaterCapacity);
    OS_ASSERT(result);
    return result;
  }

  double RefrigerationCompressorRack::basinHeaterSetpointTemperature() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->basinHeaterSetpointTemperature();
  }

  bool RefrigerationCompressorRack::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
    bool result = getImpl<detail::RefrigerationCompressorRack_Impl>()->setBasinHeaterSetpointTemperature(basinHeaterSetpointTemperature);
    OS_ASSERT(result);
    return result;
  }

  boost::optional<double> RefrigerationCompressorRack::designEvaporativeCondenserWaterPumpPower() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->designEvaporativeCondenserWaterPumpPower();
  }

  bool RefrigerationCompressorRack::setDesignEvaporativeCondenserWaterPumpPower(double designEvaporativeCondenserWaterPumpPower) {
    bool result =
      getImpl<detail::RefrigerationCompressorRack_Impl>()->setDesignEvaporativeCondenserWaterPumpPower(designEvaporativeCondenserWaterPumpPower);
    OS_ASSERT(result);
    return result;
  }

  bool RefrigerationCompressorRack::isDesignEvaporativeCondenserWaterPumpPowerAutocalculated() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->isDesignEvaporativeCondenserWaterPumpPowerAutocalculated();
  }

  bool RefrigerationCompressorRack::autocalculateDesignEvaporativeCondenserWaterPumpPower() {
    bool result = getImpl<detail::RefrigerationCompressorRack_Impl>()->autocalculateDesignEvaporativeCondenserWaterPumpPower();
    OS_ASSERT(result);
    return result;
  }

  std::string RefrigerationCompressorRack::endUseSubcategory() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->endUseSubcategory();
  }

  bool RefrigerationCompressorRack::isEndUseSubcategoryDefaulted() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->isEndUseSubcategoryDefaulted();
  }

  bool RefrigerationCompressorRack::setEndUseSubcategory(const std::string& endUseSubcategory) {
    bool result = getImpl<detail::RefrigerationCompressorRack_Impl>()->setEndUseSubcategory(endUseSubcategory);
    OS_ASSERT(result);
    return result;
  }

  void RefrigerationCompressorRack::resetEndUseSubcategory() {
    getImpl<detail::RefrigerationCompressorRack_Impl>()->resetEndUseSubcategory();
  }

  boost::optional<ThermalZone> RefrigerationCompressorRack::heatRejectionZone() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->heatRejectionZone();
  }

  bool RefrigerationCompressorRack::setHeatRejectionZone(const ThermalZone& thermalZone) {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->setHeatRejectionZone(thermalZone);
  }

  void RefrigerationCompressorRack::resetHeatRejectionZone() {
    getImpl<detail::RefrigerationCompressorRack_Impl>()->resetHeatRejectionZone();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned RefrigerationCompressorRack_Impl::inletPort() const {
      return openstudio::Refrigeration_CompressorRackFields::WaterCooledCondenserInletNodeName;
    }

    unsigned RefrigerationCompressorRack_Impl::outletPort() const {
      return openstudio::Refrigeration_CompressorRackFields::WaterCooledCondenserOutletNodeName;
    }

    bool RefrigerationCompressorRack_Impl::addToNode(Node& node) {
      if (auto plantLoop = node.plantLoop()) {
        if (plantLoop->demandComponent(node.handle())) {
          return StraightComponent_Impl::addToNode(node);
        }
      }

      return false;
    }

    std::vector<ModelObject> RefrigerationCompressorRack_Impl::children() const {
      std::vector<ModelObject> result;
      result.push_back(compressorRackCOPFunctionofTemperatureCurve());
      if (auto curve = condenserFanPowerFunctionofTemperatureCurve()) {
        result.push_back(*curve);
      }
      return result;
    }

    std::vector<IdfObject> RefrigerationCompressorRack_Impl::remove() {
      auto compressorCurve = getObject<ModelObject>().getModelObjectTarget<Curve>(openstudio::Refrigeration_CompressorRackFields::CompressorRackCOPFunctionofTemperatureCurveName);
      auto fanCurve = condenserFanPowerFunctionofTemperatureCurve();
      auto result = StraightComponent_Impl::remove();
      if (!result.empty()) {
        if (compressorCurve) {
          compressorCurve->remove();
        }
        if (fanCurve && (!compressorCurve || (fanCurve->handle() != compressorCurve->handle()))) {
          fanCurve->remove();
        }
      }
      return result;
    }

    std::string RefrigerationCompressorRack_Impl::heatRejectionLocation() const {
      boost::optional<std::string> value = getString(openstudio::Refrigeration_CompressorRackFields::HeatRejectionLocation, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCompressorRack_Impl::setHeatRejectionLocation(const std::string& heatRejectionLocation) {
      bool result = setString(openstudio::Refrigeration_CompressorRackFields::HeatRejectionLocation, heatRejectionLocation);
      OS_ASSERT(result);
      return result;
    }

    double RefrigerationCompressorRack_Impl::designCompressorRackCOP() const {
      boost::optional<double> value = getDouble(openstudio::Refrigeration_CompressorRackFields::DesignCompressorRackCOP, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCompressorRack_Impl::setDesignCompressorRackCOP(double designCompressorRackCOP) {
      bool result = setDouble(openstudio::Refrigeration_CompressorRackFields::DesignCompressorRackCOP, designCompressorRackCOP);
      OS_ASSERT(result);
      return result;
    }

    Curve RefrigerationCompressorRack_Impl::compressorRackCOPFunctionofTemperatureCurve() const {
      auto curve = getObject<ModelObject>().getModelObjectTarget<Curve>(openstudio::Refrigeration_CompressorRackFields::CompressorRackCOPFunctionofTemperatureCurveName);
      OS_ASSERT(curve);
      return *curve;
    }

    bool RefrigerationCompressorRack_Impl::setCompressorRackCOPFunctionofTemperatureCurve(const Curve& curve) {
      bool result = setPointer(openstudio::Refrigeration_CompressorRackFields::CompressorRackCOPFunctionofTemperatureCurveName, curve.handle());
      OS_ASSERT(result);
      return result;
    }

    double RefrigerationCompressorRack_Impl::designCondenserFanPower() const {
      boost::optional<double> value = getDouble(openstudio::Refrigeration_CompressorRackFields::DesignCondenserFanPower, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCompressorRack_Impl::setDesignCondenserFanPower(double designCondenserFanPower) {
      bool result = setDouble(openstudio::Refrigeration_CompressorRackFields::DesignCondenserFanPower, designCondenserFanPower);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<Curve> RefrigerationCompressorRack_Impl::condenserFanPowerFunctionofTemperatureCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(openstudio::Refrigeration_CompressorRackFields::CondenserFanPowerFunctionofTemperatureCurveName);
    }

    bool RefrigerationCompressorRack_Impl::setCondenserFanPowerFunctionofTemperatureCurve(const Curve& curve) {
      bool result = setPointer(openstudio::Refrigeration_CompressorRackFields::CondenserFanPowerFunctionofTemperatureCurveName, curve.handle());
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationCompressorRack_Impl::resetCondenserFanPowerFunctionofTemperatureCurve() {
      bool result = setString(openstudio::Refrigeration_CompressorRackFields::CondenserFanPowerFunctionofTemperatureCurveName, "");
      OS_ASSERT(result);
    }

    std::string RefrigerationCompressorRack_Impl::condenserType() const {
      boost::optional<std::string> value = getString(openstudio::Refrigeration_CompressorRackFields::CondenserType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCompressorRack_Impl::setCondenserType(const std::string& condenserType) {
      bool result = setString(openstudio::Refrigeration_CompressorRackFields::CondenserType, condenserType);
      OS_ASSERT(result);
      return result;
    }

    std::string RefrigerationCompressorRack_Impl::waterCooledLoopFlowType() const {
      boost::optional<std::string> value = getString(openstudio::Refrigeration_CompressorRackFields::WaterCooledLoopFlowType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCompressorRack_Impl::setWaterCooledLoopFlowType(const std::string& waterCooledLoopFlowType) {
      bool result = setString(openstudio::Refrigeration_CompressorRackFields::WaterCooledLoopFlowType, waterCooledLoopFlowType);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<Schedule> RefrigerationCompressorRack_Impl::waterCooledCondenserOutletTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::Refrigeration_CompressorRackFields::WaterCooledCondenserOutletTemperatureScheduleName);
    }

    bool RefrigerationCompressorRack_Impl::setWaterCooledCondenserOutletTemperatureSchedule(Schedule& schedule) {
      return setSchedule(openstudio::Refrigeration_CompressorRackFields::WaterCooledCondenserOutletTemperatureScheduleName,
                         "RefrigerationCompressorRack", "Water Cooled Condenser Outlet Temperature", schedule);
    }

    void RefrigerationCompressorRack_Impl::resetWaterCooledCondenserOutletTemperatureSchedule() {
      bool result = setString(openstudio::Refrigeration_CompressorRackFields::WaterCooledCondenserOutletTemperatureScheduleName, "");
      OS_ASSERT(result);
    }

    boost::optional<double> RefrigerationCompressorRack_Impl::waterCooledCondenserDesignFlowRate() const {
      return getDouble(openstudio::Refrigeration_CompressorRackFields::WaterCooledCondenserDesignFlowRate, true);
    }

    bool RefrigerationCompressorRack_Impl::setWaterCooledCondenserDesignFlowRate(double waterCooledCondenserDesignFlowRate) {
      bool result = setDouble(openstudio::Refrigeration_CompressorRackFields::WaterCooledCondenserDesignFlowRate, waterCooledCondenserDesignFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationCompressorRack_Impl::resetWaterCooledCondenserDesignFlowRate() {
      bool result = setString(openstudio::Refrigeration_CompressorRackFields::WaterCooledCondenserDesignFlowRate, "");
      OS_ASSERT(result);
    }

    boost::optional<double> RefrigerationCompressorRack_Impl::waterCooledCondenserMaximumFlowRate() const {
      return getDouble(openstudio::Refrigeration_CompressorRackFields::WaterCooledCondenserMaximumFlowRate, true);
    }

    bool RefrigerationCompressorRack_Impl::setWaterCooledCondenserMaximumFlowRate(double waterCooledCondenserMaximumFlowRate) {
      bool result =
        setDouble(openstudio::Refrigeration_CompressorRackFields::WaterCooledCondenserMaximumFlowRate, waterCooledCondenserMaximumFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationCompressorRack_Impl::resetWaterCooledCondenserMaximumFlowRate() {
      bool result = setString(openstudio::Refrigeration_CompressorRackFields::WaterCooledCondenserMaximumFlowRate, "");
      OS_ASSERT(result);
    }

    double RefrigerationCompressorRack_Impl::waterCooledCondenserMaximumWaterOutletTemperature() const {
      boost::optional<double> value = getDouble(openstudio::Refrigeration_CompressorRackFields::WaterCooledCondenserMaximumWaterOutletTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCompressorRack_Impl::setWaterCooledCondenserMaximumWaterOutletTemperature(
      double waterCooledCondenserMaximumWaterOutletTemperature) {
      bool result = setDouble(openstudio::Refrigeration_CompressorRackFields::WaterCooledCondenserMaximumWaterOutletTemperature,
                              waterCooledCondenserMaximumWaterOutletTemperature);
      OS_ASSERT(result);
      return result;
    }

    double RefrigerationCompressorRack_Impl::waterCooledCondenserMinimumWaterInletTemperature() const {
      boost::optional<double> value = getDouble(openstudio::Refrigeration_CompressorRackFields::WaterCooledCondenserMinimumWaterInletTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCompressorRack_Impl::setWaterCooledCondenserMinimumWaterInletTemperature(double waterCooledCondenserMinimumWaterInletTemperature) {
      bool result = setDouble(openstudio::Refrigeration_CompressorRackFields::WaterCooledCondenserMinimumWaterInletTemperature,
                              waterCooledCondenserMinimumWaterInletTemperature);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<Schedule> RefrigerationCompressorRack_Impl::evaporativeCondenserAvailabilitySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::Refrigeration_CompressorRackFields::EvaporativeCondenserAvailabilityScheduleName);
    }

    bool RefrigerationCompressorRack_Impl::setEvaporativeCondenserAvailabilitySchedule(Schedule& schedule) {
      return setSchedule(openstudio::Refrigeration_CompressorRackFields::EvaporativeCondenserAvailabilityScheduleName,
                         "RefrigerationCompressorRack", "Evaporative Condenser Availability", schedule);
    }

    void RefrigerationCompressorRack_Impl::resetEvaporativeCondenserAvailabilitySchedule() {
      bool result = setString(openstudio::Refrigeration_CompressorRackFields::EvaporativeCondenserAvailabilityScheduleName, "");
      OS_ASSERT(result);
    }

    double RefrigerationCompressorRack_Impl::evaporativeCondenserEffectiveness() const {
      boost::optional<double> value = getDouble(openstudio::Refrigeration_CompressorRackFields::EvaporativeCondenserEffectiveness, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCompressorRack_Impl::setEvaporativeCondenserEffectiveness(double evaporativeCondenserEffectiveness) {
      bool result = setDouble(openstudio::Refrigeration_CompressorRackFields::EvaporativeCondenserEffectiveness, evaporativeCondenserEffectiveness);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> RefrigerationCompressorRack_Impl::evaporativeCondenserAirFlowRate() const {
      return getDouble(openstudio::Refrigeration_CompressorRackFields::EvaporativeCondenserAirFlowRate, true);
    }

    bool RefrigerationCompressorRack_Impl::isEvaporativeCondenserAirFlowRateAutocalculated() const {
      bool result = false;
      boost::optional<std::string> value = getString(openstudio::Refrigeration_CompressorRackFields::EvaporativeCondenserAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autocalculate");
      }
      return result;
    }

    bool RefrigerationCompressorRack_Impl::setEvaporativeCondenserAirFlowRate(double evaporativeCondenserAirFlowRate) {
      bool result = setDouble(openstudio::Refrigeration_CompressorRackFields::EvaporativeCondenserAirFlowRate, evaporativeCondenserAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    bool RefrigerationCompressorRack_Impl::autocalculateEvaporativeCondenserAirFlowRate() {
      bool result = setString(openstudio::Refrigeration_CompressorRackFields::EvaporativeCondenserAirFlowRate, "Autocalculate");
      OS_ASSERT(result);
      return result;
    }

    double RefrigerationCompressorRack_Impl::basinHeaterCapacity() const {
      boost::optional<double> value = getDouble(openstudio::Refrigeration_CompressorRackFields::BasinHeaterCapacity, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCompressorRack_Impl::setBasinHeaterCapacity(double basinHeaterCapacity) {
      bool result = setDouble(openstudio::Refrigeration_CompressorRackFields::BasinHeaterCapacity, basinHeaterCapacity);
      OS_ASSERT(result);
      return result;
    }

    double RefrigerationCompressorRack_Impl::basinHeaterSetpointTemperature() const {
      boost::optional<double> value = getDouble(openstudio::Refrigeration_CompressorRackFields::BasinHeaterSetpointTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCompressorRack_Impl::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
      bool result = setDouble(openstudio::Refrigeration_CompressorRackFields::BasinHeaterSetpointTemperature, basinHeaterSetpointTemperature);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> RefrigerationCompressorRack_Impl::designEvaporativeCondenserWaterPumpPower() const {
      return getDouble(openstudio::Refrigeration_CompressorRackFields::DesignEvaporativeCondenserWaterPumpPower, true);
    }

    bool RefrigerationCompressorRack_Impl::isDesignEvaporativeCondenserWaterPumpPowerAutocalculated() const {
      bool result = false;
      boost::optional<std::string> value = getString(openstudio::Refrigeration_CompressorRackFields::DesignEvaporativeCondenserWaterPumpPower, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autocalculate");
      }
      return result;
    }

    bool RefrigerationCompressorRack_Impl::setDesignEvaporativeCondenserWaterPumpPower(double designEvaporativeCondenserWaterPumpPower) {
      bool result =
        setDouble(openstudio::Refrigeration_CompressorRackFields::DesignEvaporativeCondenserWaterPumpPower, designEvaporativeCondenserWaterPumpPower);
      OS_ASSERT(result);
      return result;
    }

    bool RefrigerationCompressorRack_Impl::autocalculateDesignEvaporativeCondenserWaterPumpPower() {
      bool result = setString(openstudio::Refrigeration_CompressorRackFields::DesignEvaporativeCondenserWaterPumpPower, "Autocalculate");
      OS_ASSERT(result);
      return result;
    }

    std::string RefrigerationCompressorRack_Impl::endUseSubcategory() const {
      boost::optional<std::string> value = getString(openstudio::Refrigeration_CompressorRackFields::EndUseSubcategory, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCompressorRack_Impl::isEndUseSubcategoryDefaulted() const {
      return isEmpty(openstudio::Refrigeration_CompressorRackFields::EndUseSubcategory);
    }

    bool RefrigerationCompressorRack_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
      bool result = setString(openstudio::Refrigeration_CompressorRackFields::EndUseSubcategory, endUseSubcategory);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationCompressorRack_Impl::resetEndUseSubcategory() {
      bool result = setString(openstudio::Refrigeration_CompressorRackFields::EndUseSubcategory, "");
      OS_ASSERT(result);
    }

    boost::optional<ThermalZone> RefrigerationCompressorRack_Impl::heatRejectionZone() const {
      return getObject<ModelObject>().getModelObjectTarget<ThermalZone>(openstudio::Refrigeration_CompressorRackFields::HeatRejectionZoneName);
    }

    bool RefrigerationCompressorRack_Impl::setHeatRejectionZone(const ThermalZone& thermalZone) {
      bool result = setPointer(openstudio::Refrigeration_CompressorRackFields::HeatRejectionZoneName, thermalZone.handle());
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationCompressorRack_Impl::resetHeatRejectionZone() {
      bool result = setString(openstudio::Refrigeration_CompressorRackFields::HeatRejectionZoneName, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
