/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SOLARCOLLECTORPERFORMANCEPHOTOVOLTAICTHERMALSIMPLE_HPP
#define EPMODEL_SOLARCOLLECTORPERFORMANCEPHOTOVOLTAICTHERMALSIMPLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class SolarCollectorPerformancePhotovoltaicThermalSimple_Impl;
}

class EPMODEL_API SolarCollectorPerformancePhotovoltaicThermalSimple : public ModelObject
{
 public:
  explicit SolarCollectorPerformancePhotovoltaicThermalSimple(const Model& model);

  virtual ~SolarCollectorPerformancePhotovoltaicThermalSimple() override = default;
  SolarCollectorPerformancePhotovoltaicThermalSimple(const SolarCollectorPerformancePhotovoltaicThermalSimple& other) = default;
  SolarCollectorPerformancePhotovoltaicThermalSimple(SolarCollectorPerformancePhotovoltaicThermalSimple&& other) = default;
  SolarCollectorPerformancePhotovoltaicThermalSimple& operator=(const SolarCollectorPerformancePhotovoltaicThermalSimple&) = default;
  SolarCollectorPerformancePhotovoltaicThermalSimple& operator=(SolarCollectorPerformancePhotovoltaicThermalSimple&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> thermalConversionEfficiencyInputModeTypeValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::SolarCollectorPerformancePhotovoltaicThermalSimple scalar accessor names/signatures.
  // - Field Mapping: Scalar APIs map directly to E+ SolarCollectorPerformance:PhotovoltaicThermal:Simple fields.
  // - ForwardTranslator evidence: ForwardTranslateSolarCollectorPerformancePhotovoltaicThermalSimple.cpp writes these scalar getters
  //   to Name, FractionofSurfaceAreawithActiveThermalCollector, ThermalConversionEfficiencyInputModeType,
  //   ValueforThermalConversionEfficiencyifFixed, and FrontSurfaceEmittance.
  // - Field Mapping: ThermalConversionEfficiencyScheduleName remains excluded from epmodel scalar API as a relationship field.
  // - TODO(parity): Add schedule relationship APIs incrementally without changing these scalar signatures.
  double fractionOfSurfaceAreaWithActiveThermalCollector() const;
  std::string thermalConversionEfficiencyInputModeType() const;
  boost::optional<double> thermalConversionEfficiency() const;
  double frontSurfaceEmittance() const;
  bool isFrontSurfaceEmittanceDefaulted() const;

  bool setFractionOfSurfaceAreaWithActiveThermalCollector(double fractionofSurfaceAreawithActiveThermalCollector);
  bool setThermalConversionEfficiency(double valueforThermalConversionEfficiencyifFixed);
  void resetThermalConversionEfficiency();
  bool setFrontSurfaceEmittance(double frontSurfaceEmittance);
  void resetFrontSurfaceEmittance();

 protected:
  using ImplType = detail::SolarCollectorPerformancePhotovoltaicThermalSimple_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit SolarCollectorPerformancePhotovoltaicThermalSimple(
    std::shared_ptr<detail::SolarCollectorPerformancePhotovoltaicThermalSimple_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
