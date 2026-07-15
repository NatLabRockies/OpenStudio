/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONCOOLINGLOAD_IMPL_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONCOOLINGLOAD_IMPL_HPP

#include "PlantEquipmentOperationScheme/PlantEquipmentOperationRangeBasedScheme_Impl.hpp"

namespace openstudio {
class IdfObject;

namespace detail {
  class WorkspaceObject_Impl;
}

namespace epmodel {

  namespace detail {

    class Model_Impl;

    class EPMODEL_API PlantEquipmentOperationCoolingLoad_Impl : public PlantEquipmentOperationRangeBasedScheme_Impl
    {
     public:
      PlantEquipmentOperationCoolingLoad_Impl(const openstudio::IdfObject& idfObject, Model_Impl* model, bool keepHandle);
      PlantEquipmentOperationCoolingLoad_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle);
      PlantEquipmentOperationCoolingLoad_Impl(const PlantEquipmentOperationCoolingLoad_Impl& other, Model_Impl* model, bool keepHandle);
      virtual ~PlantEquipmentOperationCoolingLoad_Impl() override = default;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_PLANTEQUIPMENTOPERATIONCOOLINGLOAD_IMPL_HPP
