/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULEDAYHOURLY_HPP
#define EPMODEL_SCHEDULEDAYHOURLY_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ScheduleDayHourly_Impl;
  }

  class EPMODEL_API ScheduleDayHourly : public ModelObject
  {
   public:
    explicit ScheduleDayHourly(const Model& model);

    virtual ~ScheduleDayHourly() override = default;
    ScheduleDayHourly(const ScheduleDayHourly& other) = default;
    ScheduleDayHourly(ScheduleDayHourly&& other) = default;
    ScheduleDayHourly& operator=(const ScheduleDayHourly&) = default;
    ScheduleDayHourly& operator=(ScheduleDayHourly&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
    // - Field Mapping: hour1..hour24 map directly to EnergyPlus Schedule:Day:Hourly Hour 1..Hour 24.
    // - Field Mapping: Schedule Type Limits Name is an object-list relationship field and is intentionally excluded from scalar accessors.
    // - Field Mapping: Name remains provided by base ModelObject naming APIs.
    // - ForwardTranslator evidence: no direct model ForwardTranslator for Schedule:Day:Hourly; ReverseTranslator maps Hour1..Hour24 directly.
    // - TODO(parity): Add relationship APIs for Schedule Type Limits Name after scalar saturation if needed.
    double hour1() const;
    bool isHour1Defaulted() const;
    bool setHour1(double hour1);
    void resetHour1();

    double hour2() const;
    bool isHour2Defaulted() const;
    bool setHour2(double hour2);
    void resetHour2();

    double hour3() const;
    bool isHour3Defaulted() const;
    bool setHour3(double hour3);
    void resetHour3();

    double hour4() const;
    bool isHour4Defaulted() const;
    bool setHour4(double hour4);
    void resetHour4();

    double hour5() const;
    bool isHour5Defaulted() const;
    bool setHour5(double hour5);
    void resetHour5();

    double hour6() const;
    bool isHour6Defaulted() const;
    bool setHour6(double hour6);
    void resetHour6();

    double hour7() const;
    bool isHour7Defaulted() const;
    bool setHour7(double hour7);
    void resetHour7();

    double hour8() const;
    bool isHour8Defaulted() const;
    bool setHour8(double hour8);
    void resetHour8();

    double hour9() const;
    bool isHour9Defaulted() const;
    bool setHour9(double hour9);
    void resetHour9();

    double hour10() const;
    bool isHour10Defaulted() const;
    bool setHour10(double hour10);
    void resetHour10();

    double hour11() const;
    bool isHour11Defaulted() const;
    bool setHour11(double hour11);
    void resetHour11();

    double hour12() const;
    bool isHour12Defaulted() const;
    bool setHour12(double hour12);
    void resetHour12();

    double hour13() const;
    bool isHour13Defaulted() const;
    bool setHour13(double hour13);
    void resetHour13();

    double hour14() const;
    bool isHour14Defaulted() const;
    bool setHour14(double hour14);
    void resetHour14();

    double hour15() const;
    bool isHour15Defaulted() const;
    bool setHour15(double hour15);
    void resetHour15();

    double hour16() const;
    bool isHour16Defaulted() const;
    bool setHour16(double hour16);
    void resetHour16();

    double hour17() const;
    bool isHour17Defaulted() const;
    bool setHour17(double hour17);
    void resetHour17();

    double hour18() const;
    bool isHour18Defaulted() const;
    bool setHour18(double hour18);
    void resetHour18();

    double hour19() const;
    bool isHour19Defaulted() const;
    bool setHour19(double hour19);
    void resetHour19();

    double hour20() const;
    bool isHour20Defaulted() const;
    bool setHour20(double hour20);
    void resetHour20();

    double hour21() const;
    bool isHour21Defaulted() const;
    bool setHour21(double hour21);
    void resetHour21();

    double hour22() const;
    bool isHour22Defaulted() const;
    bool setHour22(double hour22);
    void resetHour22();

    double hour23() const;
    bool isHour23Defaulted() const;
    bool setHour23(double hour23);
    void resetHour23();

    double hour24() const;
    bool isHour24Defaulted() const;
    bool setHour24(double hour24);
    void resetHour24();

   protected:
    using ImplType = detail::ScheduleDayHourly_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ScheduleDayHourly(std::shared_ptr<detail::ScheduleDayHourly_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
