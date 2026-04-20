/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACECONVECTIONALGORITHMINSIDEUSERCURVE_IMPL_HPP
#define EPMODEL_SURFACECONVECTIONALGORITHMINSIDEUSERCURVE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SurfaceConvectionAlgorithmInsideUserCurve_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SurfaceConvectionAlgorithmInsideUserCurve_Impl() override = default;

      std::vector<std::string> referenceTemperatureforConvectionHeatTransferValues() const;

      boost::optional<std::string> referenceTemperatureforConvectionHeatTransfer() const;
      bool setReferenceTemperatureforConvectionHeatTransfer(const std::string& referenceTemperatureforConvectionHeatTransfer);
      void resetReferenceTemperatureforConvectionHeatTransfer();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
