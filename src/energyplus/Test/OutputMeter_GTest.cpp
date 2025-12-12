/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include "EnergyPlusFixture.hpp"

#include "../ForwardTranslator.hpp"
#include "../ReverseTranslator.hpp"

#include "../../model/OutputMeter.hpp"
#include "../../model/OutputMeter_Impl.hpp"

#include "../../utilities/idf/Workspace.hpp"
#include "../../utilities/idf/IdfObject.hpp"
#include "../../utilities/idf/WorkspaceObject.hpp"
#include "../../utilities/data/DataEnums.hpp"

// E+ FieldEnums
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/Output_Meter_FieldEnums.hxx>
#include <utilities/idd/Output_Meter_MeterFileOnly_FieldEnums.hxx>
#include <utilities/idd/Output_Meter_Cumulative_FieldEnums.hxx>
#include <utilities/idd/Output_Meter_Cumulative_MeterFileOnly_FieldEnums.hxx>

#include <algorithm>
#include <array>
#include <compare>

using namespace openstudio::energyplus;
using namespace openstudio::model;
using namespace openstudio;

TEST_F(EnergyPlusFixture, ForwardTranslator_OutputMeter_Regular) {

  ForwardTranslator ft;

  Model m;
  OutputMeter meter(m);
  EXPECT_TRUE(meter.setInstallLocationType(InstallLocationType::Facility));
  EXPECT_TRUE(meter.setFuelType(FuelType::Gas));

  EXPECT_TRUE(meter.setReportingFrequency("Timestep"));
  EXPECT_TRUE(meter.setMeterFileOnly(false));
  EXPECT_TRUE(meter.setCumulative(false));

  const Workspace w = ft.translateModel(m);
  const auto idfObjs = w.getObjectsByType(IddObjectType::Output_Meter);
  ASSERT_EQ(1u, idfObjs.size());

  const auto& idfObject = idfObjs.front();
  EXPECT_EQ("NaturalGas:Facility", idfObject.getString(Output_MeterFields::KeyName).get());
  EXPECT_EQ("Timestep", idfObject.getString(Output_MeterFields::ReportingFrequency).get());
}

TEST_F(EnergyPlusFixture, ForwardTranslator_OutputMeter_MeterFileOnly) {

  ForwardTranslator ft;

  Model m;
  OutputMeter meter(m);
  EXPECT_TRUE(meter.setInstallLocationType(InstallLocationType::Facility));
  EXPECT_TRUE(meter.setFuelType(FuelType::Gas));

  EXPECT_TRUE(meter.setReportingFrequency("Timestep"));
  EXPECT_TRUE(meter.setMeterFileOnly(true));
  EXPECT_TRUE(meter.setCumulative(false));

  const Workspace w = ft.translateModel(m);
  const auto idfObjs = w.getObjectsByType(IddObjectType::Output_Meter_MeterFileOnly);
  ASSERT_EQ(1u, idfObjs.size());

  const auto& idfObject = idfObjs.front();
  EXPECT_EQ("NaturalGas:Facility", idfObject.getString(Output_Meter_MeterFileOnlyFields::KeyName).get());
  EXPECT_EQ("Timestep", idfObject.getString(Output_Meter_MeterFileOnlyFields::ReportingFrequency).get());
}

TEST_F(EnergyPlusFixture, ForwardTranslator_OutputMeter_Cumulative) {

  ForwardTranslator ft;

  Model m;
  OutputMeter meter(m);
  EXPECT_TRUE(meter.setInstallLocationType(InstallLocationType::Facility));
  EXPECT_TRUE(meter.setFuelType(FuelType::Gas));

  EXPECT_TRUE(meter.setReportingFrequency("Timestep"));
  EXPECT_TRUE(meter.setMeterFileOnly(false));
  EXPECT_TRUE(meter.setCumulative(true));

  const Workspace w = ft.translateModel(m);
  const auto idfObjs = w.getObjectsByType(IddObjectType::Output_Meter_Cumulative);
  ASSERT_EQ(1u, idfObjs.size());

  const auto& idfObject = idfObjs.front();
  EXPECT_EQ("NaturalGas:Facility", idfObject.getString(Output_Meter_CumulativeFields::KeyName).get());
  EXPECT_EQ("Timestep", idfObject.getString(Output_Meter_CumulativeFields::ReportingFrequency).get());
}

