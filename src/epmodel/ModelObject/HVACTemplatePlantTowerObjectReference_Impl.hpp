/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEPLANTTOWEROBJECTREFERENCE_IMPL_HPP
#define EPMODEL_HVACTEMPLATEPLANTTOWEROBJECTREFERENCE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API HVACTemplatePlantTowerObjectReference_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~HVACTemplatePlantTowerObjectReference_Impl() override = default;

      std::string coolingTowerObjectType() const;
      bool setCoolingTowerObjectType(const std::string& coolingTowerObjectType);
      bool isCoolingTowerObjectTypeDefaulted() const;
      void resetCoolingTowerObjectType();

      boost::optional<double> priority() const;
      bool setPriority(double priority);
      void resetPriority();

      boost::optional<std::string> templatePlantLoopType() const;
      bool setTemplatePlantLoopType(const std::string& templatePlantLoopType);
      void resetTemplatePlantLoopType();

      std::vector<std::string> coolingTowerObjectTypeValues() const;
      std::vector<std::string> templatePlantLoopTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
