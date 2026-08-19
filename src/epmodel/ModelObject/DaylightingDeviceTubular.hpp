/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DAYLIGHTINGDEVICETUBULAR_HPP
#define EPMODEL_DAYLIGHTINGDEVICETUBULAR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class DaylightingDeviceTubular_Impl;
  }

  /** \brief Represents <code>DaylightingDevice:Tubular</code>.
   *
   * \par EnergyPlus object
   * \epobject{group-daylighting.html#daylightingdevicetubular,DaylightingDevice:Tubular}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::DaylightingDeviceTubular</code>.
   * **Not yet available:** Model surface, construction, and extensible transition/shelf relationship conveniences are not exposed unless declared here.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API DaylightingDeviceTubular : public ModelObject
  {
   public:
    explicit DaylightingDeviceTubular(const Model& model);

    virtual ~DaylightingDeviceTubular() override = default;
    DaylightingDeviceTubular(const DaylightingDeviceTubular& other) = default;
    DaylightingDeviceTubular(DaylightingDeviceTubular&& other) = default;
    DaylightingDeviceTubular& operator=(const DaylightingDeviceTubular&) = default;
    DaylightingDeviceTubular& operator=(DaylightingDeviceTubular&&) = default;

    static IddObjectType iddObjectType();
    double diameter() const;
    bool setDiameter(double diameter);

    double totalLength() const;
    bool setTotalLength(double totalLength);

    double effectiveThermalResistance() const;
    bool setEffectiveThermalResistance(double effectiveThermalResistance);
    bool isEffectiveThermalResistanceDefaulted() const;
    void resetEffectiveThermalResistance();

   protected:
    using ImplType = detail::DaylightingDeviceTubular_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit DaylightingDeviceTubular(std::shared_ptr<detail::DaylightingDeviceTubular_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
