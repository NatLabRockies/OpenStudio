/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SHADINGFINPROJECTION_HPP
#define EPMODEL_SHADINGFINPROJECTION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ShadingFinProjection_Impl;
}

class EPMODEL_API ShadingFinProjection : public ModelObject
{
 public:
  explicit ShadingFinProjection(const Model& model);

  virtual ~ShadingFinProjection() override = default;
  ShadingFinProjection(const ShadingFinProjection& other) = default;
  ShadingFinProjection(ShadingFinProjection&& other) = default;
  ShadingFinProjection& operator=(const ShadingFinProjection&) = default;
  ShadingFinProjection& operator=(ShadingFinProjection&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs below map directly to EnergyPlus Shading:Fin:Projection numeric fields.
  // - Field Mapping: Name is inherited from ModelObject scalar API and maps to Shading:Fin:Projection / Name.
  // - TODO(parity): Add non-scalar relationship API (Window or Door Name) only when relationship parity is in scope.
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

 protected:
  using ImplType = detail::ShadingFinProjection_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ShadingFinProjection(std::shared_ptr<detail::ShadingFinProjection_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
