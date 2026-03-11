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

  namespace detail {
    class RefrigerationTranscriticalSystem_Impl;
  }

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

    // Schema Alignment Notes:
    // - API: Preserve the openstudio::model scalar accessor names/signatures for receiverPressure, subcoolerEffectiveness,
    //   refrigerationSystemWorkingFluidType, sumUASuctionPipingforMediumTemperatureLoads, sumUASuctionPipingforLowTemperatureLoads, and endUseSubcategory.
    // - Field Mapping: Each scalar maps directly to the EnergyPlus Refrigeration:TranscriticalSystem fields documented in
    //   ForwardTranslator::translateRefrigerationTranscriticalSystem.
    // - Field Mapping: Medium/Low temperature Refrigerated CaseAndWalkInList, compressor lists, Refrigeration Gas Cooler, and
    //   suction piping zone relationship fields are intentionally excluded from this scalar-only surface.
    // - TODO(parity): Add non-scalar relationship APIs later without changing scalar signatures.
    double receiverPressure() const;
    bool isReceiverPressureDefaulted() const;

    double subcoolerEffectiveness() const;
    bool isSubcoolerEffectivenessDefaulted() const;

    std::string refrigerationSystemWorkingFluidType() const;

    double sumUASuctionPipingforMediumTemperatureLoads() const;
    bool isSumUASuctionPipingforMediumTemperatureLoadsDefaulted() const;

    double sumUASuctionPipingforLowTemperatureLoads() const;
    bool isSumUASuctionPipingforLowTemperatureLoadsDefaulted() const;

    std::string endUseSubcategory() const;
    bool isEndUseSubcategoryDefaulted() const;

    bool setReceiverPressure(double receiverPressure);
    void resetReceiverPressure();

    bool setSubcoolerEffectiveness(double subcoolerEffectiveness);
    void resetSubcoolerEffectiveness();

    bool setRefrigerationSystemWorkingFluidType(const std::string& refrigerationSystemWorkingFluidType);

    bool setSumUASuctionPipingforMediumTemperatureLoads(double sumUASuctionPipingforMediumTemperatureLoads);
    void resetSumUASuctionPipingforMediumTemperatureLoads();

    bool setSumUASuctionPipingforLowTemperatureLoads(double sumUASuctionPipingforLowTemperatureLoads);
    void resetSumUASuctionPipingforLowTemperatureLoads();

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
