/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORRELATIVEHUMIDITY_IMPL_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORRELATIVEHUMIDITY_IMPL_HPP

#include "ModelObject/ModelObject_Impl.hpp"

namespace openstudio {
class IdfObject;

namespace detail {
  class WorkspaceObject_Impl;
}

namespace epmodel {

  namespace detail {

    class Model_Impl;

    class EPMODEL_API PlantEquipmentOperationOutdoorRelativeHumidity_Impl : public ModelObject_Impl
    {
     public:
      PlantEquipmentOperationOutdoorRelativeHumidity_Impl(const openstudio::IdfObject& idfObject, Model_Impl* model, bool keepHandle);
      PlantEquipmentOperationOutdoorRelativeHumidity_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle);
      PlantEquipmentOperationOutdoorRelativeHumidity_Impl(const PlantEquipmentOperationOutdoorRelativeHumidity_Impl& other, Model_Impl* model,
                                                          bool keepHandle);
      virtual ~PlantEquipmentOperationOutdoorRelativeHumidity_Impl() override = default;

      double maximumUpperLimit() const;
      double minimumLowerLimit() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORRELATIVEHUMIDITY_IMPL_HPP
