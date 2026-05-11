/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SPACE_HPP
#define EPMODEL_SPACE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include "../utilities/geometry/Point3d.hpp"
#include "../utilities/idd/IddEnums.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class ThermalZone;
  class DesignSpecificationOutdoorAir;

  namespace detail {
    class Space_Impl;
  }

  class EPMODEL_API Space : public ModelObject
  {
   public:
    // Schema Alignment Notes:
    // - API: designSpecificationOutdoorAir()/setDesignSpecificationOutdoorAir()
    //   currently route through ThermalZone -> Sizing:Zone ->
    //   DesignSpecification:OutdoorAir:SpaceList in epmodel.
    // - Field Mapping: openstudio::model stores Space DSOA directly on
    //   OS:Space, while epmodel stores zone-scoped DSOA assignment in
    //   Sizing:Zone (DesignSpecification Outdoor Air Object Name).
    // - Current behavior: setDesignSpecificationOutdoorAir(...) is supported for
    //   both zoned and unzoned spaces.
    //   Zoned spaces write through ThermalZone -> Sizing:Zone -> DSOA:SpaceList.
    //   Unzoned spaces write to an orphan DSOA:SpaceList owned by the Model.
    explicit Space(const Model& model);

    static boost::optional<Space> fromFloorPrint(const std::vector<Point3d>& floorPrint, double floorHeight, const Model& model,
                                                 const std::string& spaceName = {});

    virtual ~Space() override = default;
    Space(const Space& other) = default;
    Space(Space&& other) = default;
    Space& operator=(const Space&) = default;
    Space& operator=(Space&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model Space scalar accessor names/signatures for
    //   ceilingHeight, volume, and floorArea.
    // - Field Mapping: These APIs map directly to EnergyPlus Space fields
    //   Ceiling Height, Volume, and Floor Area.
    // - ForwardTranslator evidence: ForwardTranslateSpace.cpp only forwards these
    //   fields when hard-set (non-default), matching default/autocalculate behavior.
    double ceilingHeight() const;
    bool setCeilingHeight(double ceilingHeight);
    bool isCeilingHeightDefaulted() const;
    bool isCeilingHeightAutocalculated() const;
    void autocalculateCeilingHeight();
    void resetCeilingHeight();

    double volume() const;
    bool setVolume(double volume);
    bool isVolumeDefaulted() const;
    bool isVolumeAutocalculated() const;
    void autocalculateVolume();
    void resetVolume();

    double floorArea() const;
    bool setFloorArea(double floorArea);
    bool isFloorAreaDefaulted() const;
    bool isFloorAreaAutocalculated() const;
    void autocalculateFloorArea();
    void resetFloorArea();

    boost::optional<ThermalZone> thermalZone() const;
    bool setThermalZone(const ThermalZone& thermalZone);
    void resetThermalZone();
    boost::optional<DesignSpecificationOutdoorAir> designSpecificationOutdoorAir() const;
    bool setDesignSpecificationOutdoorAir(const DesignSpecificationOutdoorAir& designSpecificationOutdoorAir);

   protected:
    using ImplType = detail::Space_Impl;

    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    friend class Model;

    explicit Space(std::shared_ptr<detail::Space_Impl> impl);

   private:
    REGISTER_LOGGER("openstudio.epmodel.Space");
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
