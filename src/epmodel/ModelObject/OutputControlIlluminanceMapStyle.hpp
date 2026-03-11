/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTCONTROLILLUMINANCEMAPSTYLE_HPP
#define EPMODEL_OUTPUTCONTROLILLUMINANCEMAPSTYLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class OutputControlIlluminanceMapStyle_Impl;
}

class EPMODEL_API OutputControlIlluminanceMapStyle : public ModelObject
{
 public:
  explicit OutputControlIlluminanceMapStyle(const Model& model);

  virtual ~OutputControlIlluminanceMapStyle() override = default;
  OutputControlIlluminanceMapStyle(const OutputControlIlluminanceMapStyle& other) = default;
  OutputControlIlluminanceMapStyle(OutputControlIlluminanceMapStyle&& other) = default;
  OutputControlIlluminanceMapStyle& operator=(const OutputControlIlluminanceMapStyle&) = default;
  OutputControlIlluminanceMapStyle& operator=(OutputControlIlluminanceMapStyle&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> columnSeparatorValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: columnSeparator maps directly to EnergyPlus OutputControl:IlluminanceMap:Style Column Separator.
  // - TODO(parity): Extend beyond scalar coverage only if future parity work requires additional behavior.
  std::string columnSeparator() const;
  bool isColumnSeparatorDefaulted() const;
  bool setColumnSeparator(const std::string& columnSeparator);
  void resetColumnSeparator();

 protected:
  using ImplType = detail::OutputControlIlluminanceMapStyle_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit OutputControlIlluminanceMapStyle(std::shared_ptr<detail::OutputControlIlluminanceMapStyle_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
