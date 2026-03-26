/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WATERTOAIRCOMPONENT_IMPL_HPP
#define EPMODEL_WATERTOAIRCOMPONENT_IMPL_HPP

#include "HVACComponent/HVACComponent_Impl.hpp"
#include "ModelObject/Branch.hpp"
#include "ModelObject.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API WaterToAirComponent_Impl : public HVACComponent_Impl
{
 public:
  using HVACComponent_Impl::HVACComponent_Impl;
  virtual ~WaterToAirComponent_Impl() override = default;

  virtual unsigned airInletPort() const = 0;
  virtual unsigned airOutletPort() const = 0;

  virtual boost::optional<ModelObject> airInletModelObject() const;
  virtual boost::optional<ModelObject> airOutletModelObject() const;

  virtual unsigned waterInletPort() const = 0;
  virtual unsigned waterOutletPort() const = 0;

  virtual boost::optional<ModelObject> waterInletModelObject() const;
  virtual boost::optional<ModelObject> waterOutletModelObject() const;

  bool addToNode(Node& node) override;
  bool addToSplitter(Splitter& splitter) override;

  std::vector<IdfObject> remove() override;

  void disconnectWaterSide();
  void disconnectAirSide();
  void disconnect() override;

  bool removeFromAirLoopHVAC();
  bool removeFromPlantLoop();

 private:
  bool insertOnBranch(Node& node, const Branch& branch, unsigned inletPort, unsigned outletPort);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
