/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COMPLIANCEBUILDING_IMPL_HPP
#define EPMODEL_COMPLIANCEBUILDING_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ComplianceBuilding_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ComplianceBuilding_Impl() override = default;

      double buildingRotationforAppendixG() const;
      bool setBuildingRotationforAppendixG(double buildingRotationforAppendixG);
      bool isBuildingRotationforAppendixGDefaulted() const;
      void resetBuildingRotationforAppendixG();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
