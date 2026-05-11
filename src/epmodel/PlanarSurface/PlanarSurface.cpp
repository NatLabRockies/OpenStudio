/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "PlanarSurface/PlanarSurface.hpp"
#include "PlanarSurface/PlanarSurface_Impl.hpp"

#include "Model.hpp"
#include "ModelObject.hpp"
#include "PlanarSurface/SubSurface.hpp"
#include "PlanarSurface/SubSurface_Impl.hpp"
#include "PlanarSurfaceGroup/Space.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/core/String.hpp>
#include <utilities/geometry/Geometry.hpp>
#include <utilities/geometry/Plane.hpp>
#include <utilities/geometry/Point3d.hpp>
#include <utilities/geometry/Polyhedron.hpp>
#include <utilities/geometry/Transformation.hpp>
#include <utilities/geometry/Vector3d.hpp>
#include <utilities/idf/IdfExtensibleGroup.hpp>

#include <boost/math/constants/constants.hpp>

namespace openstudio {
namespace epmodel {

  PlanarSurface::PlanarSurface(IddObjectType type, const Model& model, bool fastName, bool isTransient)
    : ParentObject(type, model, fastName, isTransient) {}

  PlanarSurface::PlanarSurface(std::shared_ptr<detail::PlanarSurface_Impl> impl) : ParentObject(std::move(impl)) {}

  boost::optional<Space> PlanarSurface::space() const {
    return getImpl<detail::PlanarSurface_Impl>()->space();
  }

  std::vector<Point3d> PlanarSurface::vertices() const {
    return getImpl<detail::PlanarSurface_Impl>()->vertices();
  }

  bool PlanarSurface::setVertices(const std::vector<Point3d>& vertices) {
    return getImpl<detail::PlanarSurface_Impl>()->setVertices(vertices);
  }

  double PlanarSurface::grossArea() const {
    return getImpl<detail::PlanarSurface_Impl>()->grossArea();
  }

  bool PlanarSurface::subtractFromGrossArea() const {
    return getImpl<detail::PlanarSurface_Impl>()->subtractFromGrossArea();
  }

  double PlanarSurface::netArea() const {
    return getImpl<detail::PlanarSurface_Impl>()->netArea();
  }

  Vector3d PlanarSurface::outwardNormal() const {
    return getImpl<detail::PlanarSurface_Impl>()->outwardNormal();
  }

  double PlanarSurface::tilt() const {
    return getImpl<detail::PlanarSurface_Impl>()->tilt();
  }

  double PlanarSurface::azimuth() const {
    return getImpl<detail::PlanarSurface_Impl>()->azimuth();
  }

  Plane PlanarSurface::plane() const {
    return getImpl<detail::PlanarSurface_Impl>()->plane();
  }

  Point3d PlanarSurface::centroid() const {
    return getImpl<detail::PlanarSurface_Impl>()->centroid();
  }

  bool PlanarSurface::isConvex() const {
    return getImpl<detail::PlanarSurface_Impl>()->isConvex();
  }

  std::vector<std::vector<Point3d>> PlanarSurface::triangulation() const {
    return getImpl<detail::PlanarSurface_Impl>()->triangulation();
  }

  bool PlanarSurface::equalVertices(const PlanarSurface& other) const {
    return getImpl<detail::PlanarSurface_Impl>()->equalVertices(other);
  }

