/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/RefrigerationCompressorRack.hpp"
#include "StraightComponent/RefrigerationCompressorRack_Impl.hpp"

#include "Model.hpp"

#include "../utilities/core/Assert.hpp"
#include "../utilities/core/StringHelpers.hpp"
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_Refrigeration_CompressorRack_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  RefrigerationCompressorRack::RefrigerationCompressorRack(const Model& model)
    : StraightComponent(RefrigerationCompressorRack::iddObjectType(), model) {
    OS_ASSERT(setHeatRejectionLocation("Outdoors"));
    OS_ASSERT(setDesignCompressorRackCOP(2.0));
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
    return IddObjectType::OS_Refrigeration_CompressorRack;
  }

  std::vector<std::string> RefrigerationCompressorRack::condenserTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::OS_Refrigeration_CompressorRackFields::CondenserType);
  }

  std::vector<std::string> RefrigerationCompressorRack::waterCooledLoopFlowTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::OS_Refrigeration_CompressorRackFields::WaterCooledLoopFlowType);
  }

  std::string RefrigerationCompressorRack::heatRejectionLocation() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->heatRejectionLocation();
  }

  double RefrigerationCompressorRack::designCompressorRackCOP() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->designCompressorRackCOP();
  }

  double RefrigerationCompressorRack::designCondenserFanPower() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->designCondenserFanPower();
  }

  std::string RefrigerationCompressorRack::condenserType() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->condenserType();
  }

  std::string RefrigerationCompressorRack::waterCooledLoopFlowType() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->waterCooledLoopFlowType();
  }

  boost::optional<double> RefrigerationCompressorRack::waterCooledCondenserDesignFlowRate() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->waterCooledCondenserDesignFlowRate();
  }

  boost::optional<double> RefrigerationCompressorRack::waterCooledCondenserMaximumFlowRate() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->waterCooledCondenserMaximumFlowRate();
  }

  double RefrigerationCompressorRack::waterCooledCondenserMaximumWaterOutletTemperature() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->waterCooledCondenserMaximumWaterOutletTemperature();
  }

  double RefrigerationCompressorRack::waterCooledCondenserMinimumWaterInletTemperature() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->waterCooledCondenserMinimumWaterInletTemperature();
  }

  double RefrigerationCompressorRack::evaporativeCondenserEffectiveness() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->evaporativeCondenserEffectiveness();
  }

  boost::optional<double> RefrigerationCompressorRack::evaporativeCondenserAirFlowRate() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->evaporativeCondenserAirFlowRate();
  }

  bool RefrigerationCompressorRack::isEvaporativeCondenserAirFlowRateAutocalculated() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->isEvaporativeCondenserAirFlowRateAutocalculated();
  }

  double RefrigerationCompressorRack::basinHeaterCapacity() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->basinHeaterCapacity();
  }

  double RefrigerationCompressorRack::basinHeaterSetpointTemperature() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->basinHeaterSetpointTemperature();
  }

  boost::optional<double> RefrigerationCompressorRack::designEvaporativeCondenserWaterPumpPower() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->designEvaporativeCondenserWaterPumpPower();
  }

  bool RefrigerationCompressorRack::isDesignEvaporativeCondenserWaterPumpPowerAutocalculated() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->isDesignEvaporativeCondenserWaterPumpPowerAutocalculated();
  }

  std::string RefrigerationCompressorRack::endUseSubcategory() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->endUseSubcategory();
  }

  bool RefrigerationCompressorRack::isEndUseSubcategoryDefaulted() const {
    return getImpl<detail::RefrigerationCompressorRack_Impl>()->isEndUseSubcategoryDefaulted();
  }

  bool RefrigerationCompressorRack::setHeatRejectionLocation(const std::string& heatRejectionLocation) {
    bool result = getImpl<detail::RefrigerationCompressorRack_Impl>()->setHeatRejectionLocation(heatRejectionLocation);
    OS_ASSERT(result);
    return result;
  }

  bool RefrigerationCompressorRack::setDesignCompressorRackCOP(double designCompressorRackCOP) {
    bool result = getImpl<detail::RefrigerationCompressorRack_Impl>()->setDesignCompressorRackCOP(designCompressorRackCOP);
    OS_ASSERT(result);
    return result;
  }

  bool RefrigerationCompressorRack::setDesignCondenserFanPower(double designCondenserFanPower) {
    bool result = getImpl<detail::RefrigerationCompressorRack_Impl>()->setDesignCondenserFanPower(designCondenserFanPower);
    OS_ASSERT(result);
    return result;
  }

  bool RefrigerationCompressorRack::setCondenserType(const std::string& condenserType) {
    bool result = getImpl<detail::RefrigerationCompressorRack_Impl>()->setCondenserType(condenserType);
    OS_ASSERT(result);
    return result;
  }

  bool RefrigerationCompressorRack::setWaterCooledLoopFlowType(const std::string& waterCooledLoopFlowType) {
    bool result = getImpl<detail::RefrigerationCompressorRack_Impl>()->setWaterCooledLoopFlowType(waterCooledLoopFlowType);
    OS_ASSERT(result);
    return result;
  }

  bool RefrigerationCompressorRack::setWaterCooledCondenserDesignFlowRate(double waterCooledCondenserDesignFlowRate) {
    bool result = getImpl<detail::RefrigerationCompressorRack_Impl>()->setWaterCooledCondenserDesignFlowRate(waterCooledCondenserDesignFlowRate);
    OS_ASSERT(result);
    return result;
  }

  void RefrigerationCompressorRack::resetWaterCooledCondenserDesignFlowRate() {
    getImpl<detail::RefrigerationCompressorRack_Impl>()->resetWaterCooledCondenserDesignFlowRate();
  }

  bool RefrigerationCompressorRack::setWaterCooledCondenserMaximumFlowRate(double waterCooledCondenserMaximumFlowRate) {
    bool result = getImpl<detail::RefrigerationCompressorRack_Impl>()->setWaterCooledCondenserMaximumFlowRate(waterCooledCondenserMaximumFlowRate);
    OS_ASSERT(result);
    return result;
  }

  void RefrigerationCompressorRack::resetWaterCooledCondenserMaximumFlowRate() {
    getImpl<detail::RefrigerationCompressorRack_Impl>()->resetWaterCooledCondenserMaximumFlowRate();
  }

  bool RefrigerationCompressorRack::setWaterCooledCondenserMaximumWaterOutletTemperature(double waterCooledCondenserMaximumWaterOutletTemperature) {
    bool result = getImpl<detail::RefrigerationCompressorRack_Impl>()->setWaterCooledCondenserMaximumWaterOutletTemperature(
      waterCooledCondenserMaximumWaterOutletTemperature);
    OS_ASSERT(result);
    return result;
  }

  bool RefrigerationCompressorRack::setWaterCooledCondenserMinimumWaterInletTemperature(double waterCooledCondenserMinimumWaterInletTemperature) {
    bool result = getImpl<detail::RefrigerationCompressorRack_Impl>()->setWaterCooledCondenserMinimumWaterInletTemperature(
      waterCooledCondenserMinimumWaterInletTemperature);
    OS_ASSERT(result);
    return result;
  }

  bool RefrigerationCompressorRack::setEvaporativeCondenserEffectiveness(double evaporativeCondenserEffectiveness) {
    bool result = getImpl<detail::RefrigerationCompressorRack_Impl>()->setEvaporativeCondenserEffectiveness(evaporativeCondenserEffectiveness);
    OS_ASSERT(result);
    return result;
  }

  bool RefrigerationCompressorRack::setEvaporativeCondenserAirFlowRate(double evaporativeCondenserAirFlowRate) {
    bool result = getImpl<detail::RefrigerationCompressorRack_Impl>()->setEvaporativeCondenserAirFlowRate(evaporativeCondenserAirFlowRate);
    OS_ASSERT(result);
    return result;
  }

  bool RefrigerationCompressorRack::autocalculateEvaporativeCondenserAirFlowRate() {
    bool result = getImpl<detail::RefrigerationCompressorRack_Impl>()->autocalculateEvaporativeCondenserAirFlowRate();
    OS_ASSERT(result);
    return result;
  }

  bool RefrigerationCompressorRack::setBasinHeaterCapacity(double basinHeaterCapacity) {
    bool result = getImpl<detail::RefrigerationCompressorRack_Impl>()->setBasinHeaterCapacity(basinHeaterCapacity);
    OS_ASSERT(result);
    return result;
  }

  bool RefrigerationCompressorRack::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
    bool result = getImpl<detail::RefrigerationCompressorRack_Impl>()->setBasinHeaterSetpointTemperature(basinHeaterSetpointTemperature);
    OS_ASSERT(result);
    return result;
  }

  bool RefrigerationCompressorRack::setDesignEvaporativeCondenserWaterPumpPower(double designEvaporativeCondenserWaterPumpPower) {
    bool result =
      getImpl<detail::RefrigerationCompressorRack_Impl>()->setDesignEvaporativeCondenserWaterPumpPower(designEvaporativeCondenserWaterPumpPower);
    OS_ASSERT(result);
    return result;
  }

  bool RefrigerationCompressorRack::autocalculateDesignEvaporativeCondenserWaterPumpPower() {
    bool result = getImpl<detail::RefrigerationCompressorRack_Impl>()->autocalculateDesignEvaporativeCondenserWaterPumpPower();
    OS_ASSERT(result);
    return result;
  }

  bool RefrigerationCompressorRack::setEndUseSubcategory(const std::string& endUseSubcategory) {
    bool result = getImpl<detail::RefrigerationCompressorRack_Impl>()->setEndUseSubcategory(endUseSubcategory);
    OS_ASSERT(result);
    return result;
  }

  void RefrigerationCompressorRack::resetEndUseSubcategory() {
    getImpl<detail::RefrigerationCompressorRack_Impl>()->resetEndUseSubcategory();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned RefrigerationCompressorRack_Impl::inletPort() const {
      return openstudio::OS_Refrigeration_CompressorRackFields::WaterCooledCondenserInletNodeName;
    }

    unsigned RefrigerationCompressorRack_Impl::outletPort() const {
      return openstudio::OS_Refrigeration_CompressorRackFields::WaterCooledCondenserOutletNodeName;
    }

    std::string RefrigerationCompressorRack_Impl::heatRejectionLocation() const {
      boost::optional<std::string> value = getString(openstudio::OS_Refrigeration_CompressorRackFields::HeatRejectionLocation, true);
      OS_ASSERT(value);
      return value.get();
    }

    double RefrigerationCompressorRack_Impl::designCompressorRackCOP() const {
      boost::optional<double> value = getDouble(openstudio::OS_Refrigeration_CompressorRackFields::DesignCompressorRackCOP, true);
      OS_ASSERT(value);
      return value.get();
    }

    double RefrigerationCompressorRack_Impl::designCondenserFanPower() const {
      boost::optional<double> value = getDouble(openstudio::OS_Refrigeration_CompressorRackFields::DesignCondenserFanPower, true);
      OS_ASSERT(value);
      return value.get();
    }

    std::string RefrigerationCompressorRack_Impl::condenserType() const {
      boost::optional<std::string> value = getString(openstudio::OS_Refrigeration_CompressorRackFields::CondenserType, true);
      OS_ASSERT(value);
      return value.get();
    }

    std::string RefrigerationCompressorRack_Impl::waterCooledLoopFlowType() const {
      boost::optional<std::string> value = getString(openstudio::OS_Refrigeration_CompressorRackFields::WaterCooledLoopFlowType, true);
      OS_ASSERT(value);
      return value.get();
    }

    boost::optional<double> RefrigerationCompressorRack_Impl::waterCooledCondenserDesignFlowRate() const {
      return getDouble(openstudio::OS_Refrigeration_CompressorRackFields::WaterCooledCondenserDesignFlowRate, true);
    }

    boost::optional<double> RefrigerationCompressorRack_Impl::waterCooledCondenserMaximumFlowRate() const {
      return getDouble(openstudio::OS_Refrigeration_CompressorRackFields::WaterCooledCondenserMaximumFlowRate, true);
    }

    double RefrigerationCompressorRack_Impl::waterCooledCondenserMaximumWaterOutletTemperature() const {
      boost::optional<double> value =
        getDouble(openstudio::OS_Refrigeration_CompressorRackFields::WaterCooledCondenserMaximumWaterOutletTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    double RefrigerationCompressorRack_Impl::waterCooledCondenserMinimumWaterInletTemperature() const {
      boost::optional<double> value =
        getDouble(openstudio::OS_Refrigeration_CompressorRackFields::WaterCooledCondenserMinimumWaterInletTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    double RefrigerationCompressorRack_Impl::evaporativeCondenserEffectiveness() const {
      boost::optional<double> value = getDouble(openstudio::OS_Refrigeration_CompressorRackFields::EvaporativeCondenserEffectiveness, true);
      OS_ASSERT(value);
      return value.get();
    }

    boost::optional<double> RefrigerationCompressorRack_Impl::evaporativeCondenserAirFlowRate() const {
      return getDouble(openstudio::OS_Refrigeration_CompressorRackFields::EvaporativeCondenserAirFlowRate, true);
    }

    bool RefrigerationCompressorRack_Impl::isEvaporativeCondenserAirFlowRateAutocalculated() const {
      if (boost::optional<std::string> value = getString(openstudio::OS_Refrigeration_CompressorRackFields::EvaporativeCondenserAirFlowRate, true)) {
        return openstudio::istringEqual(value.get(), "Autocalculate");
      }
      return false;
    }

    double RefrigerationCompressorRack_Impl::basinHeaterCapacity() const {
      boost::optional<double> value = getDouble(openstudio::OS_Refrigeration_CompressorRackFields::BasinHeaterCapacity, true);
      OS_ASSERT(value);
      return value.get();
    }

    double RefrigerationCompressorRack_Impl::basinHeaterSetpointTemperature() const {
      boost::optional<double> value = getDouble(openstudio::OS_Refrigeration_CompressorRackFields::BasinHeaterSetpointTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    boost::optional<double> RefrigerationCompressorRack_Impl::designEvaporativeCondenserWaterPumpPower() const {
      return getDouble(openstudio::OS_Refrigeration_CompressorRackFields::DesignEvaporativeCondenserWaterPumpPower, true);
    }

    bool RefrigerationCompressorRack_Impl::isDesignEvaporativeCondenserWaterPumpPowerAutocalculated() const {
      if (boost::optional<std::string> value =
            getString(openstudio::OS_Refrigeration_CompressorRackFields::DesignEvaporativeCondenserWaterPumpPower, true)) {
        return openstudio::istringEqual(value.get(), "Autocalculate");
      }
      return false;
    }

    std::string RefrigerationCompressorRack_Impl::endUseSubcategory() const {
      boost::optional<std::string> value = getString(openstudio::OS_Refrigeration_CompressorRackFields::EndUseSubcategory, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationCompressorRack_Impl::isEndUseSubcategoryDefaulted() const {
      const unsigned fieldIndex = openstudio::OS_Refrigeration_CompressorRackFields::EndUseSubcategory;
      boost::optional<std::string> value = getString(fieldIndex, false, true);
      if (!value) {
        return true;
      }
      OptionalIddField iddField = iddObject().getField(fieldIndex);
      if (iddField && iddField->properties().stringDefault) {
        return openstudio::istringEqual(*value, iddField->properties().stringDefault.get());
      }
      return value->empty();
    }

    bool RefrigerationCompressorRack_Impl::setHeatRejectionLocation(const std::string& heatRejectionLocation) {
      bool result = setString(openstudio::OS_Refrigeration_CompressorRackFields::HeatRejectionLocation, heatRejectionLocation);
      OS_ASSERT(result);
      return result;
    }

    bool RefrigerationCompressorRack_Impl::setDesignCompressorRackCOP(double designCompressorRackCOP) {
      bool result = setDouble(openstudio::OS_Refrigeration_CompressorRackFields::DesignCompressorRackCOP, designCompressorRackCOP);
      OS_ASSERT(result);
      return result;
    }

    bool RefrigerationCompressorRack_Impl::setDesignCondenserFanPower(double designCondenserFanPower) {
      bool result = setDouble(openstudio::OS_Refrigeration_CompressorRackFields::DesignCondenserFanPower, designCondenserFanPower);
      OS_ASSERT(result);
      return result;
    }

    bool RefrigerationCompressorRack_Impl::setCondenserType(const std::string& condenserType) {
      bool result = setString(openstudio::OS_Refrigeration_CompressorRackFields::CondenserType, condenserType);
      OS_ASSERT(result);
      return result;
    }

    bool RefrigerationCompressorRack_Impl::setWaterCooledLoopFlowType(const std::string& waterCooledLoopFlowType) {
      bool result = setString(openstudio::OS_Refrigeration_CompressorRackFields::WaterCooledLoopFlowType, waterCooledLoopFlowType);
      OS_ASSERT(result);
      return result;
    }

    bool RefrigerationCompressorRack_Impl::setWaterCooledCondenserDesignFlowRate(double waterCooledCondenserDesignFlowRate) {
      bool result =
        setDouble(openstudio::OS_Refrigeration_CompressorRackFields::WaterCooledCondenserDesignFlowRate, waterCooledCondenserDesignFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationCompressorRack_Impl::resetWaterCooledCondenserDesignFlowRate() {
      bool result = setString(openstudio::OS_Refrigeration_CompressorRackFields::WaterCooledCondenserDesignFlowRate, "");
      OS_ASSERT(result);
    }

    bool RefrigerationCompressorRack_Impl::setWaterCooledCondenserMaximumFlowRate(double waterCooledCondenserMaximumFlowRate) {
      bool result =
        setDouble(openstudio::OS_Refrigeration_CompressorRackFields::WaterCooledCondenserMaximumFlowRate, waterCooledCondenserMaximumFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationCompressorRack_Impl::resetWaterCooledCondenserMaximumFlowRate() {
      bool result = setString(openstudio::OS_Refrigeration_CompressorRackFields::WaterCooledCondenserMaximumFlowRate, "");
      OS_ASSERT(result);
    }

    bool RefrigerationCompressorRack_Impl::setWaterCooledCondenserMaximumWaterOutletTemperature(
      double waterCooledCondenserMaximumWaterOutletTemperature) {
      bool result = setDouble(openstudio::OS_Refrigeration_CompressorRackFields::WaterCooledCondenserMaximumWaterOutletTemperature,
                              waterCooledCondenserMaximumWaterOutletTemperature);
      OS_ASSERT(result);
      return result;
    }

    bool
      RefrigerationCompressorRack_Impl::setWaterCooledCondenserMinimumWaterInletTemperature(double waterCooledCondenserMinimumWaterInletTemperature) {
      bool result = setDouble(openstudio::OS_Refrigeration_CompressorRackFields::WaterCooledCondenserMinimumWaterInletTemperature,
                              waterCooledCondenserMinimumWaterInletTemperature);
      OS_ASSERT(result);
      return result;
    }

    bool RefrigerationCompressorRack_Impl::setEvaporativeCondenserEffectiveness(double evaporativeCondenserEffectiveness) {
      bool result =
        setDouble(openstudio::OS_Refrigeration_CompressorRackFields::EvaporativeCondenserEffectiveness, evaporativeCondenserEffectiveness);
      OS_ASSERT(result);
      return result;
    }

    bool RefrigerationCompressorRack_Impl::setEvaporativeCondenserAirFlowRate(double evaporativeCondenserAirFlowRate) {
      bool result = setDouble(openstudio::OS_Refrigeration_CompressorRackFields::EvaporativeCondenserAirFlowRate, evaporativeCondenserAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    bool RefrigerationCompressorRack_Impl::autocalculateEvaporativeCondenserAirFlowRate() {
      const bool result = setString(openstudio::OS_Refrigeration_CompressorRackFields::EvaporativeCondenserAirFlowRate, "Autocalculate");
      OS_ASSERT(result);
      return result;
    }

    bool RefrigerationCompressorRack_Impl::setBasinHeaterCapacity(double basinHeaterCapacity) {
      bool result = setDouble(openstudio::OS_Refrigeration_CompressorRackFields::BasinHeaterCapacity, basinHeaterCapacity);
      OS_ASSERT(result);
      return result;
    }

    bool RefrigerationCompressorRack_Impl::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
      bool result = setDouble(openstudio::OS_Refrigeration_CompressorRackFields::BasinHeaterSetpointTemperature, basinHeaterSetpointTemperature);
      OS_ASSERT(result);
      return result;
    }

    bool RefrigerationCompressorRack_Impl::setDesignEvaporativeCondenserWaterPumpPower(double designEvaporativeCondenserWaterPumpPower) {
      bool result = setDouble(openstudio::OS_Refrigeration_CompressorRackFields::DesignEvaporativeCondenserWaterPumpPower,
                              designEvaporativeCondenserWaterPumpPower);
      OS_ASSERT(result);
      return result;
    }

    bool RefrigerationCompressorRack_Impl::autocalculateDesignEvaporativeCondenserWaterPumpPower() {
      const bool result = setString(openstudio::OS_Refrigeration_CompressorRackFields::DesignEvaporativeCondenserWaterPumpPower, "Autocalculate");
      OS_ASSERT(result);
      return result;
    }

    bool RefrigerationCompressorRack_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
      bool result = setString(openstudio::OS_Refrigeration_CompressorRackFields::EndUseSubcategory, endUseSubcategory);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationCompressorRack_Impl::resetEndUseSubcategory() {
      bool result = setString(openstudio::OS_Refrigeration_CompressorRackFields::EndUseSubcategory, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
