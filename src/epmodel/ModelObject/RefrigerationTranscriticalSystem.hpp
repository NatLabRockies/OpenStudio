/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONTRANSCRITICALSYSTEM_HPP
#define EPMODEL_REFRIGERATIONTRANSCRITICALSYSTEM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class ThermalZone;

  namespace detail {
    class RefrigerationTranscriticalSystem_Impl;
  }

  /** \brief RefrigerationTranscriticalSystem.
   *
   * \par EnergyPlus object
   * \epobject{group-refrigeration.html#refrigerationtranscriticalsystem,Refrigeration:TranscriticalSystem}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::RefrigerationTranscriticalSystem</code>. The exposed scalar controls and two suction-piping zones are available. Model's case, walk-in, compressor, and gas-cooler relationship helpers are not available.
   *
   * \par Known limitations
   * Only the fields and relationships listed in this wrapper are available; broader Model-only helpers are not exposed.
   */
  class EPMODEL_API RefrigerationTranscriticalSystem : public ModelObject
  {
   public:
    explicit RefrigerationTranscriticalSystem(const Model& model);

    virtual ~RefrigerationTranscriticalSystem() override = default;
    RefrigerationTranscriticalSystem(const RefrigerationTranscriticalSystem& other) = default;
    RefrigerationTranscriticalSystem(RefrigerationTranscriticalSystem&& other) = default;
    RefrigerationTranscriticalSystem& operator=(const RefrigerationTranscriticalSystem&) = default;
    RefrigerationTranscriticalSystem& operator=(RefrigerationTranscriticalSystem&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> refrigerationSystemWorkingFluidTypeValues();
    double receiverPressure() const;
    bool isReceiverPressureDefaulted() const;
    bool setReceiverPressure(double receiverPressure);
    void resetReceiverPressure();

    double subcoolerEffectiveness() const;
    bool isSubcoolerEffectivenessDefaulted() const;
    bool setSubcoolerEffectiveness(double subcoolerEffectiveness);
    void resetSubcoolerEffectiveness();

    std::string refrigerationSystemWorkingFluidType() const;
    bool setRefrigerationSystemWorkingFluidType(const std::string& refrigerationSystemWorkingFluidType);

    double sumUASuctionPipingforMediumTemperatureLoads() const;
    bool isSumUASuctionPipingforMediumTemperatureLoadsDefaulted() const;
    bool setSumUASuctionPipingforMediumTemperatureLoads(double sumUASuctionPipingforMediumTemperatureLoads);
    void resetSumUASuctionPipingforMediumTemperatureLoads();

    boost::optional<ThermalZone> mediumTemperatureSuctionPipingZone() const;
    bool setMediumTemperatureSuctionPipingZone(const ThermalZone& thermalZone);
    void resetMediumTemperatureSuctionPipingZone();

    double sumUASuctionPipingforLowTemperatureLoads() const;
    bool isSumUASuctionPipingforLowTemperatureLoadsDefaulted() const;
    bool setSumUASuctionPipingforLowTemperatureLoads(double sumUASuctionPipingforLowTemperatureLoads);
    void resetSumUASuctionPipingforLowTemperatureLoads();

    boost::optional<ThermalZone> lowTemperatureSuctionPipingZone() const;
    bool setLowTemperatureSuctionPipingZone(const ThermalZone& thermalZone);
    void resetLowTemperatureSuctionPipingZone();

    std::string endUseSubcategory() const;
    bool isEndUseSubcategoryDefaulted() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);
    void resetEndUseSubcategory();

   protected:
    using ImplType = detail::RefrigerationTranscriticalSystem_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit RefrigerationTranscriticalSystem(std::shared_ptr<detail::RefrigerationTranscriticalSystem_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
