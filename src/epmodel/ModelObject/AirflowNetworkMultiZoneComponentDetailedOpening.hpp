/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKMULTIZONECOMPONENTDETAILEDOPENING_HPP
#define EPMODEL_AIRFLOWNETWORKMULTIZONECOMPONENTDETAILEDOPENING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirflowNetworkMultiZoneComponentDetailedOpening_Impl;
  }

  class EPMODEL_API AirflowNetworkMultiZoneComponentDetailedOpening : public ModelObject
  {
   public:
    explicit AirflowNetworkMultiZoneComponentDetailedOpening(const Model& model);

    virtual ~AirflowNetworkMultiZoneComponentDetailedOpening() override = default;
    AirflowNetworkMultiZoneComponentDetailedOpening(const AirflowNetworkMultiZoneComponentDetailedOpening& other) = default;
    AirflowNetworkMultiZoneComponentDetailedOpening(AirflowNetworkMultiZoneComponentDetailedOpening&& other) = default;
    AirflowNetworkMultiZoneComponentDetailedOpening& operator=(const AirflowNetworkMultiZoneComponentDetailedOpening&) = default;
    AirflowNetworkMultiZoneComponentDetailedOpening& operator=(AirflowNetworkMultiZoneComponentDetailedOpening&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> typeofRectangularLargeVerticalOpeningLVOValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to EnergyPlus
    //   AirflowNetwork:MultiZone:Component:DetailedOpening fields N1/N2/A2/N3.
    // - ForwardTranslator evidence: translateAirflowNetworkDetailedOpening writes these scalar fields directly,
    //   including enum token TypeofRectangularLargeVerticalOpening_LVO_.
    // - Field Mapping: Number of Sets of Opening Factor Data plus extensible opening-factor tuples are intentionally
    //   excluded from simple scalar accessor scaffolding.
    // - TODO(parity): Add dedicated extensible-group APIs after scalar saturation.
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

   protected:
    using ImplType = detail::AirflowNetworkMultiZoneComponentDetailedOpening_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirflowNetworkMultiZoneComponentDetailedOpening(std::shared_ptr<detail::AirflowNetworkMultiZoneComponentDetailedOpening_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
