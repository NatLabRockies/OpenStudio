/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SOLARCOLLECTORUNGLAZEDTRANSPIREDMULTISYSTEM_HPP
#define EPMODEL_SOLARCOLLECTORUNGLAZEDTRANSPIREDMULTISYSTEM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class SolarCollectorUnglazedTranspiredMultisystem_Impl;
}

class EPMODEL_API SolarCollectorUnglazedTranspiredMultisystem : public ModelObject
{
 public:
  explicit SolarCollectorUnglazedTranspiredMultisystem(const Model& model);

  virtual ~SolarCollectorUnglazedTranspiredMultisystem() override = default;
  SolarCollectorUnglazedTranspiredMultisystem(const SolarCollectorUnglazedTranspiredMultisystem& other) = default;
  SolarCollectorUnglazedTranspiredMultisystem(SolarCollectorUnglazedTranspiredMultisystem&& other) = default;
  SolarCollectorUnglazedTranspiredMultisystem& operator=(const SolarCollectorUnglazedTranspiredMultisystem&) = default;
  SolarCollectorUnglazedTranspiredMultisystem& operator=(SolarCollectorUnglazedTranspiredMultisystem&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type keeps IDD-derived class/API naming.
  // - Field Mapping: Name remains available through base ModelObject scalar API.
  // - Field Mapping: Solar Collector Name is an object-list relationship field and is excluded from scalar accessors.
  // - Field Mapping: Extensible node quad-tuples are relationship fields and excluded from scalar accessors.
  // - TODO(parity): Add relationship/extensible APIs incrementally after scalar saturation.

 protected:
  using ImplType = detail::SolarCollectorUnglazedTranspiredMultisystem_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit SolarCollectorUnglazedTranspiredMultisystem(std::shared_ptr<detail::SolarCollectorUnglazedTranspiredMultisystem_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
