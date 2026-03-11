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
    // - API: Preserve openstudio::model::SwimmingPoolIndoor scalar accessor names/signatures for counterpart parity.
    // - Field Mapping: The scalar accessors map directly to EnergyPlus SwimmingPool:Indoor fields (Average Depth, Cover* factors, Pool Heating System Maximum Water Flow Rate, Pool Miscellaneous Equipment Power, Maximum Number of People).
    // - Relationship fields (Surface Name, all Schedule/Node references) are intentionally excluded from scalar accessors in this pass.
    // - ForwardTranslator evidence: ForwardTranslateSwimmingPoolIndoor.cpp writes these scalar fields before handling schedules/nodes.
    // - TODO(parity): Add the excluded relationship APIs (surface/schedule/node references) once the scalar surface is saturated.
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
