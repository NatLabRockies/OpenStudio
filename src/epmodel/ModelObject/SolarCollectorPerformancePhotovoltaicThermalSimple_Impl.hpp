/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SOLARCOLLECTORPERFORMANCEPHOTOVOLTAICTHERMALSIMPLE_IMPL_HPP
#define EPMODEL_SOLARCOLLECTORPERFORMANCEPHOTOVOLTAICTHERMALSIMPLE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API SolarCollectorPerformancePhotovoltaicThermalSimple_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~SolarCollectorPerformancePhotovoltaicThermalSimple_Impl() override = default;

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

  std::vector<std::string> thermalConversionEfficiencyInputModeTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
