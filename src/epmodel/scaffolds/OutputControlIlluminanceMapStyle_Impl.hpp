/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTCONTROLILLUMINANCEMAPSTYLE_IMPL_HPP
#define EPMODEL_OUTPUTCONTROLILLUMINANCEMAPSTYLE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API OutputControlIlluminanceMapStyle_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~OutputControlIlluminanceMapStyle_Impl() override = default;

  std::string columnSeparator() const;
  bool isColumnSeparatorDefaulted() const;
  bool setColumnSeparator(const std::string& columnSeparator);
  void resetColumnSeparator();

  std::vector<std::string> columnSeparatorValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
