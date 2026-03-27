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
    // - Status: Scalar Parity. The canonical electric-coil scalar surface is largely present, while schedule and node-link helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::CoilHeatingElectric.
    // - Implemented Parity: `efficiency` and `nominalCapacity` preserve the canonical scalar API and autosize behavior.
    // - Documented Delta: Availability schedule, temperature-setpoint node, and other relationship helpers from canonical `openstudio::model::CoilHeatingElectric` are not exposed yet.
    // - Field/Storage Mapping: Preserved scalars map directly to EnergyPlus `Coil:Heating:Electric` fields.
    // - Evidence: `src/model/CoilHeatingElectric.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingElectric.cpp`, and `src/epmodel/test/CoilHeatingElectric_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted schedule and node-link helpers without changing the preserved scalar signatures.

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
