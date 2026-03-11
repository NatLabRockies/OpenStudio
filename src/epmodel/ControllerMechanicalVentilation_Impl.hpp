/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONTROLLERMECHANICALVENTILATION_IMPL_HPP
#define EPMODEL_CONTROLLERMECHANICALVENTILATION_IMPL_HPP

#include "ModelObject_Impl.hpp"
#include "DesignSpecificationOutdoorAirSpaceList.hpp"

#include <utility>
#include <vector>

namespace openstudio {
namespace epmodel {

class ControllerOutdoorAir;
class ControllerMechanicalVentilation;
class Model;
class ModelObject;
class ThermalZone;

namespace detail {

class EPMODEL_API ControllerMechanicalVentilation_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~ControllerMechanicalVentilation_Impl() override = default;

  bool demandControlledVentilation() const;
  bool setDemandControlledVentilation(bool value);

  std::string systemOutdoorAirMethod() const;
  bool setSystemOutdoorAirMethod(const std::string& value);

  boost::optional<openstudio::epmodel::ControllerOutdoorAir> controllerOutdoorAir() const;
  std::vector<std::pair<openstudio::epmodel::ThermalZone, openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList>> zoneOutdoorAirEntries() const;
  void clearZoneOutdoorAirEntries();
  bool addZoneOutdoorAirEntry(const openstudio::epmodel::ThermalZone& zone,
                              const openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList& dsoaSpaceList);

  void doCanonicalize(LoadContext& context) override;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
