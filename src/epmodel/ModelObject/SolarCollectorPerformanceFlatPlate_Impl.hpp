/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SOLARCOLLECTORPERFORMANCEFLATPLATE_IMPL_HPP
#define EPMODEL_SOLARCOLLECTORPERFORMANCEFLATPLATE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API SolarCollectorPerformanceFlatPlate_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~SolarCollectorPerformanceFlatPlate_Impl() override = default;

  double grossArea() const;
  std::string testFluid() const;
  bool isTestFluidDefaulted() const;
  double testFlowRate() const;
  std::string testCorrelationType() const;
  double coefficient1ofEfficiencyEquation() const;
  double coefficient2ofEfficiencyEquation() const;
  boost::optional<double> coefficient3ofEfficiencyEquation() const;
  boost::optional<double> coefficient2ofIncidentAngleModifier() const;
  boost::optional<double> coefficient3ofIncidentAngleModifier() const;

  bool setGrossArea(double grossArea);
  bool setTestFluid(const std::string& testFluid);
  void resetTestFluid();
  bool setTestFlowRate(double testFlowRate);
  bool setTestCorrelationType(const std::string& testCorrelationType);
  bool setCoefficient1ofEfficiencyEquation(double coefficient1ofEfficiencyEquation);
  bool setCoefficient2ofEfficiencyEquation(double coefficient2ofEfficiencyEquation);
  bool setCoefficient3ofEfficiencyEquation(boost::optional<double> coefficient3ofEfficiencyEquation);
  void resetCoefficient3ofEfficiencyEquation();
  bool setCoefficient2ofIncidentAngleModifier(boost::optional<double> coefficient2ofIncidentAngleModifier);
  void resetCoefficient2ofIncidentAngleModifier();
  bool setCoefficient3ofIncidentAngleModifier(boost::optional<double> coefficient3ofIncidentAngleModifier);
  void resetCoefficient3ofIncidentAngleModifier();

  std::vector<std::string> testFluidValues() const;
  std::vector<std::string> testCorrelationTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
