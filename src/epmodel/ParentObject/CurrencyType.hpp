/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURRENCYTYPE_HPP
#define EPMODEL_CURRENCYTYPE_HPP

#include "EPModelAPI.hpp"
#include "ParentObject/ParentObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CurrencyType_Impl;
}

class EPMODEL_API CurrencyType : public ParentObject
{
 public:
  explicit CurrencyType(const Model& model);

  virtual ~CurrencyType() override = default;
  CurrencyType(const CurrencyType& other) = default;
  CurrencyType(CurrencyType&& other) = default;
  CurrencyType& operator=(const CurrencyType&) = default;
  CurrencyType& operator=(CurrencyType&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::CurrencyType scalar API naming/signatures.
  // - Field Mapping: monetaryUnit maps to EnergyPlus CurrencyType/Monetary Unit.
  // - ForwardTranslator evidence: ForwardTranslateCurrencyType.cpp currently emits CurrencyType without setting Monetary Unit.
  // - TODO(parity): Align ForwardTranslator behavior with preserved monetaryUnit mapping when parity work reaches translators.
  boost::optional<std::string> monetaryUnit() const;
  bool setMonetaryUnit(const std::string& monetaryUnit);

 protected:
  using ImplType = detail::CurrencyType_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CurrencyType(std::shared_ptr<detail::CurrencyType_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
