/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONHEATINGLOAD_IMPL_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONHEATINGLOAD_IMPL_HPP

#include "PlantEquipmentOperationScheme/PlantEquipmentOperationScheme_Impl.hpp"

namespace openstudio {
class IdfObject;

namespace detail {
  class WorkspaceObject_Impl;
}

namespace epmodel {

  namespace detail {

    class Model_Impl;

    class EPMODEL_API PlantEquipmentOperationHeatingLoad_Impl : public PlantEquipmentOperationScheme_Impl
    {
     public:
      PlantEquipmentOperationHeatingLoad_Impl(const openstudio::IdfObject& idfObject, Model_Impl* model, bool keepHandle);
      PlantEquipmentOperationHeatingLoad_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle);
      PlantEquipmentOperationHeatingLoad_Impl(const PlantEquipmentOperationHeatingLoad_Impl& other, Model_Impl* model, bool keepHandle);
      virtual ~PlantEquipmentOperationHeatingLoad_Impl() override = default;

      double maximumUpperLimit() const;
      double minimumLowerLimit() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_PLANTEQUIPMENTOPERATIONHEATINGLOAD_IMPL_HPP
