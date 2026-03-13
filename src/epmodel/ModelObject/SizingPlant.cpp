/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SizingPlant.hpp"
#include "SizingPlant_Impl.hpp"

#include "Loop/PlantLoop.hpp"
#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/Sizing_Plant_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SizingPlant::SizingPlant(const Model& model, const PlantLoop& plantLoop) : ModelObject(SizingPlant::iddObjectType(), model) {
    auto impl = getImpl<detail::SizingPlant_Impl>();
    OS_ASSERT(impl);

    OS_ASSERT(impl->setPlantLoop(plantLoop));

    OS_ASSERT(setLoopType("Heating"));
    OS_ASSERT(setDesignLoopExitTemperature(82.0));
    OS_ASSERT(setLoopDesignTemperatureDifference(11.0));
    OS_ASSERT(setSizingOption("NonCoincident"));
    OS_ASSERT(setZoneTimestepsinAveragingWindow(1));
    OS_ASSERT(setCoincidentSizingFactorMode("None"));
  }

  SizingPlant::SizingPlant(std::shared_ptr<detail::SizingPlant_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType SizingPlant::iddObjectType() {
    return IddObjectType::Sizing_Plant;
  }

  std::vector<std::string> SizingPlant::loopTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Sizing_PlantFields::LoopType);
  }

  std::vector<std::string> SizingPlant::sizingOptionValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Sizing_PlantFields::SizingOption);
  }

  std::vector<std::string> SizingPlant::coincidentSizingFactorModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Sizing_PlantFields::CoincidentSizingFactorMode);
  }

  std::string SizingPlant::loopType() const {
    return getImpl<detail::SizingPlant_Impl>()->loopType();
  }

  bool SizingPlant::setLoopType(const std::string& loopType) {
    return getImpl<detail::SizingPlant_Impl>()->setLoopType(loopType);
  }

  double SizingPlant::designLoopExitTemperature() const {
    return getImpl<detail::SizingPlant_Impl>()->designLoopExitTemperature();
  }

  bool SizingPlant::setDesignLoopExitTemperature(double designLoopExitTemperature) {
    return getImpl<detail::SizingPlant_Impl>()->setDesignLoopExitTemperature(designLoopExitTemperature);
  }

  double SizingPlant::loopDesignTemperatureDifference() const {
    return getImpl<detail::SizingPlant_Impl>()->loopDesignTemperatureDifference();
  }

  bool SizingPlant::setLoopDesignTemperatureDifference(double loopDesignTemperatureDifference) {
    return getImpl<detail::SizingPlant_Impl>()->setLoopDesignTemperatureDifference(loopDesignTemperatureDifference);
  }

  std::string SizingPlant::sizingOption() const {
    return getImpl<detail::SizingPlant_Impl>()->sizingOption();
  }

  bool SizingPlant::setSizingOption(const std::string& sizingOption) {
    return getImpl<detail::SizingPlant_Impl>()->setSizingOption(sizingOption);
  }

  int SizingPlant::zoneTimestepsinAveragingWindow() const {
    return getImpl<detail::SizingPlant_Impl>()->zoneTimestepsinAveragingWindow();
  }

  bool SizingPlant::setZoneTimestepsinAveragingWindow(int zoneTimestepsinAveragingWindow) {
    return getImpl<detail::SizingPlant_Impl>()->setZoneTimestepsinAveragingWindow(zoneTimestepsinAveragingWindow);
  }

  std::string SizingPlant::coincidentSizingFactorMode() const {
    return getImpl<detail::SizingPlant_Impl>()->coincidentSizingFactorMode();
  }

  bool SizingPlant::setCoincidentSizingFactorMode(const std::string& coincidentSizingFactorMode) {
    return getImpl<detail::SizingPlant_Impl>()->setCoincidentSizingFactorMode(coincidentSizingFactorMode);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string SizingPlant_Impl::loopType() const {
      const auto value = getString(openstudio::Sizing_PlantFields::LoopType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SizingPlant_Impl::setLoopType(const std::string& loopType) {
      return setString(openstudio::Sizing_PlantFields::LoopType, loopType);
    }

    double SizingPlant_Impl::designLoopExitTemperature() const {
      const auto value = getDouble(openstudio::Sizing_PlantFields::DesignLoopExitTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SizingPlant_Impl::setDesignLoopExitTemperature(double designLoopExitTemperature) {
      const bool result = setDouble(openstudio::Sizing_PlantFields::DesignLoopExitTemperature, designLoopExitTemperature);
      OS_ASSERT(result);
      return result;
    }

    double SizingPlant_Impl::loopDesignTemperatureDifference() const {
      const auto value = getDouble(openstudio::Sizing_PlantFields::LoopDesignTemperatureDifference, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SizingPlant_Impl::setLoopDesignTemperatureDifference(double loopDesignTemperatureDifference) {
      return setDouble(openstudio::Sizing_PlantFields::LoopDesignTemperatureDifference, loopDesignTemperatureDifference);
    }

    std::string SizingPlant_Impl::sizingOption() const {
      const auto value = getString(openstudio::Sizing_PlantFields::SizingOption, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SizingPlant_Impl::setSizingOption(const std::string& sizingOption) {
      return setString(openstudio::Sizing_PlantFields::SizingOption, sizingOption);
    }

    int SizingPlant_Impl::zoneTimestepsinAveragingWindow() const {
      const auto value = getInt(openstudio::Sizing_PlantFields::ZoneTimestepsinAveragingWindow, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SizingPlant_Impl::setZoneTimestepsinAveragingWindow(int zoneTimestepsinAveragingWindow) {
      return setInt(openstudio::Sizing_PlantFields::ZoneTimestepsinAveragingWindow, zoneTimestepsinAveragingWindow);
    }

    std::string SizingPlant_Impl::coincidentSizingFactorMode() const {
      const auto value = getString(openstudio::Sizing_PlantFields::CoincidentSizingFactorMode, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SizingPlant_Impl::setCoincidentSizingFactorMode(const std::string& coincidentSizingFactorMode) {
      return setString(openstudio::Sizing_PlantFields::CoincidentSizingFactorMode, coincidentSizingFactorMode);
    }

    bool SizingPlant_Impl::setPlantLoop(const openstudio::epmodel::PlantLoop& plantLoop) {
      return setPointer(openstudio::Sizing_PlantFields::PlantorCondenserLoopName, plantLoop.handle(), false);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