TEST_F(EnergyPlusFixture, ForwardTranslator_OutputMeter_Cumulative_MeterFileOnly) {

  ForwardTranslator ft;

  Model m;
  OutputMeter meter(m);
  EXPECT_TRUE(meter.setInstallLocationType(InstallLocationType::Facility));
  EXPECT_TRUE(meter.setFuelType(FuelType::Gas));

  EXPECT_TRUE(meter.setReportingFrequency("Timestep"));
  EXPECT_TRUE(meter.setMeterFileOnly(true));
  EXPECT_TRUE(meter.setCumulative(true));

  const Workspace w = ft.translateModel(m);
  const auto idfObjs = w.getObjectsByType(IddObjectType::Output_Meter_Cumulative_MeterFileOnly);
  ASSERT_EQ(1u, idfObjs.size());

  const auto& idfObject = idfObjs.front();
  EXPECT_EQ("NaturalGas:Facility", idfObject.getString(Output_Meter_Cumulative_MeterFileOnlyFields::KeyName).get());
  EXPECT_EQ("Timestep", idfObject.getString(Output_Meter_Cumulative_MeterFileOnlyFields::ReportingFrequency).get());
}

TEST_F(EnergyPlusFixture, ReverseTranslator_OutputMeter_Regular) {

  ReverseTranslator rt;

  Workspace w(StrictnessLevel::Minimal, IddFileType::EnergyPlus);

  auto woMeter = w.addObject(IdfObject(IddObjectType::Output_Meter)).get();

  EXPECT_TRUE(woMeter.setString(Output_MeterFields::KeyName, "NaturalGas:Facility"));
  EXPECT_TRUE(woMeter.setString(Output_MeterFields::ReportingFrequency, "Timestep"));

  const Model m = rt.translateWorkspace(w);
  const auto modelObjects = m.getConcreteModelObjects<OutputMeter>();
  ASSERT_EQ(1u, modelObjects.size());

  const auto& modelObject = modelObjects.front();
  EXPECT_EQ("NaturalGas:Facility", modelObject.name());
  EXPECT_EQ("Timestep", modelObject.reportingFrequency());
  EXPECT_FALSE(modelObject.meterFileOnly());
  EXPECT_FALSE(modelObject.cumulative());
}

TEST_F(EnergyPlusFixture, ReverseTranslator_OutputMeter_MeterFileOnly) {

  ReverseTranslator rt;

  Workspace w(StrictnessLevel::Minimal, IddFileType::EnergyPlus);

  auto woMeter = w.addObject(IdfObject(IddObjectType::Output_Meter_MeterFileOnly)).get();

  EXPECT_TRUE(woMeter.setString(Output_Meter_MeterFileOnlyFields::KeyName, "NaturalGas:Facility"));
  EXPECT_TRUE(woMeter.setString(Output_Meter_MeterFileOnlyFields::ReportingFrequency, "Timestep"));

  const Model m = rt.translateWorkspace(w);
  const auto modelObjects = m.getConcreteModelObjects<OutputMeter>();
  ASSERT_EQ(1u, modelObjects.size());

  const auto& modelObject = modelObjects.front();
  EXPECT_EQ("NaturalGas:Facility", modelObject.name());
  EXPECT_EQ("Timestep", modelObject.reportingFrequency());
  EXPECT_TRUE(modelObject.meterFileOnly());
  EXPECT_FALSE(modelObject.cumulative());
}

TEST_F(EnergyPlusFixture, ReverseTranslator_OutputMeter_Cumulative) {

  ReverseTranslator rt;

  Workspace w(StrictnessLevel::Minimal, IddFileType::EnergyPlus);

  auto woMeter = w.addObject(IdfObject(IddObjectType::Output_Meter_Cumulative)).get();

  EXPECT_TRUE(woMeter.setString(Output_Meter_CumulativeFields::KeyName, "NaturalGas:Facility"));
  EXPECT_TRUE(woMeter.setString(Output_Meter_CumulativeFields::ReportingFrequency, "Timestep"));

  const Model m = rt.translateWorkspace(w);
  const auto modelObjects = m.getConcreteModelObjects<OutputMeter>();
  ASSERT_EQ(1u, modelObjects.size());

  const auto& modelObject = modelObjects.front();
  EXPECT_EQ("NaturalGas:Facility", modelObject.name());
  EXPECT_EQ("Timestep", modelObject.reportingFrequency());
  EXPECT_FALSE(modelObject.meterFileOnly());
  EXPECT_TRUE(modelObject.cumulative());
}

