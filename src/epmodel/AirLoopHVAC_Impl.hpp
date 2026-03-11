/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVAC_IMPL_HPP
#define EPMODEL_AIRLOOPHVAC_IMPL_HPP

#include "Loop_Impl.hpp"
#include "BranchList.hpp"
#include "HVACComponent.hpp"
#include "ModelObject.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
  class AirLoopHVACReturnPath;
  class AirLoopHVACSupplyPath;
  class AirLoopHVACOutdoorAirSystem;
  class ThermalZone;
  class AirLoopHVACZoneMixer;
  class AirLoopHVACZoneSplitter;
  class Node;
}  // namespace epmodel
namespace epmodel {
  namespace detail {
    struct LoadContext;

    class EPMODEL_API AirLoopHVAC_Impl : public Loop_Impl
    {
     public:
      using Loop_Impl::Loop_Impl;
      virtual ~AirLoopHVAC_Impl() override = default;
      openstudio::epmodel::Node supplyInletNode() const override;
      openstudio::epmodel::Node supplyOutletNode() const override;
      std::vector<openstudio::epmodel::Node> supplyOutletNodes() const override;
      openstudio::epmodel::Node demandInletNode() const override;
      openstudio::epmodel::Node demandOutletNode() const override;
      std::vector<openstudio::epmodel::Node> demandInletNodes() const override;
      openstudio::epmodel::BranchList branchList() const;
      std::vector<openstudio::epmodel::ModelObject> supplyComponents(const openstudio::epmodel::HVACComponent& inletComp,
                                                                     const openstudio::epmodel::HVACComponent& outletComp,
                                                                     openstudio::IddObjectType type) const override;
      std::vector<openstudio::epmodel::ModelObject> supplyComponents(openstudio::IddObjectType type) const override;
      std::vector<openstudio::epmodel::ModelObject> demandComponents(const openstudio::epmodel::HVACComponent& inletComp,
                                                                     const openstudio::epmodel::HVACComponent& outletComp,
                                                                     openstudio::IddObjectType type) const override;
      std::vector<openstudio::epmodel::ModelObject> demandComponents(openstudio::IddObjectType type) const override;
      boost::optional<openstudio::epmodel::AirLoopHVACOutdoorAirSystem> airLoopHVACOutdoorAirSystem() const;
      std::vector<openstudio::epmodel::ThermalZone> thermalZones() const;
      void syncControllerMechanicalVentilationZoneOutdoorAirEntries();

      openstudio::epmodel::AirLoopHVACReturnPath airLoopHVACReturnPath() const;
      openstudio::epmodel::AirLoopHVACSupplyPath airLoopHVACSupplyPath() const;
      openstudio::epmodel::AirLoopHVACZoneSplitter zoneSplitter() const;
      openstudio::epmodel::AirLoopHVACZoneMixer zoneMixer() const;
      openstudio::epmodel::Node demandBranchNode() const;
      void doCanonicalize(LoadContext& context) override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
