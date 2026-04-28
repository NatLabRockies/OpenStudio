/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WATERTOWATERCOMPONENT_IMPL_HPP
#define EPMODEL_WATERTOWATERCOMPONENT_IMPL_HPP

#include "HVACComponent/HVACComponent_Impl.hpp"
#include "ModelObject/Branch.hpp"
#include "ModelObject.hpp"

namespace openstudio {
namespace epmodel {
class Node;
namespace detail {

class EPMODEL_API WaterToWaterComponent_Impl : public HVACComponent_Impl
{
 public:
  using HVACComponent_Impl::HVACComponent_Impl;
  virtual ~WaterToWaterComponent_Impl() override = default;

  virtual unsigned supplyInletPort() const = 0;
  virtual unsigned supplyOutletPort() const = 0;

  virtual boost::optional<ModelObject> supplyInletModelObject() const;
  virtual boost::optional<ModelObject> supplyOutletModelObject() const;

  virtual unsigned demandInletPort() const = 0;
  virtual unsigned demandOutletPort() const = 0;

  virtual boost::optional<ModelObject> demandInletModelObject() const;
  virtual boost::optional<ModelObject> demandOutletModelObject() const;

  bool addToNode(Node& node) override;
  std::vector<IdfObject> remove() override;
  void disconnect() override;

  boost::optional<PlantLoop> plantLoop() const override;
  virtual boost::optional<PlantLoop> secondaryPlantLoop() const;
  bool removeFromPlantLoop();
  virtual bool removeFromSecondaryPlantLoop();

  virtual unsigned tertiaryInletPort() const;
  virtual unsigned tertiaryOutletPort() const;

  boost::optional<ModelObject> tertiaryInletModelObject() const;
  boost::optional<ModelObject> tertiaryOutletModelObject() const;

  virtual boost::optional<PlantLoop> tertiaryPlantLoop() const;
  virtual bool removeFromTertiaryPlantLoop();
  virtual bool addToTertiaryNode(Node& node);

 protected:
  bool shouldRouteDemandSideNodeToTertiary(const Node& node) const;
  bool addToDemandSideTertiaryNode(Node& node);
  bool insertOnBranch(Node& node, const Branch& branch, unsigned inletPort, unsigned outletPort);
  bool removeFromBranch(unsigned inletPort, unsigned outletPort, const boost::optional<PlantLoop>& plantLoop_);

 private:
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
