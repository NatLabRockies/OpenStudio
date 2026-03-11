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

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::WaterUseEquipment scalar-field naming for endUseSubcategory and peakFlowRate.
    // - Field Mapping: endUseSubcategory and peakFlowRate map directly to EnergyPlus WaterUse:Equipment fields.
    // - Field Mapping: Flow Rate Fraction Schedule Name, Target Temperature Schedule Name, Hot/Cold Water Supply
    //   Temperature Schedule Name, Zone Name, Sensible Fraction Schedule Name, and Latent Fraction Schedule Name are
    //   relationship-like references and intentionally excluded from scalar accessor generation in this run.
    // - ForwardTranslator evidence: ForwardTranslateWaterUseEquipment.cpp reads these exact scalars while the remaining
    //   relationship fields drive schedule/zone/definition wiring.
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
