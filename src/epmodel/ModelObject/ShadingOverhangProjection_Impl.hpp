/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SHADINGOVERHANGPROJECTION_IMPL_HPP
#define EPMODEL_SHADINGOVERHANGPROJECTION_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API ShadingOverhangProjection_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ShadingOverhangProjection_Impl() override = default;

      // Height above the associated window or door
      boost::optional<double> heightaboveWindoworDoor() const;
      bool setHeightaboveWindoworDoor(double heightaboveWindoworDoor);
      void resetHeightaboveWindoworDoor();

      // Tilt angle measured from the window or door plane
      double tiltAnglefromWindowDoor() const;
      bool isTiltAnglefromWindowDoorDefaulted() const;
      bool setTiltAnglefromWindowDoor(double tiltAnglefromWindowDoor);
      void resetTiltAnglefromWindowDoor();

      // Left extension expressed as a fraction of the window or door width
      boost::optional<double> leftextensionfromWindowDoorWidth() const;
      bool setLeftextensionfromWindowDoorWidth(double leftextensionfromWindowDoorWidth);
      void resetLeftextensionfromWindowDoorWidth();

      // Right extension expressed as a fraction of the window or door width
      boost::optional<double> rightextensionfromWindowDoorWidth() const;
      bool setRightextensionfromWindowDoorWidth(double rightextensionfromWindowDoorWidth);
      void resetRightextensionfromWindowDoorWidth();

      // Depth expressed as a fraction of the window or door height
      boost::optional<double> depthasFractionofWindowDoorHeight() const;
      bool setDepthasFractionofWindowDoorHeight(double depthasFractionofWindowDoorHeight);
      void resetDepthasFractionofWindowDoorHeight();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
