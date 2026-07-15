/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SHADINGOVERHANG_IMPL_HPP
#define EPMODEL_SHADINGOVERHANG_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API ShadingOverhang_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ShadingOverhang_Impl() override = default;

      boost::optional<double> heightaboveWindoworDoor() const;
      bool setHeightaboveWindoworDoor(double heightaboveWindoworDoor);
      void resetHeightaboveWindoworDoor();

      double tiltAnglefromWindowDoor() const;
      bool isTiltAnglefromWindowDoorDefaulted() const;
      bool setTiltAnglefromWindowDoor(double tiltAnglefromWindowDoor);
      void resetTiltAnglefromWindowDoor();

      boost::optional<double> leftextensionfromWindowDoorWidth() const;
      bool setLeftextensionfromWindowDoorWidth(double leftextensionfromWindowDoorWidth);
      void resetLeftextensionfromWindowDoorWidth();

      boost::optional<double> rightextensionfromWindowDoorWidth() const;
      bool setRightextensionfromWindowDoorWidth(double rightextensionfromWindowDoorWidth);
      void resetRightextensionfromWindowDoorWidth();

      boost::optional<double> depth() const;
      bool setDepth(double depth);
      void resetDepth();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
