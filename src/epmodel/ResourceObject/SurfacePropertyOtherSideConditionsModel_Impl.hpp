/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACEPROPERTYOTHERSIDECONDITIONSMODEL_IMPL_HPP
#define EPMODEL_SURFACEPROPERTYOTHERSIDECONDITIONSMODEL_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SurfacePropertyOtherSideConditionsModel_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SurfacePropertyOtherSideConditionsModel_Impl() override = default;

      std::string typeOfModeling() const;
      bool isTypeOfModelingDefaulted() const;

      bool setTypeOfModeling(const std::string& typeOfModeling);
      void resetTypeOfModeling();

     private:
      REGISTER_LOGGER("openstudio.epmodel.SurfacePropertyOtherSideConditionsModel");
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
