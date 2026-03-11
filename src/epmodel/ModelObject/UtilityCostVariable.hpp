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

    boost::optional<double> januaryValue() const;
    boost::optional<double> februaryValue() const;
    boost::optional<double> marchValue() const;
    boost::optional<double> aprilValue() const;
    boost::optional<double> mayValue() const;
    boost::optional<double> juneValue() const;
    boost::optional<double> julyValue() const;
    boost::optional<double> augustValue() const;
    boost::optional<double> septemberValue() const;
    boost::optional<double> octoberValue() const;
    boost::optional<double> novemberValue() const;
    boost::optional<double> decemberValue() const;

    bool setVariableType(const std::string& variableType);
    void resetVariableType();

    bool setJanuaryValue(double januaryValue);
    void resetJanuaryValue();
    bool setFebruaryValue(double februaryValue);
    void resetFebruaryValue();
    bool setMarchValue(double marchValue);
    void resetMarchValue();
    bool setAprilValue(double aprilValue);
    void resetAprilValue();
    bool setMayValue(double mayValue);
    void resetMayValue();
    bool setJuneValue(double juneValue);
    void resetJuneValue();
    bool setJulyValue(double julyValue);
    void resetJulyValue();
    bool setAugustValue(double augustValue);
    void resetAugustValue();
    bool setSeptemberValue(double septemberValue);
    void resetSeptemberValue();
    bool setOctoberValue(double octoberValue);
    void resetOctoberValue();
    bool setNovemberValue(double novemberValue);
    void resetNovemberValue();
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
