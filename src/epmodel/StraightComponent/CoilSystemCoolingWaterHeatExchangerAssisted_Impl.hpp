/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILSYSTEMCOOLINGWATERHEATEXCHANGERASSISTED_IMPL_HPP
#define EPMODEL_COILSYSTEMCOOLINGWATERHEATEXCHANGERASSISTED_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <utility>
#include <vector>

namespace openstudio {
namespace epmodel {
  class AirToAirComponent;
  class ModelObject;
  class Node;
  class WaterToAirComponent;
  namespace detail {

    class EPMODEL_API CoilSystemCoolingWaterHeatExchangerAssisted_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~CoilSystemCoolingWaterHeatExchangerAssisted_Impl() override = default;

      bool addToNode(Node& node) override;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      boost::optional<ModelObject> inletModelObject() const override;
      boost::optional<ModelObject> outletModelObject() const override;
      std::vector<ModelObject> children() const override;
      std::vector<IdfObject> remove() override;
      void disconnect() override;
      void doCanonicalize(LoadContext& context) override;

      // EnergyPlus stores branch boundary nodes on the enclosed heat exchanger,
      // not on the zero-port coil-system wrapper.
      bool setAirInletNode(const Node& node);
      bool setAirOutletNode(const Node& node);
      void syncStorageSetpointManager();

      AirToAirComponent heatExchanger() const;
      bool setHeatExchanger(const AirToAirComponent& heatExchanger);

      WaterToAirComponent coolingCoil() const;
      bool setCoolingCoil(const WaterToAirComponent& coolingCoil);

      std::vector<std::string> heatExchangerObjectTypeValues() const;
      std::vector<std::string> coolingCoilObjectTypeValues() const;

      // Cooling-coil targets are tracked directly; the heat-exchanger side stays as schema-valid name/object-type storage.
      /** @name Heat exchanger object type */
      //@{
      std::string heatExchangerObjectType() const;
      bool setHeatExchangerObjectType(const std::string& heatExchangerObjectType);
      //@}

      /** @name Cooling coil object type */
      //@{
      std::string coolingCoilObjectType() const;
      bool setCoolingCoilObjectType(const std::string& coolingCoilObjectType);
      //@}

     private:
      bool reconcileContainedAirPath(const boost::optional<Node>& inletNode, const boost::optional<Node>& outletNode);
      boost::optional<std::pair<Node, Node>> branchBoundaryNodes() const;
      void removeStorageSetpointManager();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
