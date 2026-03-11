/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FANVARIABLEVOLUME_HPP
#define EPMODEL_FANVARIABLEVOLUME_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class FanVariableVolume_Impl;
}

class EPMODEL_API FanVariableVolume : public StraightComponent
{
 public:
  explicit FanVariableVolume(const Model& model);

  virtual ~FanVariableVolume() override = default;
  FanVariableVolume(const FanVariableVolume& other) = default;
  FanVariableVolume(FanVariableVolume&& other) = default;
  FanVariableVolume& operator=(const FanVariableVolume&) = default;
  FanVariableVolume& operator=(FanVariableVolume&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> fanPowerMinimumFlowRateInputMethodValues();

  /** \deprecated */
  static std::vector<std::string> validFanPowerMinimumFlowRateInputMethodValues();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model::FanVariableVolume scalar accessor names/signatures for counterpart parity.
  // - Field Mapping: Scalar APIs map directly to E+ Fan:VariableVolume fields.
  // - ForwardTranslator evidence: ForwardTranslateFanVariableVolume.cpp writes these scalar fields directly to Fan:VariableVolume.
  // - Field Mapping: maximumFlowRate preserves autosize/reset semantics through the "autosize" token.
  // - TODO(parity): Relationship fields (availability schedule, node links) remain excluded from scalar scaffold coverage.
  double fanTotalEfficiency() const;
  bool isFanTotalEfficiencyDefaulted() const;
  bool setFanTotalEfficiency(double fanTotalEfficiency);
  void resetFanTotalEfficiency();

  double fanEfficiency() const;
  bool isFanEfficiencyDefaulted() const;
  bool setFanEfficiency(double fanTotalEfficiency);
  void resetFanEfficiency();

  double pressureRise() const;
  bool setPressureRise(double pressureRise);

  boost::optional<double> maximumFlowRate() const;
  bool isMaximumFlowRateAutosized() const;
  bool setMaximumFlowRate(double maximumFlowRate);
  void resetMaximumFlowRate();
  void autosizeMaximumFlowRate();

  std::string fanPowerMinimumFlowRateInputMethod() const;
  bool isFanPowerMinimumFlowRateInputMethodDefaulted() const;
  bool setFanPowerMinimumFlowRateInputMethod(const std::string& fanPowerMinimumFlowRateInputMethod);
  void resetFanPowerMinimumFlowRateInputMethod();

  double fanPowerMinimumFlowFraction() const;
  bool isFanPowerMinimumFlowFractionDefaulted() const;
  bool setFanPowerMinimumFlowFraction(double fanPowerMinimumFlowFraction);
  void resetFanPowerMinimumFlowFraction();

  boost::optional<double> fanPowerMinimumAirFlowRate() const;
  bool setFanPowerMinimumAirFlowRate(double fanPowerMinimumAirFlowRate);
  void resetFanPowerMinimumAirFlowRate();

  double motorEfficiency() const;
  bool isMotorEfficiencyDefaulted() const;
  bool setMotorEfficiency(double motorEfficiency);
  void resetMotorEfficiency();

  double motorInAirstreamFraction() const;
  bool isMotorInAirstreamFractionDefaulted() const;
  bool setMotorInAirstreamFraction(double motorInAirstreamFraction);
  void resetMotorInAirstreamFraction();

  boost::optional<double> fanPowerCoefficient1() const;
  bool setFanPowerCoefficient1(double fanPowerCoefficient1);
  void resetFanPowerCoefficient1();

  boost::optional<double> fanPowerCoefficient2() const;
  bool setFanPowerCoefficient2(double fanPowerCoefficient2);
  void resetFanPowerCoefficient2();

  boost::optional<double> fanPowerCoefficient3() const;
  bool setFanPowerCoefficient3(double fanPowerCoefficient3);
  void resetFanPowerCoefficient3();

  boost::optional<double> fanPowerCoefficient4() const;
  bool setFanPowerCoefficient4(double fanPowerCoefficient4);
  void resetFanPowerCoefficient4();

  boost::optional<double> fanPowerCoefficient5() const;
  bool setFanPowerCoefficient5(double fanPowerCoefficient5);
  void resetFanPowerCoefficient5();

  std::string endUseSubcategory() const;
  bool isEndUseSubcategoryDefaulted() const;
  bool setEndUseSubcategory(const std::string& endUseSubcategory);
  void resetEndUseSubcategory();

 protected:
  using ImplType = detail::FanVariableVolume_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit FanVariableVolume(std::shared_ptr<detail::FanVariableVolume_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
