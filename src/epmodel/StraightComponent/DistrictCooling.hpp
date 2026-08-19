/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DISTRICTCOOLING_HPP
#define EPMODEL_DISTRICTCOOLING_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;

  namespace detail {
    class DistrictCooling_Impl;
  }

/** \brief A district cooling plant component.
 *
 * \par EnergyPlus object
 * \epobject{group-plant-equipment.html#districtcooling,DistrictCooling}
 *
 * \par Important behavior
 * The constructor seeds the capacity-fraction schedule; addToNode() accepts plant-supply placement only.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::DistrictCooling</code>.
 *
 * \par Known limitations
 * autosizedNominalCapacity() cannot resolve SQL sizing results.
 */
  class EPMODEL_API DistrictCooling : public StraightComponent
  {
   public:
    explicit DistrictCooling(const Model& model);

    virtual ~DistrictCooling() override = default;
    DistrictCooling(const DistrictCooling& other) = default;
    DistrictCooling(DistrictCooling&& other) = default;
    DistrictCooling& operator=(const DistrictCooling&) = default;
    DistrictCooling& operator=(DistrictCooling&&) = default;

    static IddObjectType iddObjectType();

    boost::optional<double> nominalCapacity() const;
    Schedule capacityFractionSchedule() const;

    bool setNominalCapacity(double nominalCapacity);
    bool setCapacityFractionSchedule(Schedule& schedule);
    void autosizeNominalCapacity();
    bool isNominalCapacityAutosized() const;

    boost::optional<double> autosizedNominalCapacity() const;

    bool addToNode(Node& node);

   protected:
    using ImplType = detail::DistrictCooling_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit DistrictCooling(std::shared_ptr<detail::DistrictCooling_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
