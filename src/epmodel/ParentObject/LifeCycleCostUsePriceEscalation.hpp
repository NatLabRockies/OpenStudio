/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_LIFECYCLECOSTUSEPRICEESCALATION_HPP
#define EPMODEL_LIFECYCLECOSTUSEPRICEESCALATION_HPP

#include "EPModelAPI.hpp"
#include "ParentObject/ParentObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class LifeCycleCostUsePriceEscalation_Impl;
}

class EPMODEL_API LifeCycleCostUsePriceEscalation : public ParentObject
{
 public:
  explicit LifeCycleCostUsePriceEscalation(const Model& model);

  virtual ~LifeCycleCostUsePriceEscalation() override = default;
  LifeCycleCostUsePriceEscalation(const LifeCycleCostUsePriceEscalation& other) = default;
  LifeCycleCostUsePriceEscalation(LifeCycleCostUsePriceEscalation&& other) = default;
  LifeCycleCostUsePriceEscalation& operator=(const LifeCycleCostUsePriceEscalation&) = default;
  LifeCycleCostUsePriceEscalation& operator=(LifeCycleCostUsePriceEscalation&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> resourceValues();
  static std::vector<std::string> escalationStartMonthValues();

  // Schema Alignment Notes:
  // - API: No openstudio::model counterpart is used for this epmodel type in scaffold inventory; IDD-derived scalar naming is applied.
  // - Field Mapping: resource, escalationStartYear, and escalationStartMonth map directly to LifeCycleCost:UsePriceEscalation scalar fields.
  // - Field Mapping: extensible Year 1 Escalation (+ extensible years) is excluded from this scalar-only scaffold pass.
  // - TODO(parity): Add typed extensible escalation-year APIs if/when extensible scaffold scope is enabled.
  std::string resource() const;
  bool setResource(const std::string& resource);

  boost::optional<int> escalationStartYear() const;
  bool setEscalationStartYear(int escalationStartYear);
  void resetEscalationStartYear();

  std::string escalationStartMonth() const;
  bool isEscalationStartMonthDefaulted() const;
  bool setEscalationStartMonth(const std::string& escalationStartMonth);
  void resetEscalationStartMonth();

 protected:
  using ImplType = detail::LifeCycleCostUsePriceEscalation_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit LifeCycleCostUsePriceEscalation(std::shared_ptr<detail::LifeCycleCostUsePriceEscalation_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
