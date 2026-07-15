/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SHADINGFINPROJECTION_IMPL_HPP
#define EPMODEL_SHADINGFINPROJECTION_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API ShadingFinProjection_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ShadingFinProjection_Impl() override = default;

      boost::optional<double> leftExtensionfromWindowDoor() const;
      bool setLeftExtensionfromWindowDoor(double leftExtensionfromWindowDoor);
      void resetLeftExtensionfromWindowDoor();

      boost::optional<double> leftDistanceAboveTopofWindow() const;
      bool setLeftDistanceAboveTopofWindow(double leftDistanceAboveTopofWindow);
      void resetLeftDistanceAboveTopofWindow();

      boost::optional<double> leftDistanceBelowBottomofWindow() const;
      bool setLeftDistanceBelowBottomofWindow(double leftDistanceBelowBottomofWindow);
      void resetLeftDistanceBelowBottomofWindow();

      double leftTiltAnglefromWindowDoor() const;
      bool isLeftTiltAnglefromWindowDoorDefaulted() const;
      bool setLeftTiltAnglefromWindowDoor(double leftTiltAnglefromWindowDoor);
      void resetLeftTiltAnglefromWindowDoor();

      boost::optional<double> leftDepthasFractionofWindowDoorWidth() const;
      bool setLeftDepthasFractionofWindowDoorWidth(double leftDepthasFractionofWindowDoorWidth);
      void resetLeftDepthasFractionofWindowDoorWidth();

      boost::optional<double> rightExtensionfromWindowDoor() const;
      bool setRightExtensionfromWindowDoor(double rightExtensionfromWindowDoor);
      void resetRightExtensionfromWindowDoor();

      boost::optional<double> rightDistanceAboveTopofWindow() const;
      bool setRightDistanceAboveTopofWindow(double rightDistanceAboveTopofWindow);
      void resetRightDistanceAboveTopofWindow();

      boost::optional<double> rightDistanceBelowBottomofWindow() const;
      bool setRightDistanceBelowBottomofWindow(double rightDistanceBelowBottomofWindow);
      void resetRightDistanceBelowBottomofWindow();

      double rightTiltAnglefromWindowDoor() const;
      bool isRightTiltAnglefromWindowDoorDefaulted() const;
      bool setRightTiltAnglefromWindowDoor(double rightTiltAnglefromWindowDoor);
      void resetRightTiltAnglefromWindowDoor();

      boost::optional<double> rightDepthasFractionofWindowDoorWidth() const;
      bool setRightDepthasFractionofWindowDoorWidth(double rightDepthasFractionofWindowDoorWidth);
      void resetRightDepthasFractionofWindowDoorWidth();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
