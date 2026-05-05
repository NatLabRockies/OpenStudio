/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_LIFECYCLECOSTUSEADJUSTMENT_HPP
#define EPMODEL_LIFECYCLECOSTUSEADJUSTMENT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class LifeCycleCostUseAdjustment_Impl;
  }

  class EPMODEL_API LifeCycleCostUseAdjustment : public ModelObject
  {
   public:
    explicit LifeCycleCostUseAdjustment(const Model& model);

    virtual ~LifeCycleCostUseAdjustment() override = default;
    LifeCycleCostUseAdjustment(const LifeCycleCostUseAdjustment& other) = default;
    LifeCycleCostUseAdjustment(LifeCycleCostUseAdjustment&& other) = default;
    LifeCycleCostUseAdjustment& operator=(const LifeCycleCostUseAdjustment&) = default;
    LifeCycleCostUseAdjustment& operator=(LifeCycleCostUseAdjustment&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> resourceValues();

    // Schema Alignment Notes:
    // - API: No openstudio::model counterpart exists for this type, so IDD-derived scalar naming is used.
    // - Field Mapping: resource() maps directly to EnergyPlus LifeCycleCost:UseAdjustment "Resource".
    // - Field Mapping: Year multipliers are extensible and intentionally excluded from this scalar-only scaffold pass.
    // - TODO(parity): Add typed extensible year-multiplier APIs if/when extensible scaffold scope is enabled.
    std::string resource() const;

    bool setResource(const std::string& resource);

   protected:
    using ImplType = detail::LifeCycleCostUseAdjustment_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit LifeCycleCostUseAdjustment(std::shared_ptr<detail::LifeCycleCostUseAdjustment_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
