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
    explicit CoilHeatingElectric(const Model& model);

    virtual ~CoilHeatingElectric() override = default;
    CoilHeatingElectric(const CoilHeatingElectric& other) = default;
    CoilHeatingElectric(CoilHeatingElectric&& other) = default;
    CoilHeatingElectric& operator=(const CoilHeatingElectric&) = default;
    CoilHeatingElectric& operator=(CoilHeatingElectric&&) = default;

    static IddObjectType iddObjectType();

    bool addToNode(Node& node);

    // Schema Alignment Notes:
    // - Status: Partial Parity. The canonical electric-coil scalar surface plus the required availability-schedule and optional temperature-setpoint-node
    //   relationships are present, while broader AFN helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::CoilHeatingElectric.
    // - Implemented Parity: `efficiency` and `nominalCapacity` preserve the canonical scalar API and autosize behavior; `availabilitySchedule` and
    //   `temperatureSetpointNode` preserve the bounded relationship slice; `addToNode` preserves the current epmodel supply-side and OA-system insertion
    //   paths.
    // - Documented Delta: AFN helpers from canonical `openstudio::model::CoilHeatingElectric` are not exposed yet.
    // - Field/Storage Mapping: Preserved scalars and relationships map directly to EnergyPlus `Coil:Heating:Electric` fields.
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
