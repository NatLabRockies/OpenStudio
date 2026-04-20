/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTCONTROLSIZINGSTYLE_HPP
#define EPMODEL_OUTPUTCONTROLSIZINGSTYLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class OutputControlSizingStyle_Impl;
}

class EPMODEL_API OutputControlSizingStyle : public ModelObject
{
 public:
  explicit OutputControlSizingStyle(const Model& model);

  virtual ~OutputControlSizingStyle() override = default;
  OutputControlSizingStyle(const OutputControlSizingStyle& other) = default;
  OutputControlSizingStyle(OutputControlSizingStyle&& other) = default;
  OutputControlSizingStyle& operator=(const OutputControlSizingStyle&) = default;
  OutputControlSizingStyle& operator=(OutputControlSizingStyle&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> columnSeparatorValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: columnSeparator maps directly to E+ OutputControl:Sizing:Style Column Separator.
  // - TODO(parity): Extend beyond scalar coverage only if future parity work requires additional behavior.
  std::string columnSeparator() const;
  bool setColumnSeparator(const std::string& columnSeparator);

 protected:
  using ImplType = detail::OutputControlSizingStyle_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit OutputControlSizingStyle(std::shared_ptr<detail::OutputControlSizingStyle_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
