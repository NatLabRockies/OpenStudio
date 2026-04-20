/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/SolarCollectorUnglazedTranspired.hpp"
#include "../scaffolds/SolarCollectorUnglazedTranspiredMultisystem.hpp"

#include <utilities/idd/SolarCollector_UnglazedTranspired_Multisystem_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SolarCollectorUnglazedTranspiredMultisystem_DefaultConstructor) {
  Model model;
  SolarCollectorUnglazedTranspiredMultisystem multisystem(model);
  EXPECT_EQ(SolarCollectorUnglazedTranspiredMultisystem::iddObjectType(), multisystem.iddObject().type());
}

TEST_F(EPModelFixture, SolarCollectorUnglazedTranspiredMultisystem_ScalarAccessors_RoundTrip) {
  Model model;
  SolarCollectorUnglazedTranspired collector(model);
  SolarCollectorUnglazedTranspiredMultisystem multisystem(model);

  ASSERT_TRUE(collector.setName("UTSC-1"));
  EXPECT_TRUE(multisystem.setPointer(openstudio::SolarCollector_UnglazedTranspired_MultisystemFields::SolarCollectorName, collector.handle()));
  auto linkedCollector = multisystem.getTarget(openstudio::SolarCollector_UnglazedTranspired_MultisystemFields::SolarCollectorName);
  ASSERT_TRUE(linkedCollector);
  EXPECT_EQ(collector.handle(), linkedCollector->handle());
}
