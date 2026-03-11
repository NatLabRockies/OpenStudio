/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATBALANCESETTINGSCONDUCTIONFINITEDIFFERENCE_HPP
#define EPMODEL_HEATBALANCESETTINGSCONDUCTIONFINITEDIFFERENCE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class HeatBalanceSettingsConductionFiniteDifference_Impl;
}

class EPMODEL_API HeatBalanceSettingsConductionFiniteDifference : public ModelObject
{
 public:
  explicit HeatBalanceSettingsConductionFiniteDifference(const Model& model);

  virtual ~HeatBalanceSettingsConductionFiniteDifference() override = default;
  HeatBalanceSettingsConductionFiniteDifference(const HeatBalanceSettingsConductionFiniteDifference& other) = default;
  HeatBalanceSettingsConductionFiniteDifference(HeatBalanceSettingsConductionFiniteDifference&& other) = default;
  HeatBalanceSettingsConductionFiniteDifference& operator=(const HeatBalanceSettingsConductionFiniteDifference&) = default;
  HeatBalanceSettingsConductionFiniteDifference& operator=(HeatBalanceSettingsConductionFiniteDifference&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> differenceSchemeValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: differenceScheme, spaceDiscretizationConstant, relaxationFactor, and
  //   insideFaceSurfaceTemperatureConvergenceCriteria map directly to the corresponding
  //   EnergyPlus HeatBalanceSettings:ConductionFiniteDifference scalar fields.
  // - TODO(parity): Keep relationship APIs out of scope for this scalar-only scaffold pass.
  std::string differenceScheme() const;
  bool isDifferenceSchemeDefaulted() const;
  double spaceDiscretizationConstant() const;
  bool isSpaceDiscretizationConstantDefaulted() const;
  double relaxationFactor() const;
  bool isRelaxationFactorDefaulted() const;
  double insideFaceSurfaceTemperatureConvergenceCriteria() const;
  bool isInsideFaceSurfaceTemperatureConvergenceCriteriaDefaulted() const;

  bool setDifferenceScheme(const std::string& differenceScheme);
  void resetDifferenceScheme();
  bool setSpaceDiscretizationConstant(double spaceDiscretizationConstant);
  void resetSpaceDiscretizationConstant();
  bool setRelaxationFactor(double relaxationFactor);
  void resetRelaxationFactor();
  bool setInsideFaceSurfaceTemperatureConvergenceCriteria(double insideFaceSurfaceTemperatureConvergenceCriteria);
  void resetInsideFaceSurfaceTemperatureConvergenceCriteria();

 protected:
  using ImplType = detail::HeatBalanceSettingsConductionFiniteDifference_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit HeatBalanceSettingsConductionFiniteDifference(std::shared_ptr<detail::HeatBalanceSettingsConductionFiniteDifference_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
