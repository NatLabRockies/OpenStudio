/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ROOMAIRSETTINGSONENODEDISPLACEMENTVENTILATION_IMPL_HPP
#define EPMODEL_ROOMAIRSETTINGSONENODEDISPLACEMENTVENTILATION_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API RoomAirSettingsOneNodeDisplacementVentilation_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~RoomAirSettingsOneNodeDisplacementVentilation_Impl() override = default;

      boost::optional<double> fractionofConvectiveInternalLoadsAddedtoFloorAir() const;
      bool setFractionofConvectiveInternalLoadsAddedtoFloorAir(double fractionofConvectiveInternalLoadsAddedtoFloorAir);
      void resetFractionofConvectiveInternalLoadsAddedtoFloorAir();

      boost::optional<double> fractionofInfiltrationInternalLoadsAddedtoFloorAir() const;
      bool setFractionofInfiltrationInternalLoadsAddedtoFloorAir(double fractionofInfiltrationInternalLoadsAddedtoFloorAir);
      void resetFractionofInfiltrationInternalLoadsAddedtoFloorAir();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
