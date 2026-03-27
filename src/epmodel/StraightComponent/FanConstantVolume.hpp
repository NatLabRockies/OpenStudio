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

  namespace detail {
    class FanConstantVolume_Impl;
  }

  class EPMODEL_API FanConstantVolume : public StraightComponent
  {
   public:
    explicit FanConstantVolume(const Model& model);

    virtual ~FanConstantVolume() override = default;
    FanConstantVolume(const FanConstantVolume& other) = default;
    FanConstantVolume(FanConstantVolume&& other) = default;
    FanConstantVolume& operator=(const FanConstantVolume&) = default;
    FanConstantVolume& operator=(FanConstantVolume&&) = default;

    static IddObjectType iddObjectType();

    bool addToNode(Node& node);

    // Schema Alignment Notes:
    // - Status: Partial Parity. Scalar fan properties and node insertion are aligned, but the canonical schedule and airflow-network surface is still absent.
    // - Canonical Counterpart: openstudio::model::FanConstantVolume.
    // - Implemented Parity: The fan total-efficiency, fan-efficiency, pressure-rise, maximum-flow-rate, motor, and end-use-subcategory accessors preserve the canonical scalar field behavior, including autosize/reset semantics for flow rate.
    // - Documented Delta: Epmodel does not yet expose the canonical availability-schedule constructor/accessors or the airflow-network fan relationship helpers that remain on `openstudio::model::FanConstantVolume`.
    // - Field/Storage Mapping: Scalar fields map directly to `Fan:ConstantVolume` storage in EnergyPlus.
    // - Evidence: `src/model/FanConstantVolume.hpp`, `src/model/FanConstantVolume.cpp`, `src/model/test/FanConstantVolume_GTest.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateFanConstantVolume.cpp` establish the canonical API and translation behavior.
    // - Remaining Parity Work: Add availability-schedule and airflow-network relationship support once epmodel relationship parity is broad enough to hold it without ad hoc shims.
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

    friend class openstudio::epmodel::Model;

    explicit FanConstantVolume(std::shared_ptr<detail::FanConstantVolume_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
