/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WATERUSEEQUIPMENT_IMPL_HPP
#define EPMODEL_WATERUSEEQUIPMENT_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API WaterUseEquipment_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~WaterUseEquipment_Impl() override = default;

      std::string endUseSubcategory() const;
      bool isEndUseSubcategoryDefaulted() const;
      bool setEndUseSubcategory(const std::string& endUseSubcategory);
      void resetEndUseSubcategory();

      double peakFlowRate() const;
      bool setPeakFlowRate(double peakFlowRate);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_WATERUSEEQUIPMENT_IMPL_HPP
