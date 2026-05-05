/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MATERIALPROPERTYHEATANDMOISTURETRANSFERDIFFUSION_IMPL_HPP
#define EPMODEL_MATERIALPROPERTYHEATANDMOISTURETRANSFERDIFFUSION_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API MaterialPropertyHeatAndMoistureTransferDiffusion_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~MaterialPropertyHeatAndMoistureTransferDiffusion_Impl() override = default;

      int numberofDataPairs() const;
      bool setNumberofDataPairs(int numberofDataPairs);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
