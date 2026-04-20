/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WALLADIABATIC_HPP
#define EPMODEL_WALLADIABATIC_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class WallAdiabatic_Impl;
  }

  class EPMODEL_API WallAdiabatic : public ModelObject
  {
   public:
    explicit WallAdiabatic(const Model& model);

    virtual ~WallAdiabatic() override = default;
    WallAdiabatic(const WallAdiabatic& other) = default;
    WallAdiabatic(WallAdiabatic&& other) = default;
    WallAdiabatic& operator=(const WallAdiabatic&) = default;
    WallAdiabatic& operator=(WallAdiabatic&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Scalar accessors expose only the numeric orientation and geometry properties from EnergyPlus Wall:Adiabatic.
    // - Field Mapping: Azimuth Angle, Tilt Angle, Starting (X, Y, Z) Coordinates, Length, and Height map directly to the IDD fields with the same names.
    // - Field Mapping: Construction Name, Zone Name, and Space Name are relationship-driven object-list references and are intentionally excluded here.
    // - TODO(parity): Add relationship helpers for the construction/zone/space references once adjacency logic is ported.
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
    using ImplType = detail::WallAdiabatic_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit WallAdiabatic(std::shared_ptr<detail::WallAdiabatic_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
