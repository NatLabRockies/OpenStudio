/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "PhotovoltaicPerformance/PhotovoltaicPerformanceSimple.hpp"
#include "PhotovoltaicPerformance/PhotovoltaicPerformanceSimple_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/PhotovoltaicPerformance_Simple_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  PhotovoltaicPerformanceSimple::PhotovoltaicPerformanceSimple(const Model& model)
    : ModelObject(PhotovoltaicPerformanceSimple::iddObjectType(), model) {
    getImpl<detail::PhotovoltaicPerformanceSimple_Impl>()->resetFixedEfficiency();
  }

  PhotovoltaicPerformanceSimple::PhotovoltaicPerformanceSimple(std::shared_ptr<detail::PhotovoltaicPerformanceSimple_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType PhotovoltaicPerformanceSimple::iddObjectType() {
    return IddObjectType::PhotovoltaicPerformance_Simple;
  }

  std::vector<std::string> PhotovoltaicPerformanceSimple::conversionEfficiencyInputModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PhotovoltaicPerformance_SimpleFields::ConversionEfficiencyInputMode);
  }

  double PhotovoltaicPerformanceSimple::fractionOfSurfaceAreaWithActiveSolarCells() const {
    return getImpl<detail::PhotovoltaicPerformanceSimple_Impl>()->fractionOfSurfaceAreaWithActiveSolarCells();
  }

  bool PhotovoltaicPerformanceSimple::isfractionOfSurfaceAreaWithActiveSolarCellsDefaulted() const {
    return getImpl<detail::PhotovoltaicPerformanceSimple_Impl>()->isfractionOfSurfaceAreaWithActiveSolarCellsDefaulted();
  }

  bool PhotovoltaicPerformanceSimple::setFractionOfSurfaceAreaWithActiveSolarCells(double fractionOfSurfaceAreaWithActiveSolarCells) {
    return getImpl<detail::PhotovoltaicPerformanceSimple_Impl>()->setFractionOfSurfaceAreaWithActiveSolarCells(
      fractionOfSurfaceAreaWithActiveSolarCells);
  }

  void PhotovoltaicPerformanceSimple::resetFractionOfSurfaceAreaWithActiveSolarCells() {
    getImpl<detail::PhotovoltaicPerformanceSimple_Impl>()->resetFractionOfSurfaceAreaWithActiveSolarCells();
  }

  std::string PhotovoltaicPerformanceSimple::conversionEfficiencyInputMode() const {
    return getImpl<detail::PhotovoltaicPerformanceSimple_Impl>()->conversionEfficiencyInputMode();
  }

  bool PhotovoltaicPerformanceSimple::setConversionEfficiencyInputMode(const std::string& conversionEfficiencyInputMode) {
    return getImpl<detail::PhotovoltaicPerformanceSimple_Impl>()->setConversionEfficiencyInputMode(conversionEfficiencyInputMode);
  }

  boost::optional<double> PhotovoltaicPerformanceSimple::fixedEfficiency() const {
    return getImpl<detail::PhotovoltaicPerformanceSimple_Impl>()->fixedEfficiency();
  }

  bool PhotovoltaicPerformanceSimple::setFixedEfficiency(double fixedEfficiency) {
    return getImpl<detail::PhotovoltaicPerformanceSimple_Impl>()->setFixedEfficiency(fixedEfficiency);
  }

  void PhotovoltaicPerformanceSimple::resetFixedEfficiency() {
    getImpl<detail::PhotovoltaicPerformanceSimple_Impl>()->resetFixedEfficiency();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double PhotovoltaicPerformanceSimple_Impl::fractionOfSurfaceAreaWithActiveSolarCells() const {
      const auto value = getDouble(openstudio::PhotovoltaicPerformance_SimpleFields::FractionofSurfaceAreawithActiveSolarCells, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSimple_Impl::isfractionOfSurfaceAreaWithActiveSolarCellsDefaulted() const {
      return isEmpty(openstudio::PhotovoltaicPerformance_SimpleFields::FractionofSurfaceAreawithActiveSolarCells);
    }

    bool PhotovoltaicPerformanceSimple_Impl::setFractionOfSurfaceAreaWithActiveSolarCells(double fractionOfSurfaceAreaWithActiveSolarCells) {
      return setDouble(openstudio::PhotovoltaicPerformance_SimpleFields::FractionofSurfaceAreawithActiveSolarCells,
                       fractionOfSurfaceAreaWithActiveSolarCells);
    }

    void PhotovoltaicPerformanceSimple_Impl::resetFractionOfSurfaceAreaWithActiveSolarCells() {
      const bool result = setString(openstudio::PhotovoltaicPerformance_SimpleFields::FractionofSurfaceAreawithActiveSolarCells, "");
      OS_ASSERT(result);
    }

    std::string PhotovoltaicPerformanceSimple_Impl::conversionEfficiencyInputMode() const {
      const auto value = getString(openstudio::PhotovoltaicPerformance_SimpleFields::ConversionEfficiencyInputMode, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSimple_Impl::setConversionEfficiencyInputMode(const std::string& conversionEfficiencyInputMode) {
      return setString(openstudio::PhotovoltaicPerformance_SimpleFields::ConversionEfficiencyInputMode, conversionEfficiencyInputMode);
    }

    std::vector<std::string> PhotovoltaicPerformanceSimple_Impl::conversionEfficiencyInputModeValues() const {
      return openstudio::epmodel::PhotovoltaicPerformanceSimple::conversionEfficiencyInputModeValues();
    }

    boost::optional<double> PhotovoltaicPerformanceSimple_Impl::fixedEfficiency() const {
      return getDouble(openstudio::PhotovoltaicPerformance_SimpleFields::ValueforCellEfficiencyifFixed, true);
    }

    bool PhotovoltaicPerformanceSimple_Impl::setFixedEfficiency(double fixedEfficiency) {
      bool result = setDouble(openstudio::PhotovoltaicPerformance_SimpleFields::ValueforCellEfficiencyifFixed, fixedEfficiency);
      if (result) {
        result = setConversionEfficiencyInputMode("Fixed");
        OS_ASSERT(result);
      }
      return result;
    }

    void PhotovoltaicPerformanceSimple_Impl::resetFixedEfficiency() {
      const bool result = setDefaultFixedEfficiency();
      OS_ASSERT(result);
    }

    bool PhotovoltaicPerformanceSimple_Impl::setDefaultFixedEfficiency() {
      bool result = setFixedEfficiency(0.12);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
