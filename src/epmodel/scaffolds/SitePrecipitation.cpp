/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SitePrecipitation.hpp"
#include "SitePrecipitation_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Site_Precipitation_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SitePrecipitation::SitePrecipitation(const Model& model) : ModelObject(SitePrecipitation::iddObjectType(), model) {}

SitePrecipitation::SitePrecipitation(std::shared_ptr<detail::SitePrecipitation_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType SitePrecipitation::iddObjectType() {
    return IddObjectType::Site_Precipitation;
}

std::vector<std::string> SitePrecipitation::precipitationModelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Site_PrecipitationFields::PrecipitationModelType);
}

namespace detail {

    std::vector<std::string> SitePrecipitation_Impl::precipitationModelTypeValues() const {
      return openstudio::epmodel::SitePrecipitation::precipitationModelTypeValues();
    }

}  // namespace detail

boost::optional<std::string> SitePrecipitation::precipitationModelType() const {
    return getImpl<detail::SitePrecipitation_Impl>()->precipitationModelType();
}

bool SitePrecipitation::setPrecipitationModelType(const std::string& precipitationModelType) {
    return getImpl<detail::SitePrecipitation_Impl>()->setPrecipitationModelType(precipitationModelType);
}

void SitePrecipitation::resetPrecipitationModelType() {
    getImpl<detail::SitePrecipitation_Impl>()->resetPrecipitationModelType();
}

namespace detail {

    boost::optional<std::string> SitePrecipitation_Impl::precipitationModelType() const {
      return getString(openstudio::Site_PrecipitationFields::PrecipitationModelType, true);
    }

    bool SitePrecipitation_Impl::setPrecipitationModelType(const std::string& precipitationModelType) {
      return setString(openstudio::Site_PrecipitationFields::PrecipitationModelType, precipitationModelType);
    }

    void SitePrecipitation_Impl::resetPrecipitationModelType() {
      OS_ASSERT(setString(openstudio::Site_PrecipitationFields::PrecipitationModelType, ""));
    }

}  // namespace detail

boost::optional<double> SitePrecipitation::designLevelforTotalAnnualPrecipitation() const {
    return getImpl<detail::SitePrecipitation_Impl>()->designLevelforTotalAnnualPrecipitation();
}

bool SitePrecipitation::setDesignLevelforTotalAnnualPrecipitation(double designLevelforTotalAnnualPrecipitation) {
    return getImpl<detail::SitePrecipitation_Impl>()->setDesignLevelforTotalAnnualPrecipitation(designLevelforTotalAnnualPrecipitation);
}

void SitePrecipitation::resetDesignLevelforTotalAnnualPrecipitation() {
    getImpl<detail::SitePrecipitation_Impl>()->resetDesignLevelforTotalAnnualPrecipitation();
}

namespace detail {

    boost::optional<double> SitePrecipitation_Impl::designLevelforTotalAnnualPrecipitation() const {
      return getDouble(openstudio::Site_PrecipitationFields::DesignLevelforTotalAnnualPrecipitation, true);
    }

    bool SitePrecipitation_Impl::setDesignLevelforTotalAnnualPrecipitation(double designLevelforTotalAnnualPrecipitation) {
      const bool result =
        setDouble(openstudio::Site_PrecipitationFields::DesignLevelforTotalAnnualPrecipitation, designLevelforTotalAnnualPrecipitation);
      OS_ASSERT(result);
      return result;
    }

    void SitePrecipitation_Impl::resetDesignLevelforTotalAnnualPrecipitation() {
      OS_ASSERT(setString(openstudio::Site_PrecipitationFields::DesignLevelforTotalAnnualPrecipitation, ""));
    }

}  // namespace detail

boost::optional<double> SitePrecipitation::averageTotalAnnualPrecipitation() const {
    return getImpl<detail::SitePrecipitation_Impl>()->averageTotalAnnualPrecipitation();
}

bool SitePrecipitation::setAverageTotalAnnualPrecipitation(double averageTotalAnnualPrecipitation) {
    return getImpl<detail::SitePrecipitation_Impl>()->setAverageTotalAnnualPrecipitation(averageTotalAnnualPrecipitation);
}

void SitePrecipitation::resetAverageTotalAnnualPrecipitation() {
    getImpl<detail::SitePrecipitation_Impl>()->resetAverageTotalAnnualPrecipitation();
}

namespace detail {

    boost::optional<double> SitePrecipitation_Impl::averageTotalAnnualPrecipitation() const {
      return getDouble(openstudio::Site_PrecipitationFields::AverageTotalAnnualPrecipitation, true);
    }

    bool SitePrecipitation_Impl::setAverageTotalAnnualPrecipitation(double averageTotalAnnualPrecipitation) {
      return setDouble(openstudio::Site_PrecipitationFields::AverageTotalAnnualPrecipitation, averageTotalAnnualPrecipitation);
    }

    void SitePrecipitation_Impl::resetAverageTotalAnnualPrecipitation() {
      OS_ASSERT(setString(openstudio::Site_PrecipitationFields::AverageTotalAnnualPrecipitation, ""));
    }

}  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
