/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTCONSTRUCTIONS_IMPL_HPP
#define EPMODEL_OUTPUTCONSTRUCTIONS_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API OutputConstructions_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~OutputConstructions_Impl() override = default;

  bool reportConstructions() const;
  bool reportMaterials() const;

  bool setReportConstructions(bool reportConstructions);
  bool setReportMaterials(bool reportMaterials);

 private:
  bool setReportFlags(bool reportConstructions, bool reportMaterials);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
