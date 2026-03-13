/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_MATERIALPROPERTYHEATANDMOISTURETRANSFERSETTINGS_IMPL_HPP
#define EPMODEL_MATERIALPROPERTYHEATANDMOISTURETRANSFERSETTINGS_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API MaterialPropertyHeatAndMoistureTransferSettings_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~MaterialPropertyHeatAndMoistureTransferSettings_Impl() override = default;

  double porosity() const;
  bool setPorosity(double porosity);

  double initialWaterContentRatio() const;
  bool setInitialWaterContentRatio(double initialWaterContentRatio);
  bool isInitialWaterContentRatioDefaulted() const;
  void resetInitialWaterContentRatio();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
