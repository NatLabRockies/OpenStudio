/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTSURFACESDRAWING_IMPL_HPP
#define EPMODEL_OUTPUTSURFACESDRAWING_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API OutputSurfacesDrawing_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~OutputSurfacesDrawing_Impl() override = default;

  std::string reportType() const;

  std::string reportSpecifications1() const;
  bool isReportSpecifications1Defaulted() const;

  bool setReportType(const std::string& reportType);

  bool setReportSpecifications1(const std::string& reportSpecifications1);
  void resetReportSpecifications1();

  std::vector<std::string> reportTypeValues() const;
  std::vector<std::string> reportSpecifications1Values() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
