/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONECONTAMINANTSOURCEANDSINKGENERICCUTOFFMODEL_IMPL_HPP
#define EPMODEL_ZONECONTAMINANTSOURCEANDSINKGENERICCUTOFFMODEL_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneContaminantSourceAndSinkGenericCutoffModel_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneContaminantSourceAndSinkGenericCutoffModel_Impl() override = default;

      boost::optional<double> designGenerationRateCoefficient() const;
      bool setDesignGenerationRateCoefficient(double designGenerationRateCoefficient);
      void resetDesignGenerationRateCoefficient();

      boost::optional<double> cutoffGenericContaminantAtWhichEmissionCeases() const;
      bool setCutoffGenericContaminantAtWhichEmissionCeases(double cutoffGenericContaminantAtWhichEmissionCeases);
      void resetCutoffGenericContaminantAtWhichEmissionCeases();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
