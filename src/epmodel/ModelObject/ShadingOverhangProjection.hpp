/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SHADINGOVERHANGPROJECTION_HPP
#define EPMODEL_SHADINGOVERHANGPROJECTION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ShadingOverhangProjection_Impl;
}

class EPMODEL_API ShadingOverhangProjection : public ModelObject
{
 public:
  explicit ShadingOverhangProjection(const Model& model);

  virtual ~ShadingOverhangProjection() override = default;
  ShadingOverhangProjection(const ShadingOverhangProjection& other) = default;
  ShadingOverhangProjection(ShadingOverhangProjection&& other) = default;
  ShadingOverhangProjection& operator=(const ShadingOverhangProjection&) = default;
  ShadingOverhangProjection& operator=(ShadingOverhangProjection&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs below map directly to EnergyPlus Shading:Overhang:Projection numeric fields.
  // - Field Mapping: Name is inherited from ModelObject scalar API and maps to Shading:Overhang:Projection / Name.
  // - TODO(parity): Add non-scalar relationship API (Window or Door Name) only when relationship parity is in scope.
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

  boost::optional<double> depthasFractionofWindowDoorHeight() const;
  bool setDepthasFractionofWindowDoorHeight(double depthasFractionofWindowDoorHeight);
  void resetDepthasFractionofWindowDoorHeight();

 protected:
  using ImplType = detail::ShadingOverhangProjection_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ShadingOverhangProjection(std::shared_ptr<detail::ShadingOverhangProjection_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
