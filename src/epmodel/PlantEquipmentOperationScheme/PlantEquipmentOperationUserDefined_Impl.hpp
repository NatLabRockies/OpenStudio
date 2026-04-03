/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONUSERDEFINED_IMPL_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONUSERDEFINED_IMPL_HPP

#include "PlantEquipmentOperationScheme_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API PlantEquipmentOperationUserDefined_Impl : public PlantEquipmentOperationScheme_Impl
    {
     public:
      using PlantEquipmentOperationScheme_Impl::PlantEquipmentOperationScheme_Impl;
      virtual ~PlantEquipmentOperationUserDefined_Impl() override = default;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
