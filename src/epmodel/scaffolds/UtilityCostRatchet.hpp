/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_UTILITYCOSTRATCHET_HPP
#define EPMODEL_UTILITYCOSTRATCHET_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class UtilityCostRatchet_Impl;
  }

  class EPMODEL_API UtilityCostRatchet : public ModelObject
  {
   public:
    explicit UtilityCostRatchet(const Model& model);

    virtual ~UtilityCostRatchet() override = default;
    UtilityCostRatchet(const UtilityCostRatchet& other) = default;
    UtilityCostRatchet(UtilityCostRatchet&& other) = default;
    UtilityCostRatchet& operator=(const UtilityCostRatchet&) = default;
    UtilityCostRatchet& operator=(UtilityCostRatchet&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> seasonFromValues();
    static std::vector<std::string> seasonToValues();

    // Schema Alignment Notes:
    // - API: No openstudio::model counterpart exists, so naming mirrors the EnergyPlus UtilityCost:Ratchet IDD.
    // - Field Mapping: Baseline Source Variable, Adjustment Source Variable, Season From, Season To,
    //   Multiplier Value or Variable Name, and Offset Value or Variable Name map directly to UtilityCost:Ratchet.
    // - Field Mapping: Tariff Name is an object-list relationship and is intentionally excluded in this scalar pass.
    std::string baselineSourceVariable() const;
    bool setBaselineSourceVariable(const std::string& baselineSourceVariable);

    std::string adjustmentSourceVariable() const;
    bool setAdjustmentSourceVariable(const std::string& adjustmentSourceVariable);

    std::string seasonFrom() const;
    bool setSeasonFrom(const std::string& seasonFrom);

    std::string seasonTo() const;
    bool setSeasonTo(const std::string& seasonTo);

    boost::optional<std::string> multiplierValueorVariableName() const;
    bool setMultiplierValueorVariableName(const std::string& multiplierValueorVariableName);
    void resetMultiplierValueorVariableName();

    boost::optional<std::string> offsetValueorVariableName() const;
    bool setOffsetValueorVariableName(const std::string& offsetValueorVariableName);
    void resetOffsetValueorVariableName();

   protected:
    using ImplType = detail::UtilityCostRatchet_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit UtilityCostRatchet(std::shared_ptr<detail::UtilityCostRatchet_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
