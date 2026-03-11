/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACOUTDOORAIRSYSTEMEQUIPMENTLIST_IMPL_HPP
#define EPMODEL_AIRLOOPHVACOUTDOORAIRSYSTEMEQUIPMENTLIST_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {
struct LoadContext;

class EPMODEL_API AirLoopHVACOutdoorAirSystemEquipmentList_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~AirLoopHVACOutdoorAirSystemEquipmentList_Impl() override = default;

  std::vector<openstudio::epmodel::ModelObject> equipment() const;
  bool addEquipment(const openstudio::epmodel::ModelObject& component);
  bool removeEquipment(const openstudio::epmodel::ModelObject& component);
  void doCanonicalize(LoadContext& context) override;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
