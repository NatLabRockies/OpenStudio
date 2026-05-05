/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/GroundHeatExchangerVertical.hpp"
#include "StraightComponent/GroundHeatExchangerVertical_Impl.hpp"

#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"
#include "Model.hpp"
#include "ModelObject/Branch.hpp"
#include "ModelObject/Branch_Impl.hpp"
#include "ModelObject/ModelObject.hpp"
#include "ModelObject/SiteGroundTemperatureUndisturbedFiniteDifference.hpp"
#include "ModelObject/SiteGroundTemperatureUndisturbedFiniteDifference_Impl.hpp"
#include "ModelObject/SiteGroundTemperatureUndisturbedKusudaAchenbach.hpp"
#include "ModelObject/SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl.hpp"
#include "ModelObject/SiteGroundTemperatureUndisturbedXing.hpp"
#include "ModelObject/SiteGroundTemperatureUndisturbedXing_Impl.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Compare.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>
#include <utilities/idd/GroundHeatExchanger_ResponseFactors_FieldEnums.hxx>
#include <utilities/idd/GroundHeatExchanger_System_FieldEnums.hxx>
#include <utilities/idd/GroundHeatExchanger_Vertical_Properties_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

#include <array>

namespace openstudio {
namespace epmodel {

  static constexpr std::array<std::pair<double, double>, 35> defaultGroundHeatExchangerVerticalGFunctions{{
    {-15.2996, -0.348322}, {-14.201, 0.022208}, {-13.2202, 0.412345}, {-12.2086, 0.867498}, {-11.1888, 1.357839}, {-10.1816, 1.852024},
    {-9.1815, 2.345656},   {-8.6809, 2.593958}, {-8.5, 2.679},        {-7.8, 3.023},        {-7.2, 3.32},         {-6.5, 3.681},
    {-5.9, 4.071},         {-5.2, 4.828},       {-4.5, 6.253},        {-3.963, 7.894},      {-3.27, 11.82},       {-2.864, 15.117},
    {-2.577, 18.006},      {-2.171, 22.887},    {-1.884, 26.924},     {-1.191, 38.004},     {-0.497, 49.919},     {-0.274, 53.407},
    {-0.051, 56.632},      {0.196, 59.825},     {0.419, 62.349},      {0.642, 64.524},      {0.873, 66.412},      {1.112, 67.993},
    {1.335, 69.162},       {1.679, 70.476},     {2.028, 71.361},      {2.275, 71.79},       {3.003, 72.511},
  }};

  GFunction::GFunction(double lnValue, double gValue) : m_lnValue(lnValue), m_gValue(gValue) {}

  double GFunction::lnValue() const {
    return m_lnValue;
  }

  double GFunction::gValue() const {
    return m_gValue;
  }

  GroundHeatExchangerVertical::GroundHeatExchangerVertical(const Model& model)
    : GroundHeatExchangerVertical(model, SiteGroundTemperatureUndisturbedKusudaAchenbach(model)) {
    auto kusuda = undisturbedGroundTemperatureModel().cast<SiteGroundTemperatureUndisturbedKusudaAchenbach>();
    kusuda.setSoilThermalConductivity(groundThermalConductivity().get());
    kusuda.setSoilDensity(920.0);
    kusuda.setSoilSpecificHeat(groundThermalHeatCapacity().get() / 920.0);
    kusuda.setAverageSoilSurfaceTemperature(13.375);
    kusuda.setAverageAmplitudeofSurfaceTemperature(3.2);
    kusuda.setPhaseShiftofMinimumSurfaceTemperature(8.0);
  }

  GroundHeatExchangerVertical::GroundHeatExchangerVertical(const Model& model, const ModelObject& undisturbedGroundTemperatureModel)
    : StraightComponent(GroundHeatExchangerVertical::iddObjectType(), model) {
    bool ok = setUndisturbedGroundTemperatureModel(undisturbedGroundTemperatureModel);
    if (!ok) {
      remove();
      LOG_FREE_AND_THROW("openstudio.epmodel.GroundHeatExchangerVertical", "Unable to set "
                                                                             << briefDescription() << "'s Undisturbed Ground Temperature Model to "
                                                                             << undisturbedGroundTemperatureModel.briefDescription() << ".");
    }

    ok = setDesignFlowRate(0.0033);
    OS_ASSERT(ok);
    ok = setGroundThermalConductivity(0.692626);
    OS_ASSERT(ok);
    ok = setGroundThermalHeatCapacity(0.234700E+07);
    OS_ASSERT(ok);
    ok = setBoreHoleTopDepth(1.0);
    OS_ASSERT(ok);
    ok = setBoreHoleLength(76.2);
    OS_ASSERT(ok);
    ok = setBoreHoleRadius(0.635080E-01);
    OS_ASSERT(ok);
    ok = setGroutThermalConductivity(0.692626);
    OS_ASSERT(ok);
    ok = setPipeThermalConductivity(0.391312);
    OS_ASSERT(ok);
    ok = setPipeOutDiameter(2.66667E-02);
    OS_ASSERT(ok);
    ok = setUTubeDistance(2.53977E-02);
    OS_ASSERT(ok);
    ok = setPipeThickness(2.41285E-03);
    OS_ASSERT(ok);
    ok = setNumberofBoreHoles(120);
    OS_ASSERT(ok);
    ok = setGFunctionReferenceRatio(0.0005);
    OS_ASSERT(ok);
    for (const auto& [lnValue, gValue] : defaultGroundHeatExchangerVerticalGFunctions) {
      ok = addGFunction(lnValue, gValue);
      OS_ASSERT(ok);
    }
  }

