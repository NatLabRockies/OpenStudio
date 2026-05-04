/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTUSERDEFINED_IMPL_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTUSERDEFINED_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include "ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "Node.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API AirTerminalSingleDuctUserDefined_Impl : public StraightComponent_Impl
{
 public:
  enum class AddToNodeFailureStage
  {
    None,
    AfterADUUpdateBeforeZoneRegistration,
  };

  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~AirTerminalSingleDuctUserDefined_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;
  bool addToNode(Node& node) override;
  bool addToNode(Node& node, AddToNodeFailureStage failureStage);
  bool removeFromLoop() override;
  boost::optional<ZoneHVACAirDistributionUnit> zoneHVACAirDistributionUnit() const;

  int numberofPlantLoopConnections() const;
  bool setNumberofPlantLoopConnections(int numberofPlantLoopConnections);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
