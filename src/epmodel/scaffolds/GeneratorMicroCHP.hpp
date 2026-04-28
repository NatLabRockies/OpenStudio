/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORMICROCHP_HPP
#define EPMODEL_GENERATORMICROCHP_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class GeneratorMicroCHP_Impl;
}

class EPMODEL_API GeneratorMicroCHP : public ModelObject
{
 public:
  explicit GeneratorMicroCHP(const Model& model);

  virtual ~GeneratorMicroCHP() override = default;
  GeneratorMicroCHP(const GeneratorMicroCHP& other) = default;
  GeneratorMicroCHP(GeneratorMicroCHP&& other) = default;
  GeneratorMicroCHP& operator=(const GeneratorMicroCHP&) = default;
  GeneratorMicroCHP& operator=(GeneratorMicroCHP&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type keeps IDD-derived class/API naming.
  // - Field Mapping: Name remains available through base ModelObject scalar API.
  // - Field Mapping: Performance Parameters Name, Zone Name, Cooling Water Inlet/Outlet Node Name, Air Inlet/Outlet Node Name, Generator Fuel Supply
  //   Name, and Availability Schedule Name are relationship-like link fields and excluded from scalar accessors.
  // - TODO(parity): Add relationship APIs incrementally after scalar saturation.

 protected:
  using ImplType = detail::GeneratorMicroCHP_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit GeneratorMicroCHP(std::shared_ptr<detail::GeneratorMicroCHP_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
