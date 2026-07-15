/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURRENCYTYPE_IMPL_HPP
#define EPMODEL_CURRENCYTYPE_IMPL_HPP

#include "ParentObject/ParentObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API CurrencyType_Impl : public ParentObject_Impl
    {
     public:
      using ParentObject_Impl::ParentObject_Impl;
      virtual ~CurrencyType_Impl() override = default;

      boost::optional<std::string> monetaryUnit() const;
      bool setMonetaryUnit(const std::string& monetaryUnit);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
