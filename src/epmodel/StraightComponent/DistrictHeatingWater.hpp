/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DISTRICTHEATINGWATER_HPP
#define EPMODEL_DISTRICTHEATINGWATER_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class DistrictHeatingWater_Impl;
  }

  class EPMODEL_API DistrictHeatingWater : public StraightComponent
  {
   public:
    explicit DistrictHeatingWater(const Model& model);

    virtual ~DistrictHeatingWater() override = default;
    DistrictHeatingWater(const DistrictHeatingWater& other) = default;
    DistrictHeatingWater(DistrictHeatingWater&& other) = default;
    DistrictHeatingWater& operator=(const DistrictHeatingWater&) = default;
    DistrictHeatingWater& operator=(DistrictHeatingWater&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Scalar Parity. The canonical district-heating-water scalar surface is present, while node and schedule helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::DistrictHeatingWater.
    // - Implemented Parity: The preserved scalar API matches the nominal-capacity accessor set, including autosize behavior.
    // - Documented Delta: Hot-water node names and the capacity-fraction schedule remain intentionally excluded from this scalar pass.
    // - Field/Storage Mapping: These accessors map directly to the EnergyPlus `DistrictHeating:Water` nominal-capacity field used by the forward translator.
    // - Evidence: `src/model/DistrictHeatingWater.hpp`, `src/model/DistrictHeatingWater.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateDistrictHeatingWater.cpp`.
    // - Remaining Parity Work: Add the omitted relationship helpers without changing the preserved scalar signatures.
    boost::optional<double> nominalCapacity() const;
    bool isNominalCapacityAutosized() const;
    boost::optional<double> autosizedNominalCapacity() const;

    bool setNominalCapacity(double nominalCapacity);
    void autosizeNominalCapacity();

   protected:
    using ImplType = detail::DistrictHeatingWater_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit DistrictHeatingWater(std::shared_ptr<detail::DistrictHeatingWater_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
