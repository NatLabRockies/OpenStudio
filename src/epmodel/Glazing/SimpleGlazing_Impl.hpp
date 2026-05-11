/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SIMPLEGLAZING_IMPL_HPP
#define EPMODEL_SIMPLEGLAZING_IMPL_HPP

#include "EPModelAPI.hpp"
#include "Material/Material_Impl.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SimpleGlazing_Impl : public Material_Impl
    {
     public:
      using Material_Impl::Material_Impl;
      virtual ~SimpleGlazing_Impl() override = default;

      double uFactor() const;
      bool setUFactor(double uFactor);

      double solarHeatGainCoefficient() const;
      bool setSolarHeatGainCoefficient(double solarHeatGainCoefficient);

      boost::optional<double> visibleTransmittance() const;
      bool setVisibleTransmittance(boost::optional<double> visibleTransmittance);
      void resetVisibleTransmittance();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_SIMPLEGLAZING_IMPL_HPP
