/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PERFORMANCEPRECISIONTRADEOFFS_IMPL_HPP
#define EPMODEL_PERFORMANCEPRECISIONTRADEOFFS_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API PerformancePrecisionTradeoffs_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~PerformancePrecisionTradeoffs_Impl() override = default;

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

  std::vector<std::string> zoneRadiantExchangeAlgorithmValues() const;
  std::vector<std::string> validZoneRadiantExchangeAlgorithmValues() const;

  std::vector<std::string> overrideModeValues() const;
  std::vector<std::string> validOverrideModeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
