/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DISTRICTHEATINGWATER_HPP
#define EPMODEL_DISTRICTHEATINGWATER_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;

  namespace detail {
    class DistrictHeatingWater_Impl;
  }

/** \brief A district hot-water heating plant component.
 *
 * \par EnergyPlus object
 * \epobject{group-plant-equipment.html#districtheating,DistrictHeating:Water}
 *
 * \par Important behavior
 * The constructor seeds the capacity-fraction schedule; addToNode() accepts plant-supply placement only.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::DistrictHeatingWater</code>.
 *
 * \par Known limitations
 * autosizedNominalCapacity() cannot resolve SQL sizing results.
 */
  class EPMODEL_API DistrictHeatingWater : public StraightComponent
  {
   public:
    explicit DistrictHeatingWater(const Model& model);

    virtual ~DistrictHeatingWater() override = default;
    DistrictHeatingWater(const DistrictHeatingWater& other) = default;
    DistrictHeatingWater(DistrictHeatingWater&& other) = default;
    DistrictHeatingWater& operator=(const DistrictHeatingWater&) = default;
    DistrictHeatingWater& operator=(DistrictHeatingWater&&) = default;

    static IddObjectType iddObjectType();

    boost::optional<double> nominalCapacity() const;
    Schedule capacityFractionSchedule() const;
    bool isNominalCapacityAutosized() const;
    boost::optional<double> autosizedNominalCapacity() const;

    bool setNominalCapacity(double nominalCapacity);
    bool setCapacityFractionSchedule(Schedule& schedule);
    void autosizeNominalCapacity();

    bool addToNode(Node& node);

   protected:
    using ImplType = detail::DistrictHeatingWater_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit DistrictHeatingWater(std::shared_ptr<detail::DistrictHeatingWater_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
