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

  /** \brief OutputSQLite.
   *
   * \par EnergyPlus object
   * \epobject{input-for-output.html#outputsqlite,Output:SQLite}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::OutputSQLite</code>. The option type and tabular-unit-conversion settings map directly to EnergyPlus.
   *
   * \par Known limitations
   * Only the fields and relationships listed in this wrapper are available; broader Model-only helpers are not exposed.
   */
  class EPMODEL_API OutputSQLite : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~OutputSQLite() override = default;
    OutputSQLite(const OutputSQLite& other) = default;
    OutputSQLite(OutputSQLite&& other) = default;
    OutputSQLite& operator=(const OutputSQLite&) = default;
    OutputSQLite& operator=(OutputSQLite&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> optionTypeValues();
    static std::vector<std::string> unitConversionforTabularDataValues();
    std::string optionType() const;
    bool setOptionType(const std::string& optionType);

    std::string unitConversionforTabularData() const;
    bool setUnitConversionforTabularData(const std::string& unitConversionforTabularData);

   protected:
    explicit OutputSQLite(const Model& model);

    using ImplType = detail::OutputSQLite_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit OutputSQLite(std::shared_ptr<detail::OutputSQLite_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
