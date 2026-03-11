/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WALLDETAILED_IMPL_HPP
#define EPMODEL_WALLDETAILED_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API WallDetailed_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~WallDetailed_Impl() override = default;

      std::string outsideBoundaryCondition() const;
      bool setOutsideBoundaryCondition(const std::string& outsideBoundaryCondition);

      std::string sunExposure() const;
      bool setSunExposure(const std::string& sunExposure);
      bool isSunExposureDefaulted() const;
      void resetSunExposure();

      std::string windExposure() const;
      bool setWindExposure(const std::string& windExposure);
      bool isWindExposureDefaulted() const;
      void resetWindExposure();

      boost::optional<double> viewFactorToGround() const;
      bool isViewFactorToGroundDefaulted() const;
      bool isViewFactorToGroundAutocalculated() const;
      bool setViewFactorToGround(double viewFactorToGround);
      void resetViewFactorToGround();
      void autocalculateViewFactorToGround();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
