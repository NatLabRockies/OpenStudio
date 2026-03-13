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
    // - API: Preserve openstudio::model::DistrictHeatingWater scalar accessor names/signatures for counterpart parity.
    // - Field Mapping: nominalCapacity/isNominalCapacityAutosized/setNominalCapacity/autosizeNominalCapacity map to E+ DistrictHeating:Water Nominal Capacity.
    // - ForwardTranslator evidence: ForwardTranslateDistrictHeatingWater.cpp writes model.nominalCapacity()/isNominalCapacityAutosized() to DistrictHeating:Water Nominal Capacity.
    // - Field Mapping: Hot water node names and Capacity Fraction Schedule are relationship-like fields and excluded in this scalar pass.
    // - TODO(parity): Add excluded relationship APIs without changing preserved scalar signatures.
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
