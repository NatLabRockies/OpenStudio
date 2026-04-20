/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERBASEMENTSIMPARAMETERS_IMPL_HPP
#define EPMODEL_GROUNDHEATTRANSFERBASEMENTSIMPARAMETERS_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API GroundHeatTransferBasementSimParameters_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~GroundHeatTransferBasementSimParameters_Impl() override = default;

      // Field: F, Multiplier for the ADI solution
      boost::optional<double> fMultiplierfortheADIsolution() const;
      bool setFMultiplierfortheADIsolution(double fMultiplierfortheADIsolution);
      void resetFMultiplierfortheADIsolution();

      // Field: IYRS, Maximum number of yearly iterations
      int iYRSMaximumnumberofyearlyiterations() const;
      bool isIYRSMaximumnumberofyearlyiterationsDefaulted() const;
      bool setIYRSMaximumnumberofyearlyiterations(int iYRSMaximumnumberofyearlyiterations);
      void resetIYRSMaximumnumberofyearlyiterations();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
