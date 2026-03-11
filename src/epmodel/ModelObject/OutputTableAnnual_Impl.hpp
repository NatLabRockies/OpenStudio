/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTTABLEANNUAL_IMPL_HPP
#define EPMODEL_OUTPUTTABLEANNUAL_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API OutputTableAnnual_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~OutputTableAnnual_Impl() override = default;

  boost::optional<std::string> filter() const;

  bool setFilter(const std::string& filter);
  void resetFilter();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
