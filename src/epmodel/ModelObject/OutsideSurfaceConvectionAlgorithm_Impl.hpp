/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTSIDESURFACECONVECTIONALGORITHM_IMPL_HPP
#define EPMODEL_OUTSIDESURFACECONVECTIONALGORITHM_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API OutsideSurfaceConvectionAlgorithm_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~OutsideSurfaceConvectionAlgorithm_Impl() override = default;

      std::string algorithm() const;
      bool isAlgorithmDefaulted() const;
      bool setAlgorithm(const std::string& algorithm);
      void resetAlgorithm();
      std::vector<std::string> validAlgorithmValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
