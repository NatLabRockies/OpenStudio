/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "CoolingTowerPerformanceYorkCalc.hpp"
#include "CoolingTowerPerformanceYorkCalc_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/CoolingTowerPerformance_YorkCalc_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  CoolingTowerPerformanceYorkCalc::CoolingTowerPerformanceYorkCalc(const Model& model)
    : ModelObject(CoolingTowerPerformanceYorkCalc::iddObjectType(), model) {
    setMinimumInletAirWetBulbTemperature(-34.4);
    setMaximumInletAirWetBulbTemperature(26.6667);
    setMinimumRangeTemperature(1.1111);
    setMaximumRangeTemperature(22.2222);
    setMinimumApproachTemperature(1.1111);
    setMaximumApproachTemperature(40.0);
    setMinimumWaterFlowRateRatio(0.5);
    setMaximumWaterFlowRateRatio(4.0);
    setMaximumLiquidtoGasRatio(8.0);
    setCoefficient1(-0.359741205);
    setCoefficient2(-0.055053608);
    setCoefficient3(0.0023850432);
    setCoefficient4(0.173926877);
    setCoefficient5(-0.0248473764);
    setCoefficient6(0.00048430224);
    setCoefficient7(-0.005589849456);
    setCoefficient8(0.0005770079712);
    setCoefficient9(-0.00001342427256);
    setCoefficient10(2.84765801111111);
    setCoefficient11(-0.121765149);
    setCoefficient12(0.0014599242);
    setCoefficient13(1.680428651);
    setCoefficient14(-0.0166920786);
    setCoefficient15(-0.0007190532);
    setCoefficient16(-0.025485194448);
    setCoefficient17(0.0000487491696);
    setCoefficient18(0.00002719234152);
    setCoefficient19(-0.0653766255555556);
    setCoefficient20(-0.002278167);
    setCoefficient21(0.0002500254);
    setCoefficient22(-0.0910565458);
    setCoefficient23(0.00318176316);
    setCoefficient24(0.000038621772);
    setCoefficient25(-0.0034285382352);
    setCoefficient26(0.00000856589904);
    setCoefficient27(-0.000001516821552);
  }

  CoolingTowerPerformanceYorkCalc::CoolingTowerPerformanceYorkCalc(std::shared_ptr<detail::CoolingTowerPerformanceYorkCalc_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType CoolingTowerPerformanceYorkCalc::iddObjectType() {
    return IddObjectType::CoolingTowerPerformance_YorkCalc;
  }

  double CoolingTowerPerformanceYorkCalc::minimumInletAirWetBulbTemperature() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->minimumInletAirWetBulbTemperature();
  }

  bool CoolingTowerPerformanceYorkCalc::setMinimumInletAirWetBulbTemperature(double minimumInletAirWetBulbTemperature) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setMinimumInletAirWetBulbTemperature(minimumInletAirWetBulbTemperature);
  }

  double CoolingTowerPerformanceYorkCalc::maximumInletAirWetBulbTemperature() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->maximumInletAirWetBulbTemperature();
  }

  bool CoolingTowerPerformanceYorkCalc::setMaximumInletAirWetBulbTemperature(double maximumInletAirWetBulbTemperature) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setMaximumInletAirWetBulbTemperature(maximumInletAirWetBulbTemperature);
  }

  double CoolingTowerPerformanceYorkCalc::minimumRangeTemperature() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->minimumRangeTemperature();
  }

  bool CoolingTowerPerformanceYorkCalc::setMinimumRangeTemperature(double minimumRangeTemperature) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setMinimumRangeTemperature(minimumRangeTemperature);
  }

  double CoolingTowerPerformanceYorkCalc::maximumRangeTemperature() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->maximumRangeTemperature();
  }

  bool CoolingTowerPerformanceYorkCalc::setMaximumRangeTemperature(double maximumRangeTemperature) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setMaximumRangeTemperature(maximumRangeTemperature);
  }

  double CoolingTowerPerformanceYorkCalc::minimumApproachTemperature() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->minimumApproachTemperature();
  }

  bool CoolingTowerPerformanceYorkCalc::setMinimumApproachTemperature(double minimumApproachTemperature) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setMinimumApproachTemperature(minimumApproachTemperature);
  }

  double CoolingTowerPerformanceYorkCalc::maximumApproachTemperature() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->maximumApproachTemperature();
  }

  bool CoolingTowerPerformanceYorkCalc::setMaximumApproachTemperature(double maximumApproachTemperature) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setMaximumApproachTemperature(maximumApproachTemperature);
  }

  double CoolingTowerPerformanceYorkCalc::minimumWaterFlowRateRatio() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->minimumWaterFlowRateRatio();
  }

  bool CoolingTowerPerformanceYorkCalc::setMinimumWaterFlowRateRatio(double minimumWaterFlowRateRatio) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setMinimumWaterFlowRateRatio(minimumWaterFlowRateRatio);
  }

  double CoolingTowerPerformanceYorkCalc::maximumWaterFlowRateRatio() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->maximumWaterFlowRateRatio();
  }

  bool CoolingTowerPerformanceYorkCalc::setMaximumWaterFlowRateRatio(double maximumWaterFlowRateRatio) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setMaximumWaterFlowRateRatio(maximumWaterFlowRateRatio);
  }

  double CoolingTowerPerformanceYorkCalc::maximumLiquidtoGasRatio() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->maximumLiquidtoGasRatio();
  }

  bool CoolingTowerPerformanceYorkCalc::setMaximumLiquidtoGasRatio(double maximumLiquidtoGasRatio) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setMaximumLiquidtoGasRatio(maximumLiquidtoGasRatio);
  }

  double CoolingTowerPerformanceYorkCalc::coefficient1() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->coefficient1();
  }

  bool CoolingTowerPerformanceYorkCalc::setCoefficient1(double coefficient1) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setCoefficient1(coefficient1);
  }

  double CoolingTowerPerformanceYorkCalc::coefficient2() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->coefficient2();
  }

  bool CoolingTowerPerformanceYorkCalc::setCoefficient2(double coefficient2) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setCoefficient2(coefficient2);
  }

  double CoolingTowerPerformanceYorkCalc::coefficient3() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->coefficient3();
  }

  bool CoolingTowerPerformanceYorkCalc::setCoefficient3(double coefficient3) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setCoefficient3(coefficient3);
  }

  double CoolingTowerPerformanceYorkCalc::coefficient4() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->coefficient4();
  }

  bool CoolingTowerPerformanceYorkCalc::setCoefficient4(double coefficient4) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setCoefficient4(coefficient4);
  }

  double CoolingTowerPerformanceYorkCalc::coefficient5() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->coefficient5();
  }

  bool CoolingTowerPerformanceYorkCalc::setCoefficient5(double coefficient5) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setCoefficient5(coefficient5);
  }

  double CoolingTowerPerformanceYorkCalc::coefficient6() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->coefficient6();
  }

  bool CoolingTowerPerformanceYorkCalc::setCoefficient6(double coefficient6) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setCoefficient6(coefficient6);
  }

  double CoolingTowerPerformanceYorkCalc::coefficient7() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->coefficient7();
  }

  bool CoolingTowerPerformanceYorkCalc::setCoefficient7(double coefficient7) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setCoefficient7(coefficient7);
  }

  double CoolingTowerPerformanceYorkCalc::coefficient8() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->coefficient8();
  }

  bool CoolingTowerPerformanceYorkCalc::setCoefficient8(double coefficient8) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setCoefficient8(coefficient8);
  }

  double CoolingTowerPerformanceYorkCalc::coefficient9() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->coefficient9();
  }

  bool CoolingTowerPerformanceYorkCalc::setCoefficient9(double coefficient9) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setCoefficient9(coefficient9);
  }

  double CoolingTowerPerformanceYorkCalc::coefficient10() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->coefficient10();
  }

  bool CoolingTowerPerformanceYorkCalc::setCoefficient10(double coefficient10) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setCoefficient10(coefficient10);
  }

  double CoolingTowerPerformanceYorkCalc::coefficient11() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->coefficient11();
  }

  bool CoolingTowerPerformanceYorkCalc::setCoefficient11(double coefficient11) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setCoefficient11(coefficient11);
  }

  double CoolingTowerPerformanceYorkCalc::coefficient12() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->coefficient12();
  }

  bool CoolingTowerPerformanceYorkCalc::setCoefficient12(double coefficient12) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setCoefficient12(coefficient12);
  }

  double CoolingTowerPerformanceYorkCalc::coefficient13() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->coefficient13();
  }

  bool CoolingTowerPerformanceYorkCalc::setCoefficient13(double coefficient13) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setCoefficient13(coefficient13);
  }

  double CoolingTowerPerformanceYorkCalc::coefficient14() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->coefficient14();
  }

  bool CoolingTowerPerformanceYorkCalc::setCoefficient14(double coefficient14) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setCoefficient14(coefficient14);
  }

  double CoolingTowerPerformanceYorkCalc::coefficient15() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->coefficient15();
  }

  bool CoolingTowerPerformanceYorkCalc::setCoefficient15(double coefficient15) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setCoefficient15(coefficient15);
  }

  double CoolingTowerPerformanceYorkCalc::coefficient16() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->coefficient16();
  }

  bool CoolingTowerPerformanceYorkCalc::setCoefficient16(double coefficient16) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setCoefficient16(coefficient16);
  }

  double CoolingTowerPerformanceYorkCalc::coefficient17() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->coefficient17();
  }

  bool CoolingTowerPerformanceYorkCalc::setCoefficient17(double coefficient17) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setCoefficient17(coefficient17);
  }

  double CoolingTowerPerformanceYorkCalc::coefficient18() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->coefficient18();
  }

  bool CoolingTowerPerformanceYorkCalc::setCoefficient18(double coefficient18) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setCoefficient18(coefficient18);
  }

  double CoolingTowerPerformanceYorkCalc::coefficient19() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->coefficient19();
  }

  bool CoolingTowerPerformanceYorkCalc::setCoefficient19(double coefficient19) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setCoefficient19(coefficient19);
  }

  double CoolingTowerPerformanceYorkCalc::coefficient20() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->coefficient20();
  }

  bool CoolingTowerPerformanceYorkCalc::setCoefficient20(double coefficient20) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setCoefficient20(coefficient20);
  }

  double CoolingTowerPerformanceYorkCalc::coefficient21() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->coefficient21();
  }

  bool CoolingTowerPerformanceYorkCalc::setCoefficient21(double coefficient21) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setCoefficient21(coefficient21);
  }

  double CoolingTowerPerformanceYorkCalc::coefficient22() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->coefficient22();
  }

  bool CoolingTowerPerformanceYorkCalc::setCoefficient22(double coefficient22) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setCoefficient22(coefficient22);
  }

  double CoolingTowerPerformanceYorkCalc::coefficient23() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->coefficient23();
  }

  bool CoolingTowerPerformanceYorkCalc::setCoefficient23(double coefficient23) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setCoefficient23(coefficient23);
  }

  double CoolingTowerPerformanceYorkCalc::coefficient24() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->coefficient24();
  }

  bool CoolingTowerPerformanceYorkCalc::setCoefficient24(double coefficient24) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setCoefficient24(coefficient24);
  }

  double CoolingTowerPerformanceYorkCalc::coefficient25() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->coefficient25();
  }

  bool CoolingTowerPerformanceYorkCalc::setCoefficient25(double coefficient25) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setCoefficient25(coefficient25);
  }

  double CoolingTowerPerformanceYorkCalc::coefficient26() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->coefficient26();
  }

  bool CoolingTowerPerformanceYorkCalc::setCoefficient26(double coefficient26) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setCoefficient26(coefficient26);
  }

  double CoolingTowerPerformanceYorkCalc::coefficient27() const {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->coefficient27();
  }

  bool CoolingTowerPerformanceYorkCalc::setCoefficient27(double coefficient27) {
    return getImpl<detail::CoolingTowerPerformanceYorkCalc_Impl>()->setCoefficient27(coefficient27);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double CoolingTowerPerformanceYorkCalc_Impl::minimumInletAirWetBulbTemperature() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::MinimumInletAirWetBulbTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setMinimumInletAirWetBulbTemperature(double minimumInletAirWetBulbTemperature) {
      const bool result =
        setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::MinimumInletAirWetBulbTemperature, minimumInletAirWetBulbTemperature);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::maximumInletAirWetBulbTemperature() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::MaximumInletAirWetBulbTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setMaximumInletAirWetBulbTemperature(double maximumInletAirWetBulbTemperature) {
      const bool result =
        setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::MaximumInletAirWetBulbTemperature, maximumInletAirWetBulbTemperature);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::minimumRangeTemperature() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::MinimumRangeTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setMinimumRangeTemperature(double minimumRangeTemperature) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::MinimumRangeTemperature, minimumRangeTemperature);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::maximumRangeTemperature() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::MaximumRangeTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setMaximumRangeTemperature(double maximumRangeTemperature) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::MaximumRangeTemperature, maximumRangeTemperature);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::minimumApproachTemperature() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::MinimumApproachTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setMinimumApproachTemperature(double minimumApproachTemperature) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::MinimumApproachTemperature, minimumApproachTemperature);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::maximumApproachTemperature() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::MaximumApproachTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setMaximumApproachTemperature(double maximumApproachTemperature) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::MaximumApproachTemperature, maximumApproachTemperature);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::minimumWaterFlowRateRatio() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::MinimumWaterFlowRateRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setMinimumWaterFlowRateRatio(double minimumWaterFlowRateRatio) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::MinimumWaterFlowRateRatio, minimumWaterFlowRateRatio);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::maximumWaterFlowRateRatio() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::MaximumWaterFlowRateRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setMaximumWaterFlowRateRatio(double maximumWaterFlowRateRatio) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::MaximumWaterFlowRateRatio, maximumWaterFlowRateRatio);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::maximumLiquidtoGasRatio() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::MaximumLiquidtoGasRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setMaximumLiquidtoGasRatio(double maximumLiquidtoGasRatio) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::MaximumLiquidtoGasRatio, maximumLiquidtoGasRatio);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::coefficient1() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient1, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setCoefficient1(double coefficient1) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient1, coefficient1);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::coefficient2() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient2, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setCoefficient2(double coefficient2) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient2, coefficient2);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::coefficient3() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient3, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setCoefficient3(double coefficient3) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient3, coefficient3);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::coefficient4() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient4, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setCoefficient4(double coefficient4) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient4, coefficient4);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::coefficient5() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient5, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setCoefficient5(double coefficient5) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient5, coefficient5);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::coefficient6() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient6, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setCoefficient6(double coefficient6) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient6, coefficient6);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::coefficient7() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient7, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setCoefficient7(double coefficient7) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient7, coefficient7);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::coefficient8() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient8, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setCoefficient8(double coefficient8) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient8, coefficient8);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::coefficient9() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient9, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setCoefficient9(double coefficient9) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient9, coefficient9);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::coefficient10() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient10, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setCoefficient10(double coefficient10) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient10, coefficient10);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::coefficient11() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient11, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setCoefficient11(double coefficient11) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient11, coefficient11);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::coefficient12() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient12, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setCoefficient12(double coefficient12) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient12, coefficient12);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::coefficient13() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient13, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setCoefficient13(double coefficient13) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient13, coefficient13);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::coefficient14() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient14, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setCoefficient14(double coefficient14) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient14, coefficient14);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::coefficient15() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient15, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setCoefficient15(double coefficient15) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient15, coefficient15);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::coefficient16() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient16, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setCoefficient16(double coefficient16) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient16, coefficient16);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::coefficient17() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient17, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setCoefficient17(double coefficient17) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient17, coefficient17);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::coefficient18() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient18, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setCoefficient18(double coefficient18) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient18, coefficient18);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::coefficient19() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient19, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setCoefficient19(double coefficient19) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient19, coefficient19);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::coefficient20() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient20, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setCoefficient20(double coefficient20) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient20, coefficient20);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::coefficient21() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient21, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setCoefficient21(double coefficient21) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient21, coefficient21);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::coefficient22() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient22, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setCoefficient22(double coefficient22) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient22, coefficient22);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::coefficient23() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient23, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setCoefficient23(double coefficient23) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient23, coefficient23);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::coefficient24() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient24, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setCoefficient24(double coefficient24) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient24, coefficient24);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::coefficient25() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient25, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setCoefficient25(double coefficient25) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient25, coefficient25);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::coefficient26() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient26, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setCoefficient26(double coefficient26) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient26, coefficient26);
      OS_ASSERT(result);
      return result;
    }

    double CoolingTowerPerformanceYorkCalc_Impl::coefficient27() const {
      const auto value = getDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient27, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerPerformanceYorkCalc_Impl::setCoefficient27(double coefficient27) {
      const bool result = setDouble(openstudio::CoolingTowerPerformance_YorkCalcFields::Coefficient27, coefficient27);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
