/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FAULTMODELFOULINGBOILER_IMPL_HPP
#define EPMODEL_FAULTMODELFOULINGBOILER_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API FaultModelFoulingBoiler_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~FaultModelFoulingBoiler_Impl() override = default;

      std::string boilerObjectType() const;
      bool setBoilerObjectType(const std::string& boilerObjectType);
      std::vector<std::string> boilerObjectTypeValues() const;

      double foulingFactor() const;
      bool isFoulingFactorDefaulted() const;
      bool setFoulingFactor(double foulingFactor);
      void resetFoulingFactor();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
