/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SIZINGZONE_IMPL_HPP
#define EPMODEL_SIZINGZONE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

class ThermalZone;
class ModelObject;
class DesignSpecificationOutdoorAir;
class DesignSpecificationOutdoorAirSpaceList;

namespace detail {

class EPMODEL_API SizingZone_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~SizingZone_Impl() override = default;

  boost::optional<openstudio::epmodel::ThermalZone> optionalThermalZone() const;
  openstudio::epmodel::ThermalZone thermalZone() const;

  boost::optional<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList> designSpecificationOutdoorAirSpaceList() const;
  bool setDesignSpecificationOutdoorAirSpaceList(
    const openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList& designSpecificationOutdoorAirSpaceList);

  void doCanonicalize(LoadContext& context) override;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
