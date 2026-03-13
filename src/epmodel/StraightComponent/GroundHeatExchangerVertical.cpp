/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/GroundHeatExchangerVertical.hpp"
#include "StraightComponent/GroundHeatExchangerVertical_Impl.hpp"

#include "Model.hpp"
#include "ModelObject/ModelObject.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/GroundHeatExchanger_ResponseFactors_FieldEnums.hxx>
#include <utilities/idd/GroundHeatExchanger_System_FieldEnums.hxx>
#include <utilities/idd/GroundHeatExchanger_Vertical_Properties_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  GroundHeatExchangerVertical::GroundHeatExchangerVertical(const Model& model)
    : StraightComponent(GroundHeatExchangerVertical::iddObjectType(), model) {
    bool ok = true;
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
  }

  GroundHeatExchangerVertical::GroundHeatExchangerVertical(std::shared_ptr<detail::GroundHeatExchangerVertical_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType GroundHeatExchangerVertical::iddObjectType() {
    return IddObjectType::GroundHeatExchanger_ResponseFactors;
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

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned GroundHeatExchangerVertical_Impl::inletPort() const {
      // EnergyPlus GroundHeatExchanger:ResponseFactors has no direct inlet/outlet node fields.
      return 0;
    }

    unsigned GroundHeatExchangerVertical_Impl::outletPort() const {
      // Node connectivity is delegated through GroundHeatExchanger:System.
      return 0;
    }

    boost::optional<openstudio::WorkspaceObject> GroundHeatExchangerVertical_Impl::groundHeatExchangerSystem() const {
      const auto responseFactorsName = getObject<openstudio::epmodel::GroundHeatExchangerVertical>().nameString();
      for (const auto& modelObject : model().getObjectsByType(openstudio::IddObjectType::GroundHeatExchanger_System)) {
        auto linkedResponseFactorsName =
          modelObject.getString(openstudio::GroundHeatExchanger_SystemFields::GHE_Vertical_ResponseFactorsObjectName, false);
        if (linkedResponseFactorsName && (*linkedResponseFactorsName == responseFactorsName)) {
          return modelObject;
        }
      }
      return boost::none;
    }

    boost::optional<openstudio::WorkspaceObject> GroundHeatExchangerVertical_Impl::getOrCreateGroundHeatExchangerSystem() {
      if (auto existing = groundHeatExchangerSystem()) {
        return existing;
      }

      auto systemObject = openstudio::epmodel::ModelObject::create(openstudio::IddObjectType::GroundHeatExchanger_System, model(), true);
      const auto responseFactorsName = getObject<openstudio::epmodel::GroundHeatExchangerVertical>().nameString();

      if (!systemObject.setName(responseFactorsName + " System")) {
        return boost::none;
      }

      if (!systemObject.setString(openstudio::GroundHeatExchanger_SystemFields::GHE_Vertical_ResponseFactorsObjectName, responseFactorsName)) {
        return boost::none;
      }

      return systemObject;
    }

    boost::optional<openstudio::WorkspaceObject> GroundHeatExchangerVertical_Impl::groundHeatExchangerVerticalProperties() const {
      auto propertiesName = getString(openstudio::GroundHeatExchanger_ResponseFactorsFields::GHE_Vertical_PropertiesObjectName, false);
      if (!propertiesName) {
        return boost::none;
      }

      for (const auto& modelObject : model().getObjectsByType(openstudio::IddObjectType::GroundHeatExchanger_Vertical_Properties)) {
        const auto currentName = modelObject.nameString();
        if (currentName == *propertiesName) {
          return modelObject;
        }
      }
      return boost::none;
    }

    boost::optional<openstudio::WorkspaceObject> GroundHeatExchangerVertical_Impl::getOrCreateGroundHeatExchangerVerticalProperties() {
      if (auto existing = groundHeatExchangerVerticalProperties()) {
        return existing;
      }

      auto propertiesObject =
        openstudio::epmodel::ModelObject::create(openstudio::IddObjectType::GroundHeatExchanger_Vertical_Properties, model(), true);
      const auto responseFactorsName = getObject<openstudio::epmodel::GroundHeatExchangerVertical>().nameString();
      const auto propertiesName = responseFactorsName + " Properties";

      if (!propertiesObject.setName(propertiesName)) {
        return boost::none;
      }

      if (!setString(openstudio::GroundHeatExchanger_ResponseFactorsFields::GHE_Vertical_PropertiesObjectName, propertiesName)) {
        return boost::none;
      }

      return propertiesObject;
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

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
