/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGEROPTIMUMSTART_HPP
#define EPMODEL_AVAILABILITYMANAGEROPTIMUMSTART_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AvailabilityManagerOptimumStart_Impl;
  }

  class EPMODEL_API AvailabilityManagerOptimumStart : public ModelObject
  {
   public:
    explicit AvailabilityManagerOptimumStart(const Model& model);

    virtual ~AvailabilityManagerOptimumStart() override = default;
    AvailabilityManagerOptimumStart(const AvailabilityManagerOptimumStart& other) = default;
    AvailabilityManagerOptimumStart(AvailabilityManagerOptimumStart&& other) = default;
    AvailabilityManagerOptimumStart& operator=(const AvailabilityManagerOptimumStart&) = default;
    AvailabilityManagerOptimumStart& operator=(AvailabilityManagerOptimumStart&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlTypeValues();
    static std::vector<std::string> controlAlgorithmValues();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model scalar accessor names/signatures for this model-counterpart class.
    // - Field Mapping: controlType/controlAlgorithm and numeric gradient/start-time fields map directly to
    //   E+ AvailabilityManager:OptimumStart scalar fields.
    // - ForwardTranslator evidence: model::ForwardTranslateAvailabilityManagerOptimumStart writes these
    //   same scalar fields directly (ControlType, MaximumValueforOptimumStartTime, ControlAlgorithm,
    //   Constant/Initial Temperature Gradients, ConstantStartTime, NumberofPreviousDays).
    // - TODO(parity): Keep relationship/link fields (Applicability Schedule Name, Fan Schedule Name,
    //   Control Zone Name, Zone List Name) out of this scalar-only scaffold pass.
    std::string controlType() const;
    bool setControlType(const std::string& controlType);

    double maximumValueforOptimumStartTime() const;
    bool setMaximumValueforOptimumStartTime(double maximumValueforOptimumStartTime);

    std::string controlAlgorithm() const;
    bool setControlAlgorithm(const std::string& controlAlgorithm);

    double constantTemperatureGradientduringCooling() const;
    bool setConstantTemperatureGradientduringCooling(double constantTemperatureGradientduringCooling);

    double constantTemperatureGradientduringHeating() const;
    bool setConstantTemperatureGradientduringHeating(double constantTemperatureGradientduringHeating);

    double initialTemperatureGradientduringCooling() const;
    bool setInitialTemperatureGradientduringCooling(double initialTemperatureGradientduringCooling);

    double initialTemperatureGradientduringHeating() const;
    bool setInitialTemperatureGradientduringHeating(double initialTemperatureGradientduringHeating);

    double constantStartTime() const;
    bool setConstantStartTime(double constantStartTime);

    int numberofPreviousDays() const;
    bool setNumberofPreviousDays(int numberofPreviousDays);

   protected:
    using ImplType = detail::AvailabilityManagerOptimumStart_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AvailabilityManagerOptimumStart(std::shared_ptr<detail::AvailabilityManagerOptimumStart_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
