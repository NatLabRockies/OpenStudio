/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "PhotovoltaicPerformance/PhotovoltaicPerformanceSandia.hpp"
#include "PhotovoltaicPerformance/PhotovoltaicPerformanceSandia_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/PhotovoltaicPerformance_Sandia_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  PhotovoltaicPerformanceSandia::PhotovoltaicPerformanceSandia(const Model& model)
    : ModelObject(PhotovoltaicPerformanceSandia::iddObjectType(), model) {}

  PhotovoltaicPerformanceSandia::PhotovoltaicPerformanceSandia(std::shared_ptr<detail::PhotovoltaicPerformanceSandia_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType PhotovoltaicPerformanceSandia::iddObjectType() {
    return IddObjectType::PhotovoltaicPerformance_Sandia;
  }

  double PhotovoltaicPerformanceSandia::activeArea() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->activeArea();
  }

  bool PhotovoltaicPerformanceSandia::setActiveArea(double activeArea) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setActiveArea(activeArea);
  }

  int PhotovoltaicPerformanceSandia::numberofCellsinSeries() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->numberofCellsinSeries();
  }

  bool PhotovoltaicPerformanceSandia::setNumberofCellsinSeries(int numberofCellsinSeries) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setNumberofCellsinSeries(numberofCellsinSeries);
  }

  int PhotovoltaicPerformanceSandia::numberofCellsinParallel() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->numberofCellsinParallel();
  }

  bool PhotovoltaicPerformanceSandia::setNumberofCellsinParallel(int numberofCellsinParallel) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setNumberofCellsinParallel(numberofCellsinParallel);
  }

  double PhotovoltaicPerformanceSandia::shortCircuitCurrent() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->shortCircuitCurrent();
  }

  bool PhotovoltaicPerformanceSandia::setShortCircuitCurrent(double shortCircuitCurrent) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setShortCircuitCurrent(shortCircuitCurrent);
  }

  double PhotovoltaicPerformanceSandia::openCircuitVoltage() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->openCircuitVoltage();
  }

  bool PhotovoltaicPerformanceSandia::setOpenCircuitVoltage(double openCircuitVoltage) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setOpenCircuitVoltage(openCircuitVoltage);
  }

  double PhotovoltaicPerformanceSandia::currentatMaximumPowerPoint() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->currentatMaximumPowerPoint();
  }

  bool PhotovoltaicPerformanceSandia::setCurrentatMaximumPowerPoint(double currentatMaximumPowerPoint) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setCurrentatMaximumPowerPoint(currentatMaximumPowerPoint);
  }

  double PhotovoltaicPerformanceSandia::voltageatMaximumPowerPoint() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->voltageatMaximumPowerPoint();
  }

  bool PhotovoltaicPerformanceSandia::setVoltageatMaximumPowerPoint(double voltageatMaximumPowerPoint) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setVoltageatMaximumPowerPoint(voltageatMaximumPowerPoint);
  }

  double PhotovoltaicPerformanceSandia::sandiaDatabaseParameteraIsc() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->sandiaDatabaseParameteraIsc();
  }

  bool PhotovoltaicPerformanceSandia::setSandiaDatabaseParameteraIsc(double sandiaDatabaseParameteraIsc) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setSandiaDatabaseParameteraIsc(sandiaDatabaseParameteraIsc);
  }

  double PhotovoltaicPerformanceSandia::sandiaDatabaseParameteraImp() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->sandiaDatabaseParameteraImp();
  }

  bool PhotovoltaicPerformanceSandia::setSandiaDatabaseParameteraImp(double sandiaDatabaseParameteraImp) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setSandiaDatabaseParameteraImp(sandiaDatabaseParameteraImp);
  }

  double PhotovoltaicPerformanceSandia::sandiaDatabaseParameterc0() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->sandiaDatabaseParameterc0();
  }

  bool PhotovoltaicPerformanceSandia::setSandiaDatabaseParameterc0(double sandiaDatabaseParameterc0) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setSandiaDatabaseParameterc0(sandiaDatabaseParameterc0);
  }

  double PhotovoltaicPerformanceSandia::sandiaDatabaseParameterc1() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->sandiaDatabaseParameterc1();
  }

  bool PhotovoltaicPerformanceSandia::setSandiaDatabaseParameterc1(double sandiaDatabaseParameterc1) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setSandiaDatabaseParameterc1(sandiaDatabaseParameterc1);
  }

  double PhotovoltaicPerformanceSandia::sandiaDatabaseParameterBVoc0() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->sandiaDatabaseParameterBVoc0();
  }

  bool PhotovoltaicPerformanceSandia::setSandiaDatabaseParameterBVoc0(double sandiaDatabaseParameterBVoc0) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setSandiaDatabaseParameterBVoc0(sandiaDatabaseParameterBVoc0);
  }

  double PhotovoltaicPerformanceSandia::sandiaDatabaseParametermBVoc() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->sandiaDatabaseParametermBVoc();
  }

  bool PhotovoltaicPerformanceSandia::setSandiaDatabaseParametermBVoc(double sandiaDatabaseParametermBVoc) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setSandiaDatabaseParametermBVoc(sandiaDatabaseParametermBVoc);
  }

  double PhotovoltaicPerformanceSandia::sandiaDatabaseParameterBVmp0() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->sandiaDatabaseParameterBVmp0();
  }

  bool PhotovoltaicPerformanceSandia::setSandiaDatabaseParameterBVmp0(double sandiaDatabaseParameterBVmp0) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setSandiaDatabaseParameterBVmp0(sandiaDatabaseParameterBVmp0);
  }

  double PhotovoltaicPerformanceSandia::sandiaDatabaseParametermBVmp() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->sandiaDatabaseParametermBVmp();
  }

  bool PhotovoltaicPerformanceSandia::setSandiaDatabaseParametermBVmp(double sandiaDatabaseParametermBVmp) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setSandiaDatabaseParametermBVmp(sandiaDatabaseParametermBVmp);
  }

  double PhotovoltaicPerformanceSandia::diodeFactor() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->diodeFactor();
  }

  bool PhotovoltaicPerformanceSandia::setDiodeFactor(double diodeFactor) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setDiodeFactor(diodeFactor);
  }

  double PhotovoltaicPerformanceSandia::sandiaDatabaseParameterc2() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->sandiaDatabaseParameterc2();
  }

  bool PhotovoltaicPerformanceSandia::setSandiaDatabaseParameterc2(double sandiaDatabaseParameterc2) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setSandiaDatabaseParameterc2(sandiaDatabaseParameterc2);
  }

  double PhotovoltaicPerformanceSandia::sandiaDatabaseParameterc3() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->sandiaDatabaseParameterc3();
  }

  bool PhotovoltaicPerformanceSandia::setSandiaDatabaseParameterc3(double sandiaDatabaseParameterc3) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setSandiaDatabaseParameterc3(sandiaDatabaseParameterc3);
  }

  double PhotovoltaicPerformanceSandia::sandiaDatabaseParametera0() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->sandiaDatabaseParametera0();
  }

  bool PhotovoltaicPerformanceSandia::setSandiaDatabaseParametera0(double sandiaDatabaseParametera0) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setSandiaDatabaseParametera0(sandiaDatabaseParametera0);
  }

  double PhotovoltaicPerformanceSandia::sandiaDatabaseParametera1() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->sandiaDatabaseParametera1();
  }

  bool PhotovoltaicPerformanceSandia::setSandiaDatabaseParametera1(double sandiaDatabaseParametera1) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setSandiaDatabaseParametera1(sandiaDatabaseParametera1);
  }

  double PhotovoltaicPerformanceSandia::sandiaDatabaseParametera2() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->sandiaDatabaseParametera2();
  }

  bool PhotovoltaicPerformanceSandia::setSandiaDatabaseParametera2(double sandiaDatabaseParametera2) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setSandiaDatabaseParametera2(sandiaDatabaseParametera2);
  }

  double PhotovoltaicPerformanceSandia::sandiaDatabaseParametera3() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->sandiaDatabaseParametera3();
  }

  bool PhotovoltaicPerformanceSandia::setSandiaDatabaseParametera3(double sandiaDatabaseParametera3) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setSandiaDatabaseParametera3(sandiaDatabaseParametera3);
  }

  double PhotovoltaicPerformanceSandia::sandiaDatabaseParametera4() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->sandiaDatabaseParametera4();
  }

  bool PhotovoltaicPerformanceSandia::setSandiaDatabaseParametera4(double sandiaDatabaseParametera4) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setSandiaDatabaseParametera4(sandiaDatabaseParametera4);
  }

  double PhotovoltaicPerformanceSandia::sandiaDatabaseParameterb0() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->sandiaDatabaseParameterb0();
  }

  bool PhotovoltaicPerformanceSandia::setSandiaDatabaseParameterb0(double sandiaDatabaseParameterb0) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setSandiaDatabaseParameterb0(sandiaDatabaseParameterb0);
  }

  double PhotovoltaicPerformanceSandia::sandiaDatabaseParameterb1() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->sandiaDatabaseParameterb1();
  }

  bool PhotovoltaicPerformanceSandia::setSandiaDatabaseParameterb1(double sandiaDatabaseParameterb1) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setSandiaDatabaseParameterb1(sandiaDatabaseParameterb1);
  }

  double PhotovoltaicPerformanceSandia::sandiaDatabaseParameterb2() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->sandiaDatabaseParameterb2();
  }

  bool PhotovoltaicPerformanceSandia::setSandiaDatabaseParameterb2(double sandiaDatabaseParameterb2) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setSandiaDatabaseParameterb2(sandiaDatabaseParameterb2);
  }

  double PhotovoltaicPerformanceSandia::sandiaDatabaseParameterb3() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->sandiaDatabaseParameterb3();
  }

  bool PhotovoltaicPerformanceSandia::setSandiaDatabaseParameterb3(double sandiaDatabaseParameterb3) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setSandiaDatabaseParameterb3(sandiaDatabaseParameterb3);
  }

  double PhotovoltaicPerformanceSandia::sandiaDatabaseParameterb4() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->sandiaDatabaseParameterb4();
  }

  bool PhotovoltaicPerformanceSandia::setSandiaDatabaseParameterb4(double sandiaDatabaseParameterb4) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setSandiaDatabaseParameterb4(sandiaDatabaseParameterb4);
  }

  double PhotovoltaicPerformanceSandia::sandiaDatabaseParameterb5() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->sandiaDatabaseParameterb5();
  }

  bool PhotovoltaicPerformanceSandia::setSandiaDatabaseParameterb5(double sandiaDatabaseParameterb5) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setSandiaDatabaseParameterb5(sandiaDatabaseParameterb5);
  }

  double PhotovoltaicPerformanceSandia::sandiaDatabaseParameterDeltaTc() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->sandiaDatabaseParameterDeltaTc();
  }

  bool PhotovoltaicPerformanceSandia::setSandiaDatabaseParameterDeltaTc(double sandiaDatabaseParameterDeltaTc) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setSandiaDatabaseParameterDeltaTc(sandiaDatabaseParameterDeltaTc);
  }

  double PhotovoltaicPerformanceSandia::sandiaDatabaseParameterfd() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->sandiaDatabaseParameterfd();
  }

  bool PhotovoltaicPerformanceSandia::setSandiaDatabaseParameterfd(double sandiaDatabaseParameterfd) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setSandiaDatabaseParameterfd(sandiaDatabaseParameterfd);
  }

  double PhotovoltaicPerformanceSandia::sandiaDatabaseParametera() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->sandiaDatabaseParametera();
  }

  bool PhotovoltaicPerformanceSandia::setSandiaDatabaseParametera(double sandiaDatabaseParametera) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setSandiaDatabaseParametera(sandiaDatabaseParametera);
  }

  double PhotovoltaicPerformanceSandia::sandiaDatabaseParameterb() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->sandiaDatabaseParameterb();
  }

  bool PhotovoltaicPerformanceSandia::setSandiaDatabaseParameterb(double sandiaDatabaseParameterb) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setSandiaDatabaseParameterb(sandiaDatabaseParameterb);
  }

  double PhotovoltaicPerformanceSandia::sandiaDatabaseParameterc4() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->sandiaDatabaseParameterc4();
  }

  bool PhotovoltaicPerformanceSandia::setSandiaDatabaseParameterc4(double sandiaDatabaseParameterc4) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setSandiaDatabaseParameterc4(sandiaDatabaseParameterc4);
  }

  double PhotovoltaicPerformanceSandia::sandiaDatabaseParameterc5() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->sandiaDatabaseParameterc5();
  }

  bool PhotovoltaicPerformanceSandia::setSandiaDatabaseParameterc5(double sandiaDatabaseParameterc5) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setSandiaDatabaseParameterc5(sandiaDatabaseParameterc5);
  }

  double PhotovoltaicPerformanceSandia::sandiaDatabaseParameterIx0() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->sandiaDatabaseParameterIx0();
  }

  bool PhotovoltaicPerformanceSandia::setSandiaDatabaseParameterIx0(double sandiaDatabaseParameterIx0) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setSandiaDatabaseParameterIx0(sandiaDatabaseParameterIx0);
  }

  double PhotovoltaicPerformanceSandia::sandiaDatabaseParameterIxx0() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->sandiaDatabaseParameterIxx0();
  }

  bool PhotovoltaicPerformanceSandia::setSandiaDatabaseParameterIxx0(double sandiaDatabaseParameterIxx0) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setSandiaDatabaseParameterIxx0(sandiaDatabaseParameterIxx0);
  }

  double PhotovoltaicPerformanceSandia::sandiaDatabaseParameterc6() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->sandiaDatabaseParameterc6();
  }

  bool PhotovoltaicPerformanceSandia::setSandiaDatabaseParameterc6(double sandiaDatabaseParameterc6) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setSandiaDatabaseParameterc6(sandiaDatabaseParameterc6);
  }

  double PhotovoltaicPerformanceSandia::sandiaDatabaseParameterc7() const {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->sandiaDatabaseParameterc7();
  }

  bool PhotovoltaicPerformanceSandia::setSandiaDatabaseParameterc7(double sandiaDatabaseParameterc7) {
    return getImpl<detail::PhotovoltaicPerformanceSandia_Impl>()->setSandiaDatabaseParameterc7(sandiaDatabaseParameterc7);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double PhotovoltaicPerformanceSandia_Impl::activeArea() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::ActiveArea, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setActiveArea(double activeArea) {
      return setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::ActiveArea, activeArea);
    }

    int PhotovoltaicPerformanceSandia_Impl::numberofCellsinSeries() const {
      auto value = getInt(openstudio::PhotovoltaicPerformance_SandiaFields::NumberofCellsinSeries, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setNumberofCellsinSeries(int numberofCellsinSeries) {
      return setInt(openstudio::PhotovoltaicPerformance_SandiaFields::NumberofCellsinSeries, numberofCellsinSeries);
    }

    int PhotovoltaicPerformanceSandia_Impl::numberofCellsinParallel() const {
      auto value = getInt(openstudio::PhotovoltaicPerformance_SandiaFields::NumberofCellsinParallel, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setNumberofCellsinParallel(int numberofCellsinParallel) {
      return setInt(openstudio::PhotovoltaicPerformance_SandiaFields::NumberofCellsinParallel, numberofCellsinParallel);
    }

    double PhotovoltaicPerformanceSandia_Impl::shortCircuitCurrent() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::ShortCircuitCurrent, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setShortCircuitCurrent(double shortCircuitCurrent) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::ShortCircuitCurrent, shortCircuitCurrent);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::openCircuitVoltage() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::OpenCircuitVoltage, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setOpenCircuitVoltage(double openCircuitVoltage) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::OpenCircuitVoltage, openCircuitVoltage);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::currentatMaximumPowerPoint() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::CurrentatMaximumPowerPoint, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setCurrentatMaximumPowerPoint(double currentatMaximumPowerPoint) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::CurrentatMaximumPowerPoint, currentatMaximumPowerPoint);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::voltageatMaximumPowerPoint() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::VoltageatMaximumPowerPoint, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setVoltageatMaximumPowerPoint(double voltageatMaximumPowerPoint) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::VoltageatMaximumPowerPoint, voltageatMaximumPowerPoint);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::sandiaDatabaseParameteraIsc() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameteraIsc, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setSandiaDatabaseParameteraIsc(double sandiaDatabaseParameteraIsc) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameteraIsc, sandiaDatabaseParameteraIsc);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::sandiaDatabaseParameteraImp() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameteraImp, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setSandiaDatabaseParameteraImp(double sandiaDatabaseParameteraImp) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameteraImp, sandiaDatabaseParameteraImp);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::sandiaDatabaseParameterc0() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterc0, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setSandiaDatabaseParameterc0(double sandiaDatabaseParameterc0) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterc0, sandiaDatabaseParameterc0);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::sandiaDatabaseParameterc1() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterc1, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setSandiaDatabaseParameterc1(double sandiaDatabaseParameterc1) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterc1, sandiaDatabaseParameterc1);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::sandiaDatabaseParameterBVoc0() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterBVoc0, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setSandiaDatabaseParameterBVoc0(double sandiaDatabaseParameterBVoc0) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterBVoc0, sandiaDatabaseParameterBVoc0);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::sandiaDatabaseParametermBVoc() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParametermBVoc, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setSandiaDatabaseParametermBVoc(double sandiaDatabaseParametermBVoc) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParametermBVoc, sandiaDatabaseParametermBVoc);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::sandiaDatabaseParameterBVmp0() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterBVmp0, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setSandiaDatabaseParameterBVmp0(double sandiaDatabaseParameterBVmp0) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterBVmp0, sandiaDatabaseParameterBVmp0);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::sandiaDatabaseParametermBVmp() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParametermBVmp, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setSandiaDatabaseParametermBVmp(double sandiaDatabaseParametermBVmp) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParametermBVmp, sandiaDatabaseParametermBVmp);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::diodeFactor() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::DiodeFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setDiodeFactor(double diodeFactor) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::DiodeFactor, diodeFactor);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::sandiaDatabaseParameterc2() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterc2, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setSandiaDatabaseParameterc2(double sandiaDatabaseParameterc2) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterc2, sandiaDatabaseParameterc2);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::sandiaDatabaseParameterc3() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterc3, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setSandiaDatabaseParameterc3(double sandiaDatabaseParameterc3) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterc3, sandiaDatabaseParameterc3);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::sandiaDatabaseParametera0() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParametera0, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setSandiaDatabaseParametera0(double sandiaDatabaseParametera0) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParametera0, sandiaDatabaseParametera0);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::sandiaDatabaseParametera1() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParametera1, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setSandiaDatabaseParametera1(double sandiaDatabaseParametera1) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParametera1, sandiaDatabaseParametera1);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::sandiaDatabaseParametera2() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParametera2, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setSandiaDatabaseParametera2(double sandiaDatabaseParametera2) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParametera2, sandiaDatabaseParametera2);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::sandiaDatabaseParametera3() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParametera3, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setSandiaDatabaseParametera3(double sandiaDatabaseParametera3) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParametera3, sandiaDatabaseParametera3);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::sandiaDatabaseParametera4() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParametera4, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setSandiaDatabaseParametera4(double sandiaDatabaseParametera4) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParametera4, sandiaDatabaseParametera4);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::sandiaDatabaseParameterb0() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterb0, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setSandiaDatabaseParameterb0(double sandiaDatabaseParameterb0) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterb0, sandiaDatabaseParameterb0);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::sandiaDatabaseParameterb1() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterb1, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setSandiaDatabaseParameterb1(double sandiaDatabaseParameterb1) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterb1, sandiaDatabaseParameterb1);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::sandiaDatabaseParameterb2() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterb2, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setSandiaDatabaseParameterb2(double sandiaDatabaseParameterb2) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterb2, sandiaDatabaseParameterb2);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::sandiaDatabaseParameterb3() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterb3, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setSandiaDatabaseParameterb3(double sandiaDatabaseParameterb3) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterb3, sandiaDatabaseParameterb3);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::sandiaDatabaseParameterb4() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterb4, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setSandiaDatabaseParameterb4(double sandiaDatabaseParameterb4) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterb4, sandiaDatabaseParameterb4);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::sandiaDatabaseParameterb5() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterb5, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setSandiaDatabaseParameterb5(double sandiaDatabaseParameterb5) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterb5, sandiaDatabaseParameterb5);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::sandiaDatabaseParameterDeltaTc() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterDelta_Tc_, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setSandiaDatabaseParameterDeltaTc(double sandiaDatabaseParameterDeltaTc) {
      const bool result =
        setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterDelta_Tc_, sandiaDatabaseParameterDeltaTc);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::sandiaDatabaseParameterfd() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterfd, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setSandiaDatabaseParameterfd(double sandiaDatabaseParameterfd) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterfd, sandiaDatabaseParameterfd);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::sandiaDatabaseParametera() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParametera, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setSandiaDatabaseParametera(double sandiaDatabaseParametera) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParametera, sandiaDatabaseParametera);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::sandiaDatabaseParameterb() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterb, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setSandiaDatabaseParameterb(double sandiaDatabaseParameterb) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterb, sandiaDatabaseParameterb);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::sandiaDatabaseParameterc4() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterc4, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setSandiaDatabaseParameterc4(double sandiaDatabaseParameterc4) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterc4, sandiaDatabaseParameterc4);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::sandiaDatabaseParameterc5() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterc5, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setSandiaDatabaseParameterc5(double sandiaDatabaseParameterc5) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterc5, sandiaDatabaseParameterc5);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::sandiaDatabaseParameterIx0() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterIx0, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setSandiaDatabaseParameterIx0(double sandiaDatabaseParameterIx0) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterIx0, sandiaDatabaseParameterIx0);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::sandiaDatabaseParameterIxx0() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterIxx0, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setSandiaDatabaseParameterIxx0(double sandiaDatabaseParameterIxx0) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterIxx0, sandiaDatabaseParameterIxx0);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::sandiaDatabaseParameterc6() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterc6, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setSandiaDatabaseParameterc6(double sandiaDatabaseParameterc6) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterc6, sandiaDatabaseParameterc6);
      OS_ASSERT(result);
      return result;
    }

    double PhotovoltaicPerformanceSandia_Impl::sandiaDatabaseParameterc7() const {
      auto value = getDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterc7, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PhotovoltaicPerformanceSandia_Impl::setSandiaDatabaseParameterc7(double sandiaDatabaseParameterc7) {
      const bool result = setDouble(openstudio::PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterc7, sandiaDatabaseParameterc7);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
