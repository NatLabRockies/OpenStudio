/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CEILINGADIABATIC_HPP
#define EPMODEL_CEILINGADIABATIC_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CeilingAdiabatic_Impl;
}

class EPMODEL_API CeilingAdiabatic : public ModelObject
{
 public:
  explicit CeilingAdiabatic(const Model& model);

  virtual ~CeilingAdiabatic() override = default;
  CeilingAdiabatic(const CeilingAdiabatic& other) = default;
  CeilingAdiabatic(CeilingAdiabatic&& other) = default;
  CeilingAdiabatic& operator=(const CeilingAdiabatic&) = default;
  CeilingAdiabatic& operator=(CeilingAdiabatic&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to EnergyPlus Ceiling:Adiabatic fields.
  // - Field Mapping: Construction Name, Zone Name, and Space Name are relationship-like
  //   object-list links and are excluded from scalar accessors.
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
  using ImplType = detail::CeilingAdiabatic_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CeilingAdiabatic(std::shared_ptr<detail::CeilingAdiabatic_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
