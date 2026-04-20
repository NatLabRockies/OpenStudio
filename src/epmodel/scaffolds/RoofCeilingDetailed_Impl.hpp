/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ROOFCEILINGDETAILED_IMPL_HPP
#define EPMODEL_ROOFCEILINGDETAILED_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API RoofCeilingDetailed_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~RoofCeilingDetailed_Impl() override = default;

      std::vector<std::string> outsideBoundaryConditionValues() const;
      std::vector<std::string> sunExposureValues() const;
      std::vector<std::string> windExposureValues() const;

      std::string outsideBoundaryCondition() const;
      bool setOutsideBoundaryCondition(const std::string& outsideBoundaryCondition);

      std::string sunExposure() const;
      bool isSunExposureDefaulted() const;
      bool setSunExposure(const std::string& sunExposure);
      void resetSunExposure();

      std::string windExposure() const;
      bool isWindExposureDefaulted() const;
      bool setWindExposure(const std::string& windExposure);
      void resetWindExposure();

      boost::optional<double> viewFactortoGround() const;
      bool setViewFactortoGround(double viewFactortoGround);
      bool isViewFactortoGroundAutocalculated() const;
      void autocalculateViewFactortoGround();
      void resetViewFactortoGround();

      boost::optional<int> numberofVertices() const;
      bool setNumberofVertices(int numberofVertices);
      bool isNumberofVerticesAutocalculated() const;
      void autocalculateNumberofVertices();
      void resetNumberofVertices();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
