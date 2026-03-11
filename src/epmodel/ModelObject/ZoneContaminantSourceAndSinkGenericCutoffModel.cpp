/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneContaminantSourceAndSinkGenericCutoffModel.hpp"
#include "ZoneContaminantSourceAndSinkGenericCutoffModel_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneContaminantSourceAndSink_Generic_CutoffModel_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneContaminantSourceAndSinkGenericCutoffModel::ZoneContaminantSourceAndSinkGenericCutoffModel(const Model& model)
    : ModelObject(ZoneContaminantSourceAndSinkGenericCutoffModel::iddObjectType(), model) {}

  ZoneContaminantSourceAndSinkGenericCutoffModel::ZoneContaminantSourceAndSinkGenericCutoffModel(
    std::shared_ptr<detail::ZoneContaminantSourceAndSinkGenericCutoffModel_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneContaminantSourceAndSinkGenericCutoffModel::iddObjectType() {
    return IddObjectType::ZoneContaminantSourceAndSink_Generic_CutoffModel;
  }

  boost::optional<double> ZoneContaminantSourceAndSinkGenericCutoffModel::designGenerationRateCoefficient() const {
    return getImpl<detail::ZoneContaminantSourceAndSinkGenericCutoffModel_Impl>()->designGenerationRateCoefficient();
  }

  bool ZoneContaminantSourceAndSinkGenericCutoffModel::setDesignGenerationRateCoefficient(double designGenerationRateCoefficient) {
    return getImpl<detail::ZoneContaminantSourceAndSinkGenericCutoffModel_Impl>()->setDesignGenerationRateCoefficient(
      designGenerationRateCoefficient);
  }

  void ZoneContaminantSourceAndSinkGenericCutoffModel::resetDesignGenerationRateCoefficient() {
    getImpl<detail::ZoneContaminantSourceAndSinkGenericCutoffModel_Impl>()->resetDesignGenerationRateCoefficient();
  }

  boost::optional<double> ZoneContaminantSourceAndSinkGenericCutoffModel::cutoffGenericContaminantAtWhichEmissionCeases() const {
    return getImpl<detail::ZoneContaminantSourceAndSinkGenericCutoffModel_Impl>()->cutoffGenericContaminantAtWhichEmissionCeases();
  }

  bool ZoneContaminantSourceAndSinkGenericCutoffModel::setCutoffGenericContaminantAtWhichEmissionCeases(
    double cutoffGenericContaminantAtWhichEmissionCeases) {
    return getImpl<detail::ZoneContaminantSourceAndSinkGenericCutoffModel_Impl>()->setCutoffGenericContaminantAtWhichEmissionCeases(
      cutoffGenericContaminantAtWhichEmissionCeases);
  }

  void ZoneContaminantSourceAndSinkGenericCutoffModel::resetCutoffGenericContaminantAtWhichEmissionCeases() {
    getImpl<detail::ZoneContaminantSourceAndSinkGenericCutoffModel_Impl>()->resetCutoffGenericContaminantAtWhichEmissionCeases();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> ZoneContaminantSourceAndSinkGenericCutoffModel_Impl::designGenerationRateCoefficient() const {
      return getDouble(openstudio::ZoneContaminantSourceAndSink_Generic_CutoffModelFields::DesignGenerationRateCoefficient, true);
    }

    bool ZoneContaminantSourceAndSinkGenericCutoffModel_Impl::setDesignGenerationRateCoefficient(double designGenerationRateCoefficient) {
      return setDouble(openstudio::ZoneContaminantSourceAndSink_Generic_CutoffModelFields::DesignGenerationRateCoefficient,
                       designGenerationRateCoefficient);
    }

    void ZoneContaminantSourceAndSinkGenericCutoffModel_Impl::resetDesignGenerationRateCoefficient() {
      OS_ASSERT(setString(openstudio::ZoneContaminantSourceAndSink_Generic_CutoffModelFields::DesignGenerationRateCoefficient, "", false));
    }

    boost::optional<double> ZoneContaminantSourceAndSinkGenericCutoffModel_Impl::cutoffGenericContaminantAtWhichEmissionCeases() const {
      return getDouble(openstudio::ZoneContaminantSourceAndSink_Generic_CutoffModelFields::CutoffGenericContaminantatwhichEmissionCeases, true);
    }

    bool ZoneContaminantSourceAndSinkGenericCutoffModel_Impl::setCutoffGenericContaminantAtWhichEmissionCeases(
      double cutoffGenericContaminantAtWhichEmissionCeases) {
      return setDouble(openstudio::ZoneContaminantSourceAndSink_Generic_CutoffModelFields::CutoffGenericContaminantatwhichEmissionCeases,
                       cutoffGenericContaminantAtWhichEmissionCeases);
    }

    void ZoneContaminantSourceAndSinkGenericCutoffModel_Impl::resetCutoffGenericContaminantAtWhichEmissionCeases() {
      OS_ASSERT(
        setString(openstudio::ZoneContaminantSourceAndSink_Generic_CutoffModelFields::CutoffGenericContaminantatwhichEmissionCeases, "", false));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
