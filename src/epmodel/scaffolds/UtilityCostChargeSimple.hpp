/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_UTILITYCOSTCHARGESIMPLE_HPP
#define EPMODEL_UTILITYCOSTCHARGESIMPLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class UtilityCostChargeSimple_Impl;
  }

  class EPMODEL_API UtilityCostChargeSimple : public ModelObject
  {
   public:
    explicit UtilityCostChargeSimple(const Model& model);

    virtual ~UtilityCostChargeSimple() override = default;
    UtilityCostChargeSimple(const UtilityCostChargeSimple& other) = default;
    UtilityCostChargeSimple(UtilityCostChargeSimple&& other) = default;
    UtilityCostChargeSimple& operator=(const UtilityCostChargeSimple&) = default;
    UtilityCostChargeSimple& operator=(UtilityCostChargeSimple&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> seasonValues();
    static std::vector<std::string> categoryVariableNameValues();

    // Schema alignment notes:
    // - API: No openstudio::model counterpart exists, so scalar APIs mirror the EnergyPlus name-only accessors.
    // - Field mapping: Source Variable, Season, Category Variable Name, and Cost per Unit Value or Variable Name map to their UtilityCost:Charge:Simple fields.
    // - Tariff Name is an object-list reference (relationship) and is deferred until a later parity pass.
    // - TODO(parity): Provide Tariff helpers once relationship scaffolding is in place.

    // Source Variable
    std::string sourceVariable() const;
    bool setSourceVariable(const std::string& sourceVariable);

    // Season
    boost::optional<std::string> season() const;
    bool setSeason(const std::string& season);
    void resetSeason();

    // Category Variable Name
    std::string categoryVariableName() const;
    bool setCategoryVariableName(const std::string& categoryVariableName);

    // Cost per Unit Value or Variable Name
    std::string costPerUnitValueorVariableName() const;
    bool setCostPerUnitValueorVariableName(const std::string& costPerUnitValueorVariableName);

   protected:
    using ImplType = detail::UtilityCostChargeSimple_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit UtilityCostChargeSimple(std::shared_ptr<detail::UtilityCostChargeSimple_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
