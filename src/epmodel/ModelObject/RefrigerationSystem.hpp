/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONSYSTEM_HPP
#define EPMODEL_REFRIGERATIONSYSTEM_HPP

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
    class RefrigerationSystem_Impl;
  }

  /** \brief RefrigerationSystem.
   *
   * \par EnergyPlus object
   * \epobject{group-refrigeration.html#refrigerationsystem,Refrigeration:System}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::RefrigerationSystem</code>. The exposed scalar controls and suction-piping zone are available. Model's case, walk-in, compressor, condenser, subcooler, and other refrigeration relationship helpers are not available.
   *
   * \par Known limitations
   * Only the fields and relationships listed in this wrapper are available; broader Model-only helpers are not exposed.
   */
  class EPMODEL_API RefrigerationSystem : public ModelObject
  {
   public:
    explicit RefrigerationSystem(const Model& model);

    virtual ~RefrigerationSystem() override = default;
    RefrigerationSystem(const RefrigerationSystem& other) = default;
    RefrigerationSystem(RefrigerationSystem&& other) = default;
    RefrigerationSystem& operator=(const RefrigerationSystem&) = default;
    RefrigerationSystem& operator=(RefrigerationSystem&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> refrigerationSystemWorkingFluidTypeValues();
    static std::vector<std::string> suctionTemperatureControlTypeValues();
    static std::vector<std::string> intercoolerTypeValues();
    double minimumCondensingTemperature() const;
    bool setMinimumCondensingTemperature(double minimumCondensingTemperature);

    std::string refrigerationSystemWorkingFluidType() const;
    bool setRefrigerationSystemWorkingFluidType(const std::string& refrigerationSystemWorkingFluidType);

    std::string suctionTemperatureControlType() const;
    bool setSuctionTemperatureControlType(const std::string& suctionTemperatureControlType);
    bool isSuctionTemperatureControlTypeDefaulted() const;
    void resetSuctionTemperatureControlType();

    std::string endUseSubcategory() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);
    bool isEndUseSubcategoryDefaulted() const;
    void resetEndUseSubcategory();

    std::string intercoolerType() const;
    bool setIntercoolerType(const std::string& intercoolerType);
    bool isIntercoolerTypeDefaulted() const;
    void resetIntercoolerType();

    double sumUASuctionPiping() const;
    bool setSumUASuctionPiping(double sumUASuctionPiping);
    bool isSumUASuctionPipingDefaulted() const;
    void resetSumUASuctionPiping();

    boost::optional<ThermalZone> suctionPipingZone() const;
    bool setSuctionPipingZone(const ThermalZone& thermalZone);
    void resetSuctionPipingZone();

    double shellandCoilIntercoolerEffectiveness() const;
    bool setShellandCoilIntercoolerEffectiveness(double shellandCoilIntercoolerEffectiveness);
    bool isShellandCoilIntercoolerEffectivenessDefaulted() const;
    void resetShellandCoilIntercoolerEffectiveness();

   protected:
    using ImplType = detail::RefrigerationSystem_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit RefrigerationSystem(std::shared_ptr<detail::RefrigerationSystem_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_REFRIGERATIONSYSTEM_HPP
