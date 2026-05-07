/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTCONTROLTABLESTYLE_HPP
#define EPMODEL_OUTPUTCONTROLTABLESTYLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class OutputControlTableStyle_Impl;
  }

  class EPMODEL_API OutputControlTableStyle : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~OutputControlTableStyle() override = default;
    OutputControlTableStyle(const OutputControlTableStyle& other) = default;
    OutputControlTableStyle(OutputControlTableStyle&& other) = default;
    OutputControlTableStyle& operator=(const OutputControlTableStyle&) = default;
    OutputControlTableStyle& operator=(OutputControlTableStyle&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> columnSeparatorValues();
    static std::vector<std::string> unitConversionValues();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model::OutputControlTableStyle scalar accessor names/signatures.
    // - Field Mapping: columnSeparator/unitConversion map directly to E+ OutputControl:Table:Style Column Separator/Unit Conversion.
    // - ForwardTranslator evidence: ForwardTranslateOutputControlTableStyle.cpp writes these preserved APIs directly to matching E+ fields.
    // - TODO(parity): Keep scalar API stable while extending any non-scalar parity behavior in future passes.
    std::string columnSeparator() const;
    bool setColumnSeparator(const std::string& columnSeparator);

    std::string unitConversion() const;
    bool setUnitConversion(const std::string& unitConversion);

   protected:
    explicit OutputControlTableStyle(const Model& model);

    using ImplType = detail::OutputControlTableStyle_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit OutputControlTableStyle(std::shared_ptr<detail::OutputControlTableStyle_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
