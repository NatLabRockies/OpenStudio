/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONSTRUCTIONWINDOWDATAFILE_HPP
#define EPMODEL_CONSTRUCTIONWINDOWDATAFILE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ConstructionWindowDataFile_Impl;
}

class EPMODEL_API ConstructionWindowDataFile : public ModelObject
{
 public:
  explicit ConstructionWindowDataFile(const Model& model);

  virtual ~ConstructionWindowDataFile() override = default;
  ConstructionWindowDataFile(const ConstructionWindowDataFile& other) = default;
  ConstructionWindowDataFile(ConstructionWindowDataFile&& other) = default;
  ConstructionWindowDataFile& operator=(const ConstructionWindowDataFile&) = default;
  ConstructionWindowDataFile& operator=(ConstructionWindowDataFile&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: fileName maps directly to EnergyPlus Construction:WindowDataFile field File Name.
  // - Field Mapping: Name remains available through base ModelObject name accessors.
  // - TODO(parity): Revisit API layering if model-counterpart parity is introduced later.
  boost::optional<std::string> fileName() const;
  bool setFileName(const std::string& fileName);
  void resetFileName();

 protected:
  using ImplType = detail::ConstructionWindowDataFile_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ConstructionWindowDataFile(std::shared_ptr<detail::ConstructionWindowDataFile_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
