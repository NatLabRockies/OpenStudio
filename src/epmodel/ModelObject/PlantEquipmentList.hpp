/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTLIST_HPP
#define EPMODEL_PLANTEQUIPMENTLIST_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class HVACComponent;
  class Model;

  namespace detail {
    class PlantEquipmentList_Impl;
  }

  /** \brief PlantEquipmentList.
   *
   * \par EnergyPlus object
   * \epobject{group-plant-condenser-control.html#plantequipmentlist,PlantEquipmentList}.
   *
   * \par OpenStudio Model API
   * There is no corresponding <code>openstudio::model</code> class. EPModel exposes typed HVAC equipment relationships for the extensible equipment rows; raw row/index APIs are not exposed.
   *
   * \par Known limitations
   * There is no corresponding <code>openstudio::model</code> class. EPModel exposes typed HVAC equipment relationships for the extensible equipment rows; raw row/index APIs are not exposed.
   */
  class EPMODEL_API PlantEquipmentList : public ModelObject
  {
   public:
    explicit PlantEquipmentList(const Model& model);

    virtual ~PlantEquipmentList() override = default;
    PlantEquipmentList(const PlantEquipmentList& other) = default;
    PlantEquipmentList(PlantEquipmentList&& other) = default;
    PlantEquipmentList& operator=(const PlantEquipmentList&) = default;
    PlantEquipmentList& operator=(PlantEquipmentList&&) = default;

    static IddObjectType iddObjectType();
    std::vector<HVACComponent> equipment() const;
    bool addEquipment(const HVACComponent& equipment);
    bool removeEquipment(const HVACComponent& equipment);
    void removeAllEquipment();
    bool replaceEquipment(const std::vector<HVACComponent>& equipment);

   protected:
    using ImplType = detail::PlantEquipmentList_Impl;

    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    friend class Model;

    explicit PlantEquipmentList(std::shared_ptr<detail::PlantEquipmentList_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
