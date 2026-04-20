/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "scaffolds/ZoneThermalChimney.hpp"
#include "scaffolds/ZoneThermalChimney_Impl.hpp"

#include "Model.hpp"

#include <utility>

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneThermalChimney_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneThermalChimney::ZoneThermalChimney(const Model& model) : ModelObject(ZoneThermalChimney::iddObjectType(), model) {}

  ZoneThermalChimney::ZoneThermalChimney(std::shared_ptr<detail::ZoneThermalChimney_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ZoneThermalChimney::iddObjectType() {
    return IddObjectType::ZoneThermalChimney;
  }

  double ZoneThermalChimney::widthOfTheAbsorberWall() const {
    return getImpl<detail::ZoneThermalChimney_Impl>()->widthOfTheAbsorberWall();
  }

  bool ZoneThermalChimney::setWidthOfTheAbsorberWall(double widthOfTheAbsorberWall) {
    return getImpl<detail::ZoneThermalChimney_Impl>()->setWidthOfTheAbsorberWall(widthOfTheAbsorberWall);
  }

  double ZoneThermalChimney::crossSectionalAreaOfAirChannelOutlet() const {
    return getImpl<detail::ZoneThermalChimney_Impl>()->crossSectionalAreaOfAirChannelOutlet();
  }

  bool ZoneThermalChimney::setCrossSectionalAreaOfAirChannelOutlet(double crossSectionalAreaOfAirChannelOutlet) {
    return getImpl<detail::ZoneThermalChimney_Impl>()->setCrossSectionalAreaOfAirChannelOutlet(crossSectionalAreaOfAirChannelOutlet);
  }

  double ZoneThermalChimney::dischargeCoefficient() const {
    return getImpl<detail::ZoneThermalChimney_Impl>()->dischargeCoefficient();
  }

  bool ZoneThermalChimney::setDischargeCoefficient(double dischargeCoefficient) {
    return getImpl<detail::ZoneThermalChimney_Impl>()->setDischargeCoefficient(dischargeCoefficient);
  }

  bool ZoneThermalChimney::isDischargeCoefficientDefaulted() const {
    return getImpl<detail::ZoneThermalChimney_Impl>()->isDischargeCoefficientDefaulted();
  }

  void ZoneThermalChimney::resetDischargeCoefficient() {
    getImpl<detail::ZoneThermalChimney_Impl>()->resetDischargeCoefficient();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double ZoneThermalChimney_Impl::widthOfTheAbsorberWall() const {
      if (auto value = getDouble(openstudio::ZoneThermalChimneyFields::WidthoftheAbsorberWall, true)) {
        return *value;
      }
      return 0.0;
    }

    bool ZoneThermalChimney_Impl::setWidthOfTheAbsorberWall(double widthOfTheAbsorberWall) {
      return setDouble(openstudio::ZoneThermalChimneyFields::WidthoftheAbsorberWall, widthOfTheAbsorberWall);
    }

    double ZoneThermalChimney_Impl::crossSectionalAreaOfAirChannelOutlet() const {
      if (auto value = getDouble(openstudio::ZoneThermalChimneyFields::CrossSectionalAreaofAirChannelOutlet, true)) {
        return *value;
      }
      return 0.0;
    }

    bool ZoneThermalChimney_Impl::setCrossSectionalAreaOfAirChannelOutlet(double crossSectionalAreaOfAirChannelOutlet) {
      return setDouble(openstudio::ZoneThermalChimneyFields::CrossSectionalAreaofAirChannelOutlet, crossSectionalAreaOfAirChannelOutlet);
    }

    double ZoneThermalChimney_Impl::dischargeCoefficient() const {
      if (auto value = getDouble(openstudio::ZoneThermalChimneyFields::DischargeCoefficient, true)) {
        return *value;
      }
      return 0.8;
    }

    bool ZoneThermalChimney_Impl::setDischargeCoefficient(double dischargeCoefficient) {
      return setDouble(openstudio::ZoneThermalChimneyFields::DischargeCoefficient, dischargeCoefficient);
    }

    bool ZoneThermalChimney_Impl::isDischargeCoefficientDefaulted() const {
      return isEmpty(openstudio::ZoneThermalChimneyFields::DischargeCoefficient);
    }

    void ZoneThermalChimney_Impl::resetDischargeCoefficient() {
      OS_ASSERT(setString(openstudio::ZoneThermalChimneyFields::DischargeCoefficient, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