  GroundHeatExchangerVertical::GroundHeatExchangerVertical(std::shared_ptr<detail::GroundHeatExchangerVertical_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType GroundHeatExchangerVertical::iddObjectType() {
    return IddObjectType::GroundHeatExchanger_ResponseFactors;
  }

  bool GroundHeatExchangerVertical::addGFunction(double gFunctionLN, double gFunctionGValue) {
    return getImpl<detail::GroundHeatExchangerVertical_Impl>()->addGFunction(gFunctionLN, gFunctionGValue);
  }

  bool GroundHeatExchangerVertical::addGFunction(GFunction gFunc) {
    return addGFunction(gFunc.lnValue(), gFunc.gValue());
  }

  void GroundHeatExchangerVertical::removeGFunction(int groupIndex) {
    getImpl<detail::GroundHeatExchangerVertical_Impl>()->removeGFunction(static_cast<unsigned>(groupIndex));
  }

  void GroundHeatExchangerVertical::removeAllGFunctions() {
    getImpl<detail::GroundHeatExchangerVertical_Impl>()->removeAllGFunctions();
  }

  std::vector<GFunction> GroundHeatExchangerVertical::gFunctions() {
    std::vector<GFunction> result;
    for (const auto& [lnValue, gValue] : getImpl<detail::GroundHeatExchangerVertical_Impl>()->gFunctions()) {
      result.emplace_back(lnValue, gValue);
    }
    return result;
  }

  boost::optional<int> GroundHeatExchangerVertical::numberofBoreHoles() const {
    return getImpl<detail::GroundHeatExchangerVertical_Impl>()->numberofBoreHoles();
  }

  boost::optional<double> GroundHeatExchangerVertical::designFlowRate() const {
    return getImpl<detail::GroundHeatExchangerVertical_Impl>()->designFlowRate();
  }

  bool GroundHeatExchangerVertical::setDesignFlowRate(double designFlowRate) {
    return getImpl<detail::GroundHeatExchangerVertical_Impl>()->setDesignFlowRate(designFlowRate);
  }

  boost::optional<double> GroundHeatExchangerVertical::groundThermalConductivity() const {
    return getImpl<detail::GroundHeatExchangerVertical_Impl>()->groundThermalConductivity();
  }

  bool GroundHeatExchangerVertical::setGroundThermalConductivity(double groundThermalConductivity) {
    return getImpl<detail::GroundHeatExchangerVertical_Impl>()->setGroundThermalConductivity(groundThermalConductivity);
  }

  void GroundHeatExchangerVertical::resetGroundThermalConductivity() {
    getImpl<detail::GroundHeatExchangerVertical_Impl>()->resetGroundThermalConductivity();
  }

  boost::optional<double> GroundHeatExchangerVertical::groundThermalHeatCapacity() const {
    return getImpl<detail::GroundHeatExchangerVertical_Impl>()->groundThermalHeatCapacity();
  }

  bool GroundHeatExchangerVertical::setGroundThermalHeatCapacity(double groundThermalHeatCapacity) {
    return getImpl<detail::GroundHeatExchangerVertical_Impl>()->setGroundThermalHeatCapacity(groundThermalHeatCapacity);
  }

  void GroundHeatExchangerVertical::resetGroundThermalHeatCapacity() {
    getImpl<detail::GroundHeatExchangerVertical_Impl>()->resetGroundThermalHeatCapacity();
  }

  double GroundHeatExchangerVertical::boreHoleTopDepth() const {
    return getImpl<detail::GroundHeatExchangerVertical_Impl>()->boreHoleTopDepth();
  }

  bool GroundHeatExchangerVertical::setBoreHoleTopDepth(double boreHoleTopDepth) {
    return getImpl<detail::GroundHeatExchangerVertical_Impl>()->setBoreHoleTopDepth(boreHoleTopDepth);
  }

  boost::optional<double> GroundHeatExchangerVertical::boreHoleLength() const {
    return getImpl<detail::GroundHeatExchangerVertical_Impl>()->boreHoleLength();
  }

  bool GroundHeatExchangerVertical::setBoreHoleLength(double boreHoleLength) {
    return getImpl<detail::GroundHeatExchangerVertical_Impl>()->setBoreHoleLength(boreHoleLength);
  }

  void GroundHeatExchangerVertical::resetBoreHoleLength() {
    getImpl<detail::GroundHeatExchangerVertical_Impl>()->resetBoreHoleLength();
  }

  boost::optional<double> GroundHeatExchangerVertical::boreHoleRadius() const {
    return getImpl<detail::GroundHeatExchangerVertical_Impl>()->boreHoleRadius();
  }

  bool GroundHeatExchangerVertical::setBoreHoleRadius(double boreHoleRadius) {
    return getImpl<detail::GroundHeatExchangerVertical_Impl>()->setBoreHoleRadius(boreHoleRadius);
  }

  void GroundHeatExchangerVertical::resetBoreHoleRadius() {
    getImpl<detail::GroundHeatExchangerVertical_Impl>()->resetBoreHoleRadius();
  }

  boost::optional<double> GroundHeatExchangerVertical::groutThermalConductivity() const {
    return getImpl<detail::GroundHeatExchangerVertical_Impl>()->groutThermalConductivity();
  }

  bool GroundHeatExchangerVertical::setGroutThermalConductivity(double groutThermalConductivity) {
    return getImpl<detail::GroundHeatExchangerVertical_Impl>()->setGroutThermalConductivity(groutThermalConductivity);
  }

  void GroundHeatExchangerVertical::resetGroutThermalConductivity() {
    getImpl<detail::GroundHeatExchangerVertical_Impl>()->resetGroutThermalConductivity();
  }

  boost::optional<double> GroundHeatExchangerVertical::pipeThermalConductivity() const {
    return getImpl<detail::GroundHeatExchangerVertical_Impl>()->pipeThermalConductivity();
  }

  bool GroundHeatExchangerVertical::setPipeThermalConductivity(double pipeThermalConductivity) {
    return getImpl<detail::GroundHeatExchangerVertical_Impl>()->setPipeThermalConductivity(pipeThermalConductivity);
  }

  void GroundHeatExchangerVertical::resetPipeThermalConductivity() {
    getImpl<detail::GroundHeatExchangerVertical_Impl>()->resetPipeThermalConductivity();
  }

  boost::optional<double> GroundHeatExchangerVertical::pipeOutDiameter() const {
    return getImpl<detail::GroundHeatExchangerVertical_Impl>()->pipeOutDiameter();
  }

  bool GroundHeatExchangerVertical::setPipeOutDiameter(double pipeOutDiameter) {
    return getImpl<detail::GroundHeatExchangerVertical_Impl>()->setPipeOutDiameter(pipeOutDiameter);
  }

  void GroundHeatExchangerVertical::resetPipeOutDiameter() {
    getImpl<detail::GroundHeatExchangerVertical_Impl>()->resetPipeOutDiameter();
  }

  boost::optional<double> GroundHeatExchangerVertical::uTubeDistance() const {
    return getImpl<detail::GroundHeatExchangerVertical_Impl>()->uTubeDistance();
  }

  bool GroundHeatExchangerVertical::setUTubeDistance(double uTubeDistance) {
    return getImpl<detail::GroundHeatExchangerVertical_Impl>()->setUTubeDistance(uTubeDistance);
  }

  void GroundHeatExchangerVertical::resetUTubeDistance() {
    getImpl<detail::GroundHeatExchangerVertical_Impl>()->resetUTubeDistance();
  }

  boost::optional<double> GroundHeatExchangerVertical::pipeThickness() const {
    return getImpl<detail::GroundHeatExchangerVertical_Impl>()->pipeThickness();
  }

  bool GroundHeatExchangerVertical::setPipeThickness(double pipeThickness) {
    return getImpl<detail::GroundHeatExchangerVertical_Impl>()->setPipeThickness(pipeThickness);
  }

  void GroundHeatExchangerVertical::resetPipeThickness() {
    getImpl<detail::GroundHeatExchangerVertical_Impl>()->resetPipeThickness();
  }

  bool GroundHeatExchangerVertical::setNumberofBoreHoles(int numberofBoreHoles) {
    return getImpl<detail::GroundHeatExchangerVertical_Impl>()->setNumberofBoreHoles(numberofBoreHoles);
  }

  void GroundHeatExchangerVertical::resetNumberofBoreHoles() {
    getImpl<detail::GroundHeatExchangerVertical_Impl>()->resetNumberofBoreHoles();
  }

  double GroundHeatExchangerVertical::gFunctionReferenceRatio() const {
    return getImpl<detail::GroundHeatExchangerVertical_Impl>()->gFunctionReferenceRatio();
  }

  bool GroundHeatExchangerVertical::isGFunctionReferenceRatioDefaulted() const {
    return getImpl<detail::GroundHeatExchangerVertical_Impl>()->isGFunctionReferenceRatioDefaulted();
  }

  bool GroundHeatExchangerVertical::setGFunctionReferenceRatio(double gFunctionReferenceRatio) {
    return getImpl<detail::GroundHeatExchangerVertical_Impl>()->setGFunctionReferenceRatio(gFunctionReferenceRatio);
  }

  void GroundHeatExchangerVertical::resetGFunctionReferenceRatio() {
    getImpl<detail::GroundHeatExchangerVertical_Impl>()->resetGFunctionReferenceRatio();
  }

  ModelObject GroundHeatExchangerVertical::undisturbedGroundTemperatureModel() const {
    return getImpl<detail::GroundHeatExchangerVertical_Impl>()->undisturbedGroundTemperatureModel();
  }

  bool GroundHeatExchangerVertical::setUndisturbedGroundTemperatureModel(const ModelObject& undisturbedGroundTemperatureModel) {
    return getImpl<detail::GroundHeatExchangerVertical_Impl>()->setUndisturbedGroundTemperatureModel(undisturbedGroundTemperatureModel);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned GroundHeatExchangerVertical_Impl::inletPort() const {
      return 0;
    }

    unsigned GroundHeatExchangerVertical_Impl::outletPort() const {
      return 0;
    }

    boost::optional<ModelObject> GroundHeatExchangerVertical_Impl::inletModelObject() const {
      if (auto systemObject = groundHeatExchangerSystem()) {
        if (auto target = systemObject->getTarget(openstudio::GroundHeatExchanger_SystemFields::InletNodeName)) {
          return target->optionalCast<ModelObject>();
        }
      }
      return boost::none;
    }

    boost::optional<ModelObject> GroundHeatExchangerVertical_Impl::outletModelObject() const {
      if (auto systemObject = groundHeatExchangerSystem()) {
        if (auto target = systemObject->getTarget(openstudio::GroundHeatExchanger_SystemFields::OutletNodeName)) {
          return target->optionalCast<ModelObject>();
        }
      }
      return boost::none;
    }

    boost::optional<openstudio::WorkspaceObject> GroundHeatExchangerVertical_Impl::groundHeatExchangerSystem() const {
      const auto responseFactors = getObject<ModelObject>();
      for (const auto& modelObject : model().getObjectsByType(openstudio::IddObjectType::GroundHeatExchanger_System)) {
        if (auto target = modelObject.getTarget(openstudio::GroundHeatExchanger_SystemFields::GHE_Vertical_ResponseFactorsObjectName)) {
          if (target->handle() == responseFactors.handle()) {
            return modelObject;
          }
        }
      }
      return boost::none;
    }

    boost::optional<openstudio::WorkspaceObject> GroundHeatExchangerVertical_Impl::getOrCreateGroundHeatExchangerSystem() {
      if (auto existing = groundHeatExchangerSystem()) {
        return existing;
      }

      auto responseFactors = getObject<ModelObject>();
      if (!responseFactors.name()) {
        responseFactors.createName();
        if (!responseFactors.name()) {
          return boost::none;
        }
      }

      auto systemObject = openstudio::epmodel::ModelObject::create(openstudio::IddObjectType::GroundHeatExchanger_System, model(), true);
      if (!systemObject.setName(responseFactors.nameString() + " System")) {
        return boost::none;
      }

      if (!systemObject.setPointer(openstudio::GroundHeatExchanger_SystemFields::GHE_Vertical_ResponseFactorsObjectName, responseFactors.handle())) {
        return boost::none;
      }

      return systemObject;
    }

    boost::optional<openstudio::WorkspaceObject> GroundHeatExchangerVertical_Impl::groundHeatExchangerVerticalProperties() const {
      if (auto target =
            getObject<ModelObject>().getTarget(openstudio::GroundHeatExchanger_ResponseFactorsFields::GHE_Vertical_PropertiesObjectName)) {
        return *target;
      }
      return boost::none;
    }

    boost::optional<openstudio::WorkspaceObject> GroundHeatExchangerVertical_Impl::getOrCreateGroundHeatExchangerVerticalProperties() {
      if (auto existing = groundHeatExchangerVerticalProperties()) {
        return existing;
      }

      auto responseFactors = getObject<ModelObject>();
      if (!responseFactors.name()) {
        responseFactors.createName();
        if (!responseFactors.name()) {
          return boost::none;
        }
      }

      auto propertiesObject =
        openstudio::epmodel::ModelObject::create(openstudio::IddObjectType::GroundHeatExchanger_Vertical_Properties, model(), true);
      if (!propertiesObject.setName(responseFactors.nameString() + " Properties")) {
        return boost::none;
      }

      if (!responseFactors.setPointer(openstudio::GroundHeatExchanger_ResponseFactorsFields::GHE_Vertical_PropertiesObjectName,
                                      propertiesObject.handle())) {
        return boost::none;
      }

      return propertiesObject;
    }

    bool GroundHeatExchangerVertical_Impl::addToNode(Node& node) {
      auto plantLoop = node.plantLoop();
      if (!plantLoop || plantLoop->demandComponent(node.handle())) {
        return false;
      }

      const auto nodeName = node.name();
      if (!nodeName) {
        return false;
      }

      auto thisObject = getObject<ModelObject>();
      if (!thisObject.name()) {
        thisObject.createName();
        if (!thisObject.name()) {
          return false;
        }
      }
      const auto thisName = thisObject.nameString();

      auto thisComponent = thisObject.cast<openstudio::epmodel::HVACComponent>();
      if (thisComponent.loop() && !removeFromLoop()) {
        LOG_FREE(Warn, "openstudio.epmodel.GroundHeatExchangerVertical",
                 "Failed to detach " << thisObject.briefDescription() << " from its existing loop topology before adding it to node '"
                                     << node.nameString() << "'.");
        return false;
      }

      auto systemObject = getOrCreateGroundHeatExchangerSystem();
      if (!systemObject) {
        return false;
      }

      auto plantLoopImpl = plantLoop->getImpl<openstudio::epmodel::detail::PlantLoop_Impl>();
      auto branch = plantLoopImpl->branchForNode(node);
      if (!branch) {
        return false;
      }

      auto branchImpl = branch->getImpl<openstudio::epmodel::detail::Branch_Impl>();
      OS_ASSERT(branchImpl);
      auto systemComponent = systemObject->optionalCast<ModelObject>();
      OS_ASSERT(systemComponent);
      auto components = branch->components();
      if (components.empty()) {
        std::string newInletName;
        std::string newOutletName;

        const bool isOutletAnchor = ((*branch == plantLoopImpl->supplyOutletBranch()) && (node == plantLoop->supplyOutletNode()))
                                    || ((*branch == plantLoopImpl->demandOutletBranch()) && (node == plantLoop->demandOutletNode()));
        if (isOutletAnchor) {
          newInletName = *nodeName + " - " + thisName + " Inlet";
          newOutletName = *nodeName;
        } else {
          newInletName = *nodeName;
          newOutletName = *nodeName + " - " + thisName + " Outlet";
        }

        if (!branchImpl->appendComponent(*systemComponent, newInletName, newOutletName)) {
          return false;
        }

        auto inletNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(newInletName);
        auto outletNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(newOutletName);
        if (!systemObject->setPointer(openstudio::GroundHeatExchanger_SystemFields::InletNodeName, inletNode.handle())
            || !systemObject->setPointer(openstudio::GroundHeatExchanger_SystemFields::OutletNodeName, outletNode.handle())) {
          return false;
        }
        return true;
      }

      for (std::size_t i = 0; i < components.size(); ++i) {
        auto inletNode = branch->componentInletNode(static_cast<unsigned>(i));
        auto outletNode = branch->componentOutletNode(static_cast<unsigned>(i));

        const bool matchesInlet = inletNode && openstudio::istringEqual(inletNode->nameString(), *nodeName);
        const bool matchesOutlet = outletNode && openstudio::istringEqual(outletNode->nameString(), *nodeName);
        if (!matchesInlet && !matchesOutlet) {
          continue;
        }

        if (auto comp = components[i].optionalCast<openstudio::epmodel::StraightComponent>()) {
          if (auto compInlet = comp->inletModelObject()) {
            if (auto compInletName = compInlet->name()) {
              if (inletNode && !openstudio::istringEqual(*compInletName, inletNode->nameString())) {
                LOG_FREE(Warn, "openstudio.epmodel.GroundHeatExchangerVertical",
                         "Branch inlet node '" << inletNode->nameString() << "' does not match component inlet node '" << *compInletName << "' for '"
                                               << comp->nameString() << "'.");
              }
            }
          }
          if (auto compOutlet = comp->outletModelObject()) {
            if (auto compOutletName = compOutlet->name()) {
              if (outletNode && !openstudio::istringEqual(*compOutletName, outletNode->nameString())) {
                LOG_FREE(Warn, "openstudio.epmodel.GroundHeatExchangerVertical",
                         "Branch outlet node '" << outletNode->nameString() << "' does not match component outlet node '" << *compOutletName
                                                << "' for '" << comp->nameString() << "'.");
              }
            }
          }
        }

        const std::string newNodeName = *nodeName + " - " + thisName + " Outlet";
        const unsigned insertIndex = matchesInlet ? static_cast<unsigned>(i) : static_cast<unsigned>(i + 1u);
        std::string newInletName;
        std::string newOutletName;
        if (matchesOutlet && (i + 1u == components.size())) {
          newInletName = newNodeName;
          newOutletName = *nodeName;
        } else {
          newInletName = *nodeName;
          newOutletName = newNodeName;
        }

        if (!branchImpl->insertComponent(insertIndex, *systemComponent, newInletName, newOutletName)) {
          return false;
        }

        auto newInletNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(newInletName);
        auto newOutletNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(newOutletName);
        if (!systemObject->setPointer(openstudio::GroundHeatExchanger_SystemFields::InletNodeName, newInletNode.handle())
            || !systemObject->setPointer(openstudio::GroundHeatExchanger_SystemFields::OutletNodeName, newOutletNode.handle())) {
          return false;
        }

        auto newNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(newNodeName);
        if (matchesInlet) {
          if (!branchImpl->setComponentInletNode(insertIndex + 1u, newNode)) {
            return false;
          }
          if (outletNode && !branchImpl->setComponentOutletNode(insertIndex + 1u, *outletNode)) {
            return false;
          }
          if (components[i].iddObject().type() == openstudio::IddObjectType::GroundHeatExchanger_System) {
            if (!components[i].setPointer(openstudio::GroundHeatExchanger_SystemFields::InletNodeName, newNode.handle())) {
              return false;
            }
            if (outletNode && !components[i].setPointer(openstudio::GroundHeatExchanger_SystemFields::OutletNodeName, outletNode->handle())) {
              return false;
            }
          }
        } else {
          if (!branchImpl->setComponentOutletNode(insertIndex - 1u, newNode)) {
            return false;
          }
          if (inletNode && !branchImpl->setComponentInletNode(insertIndex - 1u, *inletNode)) {
            return false;
          }
          if (components[i].iddObject().type() == openstudio::IddObjectType::GroundHeatExchanger_System) {
            if (!components[i].setPointer(openstudio::GroundHeatExchanger_SystemFields::OutletNodeName, newNode.handle())) {
              return false;
            }
            if (inletNode && !components[i].setPointer(openstudio::GroundHeatExchanger_SystemFields::InletNodeName, inletNode->handle())) {
              return false;
            }
          }
        }

        return true;
      }

      return false;
    }

    bool GroundHeatExchangerVertical_Impl::removeFromLoop() {
      auto systemObject = groundHeatExchangerSystem();
      if (!systemObject) {
        return false;
      }
      auto systemComponent = systemObject->optionalCast<ModelObject>();
      if (!systemComponent) {
        return false;
      }

      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      auto thisComponent = thisObject.optionalCast<openstudio::epmodel::StraightComponent>();
      if (!thisComponent) {
        return false;
      }

      if (auto owner = thisComponent->containingHVACComponent()) {
        LOG_FREE(Warn, "openstudio.epmodel.GroundHeatExchangerVertical",
                 "Refusing to remove " << thisObject.briefDescription() << " from its loop topology because that connectivity is owned by "
                                       << owner->briefDescription() << ".");
        return false;
      }

      const auto inletObject = inletModelObject();
      const auto outletObject = outletModelObject();
      if (!inletObject || !outletObject) {
        return false;
      }

      auto inletNode = inletObject->optionalCast<openstudio::epmodel::Node>();
      auto outletNode = outletObject->optionalCast<openstudio::epmodel::Node>();
      if (!inletNode || !outletNode) {
        return false;
      }

      auto plantLoop = thisComponent->plantLoop();
      if (!plantLoop) {
        return false;
      }

      auto plantLoopImpl = plantLoop->getImpl<openstudio::epmodel::detail::PlantLoop_Impl>();
      auto branch = plantLoopImpl->branchForNode(*inletNode);
      if (!branch) {
        branch = plantLoopImpl->branchForNode(*outletNode);
      }
      if (!branch) {
        return false;
      }

      auto components = branch->components();
      for (unsigned i = 0; i < components.size(); ++i) {
        if (components[i] != *systemComponent) {
          continue;
        }

        auto branchImpl = branch->getImpl<openstudio::epmodel::detail::Branch_Impl>();
        OS_ASSERT(branchImpl);
        if (i + 1u < components.size()) {
          if (!branchImpl->setComponentInletNode(i + 1u, *inletNode)) {
            return false;
          }
          if ((components[i + 1u].iddObject().type() == openstudio::IddObjectType::GroundHeatExchanger_System)
              && !components[i + 1u].setPointer(openstudio::GroundHeatExchanger_SystemFields::InletNodeName, inletNode->handle())) {
            return false;
          }
        } else if (i > 0u) {
          if (!branchImpl->setComponentOutletNode(i - 1u, *outletNode)) {
            return false;
          }
          if ((components[i - 1u].iddObject().type() == openstudio::IddObjectType::GroundHeatExchanger_System)
              && !components[i - 1u].setPointer(openstudio::GroundHeatExchanger_SystemFields::OutletNodeName, outletNode->handle())) {
            return false;
          }
        }
        if (!branchImpl->removeComponent(i)) {
          return false;
        }

        auto remainingComponents = branch->components();
        if (!remainingComponents.empty()) {
          if ((*branch == plantLoopImpl->supplyInletBranch()) && !branchImpl->setComponentInletNode(0u, plantLoop->supplyInletNode())) {
            return false;
          }
          if ((*branch == plantLoopImpl->supplyInletBranch())
              && (remainingComponents[0].iddObject().type() == openstudio::IddObjectType::GroundHeatExchanger_System)
              && !remainingComponents[0].setPointer(openstudio::GroundHeatExchanger_SystemFields::InletNodeName,
                                                    plantLoop->supplyInletNode().handle())) {
            return false;
          }
          if ((*branch == plantLoopImpl->demandInletBranch()) && !branchImpl->setComponentInletNode(0u, plantLoop->demandInletNode())) {
            return false;
          }
          if ((*branch == plantLoopImpl->demandInletBranch())
              && (remainingComponents[0].iddObject().type() == openstudio::IddObjectType::GroundHeatExchanger_System)
              && !remainingComponents[0].setPointer(openstudio::GroundHeatExchanger_SystemFields::InletNodeName,
                                                    plantLoop->demandInletNode().handle())) {
            return false;
          }

          const auto lastIndex = static_cast<unsigned>(remainingComponents.size() - 1u);
          if ((*branch == plantLoopImpl->supplyOutletBranch()) && !branchImpl->setComponentOutletNode(lastIndex, plantLoop->supplyOutletNode())) {
            return false;
          }
          if ((*branch == plantLoopImpl->supplyOutletBranch())
              && (remainingComponents[lastIndex].iddObject().type() == openstudio::IddObjectType::GroundHeatExchanger_System)
              && !remainingComponents[lastIndex].setPointer(openstudio::GroundHeatExchanger_SystemFields::OutletNodeName,
                                                            plantLoop->supplyOutletNode().handle())) {
            return false;
          }
          if ((*branch == plantLoopImpl->demandOutletBranch()) && !branchImpl->setComponentOutletNode(lastIndex, plantLoop->demandOutletNode())) {
            return false;
          }
          if ((*branch == plantLoopImpl->demandOutletBranch())
              && (remainingComponents[lastIndex].iddObject().type() == openstudio::IddObjectType::GroundHeatExchanger_System)
              && !remainingComponents[lastIndex].setPointer(openstudio::GroundHeatExchanger_SystemFields::OutletNodeName,
                                                            plantLoop->demandOutletNode().handle())) {
            return false;
          }
        }

        systemObject->setPointer(openstudio::GroundHeatExchanger_SystemFields::InletNodeName, Handle());
        systemObject->setPointer(openstudio::GroundHeatExchanger_SystemFields::OutletNodeName, Handle());
        return true;
      }

      return false;
    }

    std::vector<openstudio::IdfObject> GroundHeatExchangerVertical_Impl::remove() {
      auto propertiesObject = groundHeatExchangerVerticalProperties();
      auto systemObject = groundHeatExchangerSystem();
      auto result = StraightComponent_Impl::remove();
      if (!result.empty()) {
        if (auto properties = propertiesObject ? propertiesObject->optionalCast<ModelObject>() : boost::none) {
          properties->remove();
        }
        if (auto system = systemObject ? systemObject->optionalCast<ModelObject>() : boost::none) {
          system->remove();
        }
      }
      return result;
    }

    void GroundHeatExchangerVertical_Impl::disconnect() {
      if (auto owner = getObject<openstudio::epmodel::HVACComponent>().containingHVACComponent()) {
        LOG_FREE(Warn, "openstudio.epmodel.GroundHeatExchangerVertical",
                 "Refusing to disconnect " << getObject<ModelObject>().briefDescription() << " because its air-side connectivity is owned by "
                                           << owner->briefDescription() << ".");
        return;
      }

      const auto thisComponent = getObject<openstudio::epmodel::HVACComponent>();
      if (thisComponent.loop() && !removeFromLoop()) {
        LOG_FREE(Warn, "openstudio.epmodel.GroundHeatExchangerVertical",
                 "Failed to detach " << getObject<ModelObject>().briefDescription() << " from its loop topology before clearing node pointers.");
        return;
      }

      if (auto systemObject = groundHeatExchangerSystem()) {
        systemObject->setPointer(openstudio::GroundHeatExchanger_SystemFields::InletNodeName, Handle());
        systemObject->setPointer(openstudio::GroundHeatExchanger_SystemFields::OutletNodeName, Handle());
      }
    }

    bool GroundHeatExchangerVertical_Impl::addGFunction(double gFunctionLN, double gFunctionGValue) {
      auto group = getObject<ModelObject>().pushExtensibleGroup().cast<openstudio::WorkspaceExtensibleGroup>();
      bool ok = group.setDouble(openstudio::GroundHeatExchanger_ResponseFactorsExtensibleFields::gFunctionLn_T_Ts_Value, gFunctionLN);
      if (ok) {
        ok = group.setDouble(openstudio::GroundHeatExchanger_ResponseFactorsExtensibleFields::gFunctiongValue, gFunctionGValue);
      }
      if (!ok) {
        getObject<ModelObject>().eraseExtensibleGroup(group.groupIndex());
      }
      return ok;
    }

    void GroundHeatExchangerVertical_Impl::removeGFunction(unsigned groupIndex) {
      if (groupIndex < numExtensibleGroups()) {
        getObject<ModelObject>().eraseExtensibleGroup(groupIndex);
      }
    }

    void GroundHeatExchangerVertical_Impl::removeAllGFunctions() {
      getObject<ModelObject>().clearExtensibleGroups();
    }

    std::vector<std::pair<double, double>> GroundHeatExchangerVertical_Impl::gFunctions() {
      std::vector<std::pair<double, double>> result;
      for (const auto& group : extensibleGroups()) {
        auto workspaceGroup = group.cast<openstudio::WorkspaceExtensibleGroup>();
        auto lnValue = workspaceGroup.getDouble(openstudio::GroundHeatExchanger_ResponseFactorsExtensibleFields::gFunctionLn_T_Ts_Value);
        auto gValue = workspaceGroup.getDouble(openstudio::GroundHeatExchanger_ResponseFactorsExtensibleFields::gFunctiongValue);
        if (lnValue && gValue) {
          result.emplace_back(*lnValue, *gValue);
        }
      }
      return result;
    }

    boost::optional<double> GroundHeatExchangerVertical_Impl::designFlowRate() const {
      if (auto systemObject = groundHeatExchangerSystem()) {
        return systemObject->getDouble(openstudio::GroundHeatExchanger_SystemFields::DesignFlowRate, false);
      }
      return boost::none;
    }

    bool GroundHeatExchangerVertical_Impl::setDesignFlowRate(double designFlowRate) {
      auto systemObject = getOrCreateGroundHeatExchangerSystem();
      if (!systemObject) {
        return false;
      }
      return systemObject->setDouble(openstudio::GroundHeatExchanger_SystemFields::DesignFlowRate, designFlowRate);
    }

    boost::optional<double> GroundHeatExchangerVertical_Impl::groundThermalConductivity() const {
      if (auto systemObject = groundHeatExchangerSystem()) {
        return systemObject->getDouble(openstudio::GroundHeatExchanger_SystemFields::GroundThermalConductivity, false);
      }
      return boost::none;
    }

    bool GroundHeatExchangerVertical_Impl::setGroundThermalConductivity(double groundThermalConductivity) {
      auto systemObject = getOrCreateGroundHeatExchangerSystem();
      if (!systemObject) {
        return false;
      }
      return systemObject->setDouble(openstudio::GroundHeatExchanger_SystemFields::GroundThermalConductivity, groundThermalConductivity);
    }

    void GroundHeatExchangerVertical_Impl::resetGroundThermalConductivity() {
      if (auto systemObject = groundHeatExchangerSystem()) {
        OS_ASSERT(systemObject->setString(openstudio::GroundHeatExchanger_SystemFields::GroundThermalConductivity, ""));
      }
    }

    boost::optional<double> GroundHeatExchangerVertical_Impl::groundThermalHeatCapacity() const {
      if (auto systemObject = groundHeatExchangerSystem()) {
        return systemObject->getDouble(openstudio::GroundHeatExchanger_SystemFields::GroundThermalHeatCapacity, false);
      }
      return boost::none;
    }

    bool GroundHeatExchangerVertical_Impl::setGroundThermalHeatCapacity(double groundThermalHeatCapacity) {
      auto systemObject = getOrCreateGroundHeatExchangerSystem();
      if (!systemObject) {
        return false;
      }
      return systemObject->setDouble(openstudio::GroundHeatExchanger_SystemFields::GroundThermalHeatCapacity, groundThermalHeatCapacity);
    }

    void GroundHeatExchangerVertical_Impl::resetGroundThermalHeatCapacity() {
      if (auto systemObject = groundHeatExchangerSystem()) {
        OS_ASSERT(systemObject->setString(openstudio::GroundHeatExchanger_SystemFields::GroundThermalHeatCapacity, ""));
      }
    }

    double GroundHeatExchangerVertical_Impl::boreHoleTopDepth() const {
      if (auto propertiesObject = groundHeatExchangerVerticalProperties()) {
        const auto value = propertiesObject->getDouble(openstudio::GroundHeatExchanger_Vertical_PropertiesFields::DepthofTopofBorehole, false);
        OS_ASSERT(value);
        return *value;
      }
      OS_ASSERT(false);
      return 0.0;
    }

    bool GroundHeatExchangerVertical_Impl::setBoreHoleTopDepth(double boreHoleTopDepth) {
      auto propertiesObject = getOrCreateGroundHeatExchangerVerticalProperties();
      if (!propertiesObject) {
        return false;
      }
      return propertiesObject->setDouble(openstudio::GroundHeatExchanger_Vertical_PropertiesFields::DepthofTopofBorehole, boreHoleTopDepth);
    }

    boost::optional<double> GroundHeatExchangerVertical_Impl::boreHoleLength() const {
      if (auto propertiesObject = groundHeatExchangerVerticalProperties()) {
        return propertiesObject->getDouble(openstudio::GroundHeatExchanger_Vertical_PropertiesFields::BoreholeLength, false);
      }
      return boost::none;
    }

    bool GroundHeatExchangerVertical_Impl::setBoreHoleLength(double boreHoleLength) {
      auto propertiesObject = getOrCreateGroundHeatExchangerVerticalProperties();
      if (!propertiesObject) {
        return false;
      }
      return propertiesObject->setDouble(openstudio::GroundHeatExchanger_Vertical_PropertiesFields::BoreholeLength, boreHoleLength);
    }

    void GroundHeatExchangerVertical_Impl::resetBoreHoleLength() {
      if (auto propertiesObject = groundHeatExchangerVerticalProperties()) {
        OS_ASSERT(propertiesObject->setString(openstudio::GroundHeatExchanger_Vertical_PropertiesFields::BoreholeLength, ""));
      }
    }

    boost::optional<double> GroundHeatExchangerVertical_Impl::boreHoleRadius() const {
      if (auto propertiesObject = groundHeatExchangerVerticalProperties()) {
        if (const auto diameter = propertiesObject->getDouble(openstudio::GroundHeatExchanger_Vertical_PropertiesFields::BoreholeDiameter, false)) {
          return *diameter / 2.0;
        }
      }
      return boost::none;
    }

    bool GroundHeatExchangerVertical_Impl::setBoreHoleRadius(double boreHoleRadius) {
      auto propertiesObject = getOrCreateGroundHeatExchangerVerticalProperties();
      if (!propertiesObject) {
        return false;
      }
      return propertiesObject->setDouble(openstudio::GroundHeatExchanger_Vertical_PropertiesFields::BoreholeDiameter, 2.0 * boreHoleRadius);
    }

    void GroundHeatExchangerVertical_Impl::resetBoreHoleRadius() {
      if (auto propertiesObject = groundHeatExchangerVerticalProperties()) {
        OS_ASSERT(propertiesObject->setString(openstudio::GroundHeatExchanger_Vertical_PropertiesFields::BoreholeDiameter, ""));
      }
    }

    boost::optional<double> GroundHeatExchangerVertical_Impl::groutThermalConductivity() const {
      if (auto propertiesObject = groundHeatExchangerVerticalProperties()) {
        return propertiesObject->getDouble(openstudio::GroundHeatExchanger_Vertical_PropertiesFields::GroutThermalConductivity, false);
      }
      return boost::none;
    }

    bool GroundHeatExchangerVertical_Impl::setGroutThermalConductivity(double groutThermalConductivity) {
      auto propertiesObject = getOrCreateGroundHeatExchangerVerticalProperties();
      if (!propertiesObject) {
        return false;
      }
      return propertiesObject->setDouble(openstudio::GroundHeatExchanger_Vertical_PropertiesFields::GroutThermalConductivity,
                                         groutThermalConductivity);
    }

    void GroundHeatExchangerVertical_Impl::resetGroutThermalConductivity() {
      if (auto propertiesObject = groundHeatExchangerVerticalProperties()) {
        OS_ASSERT(propertiesObject->setString(openstudio::GroundHeatExchanger_Vertical_PropertiesFields::GroutThermalConductivity, ""));
      }
    }

    boost::optional<double> GroundHeatExchangerVertical_Impl::pipeThermalConductivity() const {
      if (auto propertiesObject = groundHeatExchangerVerticalProperties()) {
        return propertiesObject->getDouble(openstudio::GroundHeatExchanger_Vertical_PropertiesFields::PipeThermalConductivity, false);
      }
      return boost::none;
    }

    bool GroundHeatExchangerVertical_Impl::setPipeThermalConductivity(double pipeThermalConductivity) {
      auto propertiesObject = getOrCreateGroundHeatExchangerVerticalProperties();
      if (!propertiesObject) {
        return false;
      }
      return propertiesObject->setDouble(openstudio::GroundHeatExchanger_Vertical_PropertiesFields::PipeThermalConductivity, pipeThermalConductivity);
    }

    void GroundHeatExchangerVertical_Impl::resetPipeThermalConductivity() {
      if (auto propertiesObject = groundHeatExchangerVerticalProperties()) {
        OS_ASSERT(propertiesObject->setString(openstudio::GroundHeatExchanger_Vertical_PropertiesFields::PipeThermalConductivity, ""));
      }
    }

    boost::optional<double> GroundHeatExchangerVertical_Impl::pipeOutDiameter() const {
      if (auto propertiesObject = groundHeatExchangerVerticalProperties()) {
        return propertiesObject->getDouble(openstudio::GroundHeatExchanger_Vertical_PropertiesFields::PipeOuterDiameter, false);
      }
      return boost::none;
    }

    bool GroundHeatExchangerVertical_Impl::setPipeOutDiameter(double pipeOutDiameter) {
      auto propertiesObject = getOrCreateGroundHeatExchangerVerticalProperties();
      if (!propertiesObject) {
        return false;
      }
      return propertiesObject->setDouble(openstudio::GroundHeatExchanger_Vertical_PropertiesFields::PipeOuterDiameter, pipeOutDiameter);
    }

    void GroundHeatExchangerVertical_Impl::resetPipeOutDiameter() {
      if (auto propertiesObject = groundHeatExchangerVerticalProperties()) {
        OS_ASSERT(propertiesObject->setString(openstudio::GroundHeatExchanger_Vertical_PropertiesFields::PipeOuterDiameter, ""));
      }
    }

    boost::optional<double> GroundHeatExchangerVertical_Impl::uTubeDistance() const {
      if (auto propertiesObject = groundHeatExchangerVerticalProperties()) {
        return propertiesObject->getDouble(openstudio::GroundHeatExchanger_Vertical_PropertiesFields::UTubeDistance, false);
      }
      return boost::none;
    }

    bool GroundHeatExchangerVertical_Impl::setUTubeDistance(double uTubeDistance) {
      auto propertiesObject = getOrCreateGroundHeatExchangerVerticalProperties();
      if (!propertiesObject) {
        return false;
      }
      return propertiesObject->setDouble(openstudio::GroundHeatExchanger_Vertical_PropertiesFields::UTubeDistance, uTubeDistance);
    }

    void GroundHeatExchangerVertical_Impl::resetUTubeDistance() {
      if (auto propertiesObject = groundHeatExchangerVerticalProperties()) {
        OS_ASSERT(propertiesObject->setString(openstudio::GroundHeatExchanger_Vertical_PropertiesFields::UTubeDistance, ""));
      }
    }

    boost::optional<double> GroundHeatExchangerVertical_Impl::pipeThickness() const {
      if (auto propertiesObject = groundHeatExchangerVerticalProperties()) {
        return propertiesObject->getDouble(openstudio::GroundHeatExchanger_Vertical_PropertiesFields::PipeThickness, false);
      }
      return boost::none;
    }

    bool GroundHeatExchangerVertical_Impl::setPipeThickness(double pipeThickness) {
      auto propertiesObject = getOrCreateGroundHeatExchangerVerticalProperties();
      if (!propertiesObject) {
        return false;
      }
      return propertiesObject->setDouble(openstudio::GroundHeatExchanger_Vertical_PropertiesFields::PipeThickness, pipeThickness);
    }

    void GroundHeatExchangerVertical_Impl::resetPipeThickness() {
      if (auto propertiesObject = groundHeatExchangerVerticalProperties()) {
        OS_ASSERT(propertiesObject->setString(openstudio::GroundHeatExchanger_Vertical_PropertiesFields::PipeThickness, ""));
      }
    }

    boost::optional<int> GroundHeatExchangerVertical_Impl::numberofBoreHoles() const {
      return getInt(openstudio::GroundHeatExchanger_ResponseFactorsFields::NumberofBoreholes, true);
    }

    bool GroundHeatExchangerVertical_Impl::setNumberofBoreHoles(int numberofBoreHoles) {
      return setInt(openstudio::GroundHeatExchanger_ResponseFactorsFields::NumberofBoreholes, numberofBoreHoles);
    }

    void GroundHeatExchangerVertical_Impl::resetNumberofBoreHoles() {
      OS_ASSERT(setString(openstudio::GroundHeatExchanger_ResponseFactorsFields::NumberofBoreholes, ""));
    }

    double GroundHeatExchangerVertical_Impl::gFunctionReferenceRatio() const {
      const auto value = getDouble(openstudio::GroundHeatExchanger_ResponseFactorsFields::GFunctionReferenceRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatExchangerVertical_Impl::isGFunctionReferenceRatioDefaulted() const {
      return isEmpty(openstudio::GroundHeatExchanger_ResponseFactorsFields::GFunctionReferenceRatio);
    }

    bool GroundHeatExchangerVertical_Impl::setGFunctionReferenceRatio(double gFunctionReferenceRatio) {
      return setDouble(openstudio::GroundHeatExchanger_ResponseFactorsFields::GFunctionReferenceRatio, gFunctionReferenceRatio);
    }

    void GroundHeatExchangerVertical_Impl::resetGFunctionReferenceRatio() {
      OS_ASSERT(setString(openstudio::GroundHeatExchanger_ResponseFactorsFields::GFunctionReferenceRatio, ""));
    }

    ModelObject GroundHeatExchangerVertical_Impl::undisturbedGroundTemperatureModel() const {
      if (auto systemObject = groundHeatExchangerSystem()) {
        if (auto target = systemObject->getTarget(openstudio::GroundHeatExchanger_SystemFields::UndisturbedGroundTemperatureModelName)) {
          if (auto modelObject = target->optionalCast<ModelObject>()) {
            return *modelObject;
          }
        }
      }
      LOG_FREE_AND_THROW("openstudio.epmodel.GroundHeatExchangerVertical", briefDescription()
                                                                             << " does not have an Undisturbed Ground Temperature Model attached.");
    }

    bool GroundHeatExchangerVertical_Impl::setUndisturbedGroundTemperatureModel(const ModelObject& undisturbedGroundTemperatureModel) {
      auto systemObject = getOrCreateGroundHeatExchangerSystem();
      if (!systemObject) {
        return false;
      }

      const bool ok = systemObject->setPointer(openstudio::GroundHeatExchanger_SystemFields::UndisturbedGroundTemperatureModelName,
                                               undisturbedGroundTemperatureModel.handle());
      if (!ok) {
        return false;
      }
      return systemObject->setString(openstudio::GroundHeatExchanger_SystemFields::UndisturbedGroundTemperatureModelType,
                                     undisturbedGroundTemperatureModel.iddObject().name());
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
