/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_WALLUNDERGROUND_IMPL_HPP
#define EPMODEL_WALLUNDERGROUND_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API WallUnderground_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~WallUnderground_Impl() override = default;

      boost::optional<double> azimuthAngle() const;
      bool setAzimuthAngle(double azimuthAngle);
      void resetAzimuthAngle();

      double tiltAngle() const;
      bool isTiltAngleDefaulted() const;
      bool setTiltAngle(double tiltAngle);
      void resetTiltAngle();

      boost::optional<double> startingXCoordinate() const;
      bool setStartingXCoordinate(double startingXCoordinate);
      void resetStartingXCoordinate();

      boost::optional<double> startingYCoordinate() const;
      bool setStartingYCoordinate(double startingYCoordinate);
      void resetStartingYCoordinate();

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
