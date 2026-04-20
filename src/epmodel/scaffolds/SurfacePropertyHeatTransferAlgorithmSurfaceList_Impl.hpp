/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_SURFACEPROPERTYHEATTRANSFERALGORITHMSURFACELIST_IMPL_HPP
#define EPMODEL_SURFACEPROPERTYHEATTRANSFERALGORITHMSURFACELIST_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SurfacePropertyHeatTransferAlgorithmSurfaceList_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SurfacePropertyHeatTransferAlgorithmSurfaceList_Impl() override = default;

      std::string algorithm() const;
      bool setAlgorithm(const std::string& algorithm);
      void resetAlgorithm();
      bool isAlgorithmDefaulted() const;

      std::vector<std::string> algorithmValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
