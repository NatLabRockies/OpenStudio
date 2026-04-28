/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SHADINGOVERHANG_HPP
#define EPMODEL_SHADINGOVERHANG_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ShadingOverhang_Impl;
}

class EPMODEL_API ShadingOverhang : public ModelObject
{
 public:
  explicit ShadingOverhang(const Model& model);

  virtual ~ShadingOverhang() override = default;
  ShadingOverhang(const ShadingOverhang& other) = default;
  ShadingOverhang(ShadingOverhang&& other) = default;
  ShadingOverhang& operator=(const ShadingOverhang&) = default;
  ShadingOverhang& operator=(ShadingOverhang&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs below map directly to EnergyPlus Shading:Overhang numeric fields.
  // - Field Mapping: Name is inherited from ModelObject scalar API and maps to Shading:Overhang / Name.
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

  boost::optional<double> depth() const;
  bool setDepth(double depth);
  void resetDepth();

 protected:
  using ImplType = detail::ShadingOverhang_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ShadingOverhang(std::shared_ptr<detail::ShadingOverhang_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
