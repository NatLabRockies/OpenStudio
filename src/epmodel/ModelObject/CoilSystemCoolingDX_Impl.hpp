/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILSYSTEMCOOLINGDX_IMPL_HPP
#define EPMODEL_COILSYSTEMCOOLINGDX_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
  class AirLoopHVAC;
  class CoilCoolingDXTwoSpeed;
  class ModelObject;
  class Node;
  namespace detail {

    class EPMODEL_API CoilSystemCoolingDX_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~CoilSystemCoolingDX_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      boost::optional<AirLoopHVAC> airLoopHVAC() const override;
      bool addToNode(Node& node) override;
      bool removeFromLoop() override;
      void disconnect() override;
      std::vector<IdfObject> remove() override;

      std::vector<std::string> coolingCoilObjectTypeValues() const;
      std::vector<std::string> dehumidificationControlTypeValues() const;

      std::string coolingCoilObjectType() const;
      bool setCoolingCoilObjectType(const std::string& coolingCoilObjectType);

      std::string dehumidificationControlType() const;
      bool isDehumidificationControlTypeDefaulted() const;
      bool setDehumidificationControlType(const std::string& dehumidificationControlType);
      void resetDehumidificationControlType();

      bool runonSensibleLoad() const;
      bool isRunonSensibleLoadDefaulted() const;
      bool setRunonSensibleLoad(bool runonSensibleLoad);
      void resetRunonSensibleLoad();

      bool runonLatentLoad() const;
      bool isRunonLatentLoadDefaulted() const;
      bool setRunonLatentLoad(bool runonLatentLoad);
      void resetRunonLatentLoad();

      bool useOutdoorAirDXCoolingCoil() const;
      bool isUseOutdoorAirDXCoolingCoilDefaulted() const;
      bool setUseOutdoorAirDXCoolingCoil(bool useOutdoorAirDXCoolingCoil);
      void resetUseOutdoorAirDXCoolingCoil();

      double outdoorAirDXCoolingCoilLeavingMinimumAirTemperature() const;
      bool isOutdoorAirDXCoolingCoilLeavingMinimumAirTemperatureDefaulted() const;
      bool setOutdoorAirDXCoolingCoilLeavingMinimumAirTemperature(double outdoorAirDXCoolingCoilLeavingMinimumAirTemperature);
      void resetOutdoorAirDXCoolingCoilLeavingMinimumAirTemperature();

      boost::optional<ModelObject> coolingCoil() const;
      boost::optional<Node> sensorNode() const;

      bool configureForCoolingCoil(CoilCoolingDXTwoSpeed& coolingCoil);
      bool isCoherentForCoolingCoil(const CoilCoolingDXTwoSpeed& coolingCoil) const;
      bool syncCoolingCoilNodes();

     private:
      void clearTopologyPointers();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
