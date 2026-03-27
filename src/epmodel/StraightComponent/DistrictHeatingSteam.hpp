/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DISTRICTHEATINGSTEAM_HPP
#define EPMODEL_DISTRICTHEATINGSTEAM_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class DistrictHeatingSteam_Impl;
  }

  class EPMODEL_API DistrictHeatingSteam : public StraightComponent
  {
   public:
    explicit DistrictHeatingSteam(const Model& model);

    virtual ~DistrictHeatingSteam() override = default;
    DistrictHeatingSteam(const DistrictHeatingSteam& other) = default;
    DistrictHeatingSteam(DistrictHeatingSteam&& other) = default;
    DistrictHeatingSteam& operator=(const DistrictHeatingSteam&) = default;
    DistrictHeatingSteam& operator=(DistrictHeatingSteam&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Scalar Parity. The canonical district-heating-steam scalar surface is present, while node and schedule helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::DistrictHeatingSteam.
    // - Implemented Parity: The preserved scalar API matches the nominal-capacity accessor set, including autosize behavior.
    // - Documented Delta: Steam inlet/outlet node names and the capacity-fraction schedule remain intentionally excluded from this scalar pass.
    // - Field/Storage Mapping: These accessors map directly to the EnergyPlus `DistrictHeating:Steam` nominal-capacity field used by the forward translator.
    // - Evidence: `src/model/DistrictHeatingSteam.hpp`, `src/model/DistrictHeatingSteam.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateDistrictHeatingSteam.cpp`.
    // - Remaining Parity Work: Add the omitted relationship helpers without changing the preserved scalar signatures.
    boost::optional<double> nominalCapacity() const;
    bool setNominalCapacity(double nominalCapacity);
    void autosizeNominalCapacity();
    boost::optional<double> autosizedNominalCapacity() const;
    bool isNominalCapacityAutosized() const;

   protected:
    using ImplType = detail::DistrictHeatingSteam_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit DistrictHeatingSteam(std::shared_ptr<detail::DistrictHeatingSteam_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
