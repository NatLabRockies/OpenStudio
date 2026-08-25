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

  /** \brief OutputControlTableStyle.
   *
   * \par EnergyPlus object
   * \epobject{outputcontrol-table-style.html#outputcontroltablestyle,OutputControl:Table:Style}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::OutputControlTableStyle</code>. The column-separator and unit-conversion fields map directly to EnergyPlus.
   *
   * \par Known limitations
   * Only the fields and relationships listed in this wrapper are available; broader Model-only helpers are not exposed.
   */
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
