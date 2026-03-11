/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERIORLIGHTS_IMPL_HPP
#define EPMODEL_EXTERIORLIGHTS_IMPL_HPP

#include "ModelObject/ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API ExteriorLights_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~ExteriorLights_Impl() override = default;

  std::string controlOption() const;
  bool isControlOptionDefaulted() const;

  double multiplier() const;
  bool isMultiplierDefaulted() const;

  std::string endUseSubcategory() const;
  bool isEndUseSubcategoryDefaulted() const;

  bool setControlOption(const std::string& controlOption);
  void resetControlOption();

  bool setMultiplier(double multiplier);
  void resetMultiplier();

  bool setEndUseSubcategory(const std::string& endUseSubcategory);
  void resetEndUseSubcategory();

  std::vector<std::string> controlOptionValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
