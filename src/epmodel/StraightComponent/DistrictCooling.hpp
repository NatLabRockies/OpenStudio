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
    // - API: Preserve openstudio::model::DistrictCooling scalar accessor names/signatures for counterpart parity.
    // - Field Mapping: nominalCapacity/isNominalCapacityAutosized/setNominalCapacity/autosizeNominalCapacity map to E+ DistrictCooling Nominal Capacity.
    // - ForwardTranslator evidence: ForwardTranslateDistrictCooling.cpp writes model.nominalCapacity()/isNominalCapacityAutosized() to DistrictCooling Nominal Capacity.
    // - Field Mapping: Chilled water node names and Capacity Fraction Schedule are relationship-like fields and excluded in this scalar pass.
    // - TODO(parity): Add excluded relationship APIs without changing preserved scalar signatures.
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
