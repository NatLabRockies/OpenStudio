/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTCONTROLREPORTINGTOLERANCES_IMPL_HPP
#define EPMODEL_OUTPUTCONTROLREPORTINGTOLERANCES_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API OutputControlReportingTolerances_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~OutputControlReportingTolerances_Impl() override = default;

  double toleranceforTimeHeatingSetpointNotMet() const;
  bool isToleranceforTimeHeatingSetpointNotMetDefaulted() const;

  double toleranceforTimeCoolingSetpointNotMet() const;
  bool isToleranceforTimeCoolingSetpointNotMetDefaulted() const;

  bool setToleranceforTimeHeatingSetpointNotMet(double toleranceforTimeHeatingSetpointNotMet);
  void resetToleranceforTimeHeatingSetpointNotMet();

  bool setToleranceforTimeCoolingSetpointNotMet(double toleranceforTimeCoolingSetpointNotMet);
  void resetToleranceforTimeCoolingSetpointNotMet();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
