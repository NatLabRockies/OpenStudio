/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANARSURFACE_IMPL_HPP
#define EPMODEL_PLANARSURFACE_IMPL_HPP

#include "ParentObject/ParentObject_Impl.hpp"
#include "../utilities/idf/IdfObject.hpp"

#include "../utilities/geometry/Plane.hpp"
#include "../utilities/geometry/Point3d.hpp"
#include "../utilities/geometry/Vector3d.hpp"

#include <boost/optional.hpp>

#include <utility>

namespace openstudio {

class Surface3d;

namespace epmodel {

  class ConstructionBase;
  class PlanarSurface;
  class Space;

  namespace detail {

    // derive PlanarSurface_Impl from ParentObject_Impl to override virtual methods
    class EPMODEL_API PlanarSurface_Impl : public ParentObject_Impl
    {

     public:
      using ParentObject_Impl::ParentObject_Impl;
      virtual ~PlanarSurface_Impl() override = default;

      //@}
      /** @name Getters */
      //@{

      virtual boost::optional<Space> space() const = 0;

      std::vector<Point3d> vertices() const;

      //@}
      /** @name Setters */

      virtual bool setVertices(const std::vector<Point3d>& vertices);

      virtual boost::optional<ConstructionBase> construction() const;
      virtual boost::optional<std::pair<ConstructionBase, int>> constructionWithSearchDistance() const = 0;
      virtual bool isConstructionDefaulted() const = 0;
      virtual bool setConstruction(const ConstructionBase& construction) = 0;
      virtual void resetConstruction() = 0;

      //@}
      /** @name Queries */
      //@{

      virtual double grossArea() const;

      virtual bool subtractFromGrossArea() const = 0;

      double netArea() const;

      Vector3d outwardNormal() const;

      double tilt() const;

      double azimuth() const;

      bool equalVertices(const PlanarSurface& other) const;

      bool reverseEqualVertices(const PlanarSurface& other) const;

      Plane plane() const;

      Point3d centroid() const;

      Surface3d surface3d() const;

      bool isConvex() const;

      std::vector<std::vector<Point3d>> triangulation() const;

      //@}
     protected:
      /** Returns the construction assigned to this surface by the ConstructionAssignmentSet of its Space (search distance 1), else of
       *  the Building (search distance 2). A surface without a Space only looks at the Building's set, as EnergyPlus puts it in its
       *  zone's default Space. */
      boost::optional<std::pair<ConstructionBase, int>> defaultConstructionWithSearchDistance() const;

      /** Picks the construction of a surface from its own and its adjacent surface's constructionWithSearchDistance(), following
       *  EnergyPlus' ConstructionAssignments::resolveConstructionWithSearchDistance. When the adjacent surface wins, its construction is
       *  returned as is: EnergyPlus uses its reversed-layers copy instead, which may not exist in the model. */
      static boost::optional<ConstructionBase> resolveAdjacentConstruction(const PlanarSurface& planarSurface,
                                                                           const boost::optional<std::pair<ConstructionBase, int>>& thisCWSD,
                                                                           const PlanarSurface& adjacentPlanarSurface,
                                                                           const boost::optional<std::pair<ConstructionBase, int>>& adjacentCWSD);

      //private slots:
     private:
      void clearCachedVariables();

     private:
      REGISTER_LOGGER("openstudio.epmodel.PlanarSurface");

      mutable boost::optional<std::vector<Point3d>> m_cachedVertices;
      mutable boost::optional<Plane> m_cachedPlane;
      mutable boost::optional<Vector3d> m_cachedOutwardNormal;
      mutable std::vector<std::vector<Point3d>> m_cachedTriangulation;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
