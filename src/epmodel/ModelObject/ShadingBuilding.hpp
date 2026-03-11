/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SHADINGBUILDING_HPP
#define EPMODEL_SHADINGBUILDING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ShadingBuilding_Impl;
}

class EPMODEL_API ShadingBuilding : public ModelObject
{
 public:
  explicit ShadingBuilding(const Model& model);

  virtual ~ShadingBuilding() override = default;
  ShadingBuilding(const ShadingBuilding& other) = default;
  ShadingBuilding(ShadingBuilding&& other) = default;
  ShadingBuilding& operator=(const ShadingBuilding&) = default;
  ShadingBuilding& operator=(ShadingBuilding&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs below map directly to EnergyPlus Shading:Building fields.
  // - Field Mapping: Name is inherited from ModelObject scalar API and maps to Shading:Building / Name.
  // - TODO(parity): Add relationship/non-scalar APIs incrementally in future parity passes if needed.
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

 protected:
  using ImplType = detail::ShadingBuilding_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ShadingBuilding(std::shared_ptr<detail::ShadingBuilding_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
