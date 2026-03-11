/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GLOBALGEOMETRYRULES_HPP
#define EPMODEL_GLOBALGEOMETRYRULES_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class GlobalGeometryRules_Impl;
}

class EPMODEL_API GlobalGeometryRules : public ModelObject
{
 public:
  explicit GlobalGeometryRules(const Model& model);

  virtual ~GlobalGeometryRules() override = default;
  GlobalGeometryRules(const GlobalGeometryRules& other) = default;
  GlobalGeometryRules(GlobalGeometryRules&& other) = default;
  GlobalGeometryRules& operator=(const GlobalGeometryRules&) = default;
  GlobalGeometryRules& operator=(GlobalGeometryRules&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> startingVertexPositionValues();
  static std::vector<std::string> vertexEntryDirectionValues();
  static std::vector<std::string> coordinateSystemValues();
  static std::vector<std::string> daylightingReferencePointCoordinateSystemValues();
  static std::vector<std::string> rectangularSurfaceCoordinateSystemValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: startingVertexPosition, vertexEntryDirection, coordinateSystem,
  //   daylightingReferencePointCoordinateSystem, and rectangularSurfaceCoordinateSystem map directly
  //   to EnergyPlus GlobalGeometryRules scalar fields.
  // - API: CoordinateSystem follows EnergyPlus key values ("Relative", "World"); GeometryTranslator
  //   treats "World" as absolute behavior.
  // - TODO(parity): Keep this object scalar-only in this scaffold pass.
  std::string startingVertexPosition() const;
  bool setStartingVertexPosition(const std::string& startingVertexPosition);

  std::string vertexEntryDirection() const;
  bool setVertexEntryDirection(const std::string& vertexEntryDirection);

  std::string coordinateSystem() const;
  bool setCoordinateSystem(const std::string& coordinateSystem);

  std::string daylightingReferencePointCoordinateSystem() const;
  bool isDaylightingReferencePointCoordinateSystemDefaulted() const;
  bool setDaylightingReferencePointCoordinateSystem(const std::string& daylightingReferencePointCoordinateSystem);
  void resetDaylightingReferencePointCoordinateSystem();

  std::string rectangularSurfaceCoordinateSystem() const;
  bool isRectangularSurfaceCoordinateSystemDefaulted() const;
  bool setRectangularSurfaceCoordinateSystem(const std::string& rectangularSurfaceCoordinateSystem);
  void resetRectangularSurfaceCoordinateSystem();

 protected:
  using ImplType = detail::GlobalGeometryRules_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit GlobalGeometryRules(std::shared_ptr<detail::GlobalGeometryRules_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
