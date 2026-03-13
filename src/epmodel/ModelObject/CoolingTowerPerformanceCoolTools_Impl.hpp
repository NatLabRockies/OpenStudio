/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COOLINGTOWERPERFORMANCECOOLTOOLS_IMPL_HPP
#define EPMODEL_COOLINGTOWERPERFORMANCECOOLTOOLS_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API CoolingTowerPerformanceCoolTools_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~CoolingTowerPerformanceCoolTools_Impl() override = default;

      double minimumInletAirWetBulbTemperature() const;
      bool setMinimumInletAirWetBulbTemperature(double minimumInletAirWetBulbTemperature);

      double maximumInletAirWetBulbTemperature() const;
      bool setMaximumInletAirWetBulbTemperature(double maximumInletAirWetBulbTemperature);

      double minimumRangeTemperature() const;
      bool setMinimumRangeTemperature(double minimumRangeTemperature);

      double maximumRangeTemperature() const;
      bool setMaximumRangeTemperature(double maximumRangeTemperature);

      double minimumApproachTemperature() const;
      bool setMinimumApproachTemperature(double minimumApproachTemperature);

      double maximumApproachTemperature() const;
      bool setMaximumApproachTemperature(double maximumApproachTemperature);

      double minimumWaterFlowRateRatio() const;
      bool setMinimumWaterFlowRateRatio(double minimumWaterFlowRateRatio);

      double maximumWaterFlowRateRatio() const;
      bool setMaximumWaterFlowRateRatio(double maximumWaterFlowRateRatio);

      double coefficient1() const;
      bool setCoefficient1(double coefficient1);

      double coefficient2() const;
      bool setCoefficient2(double coefficient2);

      double coefficient3() const;
      bool setCoefficient3(double coefficient3);

      double coefficient4() const;
      bool setCoefficient4(double coefficient4);

      double coefficient5() const;
      bool setCoefficient5(double coefficient5);

      double coefficient6() const;
      bool setCoefficient6(double coefficient6);

      double coefficient7() const;
      bool setCoefficient7(double coefficient7);

      double coefficient8() const;
      bool setCoefficient8(double coefficient8);

      double coefficient9() const;
      bool setCoefficient9(double coefficient9);

      double coefficient10() const;
      bool setCoefficient10(double coefficient10);

      double coefficient11() const;
      bool setCoefficient11(double coefficient11);

      double coefficient12() const;
      bool setCoefficient12(double coefficient12);

      double coefficient13() const;
      bool setCoefficient13(double coefficient13);

      double coefficient14() const;
      bool setCoefficient14(double coefficient14);

      double coefficient15() const;
      bool setCoefficient15(double coefficient15);

      double coefficient16() const;
      bool setCoefficient16(double coefficient16);

      double coefficient17() const;
      bool setCoefficient17(double coefficient17);

      double coefficient18() const;
      bool setCoefficient18(double coefficient18);

      double coefficient19() const;
      bool setCoefficient19(double coefficient19);

      double coefficient20() const;
      bool setCoefficient20(double coefficient20);

      double coefficient21() const;
      bool setCoefficient21(double coefficient21);

      double coefficient22() const;
      bool setCoefficient22(double coefficient22);

      double coefficient23() const;
      bool setCoefficient23(double coefficient23);

      double coefficient24() const;
      bool setCoefficient24(double coefficient24);

      double coefficient25() const;
      bool setCoefficient25(double coefficient25);

      double coefficient26() const;
      bool setCoefficient26(double coefficient26);

      double coefficient27() const;
      bool setCoefficient27(double coefficient27);

      double coefficient28() const;
      bool setCoefficient28(double coefficient28);

      double coefficient29() const;
      bool setCoefficient29(double coefficient29);

      double coefficient30() const;
      bool setCoefficient30(double coefficient30);

      double coefficient31() const;
      bool setCoefficient31(double coefficient31);

      double coefficient32() const;
      bool setCoefficient32(double coefficient32);

      double coefficient33() const;
      bool setCoefficient33(double coefficient33);

      double coefficient34() const;
      bool setCoefficient34(double coefficient34);

      double coefficient35() const;
      bool setCoefficient35(double coefficient35);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
