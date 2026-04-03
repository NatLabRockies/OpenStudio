/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONSCHEME_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONSCHEME_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <boost/optional.hpp>
#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class PlantLoop;

  namespace detail {
    class PlantEquipmentOperationScheme_Impl;
  }

  class EPMODEL_API PlantEquipmentOperationScheme : public ModelObject
  {
   public:
    PlantEquipmentOperationScheme(IddObjectType type, const Model& model);

    virtual ~PlantEquipmentOperationScheme() override = default;
    PlantEquipmentOperationScheme(const PlantEquipmentOperationScheme& other) = default;
    PlantEquipmentOperationScheme(PlantEquipmentOperationScheme&& other) = default;
    PlantEquipmentOperationScheme& operator=(const PlantEquipmentOperationScheme&) = default;
    PlantEquipmentOperationScheme& operator=(PlantEquipmentOperationScheme&&) = default;

    // Schema Alignment Notes:
    // - Canonical Counterpart: openstudio::model::PlantEquipmentOperationScheme.
    // - API: This is a public base wrapper for primary plant-operation scheme types so PlantLoop can preserve canonical return types.
    // - Relationship Mapping: plantLoop() follows the canonical counterpart and currently returns no owner by default; loop-owned storage remains
    //   centralized on the PlantEquipmentOperationSchemes owner object rather than back-linked per scheme object.
    boost::optional<PlantLoop> plantLoop() const;

   protected:
    using ImplType = detail::PlantEquipmentOperationScheme_Impl;

    explicit PlantEquipmentOperationScheme(std::shared_ptr<detail::PlantEquipmentOperationScheme_Impl> impl);

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
