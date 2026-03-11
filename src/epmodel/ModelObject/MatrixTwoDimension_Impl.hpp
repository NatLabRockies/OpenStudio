/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MATRIXTWODIMENSION_IMPL_HPP
#define EPMODEL_MATRIXTWODIMENSION_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API MatrixTwoDimension_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~MatrixTwoDimension_Impl() override = default;

  int numberofRows() const;
  bool setNumberofRows(int numberofRows);

  int numberofColumns() const;
  bool setNumberofColumns(int numberofColumns);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
