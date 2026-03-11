/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILSYSTEMCOOLINGDX_HPP
#define EPMODEL_COILSYSTEMCOOLINGDX_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CoilSystemCoolingDX_Impl;
}

class EPMODEL_API CoilSystemCoolingDX : public ModelObject
{
 public:
  explicit CoilSystemCoolingDX(const Model& model);

  virtual ~CoilSystemCoolingDX() override = default;
  CoilSystemCoolingDX(const CoilSystemCoolingDX& other) = default;
  CoilSystemCoolingDX(CoilSystemCoolingDX&& other) = default;
  CoilSystemCoolingDX& operator=(const CoilSystemCoolingDX&) = default;
  CoilSystemCoolingDX& operator=(CoilSystemCoolingDX&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> coolingCoilObjectTypeValues();
  static std::vector<std::string> dehumidificationControlTypeValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to CoilSystem:Cooling:DX scalar fields.
  // - Field Mapping: Availability Schedule Name, *Node Name fields, and Cooling Coil Name are relationship-like fields and intentionally excluded.
  // - TODO(parity): Add relationship APIs after scalar saturation without changing scalar signatures.
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

 protected:
  using ImplType = detail::CoilSystemCoolingDX_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CoilSystemCoolingDX(std::shared_ptr<detail::CoilSystemCoolingDX_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