  bool PlanarSurface::reverseEqualVertices(const PlanarSurface& other) const {
    return getImpl<detail::PlanarSurface_Impl>()->reverseEqualVertices(other);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::vector<Point3d> PlanarSurface_Impl::vertices() const {
      if (!m_cachedVertices) {
        std::vector<Point3d> result;
        for (const auto& group : extensibleGroups()) {
          const auto x = group.getDouble(0);
          const auto y = group.getDouble(1);
          const auto z = group.getDouble(2);
          if (x && y && z) {
            result.emplace_back(*x, *y, *z);
          } else {
            LOG(Error, "Could not read vertex " << group.groupIndex() << " in " << briefDescription() << ".");
          }
        }
        m_cachedVertices = result;
      }
      return m_cachedVertices.get();
    }

    bool PlanarSurface_Impl::setVertices(const std::vector<Point3d>& vertices) {
      const unsigned n = vertices.size();
      if (n < 3) {
        LOG(Error, "Cannot set vertices because size of vertices is " << n << ", which is less than 3.");
        return false;
      }

      try {
        Plane{vertices};
      } catch (const std::exception&) {
        LOG(Error, "Could not compute plane for vertices for '" << nameString() << "'.");
        return false;
      }

      clearExtensibleGroups(false);

      for (const auto& vertex : vertices) {
        std::vector<std::string> values{toString(vertex.x()), toString(vertex.y()), toString(vertex.z())};
        auto group = pushExtensibleGroup(values, false);
        OS_ASSERT(!group.empty());
      }

      clearCachedVariables();
      return true;
    }

    double PlanarSurface_Impl::grossArea() const {
      const auto area = getArea(vertices());
      return area ? *area : 0.0;
    }

    double PlanarSurface_Impl::netArea() const {
      double result = grossArea();
      for (const ModelObject& child : children()) {
        const auto surface = child.optionalCast<PlanarSurface>();
        if (surface && surface->subtractFromGrossArea()) {
          double multiplier = 1.0;
          if (const auto subSurface = child.optionalCast<SubSurface>()) {
            multiplier = subSurface->multiplier();
          }
          result -= multiplier * surface->grossArea();  // TODO: should use roughOpeningArea
        }
      }
      return result;
    }

    Vector3d PlanarSurface_Impl::outwardNormal() const {
      if (!m_cachedOutwardNormal) {
        const auto verts = vertices();
        m_cachedOutwardNormal = getOutwardNormal(verts);
        if (!m_cachedOutwardNormal) {
          LOG_AND_THROW("Cannot compute outward normal for vertices " << verts << ", surface name = '" << nameString() << "'");
        }
      }
      return m_cachedOutwardNormal.get();
    }

    double PlanarSurface_Impl::tilt() const {
      const Vector3d n = outwardNormal();
      const Vector3d up(0.0, 0.0, 1.0);
      return getAngle(n, up);
    }

    double PlanarSurface_Impl::azimuth() const {
      const Vector3d n = outwardNormal();
      const Vector3d north(0.0, 1.0, 0.0);
      const double rawAngle = getAngle(n, north);
      if (n.x() < 0.0) {
        return -rawAngle + 2.0 * boost::math::constants::pi<double>();
      }
      return rawAngle;
    }

    bool PlanarSurface_Impl::equalVertices(const PlanarSurface& other) const {
      return circularEqual(vertices(), other.vertices());
    }

    bool PlanarSurface_Impl::reverseEqualVertices(const PlanarSurface& other) const {
      auto verts2 = other.vertices();
      std::reverse(verts2.begin(), verts2.end());
      return circularEqual(vertices(), verts2);
    }

    Plane PlanarSurface_Impl::plane() const {
      if (!m_cachedPlane) {
        m_cachedPlane = Plane(vertices());
      }
      return m_cachedPlane.get();
    }

    Point3d PlanarSurface_Impl::centroid() const {
      const auto result = getCentroid(vertices());
      OS_ASSERT(result);
      return *result;
    }

    Surface3d PlanarSurface_Impl::surface3d() const {
      return {vertices(), nameString(), 0};
    }

    bool PlanarSurface_Impl::isConvex() const {
      return surface3d().isConvex();
    }

    std::vector<std::vector<Point3d>> PlanarSurface_Impl::triangulation() const {
      if (m_cachedTriangulation.empty()) {
        const Transformation faceTransformation = Transformation::alignFace(vertices());
        const Transformation faceTransformationInverse = faceTransformation.inverse();

        auto faceVertices = faceTransformationInverse * vertices();
        std::reverse(faceVertices.begin(), faceVertices.end());

        std::vector<std::vector<Point3d>> faceHoles;
        for (const ModelObject& child : children()) {
          const auto surface = child.optionalCast<PlanarSurface>();
          if (surface && surface->subtractFromGrossArea()) {
            auto holeVertices = faceTransformationInverse * surface->vertices();
            std::reverse(holeVertices.begin(), holeVertices.end());
            faceHoles.push_back(std::move(holeVertices));
          }
        }

        const auto faceTriangulation = computeTriangulation(faceVertices, faceHoles);
        for (auto faceTriangle : faceTriangulation) {
          std::reverse(faceTriangle.begin(), faceTriangle.end());
          m_cachedTriangulation.push_back(faceTransformation * faceTriangle);
        }
      }
      return m_cachedTriangulation;
    }

    void PlanarSurface_Impl::clearCachedVariables() {
      m_cachedVertices.reset();
      m_cachedPlane.reset();
      m_cachedOutwardNormal.reset();
      m_cachedTriangulation.clear();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
