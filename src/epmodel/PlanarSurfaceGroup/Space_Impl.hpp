/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SPACE_IMPL_HPP
#define EPMODEL_SPACE_IMPL_HPP

#include "PlanarSurfaceGroup/PlanarSurfaceGroup_Impl.hpp"
#include "../PlanarSurface/Surface.hpp"

namespace openstudio {

class BoundingBox;
class Polyhedron;
class Transformation;

namespace epmodel {

  class DesignSpecificationOutdoorAir;
  class Space;
  class ThermalZone;

  namespace detail {

    class EPMODEL_API Space_Impl : public PlanarSurfaceGroup_Impl
    {
     public:
      using PlanarSurfaceGroup_Impl::PlanarSurfaceGroup_Impl;
      virtual ~Space_Impl() override = default;

      double ceilingHeight() const;
      bool isCeilingHeightDefaulted() const;
      bool isCeilingHeightAutocalculated() const;
      bool setCeilingHeight(double ceilingHeight);
      void autocalculateCeilingHeight();
      void resetCeilingHeight();

      double volume() const;
      bool isVolumeDefaulted() const;
      bool isVolumeAutocalculated() const;
      bool setVolume(double volume);
      void autocalculateVolume();
      void resetVolume();

      double floorArea() const;
      bool isFloorAreaDefaulted() const;
      bool isFloorAreaAutocalculated() const;
      bool setFloorArea(double floorArea);
      void autocalculateFloorArea();
      void resetFloorArea();

      boost::optional<openstudio::epmodel::ThermalZone> thermalZone() const;
      bool setThermalZone(const openstudio::epmodel::ThermalZone& thermalZone);
      void resetThermalZone();
      boost::optional<openstudio::epmodel::DesignSpecificationOutdoorAir> designSpecificationOutdoorAir() const;
      bool setDesignSpecificationOutdoorAir(const openstudio::epmodel::DesignSpecificationOutdoorAir& designSpecificationOutdoorAir);

      void doCanonicalize(LoadContext& context) override;

      std::vector<Surface> surfaces() const;

      void unmatchSurfaces();

      void matchSurfaces(Space& other);

      void intersectSurfaces(Space& other);

      Polyhedron polyhedron() const;
      bool isEnclosedVolume() const;

      openstudio::Transformation transformation() const override;
      openstudio::Transformation buildingTransformation() const override;
      bool setTransformation(const openstudio::Transformation& transformation) override;
      bool changeTransformation(const openstudio::Transformation& transformation) override;
      openstudio::BoundingBox boundingBox() const override;

     private:
      REGISTER_LOGGER("openstudio.epmodel.Space");

      mutable boost::optional<std::vector<Surface>> m_cachedNonConvexSurfaces;
      mutable boost::optional<bool> m_cachedIsConvex;
      mutable boost::optional<bool> m_cachedIsEnclosed;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
