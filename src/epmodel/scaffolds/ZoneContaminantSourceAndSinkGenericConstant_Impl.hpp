/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONECONTAMINANTSOURCEANDSINKGENERICCONSTANT_IMPL_HPP
#define EPMODEL_ZONECONTAMINANTSOURCEANDSINKGENERICCONSTANT_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneContaminantSourceAndSinkGenericConstant_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneContaminantSourceAndSinkGenericConstant_Impl() override = default;

      boost::optional<double> designGenerationRate() const;
      bool setDesignGenerationRate(double designGenerationRate);
      void resetDesignGenerationRate();

      boost::optional<double> designRemovalCoefficient() const;
      bool setDesignRemovalCoefficient(double designRemovalCoefficient);
      void resetDesignRemovalCoefficient();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
