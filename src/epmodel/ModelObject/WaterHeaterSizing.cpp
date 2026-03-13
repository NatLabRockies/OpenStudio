/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterHeaterSizing.hpp"
#include "WaterHeaterSizing_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/WaterHeater_Sizing_FieldEnums.hxx>

#include <utility>

namespace openstudio {
namespace epmodel {

  WaterHeaterSizing::WaterHeaterSizing(const Model& model) : ModelObject(WaterHeaterSizing::iddObjectType(), model) {
    setDesignMode("PeakDraw");
    setTimeStorageCanMeetPeakDraw(0.538503);
    setTimeforTankRecovery(0.0);
    setNominalTankVolumeforAutosizingPlantConnections(1.0);
  }

  WaterHeaterSizing::WaterHeaterSizing(std::shared_ptr<detail::WaterHeaterSizing_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType WaterHeaterSizing::iddObjectType() {
    return IddObjectType::WaterHeater_Sizing;
  }

  std::vector<std::string> WaterHeaterSizing::designModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), WaterHeater_SizingFields::DesignMode);
  }

  boost::optional<std::string> WaterHeaterSizing::designMode() const {
    return getImpl<detail::WaterHeaterSizing_Impl>()->designMode();
  }

  bool WaterHeaterSizing::setDesignMode(const std::string& designMode) {
    return getImpl<detail::WaterHeaterSizing_Impl>()->setDesignMode(designMode);
  }

  void WaterHeaterSizing::resetDesignMode() {
    getImpl<detail::WaterHeaterSizing_Impl>()->resetDesignMode();
  }

  boost::optional<double> WaterHeaterSizing::timeStorageCanMeetPeakDraw() const {
    return getImpl<detail::WaterHeaterSizing_Impl>()->timeStorageCanMeetPeakDraw();
  }

  bool WaterHeaterSizing::setTimeStorageCanMeetPeakDraw(double timeStorageCanMeetPeakDraw) {
    return getImpl<detail::WaterHeaterSizing_Impl>()->setTimeStorageCanMeetPeakDraw(timeStorageCanMeetPeakDraw);
  }

  void WaterHeaterSizing::resetTimeStorageCanMeetPeakDraw() {
    getImpl<detail::WaterHeaterSizing_Impl>()->resetTimeStorageCanMeetPeakDraw();
  }

  boost::optional<double> WaterHeaterSizing::timeforTankRecovery() const {
    return getImpl<detail::WaterHeaterSizing_Impl>()->timeforTankRecovery();
  }

  bool WaterHeaterSizing::setTimeforTankRecovery(double timeforTankRecovery) {
    return getImpl<detail::WaterHeaterSizing_Impl>()->setTimeforTankRecovery(timeforTankRecovery);
  }

  void WaterHeaterSizing::resetTimeforTankRecovery() {
    getImpl<detail::WaterHeaterSizing_Impl>()->resetTimeforTankRecovery();
  }

  boost::optional<double> WaterHeaterSizing::nominalTankVolumeforAutosizingPlantConnections() const {
    return getImpl<detail::WaterHeaterSizing_Impl>()->nominalTankVolumeforAutosizingPlantConnections();
  }

  bool WaterHeaterSizing::setNominalTankVolumeforAutosizingPlantConnections(double nominalTankVolumeforAutosizingPlantConnections) {
    return getImpl<detail::WaterHeaterSizing_Impl>()->setNominalTankVolumeforAutosizingPlantConnections(
      nominalTankVolumeforAutosizingPlantConnections);
  }

  void WaterHeaterSizing::resetNominalTankVolumeforAutosizingPlantConnections() {
    getImpl<detail::WaterHeaterSizing_Impl>()->resetNominalTankVolumeforAutosizingPlantConnections();
  }

  boost::optional<int> WaterHeaterSizing::numberofBedrooms() const {
    return getImpl<detail::WaterHeaterSizing_Impl>()->numberofBedrooms();
  }

  bool WaterHeaterSizing::setNumberofBedrooms(int numberofBedrooms) {
    return getImpl<detail::WaterHeaterSizing_Impl>()->setNumberofBedrooms(numberofBedrooms);
  }

  void WaterHeaterSizing::resetNumberofBedrooms() {
    getImpl<detail::WaterHeaterSizing_Impl>()->resetNumberofBedrooms();
  }

  boost::optional<int> WaterHeaterSizing::numberofBathrooms() const {
    return getImpl<detail::WaterHeaterSizing_Impl>()->numberofBathrooms();
  }

  bool WaterHeaterSizing::setNumberofBathrooms(int numberofBathrooms) {
    return getImpl<detail::WaterHeaterSizing_Impl>()->setNumberofBathrooms(numberofBathrooms);
  }

  void WaterHeaterSizing::resetNumberofBathrooms() {
    getImpl<detail::WaterHeaterSizing_Impl>()->resetNumberofBathrooms();
  }

  boost::optional<double> WaterHeaterSizing::storageCapacityperPerson() const {
    return getImpl<detail::WaterHeaterSizing_Impl>()->storageCapacityperPerson();
  }

  bool WaterHeaterSizing::setStorageCapacityperPerson(double storageCapacityperPerson) {
    return getImpl<detail::WaterHeaterSizing_Impl>()->setStorageCapacityperPerson(storageCapacityperPerson);
  }

  void WaterHeaterSizing::resetStorageCapacityperPerson() {
    getImpl<detail::WaterHeaterSizing_Impl>()->resetStorageCapacityperPerson();
  }

  boost::optional<double> WaterHeaterSizing::recoveryCapacityperPerson() const {
    return getImpl<detail::WaterHeaterSizing_Impl>()->recoveryCapacityperPerson();
  }

  bool WaterHeaterSizing::setRecoveryCapacityperPerson(double recoveryCapacityperPerson) {
    return getImpl<detail::WaterHeaterSizing_Impl>()->setRecoveryCapacityperPerson(recoveryCapacityperPerson);
  }

  void WaterHeaterSizing::resetRecoveryCapacityperPerson() {
    getImpl<detail::WaterHeaterSizing_Impl>()->resetRecoveryCapacityperPerson();
  }

  boost::optional<double> WaterHeaterSizing::storageCapacityperFloorArea() const {
    return getImpl<detail::WaterHeaterSizing_Impl>()->storageCapacityperFloorArea();
  }

  bool WaterHeaterSizing::setStorageCapacityperFloorArea(double storageCapacityperFloorArea) {
    return getImpl<detail::WaterHeaterSizing_Impl>()->setStorageCapacityperFloorArea(storageCapacityperFloorArea);
  }

  void WaterHeaterSizing::resetStorageCapacityperFloorArea() {
    getImpl<detail::WaterHeaterSizing_Impl>()->resetStorageCapacityperFloorArea();
  }

  boost::optional<double> WaterHeaterSizing::recoveryCapacityperFloorArea() const {
    return getImpl<detail::WaterHeaterSizing_Impl>()->recoveryCapacityperFloorArea();
  }

  bool WaterHeaterSizing::setRecoveryCapacityperFloorArea(double recoveryCapacityperFloorArea) {
    return getImpl<detail::WaterHeaterSizing_Impl>()->setRecoveryCapacityperFloorArea(recoveryCapacityperFloorArea);
  }

  void WaterHeaterSizing::resetRecoveryCapacityperFloorArea() {
    getImpl<detail::WaterHeaterSizing_Impl>()->resetRecoveryCapacityperFloorArea();
  }

  boost::optional<double> WaterHeaterSizing::numberofUnits() const {
    return getImpl<detail::WaterHeaterSizing_Impl>()->numberofUnits();
  }

  bool WaterHeaterSizing::setNumberofUnits(double numberofUnits) {
    return getImpl<detail::WaterHeaterSizing_Impl>()->setNumberofUnits(numberofUnits);
  }

  void WaterHeaterSizing::resetNumberofUnits() {
    getImpl<detail::WaterHeaterSizing_Impl>()->resetNumberofUnits();
  }

  boost::optional<double> WaterHeaterSizing::storageCapacityperUnit() const {
    return getImpl<detail::WaterHeaterSizing_Impl>()->storageCapacityperUnit();
  }

  bool WaterHeaterSizing::setStorageCapacityperUnit(double storageCapacityperUnit) {
    return getImpl<detail::WaterHeaterSizing_Impl>()->setStorageCapacityperUnit(storageCapacityperUnit);
  }

  void WaterHeaterSizing::resetStorageCapacityperUnit() {
    getImpl<detail::WaterHeaterSizing_Impl>()->resetStorageCapacityperUnit();
  }

  boost::optional<double> WaterHeaterSizing::recoveryCapacityPerUnit() const {
    return getImpl<detail::WaterHeaterSizing_Impl>()->recoveryCapacityPerUnit();
  }

  bool WaterHeaterSizing::setRecoveryCapacityPerUnit(double recoveryCapacityPerUnit) {
    return getImpl<detail::WaterHeaterSizing_Impl>()->setRecoveryCapacityPerUnit(recoveryCapacityPerUnit);
  }

  void WaterHeaterSizing::resetRecoveryCapacityPerUnit() {
    getImpl<detail::WaterHeaterSizing_Impl>()->resetRecoveryCapacityPerUnit();
  }

  boost::optional<double> WaterHeaterSizing::storageCapacityperCollectorArea() const {
    return getImpl<detail::WaterHeaterSizing_Impl>()->storageCapacityperCollectorArea();
  }

  bool WaterHeaterSizing::setStorageCapacityperCollectorArea(double storageCapacityperCollectorArea) {
    return getImpl<detail::WaterHeaterSizing_Impl>()->setStorageCapacityperCollectorArea(storageCapacityperCollectorArea);
  }

  void WaterHeaterSizing::resetStorageCapacityperCollectorArea() {
    getImpl<detail::WaterHeaterSizing_Impl>()->resetStorageCapacityperCollectorArea();
  }

  boost::optional<double> WaterHeaterSizing::heightAspectRatio() const {
    return getImpl<detail::WaterHeaterSizing_Impl>()->heightAspectRatio();
  }

  bool WaterHeaterSizing::setHeightAspectRatio(double heightAspectRatio) {
    return getImpl<detail::WaterHeaterSizing_Impl>()->setHeightAspectRatio(heightAspectRatio);
  }

  void WaterHeaterSizing::resetHeightAspectRatio() {
    getImpl<detail::WaterHeaterSizing_Impl>()->resetHeightAspectRatio();
  }

  namespace detail {

    boost::optional<std::string> WaterHeaterSizing_Impl::designMode() const {
      return getString(WaterHeater_SizingFields::DesignMode, true);
    }

    bool WaterHeaterSizing_Impl::setDesignMode(const std::string& designMode) {
      bool result = setString(WaterHeater_SizingFields::DesignMode, designMode);
      return result;
    }

    void WaterHeaterSizing_Impl::resetDesignMode() {
      bool result = setString(WaterHeater_SizingFields::DesignMode, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WaterHeaterSizing_Impl::timeStorageCanMeetPeakDraw() const {
      return getDouble(WaterHeater_SizingFields::TimeStorageCanMeetPeakDraw, true);
    }

    bool WaterHeaterSizing_Impl::setTimeStorageCanMeetPeakDraw(double timeStorageCanMeetPeakDraw) {
      bool result = setDouble(WaterHeater_SizingFields::TimeStorageCanMeetPeakDraw, timeStorageCanMeetPeakDraw);
      return result;
    }

    void WaterHeaterSizing_Impl::resetTimeStorageCanMeetPeakDraw() {
      bool result = setString(WaterHeater_SizingFields::TimeStorageCanMeetPeakDraw, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WaterHeaterSizing_Impl::timeforTankRecovery() const {
      return getDouble(WaterHeater_SizingFields::TimeforTankRecovery, true);
    }

    bool WaterHeaterSizing_Impl::setTimeforTankRecovery(double timeforTankRecovery) {
      bool result = setDouble(WaterHeater_SizingFields::TimeforTankRecovery, timeforTankRecovery);
      return result;
    }

    void WaterHeaterSizing_Impl::resetTimeforTankRecovery() {
      bool result = setString(WaterHeater_SizingFields::TimeforTankRecovery, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WaterHeaterSizing_Impl::nominalTankVolumeforAutosizingPlantConnections() const {
      return getDouble(WaterHeater_SizingFields::NominalTankVolumeforAutosizingPlantConnections, true);
    }

    bool WaterHeaterSizing_Impl::setNominalTankVolumeforAutosizingPlantConnections(double nominalTankVolumeforAutosizingPlantConnections) {
      bool result =
        setDouble(WaterHeater_SizingFields::NominalTankVolumeforAutosizingPlantConnections, nominalTankVolumeforAutosizingPlantConnections);
      OS_ASSERT(result);
      return result;
    }

    void WaterHeaterSizing_Impl::resetNominalTankVolumeforAutosizingPlantConnections() {
      bool result = setString(WaterHeater_SizingFields::NominalTankVolumeforAutosizingPlantConnections, "");
      OS_ASSERT(result);
    }

    boost::optional<int> WaterHeaterSizing_Impl::numberofBedrooms() const {
      return getInt(WaterHeater_SizingFields::NumberofBedrooms, true);
    }

    bool WaterHeaterSizing_Impl::setNumberofBedrooms(int numberofBedrooms) {
      bool result = setInt(WaterHeater_SizingFields::NumberofBedrooms, numberofBedrooms);
      return result;
    }

    void WaterHeaterSizing_Impl::resetNumberofBedrooms() {
      bool result = setString(WaterHeater_SizingFields::NumberofBedrooms, "");
      OS_ASSERT(result);
    }

    boost::optional<int> WaterHeaterSizing_Impl::numberofBathrooms() const {
      return getInt(WaterHeater_SizingFields::NumberofBathrooms, true);
    }

    bool WaterHeaterSizing_Impl::setNumberofBathrooms(int numberofBathrooms) {
      bool result = setInt(WaterHeater_SizingFields::NumberofBathrooms, numberofBathrooms);
      return result;
    }

    void WaterHeaterSizing_Impl::resetNumberofBathrooms() {
      bool result = setString(WaterHeater_SizingFields::NumberofBathrooms, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WaterHeaterSizing_Impl::storageCapacityperPerson() const {
      return getDouble(WaterHeater_SizingFields::StorageCapacityperPerson, true);
    }

    bool WaterHeaterSizing_Impl::setStorageCapacityperPerson(double storageCapacityperPerson) {
      bool result = setDouble(WaterHeater_SizingFields::StorageCapacityperPerson, storageCapacityperPerson);
      return result;
    }

    void WaterHeaterSizing_Impl::resetStorageCapacityperPerson() {
      bool result = setString(WaterHeater_SizingFields::StorageCapacityperPerson, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WaterHeaterSizing_Impl::recoveryCapacityperPerson() const {
      return getDouble(WaterHeater_SizingFields::RecoveryCapacityperPerson, true);
    }

    bool WaterHeaterSizing_Impl::setRecoveryCapacityperPerson(double recoveryCapacityperPerson) {
      bool result = setDouble(WaterHeater_SizingFields::RecoveryCapacityperPerson, recoveryCapacityperPerson);
      return result;
    }

    void WaterHeaterSizing_Impl::resetRecoveryCapacityperPerson() {
      bool result = setString(WaterHeater_SizingFields::RecoveryCapacityperPerson, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WaterHeaterSizing_Impl::storageCapacityperFloorArea() const {
      return getDouble(WaterHeater_SizingFields::StorageCapacityperFloorArea, true);
    }

    bool WaterHeaterSizing_Impl::setStorageCapacityperFloorArea(double storageCapacityperFloorArea) {
      bool result = setDouble(WaterHeater_SizingFields::StorageCapacityperFloorArea, storageCapacityperFloorArea);
      return result;
    }

    void WaterHeaterSizing_Impl::resetStorageCapacityperFloorArea() {
      bool result = setString(WaterHeater_SizingFields::StorageCapacityperFloorArea, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WaterHeaterSizing_Impl::recoveryCapacityperFloorArea() const {
      return getDouble(WaterHeater_SizingFields::RecoveryCapacityperFloorArea, true);
    }

    bool WaterHeaterSizing_Impl::setRecoveryCapacityperFloorArea(double recoveryCapacityperFloorArea) {
      bool result = setDouble(WaterHeater_SizingFields::RecoveryCapacityperFloorArea, recoveryCapacityperFloorArea);
      return result;
    }

    void WaterHeaterSizing_Impl::resetRecoveryCapacityperFloorArea() {
      bool result = setString(WaterHeater_SizingFields::RecoveryCapacityperFloorArea, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WaterHeaterSizing_Impl::numberofUnits() const {
      return getDouble(WaterHeater_SizingFields::NumberofUnits, true);
    }

    bool WaterHeaterSizing_Impl::setNumberofUnits(double numberofUnits) {
      bool result = setDouble(WaterHeater_SizingFields::NumberofUnits, numberofUnits);
      OS_ASSERT(result);
      return result;
    }

    void WaterHeaterSizing_Impl::resetNumberofUnits() {
      bool result = setString(WaterHeater_SizingFields::NumberofUnits, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WaterHeaterSizing_Impl::storageCapacityperUnit() const {
      return getDouble(WaterHeater_SizingFields::StorageCapacityperUnit, true);
    }

    bool WaterHeaterSizing_Impl::setStorageCapacityperUnit(double storageCapacityperUnit) {
      bool result = setDouble(WaterHeater_SizingFields::StorageCapacityperUnit, storageCapacityperUnit);
      return result;
    }

    void WaterHeaterSizing_Impl::resetStorageCapacityperUnit() {
      bool result = setString(WaterHeater_SizingFields::StorageCapacityperUnit, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WaterHeaterSizing_Impl::recoveryCapacityPerUnit() const {
      return getDouble(WaterHeater_SizingFields::RecoveryCapacityPerUnit, true);
    }

    bool WaterHeaterSizing_Impl::setRecoveryCapacityPerUnit(double recoveryCapacityPerUnit) {
      bool result = setDouble(WaterHeater_SizingFields::RecoveryCapacityPerUnit, recoveryCapacityPerUnit);
      return result;
    }

    void WaterHeaterSizing_Impl::resetRecoveryCapacityPerUnit() {
      bool result = setString(WaterHeater_SizingFields::RecoveryCapacityPerUnit, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WaterHeaterSizing_Impl::storageCapacityperCollectorArea() const {
      return getDouble(WaterHeater_SizingFields::StorageCapacityperCollectorArea, true);
    }

    bool WaterHeaterSizing_Impl::setStorageCapacityperCollectorArea(double storageCapacityperCollectorArea) {
      bool result = setDouble(WaterHeater_SizingFields::StorageCapacityperCollectorArea, storageCapacityperCollectorArea);
      return result;
    }

    void WaterHeaterSizing_Impl::resetStorageCapacityperCollectorArea() {
      bool result = setString(WaterHeater_SizingFields::StorageCapacityperCollectorArea, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WaterHeaterSizing_Impl::heightAspectRatio() const {
      return getDouble(WaterHeater_SizingFields::HeightAspectRatio, true);
    }

    bool WaterHeaterSizing_Impl::setHeightAspectRatio(double heightAspectRatio) {
      bool result = setDouble(WaterHeater_SizingFields::HeightAspectRatio, heightAspectRatio);
      return result;
    }

    void WaterHeaterSizing_Impl::resetHeightAspectRatio() {
      bool result = setString(WaterHeater_SizingFields::HeightAspectRatio, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
