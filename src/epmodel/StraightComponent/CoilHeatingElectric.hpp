/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGELECTRIC_HPP
#define EPMODEL_COILHEATINGELECTRIC_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;

  namespace detail {
    class CoilHeatingElectric_Impl;
  }

  /** \brief Represents a electric heating coil.
   *
   * \par EnergyPlus object
   * \epobject{group-heating-and-cooling-coils.html#coilheatingelectric,Coil:Heating:Electric}.
   *
   * \par Important behavior
   * The one-argument constructor uses an always-on availability schedule; direct IDF data may still contain blank availability.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::CoilHeatingElectric</code>.
   * Not yet available: AirflowNetwork helpers.
   *
   * \par Known limitations
   * No known EPModel-specific limitations beyond the listed API differences.
   */
  class EPMODEL_API CoilHeatingElectric : public StraightComponent
  {
   public:
    explicit CoilHeatingElectric(const Model& model, Schedule& schedule);
    explicit CoilHeatingElectric(const Model& model);

    virtual ~CoilHeatingElectric() override = default;
    CoilHeatingElectric(const CoilHeatingElectric& other) = default;
    CoilHeatingElectric(CoilHeatingElectric&& other) = default;
    CoilHeatingElectric& operator=(const CoilHeatingElectric&) = default;
    CoilHeatingElectric& operator=(CoilHeatingElectric&&) = default;

    static IddObjectType iddObjectType();

    bool addToNode(Node& node);

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    boost::optional<Node> temperatureSetpointNode() const;
    bool setTemperatureSetpointNode(Node& temperatureSetpointNode);
    void resetTemperatureSetpointNode();

    /** Efficiency */
    double efficiency() const;
    bool isEfficiencyDefaulted() const;
    bool setEfficiency(double efficiency);
    void resetEfficiency();

    /** Nominal capacity */
    boost::optional<double> nominalCapacity() const;
    bool isNominalCapacityDefaulted() const;
    bool isNominalCapacityAutosized() const;
    bool setNominalCapacity(double nominalCapacity);
    void resetNominalCapacity();
    void autosizeNominalCapacity();
    boost::optional<double> autosizedNominalCapacity() const;

   protected:
    using ImplType = detail::CoilHeatingElectric_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilHeatingElectric(std::shared_ptr<detail::CoilHeatingElectric_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
