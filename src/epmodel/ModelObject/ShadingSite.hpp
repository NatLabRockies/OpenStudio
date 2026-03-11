/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SHADINGSITE_HPP
#define EPMODEL_SHADINGSITE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ShadingSite_Impl;
}

class EPMODEL_API ShadingSite : public ModelObject
{
 public:
  explicit ShadingSite(const Model& model);

  virtual ~ShadingSite() override = default;
  ShadingSite(const ShadingSite& other) = default;
  ShadingSite(ShadingSite&& other) = default;
  ShadingSite& operator=(const ShadingSite&) = default;
  ShadingSite& operator=(ShadingSite&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs below map directly to EnergyPlus Shading:Site fields.
  // - Field Mapping: Name is inherited from ModelObject scalar API and maps to Shading:Site / Name.
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
  using ImplType = detail::ShadingSite_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ShadingSite(std::shared_ptr<detail::ShadingSite_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
