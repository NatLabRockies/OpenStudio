/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEFUNCTIONALPRESSUREDROP_IMPL_HPP
#define EPMODEL_CURVEFUNCTIONALPRESSUREDROP_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API CurveFunctionalPressureDrop_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~CurveFunctionalPressureDrop_Impl() override = default;

      double diameter() const;
      bool setDiameter(double diameter);

      boost::optional<double> minorLossCoefficient() const;
      bool setMinorLossCoefficient(double minorLossCoefficient);
      void resetMinorLossCoefficient();

      boost::optional<double> length() const;
      bool setLength(double length);
      void resetLength();

      boost::optional<double> roughness() const;
      bool setRoughness(double roughness);
      void resetRoughness();

      boost::optional<double> fixedFrictionFactor() const;
      bool setFixedFrictionFactor(double fixedFrictionFactor);
      void resetFixedFrictionFactor();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
