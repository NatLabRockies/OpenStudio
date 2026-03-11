/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PIPEADIABATICSTEAM_HPP
#define EPMODEL_PIPEADIABATICSTEAM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class PipeAdiabaticSteam_Impl;
}

class EPMODEL_API PipeAdiabaticSteam : public ModelObject
{
 public:
  explicit PipeAdiabaticSteam(const Model& model);

  virtual ~PipeAdiabaticSteam() override = default;
  PipeAdiabaticSteam(const PipeAdiabaticSteam& other) = default;
  PipeAdiabaticSteam(PipeAdiabaticSteam&& other) = default;
  PipeAdiabaticSteam& operator=(const PipeAdiabaticSteam&) = default;
  PipeAdiabaticSteam& operator=(PipeAdiabaticSteam&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type keeps IDD-derived class/API naming.
  // - Field Mapping: Name remains available through base ModelObject scalar API.
  // - Field Mapping: Inlet Node Name and Outlet Node Name are relationship-like node link fields and excluded from scalar accessors.
  // - TODO(parity): Add typed relationship APIs incrementally after scalar saturation.

 protected:
  using ImplType = detail::PipeAdiabaticSteam_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit PipeAdiabaticSteam(std::shared_ptr<detail::PipeAdiabaticSteam_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
