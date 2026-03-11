/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SHADINGBUILDINGDETAILED_IMPL_HPP
#define EPMODEL_SHADINGBUILDINGDETAILED_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API ShadingBuildingDetailed_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~ShadingBuildingDetailed_Impl() override = default;

  boost::optional<int> numberofVertices() const;
  bool setNumberofVertices(int numberofVertices);
  bool isNumberofVerticesAutocalculated() const;
  void autocalculateNumberofVertices();
  void resetNumberofVertices();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
