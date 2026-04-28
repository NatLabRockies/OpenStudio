/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FAULTMODELFOULINGCOOLINGTOWER_IMPL_HPP
#define EPMODEL_FAULTMODELFOULINGCOOLINGTOWER_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API FaultModelFoulingCoolingTower_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~FaultModelFoulingCoolingTower_Impl() override = default;

      std::vector<std::string> coolingTowerObjectTypeValues() const;

      std::string coolingTowerObjectType() const;
      bool setCoolingTowerObjectType(const std::string& coolingTowerObjectType);

      boost::optional<double> referenceUAReductionFactor() const;
      bool setReferenceUAReductionFactor(double referenceUAReductionFactor);
      void resetReferenceUAReductionFactor();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
