/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEMIXING_HPP
#define EPMODEL_ZONEMIXING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <string>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneMixing_Impl;
  }

  /** \brief ZoneMixing.
   *
   * \par EnergyPlus object
   * \epobject{group-airflow.html#zonemixing,ZoneMixing}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::ZoneMixing</code>. <b>Changed:</b> EPModel exposes direct construction from <code>Model</code>; Model construction requires a thermal zone or space. The scalar flow-rate choices and delta temperature are exposed. Model's zone, space, and schedule relationships are not available.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API ZoneMixing : public ModelObject
  {
   public:
    explicit ZoneMixing(const Model& model);

    virtual ~ZoneMixing() override = default;
    ZoneMixing(const ZoneMixing& other) = default;
    ZoneMixing(ZoneMixing&& other) = default;
    ZoneMixing& operator=(const ZoneMixing&) = default;
    ZoneMixing& operator=(ZoneMixing&&) = default;

    static IddObjectType iddObjectType();
    std::string designFlowRateCalculationMethod() const;

    boost::optional<double> designFlowRate() const;
    bool setDesignFlowRate(double designFlowRate);
    void resetDesignFlowRate();

    boost::optional<double> flowRateperFloorArea() const;
    bool setFlowRateperFloorArea(double flowRateperFloorArea);
    void resetFlowRateperFloorArea();

    boost::optional<double> flowRateperPerson() const;
    bool setFlowRateperPerson(double flowRateperPerson);
    void resetFlowRateperPerson();

    boost::optional<double> airChangesperHour() const;
    bool setAirChangesperHour(double airChangesperHour);
    void resetAirChangesperHour();

    boost::optional<double> deltaTemperature() const;
    bool setDeltaTemperature(double deltaTemperature);
    void resetDeltaTemperature();

   protected:
    using ImplType = detail::ZoneMixing_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneMixing(std::shared_ptr<detail::ZoneMixing_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
