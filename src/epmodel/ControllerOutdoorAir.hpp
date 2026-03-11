/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONTROLLEROUTDOORAIR_HPP
#define EPMODEL_CONTROLLEROUTDOORAIR_HPP

#include "EPModelAPI.hpp"
#include "ParentObject.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;
class ControllerMechanicalVentilation;
class AirLoopHVACOutdoorAirSystem;

namespace detail {
class ControllerOutdoorAir_Impl;
}

class EPMODEL_API ControllerOutdoorAir : public ParentObject
{
 public:
  explicit ControllerOutdoorAir(const Model& model);

  virtual ~ControllerOutdoorAir() override = default;
  ControllerOutdoorAir(const ControllerOutdoorAir& other) = default;
  ControllerOutdoorAir(ControllerOutdoorAir&& other) = default;
  ControllerOutdoorAir& operator=(const ControllerOutdoorAir&) = default;
  ControllerOutdoorAir& operator=(ControllerOutdoorAir&&) = default;

  static IddObjectType iddObjectType();

  ControllerMechanicalVentilation controllerMechanicalVentilation() const;
  bool setControllerMechanicalVentilation(const ControllerMechanicalVentilation& controllerMechanicalVentilation);

  boost::optional<AirLoopHVACOutdoorAirSystem> airLoopHVACOutdoorAirSystem() const;

 protected:
  using ImplType = detail::ControllerOutdoorAir_Impl;

  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;
  friend class openstudio::epmodel::Model;

  explicit ControllerOutdoorAir(std::shared_ptr<detail::ControllerOutdoorAir_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
