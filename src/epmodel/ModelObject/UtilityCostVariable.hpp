/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_UTILITYCOSTVARIABLE_HPP
#define EPMODEL_UTILITYCOSTVARIABLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class UtilityCostVariable_Impl;
  }

  class EPMODEL_API UtilityCostVariable : public ModelObject
  {
   public:
    explicit UtilityCostVariable(const Model& model);

    virtual ~UtilityCostVariable() override = default;
    UtilityCostVariable(const UtilityCostVariable& other) = default;
    UtilityCostVariable(UtilityCostVariable&& other) = default;
    UtilityCostVariable& operator=(const UtilityCostVariable&) = default;
    UtilityCostVariable& operator=(UtilityCostVariable&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> variableTypeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel object mirrors the EnergyPlus UtilityCost:Variable naming for scalar accessors.
    // - Field Mapping: Variable Type and the twelve monthly Value fields map directly to UtilityCost:Variable.
    // - Field Mapping: Tariff Name is an object-list relationship and is intentionally deferred to a later pass.
    std::string variableType() const;
    bool isVariableTypeDefaulted() const;
    bool setVariableType(const std::string& variableType);
    void resetVariableType();

    boost::optional<double> januaryValue() const;
    bool setJanuaryValue(double januaryValue);
    void resetJanuaryValue();

    boost::optional<double> februaryValue() const;
    bool setFebruaryValue(double februaryValue);
    void resetFebruaryValue();

    boost::optional<double> marchValue() const;
    bool setMarchValue(double marchValue);
    void resetMarchValue();

    boost::optional<double> aprilValue() const;
    bool setAprilValue(double aprilValue);
    void resetAprilValue();

    boost::optional<double> mayValue() const;
    bool setMayValue(double mayValue);
    void resetMayValue();

    boost::optional<double> juneValue() const;
    bool setJuneValue(double juneValue);
    void resetJuneValue();

    boost::optional<double> julyValue() const;
    bool setJulyValue(double julyValue);
    void resetJulyValue();

    boost::optional<double> augustValue() const;
    bool setAugustValue(double augustValue);
    void resetAugustValue();

    boost::optional<double> septemberValue() const;
    bool setSeptemberValue(double septemberValue);
    void resetSeptemberValue();

    boost::optional<double> octoberValue() const;
    bool setOctoberValue(double octoberValue);
    void resetOctoberValue();

    boost::optional<double> novemberValue() const;
    bool setNovemberValue(double novemberValue);
    void resetNovemberValue();

    boost::optional<double> decemberValue() const;
    bool setDecemberValue(double decemberValue);
    void resetDecemberValue();

   protected:
    using ImplType = detail::UtilityCostVariable_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit UtilityCostVariable(std::shared_ptr<detail::UtilityCostVariable_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
