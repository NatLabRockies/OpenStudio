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
  class WaterToWaterComponent;
  class WaterHeaterMixed;
  class WaterHeaterStratified;
  class ThermalStorageChilledWaterStratified;

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
    // - Field Mapping: Water Heater Name preserves the canonical owning WaterToWaterComponent relationship via the same object-list field.
    // - Evidence: `src/model/WaterHeaterSizing.hpp`, `src/model/WaterHeaterSizing.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateWaterHeaterSizing.cpp`.

    /** @name Field accessors */
    //@{
    WaterToWaterComponent waterHeater() const;

    boost::optional<std::string> designMode() const;
    bool setDesignMode(const std::string& designMode);
    void resetDesignMode();

    boost::optional<double> timeStorageCanMeetPeakDraw() const;
    bool setTimeStorageCanMeetPeakDraw(double timeStorageCanMeetPeakDraw);
    void resetTimeStorageCanMeetPeakDraw();

    boost::optional<double> timeforTankRecovery() const;
    bool setTimeforTankRecovery(double timeforTankRecovery);
    void resetTimeforTankRecovery();

    boost::optional<double> nominalTankVolumeforAutosizingPlantConnections() const;
    bool setNominalTankVolumeforAutosizingPlantConnections(double nominalTankVolumeforAutosizingPlantConnections);
    void resetNominalTankVolumeforAutosizingPlantConnections();

    boost::optional<int> numberofBedrooms() const;
    bool setNumberofBedrooms(int numberofBedrooms);
    void resetNumberofBedrooms();

    boost::optional<int> numberofBathrooms() const;
    bool setNumberofBathrooms(int numberofBathrooms);
    void resetNumberofBathrooms();

    boost::optional<double> storageCapacityperPerson() const;
    bool setStorageCapacityperPerson(double storageCapacityperPerson);
    void resetStorageCapacityperPerson();

    boost::optional<double> recoveryCapacityperPerson() const;
    bool setRecoveryCapacityperPerson(double recoveryCapacityperPerson);
    void resetRecoveryCapacityperPerson();

    boost::optional<double> storageCapacityperFloorArea() const;
    bool setStorageCapacityperFloorArea(double storageCapacityperFloorArea);
    void resetStorageCapacityperFloorArea();

    boost::optional<double> recoveryCapacityperFloorArea() const;
    bool setRecoveryCapacityperFloorArea(double recoveryCapacityperFloorArea);
    void resetRecoveryCapacityperFloorArea();

    boost::optional<double> numberofUnits() const;
    bool setNumberofUnits(double numberofUnits);
    void resetNumberofUnits();

    boost::optional<double> storageCapacityperUnit() const;
    bool setStorageCapacityperUnit(double storageCapacityperUnit);
    void resetStorageCapacityperUnit();

    boost::optional<double> recoveryCapacityPerUnit() const;
    bool setRecoveryCapacityPerUnit(double recoveryCapacityPerUnit);
    void resetRecoveryCapacityPerUnit();

    boost::optional<double> storageCapacityperCollectorArea() const;
    bool setStorageCapacityperCollectorArea(double storageCapacityperCollectorArea);
    void resetStorageCapacityperCollectorArea();

    boost::optional<double> heightAspectRatio() const;
    bool setHeightAspectRatio(double heightAspectRatio);
    void resetHeightAspectRatio();
    //@}

   protected:
    using ImplType = detail::WaterHeaterSizing_Impl;

    friend class WaterHeaterMixed;
    friend class WaterHeaterStratified;
    friend class ThermalStorageChilledWaterStratified;
    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit WaterHeaterSizing(const WaterToWaterComponent& waterHeater);
    bool setWaterHeater(const WaterToWaterComponent& waterHeater);
    explicit WaterHeaterSizing(std::shared_ptr<detail::WaterHeaterSizing_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_WATERHEATERSIZING_HPP
