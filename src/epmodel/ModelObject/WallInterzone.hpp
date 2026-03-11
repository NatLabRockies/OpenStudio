/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WALLINTERZONE_HPP
#define EPMODEL_WALLINTERZONE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class WallInterzone_Impl;
  }

  class EPMODEL_API WallInterzone : public ModelObject
  {
   public:
    explicit WallInterzone(const Model& model);

    virtual ~WallInterzone() override = default;
    WallInterzone(const WallInterzone& other) = default;
    WallInterzone(WallInterzone&& other) = default;
    WallInterzone& operator=(const WallInterzone&) = default;
    WallInterzone& operator=(WallInterzone&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Wall:Interzone exposes the numeric orientation and geometry primitives while deferring construction/zone/space/OutsideBoundaryConditionObject relationships to downstream translators.
    // - Field Mapping: Azimuth Angle, Tilt Angle, Starting (X, Y, Z) Coordinates, Length, and Height map directly to Wall_InterzoneFields.
    // - Field Mapping: Construction Name, Zone Name, Space Name, and Outside Boundary Condition Object are relationship/object-list fields intentionally excluded from this scalar-only surface subset.
    // - TODO(parity): Add helpers for the excluded adjacency fields once ForwardTranslator adjacency logic is ported into epmodel.
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
    using ImplType = detail::WallInterzone_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit WallInterzone(std::shared_ptr<detail::WallInterzone_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
