/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERIORWATEREQUIPMENT_IMPL_HPP
#define EPMODEL_EXTERIORWATEREQUIPMENT_IMPL_HPP

#include "ModelObject/ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ExteriorWaterEquipment_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ExteriorWaterEquipment_Impl() override = default;

      double multiplier() const;
      bool isMultiplierDefaulted() const;
      bool setMultiplier(double multiplier);
      void resetMultiplier();

      std::string endUseSubcategory() const;
      bool isEndUseSubcategoryDefaulted() const;
      bool setEndUseSubcategory(const std::string& endUseSubcategory);
      void resetEndUseSubcategory();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
