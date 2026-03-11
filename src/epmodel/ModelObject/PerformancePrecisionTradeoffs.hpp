/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PERFORMANCEPRECISIONTRADEOFFS_HPP
#define EPMODEL_PERFORMANCEPRECISIONTRADEOFFS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class PerformancePrecisionTradeoffs_Impl;
}

class EPMODEL_API PerformancePrecisionTradeoffs : public ModelObject
{
 public:
  explicit PerformancePrecisionTradeoffs(const Model& model);

  virtual ~PerformancePrecisionTradeoffs() override = default;
  PerformancePrecisionTradeoffs(const PerformancePrecisionTradeoffs& other) = default;
  PerformancePrecisionTradeoffs(PerformancePrecisionTradeoffs&& other) = default;
  PerformancePrecisionTradeoffs& operator=(const PerformancePrecisionTradeoffs&) = default;
  PerformancePrecisionTradeoffs& operator=(PerformancePrecisionTradeoffs&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> zoneRadiantExchangeAlgorithmValues();
  static std::vector<std::string> validZoneRadiantExchangeAlgorithmValues();

  static std::vector<std::string> overrideModeValues();
  static std::vector<std::string> validOverrideModeValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::PerformancePrecisionTradeoffs scalar accessor names/signatures.
  // - Field Mapping: all scalar APIs map directly to E+ PerformancePrecisionTradeoffs fields with matching concepts.
  // - ForwardTranslator evidence: ForwardTranslatePerformancePrecisionTradeoffs.cpp writes these preserved APIs directly to these fields.
  // - TODO(parity): Keep scalar API stable while extending non-scalar parity behavior in later scaffold passes.
  bool useCoilDirectSolutions() const;
  bool isUseCoilDirectSolutionsDefaulted() const;

  std::string zoneRadiantExchangeAlgorithm() const;
  bool isZoneRadiantExchangeAlgorithmDefaulted() const;

  std::string overrideMode() const;
  bool isOverrideModeDefaulted() const;

  double maxZoneTempDiff() const;
  bool isMaxZoneTempDiffDefaulted() const;

  double maxAllowedDelTemp() const;
  bool isMaxAllowedDelTempDefaulted() const;

  bool useRepresentativeSurfacesforCalculations() const;
  bool isUseRepresentativeSurfacesforCalculationsDefaulted() const;

  bool setUseCoilDirectSolutions(bool useCoilDirectSolutions);
  void resetUseCoilDirectSolutions();

  bool setZoneRadiantExchangeAlgorithm(const std::string& zoneRadiantExchangeAlgorithm);
  void resetZoneRadiantExchangeAlgorithm();

  bool setOverrideMode(const std::string& overrideMode);
  void resetOverrideMode();

  bool setMaxZoneTempDiff(double maxZoneTempDiff);
  void resetMaxZoneTempDiff();

  bool setMaxAllowedDelTemp(double maxAllowedDelTemp);
  void resetMaxAllowedDelTemp();

  bool setUseRepresentativeSurfacesforCalculations(bool useRepresentativeSurfacesforCalculations);
  void resetUseRepresentativeSurfacesforCalculations();

 protected:
  using ImplType = detail::PerformancePrecisionTradeoffs_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit PerformancePrecisionTradeoffs(std::shared_ptr<detail::PerformancePrecisionTradeoffs_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
