/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTDAYLIGHTFACTORS_HPP
#define EPMODEL_OUTPUTDAYLIGHTFACTORS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class OutputDaylightFactors_Impl;
}

class EPMODEL_API OutputDaylightFactors : public ModelObject
{
 public:
  explicit OutputDaylightFactors(const Model& model);

  virtual ~OutputDaylightFactors() override = default;
  OutputDaylightFactors(const OutputDaylightFactors& other) = default;
  OutputDaylightFactors(OutputDaylightFactors&& other) = default;
  OutputDaylightFactors& operator=(const OutputDaylightFactors&) = default;
  OutputDaylightFactors& operator=(OutputDaylightFactors&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> reportingDaysValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: reportingDays maps directly to EnergyPlus Output:DaylightFactors Reporting Days.
  // - TODO(parity): Extend beyond scalar coverage only if future parity work requires additional behavior.
  std::string reportingDays() const;
  bool setReportingDays(const std::string& reportingDays);

 protected:
  using ImplType = detail::OutputDaylightFactors_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit OutputDaylightFactors(std::shared_ptr<detail::OutputDaylightFactors_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
