/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CEILINGINTERZONE_HPP
#define EPMODEL_CEILINGINTERZONE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CeilingInterzone_Impl;
}

class EPMODEL_API CeilingInterzone : public ModelObject
{
 public:
  explicit CeilingInterzone(const Model& model);

  virtual ~CeilingInterzone() override = default;
  CeilingInterzone(const CeilingInterzone& other) = default;
  CeilingInterzone(CeilingInterzone&& other) = default;
  CeilingInterzone& operator=(const CeilingInterzone&) = default;
  CeilingInterzone& operator=(CeilingInterzone&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to EnergyPlus Ceiling:Interzone fields.
  // - Field Mapping: Construction Name, Zone Name, Space Name, and Outside Boundary
  //   Condition Object are relationship-like object-list links and are excluded from
  //   scalar accessors.
  // - ForwardTranslator Evidence: GeometryTranslator maps Ceiling:Interzone scalar
  //   geometry fields (Azimuth/Tilt/X/Y/Z/Length/Width) directly to detailed vertices.
  // - TODO(parity): Add typed relationship APIs when non-scalar parity work is prioritized.
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

  boost::optional<double> width() const;
  bool setWidth(double width);
  void resetWidth();

 protected:
  using ImplType = detail::CeilingInterzone_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CeilingInterzone(std::shared_ptr<detail::CeilingInterzone_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
