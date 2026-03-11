/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEPLANTBOILEROBJECTREFERENCE_IMPL_HPP
#define EPMODEL_HVACTEMPLATEPLANTBOILEROBJECTREFERENCE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API HVACTemplatePlantBoilerObjectReference_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~HVACTemplatePlantBoilerObjectReference_Impl() override = default;

  std::string boilerObjectType() const;
  boost::optional<double> priority() const;
  boost::optional<std::string> templatePlantLoopType() const;

  bool isBoilerObjectTypeDefaulted() const;

  bool setBoilerObjectType(const std::string& boilerObjectType);
  bool setPriority(double priority);
  bool setTemplatePlantLoopType(const std::string& templatePlantLoopType);

  void resetBoilerObjectType();
  void resetPriority();
  void resetTemplatePlantLoopType();

  std::vector<std::string> boilerObjectTypeValues() const;
  std::vector<std::string> templatePlantLoopTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