TEST_F(EnergyPlusFixture, ReverseTranslator_OutputMeter_Cumulative_MeterFileOnly) {

  ReverseTranslator rt;

  Workspace w(StrictnessLevel::Minimal, IddFileType::EnergyPlus);

  auto woMeter = w.addObject(IdfObject(IddObjectType::Output_Meter_Cumulative_MeterFileOnly)).get();

  EXPECT_TRUE(woMeter.setString(Output_Meter_Cumulative_MeterFileOnlyFields::KeyName, "NaturalGas:Facility"));
  EXPECT_TRUE(woMeter.setString(Output_Meter_Cumulative_MeterFileOnlyFields::ReportingFrequency, "Timestep"));

  const Model m = rt.translateWorkspace(w);
  const auto modelObjects = m.getConcreteModelObjects<OutputMeter>();
  ASSERT_EQ(1u, modelObjects.size());

  const auto& modelObject = modelObjects.front();
  EXPECT_EQ("NaturalGas:Facility", modelObject.name());
  EXPECT_EQ("Timestep", modelObject.reportingFrequency());
  EXPECT_TRUE(modelObject.meterFileOnly());
  EXPECT_TRUE(modelObject.cumulative());
}

// This will grab the objects in the same order as the serialization to IDF
std::vector<WorkspaceObject> getMetersInSerializedOrder(const Workspace& w) {
  WorkspaceObjectVector result;
  const std::array<IddObjectType, 4> iddTypes = {
    IddObjectType::Output_Meter,
    IddObjectType::Output_Meter_MeterFileOnly,
    IddObjectType::Output_Meter_Cumulative,
    IddObjectType::Output_Meter_Cumulative_MeterFileOnly,
  };
  // objects(sorted=true): same as serialization order
  for (const WorkspaceObject& object : w.objects(true)) {
    if (std::find(iddTypes.begin(), iddTypes.end(), object.iddObject().type()) != iddTypes.end()) {
      result.push_back(object);
    }
  }
  return result;
}

struct MeterInfo
{
  std::string name;
  std::string reportingFrequency;
  bool meterFileOnly;
  bool cumulative;

  MeterInfo(std::string t_name, std::string t_reportingFrequency, bool meterFileOnly, bool cumulative)
    : name(std::move(t_name)), reportingFrequency(std::move(t_reportingFrequency)), meterFileOnly(meterFileOnly), cumulative(cumulative){};

  MeterInfo(const WorkspaceObject& wo) {
    switch (wo.iddObject().type().value()) {
      case IddObjectType::Output_Meter: {
        name = wo.getString(Output_MeterFields::KeyName).get();
        reportingFrequency = wo.getString(Output_MeterFields::ReportingFrequency).get();
        meterFileOnly = false;
        cumulative = false;
        break;
      }
      case IddObjectType::Output_Meter_MeterFileOnly: {
        name = wo.getString(Output_Meter_MeterFileOnlyFields::KeyName).get();
        reportingFrequency = wo.getString(Output_Meter_MeterFileOnlyFields::ReportingFrequency).get();
        meterFileOnly = true;
        cumulative = false;
        break;
      }
      case IddObjectType::Output_Meter_Cumulative: {
        name = wo.getString(Output_Meter_CumulativeFields::KeyName).get();
        reportingFrequency = wo.getString(Output_Meter_CumulativeFields::ReportingFrequency).get();
        meterFileOnly = false;
        cumulative = true;
        break;
      }
      case IddObjectType::Output_Meter_Cumulative_MeterFileOnly: {
        name = wo.getString(Output_Meter_Cumulative_MeterFileOnlyFields::KeyName).get();
        reportingFrequency = wo.getString(Output_Meter_Cumulative_MeterFileOnlyFields::ReportingFrequency).get();
        meterFileOnly = true;
        cumulative = true;
        break;
      }
      default:
        throw std::runtime_error("Unexpected IddObjectType in MeterInfo constructor");
    }
  }

  std::string meterType() const {
    if (cumulative && meterFileOnly) {
      return "Output:Meter:Cumulative:MeterFileOnly";
    } else if (cumulative) {
      return "Output:Meter:Cumulative";
    } else if (meterFileOnly) {
      return "Output:Meter:MeterFileOnly";
    } else {
      return "Output:Meter";
    }
  }

  auto operator<=>(const MeterInfo&) const = default;
};

std::ostream& operator<<(std::ostream& os, const MeterInfo& mi) {
  os << mi.meterType() << "{name = '" << mi.name << "', reportingFrequency ='" << mi.reportingFrequency << "'}";
  return os;
}

