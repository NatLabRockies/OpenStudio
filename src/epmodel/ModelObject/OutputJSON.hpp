/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTJSON_HPP
#define EPMODEL_OUTPUTJSON_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class OutputJSON_Impl;
  }

  /** \brief OutputJSON.
   *
   * \par EnergyPlus object
   * \epobject{input-for-output.html#outputjson,Output:JSON}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::OutputJSON</code>. The option type and output switches map directly to EnergyPlus.
   *
   * \par Known limitations
   * Only the fields and relationships listed in this wrapper are available; broader Model-only helpers are not exposed.
   */
  class EPMODEL_API OutputJSON : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~OutputJSON() override = default;
    OutputJSON(const OutputJSON& other) = default;
    OutputJSON(OutputJSON&& other) = default;
    OutputJSON& operator=(const OutputJSON&) = default;
    OutputJSON& operator=(OutputJSON&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> optionTypeValues();
    std::string optionType() const;
    bool setOptionType(const std::string& optionType);

    // outputJSON
    bool outputJSON() const;
    bool setOutputJSON(bool outputJSON);

    // outputCBOR
    bool outputCBOR() const;
    bool setOutputCBOR(bool outputCBOR);

    // outputMessagePack
    bool outputMessagePack() const;
    bool setOutputMessagePack(bool outputMessagePack);

   protected:
    explicit OutputJSON(const Model& model);

    using ImplType = detail::OutputJSON_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit OutputJSON(std::shared_ptr<detail::OutputJSON_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
