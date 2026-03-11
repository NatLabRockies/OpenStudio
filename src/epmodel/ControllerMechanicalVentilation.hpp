/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONTROLLERMECHANICALVENTILATION_HPP
#define EPMODEL_CONTROLLERMECHANICALVENTILATION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;
class ControllerOutdoorAir;

namespace detail {
class ControllerMechanicalVentilation_Impl;
}

class EPMODEL_API ControllerMechanicalVentilation : public ModelObject
{
 public:
  explicit ControllerMechanicalVentilation(const Model& model);

  virtual ~ControllerMechanicalVentilation() override = default;
  ControllerMechanicalVentilation(const ControllerMechanicalVentilation& other) = default;
  ControllerMechanicalVentilation(ControllerMechanicalVentilation&& other) = default;
  ControllerMechanicalVentilation& operator=(const ControllerMechanicalVentilation&) = default;
  ControllerMechanicalVentilation& operator=(ControllerMechanicalVentilation&&) = default;

  static IddObjectType iddObjectType();

  bool demandControlledVentilation() const;
  bool setDemandControlledVentilation(bool value);

  std::string systemOutdoorAirMethod() const;
  bool setSystemOutdoorAirMethod(const std::string& value);

  boost::optional<ControllerOutdoorAir> controllerOutdoorAir() const;

 protected:
  using ImplType = detail::ControllerMechanicalVentilation_Impl;

  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;
  friend class openstudio::epmodel::Model;

  explicit ControllerMechanicalVentilation(std::shared_ptr<detail::ControllerMechanicalVentilation_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
