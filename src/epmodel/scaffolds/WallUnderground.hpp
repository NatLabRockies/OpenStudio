/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_WALLUNDERGROUND_HPP
#define EPMODEL_WALLUNDERGROUND_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class WallUnderground_Impl;
  }

  class EPMODEL_API WallUnderground : public ModelObject
  {
   public:
    explicit WallUnderground(const Model& model);

    virtual ~WallUnderground() override = default;
    WallUnderground(const WallUnderground& other) = default;
    WallUnderground(WallUnderground&& other) = default;
    WallUnderground& operator=(const WallUnderground&) = default;
    WallUnderground& operator=(WallUnderground&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Wall:Underground exposes the numeric orientation/geometry primitives while leaving zone/space/construction references on the relationship side.
    // - Field Mapping: Azimuth Angle, Tilt Angle, Starting (X, Y, Z) Coordinates, Length, and Height map directly to the Wall_UndergroundFields enum.
    // - Field Mapping: Construction Name, Zone Name, and Space Name are relationship/geometry-driven and intentionally excluded from this scalar scaffold phase.
    // - TODO(parity): Add the relationship helpers once the ForwardTranslator adjacency logic is ported into epmodel.

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
    using ImplType = detail::WallUnderground_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit WallUnderground(std::shared_ptr<detail::WallUnderground_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
