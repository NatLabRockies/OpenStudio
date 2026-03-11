/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACSYSTEMROOTFINDINGALGORITHM_IMPL_HPP
#define EPMODEL_HVACSYSTEMROOTFINDINGALGORITHM_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API HVACSystemRootFindingAlgorithm_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~HVACSystemRootFindingAlgorithm_Impl() override = default;

  std::string algorithm() const;
  bool isAlgorithmDefaulted() const;
  bool setAlgorithm(const std::string& algorithm);
  void resetAlgorithm();

  int numberofIterationsBeforeAlgorithmSwitch() const;
  bool isNumberofIterationsBeforeAlgorithmSwitchDefaulted() const;
  bool setNumberofIterationsBeforeAlgorithmSwitch(int numberofIterationsBeforeAlgorithmSwitch);
  void resetNumberofIterationsBeforeAlgorithmSwitch();

  std::vector<std::string> algorithmValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
