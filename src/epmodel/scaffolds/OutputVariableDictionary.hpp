/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTVARIABLEDICTIONARY_HPP
#define EPMODEL_OUTPUTVARIABLEDICTIONARY_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class OutputVariableDictionary_Impl;
  }

  class EPMODEL_API OutputVariableDictionary : public ModelObject
  {
   public:
    explicit OutputVariableDictionary(const Model& model);

    virtual ~OutputVariableDictionary() override = default;
    OutputVariableDictionary(const OutputVariableDictionary& other) = default;
    OutputVariableDictionary(OutputVariableDictionary&& other) = default;
    OutputVariableDictionary& operator=(const OutputVariableDictionary&) = default;
    OutputVariableDictionary& operator=(OutputVariableDictionary&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> keyFieldValues();
    static std::vector<std::string> sortOptionValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
    // - Field Mapping: keyField/sortOption map directly to E+ Output:VariableDictionary Key Field/Sort Option.
    // - ForwardTranslator evidence: ForwardTranslator::createStandardOutputRequests writes Key Field=IDF and Sort Option=Unsorted.
    // - TODO(parity): Keep this scalar API stable while adding any future non-scalar parity behavior.
    std::string keyField() const;
    bool isKeyFieldDefaulted() const;
    bool setKeyField(const std::string& keyField);
    void resetKeyField();

    boost::optional<std::string> sortOption() const;
    bool setSortOption(const std::string& sortOption);
    void resetSortOption();

   protected:
    using ImplType = detail::OutputVariableDictionary_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit OutputVariableDictionary(std::shared_ptr<detail::OutputVariableDictionary_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
