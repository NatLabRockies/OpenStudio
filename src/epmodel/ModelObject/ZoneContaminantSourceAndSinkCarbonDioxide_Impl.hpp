/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONECONTAMINANTSOURCEANDSINKCARBONDIOXIDE_IMPL_HPP
#define EPMODEL_ZONECONTAMINANTSOURCEANDSINKCARBONDIOXIDE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneContaminantSourceAndSinkCarbonDioxide_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneContaminantSourceAndSinkCarbonDioxide_Impl() override = default;

      boost::optional<double> designGenerationRate() const;
      bool setDesignGenerationRate(double designGenerationRate);
      void resetDesignGenerationRate();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
