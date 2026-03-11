/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTTABLETIMEBINS_IMPL_HPP
#define EPMODEL_OUTPUTTABLETIMEBINS_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API OutputTableTimeBins_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~OutputTableTimeBins_Impl() override = default;

  std::string keyValue() const;
  bool isKeyValueDefaulted() const;

  std::string variableName() const;

  boost::optional<double> intervalStart() const;

  boost::optional<double> intervalSize() const;

  boost::optional<int> intervalCount() const;

  boost::optional<std::string> variableType() const;

  bool setKeyValue(const std::string& keyValue);
  void resetKeyValue();

  bool setVariableName(const std::string& variableName);

  bool setIntervalStart(double intervalStart);
  void resetIntervalStart();

  bool setIntervalSize(double intervalSize);
  void resetIntervalSize();

  bool setIntervalCount(int intervalCount);
  void resetIntervalCount();

  bool setVariableType(const std::string& variableType);
  void resetVariableType();

  std::vector<std::string> variableTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