TEST_F(EnergyPlusFixture, ForwardTranslator_OutputMeter_ReproducibleOrder) {

  ForwardTranslator ft;
  ft.setExcludeLCCObjects(true);
  ft.setExcludeHTMLOutputReport(true);
  ft.setExcludeSQliteOutputReport(true);
  ft.setExcludeVariableDictionary(true);

  // Electricity:Total ends up being a child of Building, so it's translated first
  const std::vector<std::string> meter_names{"Electricity:Total", "NaturalGas:Facility", "Electricity:Facility"};
  const std::vector<std::string> reporting_frequencies{"RunPeriod", "Monthly"};
  const std::vector<bool> fileonlys{true, false};
  const std::vector<bool> cumulatives{true, false};

  const std::vector<std::string> ordered_meter_names = {
    "Electricity:Total",  // This one is first because it's a child of Building
    "Electricity:Facility",
    "NaturalGas:Facility",
  };
  std::vector<std::string> ordered_reporting_frequencies = reporting_frequencies;
  std::sort(ordered_reporting_frequencies.begin(), ordered_reporting_frequencies.end());

  // TL;DR: this means that given the same name and reporting frequency, order is
  // 1. Output:Meter
  // 2. Output:Meter:Cumulative
  // 3. Output:Meter:MeterFileOnly
  // 4. Output:Meter:Cumulative:MeterFileOnly
  std::vector<bool> ordered_fileonlys = fileonlys;
  std::sort(ordered_fileonlys.begin(), ordered_fileonlys.end());  // false, true
  std::vector<bool> ordered_cumulatives = cumulatives;
  std::sort(ordered_cumulatives.begin(), ordered_cumulatives.end());  // false, true

  std::vector<MeterInfo> expectedMeterInfos;
  for (const auto& name : ordered_meter_names) {
    for (const auto& reportingFrequency : ordered_reporting_frequencies) {
      for (const auto& meterFileOnly : ordered_fileonlys) {
        for (const auto& cumulative : ordered_cumulatives) {
          expectedMeterInfos.emplace_back(name, reportingFrequency, meterFileOnly, cumulative);
        }
      }
    }
  }

  auto prepareModel = [&meter_names, &reporting_frequencies, &fileonlys, &cumulatives]() -> openstudio::model::Model {
    Model m;
    for (const auto& name : meter_names) {
      for (const auto& freq : reporting_frequencies) {
        for (const auto& meterFileOnly : fileonlys) {
          for (const auto& cumulative : cumulatives) {
            OutputMeter meter(m);
            EXPECT_TRUE(meter.setName(name));
            EXPECT_TRUE(meter.setReportingFrequency(freq));
            EXPECT_TRUE(meter.setMeterFileOnly(meterFileOnly));
            EXPECT_TRUE(meter.setCumulative(cumulative));
          }
        }
      }
    }
    return m;
  };

  auto produceMeterInfo = [&]() -> std::vector<MeterInfo> {
    auto m = prepareModel();

    const Workspace w = ft.translateModel(prepareModel());
    const auto idfObjs = getMetersInSerializedOrder(w);

    std::vector<MeterInfo> meterInfos;
    meterInfos.reserve(idfObjs.size());
    std::transform(idfObjs.begin(), idfObjs.end(), std::back_inserter(meterInfos), [](const WorkspaceObject& wo) { return MeterInfo(wo); });
    return meterInfos;
  };

  auto meterInfos = produceMeterInfo();
  ASSERT_EQ(meter_names.size() * reporting_frequencies.size() * fileonlys.size() * cumulatives.size(), meterInfos.size());
  EXPECT_EQ(expectedMeterInfos, meterInfos);

  size_t n_failures = 0;
  for (size_t n = 1; n < 10; ++n) {
    auto newMeterInfos = produceMeterInfo();
    // EXPECT_EQ(meterInfos, newMeterInfos) << "MeterInfos differ on iteration " << n;
    EXPECT_EQ(meterInfos.size(), newMeterInfos.size());
    for (size_t i = 0; i < meterInfos.size(); ++i) {
      EXPECT_EQ(meterInfos[i], newMeterInfos[i]) << "MeterInfos differ at index " << i << " on iteration " << n;
    }
    if (meterInfos != newMeterInfos) {
      ++n_failures;
    }
  }
  EXPECT_EQ(0, n_failures) << "Out of 9 re-translations, " << n_failures << " produced different OutputMeter orderings.";
}
