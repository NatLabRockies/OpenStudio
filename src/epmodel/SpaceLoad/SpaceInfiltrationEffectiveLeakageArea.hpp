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

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model scalar accessor names for the SpaceInfiltrationEffectiveLeakageArea counterpart.
    // - Field Mapping: effectiveAirLeakageArea, stackCoefficient, and windCoefficient map directly to
    //   ZoneInfiltration:EffectiveLeakageArea.
    // - Field Mapping: Schedule/Zone/Space object relationships are intentionally excluded from this scalar-only API.
    // - ForwardTranslator evidence: translateSpaceInfiltrationEffectiveLeakageArea writes these scalar values directly onto
    //   ZoneInfiltration:EffectiveLeakageArea.
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
