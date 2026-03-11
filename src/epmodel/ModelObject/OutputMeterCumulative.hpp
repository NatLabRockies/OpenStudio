/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTMETERCUMULATIVE_HPP
#define EPMODEL_OUTPUTMETERCUMULATIVE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class OutputMeterCumulative_Impl;
}

class EPMODEL_API OutputMeterCumulative : public ModelObject
{
 public:
  explicit OutputMeterCumulative(const Model& model);

  virtual ~OutputMeterCumulative() override = default;
  OutputMeterCumulative(const OutputMeterCumulative& other) = default;
  OutputMeterCumulative(OutputMeterCumulative&& other) = default;
  OutputMeterCumulative& operator=(const OutputMeterCumulative&) = default;
  OutputMeterCumulative& operator=(OutputMeterCumulative&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> reportingFrequencyValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: keyName/reportingFrequency map directly to EnergyPlus Output:Meter:Cumulative Key Name/Reporting Frequency.
  // - Field Mapping: Name is not an Output:Meter:Cumulative field here and remains managed by base ModelObject naming API.
  // - ForwardTranslator evidence: ForwardTranslateOutputMeter.cpp writes model meter name to Output:Meter:Cumulative Key Name and
  //   reportingFrequency to Reporting Frequency when cumulative=true and meterFileOnly=false; this epmodel class maps directly.
  // - TODO(parity): Keep scalar API stable while adding cross-object OutputMeter-family behavior in later parity work.
  std::string keyName() const;
  std::string reportingFrequency() const;

  bool isReportingFrequencyDefaulted() const;

  bool setKeyName(const std::string& keyName);
  bool setReportingFrequency(const std::string& reportingFrequency);

  void resetReportingFrequency();

 protected:
  using ImplType = detail::OutputMeterCumulative_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit OutputMeterCumulative(std::shared_ptr<detail::OutputMeterCumulative_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
