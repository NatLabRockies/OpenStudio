/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FLOORGROUNDCONTACT_HPP
#define EPMODEL_FLOORGROUNDCONTACT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class FloorGroundContact_Impl;
}

class EPMODEL_API FloorGroundContact : public ModelObject
{
 public:
  explicit FloorGroundContact(const Model& model);

  virtual ~FloorGroundContact() override = default;
  FloorGroundContact(const FloorGroundContact& other) = default;
  FloorGroundContact(FloorGroundContact&& other) = default;
  FloorGroundContact& operator=(const FloorGroundContact&) = default;
  FloorGroundContact& operator=(FloorGroundContact&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: azimuthAngle, tiltAngle, startingXCoordinate, startingYCoordinate, startingZCoordinate,
  //   length, and width map directly to EnergyPlus Floor:GroundContact scalar fields with matching names.
  // - Field Mapping: Construction Name, Zone Name, and Space Name are object-list relationship fields and are
  //   intentionally excluded from scalar accessors.
  // - Field Mapping: Name remains available through base ModelObject naming API.
  // - ForwardTranslator Evidence: GeometryTranslator maps Floor:GroundContact scalar fields into
  //   BuildingSurface:Detailed scalar fields during import translation.
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
  using ImplType = detail::FloorGroundContact_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit FloorGroundContact(std::shared_ptr<detail::FloorGroundContact_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
