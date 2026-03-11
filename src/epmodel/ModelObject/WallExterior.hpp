/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WALLEXTERIOR_HPP
#define EPMODEL_WALLEXTERIOR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class WallExterior_Impl;
  }

  class EPMODEL_API WallExterior : public ModelObject
  {
   public:
    explicit WallExterior(const Model& model);

    virtual ~WallExterior() override = default;
    WallExterior(const WallExterior& other) = default;
    WallExterior(WallExterior&& other) = default;
    WallExterior& operator=(const WallExterior&) = default;
    WallExterior& operator=(WallExterior&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Wall:Exterior exposes the numeric orientation and geometry primitives while leaving relationship data on the construction/zone/space references to downstream translators.
    // - Field Mapping: Azimuth Angle, Tilt Angle, Starting (X, Y, Z) Coordinates, Length, and Height map directly to the Wall_ExteriorFields enum.
    // - Field Mapping: Construction Name, Zone Name, Space Name, and vertex coordinate sets are relationship/geometry-driven and intentionally excluded here.
    // - TODO(parity): Add helpers for the relationship fields once ForwardTranslator adjacency logic is ported into epmodel.
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
    using ImplType = detail::WallExterior_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit WallExterior(std::shared_ptr<detail::WallExterior_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
