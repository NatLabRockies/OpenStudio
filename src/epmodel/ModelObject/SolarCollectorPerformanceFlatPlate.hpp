/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SOLARCOLLECTORPERFORMANCEFLATPLATE_HPP
#define EPMODEL_SOLARCOLLECTORPERFORMANCEFLATPLATE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class SolarCollectorPerformanceFlatPlate_Impl;
}

class EPMODEL_API SolarCollectorPerformanceFlatPlate : public ModelObject
{
 public:
  explicit SolarCollectorPerformanceFlatPlate(const Model& model);

  virtual ~SolarCollectorPerformanceFlatPlate() override = default;
  SolarCollectorPerformanceFlatPlate(const SolarCollectorPerformanceFlatPlate& other) = default;
  SolarCollectorPerformanceFlatPlate(SolarCollectorPerformanceFlatPlate&& other) = default;
  SolarCollectorPerformanceFlatPlate& operator=(const SolarCollectorPerformanceFlatPlate&) = default;
  SolarCollectorPerformanceFlatPlate& operator=(SolarCollectorPerformanceFlatPlate&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> testFluidValues();
  static std::vector<std::string> testCorrelationTypeValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::SolarCollectorPerformanceFlatPlate scalar accessor names/signatures.
  // - Field Mapping: grossArea, testFluid, testFlowRate, testCorrelationType, and coefficient* APIs map directly to E+ SolarCollectorPerformance:FlatPlate fields.
  // - ForwardTranslator evidence: ForwardTranslateSolarCollectorPerformanceFlatPlate.cpp writes these exact API getters to matching IDF fields.
  // - Field Mapping: Name remains inherited via ModelObject naming API; this scaffold only adds class-specific scalar accessors.
  // - TODO(parity): Keep scalar signature parity while adding any future non-scalar behavior incrementally.
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
  bool setCoefficient3ofEfficiencyEquation(double coefficient3ofEfficiencyEquation);
  void resetCoefficient3ofEfficiencyEquation();
  bool setCoefficient2ofIncidentAngleModifier(double coefficient2ofIncidentAngleModifier);
  void resetCoefficient2ofIncidentAngleModifier();
  bool setCoefficient3ofIncidentAngleModifier(double coefficient3ofIncidentAngleModifier);
  void resetCoefficient3ofIncidentAngleModifier();

 protected:
  using ImplType = detail::SolarCollectorPerformanceFlatPlate_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit SolarCollectorPerformanceFlatPlate(std::shared_ptr<detail::SolarCollectorPerformanceFlatPlate_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
