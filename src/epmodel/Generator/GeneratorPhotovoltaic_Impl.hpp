/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORPHOTOVOLTAIC_IMPL_HPP
#define EPMODEL_GENERATORPHOTOVOLTAIC_IMPL_HPP

#include "ModelObject/ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API GeneratorPhotovoltaic_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~GeneratorPhotovoltaic_Impl() override = default;

      std::string heatTransferIntegrationMode() const;
      bool isHeatTransferIntegrationModeDefaulted() const;
      bool setHeatTransferIntegrationMode(const std::string& heatTransferIntegrationMode);
      void resetHeatTransferIntegrationMode();

      double numberOfModulesInParallel() const;
      bool isNumberOfModulesInParallelDefaulted() const;
      bool setNumberOfModulesInParallel(double numberOfModulesInParallel);
      void resetNumberOfModulesInParallel();

      double numberOfModulesInSeries() const;
      bool isNumberOfModulesInSeriesDefaulted() const;
      bool setNumberOfModulesInSeries(double numberOfModulesInSeries);
      void resetNumberOfModulesInSeries();

      std::vector<std::string> heatTransferIntegrationModeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
