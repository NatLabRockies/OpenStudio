/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORWETBULBDIFFERENCE_IMPL_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORWETBULBDIFFERENCE_IMPL_HPP

#include "ModelObject/ModelObject_Impl.hpp"

namespace openstudio {
class IdfObject;

namespace detail {
  class WorkspaceObject_Impl;
}

namespace epmodel {

  namespace detail {

    class Model_Impl;

    class EPMODEL_API PlantEquipmentOperationOutdoorWetBulbDifference_Impl : public ModelObject_Impl
    {
     public:
      PlantEquipmentOperationOutdoorWetBulbDifference_Impl(const openstudio::IdfObject& idfObject, Model_Impl* model, bool keepHandle);
      PlantEquipmentOperationOutdoorWetBulbDifference_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle);
      PlantEquipmentOperationOutdoorWetBulbDifference_Impl(const PlantEquipmentOperationOutdoorWetBulbDifference_Impl& other, Model_Impl* model,
                                                           bool keepHandle);
      virtual ~PlantEquipmentOperationOutdoorWetBulbDifference_Impl() override = default;

      double maximumUpperLimit() const;
      double minimumLowerLimit() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORWETBULBDIFFERENCE_IMPL_HPP
