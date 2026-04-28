/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONECONTAMINANTSOURCEANDSINKGENERICDEPOSITIONRATESINK_IMPL_HPP
#define EPMODEL_ZONECONTAMINANTSOURCEANDSINKGENERICDEPOSITIONRATESINK_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneContaminantSourceAndSinkGenericDepositionRateSink_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneContaminantSourceAndSinkGenericDepositionRateSink_Impl() override = default;

      boost::optional<double> depositionRate() const;
      bool setDepositionRate(double depositionRate);
      void resetDepositionRate();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
