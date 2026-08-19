/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DISTRICTHEATINGSTEAM_HPP
#define EPMODEL_DISTRICTHEATINGSTEAM_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;

  namespace detail {
    class DistrictHeatingSteam_Impl;
  }

/** \brief A district steam-heating plant component.
 *
 * \par EnergyPlus object
 * \epobject{group-plant-equipment.html#districtheatingsteam,DistrictHeating:Steam}
 *
 * \par Important behavior
 * The constructor seeds the capacity-fraction schedule; addToNode() accepts plant-supply placement only.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::DistrictHeatingSteam</code>.
 *
 * \par Known limitations
 * autosizedNominalCapacity() cannot resolve SQL sizing results.
 */
  class EPMODEL_API DistrictHeatingSteam : public StraightComponent
  {
   public:
    explicit DistrictHeatingSteam(const Model& model);

    virtual ~DistrictHeatingSteam() override = default;
    DistrictHeatingSteam(const DistrictHeatingSteam& other) = default;
    DistrictHeatingSteam(DistrictHeatingSteam&& other) = default;
    DistrictHeatingSteam& operator=(const DistrictHeatingSteam&) = default;
    DistrictHeatingSteam& operator=(DistrictHeatingSteam&&) = default;

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
    using ImplType = detail::DistrictHeatingSteam_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit DistrictHeatingSteam(std::shared_ptr<detail::DistrictHeatingSteam_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
