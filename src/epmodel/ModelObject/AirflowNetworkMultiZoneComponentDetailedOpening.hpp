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

  /** \brief Represents the EnergyPlus AirflowNetwork:MultiZone:Component:DetailedOpening object.
   *
   * \par EnergyPlus object
   * \epobject{group-airflow-network.html#airflownetworkmultizonecomponentdetailedopening,AirflowNetwork:MultiZone:Component:DetailedOpening}
   *
   * \par OpenStudio Model API
   * OpenStudio Model has no public wrapper for this EnergyPlus object. This wrapper is new to the EPModel API.
   *
   * \par Known limitations
   * No known EPModel-specific limitations beyond the public fields and relationships exposed by this wrapper.
   */
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
