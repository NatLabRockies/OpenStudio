/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DESIGNSPECIFICATIONOUTDOORAIR_HPP
#define EPMODEL_DESIGNSPECIFICATIONOUTDOORAIR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <boost/optional.hpp>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;

  namespace detail {
    class DesignSpecificationOutdoorAir_Impl;
  }

  /** \brief Specifies outdoor-air flow requirements for a zone or space.
   *
   * \par EnergyPlus object
   * \epobject{group-design-objects.html#designspecificationoutdoorair,DesignSpecification:OutdoorAir}.
   *
   * \par Important behavior
   * Blank scalar fields remain blank in the stored object, while getters
   * project the OpenStudio Model defaults (<code>Sum</code> and 0.0). A blank
   * outdoor-air schedule field is repaired with a uniquely resolved persisted
   * schedule only when loading; missing or ambiguous names are not guessed.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::DesignSpecificationOutdoorAir</code>. The Model
   * class exposes the same public fields and schedule relationship. EPModel is
   * a <code>ModelObject</code>; the Model counterpart is a
   * <code>ResourceObject</code>.
   *
   * \par Known limitations
   * The EnergyPlus Proportional Control Minimum Outdoor Air Flow Rate Schedule
   * field has no public API in either wrapper.
   */
  class EPMODEL_API DesignSpecificationOutdoorAir : public ModelObject
  {
   public:
    explicit DesignSpecificationOutdoorAir(const Model& model);

    virtual ~DesignSpecificationOutdoorAir() override = default;
    DesignSpecificationOutdoorAir(const DesignSpecificationOutdoorAir& other) = default;
    DesignSpecificationOutdoorAir(DesignSpecificationOutdoorAir&& other) = default;
    DesignSpecificationOutdoorAir& operator=(const DesignSpecificationOutdoorAir&) = default;
    DesignSpecificationOutdoorAir& operator=(DesignSpecificationOutdoorAir&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> outdoorAirMethodValues();

    /** \deprecated */
    static std::vector<std::string> validOutdoorAirMethodValues();


    std::string outdoorAirMethod() const;
    bool isOutdoorAirMethodDefaulted() const;
    bool setOutdoorAirMethod(const std::string& value);
    void resetOutdoorAirMethod();

    double outdoorAirFlowperPerson() const;
    bool isOutdoorAirFlowperPersonDefaulted() const;
    bool setOutdoorAirFlowperPerson(double value);
    void resetOutdoorAirFlowperPerson();

    double outdoorAirFlowperFloorArea() const;
    bool isOutdoorAirFlowperFloorAreaDefaulted() const;
    bool setOutdoorAirFlowperFloorArea(double value);
    void resetOutdoorAirFlowperFloorArea();

    double outdoorAirFlowRate() const;
    bool isOutdoorAirFlowRateDefaulted() const;
    bool setOutdoorAirFlowRate(double value);
    void resetOutdoorAirFlowRate();

    double outdoorAirFlowAirChangesperHour() const;
    bool isOutdoorAirFlowAirChangesperHourDefaulted() const;
    bool setOutdoorAirFlowAirChangesperHour(double value);
    void resetOutdoorAirFlowAirChangesperHour();

    boost::optional<Schedule> outdoorAirFlowRateFractionSchedule() const;
    bool setOutdoorAirFlowRateFractionSchedule(Schedule& schedule);
    void resetOutdoorAirFlowRateFractionSchedule();

   protected:
    using ImplType = detail::DesignSpecificationOutdoorAir_Impl;

    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    friend class Model;

    explicit DesignSpecificationOutdoorAir(std::shared_ptr<detail::DesignSpecificationOutdoorAir_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
