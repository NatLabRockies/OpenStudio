/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WATERHEATERSIZING_HPP
#define EPMODEL_WATERHEATERSIZING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <boost/optional.hpp>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {

namespace epmodel {

  class Model;

  namespace detail {
    class WaterHeaterSizing_Impl;
  }

  class EPMODEL_API WaterHeaterSizing : public ModelObject
  {
   public:
    explicit WaterHeaterSizing(const Model& model);

    virtual ~WaterHeaterSizing() override = default;
    WaterHeaterSizing(const WaterHeaterSizing& other) = default;
    WaterHeaterSizing(WaterHeaterSizing&& other) = default;
    WaterHeaterSizing& operator=(const WaterHeaterSizing&) = default;
    WaterHeaterSizing& operator=(WaterHeaterSizing&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> designModeValues();

    // Schema Alignment Notes:
    // - API: Preserve the openstudio::model scalar accessor names/signatures for this model-counterpart class.
    // - Field Mapping: All declared scalars map directly to the EnergyPlus WaterHeater:Sizing fields referenced in ForwardTranslateWaterHeaterSizing.cpp.
    // - Field Mapping: Water Heater Name is a relationship-like object-list field and remains intentionally excluded from this scalar-only scaffold.
    // - TODO(parity): Add the non-scalar Water Heater linkage API once the translator/relationships are wired into epmodel.
    boost::optional<std::string> designMode() const;

    boost::optional<double> timeStorageCanMeetPeakDraw() const;
    boost::optional<double> timeforTankRecovery() const;
    boost::optional<double> nominalTankVolumeforAutosizingPlantConnections() const;
    boost::optional<int> numberofBedrooms() const;
    boost::optional<int> numberofBathrooms() const;
    boost::optional<double> storageCapacityperPerson() const;
    boost::optional<double> recoveryCapacityperPerson() const;
    boost::optional<double> storageCapacityperFloorArea() const;
    boost::optional<double> recoveryCapacityperFloorArea() const;
    boost::optional<double> numberofUnits() const;
    boost::optional<double> storageCapacityperUnit() const;
    boost::optional<double> recoveryCapacityPerUnit() const;
    boost::optional<double> storageCapacityperCollectorArea() const;
    boost::optional<double> heightAspectRatio() const;

    bool setDesignMode(const std::string& designMode);
    void resetDesignMode();

    bool setTimeStorageCanMeetPeakDraw(double timeStorageCanMeetPeakDraw);
    void resetTimeStorageCanMeetPeakDraw();

    bool setTimeforTankRecovery(double timeforTankRecovery);
    void resetTimeforTankRecovery();

    bool setNominalTankVolumeforAutosizingPlantConnections(double nominalTankVolumeforAutosizingPlantConnections);
    void resetNominalTankVolumeforAutosizingPlantConnections();

    bool setNumberofBedrooms(int numberofBedrooms);
    void resetNumberofBedrooms();

    bool setNumberofBathrooms(int numberofBathrooms);
    void resetNumberofBathrooms();

    bool setStorageCapacityperPerson(double storageCapacityperPerson);
    void resetStorageCapacityperPerson();

    bool setRecoveryCapacityperPerson(double recoveryCapacityperPerson);
    void resetRecoveryCapacityperPerson();

    bool setStorageCapacityperFloorArea(double storageCapacityperFloorArea);
    void resetStorageCapacityperFloorArea();

    bool setRecoveryCapacityperFloorArea(double recoveryCapacityperFloorArea);
    void resetRecoveryCapacityperFloorArea();

    bool setNumberofUnits(double numberofUnits);
    void resetNumberofUnits();

    bool setStorageCapacityperUnit(double storageCapacityperUnit);
    void resetStorageCapacityperUnit();

    bool setRecoveryCapacityPerUnit(double recoveryCapacityPerUnit);
    void resetRecoveryCapacityPerUnit();

    bool setStorageCapacityperCollectorArea(double storageCapacityperCollectorArea);
    void resetStorageCapacityperCollectorArea();

    bool setHeightAspectRatio(double heightAspectRatio);
    void resetHeightAspectRatio();

   protected:
    using ImplType = detail::WaterHeaterSizing_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit WaterHeaterSizing(std::shared_ptr<detail::WaterHeaterSizing_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_WATERHEATERSIZING_HPP
