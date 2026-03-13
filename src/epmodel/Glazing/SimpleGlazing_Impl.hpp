/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SIMPLEGLAZING_IMPL_HPP
#define EPMODEL_SIMPLEGLAZING_IMPL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SimpleGlazing_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
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
