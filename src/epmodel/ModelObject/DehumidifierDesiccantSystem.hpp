/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DEHUMIDIFIERDESICCANTSYSTEM_HPP
#define EPMODEL_DEHUMIDIFIERDESICCANTSYSTEM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class DehumidifierDesiccantSystem_Impl;
}

class EPMODEL_API DehumidifierDesiccantSystem : public ModelObject
{
 public:
  explicit DehumidifierDesiccantSystem(const Model& model);

  virtual ~DehumidifierDesiccantSystem() override = default;
  DehumidifierDesiccantSystem(const DehumidifierDesiccantSystem& other) = default;
  DehumidifierDesiccantSystem(DehumidifierDesiccantSystem&& other) = default;
  DehumidifierDesiccantSystem& operator=(const DehumidifierDesiccantSystem&) = default;
  DehumidifierDesiccantSystem& operator=(DehumidifierDesiccantSystem&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> desiccantHeatExchangerObjectTypeValues();
  static std::vector<std::string> regenerationAirFanObjectTypeValues();
  static std::vector<std::string> regenerationAirFanPlacementValues();
  static std::vector<std::string> regenerationAirHeaterObjectTypeValues();
  static std::vector<std::string> companionCoolingCoilObjectTypeValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to Dehumidifier:Desiccant:System numeric/choice fields.
  // - Field Mapping: Availability schedule, node names, and linked object-list name fields remain excluded as relationship fields.
  // - TODO(parity): Add relationship APIs after scalar saturation without changing scalar signatures.
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

 protected:
  using ImplType = detail::DehumidifierDesiccantSystem_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit DehumidifierDesiccantSystem(std::shared_ptr<detail::DehumidifierDesiccantSystem_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
