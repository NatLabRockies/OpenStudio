/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PHOTOVOLTAICPERFORMANCESANDIA_IMPL_HPP
#define EPMODEL_PHOTOVOLTAICPERFORMANCESANDIA_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API PhotovoltaicPerformanceSandia_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~PhotovoltaicPerformanceSandia_Impl() override = default;

      double activeArea() const;
      bool setActiveArea(double activeArea);

      int numberofCellsinSeries() const;
      bool setNumberofCellsinSeries(int numberofCellsinSeries);

      int numberofCellsinParallel() const;
      bool setNumberofCellsinParallel(int numberofCellsinParallel);

      double shortCircuitCurrent() const;
      bool setShortCircuitCurrent(double shortCircuitCurrent);

      double openCircuitVoltage() const;
      bool setOpenCircuitVoltage(double openCircuitVoltage);

      double currentatMaximumPowerPoint() const;
      bool setCurrentatMaximumPowerPoint(double currentatMaximumPowerPoint);

      double voltageatMaximumPowerPoint() const;
      bool setVoltageatMaximumPowerPoint(double voltageatMaximumPowerPoint);

      double sandiaDatabaseParameteraIsc() const;
      bool setSandiaDatabaseParameteraIsc(double sandiaDatabaseParameteraIsc);

      double sandiaDatabaseParameteraImp() const;
      bool setSandiaDatabaseParameteraImp(double sandiaDatabaseParameteraImp);

      double sandiaDatabaseParameterc0() const;
      bool setSandiaDatabaseParameterc0(double sandiaDatabaseParameterc0);

      double sandiaDatabaseParameterc1() const;
      bool setSandiaDatabaseParameterc1(double sandiaDatabaseParameterc1);

      double sandiaDatabaseParameterBVoc0() const;
      bool setSandiaDatabaseParameterBVoc0(double sandiaDatabaseParameterBVoc0);

      double sandiaDatabaseParametermBVoc() const;
      bool setSandiaDatabaseParametermBVoc(double sandiaDatabaseParametermBVoc);

      double sandiaDatabaseParameterBVmp0() const;
      bool setSandiaDatabaseParameterBVmp0(double sandiaDatabaseParameterBVmp0);

      double sandiaDatabaseParametermBVmp() const;
      bool setSandiaDatabaseParametermBVmp(double sandiaDatabaseParametermBVmp);

      double diodeFactor() const;
      bool setDiodeFactor(double diodeFactor);

      double sandiaDatabaseParameterc2() const;
      bool setSandiaDatabaseParameterc2(double sandiaDatabaseParameterc2);

      double sandiaDatabaseParameterc3() const;
      bool setSandiaDatabaseParameterc3(double sandiaDatabaseParameterc3);

      double sandiaDatabaseParametera0() const;
      bool setSandiaDatabaseParametera0(double sandiaDatabaseParametera0);

      double sandiaDatabaseParametera1() const;
      bool setSandiaDatabaseParametera1(double sandiaDatabaseParametera1);

      double sandiaDatabaseParametera2() const;
      bool setSandiaDatabaseParametera2(double sandiaDatabaseParametera2);

      double sandiaDatabaseParametera3() const;
      bool setSandiaDatabaseParametera3(double sandiaDatabaseParametera3);

      double sandiaDatabaseParametera4() const;
      bool setSandiaDatabaseParametera4(double sandiaDatabaseParametera4);

      double sandiaDatabaseParameterb0() const;
      bool setSandiaDatabaseParameterb0(double sandiaDatabaseParameterb0);

      double sandiaDatabaseParameterb1() const;
      bool setSandiaDatabaseParameterb1(double sandiaDatabaseParameterb1);

      double sandiaDatabaseParameterb2() const;
      bool setSandiaDatabaseParameterb2(double sandiaDatabaseParameterb2);

      double sandiaDatabaseParameterb3() const;
      bool setSandiaDatabaseParameterb3(double sandiaDatabaseParameterb3);

      double sandiaDatabaseParameterb4() const;
      bool setSandiaDatabaseParameterb4(double sandiaDatabaseParameterb4);

      double sandiaDatabaseParameterb5() const;
      bool setSandiaDatabaseParameterb5(double sandiaDatabaseParameterb5);

      double sandiaDatabaseParameterDeltaTc() const;
      bool setSandiaDatabaseParameterDeltaTc(double sandiaDatabaseParameterDeltaTc);

      double sandiaDatabaseParameterfd() const;
      bool setSandiaDatabaseParameterfd(double sandiaDatabaseParameterfd);

      double sandiaDatabaseParametera() const;
      bool setSandiaDatabaseParametera(double sandiaDatabaseParametera);

      double sandiaDatabaseParameterb() const;
      bool setSandiaDatabaseParameterb(double sandiaDatabaseParameterb);

      double sandiaDatabaseParameterc4() const;
      bool setSandiaDatabaseParameterc4(double sandiaDatabaseParameterc4);

      double sandiaDatabaseParameterc5() const;
      bool setSandiaDatabaseParameterc5(double sandiaDatabaseParameterc5);

      double sandiaDatabaseParameterIx0() const;
      bool setSandiaDatabaseParameterIx0(double sandiaDatabaseParameterIx0);

      double sandiaDatabaseParameterIxx0() const;
      bool setSandiaDatabaseParameterIxx0(double sandiaDatabaseParameterIxx0);

      double sandiaDatabaseParameterc6() const;
      bool setSandiaDatabaseParameterc6(double sandiaDatabaseParameterc6);

      double sandiaDatabaseParameterc7() const;
      bool setSandiaDatabaseParameterc7(double sandiaDatabaseParameterc7);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
