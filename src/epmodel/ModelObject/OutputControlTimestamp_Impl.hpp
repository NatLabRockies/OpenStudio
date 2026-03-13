/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTCONTROLTIMESTAMP_IMPL_HPP
#define EPMODEL_OUTPUTCONTROLTIMESTAMP_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API OutputControlTimestamp_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~OutputControlTimestamp_Impl() override = default;

      bool iso8601Format() const;
      bool setISO8601Format(bool iso8601Format);

      bool timestampAtBeginningOfInterval() const;
      bool setTimestampAtBeginningOfInterval(bool timestampAtBeginningOfInterval);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
