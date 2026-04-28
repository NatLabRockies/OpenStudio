/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_UTILITYCOSTCHARGEBLOCK_HPP
#define EPMODEL_UTILITYCOSTCHARGEBLOCK_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class UtilityCostChargeBlock_Impl;
  }

  class EPMODEL_API UtilityCostChargeBlock : public ModelObject
  {
   public:
    explicit UtilityCostChargeBlock(const Model& model);

    virtual ~UtilityCostChargeBlock() override = default;
    UtilityCostChargeBlock(const UtilityCostChargeBlock& other) = default;
    UtilityCostChargeBlock(UtilityCostChargeBlock&& other) = default;
    UtilityCostChargeBlock& operator=(const UtilityCostChargeBlock&) = default;
    UtilityCostChargeBlock& operator=(UtilityCostChargeBlock&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> seasonValues();
    static std::vector<std::string> categoryVariableNameValues();

    // Schema Alignment Notes:
    // - API: No openstudio::model counterpart exists, so the class/accessor naming mirrors the EnergyPlus IDD.
    // - Field Mapping: Tariff Name is an object-list reference; the relationship helper is deferred until UtilityCostTariff is available.
    // - Field Mapping: Source Variable, Remaining Into Variable, and Block Size Multiplier map directly to UtilityCost:Charge:Block fields.
    // - Field Mapping: Season and Category Variable Name are choice fields; values helpers expose the allowed options.
    // - Field Mapping: Extensible block size/cost entries are relationship-like and intentionally excluded in this scalar pass.
    std::string sourceVariable() const;
    bool setSourceVariable(const std::string& sourceVariable);

    std::string season() const;
    bool setSeason(const std::string& season);
    bool isSeasonDefaulted() const;
    void resetSeason();

    std::string categoryVariableName() const;
    bool setCategoryVariableName(const std::string& categoryVariableName);

    boost::optional<std::string> remainingIntoVariable() const;
    bool setRemainingIntoVariable(const std::string& remainingIntoVariable);
    void resetRemainingIntoVariable();

    boost::optional<std::string> blockSizeMultiplierValueorVariableName() const;
    bool setBlockSizeMultiplierValueorVariableName(const std::string& blockSizeMultiplierValueorVariableName);
    void resetBlockSizeMultiplierValueorVariableName();

   protected:
    using ImplType = detail::UtilityCostChargeBlock_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit UtilityCostChargeBlock(std::shared_ptr<detail::UtilityCostChargeBlock_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
