/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ELECTRICLOADCENTERINVERTERSIMPLE_HPP
#define EPMODEL_ELECTRICLOADCENTERINVERTERSIMPLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject/ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ElectricLoadCenterInverterSimple_Impl;
}

class EPMODEL_API ElectricLoadCenterInverterSimple : public ModelObject
{
 public:
  explicit ElectricLoadCenterInverterSimple(const Model& model);

  virtual ~ElectricLoadCenterInverterSimple() override = default;
  ElectricLoadCenterInverterSimple(const ElectricLoadCenterInverterSimple& other) = default;
  ElectricLoadCenterInverterSimple(ElectricLoadCenterInverterSimple&& other) = default;
  ElectricLoadCenterInverterSimple& operator=(const ElectricLoadCenterInverterSimple&) = default;
  ElectricLoadCenterInverterSimple& operator=(ElectricLoadCenterInverterSimple&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserves existing openstudio::model scalar accessor names/signatures for counterpart parity.
  // - Field Mapping: radiativeFraction <-> ElectricLoadCenter:Inverter:Simple "Radiative Fraction".
  // - Field Mapping: inverterEfficiency <-> ElectricLoadCenter:Inverter:Simple "Inverter Efficiency".
  // - Field Mapping: Availability Schedule Name and Zone Name are relationship-like link fields and are excluded.
  // - ForwardTranslator evidence: ForwardTranslateElectricLoadCenterInverterSimple maps these exact scalar APIs to
  //   matching EnergyPlus fields.
  // - TODO(parity): add relationship APIs incrementally without changing preserved scalar signatures.
  boost::optional<double> radiativeFraction() const;
  bool setRadiativeFraction(double radiativeFraction);
  void resetRadiativeFraction();

  boost::optional<double> inverterEfficiency() const;
  bool setInverterEfficiency(double inverterEfficiency);
  void resetInverterEfficiency();

 protected:
  using ImplType = detail::ElectricLoadCenterInverterSimple_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ElectricLoadCenterInverterSimple(std::shared_ptr<detail::ElectricLoadCenterInverterSimple_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
