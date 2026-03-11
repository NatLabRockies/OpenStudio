/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATEXCHANGERVERTICALARRAY_IMPL_HPP
#define EPMODEL_GROUNDHEATEXCHANGERVERTICALARRAY_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API GroundHeatExchangerVerticalArray_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~GroundHeatExchangerVerticalArray_Impl() override = default;

  int numberofBoreholesinXDirection() const;
  int numberofBoreholesinYDirection() const;
  double boreholeSpacing() const;

  bool setNumberofBoreholesinXDirection(int numberofBoreholesinXDirection);
  bool setNumberofBoreholesinYDirection(int numberofBoreholesinYDirection);
  bool setBoreholeSpacing(double boreholeSpacing);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
