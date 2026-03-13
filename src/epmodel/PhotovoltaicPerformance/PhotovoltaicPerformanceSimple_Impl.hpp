/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PHOTOVOLTAICPERFORMANCESIMPLE_IMPL_HPP
#define EPMODEL_PHOTOVOLTAICPERFORMANCESIMPLE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API PhotovoltaicPerformanceSimple_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~PhotovoltaicPerformanceSimple_Impl() override = default;

      double fractionOfSurfaceAreaWithActiveSolarCells() const;
      bool isfractionOfSurfaceAreaWithActiveSolarCellsDefaulted() const;
      bool setFractionOfSurfaceAreaWithActiveSolarCells(double fractionOfSurfaceAreaWithActiveSolarCells);
      void resetFractionOfSurfaceAreaWithActiveSolarCells();

      std::string conversionEfficiencyInputMode() const;
      bool setConversionEfficiencyInputMode(const std::string& conversionEfficiencyInputMode);
      std::vector<std::string> conversionEfficiencyInputModeValues() const;

      boost::optional<double> fixedEfficiency() const;
      bool setFixedEfficiency(double fixedEfficiency);
      void resetFixedEfficiency();

     private:
      bool setDefaultFixedEfficiency();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
