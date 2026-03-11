/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WALLEXTERIOR_IMPL_HPP
#define EPMODEL_WALLEXTERIOR_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API WallExterior_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~WallExterior_Impl() override = default;

      boost::optional<double> azimuthAngle() const;
      double tiltAngle() const;
      bool isTiltAngleDefaulted() const;

      boost::optional<double> startingXCoordinate() const;
      boost::optional<double> startingYCoordinate() const;
      boost::optional<double> startingZCoordinate() const;
      boost::optional<double> length() const;
      boost::optional<double> height() const;

      bool setAzimuthAngle(double azimuthAngle);
      bool setTiltAngle(double tiltAngle);
      bool setStartingXCoordinate(double startingXCoordinate);
      bool setStartingYCoordinate(double startingYCoordinate);
      bool setStartingZCoordinate(double startingZCoordinate);
      bool setLength(double length);
      bool setHeight(double height);

      void resetAzimuthAngle();
      void resetTiltAngle();
      void resetStartingXCoordinate();
      void resetStartingYCoordinate();
      void resetStartingZCoordinate();
      void resetLength();
      void resetHeight();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
