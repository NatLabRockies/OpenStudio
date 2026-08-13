/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "PlanarSurface/InteriorPartitionSurface.hpp"
#include "PlanarSurface/InteriorPartitionSurface_Impl.hpp"
#include "ConstructionBase/ConstructionBase.hpp"
#include "ConstructionBase/ConstructionBase_Impl.hpp"

#include "Model.hpp"
#include "PlanarSurfaceGroup/Space.hpp"
#include "PlanarSurfaceGroup/Space_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/geometry/Geometry.hpp>
#include <utilities/geometry/Plane.hpp>
#include <utilities/geometry/Point3d.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/InternalMass_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  InteriorPartitionSurface::InteriorPartitionSurface(const std::vector<Point3d>& vertices, const Model& model)
    : PlanarSurface(InteriorPartitionSurface::iddObjectType(), model) {
    if (!getImpl<detail::InteriorPartitionSurface_Impl>()->setVertices(vertices)) {
      remove();
      LOG_AND_THROW("Cannot create an InteriorPartitionSurface from the supplied vertices.");
    }
  }

  InteriorPartitionSurface::InteriorPartitionSurface(std::shared_ptr<detail::InteriorPartitionSurface_Impl> impl) : PlanarSurface(std::move(impl)) {}

  IddObjectType InteriorPartitionSurface::iddObjectType() {
    return IddObjectType::InternalMass;
  }

  bool InteriorPartitionSurface::converttoInternalMass() const {
    return getImpl<detail::InteriorPartitionSurface_Impl>()->converttoInternalMass();
  }

  bool InteriorPartitionSurface::isConverttoInternalMassDefaulted() const {
    return getImpl<detail::InteriorPartitionSurface_Impl>()->isConverttoInternalMassDefaulted();
  }

  boost::optional<double> InteriorPartitionSurface::surfaceArea() const {
    return getImpl<detail::InteriorPartitionSurface_Impl>()->surfaceArea();
  }

  boost::optional<double> InteriorPartitionSurface::numberofVertices() const {
    return getImpl<detail::InteriorPartitionSurface_Impl>()->numberofVertices();
  }

  bool InteriorPartitionSurface::isNumberofVerticesDefaulted() const {
    return getImpl<detail::InteriorPartitionSurface_Impl>()->isNumberofVerticesDefaulted();
  }

  bool InteriorPartitionSurface::isNumberofVerticesAutocalculated() const {
    return getImpl<detail::InteriorPartitionSurface_Impl>()->isNumberofVerticesAutocalculated();
  }

  bool InteriorPartitionSurface::setConverttoInternalMass(bool converttoInternalMass) {
    return getImpl<detail::InteriorPartitionSurface_Impl>()->setConverttoInternalMass(converttoInternalMass);
  }

  void InteriorPartitionSurface::resetConverttoInternalMass() {
    getImpl<detail::InteriorPartitionSurface_Impl>()->resetConverttoInternalMass();
  }

  bool InteriorPartitionSurface::setSurfaceArea(boost::optional<double> surfaceArea) {
    return getImpl<detail::InteriorPartitionSurface_Impl>()->setSurfaceArea(surfaceArea);
  }

  bool InteriorPartitionSurface::setSurfaceArea(double surfaceArea) {
    return getImpl<detail::InteriorPartitionSurface_Impl>()->setSurfaceArea(surfaceArea);
  }

  void InteriorPartitionSurface::resetSurfaceArea() {
    getImpl<detail::InteriorPartitionSurface_Impl>()->resetSurfaceArea();
  }

  bool InteriorPartitionSurface::setNumberofVertices(boost::optional<double> numberofVertices) {
    return getImpl<detail::InteriorPartitionSurface_Impl>()->setNumberofVertices(numberofVertices);
  }

  bool InteriorPartitionSurface::setNumberofVertices(double numberofVertices) {
    return getImpl<detail::InteriorPartitionSurface_Impl>()->setNumberofVertices(numberofVertices);
  }

  void InteriorPartitionSurface::resetNumberofVertices() {
    getImpl<detail::InteriorPartitionSurface_Impl>()->resetNumberofVertices();
  }

  void InteriorPartitionSurface::autocalculateNumberofVertices() {
    getImpl<detail::InteriorPartitionSurface_Impl>()->autocalculateNumberofVertices();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<Space> InteriorPartitionSurface_Impl::space() const {
      return getObject<InteriorPartitionSurface>().getModelObjectTarget<Space>(openstudio::InternalMassFields::SpaceorSpaceListName);
    }

    bool InteriorPartitionSurface_Impl::subtractFromGrossArea() const {
      return false;
    }

    bool InteriorPartitionSurface_Impl::setVertices(const std::vector<Point3d>& vertices) {
      if (vertices.size() < 3u) {
        LOG(Error, "Cannot set vertices because size of vertices is " << vertices.size() << ", which is less than 3.");
        return false;
      }

      try {
        Plane{vertices};
      } catch (const std::exception&) {
        LOG(Error, "Could not compute plane for vertices for '" << nameString() << "'.");
        return false;
      }

      const auto area = getArea(vertices);
      if (!area || (*area <= 0.0)) {
        LOG(Error, "Could not compute a positive surface area from vertices for '" << nameString() << "'.");
        return false;
      }

      return setSurfaceArea(*area);
    }

    double InteriorPartitionSurface_Impl::grossArea() const {
      return surfaceArea().value_or(0.0);
    }

    boost::optional<ConstructionBase> InteriorPartitionSurface_Impl::construction() const {
      return getObject<InteriorPartitionSurface>().getModelObjectTarget<ConstructionBase>(openstudio::InternalMassFields::ConstructionName);
    }

    bool InteriorPartitionSurface_Impl::setConstruction(const ConstructionBase& construction) {
      return setPointer(openstudio::InternalMassFields::ConstructionName, construction.handle());
    }

    void InteriorPartitionSurface_Impl::resetConstruction() {
      setString(openstudio::InternalMassFields::ConstructionName, "");
    }

    bool InteriorPartitionSurface_Impl::converttoInternalMass() const {
      // InternalMass is already the translated EP object for this class.
      return true;
    }

    bool InteriorPartitionSurface_Impl::isConverttoInternalMassDefaulted() const {
      // Compatibility shim: no dedicated EP field exists for this OS-only flag.
      return true;
    }

    bool InteriorPartitionSurface_Impl::setConverttoInternalMass(bool converttoInternalMass) {
      // Compatibility shim: this epmodel class always maps to InternalMass.
      return converttoInternalMass;
    }

    void InteriorPartitionSurface_Impl::resetConverttoInternalMass() {}

    boost::optional<double> InteriorPartitionSurface_Impl::surfaceArea() const {
      return getDouble(openstudio::InternalMassFields::SurfaceArea, true);
    }

    bool InteriorPartitionSurface_Impl::setSurfaceArea(boost::optional<double> surfaceArea) {
      if (!surfaceArea) {
        return false;
      }
      return setSurfaceArea(*surfaceArea);
    }

    bool InteriorPartitionSurface_Impl::setSurfaceArea(double surfaceArea) {
      return setDouble(openstudio::InternalMassFields::SurfaceArea, surfaceArea);
    }

    void InteriorPartitionSurface_Impl::resetSurfaceArea() {}

    boost::optional<double> InteriorPartitionSurface_Impl::numberofVertices() const {
      // Compatibility shim: InternalMass has no vertex-count scalar.
      return boost::none;
    }

    bool InteriorPartitionSurface_Impl::isNumberofVerticesDefaulted() const {
      return true;
    }

    bool InteriorPartitionSurface_Impl::isNumberofVerticesAutocalculated() const {
      return false;
    }

    bool InteriorPartitionSurface_Impl::setNumberofVertices(boost::optional<double> numberofVertices) {
      if (!numberofVertices) {
        return true;
      }
      return false;
    }

    bool InteriorPartitionSurface_Impl::setNumberofVertices(double numberofVertices) {
      static_cast<void>(numberofVertices);
      return false;
    }

    void InteriorPartitionSurface_Impl::resetNumberofVertices() {}

    void InteriorPartitionSurface_Impl::autocalculateNumberofVertices() {}

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
