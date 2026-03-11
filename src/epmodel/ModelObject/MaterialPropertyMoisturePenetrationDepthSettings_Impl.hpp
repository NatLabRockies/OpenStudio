/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MATERIALPROPERTYMOISTUREPENETRATIONDEPTHSETTINGS_IMPL_HPP
#define EPMODEL_MATERIALPROPERTYMOISTUREPENETRATIONDEPTHSETTINGS_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API MaterialPropertyMoisturePenetrationDepthSettings_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~MaterialPropertyMoisturePenetrationDepthSettings_Impl() override = default;

  double waterVaporDiffusionResistanceFactor() const;
  bool setWaterVaporDiffusionResistanceFactor(double waterVaporDiffusionResistanceFactor);

  double moistureEquationCoefficientA() const;
  bool setMoistureEquationCoefficientA(double moistureEquationCoefficientA);

  double moistureEquationCoefficientB() const;
  bool setMoistureEquationCoefficientB(double moistureEquationCoefficientB);

  double moistureEquationCoefficientC() const;
  bool setMoistureEquationCoefficientC(double moistureEquationCoefficientC);

  double moistureEquationCoefficientD() const;
  bool setMoistureEquationCoefficientD(double moistureEquationCoefficientD);

  std::vector<double> moistureEquationCoefficients() const;
  bool setMoistureEquationCoefficients(double moistureEquationCoefficientA, double moistureEquationCoefficientB,
                                       double moistureEquationCoefficientC, double moistureEquationCoefficientD);

  boost::optional<double> surfaceLayerPenetrationDepth();
  bool isSurfaceLayerPenetrationDepthAutocalculated();
  bool setSurfaceLayerPenetrationDepth(double surfaceLayerPenetrationDepth);
  void autocalculateSurfaceLayerPenetrationDepth();

  boost::optional<double> deepLayerPenetrationDepth();
  bool isDeepLayerPenetrationDepthAutocalculated();
  bool setDeepLayerPenetrationDepth(double deepLayerPenetrationDepth);
  void autocalculateDeepLayerPenetrationDepth();

  double coatingLayerThickness() const;
  bool setCoatingLayerThickness(double coatingLayerThickness);

  double coatingLayerWaterVaporDiffusionResistanceFactor() const;
  bool setCoatingLayerWaterVaporDiffusionResistanceFactor(double coatingLayerWaterVaporDiffusionResistanceFactor);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
