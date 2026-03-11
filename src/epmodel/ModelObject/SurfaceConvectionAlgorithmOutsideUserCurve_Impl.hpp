/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACECONVECTIONALGORITHMOUTSIDEUSERCURVE_IMPL_HPP
#define EPMODEL_SURFACECONVECTIONALGORITHMOUTSIDEUSERCURVE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SurfaceConvectionAlgorithmOutsideUserCurve_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SurfaceConvectionAlgorithmOutsideUserCurve_Impl() override = default;

      std::string windSpeedTypeforCurve() const;
      bool isWindSpeedTypeforCurveDefaulted() const;
      bool setWindSpeedTypeforCurve(const std::string& windSpeedTypeforCurve);
      void resetWindSpeedTypeforCurve();

      std::vector<std::string> windSpeedTypeforCurveValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
