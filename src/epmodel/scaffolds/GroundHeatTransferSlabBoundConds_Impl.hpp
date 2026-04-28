/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERSLABBOUNDCONDS_IMPL_HPP
#define EPMODEL_GROUNDHEATTRANSFERSLABBOUNDCONDS_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API GroundHeatTransferSlabBoundConds_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~GroundHeatTransferSlabBoundConds_Impl() override = default;

      bool eVTRIssurfaceevapotranspirationmodeled() const;
      bool setEVTRIssurfaceevapotranspirationmodeled(bool eVTRIssurfaceevapotranspirationmodeled);

      bool fIXBCIsthelowerboundaryatafixedtemperature() const;
      bool setFIXBCIsthelowerboundaryatafixedtemperature(bool fIXBCIsthelowerboundaryatafixedtemperature);

      boost::optional<double> tDEEPin() const;
      bool setTDEEPin(double tDEEPin);
      void resetTDEEPin();

      bool uSRHflagIsthegroundsurfacehspecifiedbytheuser() const;
      bool setUSRHflagIsthegroundsurfacehspecifiedbytheuser(bool uSRHflagIsthegroundsurfacehspecifiedbytheuser);

      boost::optional<double> uSERHUserspecifiedgroundsurfaceheattransfercoefficient() const;
      bool setUSERHUserspecifiedgroundsurfaceheattransfercoefficient(double uSERHUserspecifiedgroundsurfaceheattransfercoefficient);
      void resetUSERHUserspecifiedgroundsurfaceheattransfercoefficient();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
