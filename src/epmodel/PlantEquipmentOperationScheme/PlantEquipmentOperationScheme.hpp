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

  /** \brief Base interface for plant equipment operation schemes.
   *
   * \par EnergyPlus object
   * No single EnergyPlus object. This is the base for concrete plant
   * operation scheme objects.
   *
   * \par Important behavior
   * <code>plantLoop()</code> currently returns an empty optional. Plant-loop
   * ownership is represented by the plant operation scheme list rather than a
   * back-link on each scheme.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::PlantEquipmentOperationScheme</code>.
   *
   * No known public API differences.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API PlantEquipmentOperationScheme : public ModelObject
  {
   public:
    PlantEquipmentOperationScheme(IddObjectType type, const Model& model);

    virtual ~PlantEquipmentOperationScheme() override = default;
    PlantEquipmentOperationScheme(const PlantEquipmentOperationScheme& other) = default;
    PlantEquipmentOperationScheme(PlantEquipmentOperationScheme&& other) = default;
    PlantEquipmentOperationScheme& operator=(const PlantEquipmentOperationScheme&) = default;
    PlantEquipmentOperationScheme& operator=(PlantEquipmentOperationScheme&&) = default;

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
