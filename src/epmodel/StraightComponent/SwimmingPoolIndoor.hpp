/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SWIMMINGPOOLINDOOR_HPP
#define EPMODEL_SWIMMINGPOOLINDOOR_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace boost {
template <typename T>
class optional;
}

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SwimmingPoolIndoor_Impl;
  }

  class EPMODEL_API SwimmingPoolIndoor : public StraightComponent
  {
   public:
    explicit SwimmingPoolIndoor(const Model& model);

    virtual ~SwimmingPoolIndoor() override = default;
    SwimmingPoolIndoor(const SwimmingPoolIndoor& other) = default;
    SwimmingPoolIndoor(SwimmingPoolIndoor&& other) = default;
    SwimmingPoolIndoor& operator=(const SwimmingPoolIndoor&) = default;
    SwimmingPoolIndoor& operator=(SwimmingPoolIndoor&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Scalar Parity. The canonical indoor-swimming-pool scalar surface is present, while surface, schedule, and node helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::SwimmingPoolIndoor.
    // - Implemented Parity: The preserved scalar API matches the cover-factor, heating-flow, miscellaneous-power, depth, and occupancy accessors with matching default behavior.
    // - Documented Delta: Surface-name and all schedule/node helpers remain intentionally excluded from this scalar pass.
    // - Field/Storage Mapping: These accessors map directly to EnergyPlus `SwimmingPool:Indoor` scalar fields used by the forward translator.
    // - Evidence: `src/model/SwimmingPoolIndoor.hpp`, `src/model/SwimmingPoolIndoor.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateSwimmingPoolIndoor.cpp`.
    // - Remaining Parity Work: Add the omitted relationship helpers without changing the preserved scalar signatures.
    double averageDepth() const;
    bool setAverageDepth(double averageDepth);

    double coverEvaporationFactor() const;
    bool isCoverEvaporationFactorDefaulted() const;
    bool setCoverEvaporationFactor(double coverEvaporationFactor);
    void resetCoverEvaporationFactor();

    double coverConvectionFactor() const;
    bool isCoverConvectionFactorDefaulted() const;
    bool setCoverConvectionFactor(double coverConvectionFactor);
    void resetCoverConvectionFactor();

    double coverShortWavelengthRadiationFactor() const;
    bool isCoverShortWavelengthRadiationFactorDefaulted() const;
    bool setCoverShortWavelengthRadiationFactor(double coverShortWavelengthRadiationFactor);
    void resetCoverShortWavelengthRadiationFactor();

    double coverLongWavelengthRadiationFactor() const;
    bool isCoverLongWavelengthRadiationFactorDefaulted() const;
    bool setCoverLongWavelengthRadiationFactor(double coverLongWavelengthRadiationFactor);
    void resetCoverLongWavelengthRadiationFactor();

    boost::optional<double> poolHeatingSystemMaximumWaterFlowRate() const;
    bool setPoolHeatingSystemMaximumWaterFlowRate(double poolHeatingSystemMaximumWaterFlowRate);
    void resetPoolHeatingSystemMaximumWaterFlowRate();

    boost::optional<double> poolMiscellaneousEquipmentPower() const;
    bool setPoolMiscellaneousEquipmentPower(double poolMiscellaneousEquipmentPower);
    void resetPoolMiscellaneousEquipmentPower();

    double maximumNumberofPeople() const;
    bool setMaximumNumberofPeople(double maximumNumberofPeople);

   protected:
    using ImplType = detail::SwimmingPoolIndoor_Impl;

    explicit SwimmingPoolIndoor(std::shared_ptr<detail::SwimmingPoolIndoor_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
