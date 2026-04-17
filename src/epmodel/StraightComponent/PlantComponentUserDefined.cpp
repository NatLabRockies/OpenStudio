/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/PlantComponentUserDefined.hpp"
#include "StraightComponent/PlantComponentUserDefined_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/PlantComponent_UserDefined_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  PlantComponentUserDefined::PlantComponentUserDefined(const Model& model) : StraightComponent(PlantComponentUserDefined::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::PlantComponentUserDefined_Impl>());
    OS_ASSERT(setNumberOfPlantLoopConnections(1));
    OS_ASSERT(setPlantConnection1LoadingMode("MeetsLoadWithNominalCapacityHiOutLimit"));
    OS_ASSERT(setPlantConnection1LoopFlowRequestMode("NeedsFlowIfLoopOn"));
  }

  PlantComponentUserDefined::PlantComponentUserDefined(std::shared_ptr<detail::PlantComponentUserDefined_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType PlantComponentUserDefined::iddObjectType() {
    return IddObjectType::PlantComponent_UserDefined;
  }

  std::vector<std::string> PlantComponentUserDefined::plantConnection1LoadingModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PlantComponent_UserDefinedFields::PlantConnection1LoadingMode);
  }

  std::vector<std::string> PlantComponentUserDefined::plantConnection1LoopFlowRequestModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PlantComponent_UserDefinedFields::PlantConnection1LoopFlowRequestMode);
  }

  std::vector<std::string> PlantComponentUserDefined::plantConnection2LoadingModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PlantComponent_UserDefinedFields::PlantConnection2LoadingMode);
  }

  std::vector<std::string> PlantComponentUserDefined::plantConnection2LoopFlowRequestModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PlantComponent_UserDefinedFields::PlantConnection2LoopFlowRequestMode);
  }

  std::vector<std::string> PlantComponentUserDefined::plantConnection3LoadingModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PlantComponent_UserDefinedFields::PlantConnection3LoadingMode);
  }

  std::vector<std::string> PlantComponentUserDefined::plantConnection3LoopFlowRequestModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PlantComponent_UserDefinedFields::PlantConnection3LoopFlowRequestMode);
  }

  std::vector<std::string> PlantComponentUserDefined::plantConnection4LoadingModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PlantComponent_UserDefinedFields::PlantConnection4LoadingMode);
  }

  std::vector<std::string> PlantComponentUserDefined::plantConnection4LoopFlowRequestModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PlantComponent_UserDefinedFields::PlantConnection4LoopFlowRequestMode);
  }

  int PlantComponentUserDefined::numberOfPlantLoopConnections() const {
    return getImpl<detail::PlantComponentUserDefined_Impl>()->numberOfPlantLoopConnections();
  }

  bool PlantComponentUserDefined::setNumberOfPlantLoopConnections(int numberOfPlantLoopConnections) {
    return getImpl<detail::PlantComponentUserDefined_Impl>()->setNumberOfPlantLoopConnections(numberOfPlantLoopConnections);
  }

  std::string PlantComponentUserDefined::plantConnection1LoadingMode() const {
    return getImpl<detail::PlantComponentUserDefined_Impl>()->plantConnection1LoadingMode();
  }

  bool PlantComponentUserDefined::setPlantConnection1LoadingMode(const std::string& plantConnection1LoadingMode) {
    return getImpl<detail::PlantComponentUserDefined_Impl>()->setPlantConnection1LoadingMode(plantConnection1LoadingMode);
  }

  std::string PlantComponentUserDefined::plantConnection1LoopFlowRequestMode() const {
    return getImpl<detail::PlantComponentUserDefined_Impl>()->plantConnection1LoopFlowRequestMode();
  }

  bool PlantComponentUserDefined::setPlantConnection1LoopFlowRequestMode(const std::string& plantConnection1LoopFlowRequestMode) {
    return getImpl<detail::PlantComponentUserDefined_Impl>()->setPlantConnection1LoopFlowRequestMode(plantConnection1LoopFlowRequestMode);
  }

  boost::optional<std::string> PlantComponentUserDefined::plantConnection2LoadingMode() const {
    return getImpl<detail::PlantComponentUserDefined_Impl>()->plantConnection2LoadingMode();
  }

  bool PlantComponentUserDefined::setPlantConnection2LoadingMode(const std::string& plantConnection2LoadingMode) {
    return getImpl<detail::PlantComponentUserDefined_Impl>()->setPlantConnection2LoadingMode(plantConnection2LoadingMode);
  }

  void PlantComponentUserDefined::resetPlantConnection2LoadingMode() {
    getImpl<detail::PlantComponentUserDefined_Impl>()->resetPlantConnection2LoadingMode();
  }

  boost::optional<std::string> PlantComponentUserDefined::plantConnection2LoopFlowRequestMode() const {
    return getImpl<detail::PlantComponentUserDefined_Impl>()->plantConnection2LoopFlowRequestMode();
  }

  bool PlantComponentUserDefined::setPlantConnection2LoopFlowRequestMode(const std::string& plantConnection2LoopFlowRequestMode) {
    return getImpl<detail::PlantComponentUserDefined_Impl>()->setPlantConnection2LoopFlowRequestMode(plantConnection2LoopFlowRequestMode);
  }

  void PlantComponentUserDefined::resetPlantConnection2LoopFlowRequestMode() {
    getImpl<detail::PlantComponentUserDefined_Impl>()->resetPlantConnection2LoopFlowRequestMode();
  }

  boost::optional<std::string> PlantComponentUserDefined::plantConnection3LoadingMode() const {
    return getImpl<detail::PlantComponentUserDefined_Impl>()->plantConnection3LoadingMode();
  }

  bool PlantComponentUserDefined::setPlantConnection3LoadingMode(const std::string& plantConnection3LoadingMode) {
    return getImpl<detail::PlantComponentUserDefined_Impl>()->setPlantConnection3LoadingMode(plantConnection3LoadingMode);
  }

  void PlantComponentUserDefined::resetPlantConnection3LoadingMode() {
    getImpl<detail::PlantComponentUserDefined_Impl>()->resetPlantConnection3LoadingMode();
  }

  boost::optional<std::string> PlantComponentUserDefined::plantConnection3LoopFlowRequestMode() const {
    return getImpl<detail::PlantComponentUserDefined_Impl>()->plantConnection3LoopFlowRequestMode();
  }

  bool PlantComponentUserDefined::setPlantConnection3LoopFlowRequestMode(const std::string& plantConnection3LoopFlowRequestMode) {
    return getImpl<detail::PlantComponentUserDefined_Impl>()->setPlantConnection3LoopFlowRequestMode(plantConnection3LoopFlowRequestMode);
  }

  void PlantComponentUserDefined::resetPlantConnection3LoopFlowRequestMode() {
    getImpl<detail::PlantComponentUserDefined_Impl>()->resetPlantConnection3LoopFlowRequestMode();
  }

  boost::optional<std::string> PlantComponentUserDefined::plantConnection4LoadingMode() const {
    return getImpl<detail::PlantComponentUserDefined_Impl>()->plantConnection4LoadingMode();
  }

  bool PlantComponentUserDefined::setPlantConnection4LoadingMode(const std::string& plantConnection4LoadingMode) {
    return getImpl<detail::PlantComponentUserDefined_Impl>()->setPlantConnection4LoadingMode(plantConnection4LoadingMode);
  }

  void PlantComponentUserDefined::resetPlantConnection4LoadingMode() {
    getImpl<detail::PlantComponentUserDefined_Impl>()->resetPlantConnection4LoadingMode();
  }

  boost::optional<std::string> PlantComponentUserDefined::plantConnection4LoopFlowRequestMode() const {
    return getImpl<detail::PlantComponentUserDefined_Impl>()->plantConnection4LoopFlowRequestMode();
  }

  bool PlantComponentUserDefined::setPlantConnection4LoopFlowRequestMode(const std::string& plantConnection4LoopFlowRequestMode) {
    return getImpl<detail::PlantComponentUserDefined_Impl>()->setPlantConnection4LoopFlowRequestMode(plantConnection4LoopFlowRequestMode);
  }

  void PlantComponentUserDefined::resetPlantConnection4LoopFlowRequestMode() {
    getImpl<detail::PlantComponentUserDefined_Impl>()->resetPlantConnection4LoopFlowRequestMode();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned PlantComponentUserDefined_Impl::inletPort() const {
      return openstudio::PlantComponent_UserDefinedFields::PlantConnection1InletNodeName;
    }

    unsigned PlantComponentUserDefined_Impl::outletPort() const {
      return openstudio::PlantComponent_UserDefinedFields::PlantConnection1OutletNodeName;
    }

    int PlantComponentUserDefined_Impl::numberOfPlantLoopConnections() const {
      const auto value = getInt(openstudio::PlantComponent_UserDefinedFields::NumberofPlantLoopConnections, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PlantComponentUserDefined_Impl::setNumberOfPlantLoopConnections(int numberOfPlantLoopConnections) {
      if (numberOfPlantLoopConnections != 1) {
        return false;
      }
      return setInt(openstudio::PlantComponent_UserDefinedFields::NumberofPlantLoopConnections, numberOfPlantLoopConnections);
    }

    std::string PlantComponentUserDefined_Impl::plantConnection1LoadingMode() const {
      const auto value = getString(openstudio::PlantComponent_UserDefinedFields::PlantConnection1LoadingMode, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PlantComponentUserDefined_Impl::setPlantConnection1LoadingMode(const std::string& plantConnection1LoadingMode) {
      return setString(openstudio::PlantComponent_UserDefinedFields::PlantConnection1LoadingMode, plantConnection1LoadingMode);
    }

    std::vector<std::string> PlantComponentUserDefined_Impl::plantConnection1LoadingModeValues() const {
      return PlantComponentUserDefined::plantConnection1LoadingModeValues();
    }

    std::string PlantComponentUserDefined_Impl::plantConnection1LoopFlowRequestMode() const {
      const auto value = getString(openstudio::PlantComponent_UserDefinedFields::PlantConnection1LoopFlowRequestMode, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PlantComponentUserDefined_Impl::setPlantConnection1LoopFlowRequestMode(const std::string& plantConnection1LoopFlowRequestMode) {
      return setString(openstudio::PlantComponent_UserDefinedFields::PlantConnection1LoopFlowRequestMode, plantConnection1LoopFlowRequestMode);
    }

    std::vector<std::string> PlantComponentUserDefined_Impl::plantConnection1LoopFlowRequestModeValues() const {
      return PlantComponentUserDefined::plantConnection1LoopFlowRequestModeValues();
    }

    boost::optional<std::string> PlantComponentUserDefined_Impl::plantConnection2LoadingMode() const {
      return getString(openstudio::PlantComponent_UserDefinedFields::PlantConnection2LoadingMode, true);
    }

    bool PlantComponentUserDefined_Impl::setPlantConnection2LoadingMode(const std::string& plantConnection2LoadingMode) {
      return setString(openstudio::PlantComponent_UserDefinedFields::PlantConnection2LoadingMode, plantConnection2LoadingMode);
    }

    void PlantComponentUserDefined_Impl::resetPlantConnection2LoadingMode() {
      OS_ASSERT(setString(openstudio::PlantComponent_UserDefinedFields::PlantConnection2LoadingMode, ""));
    }

    std::vector<std::string> PlantComponentUserDefined_Impl::plantConnection2LoadingModeValues() const {
      return PlantComponentUserDefined::plantConnection2LoadingModeValues();
    }

    boost::optional<std::string> PlantComponentUserDefined_Impl::plantConnection2LoopFlowRequestMode() const {
      return getString(openstudio::PlantComponent_UserDefinedFields::PlantConnection2LoopFlowRequestMode, true);
    }

    bool PlantComponentUserDefined_Impl::setPlantConnection2LoopFlowRequestMode(const std::string& plantConnection2LoopFlowRequestMode) {
      return setString(openstudio::PlantComponent_UserDefinedFields::PlantConnection2LoopFlowRequestMode, plantConnection2LoopFlowRequestMode);
    }

    void PlantComponentUserDefined_Impl::resetPlantConnection2LoopFlowRequestMode() {
      OS_ASSERT(setString(openstudio::PlantComponent_UserDefinedFields::PlantConnection2LoopFlowRequestMode, ""));
    }

    std::vector<std::string> PlantComponentUserDefined_Impl::plantConnection2LoopFlowRequestModeValues() const {
      return PlantComponentUserDefined::plantConnection2LoopFlowRequestModeValues();
    }

    boost::optional<std::string> PlantComponentUserDefined_Impl::plantConnection3LoadingMode() const {
      return getString(openstudio::PlantComponent_UserDefinedFields::PlantConnection3LoadingMode, true);
    }

    bool PlantComponentUserDefined_Impl::setPlantConnection3LoadingMode(const std::string& plantConnection3LoadingMode) {
      return setString(openstudio::PlantComponent_UserDefinedFields::PlantConnection3LoadingMode, plantConnection3LoadingMode);
    }

    void PlantComponentUserDefined_Impl::resetPlantConnection3LoadingMode() {
      OS_ASSERT(setString(openstudio::PlantComponent_UserDefinedFields::PlantConnection3LoadingMode, ""));
    }

    std::vector<std::string> PlantComponentUserDefined_Impl::plantConnection3LoadingModeValues() const {
      return PlantComponentUserDefined::plantConnection3LoadingModeValues();
    }

    boost::optional<std::string> PlantComponentUserDefined_Impl::plantConnection3LoopFlowRequestMode() const {
      return getString(openstudio::PlantComponent_UserDefinedFields::PlantConnection3LoopFlowRequestMode, true);
    }

    bool PlantComponentUserDefined_Impl::setPlantConnection3LoopFlowRequestMode(const std::string& plantConnection3LoopFlowRequestMode) {
      return setString(openstudio::PlantComponent_UserDefinedFields::PlantConnection3LoopFlowRequestMode, plantConnection3LoopFlowRequestMode);
    }

    void PlantComponentUserDefined_Impl::resetPlantConnection3LoopFlowRequestMode() {
      OS_ASSERT(setString(openstudio::PlantComponent_UserDefinedFields::PlantConnection3LoopFlowRequestMode, ""));
    }

    std::vector<std::string> PlantComponentUserDefined_Impl::plantConnection3LoopFlowRequestModeValues() const {
      return PlantComponentUserDefined::plantConnection3LoopFlowRequestModeValues();
    }

    boost::optional<std::string> PlantComponentUserDefined_Impl::plantConnection4LoadingMode() const {
      return getString(openstudio::PlantComponent_UserDefinedFields::PlantConnection4LoadingMode, true);
    }

    bool PlantComponentUserDefined_Impl::setPlantConnection4LoadingMode(const std::string& plantConnection4LoadingMode) {
      return setString(openstudio::PlantComponent_UserDefinedFields::PlantConnection4LoadingMode, plantConnection4LoadingMode);
    }

    void PlantComponentUserDefined_Impl::resetPlantConnection4LoadingMode() {
      OS_ASSERT(setString(openstudio::PlantComponent_UserDefinedFields::PlantConnection4LoadingMode, ""));
    }

    std::vector<std::string> PlantComponentUserDefined_Impl::plantConnection4LoadingModeValues() const {
      return PlantComponentUserDefined::plantConnection4LoadingModeValues();
    }

    boost::optional<std::string> PlantComponentUserDefined_Impl::plantConnection4LoopFlowRequestMode() const {
      return getString(openstudio::PlantComponent_UserDefinedFields::PlantConnection4LoopFlowRequestMode, true);
    }

    bool PlantComponentUserDefined_Impl::setPlantConnection4LoopFlowRequestMode(const std::string& plantConnection4LoopFlowRequestMode) {
      return setString(openstudio::PlantComponent_UserDefinedFields::PlantConnection4LoopFlowRequestMode, plantConnection4LoopFlowRequestMode);
    }

    void PlantComponentUserDefined_Impl::resetPlantConnection4LoopFlowRequestMode() {
      OS_ASSERT(setString(openstudio::PlantComponent_UserDefinedFields::PlantConnection4LoopFlowRequestMode, ""));
    }

    std::vector<std::string> PlantComponentUserDefined_Impl::plantConnection4LoopFlowRequestModeValues() const {
      return PlantComponentUserDefined::plantConnection4LoopFlowRequestModeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
