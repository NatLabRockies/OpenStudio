/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTSCHEDULES_HPP
#define EPMODEL_OUTPUTSCHEDULES_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class OutputSchedules_Impl;
}

class EPMODEL_API OutputSchedules : public ModelObject
{
 public:
  explicit OutputSchedules(const Model& model);

  virtual ~OutputSchedules() override = default;
  OutputSchedules(const OutputSchedules& other) = default;
  OutputSchedules(OutputSchedules&& other) = default;
  OutputSchedules& operator=(const OutputSchedules&) = default;
  OutputSchedules& operator=(OutputSchedules&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> keyFieldValues();
  static std::vector<std::string> validKeyFieldValues();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model::OutputSchedules class/accessor naming for counterpart parity.
  // - Field Mapping: keyField maps directly to EnergyPlus Output:Schedules Key Field.
  // - ForwardTranslator evidence: ForwardTranslateOutputSchedules.cpp writes model keyField() to Output:Schedules Key Field.
  // - TODO(parity): Keep this scalar API stable while adding any broader output-configuration behavior in later parity passes.
  std::string keyField() const;

  bool setKeyField(const std::string& keyField);

 protected:
  using ImplType = detail::OutputSchedules_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit OutputSchedules(std::shared_ptr<detail::OutputSchedules_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
