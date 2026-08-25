/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SizingPlant.hpp"
#include "SizingPlant_Impl.hpp"

#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"
#include "Model.hpp"
#include "TestFailurePoint.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/Sizing_Plant_FieldEnums.hxx>
#include <utilities/idf/IdfObject_Impl.hpp>

namespace openstudio {
namespace epmodel {

  SizingPlant::SizingPlant(const Model& model, const PlantLoop& plantLoop) : ModelObject(SizingPlant::iddObjectType(), model) {
    auto impl = getImpl<detail::SizingPlant_Impl>();
    OS_ASSERT(impl);

    OS_ASSERT(impl->setPlantLoopPointer(plantLoop));

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

  PlantLoop SizingPlant::plantLoop() const {
    return getImpl<detail::SizingPlant_Impl>()->plantLoop();
  }

  bool SizingPlant::setPlantLoop(const PlantLoop& plantLoop) {
    return getImpl<detail::SizingPlant_Impl>()->setPlantLoop(plantLoop);
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

    namespace {

      struct SizingPlantCompanionPreflight
      {
        bool valid = true;
        std::vector<SizingPlant> sourceCompanions;
        std::vector<SizingPlant> targetCompanions;
      };

      boost::optional<std::string> rawPlantLoopReference(const SizingPlant& sizingPlant) {
        const auto workspaceImpl = sizingPlant.getImpl<openstudio::detail::WorkspaceObject_Impl>();
        if (!workspaceImpl) {
          return boost::none;
        }
        return workspaceImpl->openstudio::detail::IdfObject_Impl::getString(openstudio::Sizing_PlantFields::PlantorCondenserLoopName, false, true);
      }

      bool loopNamesAreUnique(const Model& model, const PlantLoop& plantLoop) {
        const auto plantLoopName = plantLoop.name();
        if (!plantLoopName || plantLoopName->empty()) {
          return false;
        }

        unsigned matches = 0u;
        for (const auto& candidate : model.getConcreteModelObjects<PlantLoop>()) {
          const auto candidateName = candidate.name();
          if (candidateName && openstudio::istringEqual(*candidateName, *plantLoopName)) {
            ++matches;
          }
        }
        return matches == 1u;
      }

      bool rawReferenceMatchesLoop(const boost::optional<std::string>& rawReference, const PlantLoop& plantLoop) {
        if (!rawReference || rawReference->empty()) {
          return false;
        }
        return (*rawReference == openstudio::toString(plantLoop.handle())) || openstudio::istringEqual(*rawReference, plantLoop.nameString());
      }

      SizingPlantCompanionPreflight sizingPlantCompanionPreflight(const Model& model, const PlantLoop& sourcePlantLoop,
                                                                  const PlantLoop& targetPlantLoop) {
        SizingPlantCompanionPreflight result;
        if (!loopNamesAreUnique(model, sourcePlantLoop) || !loopNamesAreUnique(model, targetPlantLoop)) {
          result.valid = false;
          return result;
        }

        for (const auto& candidate : model.getConcreteModelObjects<SizingPlant>()) {
          const auto managedPlantLoop = candidate.getModelObjectTarget<PlantLoop>(openstudio::Sizing_PlantFields::PlantorCondenserLoopName);
          const bool managedSource = managedPlantLoop && (*managedPlantLoop == sourcePlantLoop);
          const bool managedTarget = managedPlantLoop && (*managedPlantLoop == targetPlantLoop);
          const auto rawReference = rawPlantLoopReference(candidate);
          const bool rawSource = rawReferenceMatchesLoop(rawReference, sourcePlantLoop);
          const bool rawTarget = rawReferenceMatchesLoop(rawReference, targetPlantLoop);
          if (!managedSource && !managedTarget && !rawSource && !rawTarget) {
            continue;
          }

          // A managed pointer is the only accepted representation for either
          // endpoint. A nonempty raw field would make a later handle rollback
          // normalize caller-provided spelling instead of restoring it exactly.
          if ((managedSource || managedTarget) && rawReference) {
            result.valid = false;
            return result;
          }
          if (rawSource || rawTarget) {
            result.valid = false;
            return result;
          }

          if (managedSource) {
            result.sourceCompanions.push_back(candidate);
          }
          if (managedTarget) {
            result.targetCompanions.push_back(candidate);
          }
        }
        return result;
      }

    }  // namespace

    PlantLoop SizingPlant_Impl::plantLoop() const {
      const auto result = optionalPlantLoop();
      OS_ASSERT(result);
      return *result;
    }

    boost::optional<PlantLoop> SizingPlant_Impl::optionalPlantLoop() const {
      return getObject<SizingPlant>().getModelObjectTarget<PlantLoop>(openstudio::Sizing_PlantFields::PlantorCondenserLoopName);
    }

    void SizingPlant_Impl::doCanonicalize(LoadContext& context) {
      ModelObject_Impl::doCanonicalize(context);

      auto sizingPlant = getObject<SizingPlant>();
      const auto sizingPlantName = sizingPlant.nameString().empty() ? std::string{"unnamed"} : sizingPlant.nameString();
      const auto plantLoop = optionalPlantLoop();
      if (!plantLoop) {
        // EnergyPlus 26.1 still supports the legacy CondenserLoop object, whose
        // name participates in the same PlantLoops reference list. EPModel has
        // only a scalar scaffold for that family, so the typed PlantLoop API
        // cannot represent its back-reference yet. Preserve the valid imported
        // Sizing:Plant relationship instead of misclassifying it as an orphan.
        const auto genericLoop = sizingPlant.getModelObjectTarget<ModelObject>(openstudio::Sizing_PlantFields::PlantorCondenserLoopName);
        if (genericLoop && (genericLoop->iddObject().type() == IddObjectType::CondenserLoop)) {
          return;
        }
        detail::addLoadWarning(context, "Removed orphan Sizing:Plant '" + sizingPlantName
                                          + "' because Plant or Condenser Loop Name does not resolve to a PlantLoop.");
        sizingPlant.remove();
        return;
      }

      for (const auto& candidate : model().getConcreteModelObjects<SizingPlant>()) {
        const auto candidateLoop = candidate.getImpl<SizingPlant_Impl>()->optionalPlantLoop();
        if (!candidateLoop || (*candidateLoop != *plantLoop)) {
          continue;
        }

        if (candidate.handle() != sizingPlant.handle()) {
          detail::addLoadWarning(context, "Removed duplicate Sizing:Plant '" + sizingPlantName + "' for PlantLoop '" + plantLoop->nameString()
                                            + "'. Kept '" + candidate.nameString() + "'.");
          sizingPlant.remove();
        }
        return;
      }

      OS_ASSERT(false);
    }

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
      const auto sizingPlant = getObject<SizingPlant>();
      const auto sourcePlantLoop = optionalPlantLoop();
      if (!sourcePlantLoop || (plantLoop.model() != model())) {
        return false;
      }

      const auto companionPreflight = sizingPlantCompanionPreflight(model(), *sourcePlantLoop, plantLoop);
      if (!companionPreflight.valid || (companionPreflight.sourceCompanions.size() != 1u)
          || (companionPreflight.sourceCompanions.front().handle() != sizingPlant.handle())) {
        return false;
      }

      if (*sourcePlantLoop == plantLoop) {
        return true;
      }

      if (companionPreflight.targetCompanions.size() != 1u) {
        return false;
      }
      auto targetImpl = companionPreflight.targetCompanions.front().getImpl<SizingPlant_Impl>();
      if (!targetImpl) {
        return false;
      }

      if (!targetImpl->setPlantLoopPointer(*sourcePlantLoop)) {
        return false;
      }
      if (testFailurePointReached(model(), TestFailurePoint::SizingPlantAfterFirstCompanionPointerWritten)) {
        OS_ASSERT(targetImpl->setPlantLoopPointer(plantLoop));
        return false;
      }
      if (setPlantLoopPointer(plantLoop)) {
        return true;
      }

      OS_ASSERT(targetImpl->setPlantLoopPointer(plantLoop));
      return false;
    }

    bool SizingPlant_Impl::setPlantLoopPointer(const openstudio::epmodel::PlantLoop& plantLoop) {
      return setPointer(openstudio::Sizing_PlantFields::PlantorCondenserLoopName, plantLoop.handle(), false);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
