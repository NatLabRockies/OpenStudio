/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTSQLITE_HPP
#define EPMODEL_OUTPUTSQLITE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class OutputSQLite_Impl;
}

class EPMODEL_API OutputSQLite : public ModelObject
{
 public:
  explicit OutputSQLite(const Model& model);

  virtual ~OutputSQLite() override = default;
  OutputSQLite(const OutputSQLite& other) = default;
  OutputSQLite(OutputSQLite&& other) = default;
  OutputSQLite& operator=(const OutputSQLite&) = default;
  OutputSQLite& operator=(OutputSQLite&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> optionTypeValues();
  static std::vector<std::string> unitConversionforTabularDataValues();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model::OutputSQLite scalar accessor names/signatures.
  // - Field Mapping: optionType/unitConversionforTabularData map directly to E+ Output:SQLite Option Type/Unit Conversion for Tabular Data.
  // - ForwardTranslator evidence: ForwardTranslateOutputSQLite.cpp writes these preserved APIs directly to Output:SQLite fields.
  // - TODO(parity): Keep scalar API stable while extending any non-scalar parity behavior in future passes.
  std::string optionType() const;
  std::string unitConversionforTabularData() const;

  bool setOptionType(const std::string& optionType);
  bool setUnitConversionforTabularData(const std::string& unitConversionforTabularData);

 protected:
  using ImplType = detail::OutputSQLite_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit OutputSQLite(std::shared_ptr<detail::OutputSQLite_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
