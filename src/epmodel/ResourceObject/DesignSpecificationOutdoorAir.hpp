/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DESIGNSPECIFICATIONOUTDOORAIR_HPP
#define EPMODEL_DESIGNSPECIFICATIONOUTDOORAIR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class DesignSpecificationOutdoorAir_Impl;
}

class EPMODEL_API DesignSpecificationOutdoorAir : public ModelObject
{
 public:
  explicit DesignSpecificationOutdoorAir(const Model& model);

  virtual ~DesignSpecificationOutdoorAir() override = default;
  DesignSpecificationOutdoorAir(const DesignSpecificationOutdoorAir& other) = default;
  DesignSpecificationOutdoorAir(DesignSpecificationOutdoorAir&& other) = default;
  DesignSpecificationOutdoorAir& operator=(const DesignSpecificationOutdoorAir&) = default;
  DesignSpecificationOutdoorAir& operator=(DesignSpecificationOutdoorAir&&) = default;

  static IddObjectType iddObjectType();

  std::string outdoorAirMethod() const;
  bool setOutdoorAirMethod(const std::string& value);

  double outdoorAirFlowperPerson() const;
  bool setOutdoorAirFlowperPerson(double value);

  double outdoorAirFlowperFloorArea() const;
  bool setOutdoorAirFlowperFloorArea(double value);

  double outdoorAirFlowRate() const;
  bool setOutdoorAirFlowRate(double value);

  double outdoorAirFlowAirChangesperHour() const;
  bool setOutdoorAirFlowAirChangesperHour(double value);

 protected:
  using ImplType = detail::DesignSpecificationOutdoorAir_Impl;

  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;
  friend class Model;

  explicit DesignSpecificationOutdoorAir(std::shared_ptr<detail::DesignSpecificationOutdoorAir_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
