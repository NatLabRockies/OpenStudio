/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACBaseboardRadiantConvectiveWater.hpp"
#include "ZoneHVACComponent/ZoneHVACBaseboardRadiantConvectiveWater_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_Baseboard_RadiantConvective_Water_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneHVACBaseboardRadiantConvectiveWater::ZoneHVACBaseboardRadiantConvectiveWater(const Model& model)
    : ModelObject(ZoneHVACBaseboardRadiantConvectiveWater::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>());

    autosizeHeatingDesignCapacity();
    autosizeMaximumWaterFlowRate();
  }

  ZoneHVACBaseboardRadiantConvectiveWater::ZoneHVACBaseboardRadiantConvectiveWater(
    std::shared_ptr<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneHVACBaseboardRadiantConvectiveWater::iddObjectType() {
    return IddObjectType::ZoneHVAC_Baseboard_RadiantConvective_Water;
  }

  boost::optional<double> ZoneHVACBaseboardRadiantConvectiveWater::ratedAverageWaterTemperature() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->ratedAverageWaterTemperature();
  }

  bool ZoneHVACBaseboardRadiantConvectiveWater::isRatedAverageWaterTemperatureDefaulted() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->isRatedAverageWaterTemperatureDefaulted();
  }

  bool ZoneHVACBaseboardRadiantConvectiveWater::setRatedAverageWaterTemperature(double ratedAverageWaterTemperature) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->setRatedAverageWaterTemperature(ratedAverageWaterTemperature);
  }

  void ZoneHVACBaseboardRadiantConvectiveWater::resetRatedAverageWaterTemperature() {
    getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->resetRatedAverageWaterTemperature();
  }

  boost::optional<double> ZoneHVACBaseboardRadiantConvectiveWater::ratedWaterMassFlowRate() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->ratedWaterMassFlowRate();
  }

  bool ZoneHVACBaseboardRadiantConvectiveWater::isRatedWaterMassFlowRateDefaulted() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->isRatedWaterMassFlowRateDefaulted();
  }

  bool ZoneHVACBaseboardRadiantConvectiveWater::setRatedWaterMassFlowRate(double ratedWaterMassFlowRate) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->setRatedWaterMassFlowRate(ratedWaterMassFlowRate);
  }

  void ZoneHVACBaseboardRadiantConvectiveWater::resetRatedWaterMassFlowRate() {
    getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->resetRatedWaterMassFlowRate();
  }

  boost::optional<double> ZoneHVACBaseboardRadiantConvectiveWater::heatingDesignCapacity() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->heatingDesignCapacity();
  }

  bool ZoneHVACBaseboardRadiantConvectiveWater::isHeatingDesignCapacityAutosized() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->isHeatingDesignCapacityAutosized();
  }

  bool ZoneHVACBaseboardRadiantConvectiveWater::setHeatingDesignCapacity(double heatingDesignCapacity) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->setHeatingDesignCapacity(heatingDesignCapacity);
  }

  void ZoneHVACBaseboardRadiantConvectiveWater::autosizeHeatingDesignCapacity() {
    getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->autosizeHeatingDesignCapacity();
  }

  boost::optional<double> ZoneHVACBaseboardRadiantConvectiveWater::maximumWaterFlowRate() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->maximumWaterFlowRate();
  }

  bool ZoneHVACBaseboardRadiantConvectiveWater::isMaximumWaterFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->isMaximumWaterFlowRateAutosized();
  }

  bool ZoneHVACBaseboardRadiantConvectiveWater::setMaximumWaterFlowRate(double maximumWaterFlowRate) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->setMaximumWaterFlowRate(maximumWaterFlowRate);
  }

  void ZoneHVACBaseboardRadiantConvectiveWater::autosizeMaximumWaterFlowRate() {
    getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->autosizeMaximumWaterFlowRate();
  }

  namespace detail {

    boost::optional<double> ZoneHVACBaseboardRadiantConvectiveWater_Impl::ratedAverageWaterTemperature() const {
      return getDouble(ZoneHVAC_Baseboard_RadiantConvective_WaterFields::RatedAverageWaterTemperature, true);
    }

    bool ZoneHVACBaseboardRadiantConvectiveWater_Impl::isRatedAverageWaterTemperatureDefaulted() const {
      return isEmpty(ZoneHVAC_Baseboard_RadiantConvective_WaterFields::RatedAverageWaterTemperature);
    }

    bool ZoneHVACBaseboardRadiantConvectiveWater_Impl::setRatedAverageWaterTemperature(double ratedAverageWaterTemperature) {
      const bool result = setDouble(ZoneHVAC_Baseboard_RadiantConvective_WaterFields::RatedAverageWaterTemperature, ratedAverageWaterTemperature);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACBaseboardRadiantConvectiveWater_Impl::resetRatedAverageWaterTemperature() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_RadiantConvective_WaterFields::RatedAverageWaterTemperature, ""));
    }

    boost::optional<double> ZoneHVACBaseboardRadiantConvectiveWater_Impl::ratedWaterMassFlowRate() const {
      return getDouble(ZoneHVAC_Baseboard_RadiantConvective_WaterFields::RatedWaterMassFlowRate, true);
    }

    bool ZoneHVACBaseboardRadiantConvectiveWater_Impl::isRatedWaterMassFlowRateDefaulted() const {
      return isEmpty(ZoneHVAC_Baseboard_RadiantConvective_WaterFields::RatedWaterMassFlowRate);
    }

    bool ZoneHVACBaseboardRadiantConvectiveWater_Impl::setRatedWaterMassFlowRate(double ratedWaterMassFlowRate) {
      const bool result = setDouble(ZoneHVAC_Baseboard_RadiantConvective_WaterFields::RatedWaterMassFlowRate, ratedWaterMassFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACBaseboardRadiantConvectiveWater_Impl::resetRatedWaterMassFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_RadiantConvective_WaterFields::RatedWaterMassFlowRate, ""));
    }

    boost::optional<double> ZoneHVACBaseboardRadiantConvectiveWater_Impl::heatingDesignCapacity() const {
      return getDouble(ZoneHVAC_Baseboard_RadiantConvective_WaterFields::HeatingDesignCapacity, true);
    }

    bool ZoneHVACBaseboardRadiantConvectiveWater_Impl::isHeatingDesignCapacityAutosized() const {
      if (auto value = getString(ZoneHVAC_Baseboard_RadiantConvective_WaterFields::HeatingDesignCapacity, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    bool ZoneHVACBaseboardRadiantConvectiveWater_Impl::setHeatingDesignCapacity(double heatingDesignCapacity) {
      const bool result = setDouble(ZoneHVAC_Baseboard_RadiantConvective_WaterFields::HeatingDesignCapacity, heatingDesignCapacity);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACBaseboardRadiantConvectiveWater_Impl::autosizeHeatingDesignCapacity() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_RadiantConvective_WaterFields::HeatingDesignCapacity, "autosize"));
    }

    boost::optional<double> ZoneHVACBaseboardRadiantConvectiveWater_Impl::maximumWaterFlowRate() const {
      return getDouble(ZoneHVAC_Baseboard_RadiantConvective_WaterFields::MaximumWaterFlowRate, true);
    }

    bool ZoneHVACBaseboardRadiantConvectiveWater_Impl::isMaximumWaterFlowRateAutosized() const {
      if (auto value = getString(ZoneHVAC_Baseboard_RadiantConvective_WaterFields::MaximumWaterFlowRate, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    bool ZoneHVACBaseboardRadiantConvectiveWater_Impl::setMaximumWaterFlowRate(double maximumWaterFlowRate) {
      const bool result = setDouble(ZoneHVAC_Baseboard_RadiantConvective_WaterFields::MaximumWaterFlowRate, maximumWaterFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACBaseboardRadiantConvectiveWater_Impl::autosizeMaximumWaterFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_RadiantConvective_WaterFields::MaximumWaterFlowRate, "autosize"));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
