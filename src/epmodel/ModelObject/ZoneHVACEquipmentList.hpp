/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACEQUIPMENTLIST_HPP
#define EPMODEL_ZONEHVACEQUIPMENTLIST_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <boost/optional.hpp>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class ModelObject;
  class Schedule;
  class ThermalZone;

  namespace detail {
    class ZoneHVACEquipmentList_Impl;
  }

  /** \brief ZoneHVACEquipmentList.
   *
   * \par EnergyPlus object
   * \epobject{group-zone-equipment.html#zonehvacequipmentlist,ZoneHVAC:EquipmentList}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::ZoneHVACEquipmentList</code>. <b>Changed:</b> EPModel also permits direct construction from <code>Model</code>; Model construction requires a thermal zone. The load-distribution field and typed equipment-priority relationships are exposed.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API ZoneHVACEquipmentList : public ModelObject
  {
   public:
    explicit ZoneHVACEquipmentList(const Model& model);
    explicit ZoneHVACEquipmentList(const ThermalZone& thermalZone);

    virtual ~ZoneHVACEquipmentList() override = default;
    ZoneHVACEquipmentList(const ZoneHVACEquipmentList& other) = default;
    ZoneHVACEquipmentList(ZoneHVACEquipmentList&& other) = default;
    ZoneHVACEquipmentList& operator=(const ZoneHVACEquipmentList&) = default;
    ZoneHVACEquipmentList& operator=(ZoneHVACEquipmentList&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> loadDistributionSchemeValues();
    static std::vector<std::string> validLoadDistributionSchemeValues();
    std::string loadDistributionScheme() const;
    bool setLoadDistributionScheme(const std::string& loadDistributionScheme);
    bool isLoadDistributionSchemeDefaulted() const;
    void resetLoadDistributionScheme();

    bool addEquipment(const ModelObject& equipment);
    bool removeEquipment(const ModelObject& equipment);

    bool setCoolingPriority(const ModelObject& equipment, unsigned priority);
    bool setHeatingPriority(const ModelObject& equipment, unsigned priority);

    std::vector<ModelObject> equipment() const;
    std::vector<ModelObject> equipmentInHeatingOrder() const;
    std::vector<ModelObject> equipmentInCoolingOrder() const;

    ThermalZone thermalZone() const;

    unsigned heatingPriority(const ModelObject& equipment) const;
    unsigned coolingPriority(const ModelObject& equipment) const;

    boost::optional<double> sequentialCoolingFraction(const ModelObject& equipment) const;
    boost::optional<Schedule> sequentialCoolingFractionSchedule(const ModelObject& equipment) const;
    boost::optional<double> sequentialHeatingFraction(const ModelObject& equipment) const;
    boost::optional<Schedule> sequentialHeatingFractionSchedule(const ModelObject& equipment) const;

    bool setSequentialCoolingFraction(const ModelObject& equipment, double fraction);
    bool setSequentialCoolingFractionSchedule(const ModelObject& equipment, Schedule& schedule);
    bool setSequentialHeatingFraction(const ModelObject& equipment, double fraction);
    bool setSequentialHeatingFractionSchedule(const ModelObject& equipment, Schedule& schedule);

   protected:
    using ImplType = detail::ZoneHVACEquipmentList_Impl;

    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    friend class Model;

    explicit ZoneHVACEquipmentList(std::shared_ptr<detail::ZoneHVACEquipmentList_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
