/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORWETBULB_IMPL_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORWETBULB_IMPL_HPP

#include "ModelObject/ModelObject_Impl.hpp"

namespace openstudio {
class IdfObject;

namespace detail {
  class WorkspaceObject_Impl;
}

namespace epmodel {

  namespace detail {

    class Model_Impl;

    class EPMODEL_API PlantEquipmentOperationOutdoorWetBulb_Impl : public ModelObject_Impl
    {
     public:
      PlantEquipmentOperationOutdoorWetBulb_Impl(const openstudio::IdfObject& idfObject, Model_Impl* model, bool keepHandle);
      PlantEquipmentOperationOutdoorWetBulb_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle);
      PlantEquipmentOperationOutdoorWetBulb_Impl(const PlantEquipmentOperationOutdoorWetBulb_Impl& other, Model_Impl* model, bool keepHandle);
      virtual ~PlantEquipmentOperationOutdoorWetBulb_Impl() override = default;

      double maximumUpperLimit() const;
      double minimumLowerLimit() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORWETBULB_IMPL_HPP
