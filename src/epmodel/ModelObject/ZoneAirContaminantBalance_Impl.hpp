/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_ZONEAIRCONTAMINANTBALANCE_IMPL_HPP
#define EPMODEL_ZONEAIRCONTAMINANTBALANCE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneAirContaminantBalance_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneAirContaminantBalance_Impl() override = default;

      bool carbonDioxideConcentration() const;
      bool isCarbonDioxideConcentrationDefaulted() const;
      bool setCarbonDioxideConcentration(bool carbonDioxideConcentration);
      void resetCarbonDioxideConcentration();

      bool genericContaminantConcentration() const;
      bool isGenericContaminantConcentrationDefaulted() const;
      bool setGenericContaminantConcentration(bool genericContaminantConcentration);
      void resetGenericContaminantConcentration();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
