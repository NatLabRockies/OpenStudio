/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DEHUMIDIFIERDESICCANTSYSTEM_IMPL_HPP
#define EPMODEL_DEHUMIDIFIERDESICCANTSYSTEM_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API DehumidifierDesiccantSystem_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~DehumidifierDesiccantSystem_Impl() override = default;

  std::string desiccantHeatExchangerObjectType() const;
  bool setDesiccantHeatExchangerObjectType(const std::string& desiccantHeatExchangerObjectType);

  std::string regenerationAirFanObjectType() const;
  bool setRegenerationAirFanObjectType(const std::string& regenerationAirFanObjectType);

  std::string regenerationAirFanPlacement() const;
  bool isRegenerationAirFanPlacementDefaulted() const;
  bool setRegenerationAirFanPlacement(const std::string& regenerationAirFanPlacement);
  void resetRegenerationAirFanPlacement();

  boost::optional<std::string> regenerationAirHeaterObjectType() const;
  bool setRegenerationAirHeaterObjectType(const std::string& regenerationAirHeaterObjectType);
  void resetRegenerationAirHeaterObjectType();

  double regenerationInletAirSetpointTemperature() const;
  bool isRegenerationInletAirSetpointTemperatureDefaulted() const;
  bool setRegenerationInletAirSetpointTemperature(double regenerationInletAirSetpointTemperature);
  void resetRegenerationInletAirSetpointTemperature();

  boost::optional<std::string> companionCoolingCoilObjectType() const;
  bool setCompanionCoolingCoilObjectType(const std::string& companionCoolingCoilObjectType);
  void resetCompanionCoolingCoilObjectType();

  bool companionCoolingCoilUpstreamofDehumidifierProcessInlet() const;
  bool isCompanionCoolingCoilUpstreamofDehumidifierProcessInletDefaulted() const;
  bool setCompanionCoolingCoilUpstreamofDehumidifierProcessInlet(bool companionCoolingCoilUpstreamofDehumidifierProcessInlet);
  void resetCompanionCoolingCoilUpstreamofDehumidifierProcessInlet();

  bool companionCoilRegenerationAirHeating() const;
  bool isCompanionCoilRegenerationAirHeatingDefaulted() const;
  bool setCompanionCoilRegenerationAirHeating(bool companionCoilRegenerationAirHeating);
  void resetCompanionCoilRegenerationAirHeating();

  boost::optional<double> exhaustFanMaximumFlowRate() const;
  bool setExhaustFanMaximumFlowRate(double exhaustFanMaximumFlowRate);
  void resetExhaustFanMaximumFlowRate();

  boost::optional<double> exhaustFanMaximumPower() const;
  bool setExhaustFanMaximumPower(double exhaustFanMaximumPower);
  void resetExhaustFanMaximumPower();

  std::vector<std::string> desiccantHeatExchangerObjectTypeValues() const;
  std::vector<std::string> regenerationAirFanObjectTypeValues() const;
  std::vector<std::string> regenerationAirFanPlacementValues() const;
  std::vector<std::string> regenerationAirHeaterObjectTypeValues() const;
  std::vector<std::string> companionCoolingCoilObjectTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
