/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "scaffolds/ZoneHVACBaseboardRadiantConvectiveSteam.hpp"
#include "scaffolds/ZoneHVACBaseboardRadiantConvectiveSteam_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_Baseboard_RadiantConvective_Steam_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneHVACBaseboardRadiantConvectiveSteam::ZoneHVACBaseboardRadiantConvectiveSteam(const Model& model)
    : ModelObject(ZoneHVACBaseboardRadiantConvectiveSteam::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ZoneHVACBaseboardRadiantConvectiveSteam_Impl>());

    autosizeHeatingDesignCapacity();
    OS_ASSERT(setDegreeofSubCooling(5.0));
    autosizeMaximumSteamFlowRate();
  }

  ZoneHVACBaseboardRadiantConvectiveSteam::ZoneHVACBaseboardRadiantConvectiveSteam(
    std::shared_ptr<detail::ZoneHVACBaseboardRadiantConvectiveSteam_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneHVACBaseboardRadiantConvectiveSteam::iddObjectType() {
    return IddObjectType::ZoneHVAC_Baseboard_RadiantConvective_Steam;
  }

  boost::optional<double> ZoneHVACBaseboardRadiantConvectiveSteam::heatingDesignCapacity() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveSteam_Impl>()->heatingDesignCapacity();
  }

  bool ZoneHVACBaseboardRadiantConvectiveSteam::isHeatingDesignCapacityAutosized() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveSteam_Impl>()->isHeatingDesignCapacityAutosized();
  }

  bool ZoneHVACBaseboardRadiantConvectiveSteam::setHeatingDesignCapacity(double heatingDesignCapacity) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveSteam_Impl>()->setHeatingDesignCapacity(heatingDesignCapacity);
  }

  void ZoneHVACBaseboardRadiantConvectiveSteam::autosizeHeatingDesignCapacity() {
    getImpl<detail::ZoneHVACBaseboardRadiantConvectiveSteam_Impl>()->autosizeHeatingDesignCapacity();
  }

  boost::optional<double> ZoneHVACBaseboardRadiantConvectiveSteam::degreeofSubCooling() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveSteam_Impl>()->degreeofSubCooling();
  }

  bool ZoneHVACBaseboardRadiantConvectiveSteam::isDegreeofSubCoolingDefaulted() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveSteam_Impl>()->isDegreeofSubCoolingDefaulted();
  }

  bool ZoneHVACBaseboardRadiantConvectiveSteam::setDegreeofSubCooling(double degreeofSubCooling) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveSteam_Impl>()->setDegreeofSubCooling(degreeofSubCooling);
  }

  void ZoneHVACBaseboardRadiantConvectiveSteam::resetDegreeofSubCooling() {
    getImpl<detail::ZoneHVACBaseboardRadiantConvectiveSteam_Impl>()->resetDegreeofSubCooling();
  }

  boost::optional<double> ZoneHVACBaseboardRadiantConvectiveSteam::maximumSteamFlowRate() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveSteam_Impl>()->maximumSteamFlowRate();
  }

  bool ZoneHVACBaseboardRadiantConvectiveSteam::isMaximumSteamFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveSteam_Impl>()->isMaximumSteamFlowRateAutosized();
  }

  bool ZoneHVACBaseboardRadiantConvectiveSteam::setMaximumSteamFlowRate(double maximumSteamFlowRate) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveSteam_Impl>()->setMaximumSteamFlowRate(maximumSteamFlowRate);
  }

  void ZoneHVACBaseboardRadiantConvectiveSteam::autosizeMaximumSteamFlowRate() {
    getImpl<detail::ZoneHVACBaseboardRadiantConvectiveSteam_Impl>()->autosizeMaximumSteamFlowRate();
  }

  namespace detail {

    boost::optional<double> ZoneHVACBaseboardRadiantConvectiveSteam_Impl::heatingDesignCapacity() const {
      return getDouble(ZoneHVAC_Baseboard_RadiantConvective_SteamFields::HeatingDesignCapacity, true);
    }

    bool ZoneHVACBaseboardRadiantConvectiveSteam_Impl::isHeatingDesignCapacityAutosized() const {
      if (auto value = getString(ZoneHVAC_Baseboard_RadiantConvective_SteamFields::HeatingDesignCapacity, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    bool ZoneHVACBaseboardRadiantConvectiveSteam_Impl::setHeatingDesignCapacity(double heatingDesignCapacity) {
      const bool result = setDouble(ZoneHVAC_Baseboard_RadiantConvective_SteamFields::HeatingDesignCapacity, heatingDesignCapacity);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACBaseboardRadiantConvectiveSteam_Impl::autosizeHeatingDesignCapacity() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_RadiantConvective_SteamFields::HeatingDesignCapacity, "autosize"));
    }

    boost::optional<double> ZoneHVACBaseboardRadiantConvectiveSteam_Impl::degreeofSubCooling() const {
      return getDouble(ZoneHVAC_Baseboard_RadiantConvective_SteamFields::DegreeofSubCooling, true);
    }

    bool ZoneHVACBaseboardRadiantConvectiveSteam_Impl::isDegreeofSubCoolingDefaulted() const {
      return isEmpty(ZoneHVAC_Baseboard_RadiantConvective_SteamFields::DegreeofSubCooling);
    }

    bool ZoneHVACBaseboardRadiantConvectiveSteam_Impl::setDegreeofSubCooling(double degreeofSubCooling) {
      const bool result = setDouble(ZoneHVAC_Baseboard_RadiantConvective_SteamFields::DegreeofSubCooling, degreeofSubCooling);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACBaseboardRadiantConvectiveSteam_Impl::resetDegreeofSubCooling() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_RadiantConvective_SteamFields::DegreeofSubCooling, ""));
    }

    boost::optional<double> ZoneHVACBaseboardRadiantConvectiveSteam_Impl::maximumSteamFlowRate() const {
      return getDouble(ZoneHVAC_Baseboard_RadiantConvective_SteamFields::MaximumSteamFlowRate, true);
    }

    bool ZoneHVACBaseboardRadiantConvectiveSteam_Impl::isMaximumSteamFlowRateAutosized() const {
      if (auto value = getString(ZoneHVAC_Baseboard_RadiantConvective_SteamFields::MaximumSteamFlowRate, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    bool ZoneHVACBaseboardRadiantConvectiveSteam_Impl::setMaximumSteamFlowRate(double maximumSteamFlowRate) {
      const bool result = setDouble(ZoneHVAC_Baseboard_RadiantConvective_SteamFields::MaximumSteamFlowRate, maximumSteamFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACBaseboardRadiantConvectiveSteam_Impl::autosizeMaximumSteamFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_RadiantConvective_SteamFields::MaximumSteamFlowRate, "autosize"));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
