/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "CoilHeatingSteam.hpp"
#include "CoilHeatingSteam_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Heating_Steam_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  CoilHeatingSteam::CoilHeatingSteam(const Model& model) : ModelObject(CoilHeatingSteam::iddObjectType(), model) {}

  CoilHeatingSteam::CoilHeatingSteam(std::shared_ptr<detail::CoilHeatingSteam_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType CoilHeatingSteam::iddObjectType() {
    return IddObjectType::Coil_Heating_Steam;
  }

  std::vector<std::string> CoilHeatingSteam::coilControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Coil_Heating_SteamFields::CoilControlType);
  }

  boost::optional<double> CoilHeatingSteam::maximumSteamFlowRate() const {
    return getImpl<detail::CoilHeatingSteam_Impl>()->maximumSteamFlowRate();
  }

  bool CoilHeatingSteam::isMaximumSteamFlowRateAutosized() const {
    return getImpl<detail::CoilHeatingSteam_Impl>()->isMaximumSteamFlowRateAutosized();
  }

  bool CoilHeatingSteam::setMaximumSteamFlowRate(double maximumSteamFlowRate) {
    return getImpl<detail::CoilHeatingSteam_Impl>()->setMaximumSteamFlowRate(maximumSteamFlowRate);
  }

  void CoilHeatingSteam::resetMaximumSteamFlowRate() {
    getImpl<detail::CoilHeatingSteam_Impl>()->resetMaximumSteamFlowRate();
  }

  void CoilHeatingSteam::autosizeMaximumSteamFlowRate() {
    getImpl<detail::CoilHeatingSteam_Impl>()->autosizeMaximumSteamFlowRate();
  }

  boost::optional<double> CoilHeatingSteam::degreeofSubCooling() const {
    return getImpl<detail::CoilHeatingSteam_Impl>()->degreeofSubCooling();
  }

  bool CoilHeatingSteam::setDegreeofSubCooling(double degreeofSubCooling) {
    return getImpl<detail::CoilHeatingSteam_Impl>()->setDegreeofSubCooling(degreeofSubCooling);
  }

  void CoilHeatingSteam::resetDegreeofSubCooling() {
    getImpl<detail::CoilHeatingSteam_Impl>()->resetDegreeofSubCooling();
  }

  double CoilHeatingSteam::degreeofLoopSubCooling() const {
    return getImpl<detail::CoilHeatingSteam_Impl>()->degreeofLoopSubCooling();
  }

  bool CoilHeatingSteam::isDegreeofLoopSubCoolingDefaulted() const {
    return getImpl<detail::CoilHeatingSteam_Impl>()->isDegreeofLoopSubCoolingDefaulted();
  }

  bool CoilHeatingSteam::setDegreeofLoopSubCooling(double degreeofLoopSubCooling) {
    return getImpl<detail::CoilHeatingSteam_Impl>()->setDegreeofLoopSubCooling(degreeofLoopSubCooling);
  }

  void CoilHeatingSteam::resetDegreeofLoopSubCooling() {
    getImpl<detail::CoilHeatingSteam_Impl>()->resetDegreeofLoopSubCooling();
  }

  boost::optional<std::string> CoilHeatingSteam::coilControlType() const {
    return getImpl<detail::CoilHeatingSteam_Impl>()->coilControlType();
  }

  bool CoilHeatingSteam::setCoilControlType(const std::string& coilControlType) {
    return getImpl<detail::CoilHeatingSteam_Impl>()->setCoilControlType(coilControlType);
  }

  void CoilHeatingSteam::resetCoilControlType() {
    getImpl<detail::CoilHeatingSteam_Impl>()->resetCoilControlType();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> CoilHeatingSteam_Impl::maximumSteamFlowRate() const {
      return getDouble(openstudio::Coil_Heating_SteamFields::MaximumSteamFlowRate, true);
    }

    bool CoilHeatingSteam_Impl::isMaximumSteamFlowRateAutosized() const {
      if (const auto value = getString(openstudio::Coil_Heating_SteamFields::MaximumSteamFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool CoilHeatingSteam_Impl::setMaximumSteamFlowRate(double maximumSteamFlowRate) {
      return setDouble(openstudio::Coil_Heating_SteamFields::MaximumSteamFlowRate, maximumSteamFlowRate);
    }

    void CoilHeatingSteam_Impl::resetMaximumSteamFlowRate() {
      OS_ASSERT(setString(openstudio::Coil_Heating_SteamFields::MaximumSteamFlowRate, ""));
    }

    void CoilHeatingSteam_Impl::autosizeMaximumSteamFlowRate() {
      OS_ASSERT(setString(openstudio::Coil_Heating_SteamFields::MaximumSteamFlowRate, "autosize"));
    }

    boost::optional<double> CoilHeatingSteam_Impl::degreeofSubCooling() const {
      return getDouble(openstudio::Coil_Heating_SteamFields::DegreeofSubCooling, true);
    }

    bool CoilHeatingSteam_Impl::setDegreeofSubCooling(double degreeofSubCooling) {
      return setDouble(openstudio::Coil_Heating_SteamFields::DegreeofSubCooling, degreeofSubCooling);
    }

    void CoilHeatingSteam_Impl::resetDegreeofSubCooling() {
      OS_ASSERT(setString(openstudio::Coil_Heating_SteamFields::DegreeofSubCooling, ""));
    }

    double CoilHeatingSteam_Impl::degreeofLoopSubCooling() const {
      const auto value = getDouble(openstudio::Coil_Heating_SteamFields::DegreeofLoopSubCooling, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingSteam_Impl::isDegreeofLoopSubCoolingDefaulted() const {
      return isEmpty(openstudio::Coil_Heating_SteamFields::DegreeofLoopSubCooling);
    }

    bool CoilHeatingSteam_Impl::setDegreeofLoopSubCooling(double degreeofLoopSubCooling) {
      return setDouble(openstudio::Coil_Heating_SteamFields::DegreeofLoopSubCooling, degreeofLoopSubCooling);
    }

    void CoilHeatingSteam_Impl::resetDegreeofLoopSubCooling() {
      OS_ASSERT(setString(openstudio::Coil_Heating_SteamFields::DegreeofLoopSubCooling, ""));
    }

    boost::optional<std::string> CoilHeatingSteam_Impl::coilControlType() const {
      return getString(openstudio::Coil_Heating_SteamFields::CoilControlType, true);
    }

    bool CoilHeatingSteam_Impl::setCoilControlType(const std::string& coilControlType) {
      return setString(openstudio::Coil_Heating_SteamFields::CoilControlType, coilControlType);
    }

    void CoilHeatingSteam_Impl::resetCoilControlType() {
      OS_ASSERT(setString(openstudio::Coil_Heating_SteamFields::CoilControlType, ""));
    }

    std::vector<std::string> CoilHeatingSteam_Impl::coilControlTypeValues() const {
      return openstudio::epmodel::CoilHeatingSteam::coilControlTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
