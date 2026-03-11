/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FANPERFORMANCENIGHTVENTILATION_HPP
#define EPMODEL_FANPERFORMANCENIGHTVENTILATION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class FanPerformanceNightVentilation_Impl;
}

class EPMODEL_API FanPerformanceNightVentilation : public ModelObject
{
 public:
  explicit FanPerformanceNightVentilation(const Model& model);

  virtual ~FanPerformanceNightVentilation() override = default;
  FanPerformanceNightVentilation(const FanPerformanceNightVentilation& other) = default;
  FanPerformanceNightVentilation(FanPerformanceNightVentilation&& other) = default;
  FanPerformanceNightVentilation& operator=(const FanPerformanceNightVentilation&) = default;
  FanPerformanceNightVentilation& operator=(FanPerformanceNightVentilation&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to FanPerformance:NightVentilation scalar fields.
  // - Field Mapping: Fan Name remains excluded as an object-list relationship field.
  // - TODO(parity): Add relationship APIs after scalar saturation without changing scalar signatures.
  double fanTotalEfficiency() const;
  bool setFanTotalEfficiency(double fanTotalEfficiency);

  double pressureRise() const;
  bool setPressureRise(double pressureRise);

  boost::optional<double> maximumFlowRate() const;
  bool isMaximumFlowRateAutosized() const;
  bool setMaximumFlowRate(double maximumFlowRate);
  void resetMaximumFlowRate();
  void autosizeMaximumFlowRate();

  double motorEfficiency() const;
  bool setMotorEfficiency(double motorEfficiency);

  double motorinAirstreamFraction() const;
  bool isMotorinAirstreamFractionDefaulted() const;
  bool setMotorinAirstreamFraction(double motorinAirstreamFraction);
  void resetMotorinAirstreamFraction();

 protected:
  using ImplType = detail::FanPerformanceNightVentilation_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit FanPerformanceNightVentilation(std::shared_ptr<detail::FanPerformanceNightVentilation_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
