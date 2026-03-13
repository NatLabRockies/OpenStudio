/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ELECTRICLOADCENTERSTORAGECONVERTER_HPP
#define EPMODEL_ELECTRICLOADCENTERSTORAGECONVERTER_HPP

#include "EPModelAPI.hpp"
#include "ParentObject/ParentObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ElectricLoadCenterStorageConverter_Impl;
  }

  class EPMODEL_API ElectricLoadCenterStorageConverter : public ParentObject
  {
   public:
    explicit ElectricLoadCenterStorageConverter(const Model& model);

    virtual ~ElectricLoadCenterStorageConverter() override = default;
    ElectricLoadCenterStorageConverter(const ElectricLoadCenterStorageConverter& other) = default;
    ElectricLoadCenterStorageConverter(ElectricLoadCenterStorageConverter&& other) = default;
    ElectricLoadCenterStorageConverter& operator=(const ElectricLoadCenterStorageConverter&) = default;
    ElectricLoadCenterStorageConverter& operator=(ElectricLoadCenterStorageConverter&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> powerConversionEfficiencyMethodValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::ElectricLoadCenterStorageConverter scalar accessor names/signatures.
    // - Field Mapping: powerConversionEfficiencyMethod, simpleFixedEfficiency, designMaximumContinuousInputPower,
    //   ancillaryPowerConsumedInStandby, and radiativeFraction map directly to EnergyPlus
    //   ElectricLoadCenter:Storage:Converter scalar fields.
    // - Field Mapping: Availability Schedule Name, Efficiency Function of Power Curve Name, Zone Name,
    //   and parent linkage are relationship-like fields and intentionally excluded from scalar accessor scope.
    // - ForwardTranslator evidence: ForwardTranslateElectricLoadCenterStorageConverter.cpp writes these scalar
    //   fields directly to ElectricLoadCenter:Storage:Converter.
    // - TODO(parity): Add relationship APIs incrementally without changing preserved scalar signatures.
    std::string powerConversionEfficiencyMethod() const;

    // simpleFixedEfficiency field
    boost::optional<double> simpleFixedEfficiency() const;
    bool setSimpleFixedEfficiency(double simpleFixedEfficiency);

    // designMaximumContinuousInputPower field
    boost::optional<double> designMaximumContinuousInputPower() const;
    bool setDesignMaximumContinuousInputPower(double designMaximumContinuousInputPower);

    // ancillaryPowerConsumedInStandby field
    double ancillaryPowerConsumedInStandby() const;
    bool isAncillaryPowerConsumedInStandbyDefaulted() const;
    bool setAncillaryPowerConsumedInStandby(double ancillaryPowerConsumedInStandby);
    void resetAncillaryPowerConsumedInStandby();

    // radiativeFraction field
    double radiativeFraction() const;
    bool isRadiativeFractionDefaulted() const;
    bool setRadiativeFraction(double radiativeFraction);
    void resetRadiativeFraction();

   protected:
    using ImplType = detail::ElectricLoadCenterStorageConverter_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ElectricLoadCenterStorageConverter(std::shared_ptr<detail::ElectricLoadCenterStorageConverter_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
