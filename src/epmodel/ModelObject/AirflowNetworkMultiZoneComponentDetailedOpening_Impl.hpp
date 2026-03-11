/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKMULTIZONECOMPONENTDETAILEDOPENING_IMPL_HPP
#define EPMODEL_AIRFLOWNETWORKMULTIZONECOMPONENTDETAILEDOPENING_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API AirflowNetworkMultiZoneComponentDetailedOpening_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~AirflowNetworkMultiZoneComponentDetailedOpening_Impl() override = default;

  double airMassFlowCoefficientWhenOpeningisClosed() const;
  bool setAirMassFlowCoefficientWhenOpeningisClosed(double airMassFlowCoefficientWhenOpeningisClosed);

  double airMassFlowExponentWhenOpeningisClosed() const;
  bool isAirMassFlowExponentWhenOpeningisClosedDefaulted() const;
  bool setAirMassFlowExponentWhenOpeningisClosed(double airMassFlowExponentWhenOpeningisClosed);
  void resetAirMassFlowExponentWhenOpeningisClosed();

  std::string typeofRectangularLargeVerticalOpeningLVO() const;
  bool isTypeofRectangularLargeVerticalOpeningLVODefaulted() const;
  bool setTypeofRectangularLargeVerticalOpeningLVO(const std::string& typeofRectangularLargeVerticalOpeningLVO);
  void resetTypeofRectangularLargeVerticalOpeningLVO();

  double extraCrackLengthorHeightofPivotingAxis() const;
  bool isExtraCrackLengthorHeightofPivotingAxisDefaulted() const;
  bool setExtraCrackLengthorHeightofPivotingAxis(double extraCrackLengthorHeightofPivotingAxis);
  void resetExtraCrackLengthorHeightofPivotingAxis();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
