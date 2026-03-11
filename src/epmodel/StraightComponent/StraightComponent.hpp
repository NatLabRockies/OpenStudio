/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_STRAIGHTCOMPONENT_HPP
#define EPMODEL_STRAIGHTCOMPONENT_HPP

#include "HVACComponent/HVACComponent.hpp"
#include "ModelObject.hpp"
#include "Loop/AirLoopHVAC.hpp"

#include <boost/optional.hpp>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
  class StraightComponent_Impl;
}

class EPMODEL_API StraightComponent : public HVACComponent
{
 public:
  virtual ~StraightComponent() override = default;
  StraightComponent() = default;
  StraightComponent(const StraightComponent& other) = default;
  StraightComponent(StraightComponent&& other) = default;
  StraightComponent& operator=(const StraightComponent&) = default;
  StraightComponent& operator=(StraightComponent&&) = default;

  bool removeFromLoop();

  unsigned inletPort() const;
  unsigned outletPort() const;

  boost::optional<ModelObject> inletModelObject() const;
  boost::optional<ModelObject> outletModelObject() const;


 protected:
  friend class Model;
  friend class openstudio::IdfObject;

  using ImplType = detail::StraightComponent_Impl;

  StraightComponent(IddObjectType type, const Model& model, bool fastName = false, bool isTransient = false);
  explicit StraightComponent(std::shared_ptr<detail::StraightComponent_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
