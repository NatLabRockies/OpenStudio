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

/** \brief Defines the conversion efficiency and standby behavior of an electric storage converter.
 *
 * \par EnergyPlus object
 * \epobject{group-electric-load-center-generator.html#electricloadcenterstorageconverter,ElectricLoadCenter:Storage:Converter}
 *
 * \par Important behavior
 * A newly created converter defaults simple fixed efficiency to 0.95; efficiency method, input power, standby, and radiative-fraction fields then map directly to EnergyPlus.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::ElectricLoadCenterStorageConverter</code>.
 * <b>Not yet available:</b> Model's availability schedule, efficiency curve, thermal-zone, and electric-load-center distribution relationships are not exposed.
 *
 * \par Known limitations
 * The converter is not connected to storage by this wrapper; load-center ownership is represented by the referencing distribution object.
 */
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
