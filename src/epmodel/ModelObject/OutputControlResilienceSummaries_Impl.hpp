/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTCONTROLRESILIENCESUMMARIES_IMPL_HPP
#define EPMODEL_OUTPUTCONTROLRESILIENCESUMMARIES_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API OutputControlResilienceSummaries_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~OutputControlResilienceSummaries_Impl() override = default;

  std::string heatIndexAlgorithm() const;
  bool setHeatIndexAlgorithm(const std::string& heatIndexAlgorithm);

  std::vector<std::string> heatIndexAlgorithmValues() const;
  std::vector<std::string> validHeatIndexAlgorithmValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
