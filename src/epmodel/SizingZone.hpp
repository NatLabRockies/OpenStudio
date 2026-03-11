/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SIZINGZONE_HPP
#define EPMODEL_SIZINGZONE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;
class ThermalZone;

namespace detail {
class SizingZone_Impl;
}

class EPMODEL_API SizingZone : public ModelObject
{
 public:
  explicit SizingZone(const Model& model, const ThermalZone& thermalZone);

  virtual ~SizingZone() override = default;
  SizingZone(const SizingZone& other) = default;
  SizingZone(SizingZone&& other) = default;
  SizingZone& operator=(const SizingZone&) = default;
  SizingZone& operator=(SizingZone&&) = default;

  static IddObjectType iddObjectType();

  ThermalZone thermalZone() const;

 protected:
  using ImplType = detail::SizingZone_Impl;

  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;
  friend class openstudio::epmodel::Model;

  explicit SizingZone(std::shared_ptr<detail::SizingZone_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
