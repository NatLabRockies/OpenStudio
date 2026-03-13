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
    // - API: Preserve openstudio::model::CoilHeatingElectric scalar accessor names/signatures.
    // - Field Mapping: efficiency maps to E+ Coil:Heating:Electric Efficiency.
    // - Field Mapping: nominalCapacity maps to E+ Coil:Heating:Electric Nominal Capacity.
    // - Field Mapping: Relationship-like fields (availability schedule, temperature setpoint node, and air node links) are excluded in this pass.
    // - ForwardTranslator evidence: ForwardTranslateCoilHeatingElectric.cpp writes Efficiency and Nominal Capacity directly.
    // - TODO(parity): Add excluded relationship APIs without changing preserved scalar signatures.

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
