/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "ZoneHVACOutdoorAirUnit.hpp"
#include "ZoneHVACOutdoorAirUnit_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/ZoneHVAC_OutdoorAirUnit_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneHVACOutdoorAirUnit::ZoneHVACOutdoorAirUnit(const Model& model) : ModelObject(ZoneHVACOutdoorAirUnit::iddObjectType(), model) {}

  ZoneHVACOutdoorAirUnit::ZoneHVACOutdoorAirUnit(std::shared_ptr<detail::ZoneHVACOutdoorAirUnit_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ZoneHVACOutdoorAirUnit::iddObjectType() {
    return IddObjectType::ZoneHVAC_OutdoorAirUnit;
  }

  std::vector<std::string> ZoneHVACOutdoorAirUnit::supplyFanPlacementValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::ZoneHVAC_OutdoorAirUnitFields::SupplyFanPlacement);
  }

  std::vector<std::string> ZoneHVACOutdoorAirUnit::unitControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::ZoneHVAC_OutdoorAirUnitFields::UnitControlType);
  }

  boost::optional<double> ZoneHVACOutdoorAirUnit::outdoorAirFlowRate() const {
    return getImpl<detail::ZoneHVACOutdoorAirUnit_Impl>()->outdoorAirFlowRate();
  }

  bool ZoneHVACOutdoorAirUnit::isOutdoorAirFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACOutdoorAirUnit_Impl>()->isOutdoorAirFlowRateAutosized();
  }

  bool ZoneHVACOutdoorAirUnit::setOutdoorAirFlowRate(double outdoorAirFlowRate) {
    return getImpl<detail::ZoneHVACOutdoorAirUnit_Impl>()->setOutdoorAirFlowRate(outdoorAirFlowRate);
  }

  void ZoneHVACOutdoorAirUnit::autosizeOutdoorAirFlowRate() {
    getImpl<detail::ZoneHVACOutdoorAirUnit_Impl>()->autosizeOutdoorAirFlowRate();
  }

  boost::optional<double> ZoneHVACOutdoorAirUnit::exhaustAirFlowRate() const {
    return getImpl<detail::ZoneHVACOutdoorAirUnit_Impl>()->exhaustAirFlowRate();
  }

  bool ZoneHVACOutdoorAirUnit::isExhaustAirFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACOutdoorAirUnit_Impl>()->isExhaustAirFlowRateAutosized();
  }

  bool ZoneHVACOutdoorAirUnit::setExhaustAirFlowRate(double exhaustAirFlowRate) {
    return getImpl<detail::ZoneHVACOutdoorAirUnit_Impl>()->setExhaustAirFlowRate(exhaustAirFlowRate);
  }

  void ZoneHVACOutdoorAirUnit::autosizeExhaustAirFlowRate() {
    getImpl<detail::ZoneHVACOutdoorAirUnit_Impl>()->autosizeExhaustAirFlowRate();
  }

  void ZoneHVACOutdoorAirUnit::resetExhaustAirFlowRate() {
    getImpl<detail::ZoneHVACOutdoorAirUnit_Impl>()->resetExhaustAirFlowRate();
  }

  std::string ZoneHVACOutdoorAirUnit::supplyFanPlacement() const {
    return getImpl<detail::ZoneHVACOutdoorAirUnit_Impl>()->supplyFanPlacement();
  }

  bool ZoneHVACOutdoorAirUnit::setSupplyFanPlacement(const std::string& supplyFanPlacement) {
    return getImpl<detail::ZoneHVACOutdoorAirUnit_Impl>()->setSupplyFanPlacement(supplyFanPlacement);
  }

  bool ZoneHVACOutdoorAirUnit::isSupplyFanPlacementDefaulted() const {
    return getImpl<detail::ZoneHVACOutdoorAirUnit_Impl>()->isSupplyFanPlacementDefaulted();
  }

  void ZoneHVACOutdoorAirUnit::resetSupplyFanPlacement() {
    getImpl<detail::ZoneHVACOutdoorAirUnit_Impl>()->resetSupplyFanPlacement();
  }

  std::string ZoneHVACOutdoorAirUnit::unitControlType() const {
    return getImpl<detail::ZoneHVACOutdoorAirUnit_Impl>()->unitControlType();
  }

  bool ZoneHVACOutdoorAirUnit::setUnitControlType(const std::string& unitControlType) {
    return getImpl<detail::ZoneHVACOutdoorAirUnit_Impl>()->setUnitControlType(unitControlType);
  }

  bool ZoneHVACOutdoorAirUnit::isUnitControlTypeDefaulted() const {
    return getImpl<detail::ZoneHVACOutdoorAirUnit_Impl>()->isUnitControlTypeDefaulted();
  }

  void ZoneHVACOutdoorAirUnit::resetUnitControlType() {
    getImpl<detail::ZoneHVACOutdoorAirUnit_Impl>()->resetUnitControlType();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> ZoneHVACOutdoorAirUnit_Impl::outdoorAirFlowRate() const {
      return getDouble(openstudio::ZoneHVAC_OutdoorAirUnitFields::OutdoorAirFlowRate, true);
    }

    bool ZoneHVACOutdoorAirUnit_Impl::isOutdoorAirFlowRateAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(openstudio::ZoneHVAC_OutdoorAirUnitFields::OutdoorAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "autosize");
      }
      return result;
    }

    bool ZoneHVACOutdoorAirUnit_Impl::setOutdoorAirFlowRate(double outdoorAirFlowRate) {
      return setDouble(openstudio::ZoneHVAC_OutdoorAirUnitFields::OutdoorAirFlowRate, outdoorAirFlowRate);
    }

    void ZoneHVACOutdoorAirUnit_Impl::autosizeOutdoorAirFlowRate() {
      const bool result = setString(openstudio::ZoneHVAC_OutdoorAirUnitFields::OutdoorAirFlowRate, "autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACOutdoorAirUnit_Impl::exhaustAirFlowRate() const {
      return getDouble(openstudio::ZoneHVAC_OutdoorAirUnitFields::ExhaustAirFlowRate, true);
    }

    bool ZoneHVACOutdoorAirUnit_Impl::isExhaustAirFlowRateAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(openstudio::ZoneHVAC_OutdoorAirUnitFields::ExhaustAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "autosize");
      }
      return result;
    }

    bool ZoneHVACOutdoorAirUnit_Impl::setExhaustAirFlowRate(double exhaustAirFlowRate) {
      return setDouble(openstudio::ZoneHVAC_OutdoorAirUnitFields::ExhaustAirFlowRate, exhaustAirFlowRate);
    }

    void ZoneHVACOutdoorAirUnit_Impl::autosizeExhaustAirFlowRate() {
      const bool result = setString(openstudio::ZoneHVAC_OutdoorAirUnitFields::ExhaustAirFlowRate, "autosize");
      OS_ASSERT(result);
    }

    void ZoneHVACOutdoorAirUnit_Impl::resetExhaustAirFlowRate() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_OutdoorAirUnitFields::ExhaustAirFlowRate, ""));
    }

    std::string ZoneHVACOutdoorAirUnit_Impl::supplyFanPlacement() const {
      const auto value = getString(openstudio::ZoneHVAC_OutdoorAirUnitFields::SupplyFanPlacement, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACOutdoorAirUnit_Impl::setSupplyFanPlacement(const std::string& supplyFanPlacement) {
      return setString(openstudio::ZoneHVAC_OutdoorAirUnitFields::SupplyFanPlacement, supplyFanPlacement);
    }

    bool ZoneHVACOutdoorAirUnit_Impl::isSupplyFanPlacementDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_OutdoorAirUnitFields::SupplyFanPlacement);
    }

    void ZoneHVACOutdoorAirUnit_Impl::resetSupplyFanPlacement() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_OutdoorAirUnitFields::SupplyFanPlacement, ""));
    }

    std::string ZoneHVACOutdoorAirUnit_Impl::unitControlType() const {
      const auto value = getString(openstudio::ZoneHVAC_OutdoorAirUnitFields::UnitControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACOutdoorAirUnit_Impl::setUnitControlType(const std::string& unitControlType) {
      return setString(openstudio::ZoneHVAC_OutdoorAirUnitFields::UnitControlType, unitControlType);
    }

    bool ZoneHVACOutdoorAirUnit_Impl::isUnitControlTypeDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_OutdoorAirUnitFields::UnitControlType);
    }

    void ZoneHVACOutdoorAirUnit_Impl::resetUnitControlType() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_OutdoorAirUnitFields::UnitControlType, ""));
    }

    std::vector<std::string> ZoneHVACOutdoorAirUnit_Impl::supplyFanPlacementValues() const {
      return openstudio::epmodel::ZoneHVACOutdoorAirUnit::supplyFanPlacementValues();
    }

    std::vector<std::string> ZoneHVACOutdoorAirUnit_Impl::unitControlTypeValues() const {
      return openstudio::epmodel::ZoneHVACOutdoorAirUnit::unitControlTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
