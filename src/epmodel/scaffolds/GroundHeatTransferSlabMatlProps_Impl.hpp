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
      bool isRHOSlabMaterialdensityDefaulted() const;
      bool setRHOSlabMaterialdensity(double rHOSlabMaterialdensity);
      void resetRHOSlabMaterialdensity();

      double rHOSoilDensity() const;
      bool isRHOSoilDensityDefaulted() const;
      bool setRHOSoilDensity(double rHOSoilDensity);
      void resetRHOSoilDensity();

      double cPSlabCP() const;
      bool isCPSlabCPDefaulted() const;
      bool setCPSlabCP(double cPSlabCP);
      void resetCPSlabCP();

      double cPSoilCP() const;
      bool isCPSoilCPDefaulted() const;
      bool setCPSoilCP(double cPSoilCP);
      void resetCPSoilCP();

      double tCONSlabk() const;
      bool isTCONSlabkDefaulted() const;
      bool setTCONSlabk(double tCONSlabk);
      void resetTCONSlabk();

      double tCONSoilk() const;
      bool isTCONSoilkDefaulted() const;
      bool setTCONSoilk(double tCONSoilk);
      void resetTCONSoilk();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
