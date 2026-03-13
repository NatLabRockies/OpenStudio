/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEAIRHEATBALANCEALGORITHM_IMPL_HPP
#define EPMODEL_ZONEAIRHEATBALANCEALGORITHM_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneAirHeatBalanceAlgorithm_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneAirHeatBalanceAlgorithm_Impl() override = default;

      std::string algorithm() const;
      bool isAlgorithmDefaulted() const;
      bool setAlgorithm(const std::string& algorithm);
      void resetAlgorithm();

      bool doSpaceHeatBalanceforSizing() const;
      bool isDoSpaceHeatBalanceforSizingDefaulted() const;
      bool setDoSpaceHeatBalanceforSizing(bool doSpaceHeatBalanceforSizing);
      void resetDoSpaceHeatBalanceforSizing();

      bool doSpaceHeatBalanceforSimulation() const;
      bool isDoSpaceHeatBalanceforSimulationDefaulted() const;
      bool setDoSpaceHeatBalanceforSimulation(bool doSpaceHeatBalanceforSimulation);
      void resetDoSpaceHeatBalanceforSimulation();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_ZONEAIRHEATBALANCEALGORITHM_IMPL_HPP
