/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORDRYBULB_IMPL_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORDRYBULB_IMPL_HPP

#include "ModelObject/ModelObject_Impl.hpp"

namespace openstudio {
class IdfObject;

namespace detail {
  class WorkspaceObject_Impl;
}

namespace epmodel {

  namespace detail {

    class Model_Impl;

    class EPMODEL_API PlantEquipmentOperationOutdoorDryBulb_Impl : public ModelObject_Impl
    {
     public:
      PlantEquipmentOperationOutdoorDryBulb_Impl(const openstudio::IdfObject& idfObject, Model_Impl* model, bool keepHandle);
      PlantEquipmentOperationOutdoorDryBulb_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle);
      PlantEquipmentOperationOutdoorDryBulb_Impl(const PlantEquipmentOperationOutdoorDryBulb_Impl& other, Model_Impl* model, bool keepHandle);
      virtual ~PlantEquipmentOperationOutdoorDryBulb_Impl() override = default;

      double maximumUpperLimit() const;
      double minimumLowerLimit() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORDRYBULB_IMPL_HPP
