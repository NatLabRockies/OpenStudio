/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTSCHEDULES_HPP
#define EPMODEL_OUTPUTSCHEDULES_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class OutputSchedules_Impl;
  }

  /** \brief OutputSchedules.
   *
   * \par EnergyPlus object
   * \epobject{input-for-output.html#outputschedules,Output:Schedules}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::OutputSchedules</code>. The key-field setting maps directly to EnergyPlus. The object is unique within a model.
   *
   * \par Known limitations
   * Only the fields and relationships listed in this wrapper are available; broader Model-only helpers are not exposed.
   */
  class EPMODEL_API OutputSchedules : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~OutputSchedules() override = default;
    OutputSchedules(const OutputSchedules& other) = default;
    OutputSchedules(OutputSchedules&& other) = default;
    OutputSchedules& operator=(const OutputSchedules&) = default;
    OutputSchedules& operator=(OutputSchedules&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> keyFieldValues();
    static std::vector<std::string> validKeyFieldValues();
    std::string keyField() const;
    bool setKeyField(const std::string& keyField);

   protected:
    explicit OutputSchedules(const Model& model);

    using ImplType = detail::OutputSchedules_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit OutputSchedules(std::shared_ptr<detail::OutputSchedules_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
