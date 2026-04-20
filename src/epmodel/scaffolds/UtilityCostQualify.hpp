/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_UTILITYCOSTQUALIFY_HPP
#define EPMODEL_UTILITYCOSTQUALIFY_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class UtilityCostQualify_Impl;
  }

  class EPMODEL_API UtilityCostQualify : public ModelObject
  {
   public:
    explicit UtilityCostQualify(const Model& model);

    virtual ~UtilityCostQualify() override = default;
    UtilityCostQualify(const UtilityCostQualify& other) = default;
    UtilityCostQualify(UtilityCostQualify&& other) = default;
    UtilityCostQualify& operator=(const UtilityCostQualify&) = default;
    UtilityCostQualify& operator=(UtilityCostQualify&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> qualifyTypeValues();
    static std::vector<std::string> seasonValues();
    static std::vector<std::string> thresholdTestValues();

    // Schema Alignment Notes:
    // - API: No openstudio::model counterpart exists, so naming mirrors the EnergyPlus UtilityCost:Qualify IDD.
    // - Field Mapping: variableName, qualifyType, thresholdValueorVariableName, season, thresholdTest, and numberOfMonths map directly to UtilityCost:Qualify fields.
    // - Field Mapping: Tariff Name is an object-list relationship; the helper is deferred until UtilityCostTariff scaffolding arrives.
    // - Field Mapping: Season defaults to Annual when blank, Threshold Test choices are Count/Consecutive, and Number of Months falls back to 12 or 1 depending on qualify type.
    // - TODO(parity): Add relationship helpers once Tariff scaffolding is available.
    std::string variableName() const;
    bool setVariableName(const std::string& variableName);

    std::string qualifyType() const;
    bool setQualifyType(const std::string& qualifyType);

    std::string thresholdValueorVariableName() const;
    bool setThresholdValueorVariableName(const std::string& thresholdValueorVariableName);

    std::string season() const;
    bool setSeason(const std::string& season);
    bool isSeasonDefaulted() const;
    void resetSeason();

    std::string thresholdTest() const;
    bool setThresholdTest(const std::string& thresholdTest);

    int numberOfMonths() const;
    bool setNumberOfMonths(int numberOfMonths);
    bool isNumberOfMonthsDefaulted() const;
    void resetNumberOfMonths();

   protected:
    using ImplType = detail::UtilityCostQualify_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit UtilityCostQualify(std::shared_ptr<detail::UtilityCostQualify_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
