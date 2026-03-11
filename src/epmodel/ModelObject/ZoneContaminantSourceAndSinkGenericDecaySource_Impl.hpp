/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONECONTAMINANTSOURCEANDSINKGENERICDECAYSOURCE_IMPL_HPP
#define EPMODEL_ZONECONTAMINANTSOURCEANDSINKGENERICDECAYSOURCE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneContaminantSourceAndSinkGenericDecaySource_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneContaminantSourceAndSinkGenericDecaySource_Impl() override = default;

      boost::optional<double> initialEmissionRate() const;
      bool setInitialEmissionRate(double initialEmissionRate);
      void resetInitialEmissionRate();

      boost::optional<double> delayTimeConstant() const;
      bool setDelayTimeConstant(double delayTimeConstant);
      void resetDelayTimeConstant();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
