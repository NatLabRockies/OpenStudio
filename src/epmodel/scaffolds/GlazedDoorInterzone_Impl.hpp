/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GLAZEDDOORINTERZONE_IMPL_HPP
#define EPMODEL_GLAZEDDOORINTERZONE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API GlazedDoorInterzone_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~GlazedDoorInterzone_Impl() override = default;

      double multiplier() const;
      bool isMultiplierDefaulted() const;
      bool setMultiplier(double multiplier);
      void resetMultiplier();

      boost::optional<double> startingXCoordinate() const;
      bool setStartingXCoordinate(double startingXCoordinate);
      void resetStartingXCoordinate();

      boost::optional<double> startingZCoordinate() const;
      bool setStartingZCoordinate(double startingZCoordinate);
      void resetStartingZCoordinate();

      boost::optional<double> length() const;
      bool setLength(double length);
      void resetLength();

      boost::optional<double> height() const;
      bool setHeight(double height);
      void resetHeight();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
