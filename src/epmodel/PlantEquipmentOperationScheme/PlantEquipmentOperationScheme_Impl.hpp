/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONSCHEME_IMPL_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONSCHEME_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
class IdfObject;

namespace detail {
  class WorkspaceObject_Impl;
}

namespace epmodel {
  class PlantLoop;

  namespace detail {

    class Model_Impl;

    class EPMODEL_API PlantEquipmentOperationScheme_Impl : public ModelObject_Impl
    {
     public:
      PlantEquipmentOperationScheme_Impl(const openstudio::IdfObject& idfObject, Model_Impl* model, bool keepHandle);
      PlantEquipmentOperationScheme_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle);
      PlantEquipmentOperationScheme_Impl(const PlantEquipmentOperationScheme_Impl& other, Model_Impl* model, bool keepHandle);
      virtual ~PlantEquipmentOperationScheme_Impl() override = default;

      virtual boost::optional<openstudio::epmodel::PlantLoop> plantLoop() const;
    };

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio

#endif
