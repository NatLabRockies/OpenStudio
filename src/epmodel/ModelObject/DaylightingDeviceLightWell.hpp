/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DAYLIGHTINGDEVICELIGHTWELL_HPP
#define EPMODEL_DAYLIGHTINGDEVICELIGHTWELL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class DaylightingDeviceLightWell_Impl;
  }

  /** \brief Represents <code>DaylightingDevice:LightWell</code>.
   *
   * \par EnergyPlus object
   * \epobject{group-daylighting.html#daylightingdevicelightwell,DaylightingDevice:LightWell}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::DaylightingDeviceLightWell</code>.
   * **Not yet available:** Model surface, construction, and extensible transition/shelf relationship conveniences are not exposed unless declared here.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API DaylightingDeviceLightWell : public ModelObject
  {
   public:
    explicit DaylightingDeviceLightWell(const Model& model);

    virtual ~DaylightingDeviceLightWell() override = default;
    DaylightingDeviceLightWell(const DaylightingDeviceLightWell& other) = default;
    DaylightingDeviceLightWell(DaylightingDeviceLightWell&& other) = default;
    DaylightingDeviceLightWell& operator=(const DaylightingDeviceLightWell&) = default;
    DaylightingDeviceLightWell& operator=(DaylightingDeviceLightWell&&) = default;

    static IddObjectType iddObjectType();
    double heightofWell() const;
    bool setHeightofWell(double heightofWell);

    // Field: Perimeter of the Bottom of the Well
    double perimeterofBottomofWell() const;
    bool setPerimeterofBottomofWell(double perimeterofBottomofWell);

    // Field: Area of the Bottom of the Well
    double areaofBottomofWell() const;
    bool setAreaofBottomofWell(double areaofBottomofWell);

    // Field: Visible Reflectance of the Well Walls
    double visibleReflectanceofWellWalls() const;
    bool setVisibleReflectanceofWellWalls(double visibleReflectanceofWellWalls);

   protected:
    using ImplType = detail::DaylightingDeviceLightWell_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit DaylightingDeviceLightWell(std::shared_ptr<detail::DaylightingDeviceLightWell_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
