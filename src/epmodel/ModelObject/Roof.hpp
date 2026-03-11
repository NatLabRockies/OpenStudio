/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_ROOF_HPP
#define EPMODEL_ROOF_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class Roof_Impl;
  }

  class EPMODEL_API Roof : public ModelObject
  {
   public:
    explicit Roof(const Model& model);

    virtual ~Roof() override = default;
    Roof(const Roof& other) = default;
    Roof(Roof&& other) = default;
    Roof& operator=(const Roof&) = default;
    Roof& operator=(Roof&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type keeps IDD-derived naming and preserves scalar-only coverage of Roof fields.
    // - Field Mapping: Azimuth Angle, Tilt Angle, Starting Coordinates, Length, and Width map directly to EnergyPlus Roof scalars.
    // - Field Mapping: Construction Name, Zone Name, and Space Name are object-list references and intentionally excluded from scalar accessors.
    // - TODO(parity): Add typed relationship APIs once non-scalar work is prioritized.
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
    using ImplType = detail::Roof_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit Roof(std::shared_ptr<detail::Roof_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
