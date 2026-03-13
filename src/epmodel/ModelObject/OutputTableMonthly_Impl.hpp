/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTTABLEMONTHLY_IMPL_HPP
#define EPMODEL_OUTPUTTABLEMONTHLY_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API OutputTableMonthly_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~OutputTableMonthly_Impl() override = default;

      /** Field accessors for digitsAfterDecimal. */
      //@{
      int digitsAfterDecimal() const;

      bool setDigitsAfterDecimal(int digitsAfterDecimal);
      //@}
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
