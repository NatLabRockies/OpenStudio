/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERSLABMATLPROPS_IMPL_HPP
#define EPMODEL_GROUNDHEATTRANSFERSLABMATLPROPS_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API GroundHeatTransferSlabMatlProps_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~GroundHeatTransferSlabMatlProps_Impl() override = default;

  double rHOSlabMaterialdensity() const;
  double rHOSoilDensity() const;
  double cPSlabCP() const;
  double cPSoilCP() const;
  double tCONSlabk() const;
  double tCONSoilk() const;

  bool isRHOSlabMaterialdensityDefaulted() const;
  bool isRHOSoilDensityDefaulted() const;
  bool isCPSlabCPDefaulted() const;
  bool isCPSoilCPDefaulted() const;
  bool isTCONSlabkDefaulted() const;
  bool isTCONSoilkDefaulted() const;

  bool setRHOSlabMaterialdensity(double rHOSlabMaterialdensity);
  bool setRHOSoilDensity(double rHOSoilDensity);
  bool setCPSlabCP(double cPSlabCP);
  bool setCPSoilCP(double cPSoilCP);
  bool setTCONSlabk(double tCONSlabk);
  bool setTCONSoilk(double tCONSoilk);

  void resetRHOSlabMaterialdensity();
  void resetRHOSoilDensity();
  void resetCPSlabCP();
  void resetCPSoilCP();
  void resetTCONSlabk();
  void resetTCONSoilk();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
