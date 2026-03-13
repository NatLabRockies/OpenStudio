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
      bool setFractionOfSurfaceAreaWithActiveThermalCollector(double fractionofSurfaceAreawithActiveThermalCollector);

      std::string thermalConversionEfficiencyInputModeType() const;
      std::vector<std::string> thermalConversionEfficiencyInputModeTypeValues() const;
      boost::optional<double> thermalConversionEfficiency() const;
      bool setThermalConversionEfficiency(double valueforThermalConversionEfficiencyifFixed);
      void resetThermalConversionEfficiency();

      double frontSurfaceEmittance() const;
      bool isFrontSurfaceEmittanceDefaulted() const;
      bool setFrontSurfaceEmittance(double frontSurfaceEmittance);
      void resetFrontSurfaceEmittance();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
