/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FLOORINTERZONE_IMPL_HPP
#define EPMODEL_FLOORINTERZONE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API FloorInterzone_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~FloorInterzone_Impl() override = default;

      // Scalar-only APIs for Floor:Interzone; relationship-like fields are intentionally excluded.
      boost::optional<double> azimuthAngle() const;
      bool setAzimuthAngle(double azimuthAngle);
      void resetAzimuthAngle();

      double tiltAngle() const;
      bool setTiltAngle(double tiltAngle);
      bool isTiltAngleDefaulted() const;
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

      boost::optional<double> width() const;
      bool setWidth(double width);
      void resetWidth();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
