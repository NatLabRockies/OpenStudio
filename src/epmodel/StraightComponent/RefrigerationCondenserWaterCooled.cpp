/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "StraightComponent/RefrigerationCondenserWaterCooled.hpp"
#include "StraightComponent/RefrigerationCondenserWaterCooled_Impl.hpp"

#include "Loop/PlantLoop.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"

#include "../utilities/core/Assert.hpp"

#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Refrigeration_Condenser_WaterCooled_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  RefrigerationCondenserWaterCooled::RefrigerationCondenserWaterCooled(const Model& model)
    : StraightComponent(RefrigerationCondenserWaterCooled::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::RefrigerationCondenserWaterCooled_Impl>());

    OS_ASSERT(setRatedEffectiveTotalHeatRejectionRate(58000.0));
    OS_ASSERT(setRatedCondensingTemperature(29.4));
    OS_ASSERT(setRatedSubcoolingTemperatureDifference(0.0));
    OS_ASSERT(setRatedWaterInletTemperature(10.0));
    OS_ASSERT(setWaterCooledLoopFlowType("ConstantFlow"));
    OS_ASSERT(setWaterDesignFlowRate(0.0025));
    OS_ASSERT(setWaterMaximumFlowRate(0.003));
    OS_ASSERT(setWaterMaximumWaterOutletTemperature(55.0));
    OS_ASSERT(setWaterMinimumWaterInletTemperature(10.0));
  }

  RefrigerationCondenserWaterCooled::RefrigerationCondenserWaterCooled(std::shared_ptr<detail::RefrigerationCondenserWaterCooled_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType RefrigerationCondenserWaterCooled::iddObjectType() {
    return IddObjectType::Refrigeration_Condenser_WaterCooled;
  }

  std::vector<std::string> RefrigerationCondenserWaterCooled::waterCooledLoopFlowTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          Refrigeration_Condenser_WaterCooledFields::WaterCooledLoopFlowType);
  }

  boost::optional<double> RefrigerationCondenserWaterCooled::ratedEffectiveTotalHeatRejectionRate() const {
    return getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->ratedEffectiveTotalHeatRejectionRate();
  }

  bool RefrigerationCondenserWaterCooled::setRatedEffectiveTotalHeatRejectionRate(double ratedEffectiveTotalHeatRejectionRate) {
    return getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->setRatedEffectiveTotalHeatRejectionRate(ratedEffectiveTotalHeatRejectionRate);
  }

  void RefrigerationCondenserWaterCooled::resetRatedEffectiveTotalHeatRejectionRate() {
    getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->resetRatedEffectiveTotalHeatRejectionRate();
  }

  double RefrigerationCondenserWaterCooled::ratedCondensingTemperature() const {
    return getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->ratedCondensingTemperature();
  }

  bool RefrigerationCondenserWaterCooled::setRatedCondensingTemperature(double ratedCondensingTemperature) {
    return getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->setRatedCondensingTemperature(ratedCondensingTemperature);
  }

  double RefrigerationCondenserWaterCooled::ratedSubcoolingTemperatureDifference() const {
    return getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->ratedSubcoolingTemperatureDifference();
  }

  bool RefrigerationCondenserWaterCooled::isRatedSubcoolingTemperatureDifferenceDefaulted() const {
    return getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->isRatedSubcoolingTemperatureDifferenceDefaulted();
  }

  bool RefrigerationCondenserWaterCooled::setRatedSubcoolingTemperatureDifference(double ratedSubcoolingTemperatureDifference) {
    return getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->setRatedSubcoolingTemperatureDifference(ratedSubcoolingTemperatureDifference);
  }

  void RefrigerationCondenserWaterCooled::resetRatedSubcoolingTemperatureDifference() {
    getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->resetRatedSubcoolingTemperatureDifference();
  }

  double RefrigerationCondenserWaterCooled::ratedWaterInletTemperature() const {
    return getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->ratedWaterInletTemperature();
  }

  bool RefrigerationCondenserWaterCooled::setRatedWaterInletTemperature(double ratedWaterInletTemperature) {
    return getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->setRatedWaterInletTemperature(ratedWaterInletTemperature);
  }

  std::string RefrigerationCondenserWaterCooled::waterCooledLoopFlowType() const {
    return getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->waterCooledLoopFlowType();
  }

  bool RefrigerationCondenserWaterCooled::isWaterCooledLoopFlowTypeDefaulted() const {
    return getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->isWaterCooledLoopFlowTypeDefaulted();
  }

  bool RefrigerationCondenserWaterCooled::setWaterCooledLoopFlowType(const std::string& waterCooledLoopFlowType) {
    return getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->setWaterCooledLoopFlowType(waterCooledLoopFlowType);
  }

  void RefrigerationCondenserWaterCooled::resetWaterCooledLoopFlowType() {
    getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->resetWaterCooledLoopFlowType();
  }

  boost::optional<Schedule> RefrigerationCondenserWaterCooled::waterOutletTemperatureSchedule() const {
    return getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->waterOutletTemperatureSchedule();
  }

  bool RefrigerationCondenserWaterCooled::setWaterOutletTemperatureSchedule(Schedule& waterOutletTemperatureSchedule) {
    return getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->setWaterOutletTemperatureSchedule(waterOutletTemperatureSchedule);
  }

  void RefrigerationCondenserWaterCooled::resetWaterOutletTemperatureSchedule() {
    getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->resetWaterOutletTemperatureSchedule();
  }

  boost::optional<double> RefrigerationCondenserWaterCooled::waterDesignFlowRate() const {
    return getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->waterDesignFlowRate();
  }

  bool RefrigerationCondenserWaterCooled::setWaterDesignFlowRate(double waterDesignFlowRate) {
    return getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->setWaterDesignFlowRate(waterDesignFlowRate);
  }

  void RefrigerationCondenserWaterCooled::resetWaterDesignFlowRate() {
    getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->resetWaterDesignFlowRate();
  }

  boost::optional<double> RefrigerationCondenserWaterCooled::waterMaximumFlowRate() const {
    return getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->waterMaximumFlowRate();
  }

  bool RefrigerationCondenserWaterCooled::setWaterMaximumFlowRate(double waterMaximumFlowRate) {
    return getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->setWaterMaximumFlowRate(waterMaximumFlowRate);
  }

  void RefrigerationCondenserWaterCooled::resetWaterMaximumFlowRate() {
    getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->resetWaterMaximumFlowRate();
  }

  double RefrigerationCondenserWaterCooled::waterMaximumWaterOutletTemperature() const {
    return getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->waterMaximumWaterOutletTemperature();
  }

  bool RefrigerationCondenserWaterCooled::isWaterMaximumWaterOutletTemperatureDefaulted() const {
    return getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->isWaterMaximumWaterOutletTemperatureDefaulted();
  }

  bool RefrigerationCondenserWaterCooled::setWaterMaximumWaterOutletTemperature(double waterMaximumWaterOutletTemperature) {
    return getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->setWaterMaximumWaterOutletTemperature(waterMaximumWaterOutletTemperature);
  }

  void RefrigerationCondenserWaterCooled::resetWaterMaximumWaterOutletTemperature() {
    getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->resetWaterMaximumWaterOutletTemperature();
  }

  double RefrigerationCondenserWaterCooled::waterMinimumWaterInletTemperature() const {
    return getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->waterMinimumWaterInletTemperature();
  }

  bool RefrigerationCondenserWaterCooled::isWaterMinimumWaterInletTemperatureDefaulted() const {
    return getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->isWaterMinimumWaterInletTemperatureDefaulted();
  }

  bool RefrigerationCondenserWaterCooled::setWaterMinimumWaterInletTemperature(double waterMinimumWaterInletTemperature) {
    return getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->setWaterMinimumWaterInletTemperature(waterMinimumWaterInletTemperature);
  }

  void RefrigerationCondenserWaterCooled::resetWaterMinimumWaterInletTemperature() {
    getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->resetWaterMinimumWaterInletTemperature();
  }

  std::string RefrigerationCondenserWaterCooled::endUseSubcategory() const {
    return getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->endUseSubcategory();
  }

  bool RefrigerationCondenserWaterCooled::isEndUseSubcategoryDefaulted() const {
    return getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->isEndUseSubcategoryDefaulted();
  }

  bool RefrigerationCondenserWaterCooled::setEndUseSubcategory(const std::string& endUseSubcategory) {
    return getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->setEndUseSubcategory(endUseSubcategory);
  }

  void RefrigerationCondenserWaterCooled::resetEndUseSubcategory() {
    getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->resetEndUseSubcategory();
  }

  boost::optional<double> RefrigerationCondenserWaterCooled::condenserRefrigerantOperatingChargeInventory() const {
    return getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->condenserRefrigerantOperatingChargeInventory();
  }

  bool RefrigerationCondenserWaterCooled::setCondenserRefrigerantOperatingChargeInventory(double condenserRefrigerantOperatingChargeInventory) {
    return getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->setCondenserRefrigerantOperatingChargeInventory(
      condenserRefrigerantOperatingChargeInventory);
  }

  void RefrigerationCondenserWaterCooled::resetCondenserRefrigerantOperatingChargeInventory() {
    getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->resetCondenserRefrigerantOperatingChargeInventory();
  }

  boost::optional<double> RefrigerationCondenserWaterCooled::condensateReceiverRefrigerantInventory() const {
    return getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->condensateReceiverRefrigerantInventory();
  }

  bool RefrigerationCondenserWaterCooled::setCondensateReceiverRefrigerantInventory(double condensateReceiverRefrigerantInventory) {
    return getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->setCondensateReceiverRefrigerantInventory(
      condensateReceiverRefrigerantInventory);
  }

  void RefrigerationCondenserWaterCooled::resetCondensateReceiverRefrigerantInventory() {
    getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->resetCondensateReceiverRefrigerantInventory();
  }

  boost::optional<double> RefrigerationCondenserWaterCooled::condensatePipingRefrigerantInventory() const {
    return getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->condensatePipingRefrigerantInventory();
  }

  bool RefrigerationCondenserWaterCooled::setCondensatePipingRefrigerantInventory(double condensatePipingRefrigerantInventory) {
    return getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->setCondensatePipingRefrigerantInventory(condensatePipingRefrigerantInventory);
  }

  void RefrigerationCondenserWaterCooled::resetCondensatePipingRefrigerantInventory() {
    getImpl<detail::RefrigerationCondenserWaterCooled_Impl>()->resetCondensatePipingRefrigerantInventory();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned RefrigerationCondenserWaterCooled_Impl::inletPort() const {
      return Refrigeration_Condenser_WaterCooledFields::WaterInletNodeName;
    }

    unsigned RefrigerationCondenserWaterCooled_Impl::outletPort() const {
      return Refrigeration_Condenser_WaterCooledFields::WaterOutletNodeName;
    }

    bool RefrigerationCondenserWaterCooled_Impl::addToNode(Node& node) {
      if (auto plantLoop = node.plantLoop()) {
        if (plantLoop->demandComponent(node.handle())) {
          return StraightComponent_Impl::addToNode(node);
        }
      }

      return false;
    }

    boost::optional<double> RefrigerationCondenserWaterCooled_Impl::ratedEffectiveTotalHeatRejectionRate() const {
      return getDouble(Refrigeration_Condenser_WaterCooledFields::RatedEffectiveTotalHeatRejectionRate, true);
    }

    bool
      RefrigerationCondenserWaterCooled_Impl::setRatedEffectiveTotalHeatRejectionRate(boost::optional<double> ratedEffectiveTotalHeatRejectionRate) {
      bool result(false);
      if (ratedEffectiveTotalHeatRejectionRate) {
        result =
          setDouble(Refrigeration_Condenser_WaterCooledFields::RatedEffectiveTotalHeatRejectionRate, ratedEffectiveTotalHeatRejectionRate.get());
      } else {
        resetRatedEffectiveTotalHeatRejectionRate();
        result = true;
      }
      return result;
    }

    void RefrigerationCondenserWaterCooled_Impl::resetRatedEffectiveTotalHeatRejectionRate() {
      const bool result = setString(Refrigeration_Condenser_WaterCooledFields::RatedEffectiveTotalHeatRejectionRate, "");
      OS_ASSERT(result);
    }

    double RefrigerationCondenserWaterCooled_Impl::ratedCondensingTemperature() const {
      const auto value = getDouble(Refrigeration_Condenser_WaterCooledFields::RatedCondensingTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationCondenserWaterCooled_Impl::setRatedCondensingTemperature(double ratedCondensingTemperature) {
      return setDouble(Refrigeration_Condenser_WaterCooledFields::RatedCondensingTemperature, ratedCondensingTemperature);
    }

    double RefrigerationCondenserWaterCooled_Impl::ratedSubcoolingTemperatureDifference() const {
      const auto value = getDouble(Refrigeration_Condenser_WaterCooledFields::RatedSubcoolingTemperatureDifference, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationCondenserWaterCooled_Impl::isRatedSubcoolingTemperatureDifferenceDefaulted() const {
      return isEmpty(Refrigeration_Condenser_WaterCooledFields::RatedSubcoolingTemperatureDifference);
    }

    bool RefrigerationCondenserWaterCooled_Impl::setRatedSubcoolingTemperatureDifference(double ratedSubcoolingTemperatureDifference) {
      return setDouble(Refrigeration_Condenser_WaterCooledFields::RatedSubcoolingTemperatureDifference, ratedSubcoolingTemperatureDifference);
    }

    void RefrigerationCondenserWaterCooled_Impl::resetRatedSubcoolingTemperatureDifference() {
      const bool result = setString(Refrigeration_Condenser_WaterCooledFields::RatedSubcoolingTemperatureDifference, "");
      OS_ASSERT(result);
    }

    double RefrigerationCondenserWaterCooled_Impl::ratedWaterInletTemperature() const {
      const auto value = getDouble(Refrigeration_Condenser_WaterCooledFields::RatedWaterInletTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationCondenserWaterCooled_Impl::setRatedWaterInletTemperature(double ratedWaterInletTemperature) {
      return setDouble(Refrigeration_Condenser_WaterCooledFields::RatedWaterInletTemperature, ratedWaterInletTemperature);
    }

    std::string RefrigerationCondenserWaterCooled_Impl::waterCooledLoopFlowType() const {
      const auto value = getString(Refrigeration_Condenser_WaterCooledFields::WaterCooledLoopFlowType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationCondenserWaterCooled_Impl::isWaterCooledLoopFlowTypeDefaulted() const {
      return isEmpty(Refrigeration_Condenser_WaterCooledFields::WaterCooledLoopFlowType);
    }

    bool RefrigerationCondenserWaterCooled_Impl::setWaterCooledLoopFlowType(const std::string& waterCooledLoopFlowType) {
      return setString(Refrigeration_Condenser_WaterCooledFields::WaterCooledLoopFlowType, waterCooledLoopFlowType);
    }

    void RefrigerationCondenserWaterCooled_Impl::resetWaterCooledLoopFlowType() {
      const bool result = setString(Refrigeration_Condenser_WaterCooledFields::WaterCooledLoopFlowType, "");
      OS_ASSERT(result);
    }

    boost::optional<Schedule> RefrigerationCondenserWaterCooled_Impl::waterOutletTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(Refrigeration_Condenser_WaterCooledFields::WaterOutletTemperatureScheduleName);
    }

    bool RefrigerationCondenserWaterCooled_Impl::setWaterOutletTemperatureSchedule(Schedule& waterOutletTemperatureSchedule) {
      return setSchedule(Refrigeration_Condenser_WaterCooledFields::WaterOutletTemperatureScheduleName,
                         "RefrigerationCondenserWaterCooled", "Water Outlet Temperature", waterOutletTemperatureSchedule);
    }

    void RefrigerationCondenserWaterCooled_Impl::resetWaterOutletTemperatureSchedule() {
      const bool result = setString(Refrigeration_Condenser_WaterCooledFields::WaterOutletTemperatureScheduleName, "");
      OS_ASSERT(result);
    }

    boost::optional<double> RefrigerationCondenserWaterCooled_Impl::waterDesignFlowRate() const {
      return getDouble(Refrigeration_Condenser_WaterCooledFields::WaterDesignFlowRate, true);
    }

    bool RefrigerationCondenserWaterCooled_Impl::setWaterDesignFlowRate(boost::optional<double> waterDesignFlowRate) {
      bool result(false);
      if (waterDesignFlowRate) {
        result = setDouble(Refrigeration_Condenser_WaterCooledFields::WaterDesignFlowRate, waterDesignFlowRate.get());
      } else {
        resetWaterDesignFlowRate();
        result = true;
      }
      return result;
    }

    void RefrigerationCondenserWaterCooled_Impl::resetWaterDesignFlowRate() {
      const bool result = setString(Refrigeration_Condenser_WaterCooledFields::WaterDesignFlowRate, "");
      OS_ASSERT(result);
    }

    boost::optional<double> RefrigerationCondenserWaterCooled_Impl::waterMaximumFlowRate() const {
      return getDouble(Refrigeration_Condenser_WaterCooledFields::WaterMaximumFlowRate, true);
    }

    bool RefrigerationCondenserWaterCooled_Impl::setWaterMaximumFlowRate(boost::optional<double> waterMaximumFlowRate) {
      bool result(false);
      if (waterMaximumFlowRate) {
        result = setDouble(Refrigeration_Condenser_WaterCooledFields::WaterMaximumFlowRate, waterMaximumFlowRate.get());
      } else {
        resetWaterMaximumFlowRate();
        result = true;
      }
      return result;
    }

    void RefrigerationCondenserWaterCooled_Impl::resetWaterMaximumFlowRate() {
      const bool result = setString(Refrigeration_Condenser_WaterCooledFields::WaterMaximumFlowRate, "");
      OS_ASSERT(result);
    }

    double RefrigerationCondenserWaterCooled_Impl::waterMaximumWaterOutletTemperature() const {
      const auto value = getDouble(Refrigeration_Condenser_WaterCooledFields::WaterMaximumWaterOutletTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationCondenserWaterCooled_Impl::isWaterMaximumWaterOutletTemperatureDefaulted() const {
      return isEmpty(Refrigeration_Condenser_WaterCooledFields::WaterMaximumWaterOutletTemperature);
    }

    bool RefrigerationCondenserWaterCooled_Impl::setWaterMaximumWaterOutletTemperature(double waterMaximumWaterOutletTemperature) {
      return setDouble(Refrigeration_Condenser_WaterCooledFields::WaterMaximumWaterOutletTemperature, waterMaximumWaterOutletTemperature);
    }

    void RefrigerationCondenserWaterCooled_Impl::resetWaterMaximumWaterOutletTemperature() {
      const bool result = setString(Refrigeration_Condenser_WaterCooledFields::WaterMaximumWaterOutletTemperature, "");
      OS_ASSERT(result);
    }

    double RefrigerationCondenserWaterCooled_Impl::waterMinimumWaterInletTemperature() const {
      const auto value = getDouble(Refrigeration_Condenser_WaterCooledFields::WaterMinimumWaterInletTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationCondenserWaterCooled_Impl::isWaterMinimumWaterInletTemperatureDefaulted() const {
      return isEmpty(Refrigeration_Condenser_WaterCooledFields::WaterMinimumWaterInletTemperature);
    }

    bool RefrigerationCondenserWaterCooled_Impl::setWaterMinimumWaterInletTemperature(double waterMinimumWaterInletTemperature) {
      return setDouble(Refrigeration_Condenser_WaterCooledFields::WaterMinimumWaterInletTemperature, waterMinimumWaterInletTemperature);
    }

    void RefrigerationCondenserWaterCooled_Impl::resetWaterMinimumWaterInletTemperature() {
      const bool result = setString(Refrigeration_Condenser_WaterCooledFields::WaterMinimumWaterInletTemperature, "");
      OS_ASSERT(result);
    }

    std::string RefrigerationCondenserWaterCooled_Impl::endUseSubcategory() const {
      const auto value = getString(Refrigeration_Condenser_WaterCooledFields::EndUseSubcategory, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefrigerationCondenserWaterCooled_Impl::isEndUseSubcategoryDefaulted() const {
      return isEmpty(Refrigeration_Condenser_WaterCooledFields::EndUseSubcategory);
    }

    bool RefrigerationCondenserWaterCooled_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
      const bool result = setString(Refrigeration_Condenser_WaterCooledFields::EndUseSubcategory, endUseSubcategory);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationCondenserWaterCooled_Impl::resetEndUseSubcategory() {
      const bool result = setString(Refrigeration_Condenser_WaterCooledFields::EndUseSubcategory, "");
      OS_ASSERT(result);
    }

    boost::optional<double> RefrigerationCondenserWaterCooled_Impl::condenserRefrigerantOperatingChargeInventory() const {
      return getDouble(Refrigeration_Condenser_WaterCooledFields::CondenserRefrigerantOperatingChargeInventory, true);
    }

    bool RefrigerationCondenserWaterCooled_Impl::setCondenserRefrigerantOperatingChargeInventory(
      boost::optional<double> condenserRefrigerantOperatingChargeInventory) {
      bool result(false);
      if (condenserRefrigerantOperatingChargeInventory) {
        result = setDouble(Refrigeration_Condenser_WaterCooledFields::CondenserRefrigerantOperatingChargeInventory,
                           condenserRefrigerantOperatingChargeInventory.get());
      } else {
        resetCondenserRefrigerantOperatingChargeInventory();
        result = true;
      }
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationCondenserWaterCooled_Impl::resetCondenserRefrigerantOperatingChargeInventory() {
      const bool result = setString(Refrigeration_Condenser_WaterCooledFields::CondenserRefrigerantOperatingChargeInventory, "");
      OS_ASSERT(result);
    }

    boost::optional<double> RefrigerationCondenserWaterCooled_Impl::condensateReceiverRefrigerantInventory() const {
      return getDouble(Refrigeration_Condenser_WaterCooledFields::CondensateReceiverRefrigerantInventory, true);
    }

    bool RefrigerationCondenserWaterCooled_Impl::setCondensateReceiverRefrigerantInventory(
      boost::optional<double> condensateReceiverRefrigerantInventory) {
      bool result(false);
      if (condensateReceiverRefrigerantInventory) {
        result =
          setDouble(Refrigeration_Condenser_WaterCooledFields::CondensateReceiverRefrigerantInventory, condensateReceiverRefrigerantInventory.get());
      } else {
        resetCondensateReceiverRefrigerantInventory();
        result = true;
      }
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationCondenserWaterCooled_Impl::resetCondensateReceiverRefrigerantInventory() {
      const bool result = setString(Refrigeration_Condenser_WaterCooledFields::CondensateReceiverRefrigerantInventory, "");
      OS_ASSERT(result);
    }

    boost::optional<double> RefrigerationCondenserWaterCooled_Impl::condensatePipingRefrigerantInventory() const {
      return getDouble(Refrigeration_Condenser_WaterCooledFields::CondensatePipingRefrigerantInventory, true);
    }

    bool
      RefrigerationCondenserWaterCooled_Impl::setCondensatePipingRefrigerantInventory(boost::optional<double> condensatePipingRefrigerantInventory) {
      bool result(false);
      if (condensatePipingRefrigerantInventory) {
        result =
          setDouble(Refrigeration_Condenser_WaterCooledFields::CondensatePipingRefrigerantInventory, condensatePipingRefrigerantInventory.get());
      } else {
        resetCondensatePipingRefrigerantInventory();
        result = true;
      }
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationCondenserWaterCooled_Impl::resetCondensatePipingRefrigerantInventory() {
      const bool result = setString(Refrigeration_Condenser_WaterCooledFields::CondensatePipingRefrigerantInventory, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
