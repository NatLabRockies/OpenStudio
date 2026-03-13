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

      std::vector<std::string> algorithmValues() const;

      std::string algorithm() const;
      bool setAlgorithm(const std::string& algorithm);
      bool isAlgorithmDefaulted() const;
      void resetAlgorithm();

      int numberofIterationsBeforeAlgorithmSwitch() const;
      bool setNumberofIterationsBeforeAlgorithmSwitch(int numberofIterationsBeforeAlgorithmSwitch);
      bool isNumberofIterationsBeforeAlgorithmSwitchDefaulted() const;
      void resetNumberofIterationsBeforeAlgorithmSwitch();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
