/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MATERIALPROPERTYHEATANDMOISTURETRANSFERSORPTIONISOTHERM_IMPL_HPP
#define EPMODEL_MATERIALPROPERTYHEATANDMOISTURETRANSFERSORPTIONISOTHERM_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API MaterialPropertyHeatAndMoistureTransferSorptionIsotherm_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~MaterialPropertyHeatAndMoistureTransferSorptionIsotherm_Impl() override = default;

  // Scalar-only scaffold: Number of Isotherm Coordinates (N1).
  // Non-scalar extensible pairs are excluded for this scaffold cycle.
  int numberofIsothermCoordinates() const;
  bool setNumberofIsothermCoordinates(int numberofIsothermCoordinates);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
