/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ELECTRICLOADCENTERINVERTERPVWATTS_HPP
#define EPMODEL_ELECTRICLOADCENTERINVERTERPVWATTS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject/ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ElectricLoadCenterInverterPVWatts_Impl;
}

class EPMODEL_API ElectricLoadCenterInverterPVWatts : public ModelObject
{
 public:
  explicit ElectricLoadCenterInverterPVWatts(const Model& model);

  virtual ~ElectricLoadCenterInverterPVWatts() override = default;
  ElectricLoadCenterInverterPVWatts(const ElectricLoadCenterInverterPVWatts& other) = default;
  ElectricLoadCenterInverterPVWatts(ElectricLoadCenterInverterPVWatts&& other) = default;
  ElectricLoadCenterInverterPVWatts& operator=(const ElectricLoadCenterInverterPVWatts&) = default;
  ElectricLoadCenterInverterPVWatts& operator=(ElectricLoadCenterInverterPVWatts&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserves existing openstudio::model accessor names/signatures for counterpart parity.
  // - Field Mapping: dcToACSizeRatio <-> ElectricLoadCenter:Inverter:PVWatts "DC to AC Size Ratio".
  // - Field Mapping: inverterEfficiency <-> ElectricLoadCenter:Inverter:PVWatts "Inverter Efficiency".
  // - ForwardTranslator evidence: ForwardTranslateElectricLoadCenterInverterPVWatts maps these exact model APIs to matching E+ fields.
  // - TODO(parity): add non-scalar APIs incrementally without changing preserved scalar signatures.
  double dcToACSizeRatio() const;
  bool isDCToACSizeRatioDefaulted() const;
  bool setDCToACSizeRatio(double dcToACSizeRatio);
  void resetDCToACSizeRatio();

  double inverterEfficiency() const;
  bool isInverterEfficiencyDefaulted() const;
  bool setInverterEfficiency(double inverterEfficiency);
  void resetInverterEfficiency();

 protected:
  using ImplType = detail::ElectricLoadCenterInverterPVWatts_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ElectricLoadCenterInverterPVWatts(std::shared_ptr<detail::ElectricLoadCenterInverterPVWatts_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
