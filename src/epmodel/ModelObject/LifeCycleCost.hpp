/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_LIFECYCLECOST_HPP
#define EPMODEL_LIFECYCLECOST_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class LifeCycleCost_Impl;
  }

  class EPMODEL_API LifeCycleCost : public ModelObject
  {
   public:
    explicit LifeCycleCost(const Model& model);

    virtual ~LifeCycleCost() override = default;
    LifeCycleCost(const LifeCycleCost& other) = default;
    LifeCycleCost(LifeCycleCost&& other) = default;
    LifeCycleCost& operator=(const LifeCycleCost&) = default;
    LifeCycleCost& operator=(LifeCycleCost&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> validCategoryValues();
    static std::vector<std::string> validStartOfCostsValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model LifeCycleCost scalar accessor naming/signatures where they map to current schema.
    // - Field Mapping: This scaffold targets EnergyPlus LifeCycleCost:RecurringCosts and maps category/cost/start-of-costs/years/months/repeat-period fields directly.
    // - Field Mapping: item/itemType/costUnits APIs remain excluded in this scalar pass because they are OpenStudio object-link semantics, not direct E+ scalar fields.
    // - TODO(parity): Add annual escalation rate only if/when openstudio::model counterpart surface is intentionally expanded.

    std::string category() const;
    bool setCategory(const std::string& category);

    double cost() const;
    bool setCost(double cost);

    std::string startOfCosts() const;
    bool isStartOfCostsDefaulted() const;
    bool setStartOfCosts(const std::string& startOfCosts);
    void resetStartOfCosts();

    int yearsFromStart() const;
    bool isYearsFromStartDefaulted() const;
    bool setYearsFromStart(int yearsFromStart);
    void resetYearsFromStart();

    int monthsFromStart() const;
    bool isMonthsFromStartDefaulted() const;
    bool setMonthsFromStart(int monthsFromStart);
    void resetMonthsFromStart();

    int repeatPeriodYears() const;
    bool isRepeatPeriodYearsDefaulted() const;
    bool setRepeatPeriodYears(int repeatPeriodYears);
    void resetRepeatPeriodYears();

    int repeatPeriodMonths() const;
    bool isRepeatPeriodMonthsDefaulted() const;
    bool setRepeatPeriodMonths(int repeatPeriodMonths);
    void resetRepeatPeriodMonths();

   protected:
    using ImplType = detail::LifeCycleCost_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit LifeCycleCost(std::shared_ptr<detail::LifeCycleCost_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
