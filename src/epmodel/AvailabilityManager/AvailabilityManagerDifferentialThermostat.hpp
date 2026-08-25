/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGERDIFFERENTIALTHERMOSTAT_HPP
#define EPMODEL_AVAILABILITYMANAGERDIFFERENTIALTHERMOSTAT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AvailabilityManagerDifferentialThermostat_Impl;
  }

  /** \brief Controls availability from the temperature difference between hot and cold sensor nodes.
   *
   * \par EnergyPlus object
   * \epobject{group-system-availability-managers.html#availabilitymanagerdifferentialthermostat,AvailabilityManager:DifferentialThermostat}
   *
   * \par Important behavior
   * A newly constructed manager initializes the on and off temperature
   * difference limits to 10.0 and 2.0, respectively.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::AvailabilityManagerDifferentialThermostat</code>.
   *
   * - <b>Not yet available:</b> <code>loop()</code>,
   *   <code>hotNode()</code>, <code>setHotNode(...)</code>,
   *   <code>resetHotNode()</code>, <code>coldNode()</code>,
   *   <code>setColdNode(...)</code>, and <code>resetColdNode()</code>.
   *
   * \par Known limitations
   * The EPModel wrapper currently exposes only the scalar temperature limits.
   * It cannot be passed to typed loop-assignment APIs until its sensor-node
   * relationships and availability-manager base interface are exposed.
   */
  class EPMODEL_API AvailabilityManagerDifferentialThermostat : public ModelObject
  {
   public:
    explicit AvailabilityManagerDifferentialThermostat(const Model& model);

    virtual ~AvailabilityManagerDifferentialThermostat() override = default;
    AvailabilityManagerDifferentialThermostat(const AvailabilityManagerDifferentialThermostat& other) = default;
    AvailabilityManagerDifferentialThermostat(AvailabilityManagerDifferentialThermostat&& other) = default;
    AvailabilityManagerDifferentialThermostat& operator=(const AvailabilityManagerDifferentialThermostat&) = default;
    AvailabilityManagerDifferentialThermostat& operator=(AvailabilityManagerDifferentialThermostat&&) = default;

    static IddObjectType iddObjectType();

    // Temperature difference on limit
    double temperatureDifferenceOnLimit() const;
    bool setTemperatureDifferenceOnLimit(double temperatureDifferenceOnLimit);

    // Temperature difference off limit
    double temperatureDifferenceOffLimit() const;
    bool setTemperatureDifferenceOffLimit(double temperatureDifferenceOffLimit);

   protected:
    using ImplType = detail::AvailabilityManagerDifferentialThermostat_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AvailabilityManagerDifferentialThermostat(std::shared_ptr<detail::AvailabilityManagerDifferentialThermostat_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
