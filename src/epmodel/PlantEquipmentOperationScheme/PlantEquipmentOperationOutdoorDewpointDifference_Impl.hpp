/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORDEWPOINTDIFFERENCE_IMPL_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORDEWPOINTDIFFERENCE_IMPL_HPP

#include "PlantEquipmentOperationScheme/PlantEquipmentOperationScheme_Impl.hpp"

namespace openstudio {
class IdfObject;

namespace detail {
  class WorkspaceObject_Impl;
}

namespace epmodel {

  namespace detail {

    class Model_Impl;

    class EPMODEL_API PlantEquipmentOperationOutdoorDewpointDifference_Impl : public PlantEquipmentOperationScheme_Impl
    {
     public:
      PlantEquipmentOperationOutdoorDewpointDifference_Impl(const openstudio::IdfObject& idfObject, Model_Impl* model, bool keepHandle);
      PlantEquipmentOperationOutdoorDewpointDifference_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model,
                                                            bool keepHandle);
      PlantEquipmentOperationOutdoorDewpointDifference_Impl(const PlantEquipmentOperationOutdoorDewpointDifference_Impl& other, Model_Impl* model,
                                                            bool keepHandle);
      virtual ~PlantEquipmentOperationOutdoorDewpointDifference_Impl() override = default;

      double maximumUpperLimit() const;
      double minimumLowerLimit() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_PLANTEQUIPMENTOPERATIONOUTDOORDEWPOINTDIFFERENCE_IMPL_HPP
