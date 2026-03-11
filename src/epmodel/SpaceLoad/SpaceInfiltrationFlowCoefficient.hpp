/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SPACEINFILTRATIONFLOWCOEFFICIENT_HPP
#define EPMODEL_SPACEINFILTRATIONFLOWCOEFFICIENT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SpaceInfiltrationFlowCoefficient_Impl;
  }

  class EPMODEL_API SpaceInfiltrationFlowCoefficient : public ModelObject
  {
   public:
    explicit SpaceInfiltrationFlowCoefficient(const Model& model);

    virtual ~SpaceInfiltrationFlowCoefficient() override = default;
    SpaceInfiltrationFlowCoefficient(const SpaceInfiltrationFlowCoefficient& other) = default;
    SpaceInfiltrationFlowCoefficient(SpaceInfiltrationFlowCoefficient&& other) = default;
    SpaceInfiltrationFlowCoefficient& operator=(const SpaceInfiltrationFlowCoefficient&) = default;
    SpaceInfiltrationFlowCoefficient& operator=(SpaceInfiltrationFlowCoefficient&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model scalar accessor names for the SpaceInfiltrationFlowCoefficient counterpart.
    // - Field Mapping: flowCoefficient, stackCoefficient, pressureExponent, windCoefficient, and shelterFactor map
    //   directly to ZoneInfiltration:FlowCoefficient.
    // - Field Mapping: Zone/Space relationships plus ScheduleName are intentionally excluded from this scalar-only API.
    // - ForwardTranslator evidence: translateSpaceInfiltrationFlowCoefficient writes these scalar values directly to
    //   the EnergyPlus object.
    double flowCoefficient() const;
    double stackCoefficient() const;
    double pressureExponent() const;
    bool isPressureExponentDefaulted() const;
    double windCoefficient() const;
    double shelterFactor() const;

    bool setFlowCoefficient(double flowCoefficient);
    bool setStackCoefficient(double stackCoefficient);
    bool setPressureExponent(double pressureExponent);
    void resetPressureExponent();
    bool setWindCoefficient(double windCoefficient);
    bool setShelterFactor(double shelterFactor);

   protected:
    using ImplType = detail::SpaceInfiltrationFlowCoefficient_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SpaceInfiltrationFlowCoefficient(std::shared_ptr<detail::SpaceInfiltrationFlowCoefficient_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
