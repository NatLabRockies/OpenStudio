/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_INSIDESURFACECONVECTIONALGORITHM_IMPL_HPP
#define EPMODEL_INSIDESURFACECONVECTIONALGORITHM_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API InsideSurfaceConvectionAlgorithm_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~InsideSurfaceConvectionAlgorithm_Impl() override = default;

      std::vector<std::string> validAlgorithmValues() const;
      std::string algorithm() const;
      bool isAlgorithmDefaulted() const;
      bool setAlgorithm(const std::string& algorithm);
      void resetAlgorithm();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
