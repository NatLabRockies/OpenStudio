/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GLOBALGEOMETRYRULES_IMPL_HPP
#define EPMODEL_GLOBALGEOMETRYRULES_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API GlobalGeometryRules_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~GlobalGeometryRules_Impl() override = default;

      std::string startingVertexPosition() const;
      bool setStartingVertexPosition(const std::string& startingVertexPosition);
      std::vector<std::string> startingVertexPositionValues() const;

      std::string vertexEntryDirection() const;
      bool setVertexEntryDirection(const std::string& vertexEntryDirection);
      std::vector<std::string> vertexEntryDirectionValues() const;

      std::string coordinateSystem() const;
      bool setCoordinateSystem(const std::string& coordinateSystem);
      std::vector<std::string> coordinateSystemValues() const;

      std::string daylightingReferencePointCoordinateSystem() const;
      bool isDaylightingReferencePointCoordinateSystemDefaulted() const;
      bool setDaylightingReferencePointCoordinateSystem(const std::string& daylightingReferencePointCoordinateSystem);
      void resetDaylightingReferencePointCoordinateSystem();
      std::vector<std::string> daylightingReferencePointCoordinateSystemValues() const;

      std::string rectangularSurfaceCoordinateSystem() const;
      bool isRectangularSurfaceCoordinateSystemDefaulted() const;
      bool setRectangularSurfaceCoordinateSystem(const std::string& rectangularSurfaceCoordinateSystem);
      void resetRectangularSurfaceCoordinateSystem();
      std::vector<std::string> rectangularSurfaceCoordinateSystemValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
