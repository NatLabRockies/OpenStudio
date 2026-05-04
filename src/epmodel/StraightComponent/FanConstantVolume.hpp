/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FANCONSTANTVOLUME_HPP
#define EPMODEL_FANCONSTANTVOLUME_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;

  namespace detail {
    class FanConstantVolume_Impl;
  }

  class EPMODEL_API FanConstantVolume : public StraightComponent
  {
   public:
    explicit FanConstantVolume(const Model& model);
    FanConstantVolume(const Model& model, Schedule& schedule);

    virtual ~FanConstantVolume() override = default;
    FanConstantVolume(const FanConstantVolume& other) = default;
    FanConstantVolume(FanConstantVolume&& other) = default;
    FanConstantVolume& operator=(const FanConstantVolume&) = default;
    FanConstantVolume& operator=(FanConstantVolume&&) = default;

    static IddObjectType iddObjectType();

    bool addToNode(Node& node);

    // Schema Alignment Notes:
    // - Status: Near Parity. The canonical scalar field behavior, availability-schedule constructors, and node insertion are aligned, while the airflow-network helper surface remains absent.
    // - Canonical Counterpart: openstudio::model::FanConstantVolume.
    // - Implemented Parity: The canonical constructors plus the availability-schedule, fan total-efficiency, fan-efficiency, pressure-rise, maximum-flow-rate, motor, and end-use-subcategory accessors preserve the canonical scalar field behavior, including autosize/reset semantics for flow rate.
    // - Documented Delta: Epmodel still omits the airflow-network fan relationship helpers and autosized-maximum-flow-rate convenience from `openstudio::model::FanConstantVolume`.
    // - Field/Storage Mapping: The availability schedule is represented as a typed `Schedule` relationship, while the scalar fields map directly to `Fan:ConstantVolume` storage in EnergyPlus.
    // - Evidence: `src/model/FanConstantVolume.hpp`, `src/model/FanConstantVolume.cpp`, `src/model/test/FanConstantVolume_GTest.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateFanConstantVolume.cpp` establish the canonical API and translation behavior.
    // - Remaining Parity Work: Add airflow-network relationship support and the autosized flow-rate convenience once epmodel grows the corresponding fan helper surface cleanly.
    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    double fanTotalEfficiency() const;
    bool setFanTotalEfficiency(double fanTotalEfficiency);

    double fanEfficiency() const;
    bool setFanEfficiency(double fanEfficiency);

    double pressureRise() const;
    bool setPressureRise(double pressureRise);

    boost::optional<double> maximumFlowRate() const;
    bool setMaximumFlowRate(double maximumFlowRate);
    void resetMaximumFlowRate();
    void autosizeMaximumFlowRate();
    bool isMaximumFlowRateAutosized() const;

    double motorEfficiency() const;
    bool setMotorEfficiency(double motorEfficiency);

    double motorInAirstreamFraction() const;
    bool setMotorInAirstreamFraction(double motorInAirstreamFraction);

    std::string endUseSubcategory() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);

   protected:
    using ImplType = detail::FanConstantVolume_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit FanConstantVolume(std::shared_ptr<detail::FanConstantVolume_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
