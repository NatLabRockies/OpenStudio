/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULEDAYHOURLY_IMPL_HPP
#define EPMODEL_SCHEDULEDAYHOURLY_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ScheduleDayHourly_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ScheduleDayHourly_Impl() override = default;

      double hour1() const;
      bool setHour1(double hour1);
      bool isHour1Defaulted() const;
      void resetHour1();

      double hour2() const;
      bool setHour2(double hour2);
      bool isHour2Defaulted() const;
      void resetHour2();

      double hour3() const;
      bool setHour3(double hour3);
      bool isHour3Defaulted() const;
      void resetHour3();

      double hour4() const;
      bool setHour4(double hour4);
      bool isHour4Defaulted() const;
      void resetHour4();

      double hour5() const;
      bool setHour5(double hour5);
      bool isHour5Defaulted() const;
      void resetHour5();

      double hour6() const;
      bool setHour6(double hour6);
      bool isHour6Defaulted() const;
      void resetHour6();

      double hour7() const;
      bool setHour7(double hour7);
      bool isHour7Defaulted() const;
      void resetHour7();

      double hour8() const;
      bool setHour8(double hour8);
      bool isHour8Defaulted() const;
      void resetHour8();

      double hour9() const;
      bool setHour9(double hour9);
      bool isHour9Defaulted() const;
      void resetHour9();

      double hour10() const;
      bool setHour10(double hour10);
      bool isHour10Defaulted() const;
      void resetHour10();

      double hour11() const;
      bool setHour11(double hour11);
      bool isHour11Defaulted() const;
      void resetHour11();

      double hour12() const;
      bool setHour12(double hour12);
      bool isHour12Defaulted() const;
      void resetHour12();

      double hour13() const;
      bool setHour13(double hour13);
      bool isHour13Defaulted() const;
      void resetHour13();

      double hour14() const;
      bool setHour14(double hour14);
      bool isHour14Defaulted() const;
      void resetHour14();

      double hour15() const;
      bool setHour15(double hour15);
      bool isHour15Defaulted() const;
      void resetHour15();

      double hour16() const;
      bool setHour16(double hour16);
      bool isHour16Defaulted() const;
      void resetHour16();

      double hour17() const;
      bool setHour17(double hour17);
      bool isHour17Defaulted() const;
      void resetHour17();

      double hour18() const;
      bool setHour18(double hour18);
      bool isHour18Defaulted() const;
      void resetHour18();

      double hour19() const;
      bool setHour19(double hour19);
      bool isHour19Defaulted() const;
      void resetHour19();

      double hour20() const;
      bool setHour20(double hour20);
      bool isHour20Defaulted() const;
      void resetHour20();

      double hour21() const;
      bool setHour21(double hour21);
      bool isHour21Defaulted() const;
      void resetHour21();

      double hour22() const;
      bool setHour22(double hour22);
      bool isHour22Defaulted() const;
      void resetHour22();

      double hour23() const;
      bool setHour23(double hour23);
      bool isHour23Defaulted() const;
      void resetHour23();

      double hour24() const;
      bool setHour24(double hour24);
      bool isHour24Defaulted() const;
      void resetHour24();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
