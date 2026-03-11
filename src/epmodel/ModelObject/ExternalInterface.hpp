/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACE_HPP
#define EPMODEL_EXTERNALINTERFACE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ExternalInterface_Impl;
}

class EPMODEL_API ExternalInterface : public ModelObject
{
 public:
  explicit ExternalInterface(const Model& model);

  virtual ~ExternalInterface() override = default;
  ExternalInterface(const ExternalInterface& other) = default;
  ExternalInterface(ExternalInterface&& other) = default;
  ExternalInterface& operator=(const ExternalInterface&) = default;
  ExternalInterface& operator=(ExternalInterface&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> nameofExternalInterfaceValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model scalar accessor names/signatures for this model-counterpart class.
  // - Field Mapping: nameofExternalInterface maps directly to EnergyPlus ExternalInterface: Name of External Interface.
  // - TODO(parity): Keep this mapping unless upstream model API changes for ExternalInterface parity milestones.
  std::string nameofExternalInterface() const;
  bool setNameofExternalInterface(const std::string& nameofExternalInterface);

 protected:
  using ImplType = detail::ExternalInterface_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ExternalInterface(std::shared_ptr<detail::ExternalInterface_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
