/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SpaceInfiltrationDesignFlowRate.hpp"
#include "SpaceInfiltrationDesignFlowRate_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Compare.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneInfiltration_DesignFlowRate_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace detail {

    SpaceInfiltrationDesignFlowRate_Impl::SpaceInfiltrationDesignFlowRate_Impl(const IdfObject& object, Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(object, model, keepHandle) {
      OS_ASSERT(object.iddObject().type() == SpaceInfiltrationDesignFlowRate::iddObjectType());
    }

    SpaceInfiltrationDesignFlowRate_Impl::SpaceInfiltrationDesignFlowRate_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                                                               Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(other, model, keepHandle) {
      OS_ASSERT(other.iddObject().type() == SpaceInfiltrationDesignFlowRate::iddObjectType());
    }

    SpaceInfiltrationDesignFlowRate_Impl::SpaceInfiltrationDesignFlowRate_Impl(const SpaceInfiltrationDesignFlowRate_Impl& other, Model_Impl* model,
                                                                               bool keepHandle)
      : ModelObject_Impl(other, model, keepHandle) {}

    std::string SpaceInfiltrationDesignFlowRate_Impl::designFlowRateCalculationMethod() const {
      boost::optional<std::string> value = getString(ZoneInfiltration_DesignFlowRateFields::DesignFlowRateCalculationMethod, true);
      OS_ASSERT(value);
      return value.get();
    }

    boost::optional<double> SpaceInfiltrationDesignFlowRate_Impl::designFlowRate() const {
      boost::optional<double> result;
      const auto method = this->designFlowRateCalculationMethod();
      if (istringEqual("Flow/Zone", method) || istringEqual("Flow/Space", method)) {
        result = getDouble(ZoneInfiltration_DesignFlowRateFields::DesignFlowRate, true);
      }
      return result;
    }

    bool SpaceInfiltrationDesignFlowRate_Impl::setDesignFlowRate(double designFlowRate) {
      bool result = true;
      if (designFlowRate < 0) {
        result = false;
      } else {
        result = setDouble(ZoneInfiltration_DesignFlowRateFields::DesignFlowRate, designFlowRate);
        if (result) {
          result = setString(ZoneInfiltration_DesignFlowRateFields::DesignFlowRateCalculationMethod, "Flow/Zone");
          OS_ASSERT(result);
        }
      }
      return result;
    }

    boost::optional<double> SpaceInfiltrationDesignFlowRate_Impl::flowperSpaceFloorArea() const {
      boost::optional<double> result;
      if (istringEqual("Flow/Area", this->designFlowRateCalculationMethod())) {
        result = getDouble(ZoneInfiltration_DesignFlowRateFields::FlowRateperFloorArea, true);
      }
      return result;
    }

    bool SpaceInfiltrationDesignFlowRate_Impl::setFlowperSpaceFloorArea(double flowperSpaceFloorArea) {
      bool result = true;
      if (flowperSpaceFloorArea < 0) {
        result = false;
      } else {
        result = setDouble(ZoneInfiltration_DesignFlowRateFields::FlowRateperFloorArea, flowperSpaceFloorArea);
        if (result) {
          result = setString(ZoneInfiltration_DesignFlowRateFields::DesignFlowRateCalculationMethod, "Flow/Area");
          OS_ASSERT(result);
          result = setString(ZoneInfiltration_DesignFlowRateFields::DesignFlowRate, "");
          OS_ASSERT(result);
          result = setString(ZoneInfiltration_DesignFlowRateFields::FlowRateperExteriorSurfaceArea, "");
          OS_ASSERT(result);
          result = setString(ZoneInfiltration_DesignFlowRateFields::AirChangesperHour, "");
          OS_ASSERT(result);
        }
      }
      return result;
    }

    boost::optional<double> SpaceInfiltrationDesignFlowRate_Impl::flowperExteriorSurfaceArea() const {
      boost::optional<double> result;
      if (istringEqual("Flow/ExteriorArea", this->designFlowRateCalculationMethod())) {
        result = getDouble(ZoneInfiltration_DesignFlowRateFields::FlowRateperExteriorSurfaceArea, true);
      }
      return result;
    }

    bool SpaceInfiltrationDesignFlowRate_Impl::setFlowperExteriorSurfaceArea(double flowperExteriorSurfaceArea) {
      bool result = true;
      if (flowperExteriorSurfaceArea < 0) {
        result = false;
      } else {
        result = setDouble(ZoneInfiltration_DesignFlowRateFields::FlowRateperExteriorSurfaceArea, flowperExteriorSurfaceArea);
        if (result) {
          result = setString(ZoneInfiltration_DesignFlowRateFields::DesignFlowRateCalculationMethod, "Flow/ExteriorArea");
          OS_ASSERT(result);
          result = setString(ZoneInfiltration_DesignFlowRateFields::DesignFlowRate, "");
          OS_ASSERT(result);
          result = setString(ZoneInfiltration_DesignFlowRateFields::FlowRateperFloorArea, "");
          OS_ASSERT(result);
          result = setString(ZoneInfiltration_DesignFlowRateFields::AirChangesperHour, "");
          OS_ASSERT(result);
        }
      }
      return result;
    }

    boost::optional<double> SpaceInfiltrationDesignFlowRate_Impl::flowperExteriorWallArea() const {
      boost::optional<double> result;
      if (istringEqual("Flow/ExteriorWallArea", this->designFlowRateCalculationMethod())) {
        result = getDouble(ZoneInfiltration_DesignFlowRateFields::FlowRateperExteriorSurfaceArea, true);
      }
      return result;
    }

    bool SpaceInfiltrationDesignFlowRate_Impl::setFlowperExteriorWallArea(double flowperExteriorWallArea) {
      bool result = true;
      if (flowperExteriorWallArea < 0) {
        result = false;
      } else {
        result = setDouble(ZoneInfiltration_DesignFlowRateFields::FlowRateperExteriorSurfaceArea, flowperExteriorWallArea);
        if (result) {
          result = setString(ZoneInfiltration_DesignFlowRateFields::DesignFlowRateCalculationMethod, "Flow/ExteriorWallArea");
          OS_ASSERT(result);
          result = setString(ZoneInfiltration_DesignFlowRateFields::DesignFlowRate, "");
          OS_ASSERT(result);
          result = setString(ZoneInfiltration_DesignFlowRateFields::FlowRateperFloorArea, "");
          OS_ASSERT(result);
          result = setString(ZoneInfiltration_DesignFlowRateFields::AirChangesperHour, "");
          OS_ASSERT(result);
        }
      }
      return result;
    }

    boost::optional<double> SpaceInfiltrationDesignFlowRate_Impl::airChangesperHour() const {
      boost::optional<double> result;
      if (istringEqual("AirChanges/Hour", this->designFlowRateCalculationMethod())) {
        result = getDouble(ZoneInfiltration_DesignFlowRateFields::AirChangesperHour, true);
      }
      return result;
    }

    bool SpaceInfiltrationDesignFlowRate_Impl::setAirChangesperHour(double airChangesperHour) {
      bool result = true;
      if (airChangesperHour < 0) {
        result = false;
      } else {
        result = setDouble(ZoneInfiltration_DesignFlowRateFields::AirChangesperHour, airChangesperHour);
        if (result) {
          result = setString(ZoneInfiltration_DesignFlowRateFields::DesignFlowRateCalculationMethod, "AirChanges/Hour");
          OS_ASSERT(result);
          result = setString(ZoneInfiltration_DesignFlowRateFields::DesignFlowRate, "");
          OS_ASSERT(result);
          result = setString(ZoneInfiltration_DesignFlowRateFields::FlowRateperFloorArea, "");
          OS_ASSERT(result);
          result = setString(ZoneInfiltration_DesignFlowRateFields::FlowRateperExteriorSurfaceArea, "");
          OS_ASSERT(result);
        }
      }
      return result;
    }

    double SpaceInfiltrationDesignFlowRate_Impl::constantTermCoefficient() const {
      boost::optional<double> value = getDouble(ZoneInfiltration_DesignFlowRateFields::ConstantTermCoefficient, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SpaceInfiltrationDesignFlowRate_Impl::isConstantTermCoefficientDefaulted() const {
      return isEmpty(ZoneInfiltration_DesignFlowRateFields::ConstantTermCoefficient);
    }

    bool SpaceInfiltrationDesignFlowRate_Impl::setConstantTermCoefficient(double constantTermCoefficient) {
      return setDouble(ZoneInfiltration_DesignFlowRateFields::ConstantTermCoefficient, constantTermCoefficient);
    }

    void SpaceInfiltrationDesignFlowRate_Impl::resetConstantTermCoefficient() {
      const bool result = setString(ZoneInfiltration_DesignFlowRateFields::ConstantTermCoefficient, "");
      OS_ASSERT(result);
    }

    double SpaceInfiltrationDesignFlowRate_Impl::temperatureTermCoefficient() const {
      boost::optional<double> value = getDouble(ZoneInfiltration_DesignFlowRateFields::TemperatureTermCoefficient, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SpaceInfiltrationDesignFlowRate_Impl::isTemperatureTermCoefficientDefaulted() const {
      return isEmpty(ZoneInfiltration_DesignFlowRateFields::TemperatureTermCoefficient);
    }

    bool SpaceInfiltrationDesignFlowRate_Impl::setTemperatureTermCoefficient(double temperatureTermCoefficient) {
      return setDouble(ZoneInfiltration_DesignFlowRateFields::TemperatureTermCoefficient, temperatureTermCoefficient);
    }

    void SpaceInfiltrationDesignFlowRate_Impl::resetTemperatureTermCoefficient() {
      const bool result = setString(ZoneInfiltration_DesignFlowRateFields::TemperatureTermCoefficient, "");
      OS_ASSERT(result);
    }

    double SpaceInfiltrationDesignFlowRate_Impl::velocityTermCoefficient() const {
      boost::optional<double> value = getDouble(ZoneInfiltration_DesignFlowRateFields::VelocityTermCoefficient, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SpaceInfiltrationDesignFlowRate_Impl::isVelocityTermCoefficientDefaulted() const {
      return isEmpty(ZoneInfiltration_DesignFlowRateFields::VelocityTermCoefficient);
    }

    bool SpaceInfiltrationDesignFlowRate_Impl::setVelocityTermCoefficient(double velocityTermCoefficient) {
      return setDouble(ZoneInfiltration_DesignFlowRateFields::VelocityTermCoefficient, velocityTermCoefficient);
    }

    void SpaceInfiltrationDesignFlowRate_Impl::resetVelocityTermCoefficient() {
      const bool result = setString(ZoneInfiltration_DesignFlowRateFields::VelocityTermCoefficient, "");
      OS_ASSERT(result);
    }

    double SpaceInfiltrationDesignFlowRate_Impl::velocitySquaredTermCoefficient() const {
      boost::optional<double> value = getDouble(ZoneInfiltration_DesignFlowRateFields::VelocitySquaredTermCoefficient, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SpaceInfiltrationDesignFlowRate_Impl::isVelocitySquaredTermCoefficientDefaulted() const {
      return isEmpty(ZoneInfiltration_DesignFlowRateFields::VelocitySquaredTermCoefficient);
    }

    bool SpaceInfiltrationDesignFlowRate_Impl::setVelocitySquaredTermCoefficient(double velocitySquaredTermCoefficient) {
      return setDouble(ZoneInfiltration_DesignFlowRateFields::VelocitySquaredTermCoefficient, velocitySquaredTermCoefficient);
    }

    void SpaceInfiltrationDesignFlowRate_Impl::resetVelocitySquaredTermCoefficient() {
      const bool result = setString(ZoneInfiltration_DesignFlowRateFields::VelocitySquaredTermCoefficient, "");
      OS_ASSERT(result);
    }

    std::string SpaceInfiltrationDesignFlowRate_Impl::densityBasis() const {
      boost::optional<std::string> value = getString(ZoneInfiltration_DesignFlowRateFields::DensityBasis, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SpaceInfiltrationDesignFlowRate_Impl::setDensityBasis(const std::string& densityBasis) {
      return setString(ZoneInfiltration_DesignFlowRateFields::DensityBasis, densityBasis);
    }

  }  // namespace detail

  SpaceInfiltrationDesignFlowRate::SpaceInfiltrationDesignFlowRate(const Model& model)
    : ModelObject(SpaceInfiltrationDesignFlowRate::iddObjectType(), model) {
    OS_ASSERT(setDesignFlowRate(0.0));
    OS_ASSERT(setDensityBasis("Outdoor"));
  }

  SpaceInfiltrationDesignFlowRate::SpaceInfiltrationDesignFlowRate(std::shared_ptr<detail::SpaceInfiltrationDesignFlowRate_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SpaceInfiltrationDesignFlowRate::iddObjectType() {
    return IddObjectType::ZoneInfiltration_DesignFlowRate;
  }

  std::vector<std::string> SpaceInfiltrationDesignFlowRate::designFlowRateCalculationMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          ZoneInfiltration_DesignFlowRateFields::DesignFlowRateCalculationMethod);
  }

  std::vector<std::string> SpaceInfiltrationDesignFlowRate::densityBasisValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), ZoneInfiltration_DesignFlowRateFields::DensityBasis);
  }

  std::string SpaceInfiltrationDesignFlowRate::designFlowRateCalculationMethod() const {
    return getImpl<detail::SpaceInfiltrationDesignFlowRate_Impl>()->designFlowRateCalculationMethod();
  }

  boost::optional<double> SpaceInfiltrationDesignFlowRate::designFlowRate() const {
    return getImpl<detail::SpaceInfiltrationDesignFlowRate_Impl>()->designFlowRate();
  }

  boost::optional<double> SpaceInfiltrationDesignFlowRate::flowperSpaceFloorArea() const {
    return getImpl<detail::SpaceInfiltrationDesignFlowRate_Impl>()->flowperSpaceFloorArea();
  }

  boost::optional<double> SpaceInfiltrationDesignFlowRate::flowperExteriorSurfaceArea() const {
    return getImpl<detail::SpaceInfiltrationDesignFlowRate_Impl>()->flowperExteriorSurfaceArea();
  }

  boost::optional<double> SpaceInfiltrationDesignFlowRate::flowperExteriorWallArea() const {
    return getImpl<detail::SpaceInfiltrationDesignFlowRate_Impl>()->flowperExteriorWallArea();
  }

  boost::optional<double> SpaceInfiltrationDesignFlowRate::airChangesperHour() const {
    return getImpl<detail::SpaceInfiltrationDesignFlowRate_Impl>()->airChangesperHour();
  }

  double SpaceInfiltrationDesignFlowRate::constantTermCoefficient() const {
    return getImpl<detail::SpaceInfiltrationDesignFlowRate_Impl>()->constantTermCoefficient();
  }

  bool SpaceInfiltrationDesignFlowRate::isConstantTermCoefficientDefaulted() const {
    return getImpl<detail::SpaceInfiltrationDesignFlowRate_Impl>()->isConstantTermCoefficientDefaulted();
  }

  double SpaceInfiltrationDesignFlowRate::temperatureTermCoefficient() const {
    return getImpl<detail::SpaceInfiltrationDesignFlowRate_Impl>()->temperatureTermCoefficient();
  }

  bool SpaceInfiltrationDesignFlowRate::isTemperatureTermCoefficientDefaulted() const {
    return getImpl<detail::SpaceInfiltrationDesignFlowRate_Impl>()->isTemperatureTermCoefficientDefaulted();
  }

  double SpaceInfiltrationDesignFlowRate::velocityTermCoefficient() const {
    return getImpl<detail::SpaceInfiltrationDesignFlowRate_Impl>()->velocityTermCoefficient();
  }

  bool SpaceInfiltrationDesignFlowRate::isVelocityTermCoefficientDefaulted() const {
    return getImpl<detail::SpaceInfiltrationDesignFlowRate_Impl>()->isVelocityTermCoefficientDefaulted();
  }

  double SpaceInfiltrationDesignFlowRate::velocitySquaredTermCoefficient() const {
    return getImpl<detail::SpaceInfiltrationDesignFlowRate_Impl>()->velocitySquaredTermCoefficient();
  }

  bool SpaceInfiltrationDesignFlowRate::isVelocitySquaredTermCoefficientDefaulted() const {
    return getImpl<detail::SpaceInfiltrationDesignFlowRate_Impl>()->isVelocitySquaredTermCoefficientDefaulted();
  }

  bool SpaceInfiltrationDesignFlowRate::setDesignFlowRate(double designFlowRate) {
    return getImpl<detail::SpaceInfiltrationDesignFlowRate_Impl>()->setDesignFlowRate(designFlowRate);
  }

  bool SpaceInfiltrationDesignFlowRate::setFlowperSpaceFloorArea(double flowperSpaceFloorArea) {
    return getImpl<detail::SpaceInfiltrationDesignFlowRate_Impl>()->setFlowperSpaceFloorArea(flowperSpaceFloorArea);
  }

  bool SpaceInfiltrationDesignFlowRate::setFlowperExteriorSurfaceArea(double flowperExteriorSurfaceArea) {
    return getImpl<detail::SpaceInfiltrationDesignFlowRate_Impl>()->setFlowperExteriorSurfaceArea(flowperExteriorSurfaceArea);
  }

  bool SpaceInfiltrationDesignFlowRate::setFlowperExteriorWallArea(double flowperExteriorWallArea) {
    return getImpl<detail::SpaceInfiltrationDesignFlowRate_Impl>()->setFlowperExteriorWallArea(flowperExteriorWallArea);
  }

  bool SpaceInfiltrationDesignFlowRate::setAirChangesperHour(double airChangesperHour) {
    return getImpl<detail::SpaceInfiltrationDesignFlowRate_Impl>()->setAirChangesperHour(airChangesperHour);
  }

  bool SpaceInfiltrationDesignFlowRate::setConstantTermCoefficient(double constantTermCoefficient) {
    return getImpl<detail::SpaceInfiltrationDesignFlowRate_Impl>()->setConstantTermCoefficient(constantTermCoefficient);
  }

  void SpaceInfiltrationDesignFlowRate::resetConstantTermCoefficient() {
    getImpl<detail::SpaceInfiltrationDesignFlowRate_Impl>()->resetConstantTermCoefficient();
  }

  bool SpaceInfiltrationDesignFlowRate::setTemperatureTermCoefficient(double temperatureTermCoefficient) {
    return getImpl<detail::SpaceInfiltrationDesignFlowRate_Impl>()->setTemperatureTermCoefficient(temperatureTermCoefficient);
  }

  void SpaceInfiltrationDesignFlowRate::resetTemperatureTermCoefficient() {
    getImpl<detail::SpaceInfiltrationDesignFlowRate_Impl>()->resetTemperatureTermCoefficient();
  }

  bool SpaceInfiltrationDesignFlowRate::setVelocityTermCoefficient(double velocityTermCoefficient) {
    return getImpl<detail::SpaceInfiltrationDesignFlowRate_Impl>()->setVelocityTermCoefficient(velocityTermCoefficient);
  }

  void SpaceInfiltrationDesignFlowRate::resetVelocityTermCoefficient() {
    getImpl<detail::SpaceInfiltrationDesignFlowRate_Impl>()->resetVelocityTermCoefficient();
  }

  bool SpaceInfiltrationDesignFlowRate::setVelocitySquaredTermCoefficient(double velocitySquaredTermCoefficient) {
    return getImpl<detail::SpaceInfiltrationDesignFlowRate_Impl>()->setVelocitySquaredTermCoefficient(velocitySquaredTermCoefficient);
  }

  void SpaceInfiltrationDesignFlowRate::resetVelocitySquaredTermCoefficient() {
    getImpl<detail::SpaceInfiltrationDesignFlowRate_Impl>()->resetVelocitySquaredTermCoefficient();
  }

  std::string SpaceInfiltrationDesignFlowRate::densityBasis() const {
    return getImpl<detail::SpaceInfiltrationDesignFlowRate_Impl>()->densityBasis();
  }

  bool SpaceInfiltrationDesignFlowRate::setDensityBasis(const std::string& densityBasis) {
    return getImpl<detail::SpaceInfiltrationDesignFlowRate_Impl>()->setDensityBasis(densityBasis);
  }

}  // namespace epmodel
}  // namespace openstudio
