/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTTABLETIMEBINS_HPP
#define EPMODEL_OUTPUTTABLETIMEBINS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class OutputTableTimeBins_Impl;
}

class EPMODEL_API OutputTableTimeBins : public ModelObject
{
 public:
  explicit OutputTableTimeBins(const Model& model);

  virtual ~OutputTableTimeBins() override = default;
  OutputTableTimeBins(const OutputTableTimeBins& other) = default;
  OutputTableTimeBins(OutputTableTimeBins&& other) = default;
  OutputTableTimeBins& operator=(const OutputTableTimeBins&) = default;
  OutputTableTimeBins& operator=(OutputTableTimeBins&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> variableTypeValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: keyValue, variableName, intervalStart, intervalSize, intervalCount, and variableType map directly to E+
  //   Output:Table:TimeBins scalar fields.
  // - Field Mapping: Schedule Name is a relationship/object-list field and is intentionally excluded in this scalar-only pass.
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

 protected:
  using ImplType = detail::OutputTableTimeBins_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit OutputTableTimeBins(std::shared_ptr<detail::OutputTableTimeBins_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
