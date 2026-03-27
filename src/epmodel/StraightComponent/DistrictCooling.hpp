/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DISTRICTCOOLING_HPP
#define EPMODEL_DISTRICTCOOLING_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class DistrictCooling_Impl;
  }

  class EPMODEL_API DistrictCooling : public StraightComponent
  {
   public:
    explicit DistrictCooling(const Model& model);

    virtual ~DistrictCooling() override = default;
    DistrictCooling(const DistrictCooling& other) = default;
    DistrictCooling(DistrictCooling&& other) = default;
    DistrictCooling& operator=(const DistrictCooling&) = default;
    DistrictCooling& operator=(DistrictCooling&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Scalar Parity. The canonical district-cooling scalar surface is present, while node and schedule helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::DistrictCooling.
    // - Implemented Parity: The preserved scalar API matches the nominal-capacity accessor set, including autosize behavior.
    // - Documented Delta: Chilled-water node names and the capacity-fraction schedule remain intentionally excluded from this scalar pass.
    // - Field/Storage Mapping: These accessors map directly to the EnergyPlus `DistrictCooling` nominal-capacity field used by the forward translator.
    // - Evidence: `src/model/DistrictCooling.hpp`, `src/model/DistrictCooling.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateDistrictCooling.cpp`.
    // - Remaining Parity Work: Add the omitted relationship helpers without changing the preserved scalar signatures.
    boost::optional<double> nominalCapacity() const;

    bool setNominalCapacity(double nominalCapacity);
    void autosizeNominalCapacity();
    bool isNominalCapacityAutosized() const;

    boost::optional<double> autosizedNominalCapacity() const;

   protected:
    using ImplType = detail::DistrictCooling_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit DistrictCooling(std::shared_ptr<detail::DistrictCooling_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
