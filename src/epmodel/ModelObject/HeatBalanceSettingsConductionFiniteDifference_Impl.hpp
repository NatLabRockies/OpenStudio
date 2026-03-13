/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATBALANCESETTINGSCONDUCTIONFINITEDIFFERENCE_IMPL_HPP
#define EPMODEL_HEATBALANCESETTINGSCONDUCTIONFINITEDIFFERENCE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API HeatBalanceSettingsConductionFiniteDifference_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~HeatBalanceSettingsConductionFiniteDifference_Impl() override = default;

      std::string differenceScheme() const;
      bool isDifferenceSchemeDefaulted() const;
      bool setDifferenceScheme(const std::string& differenceScheme);
      void resetDifferenceScheme();

      double spaceDiscretizationConstant() const;
      bool isSpaceDiscretizationConstantDefaulted() const;
      bool setSpaceDiscretizationConstant(double spaceDiscretizationConstant);
      void resetSpaceDiscretizationConstant();

      double relaxationFactor() const;
      bool isRelaxationFactorDefaulted() const;
      bool setRelaxationFactor(double relaxationFactor);
      void resetRelaxationFactor();

      double insideFaceSurfaceTemperatureConvergenceCriteria() const;
      bool isInsideFaceSurfaceTemperatureConvergenceCriteriaDefaulted() const;
      bool setInsideFaceSurfaceTemperatureConvergenceCriteria(double insideFaceSurfaceTemperatureConvergenceCriteria);
      void resetInsideFaceSurfaceTemperatureConvergenceCriteria();

     private:
      std::vector<std::string> differenceSchemeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
