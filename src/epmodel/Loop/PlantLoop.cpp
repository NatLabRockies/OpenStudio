/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_PlantLoop_FieldEnums.hxx>
#include <utilities/idd/PlantLoop_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  PlantLoop::PlantLoop(const Model& model) : Loop(PlantLoop::iddObjectType(), model) {}

  PlantLoop::PlantLoop(std::shared_ptr<detail::PlantLoop_Impl> impl) : Loop(std::move(impl)) {}

  IddObjectType PlantLoop::iddObjectType() {
    return IddObjectType::PlantLoop;
  }

  std::string PlantLoop::loadDistributionScheme() const {
    return getImpl<detail::PlantLoop_Impl>()->loadDistributionScheme();
  }

  bool PlantLoop::setLoadDistributionScheme(const std::string& scheme) {
    return getImpl<detail::PlantLoop_Impl>()->setLoadDistributionScheme(scheme);
  }

  std::string PlantLoop::fluidType() const {
    return getImpl<detail::PlantLoop_Impl>()->fluidType();
  }

  bool PlantLoop::setFluidType(const std::string& value) {
    return getImpl<detail::PlantLoop_Impl>()->setFluidType(value);
  }

  int PlantLoop::glycolConcentration() const {
    return getImpl<detail::PlantLoop_Impl>()->glycolConcentration();
  }

  bool PlantLoop::setGlycolConcentration(int glycolConcentration) {
    return getImpl<detail::PlantLoop_Impl>()->setGlycolConcentration(glycolConcentration);
  }

  double PlantLoop::maximumLoopTemperature() const {
    return getImpl<detail::PlantLoop_Impl>()->maximumLoopTemperature();
  }

  bool PlantLoop::setMaximumLoopTemperature(double value) {
    return getImpl<detail::PlantLoop_Impl>()->setMaximumLoopTemperature(value);
  }

  double PlantLoop::minimumLoopTemperature() const {
    return getImpl<detail::PlantLoop_Impl>()->minimumLoopTemperature();
  }

  bool PlantLoop::setMinimumLoopTemperature(double value) {
    return getImpl<detail::PlantLoop_Impl>()->setMinimumLoopTemperature(value);
  }

  boost::optional<double> PlantLoop::maximumLoopFlowRate() const {
    return getImpl<detail::PlantLoop_Impl>()->maximumLoopFlowRate();
  }

  bool PlantLoop::setMaximumLoopFlowRate(double value) {
    return getImpl<detail::PlantLoop_Impl>()->setMaximumLoopFlowRate(value);
  }

  bool PlantLoop::isMaximumLoopFlowRateAutosized() const {
    return getImpl<detail::PlantLoop_Impl>()->isMaximumLoopFlowRateAutosized();
  }

  void PlantLoop::autosizeMaximumLoopFlowRate() {
    getImpl<detail::PlantLoop_Impl>()->autosizeMaximumLoopFlowRate();
  }

  boost::optional<double> PlantLoop::minimumLoopFlowRate() const {
    return getImpl<detail::PlantLoop_Impl>()->minimumLoopFlowRate();
  }

  bool PlantLoop::setMinimumLoopFlowRate(double value) {
    return getImpl<detail::PlantLoop_Impl>()->setMinimumLoopFlowRate(value);
  }

  bool PlantLoop::isMinimumLoopFlowRateAutosized() const {
    return getImpl<detail::PlantLoop_Impl>()->isMinimumLoopFlowRateAutosized();
  }

  void PlantLoop::autosizeMinimumLoopFlowRate() {
    getImpl<detail::PlantLoop_Impl>()->autosizeMinimumLoopFlowRate();
  }

  boost::optional<double> PlantLoop::plantLoopVolume() const {
    return getImpl<detail::PlantLoop_Impl>()->plantLoopVolume();
  }

  bool PlantLoop::setPlantLoopVolume(double value) {
    return getImpl<detail::PlantLoop_Impl>()->setPlantLoopVolume(value);
  }

  bool PlantLoop::isPlantLoopVolumeAutocalculated() const {
    return getImpl<detail::PlantLoop_Impl>()->isPlantLoopVolumeAutocalculated();
  }

  void PlantLoop::autocalculatePlantLoopVolume() {
    getImpl<detail::PlantLoop_Impl>()->autocalculatePlantLoopVolume();
  }

  std::string PlantLoop::commonPipeSimulation() const {
    return getImpl<detail::PlantLoop_Impl>()->commonPipeSimulation();
  }

  bool PlantLoop::isCommonPipeSimulationDefaulted() const {
    return getImpl<detail::PlantLoop_Impl>()->isCommonPipeSimulationDefaulted();
  }

  bool PlantLoop::setCommonPipeSimulation(const std::string& value) {
    return getImpl<detail::PlantLoop_Impl>()->setCommonPipeSimulation(value);
  }

  void PlantLoop::resetCommonPipeSimulation() {
    getImpl<detail::PlantLoop_Impl>()->resetCommonPipeSimulation();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string PlantLoop_Impl::loadDistributionScheme() const {
      const auto value = getString(openstudio::PlantLoopFields::LoadDistributionScheme, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool PlantLoop_Impl::setLoadDistributionScheme(const std::string& scheme) {
      auto normalized = scheme;
      if (openstudio::istringEqual(normalized, "Sequential")) {
        normalized = "SequentialLoad";
      } else if (openstudio::istringEqual(normalized, "Uniform")) {
        normalized = "UniformLoad";
      }
      return setString(openstudio::PlantLoopFields::LoadDistributionScheme, normalized);
    }

    std::string PlantLoop_Impl::fluidType() const {
      const auto value = getString(openstudio::PlantLoopFields::FluidType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool PlantLoop_Impl::setFluidType(const std::string& value) {
      return setString(openstudio::PlantLoopFields::FluidType, value);
    }

    int PlantLoop_Impl::glycolConcentration() const {
      return getInt(openstudio::OS_PlantLoopFields::GlycolConcentration, true).get();
    }

    bool PlantLoop_Impl::setGlycolConcentration(int glycolConcentration) {
      return setInt(openstudio::OS_PlantLoopFields::GlycolConcentration, glycolConcentration);
    }

    double PlantLoop_Impl::maximumLoopTemperature() const {
      const auto value = getDouble(openstudio::PlantLoopFields::MaximumLoopTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool PlantLoop_Impl::setMaximumLoopTemperature(double value) {
      return setDouble(openstudio::PlantLoopFields::MaximumLoopTemperature, value);
    }

    double PlantLoop_Impl::minimumLoopTemperature() const {
      const auto value = getDouble(openstudio::PlantLoopFields::MinimumLoopTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool PlantLoop_Impl::setMinimumLoopTemperature(double value) {
      return setDouble(openstudio::PlantLoopFields::MinimumLoopTemperature, value);
    }

    boost::optional<double> PlantLoop_Impl::maximumLoopFlowRate() const {
      return getDouble(openstudio::PlantLoopFields::MaximumLoopFlowRate, true);
    }

    bool PlantLoop_Impl::setMaximumLoopFlowRate(double value) {
      return setDouble(openstudio::PlantLoopFields::MaximumLoopFlowRate, value);
    }

    bool PlantLoop_Impl::isMaximumLoopFlowRateAutosized() const {
      if (const auto value = getString(openstudio::PlantLoopFields::MaximumLoopFlowRate, true)) {
        return openstudio::istringEqual(value.get(), "Autosize");
      }
      return false;
    }

    void PlantLoop_Impl::autosizeMaximumLoopFlowRate() {
      OS_ASSERT(setString(openstudio::PlantLoopFields::MaximumLoopFlowRate, "Autosize"));
    }

    boost::optional<double> PlantLoop_Impl::minimumLoopFlowRate() const {
      return getDouble(openstudio::PlantLoopFields::MinimumLoopFlowRate, true);
    }

    bool PlantLoop_Impl::setMinimumLoopFlowRate(double value) {
      return setDouble(openstudio::PlantLoopFields::MinimumLoopFlowRate, value);
    }

    bool PlantLoop_Impl::isMinimumLoopFlowRateAutosized() const {
      if (const auto value = getString(openstudio::PlantLoopFields::MinimumLoopFlowRate, true)) {
        return openstudio::istringEqual(value.get(), "Autosize");
      }
      return false;
    }

    void PlantLoop_Impl::autosizeMinimumLoopFlowRate() {
      OS_ASSERT(setString(openstudio::PlantLoopFields::MinimumLoopFlowRate, "Autosize"));
    }

    boost::optional<double> PlantLoop_Impl::plantLoopVolume() const {
      return getDouble(openstudio::PlantLoopFields::PlantLoopVolume, true);
    }

    bool PlantLoop_Impl::setPlantLoopVolume(double value) {
      return setDouble(openstudio::PlantLoopFields::PlantLoopVolume, value);
    }

    bool PlantLoop_Impl::isPlantLoopVolumeAutocalculated() const {
      if (const auto value = getString(openstudio::PlantLoopFields::PlantLoopVolume, true)) {
        return openstudio::istringEqual(value.get(), "Autocalculate");
      }
      return false;
    }

    void PlantLoop_Impl::autocalculatePlantLoopVolume() {
      OS_ASSERT(setString(openstudio::PlantLoopFields::PlantLoopVolume, "Autocalculate"));
    }

    std::string PlantLoop_Impl::commonPipeSimulation() const {
      const auto value = getString(openstudio::PlantLoopFields::CommonPipeSimulation, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool PlantLoop_Impl::isCommonPipeSimulationDefaulted() const {
      return isEmpty(openstudio::PlantLoopFields::CommonPipeSimulation);
    }

    bool PlantLoop_Impl::setCommonPipeSimulation(const std::string& value) {
      return setString(openstudio::PlantLoopFields::CommonPipeSimulation, value);
    }

    void PlantLoop_Impl::resetCommonPipeSimulation() {
      OS_ASSERT(setString(openstudio::PlantLoopFields::CommonPipeSimulation, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
