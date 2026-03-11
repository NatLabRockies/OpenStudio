/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTMETER_HPP
#define EPMODEL_OUTPUTMETER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class OutputMeter_Impl;
}

class EPMODEL_API OutputMeter : public ModelObject
{
 public:
  explicit OutputMeter(const Model& model);

  virtual ~OutputMeter() override = default;
  OutputMeter(const OutputMeter& other) = default;
  OutputMeter(OutputMeter&& other) = default;
  OutputMeter& operator=(const OutputMeter&) = default;
  OutputMeter& operator=(OutputMeter&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> reportingFrequencyValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: keyName/reportingFrequency map directly to EnergyPlus Output:Meter Key Name/Reporting Frequency.
  // - Field Mapping: Name is not an Output:Meter field here and remains managed by base ModelObject naming API.
  // - ForwardTranslator evidence: ForwardTranslateOutputMeter.cpp writes model meter name to Output:Meter Key Name and
  //   reportingFrequency to Reporting Frequency; this epmodel class maps directly to those scalar fields.
  // - TODO(parity): Keep scalar API stable while adding cross-object OutputMeter-family behavior in later parity work.
  std::string keyName() const;
  std::string reportingFrequency() const;

  bool isReportingFrequencyDefaulted() const;

  bool setKeyName(const std::string& keyName);
  bool setReportingFrequency(const std::string& reportingFrequency);

  void resetReportingFrequency();

 protected:
  using ImplType = detail::OutputMeter_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit OutputMeter(std::shared_ptr<detail::OutputMeter_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
