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

  namespace detail {

    class EPMODEL_API WaterHeaterSizing_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~WaterHeaterSizing_Impl() override = default;

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
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_WATERHEATERSIZING_IMPL_HPP
