/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACE_IMPL_HPP
#define EPMODEL_SURFACE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API Surface_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~Surface_Impl() override = default;

  std::string surfaceType() const;
  std::string outsideBoundaryCondition() const;

  std::string sunExposure() const;
  bool isSunExposureDefaulted() const;

  std::string windExposure() const;
  bool isWindExposureDefaulted() const;

  boost::optional<double> viewFactortoGround() const;
  bool isViewFactortoGroundDefaulted() const;
  bool isViewFactortoGroundAutocalculated() const;

  boost::optional<double> numberofVertices() const;
  bool isNumberofVerticesDefaulted() const;
  bool isNumberofVerticesAutocalculated() const;

  bool setSurfaceType(const std::string& surfaceType);
  bool setOutsideBoundaryCondition(const std::string& outsideBoundaryCondition);

  bool setSunExposure(const std::string& sunExposure);
  void resetSunExposure();

  bool setWindExposure(const std::string& windExposure);
  void resetWindExposure();

  bool setViewFactortoGround(boost::optional<double> viewFactortoGround);
  bool setViewFactortoGround(double viewFactortoGround);
  void resetViewFactortoGround();
  void autocalculateViewFactortoGround();

  bool setNumberofVertices(boost::optional<double> numberofVertices);
  bool setNumberofVertices(double numberofVertices);
  void resetNumberofVertices();
  void autocalculateNumberofVertices();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
