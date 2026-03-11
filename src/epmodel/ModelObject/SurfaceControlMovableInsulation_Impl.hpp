/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACECONTROLMOVABLEINSULATION_IMPL_HPP
#define EPMODEL_SURFACECONTROLMOVABLEINSULATION_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SurfaceControlMovableInsulation_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SurfaceControlMovableInsulation_Impl() override = default;

      std::string insulationType() const;

      bool setInsulationType(const std::string& insulationType);

     private:
      std::vector<std::string> insulationTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
