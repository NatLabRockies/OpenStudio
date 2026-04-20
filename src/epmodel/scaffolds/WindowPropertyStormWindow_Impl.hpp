/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WINDOWPROPERTYSTORMWINDOW_IMPL_HPP
#define EPMODEL_WINDOWPROPERTYSTORMWINDOW_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API WindowPropertyStormWindow_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~WindowPropertyStormWindow_Impl() override = default;

      double distanceBetweenStormGlassLayerandAdjacentGlass() const;
      bool isDistanceBetweenStormGlassLayerandAdjacentGlassDefaulted() const;
      bool setDistanceBetweenStormGlassLayerandAdjacentGlass(double distanceBetweenStormGlassLayerandAdjacentGlass);
      void resetDistanceBetweenStormGlassLayerandAdjacentGlass();

      int monththatStormGlassLayerisPutOn() const;
      bool setMonththatStormGlassLayerisPutOn(int monththatStormGlassLayerisPutOn);

      int dayofMonththatStormGlassLayerisPutOn() const;
      bool setDayofMonththatStormGlassLayerisPutOn(int dayofMonththatStormGlassLayerisPutOn);

      int monththatStormGlassLayerisTakenOff() const;
      bool setMonththatStormGlassLayerisTakenOff(int monththatStormGlassLayerisTakenOff);

      int dayofMonththatStormGlassLayerisTakenOff() const;
      bool setDayofMonththatStormGlassLayerisTakenOff(int dayofMonththatStormGlassLayerisTakenOff);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
