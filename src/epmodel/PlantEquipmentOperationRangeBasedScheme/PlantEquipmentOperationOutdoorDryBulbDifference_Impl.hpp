/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORDRYBULBDIFFERENCE_IMPL_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORDRYBULBDIFFERENCE_IMPL_HPP

#include "ModelObject/ModelObject_Impl.hpp"

namespace openstudio {
class IdfObject;

namespace detail {
  class WorkspaceObject_Impl;
}

namespace epmodel {

  namespace detail {

    class Model_Impl;

    class EPMODEL_API PlantEquipmentOperationOutdoorDryBulbDifference_Impl : public ModelObject_Impl
    {
     public:
      PlantEquipmentOperationOutdoorDryBulbDifference_Impl(const openstudio::IdfObject& idfObject, Model_Impl* model, bool keepHandle);
      PlantEquipmentOperationOutdoorDryBulbDifference_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle);
      PlantEquipmentOperationOutdoorDryBulbDifference_Impl(const PlantEquipmentOperationOutdoorDryBulbDifference_Impl& other, Model_Impl* model,
                                                           bool keepHandle);
      virtual ~PlantEquipmentOperationOutdoorDryBulbDifference_Impl() override = default;

      double maximumUpperLimit() const;
      double minimumLowerLimit() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORDRYBULBDIFFERENCE_IMPL_HPP
