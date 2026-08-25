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

  /** \brief Represents the EnergyPlus ZoneInfiltration:FlowCoefficient object.
   *
   * \par EnergyPlus object
   * \epobject{group-airflow.html#zoneinfiltrationflowcoefficient,ZoneInfiltration:FlowCoefficient}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::SpaceInfiltrationFlowCoefficient</code>. <b>Not yet available:</b> the Model <code>schedule()</code>, <code>setSchedule()</code>, and <code>resetSchedule()</code> methods and space/zone relationship APIs. EPModel exposes flow, pressure, wind, and shelter scalars.
   *
   * \par Known limitations
   * The pressure exponent has EnergyPlus default/reset behavior; relationship assignment remains outside this scalar wrapper.
   */
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

    double flowCoefficient() const;
    bool setFlowCoefficient(double flowCoefficient);

    double stackCoefficient() const;
    bool setStackCoefficient(double stackCoefficient);

    double pressureExponent() const;
    bool isPressureExponentDefaulted() const;
    bool setPressureExponent(double pressureExponent);
    void resetPressureExponent();

    double windCoefficient() const;
    bool setWindCoefficient(double windCoefficient);

    double shelterFactor() const;
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
