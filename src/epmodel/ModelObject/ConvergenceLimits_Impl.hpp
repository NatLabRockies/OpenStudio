/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONVERGENCELIMITS_IMPL_HPP
#define EPMODEL_CONVERGENCELIMITS_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ConvergenceLimits_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ConvergenceLimits_Impl() override = default;

      boost::optional<int> minimumSystemTimestep() const;
      bool setMinimumSystemTimestep(int minimumSystemTimestep);
      void resetMinimumSystemTimestep();

      int maximumHVACIterations() const;
      bool isMaximumHVACIterationsDefaulted() const;
      bool setMaximumHVACIterations(int maximumHVACIterations);
      void resetMaximumHVACIterations();

      int minimumPlantIterations() const;
      bool isMinimumPlantIterationsDefaulted() const;
      bool setMinimumPlantIterations(int minimumPlantIterations);
      void resetMinimumPlantIterations();

      int maximumPlantIterations() const;
      bool isMaximumPlantIterationsDefaulted() const;
      bool setMaximumPlantIterations(int maximumPlantIterations);
      void resetMaximumPlantIterations();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
