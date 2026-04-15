/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WATERHEATERSIZING_IMPL_HPP
#define EPMODEL_WATERHEATERSIZING_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>

#include <string>

namespace openstudio {
namespace epmodel {

  class WaterToWaterComponent;

  namespace detail {

    class EPMODEL_API WaterHeaterSizing_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~WaterHeaterSizing_Impl() override = default;

      WaterToWaterComponent waterHeater() const;
      bool setWaterHeater(const WaterToWaterComponent& waterHeater);

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
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_WATERHEATERSIZING_IMPL_HPP
