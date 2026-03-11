/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include <algorithm>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirflowNetworkMultiZoneComponentDetailedOpening.hpp"
#include <utilities/idd/AirflowNetwork_MultiZone_Component_DetailedOpening_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirflowNetworkMultiZoneComponentDetailedOpening_DefaultConstructor) {
  Model model;
  AirflowNetworkMultiZoneComponentDetailedOpening opening(model);
  EXPECT_EQ(AirflowNetworkMultiZoneComponentDetailedOpening::iddObjectType(), opening.iddObject().type());
}

TEST_F(EPModelFixture, AirflowNetworkMultiZoneComponentDetailedOpening_ScalarAccessors_RoundTrip) {
  Model model;
  AirflowNetworkMultiZoneComponentDetailedOpening opening(model);

  EXPECT_TRUE(opening.setAirMassFlowCoefficientWhenOpeningisClosed(0.0025));
  EXPECT_DOUBLE_EQ(0.0025, opening.airMassFlowCoefficientWhenOpeningisClosed());

  EXPECT_TRUE(opening.isAirMassFlowExponentWhenOpeningisClosedDefaulted());
  EXPECT_DOUBLE_EQ(0.65, opening.airMassFlowExponentWhenOpeningisClosed());
  EXPECT_TRUE(opening.setAirMassFlowExponentWhenOpeningisClosed(0.8));
  EXPECT_DOUBLE_EQ(0.8, opening.airMassFlowExponentWhenOpeningisClosed());
  EXPECT_FALSE(opening.isAirMassFlowExponentWhenOpeningisClosedDefaulted());
  opening.resetAirMassFlowExponentWhenOpeningisClosed();
  EXPECT_TRUE(opening.isAirMassFlowExponentWhenOpeningisClosedDefaulted());
  EXPECT_DOUBLE_EQ(0.65, opening.airMassFlowExponentWhenOpeningisClosed());

  const auto lvoValues = AirflowNetworkMultiZoneComponentDetailedOpening::typeofRectangularLargeVerticalOpeningLVOValues();
  EXPECT_FALSE(lvoValues.empty());
  EXPECT_NE(std::find(lvoValues.begin(), lvoValues.end(), "NonPivoted"), lvoValues.end());

  EXPECT_TRUE(opening.isTypeofRectangularLargeVerticalOpeningLVODefaulted());
  EXPECT_EQ("NonPivoted", opening.typeofRectangularLargeVerticalOpeningLVO());
  EXPECT_TRUE(opening.setTypeofRectangularLargeVerticalOpeningLVO("HorizontallyPivoted"));
  EXPECT_EQ("HorizontallyPivoted", opening.typeofRectangularLargeVerticalOpeningLVO());
  EXPECT_FALSE(opening.isTypeofRectangularLargeVerticalOpeningLVODefaulted());
  opening.resetTypeofRectangularLargeVerticalOpeningLVO();
  EXPECT_TRUE(opening.isTypeofRectangularLargeVerticalOpeningLVODefaulted());
  EXPECT_EQ("NonPivoted", opening.typeofRectangularLargeVerticalOpeningLVO());

  EXPECT_TRUE(opening.isExtraCrackLengthorHeightofPivotingAxisDefaulted());
  EXPECT_DOUBLE_EQ(0.0, opening.extraCrackLengthorHeightofPivotingAxis());
  EXPECT_TRUE(opening.setExtraCrackLengthorHeightofPivotingAxis(0.19));
  EXPECT_DOUBLE_EQ(0.19, opening.extraCrackLengthorHeightofPivotingAxis());
  EXPECT_FALSE(opening.isExtraCrackLengthorHeightofPivotingAxisDefaulted());
  opening.resetExtraCrackLengthorHeightofPivotingAxis();
  EXPECT_TRUE(opening.isExtraCrackLengthorHeightofPivotingAxisDefaulted());
  EXPECT_DOUBLE_EQ(0.0, opening.extraCrackLengthorHeightofPivotingAxis());

  // Relationship/extensible fields remain accessible through generic IDF APIs and are excluded from scalar wrappers.
  EXPECT_TRUE(
    opening.setInt(openstudio::AirflowNetwork_MultiZone_Component_DetailedOpeningFields::NumberofSetsofOpeningFactorData, 2));
  auto numberOfSets =
    opening.getInt(openstudio::AirflowNetwork_MultiZone_Component_DetailedOpeningFields::NumberofSetsofOpeningFactorData, true);
  ASSERT_TRUE(numberOfSets);
  EXPECT_EQ(2, *numberOfSets);
}
