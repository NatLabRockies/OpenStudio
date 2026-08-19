/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WATERUSEEQUIPMENT_HPP
#define EPMODEL_WATERUSEEQUIPMENT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <string>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class WaterUseEquipment_Impl;
  }

  /** \brief Represents the EnergyPlus WaterUse:Equipment object.
   *
   * \par EnergyPlus object
   * \epobject{group-water-systems.html#wateruseequipment,WaterUse:Equipment}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::WaterUseEquipment</code>. <b>Not yet available:</b> water-use connection, schedule, zone, and fraction relationship methods. EPModel exposes end-use subcategory and peak-flow scalars.
   *
   * \par Known limitations
   * Use the owning water-use connection workflow for the object-list relationships; this wrapper manages only the persisted scalar surface.
   */
  class EPMODEL_API WaterUseEquipment : public ModelObject
  {
   public:
    explicit WaterUseEquipment(const Model& model);

    virtual ~WaterUseEquipment() override = default;
    WaterUseEquipment(const WaterUseEquipment& other) = default;
    WaterUseEquipment(WaterUseEquipment&& other) = default;
    WaterUseEquipment& operator=(const WaterUseEquipment&) = default;
    WaterUseEquipment& operator=(WaterUseEquipment&&) = default;

    static IddObjectType iddObjectType();

    std::string endUseSubcategory() const;
    bool isEndUseSubcategoryDefaulted() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);
    void resetEndUseSubcategory();

    double peakFlowRate() const;
    bool setPeakFlowRate(double peakFlowRate);

   protected:
    using ImplType = detail::WaterUseEquipment_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit WaterUseEquipment(std::shared_ptr<detail::WaterUseEquipment_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_WATERUSEEQUIPMENT_HPP
