/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_SURFACEPROPERTYHEATTRANSFERALGORITHMCONSTRUCTION_IMPL_HPP
#define EPMODEL_SURFACEPROPERTYHEATTRANSFERALGORITHMCONSTRUCTION_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SurfacePropertyHeatTransferAlgorithmConstruction_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SurfacePropertyHeatTransferAlgorithmConstruction_Impl() override = default;

      std::vector<std::string> algorithmValues() const;

      std::string algorithm() const;
      bool setAlgorithm(const std::string& algorithm);
      bool isAlgorithmDefaulted() const;
      void resetAlgorithm();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
