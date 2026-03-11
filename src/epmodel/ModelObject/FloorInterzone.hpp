/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FLOORINTERZONE_HPP
#define EPMODEL_FLOORINTERZONE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class FloorInterzone_Impl;
}

class EPMODEL_API FloorInterzone : public ModelObject
{
 public:
  explicit FloorInterzone(const Model& model);

  virtual ~FloorInterzone() override = default;
  FloorInterzone(const FloorInterzone& other) = default;
  FloorInterzone(FloorInterzone&& other) = default;
  FloorInterzone& operator=(const FloorInterzone&) = default;
  FloorInterzone& operator=(FloorInterzone&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: azimuthAngle, tiltAngle, startingXCoordinate, startingYCoordinate, startingZCoordinate,
  //   length, and width map directly to EnergyPlus Floor:Interzone scalar fields with matching names.
  // - Field Mapping: Construction Name, Zone Name, Space Name, and Outside Boundary Condition Object are
  //   object-list relationship fields and are intentionally excluded from scalar accessors.
  // - Field Mapping: Name remains available through base ModelObject naming API.
  // - ForwardTranslator Evidence: GeometryTranslator maps Floor:Interzone scalar geometry
  //   (Azimuth/Tilt/X/Y/Z/Length/Width) to BuildingSurface:Detailed vertices and passes
  //   Name/Construction/Zone/Outside Boundary Condition Object through to matching
  //   BuildingSurface:Detailed fields during geometry translation.
  // - TODO(parity): Add typed relationship APIs after scalar scaffold saturation.
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
  using ImplType = detail::FloorInterzone_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit FloorInterzone(std::shared_ptr<detail::FloorInterzone_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
