/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILSYSTEMCOOLINGDXHEATEXCHANGERASSISTED_IMPL_HPP
#define EPMODEL_COILSYSTEMCOOLINGDXHEATEXCHANGERASSISTED_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  class AirToAirComponent;
  class ModelObject;
  class Node;
  class StraightComponent;

  namespace detail {

    class EPMODEL_API CoilSystemCoolingDXHeatExchangerAssisted_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~CoilSystemCoolingDXHeatExchangerAssisted_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      boost::optional<ModelObject> inletModelObject() const override;
      boost::optional<ModelObject> outletModelObject() const override;
      bool addToNode(Node& node) override;
      std::vector<ModelObject> children() const override;
      std::vector<openstudio::IdfObject> remove() override;
      void disconnect() override;
      void doCanonicalize(LoadContext& context) override;

      // The EnergyPlus wrapper has no node fields. Its enclosing unitary system
      // supplies the two boundary nodes, while this object owns the two internal
      // connectors between the heat exchanger and DX coil.
      bool setAirInletNode(const Node& node);
      bool setAirOutletNode(const Node& node);

      AirToAirComponent heatExchanger() const;
      bool setHeatExchanger(const AirToAirComponent& heatExchanger);

      StraightComponent coolingCoil() const;
      bool setCoolingCoil(const StraightComponent& coolingCoil);

      std::vector<std::string> heatExchangerObjectTypeValues() const;
      std::string heatExchangerObjectType() const;
      bool setHeatExchangerObjectType(const std::string& heatExchangerObjectType);

      std::vector<std::string> coolingCoilObjectTypeValues() const;
      std::string coolingCoilObjectType() const;
      bool setCoolingCoilObjectType(const std::string& coolingCoilObjectType);

     private:
      bool reconcileContainedAirPath(const boost::optional<Node>& inletNode, const boost::optional<Node>& outletNode);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
