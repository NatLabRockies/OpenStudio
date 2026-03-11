/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONTROLLEROUTDOORAIR_IMPL_HPP
#define EPMODEL_CONTROLLEROUTDOORAIR_IMPL_HPP

#include "ParentObject/ParentObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

class ControllerMechanicalVentilation;
class AirLoopHVACOutdoorAirSystem;

namespace detail {

class EPMODEL_API ControllerOutdoorAir_Impl : public ParentObject_Impl
{
 public:
  using ParentObject_Impl::ParentObject_Impl;
  virtual ~ControllerOutdoorAir_Impl() override = default;

  boost::optional<openstudio::epmodel::ControllerMechanicalVentilation> optionalControllerMechanicalVentilation() const;
  openstudio::epmodel::ControllerMechanicalVentilation controllerMechanicalVentilation() const;
  bool setControllerMechanicalVentilation(const openstudio::epmodel::ControllerMechanicalVentilation& controllerMechanicalVentilation);
  boost::optional<openstudio::epmodel::AirLoopHVACOutdoorAirSystem> airLoopHVACOutdoorAirSystem() const;

  void doCanonicalize(LoadContext& context) override;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
