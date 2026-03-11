/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PHOTOVOLTAICPERFORMANCESANDIA_HPP
#define EPMODEL_PHOTOVOLTAICPERFORMANCESANDIA_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class PhotovoltaicPerformanceSandia_Impl;
}

class EPMODEL_API PhotovoltaicPerformanceSandia : public ModelObject
{
 public:
  explicit PhotovoltaicPerformanceSandia(const Model& model);

  virtual ~PhotovoltaicPerformanceSandia() override = default;
  PhotovoltaicPerformanceSandia(const PhotovoltaicPerformanceSandia& other) = default;
  PhotovoltaicPerformanceSandia(PhotovoltaicPerformanceSandia&& other) = default;
  PhotovoltaicPerformanceSandia& operator=(const PhotovoltaicPerformanceSandia&) = default;
  PhotovoltaicPerformanceSandia& operator=(PhotovoltaicPerformanceSandia&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model PhotovoltaicPerformanceSandia scalar accessor naming/signatures.
  // - Field Mapping: Preserved API maps directly to EnergyPlus PhotovoltaicPerformance:Sandia scalar fields.
  // - Field Mapping: sandiaDatabaseParameterDeltaTc delegates to field enum SandiaDatabaseParameterDelta_Tc_.
  // - TODO(parity): Add non-scalar Sandia DB convenience APIs only if/when parity scope expands.
  double activeArea() const;
  int numberofCellsinSeries() const;
  int numberofCellsinParallel() const;
  double shortCircuitCurrent() const;
  double openCircuitVoltage() const;
  double currentatMaximumPowerPoint() const;
  double voltageatMaximumPowerPoint() const;
  double sandiaDatabaseParameteraIsc() const;
  double sandiaDatabaseParameteraImp() const;
  double sandiaDatabaseParameterc0() const;
  double sandiaDatabaseParameterc1() const;
  double sandiaDatabaseParameterBVoc0() const;
  double sandiaDatabaseParametermBVoc() const;
  double sandiaDatabaseParameterBVmp0() const;
  double sandiaDatabaseParametermBVmp() const;
  double diodeFactor() const;
  double sandiaDatabaseParameterc2() const;
  double sandiaDatabaseParameterc3() const;
  double sandiaDatabaseParametera0() const;
  double sandiaDatabaseParametera1() const;
  double sandiaDatabaseParametera2() const;
  double sandiaDatabaseParametera3() const;
  double sandiaDatabaseParametera4() const;
  double sandiaDatabaseParameterb0() const;
  double sandiaDatabaseParameterb1() const;
  double sandiaDatabaseParameterb2() const;
  double sandiaDatabaseParameterb3() const;
  double sandiaDatabaseParameterb4() const;
  double sandiaDatabaseParameterb5() const;
  double sandiaDatabaseParameterDeltaTc() const;
  double sandiaDatabaseParameterfd() const;
  double sandiaDatabaseParametera() const;
  double sandiaDatabaseParameterb() const;
  double sandiaDatabaseParameterc4() const;
  double sandiaDatabaseParameterc5() const;
  double sandiaDatabaseParameterIx0() const;
  double sandiaDatabaseParameterIxx0() const;
  double sandiaDatabaseParameterc6() const;
  double sandiaDatabaseParameterc7() const;

  bool setActiveArea(double activeArea);
  bool setNumberofCellsinSeries(int numberofCellsinSeries);
  bool setNumberofCellsinParallel(int numberofCellsinParallel);
  bool setShortCircuitCurrent(double shortCircuitCurrent);
  bool setOpenCircuitVoltage(double openCircuitVoltage);
  bool setCurrentatMaximumPowerPoint(double currentatMaximumPowerPoint);
  bool setVoltageatMaximumPowerPoint(double voltageatMaximumPowerPoint);
  bool setSandiaDatabaseParameteraIsc(double sandiaDatabaseParameteraIsc);
  bool setSandiaDatabaseParameteraImp(double sandiaDatabaseParameteraImp);
  bool setSandiaDatabaseParameterc0(double sandiaDatabaseParameterc0);
  bool setSandiaDatabaseParameterc1(double sandiaDatabaseParameterc1);
  bool setSandiaDatabaseParameterBVoc0(double sandiaDatabaseParameterBVoc0);
  bool setSandiaDatabaseParametermBVoc(double sandiaDatabaseParametermBVoc);
  bool setSandiaDatabaseParameterBVmp0(double sandiaDatabaseParameterBVmp0);
  bool setSandiaDatabaseParametermBVmp(double sandiaDatabaseParametermBVmp);
  bool setDiodeFactor(double diodeFactor);
  bool setSandiaDatabaseParameterc2(double sandiaDatabaseParameterc2);
  bool setSandiaDatabaseParameterc3(double sandiaDatabaseParameterc3);
  bool setSandiaDatabaseParametera0(double sandiaDatabaseParametera0);
  bool setSandiaDatabaseParametera1(double sandiaDatabaseParametera1);
  bool setSandiaDatabaseParametera2(double sandiaDatabaseParametera2);
  bool setSandiaDatabaseParametera3(double sandiaDatabaseParametera3);
  bool setSandiaDatabaseParametera4(double sandiaDatabaseParametera4);
  bool setSandiaDatabaseParameterb0(double sandiaDatabaseParameterb0);
  bool setSandiaDatabaseParameterb1(double sandiaDatabaseParameterb1);
  bool setSandiaDatabaseParameterb2(double sandiaDatabaseParameterb2);
  bool setSandiaDatabaseParameterb3(double sandiaDatabaseParameterb3);
  bool setSandiaDatabaseParameterb4(double sandiaDatabaseParameterb4);
  bool setSandiaDatabaseParameterb5(double sandiaDatabaseParameterb5);
  bool setSandiaDatabaseParameterDeltaTc(double sandiaDatabaseParameterDeltaTc);
  bool setSandiaDatabaseParameterfd(double sandiaDatabaseParameterfd);
  bool setSandiaDatabaseParametera(double sandiaDatabaseParametera);
  bool setSandiaDatabaseParameterb(double sandiaDatabaseParameterb);
  bool setSandiaDatabaseParameterc4(double sandiaDatabaseParameterc4);
  bool setSandiaDatabaseParameterc5(double sandiaDatabaseParameterc5);
  bool setSandiaDatabaseParameterIx0(double sandiaDatabaseParameterIx0);
  bool setSandiaDatabaseParameterIxx0(double sandiaDatabaseParameterIxx0);
  bool setSandiaDatabaseParameterc6(double sandiaDatabaseParameterc6);
  bool setSandiaDatabaseParameterc7(double sandiaDatabaseParameterc7);

 protected:
  using ImplType = detail::PhotovoltaicPerformanceSandia_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit PhotovoltaicPerformanceSandia(std::shared_ptr<detail::PhotovoltaicPerformanceSandia_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
