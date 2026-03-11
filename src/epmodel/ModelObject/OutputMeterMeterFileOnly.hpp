/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTMETERMETERFILEONLY_HPP
#define EPMODEL_OUTPUTMETERMETERFILEONLY_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class OutputMeterMeterFileOnly_Impl;
}

class EPMODEL_API OutputMeterMeterFileOnly : public ModelObject
{
 public:
  explicit OutputMeterMeterFileOnly(const Model& model);

  virtual ~OutputMeterMeterFileOnly() override = default;
  OutputMeterMeterFileOnly(const OutputMeterMeterFileOnly& other) = default;
  OutputMeterMeterFileOnly(OutputMeterMeterFileOnly&& other) = default;
  OutputMeterMeterFileOnly& operator=(const OutputMeterMeterFileOnly&) = default;
  OutputMeterMeterFileOnly& operator=(OutputMeterMeterFileOnly&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> reportingFrequencyValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: keyName/reportingFrequency map directly to EnergyPlus Output:Meter:MeterFileOnly
  //   Key Name/Reporting Frequency.
  // - Field Mapping: Name is not an Output:Meter:MeterFileOnly field here and remains managed by
  //   base ModelObject naming API.
  // - ForwardTranslator evidence: ForwardTranslateOutputMeter.cpp writes model meter name to
  //   Output:Meter:MeterFileOnly Key Name and reportingFrequency to Reporting Frequency when
  //   cumulative=false and meterFileOnly=true; this epmodel class maps directly.
  // - TODO(parity): Keep scalar API stable while adding cross-object OutputMeter-family behavior in later parity work.
  std::string keyName() const;
  std::string reportingFrequency() const;

  bool isReportingFrequencyDefaulted() const;

  bool setKeyName(const std::string& keyName);
  bool setReportingFrequency(const std::string& reportingFrequency);

  void resetReportingFrequency();

 protected:
  using ImplType = detail::OutputMeterMeterFileOnly_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit OutputMeterMeterFileOnly(std::shared_ptr<detail::OutputMeterMeterFileOnly_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
