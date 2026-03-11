/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_ROOFIRRIGATION_HPP
#define EPMODEL_ROOFIRRIGATION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class RoofIrrigation_Impl;
  }

  class EPMODEL_API RoofIrrigation : public ModelObject
  {
   public:
    explicit RoofIrrigation(const Model& model);

    virtual ~RoofIrrigation() override = default;
    RoofIrrigation(const RoofIrrigation& other) = default;
    RoofIrrigation(RoofIrrigation&& other) = default;
    RoofIrrigation& operator=(const RoofIrrigation&) = default;
    RoofIrrigation& operator=(RoofIrrigation&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> irrigationModelTypeValues();

    // Schema Alignment Notes:
    // - API: IDD-only RoofIrrigation retains IDD-derived naming to mirror generator behavior.
    // - Field Mapping: irrigationModelType maps to RoofIrrigation.Irrigation Model Type (choice) with helper values from IddFactory/getIddKeyNames.
    // - Field Mapping: irrigationMaximumSaturationThreshold maps to RoofIrrigation.Irrigation Maximum Saturation Threshold (percent, default 40.0).
    // - Field Mapping: Irrigation Rate Schedule Name is an object-list relationship and is intentionally excluded from scalar accessors.
    // - TODO(parity): Add relationship helpers for schedules when non-scalar coverage expands.
    boost::optional<std::string> irrigationModelType() const;
    bool setIrrigationModelType(const std::string& irrigationModelType);
    void resetIrrigationModelType();

    double irrigationMaximumSaturationThreshold() const;
    bool isIrrigationMaximumSaturationThresholdDefaulted() const;
    bool setIrrigationMaximumSaturationThreshold(double irrigationMaximumSaturationThreshold);
    void resetIrrigationMaximumSaturationThreshold();

   protected:
    using ImplType = detail::RoofIrrigation_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit RoofIrrigation(std::shared_ptr<detail::RoofIrrigation_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
