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

    // Schema Alignment Notes:
    // - Status: Partial Parity. The canonical electric-coil scalar surface plus the availability-schedule and optional temperature-setpoint-node
    //   relationships are present, while broader AFN helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::CoilHeatingElectric.
    // - Implemented Parity: `efficiency` and `nominalCapacity` preserve the canonical scalar API and autosize behavior; the canonical schedule
    //   constructor and typed `availabilitySchedule` relationship preserve the canonical availability slice; `temperatureSetpointNode` and `addToNode`
    //   preserve the existing epmodel node relationship and supply-side/OA-system insertion paths.
    // - Documented Delta: The one-argument constructor remains as an EnergyPlus-compatible convenience that selects always-on availability. AFN helpers
    //   from canonical `openstudio::model::CoilHeatingElectric` are not exposed yet.
    // - Field/Storage Mapping: Preserved scalars and relationships map directly to EnergyPlus `Coil:Heating:Electric` fields. EnergyPlus A2 is optional,
    //   with blank meaning always-on; epmodel canonical form materializes that meaning as a managed schedule relationship.
    // - Canonicalization: Ordinary availability access is observational. Managed relationships are revalidated through the typed setter and unique
    //   eligible persisted names are reattached. Only truly blank availability is repaired to always-on; malformed nonblank evidence is preserved and
    //   reported. Existing temperature-setpoint-node, topology, and scalar behavior is unchanged.
    // - Evidence: `src/model/CoilHeatingElectric.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingElectric.cpp`, and `src/epmodel/test/CoilHeatingElectric_GTest.cpp`.
    // - Remaining Parity Work: Add AFN helpers without changing the preserved scalar signatures.
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
