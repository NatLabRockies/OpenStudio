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
  boost::optional<double> priority() const;
  boost::optional<std::string> templatePlantLoopType() const;

  bool isCoolingTowerObjectTypeDefaulted() const;

  bool setCoolingTowerObjectType(const std::string& coolingTowerObjectType);
  bool setPriority(double priority);
  bool setTemplatePlantLoopType(const std::string& templatePlantLoopType);

  void resetCoolingTowerObjectType();
  void resetPriority();
  void resetTemplatePlantLoopType();

  std::vector<std::string> coolingTowerObjectTypeValues() const;
  std::vector<std::string> templatePlantLoopTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
