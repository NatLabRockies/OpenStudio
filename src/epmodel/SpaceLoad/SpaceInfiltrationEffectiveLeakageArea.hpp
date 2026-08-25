/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SPACEINFILTRATIONEFFECTIVELEAKAGEAREA_HPP
#define EPMODEL_SPACEINFILTRATIONEFFECTIVELEAKAGEAREA_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SpaceInfiltrationEffectiveLeakageArea_Impl;
  }

  /** \brief Represents the EnergyPlus ZoneInfiltration:EffectiveLeakageArea object.
   *
   * \par EnergyPlus object
   * \epobject{group-airflow.html#zoneinfiltrationeffectiveleakagearea,ZoneInfiltration:EffectiveLeakageArea}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::SpaceInfiltrationEffectiveLeakageArea</code>. <b>Not yet available:</b> the Model <code>schedule()</code>, <code>setSchedule()</code>, and <code>resetSchedule()</code> methods and space/zone relationship APIs. EPModel exposes effective leakage and coefficient scalars.
   *
   * \par Known limitations
   * Only the EnergyPlus scalar fields are directly managed by this wrapper.
   */
  class EPMODEL_API SpaceInfiltrationEffectiveLeakageArea : public ModelObject
  {
   public:
    explicit SpaceInfiltrationEffectiveLeakageArea(const Model& model);

    virtual ~SpaceInfiltrationEffectiveLeakageArea() override = default;
    SpaceInfiltrationEffectiveLeakageArea(const SpaceInfiltrationEffectiveLeakageArea& other) = default;
    SpaceInfiltrationEffectiveLeakageArea(SpaceInfiltrationEffectiveLeakageArea&& other) = default;
    SpaceInfiltrationEffectiveLeakageArea& operator=(const SpaceInfiltrationEffectiveLeakageArea&) = default;
    SpaceInfiltrationEffectiveLeakageArea& operator=(SpaceInfiltrationEffectiveLeakageArea&&) = default;

    static IddObjectType iddObjectType();

    double effectiveAirLeakageArea() const;
    bool setEffectiveAirLeakageArea(double effectiveAirLeakageArea);

    double stackCoefficient() const;
    bool setStackCoefficient(double stackCoefficient);

    double windCoefficient() const;
    bool setWindCoefficient(double windCoefficient);

   protected:
    using ImplType = detail::SpaceInfiltrationEffectiveLeakageArea_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SpaceInfiltrationEffectiveLeakageArea(std::shared_ptr<detail::SpaceInfiltrationEffectiveLeakageArea_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
