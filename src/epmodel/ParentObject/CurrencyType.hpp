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

/** \brief Defines the monetary unit used by life-cycle cost calculations.
 *
 * \par EnergyPlus object
 * \epobject{currencytype.html#currencytype,CurrencyType}
 *
 * \par Important behavior
 * The monetary-unit value is stored directly on the EnergyPlus object.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::CurrencyType</code>.
 *
 * \par Known limitations
 * No currency conversion or cost calculation is performed by this wrapper.
 */
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

    /** @name Monetary unit access */
    //@{
    boost::optional<std::string> monetaryUnit() const;
    bool setMonetaryUnit(const std::string& monetaryUnit);
    //@}

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
