/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include "MeasureFixture.hpp"

#include "../OSArgument.hpp"
#include "../OSRunner.hpp"
#include "../OSMeasure.hpp"
#include "../ModelMeasure.hpp"

#include "../../epmodel/Model.hpp"
#include "../../epmodel/ModelObject/Timestep.hpp"
#include "../../epmodel/ModelObject/Timestep_Impl.hpp"
#include "../../model/Model.hpp"
#include "../../model/Space.hpp"
#include "../../model/Space_Impl.hpp"
#include "../../model/LightsDefinition.hpp"
#include "../../model/LightsDefinition_Impl.hpp"

#include "../../utilities/idd/IddEnums.hpp"
#include <utilities/idd/IddEnums.hxx>

#include "../../utilities/idf/IdfObject.hpp"
#include "../../utilities/idf/WorkspaceObject.hpp"
#include "../../utilities/core/Finder.hpp"
#include "../../utilities/core/StringStreamLogSink.hpp"
#include "../../utilities/filetypes/WorkflowJSON.hpp"
#include "../../utilities/filetypes/WorkflowStep.hpp"

#include "../../utilities/units/QuantityConverter.hpp"

#include <fmt/format.h>

#include <limits>
#include <map>
#include <vector>

using namespace openstudio;
using namespace openstudio::model;
using namespace openstudio::measure;

class TestOSRunner : public OSRunner
{
 public:
  TestOSRunner(const WorkflowJSON& workflow) : OSRunner(workflow) {}

  virtual bool inSelection(const openstudio::model::ModelObject& /*modelObject*/) const override {
    return false;
  }
};

namespace {

openstudio::epmodel::Timestep addTimestep(openstudio::epmodel::Model& model, int numberOfTimestepsPerHour) {
  auto object = model.getUniqueModelObject<openstudio::epmodel::Timestep>();
  OS_ASSERT(object.setNumberOfTimestepsPerHour(numberOfTimestepsPerHour));
  return object;
}

}  // namespace

// derive some test classes
class TestModelUserScript1 : public ModelMeasure
{
 public:
  virtual std::string name() const override {
    return "TestModelUserScript1";
  }

  // remove all objects and add a new one
  virtual bool run(openstudio::epmodel::Model& model, OSRunner& runner, const std::map<std::string, OSArgument>& user_arguments) const override {
    ModelMeasure::run(model, runner, user_arguments);

    if (!runner.validateUserArguments(arguments(model), user_arguments)) {
      return false;
    }

    std::stringstream ss;

    // remove old objects
    const auto objects = model.objects();
    int count = static_cast<int>(objects.size());
    for (auto object : objects) {
      object.remove();
    }
    ss << "Initial model had " << count << " objects.";
    runner.registerInitialCondition(ss.str());
    ss.str("");

    // add a new one
    addTimestep(model, 6);

    ss << "Removed the " << count << " original objects, and added one new Timestep object.";
    runner.registerFinalCondition(ss.str());

    // success
    return true;
  }
};

TEST_F(MeasureFixture, UserScript_TestModelUserScript1) {
  TestModelUserScript1 script;
  EXPECT_EQ("TestModelUserScript1", script.name());

  std::vector<WorkflowStep> steps;
  steps.push_back(MeasureStep("dummy"));

  WorkflowJSON workflow;
  workflow.setWorkflowSteps(steps);

  TestOSRunner runner(workflow);
  std::map<std::string, OSArgument> user_arguments;

  // test with empty model
  openstudio::epmodel::Model model1;
  EXPECT_EQ(0u, model1.numObjects());
  EXPECT_EQ(0u, script.arguments(model1).size());
  script.run(model1, runner, user_arguments);
  EXPECT_EQ(1u, model1.numObjects());
  WorkflowStepResult result = runner.result();
  ASSERT_TRUE(result.stepResult());
  EXPECT_TRUE(result.stepResult()->value() == StepResult::Success);
  EXPECT_EQ(0u, result.stepErrors().size());
  EXPECT_EQ(0u, result.stepWarnings().size());
  EXPECT_EQ(0u, result.stepInfo().size());
  ASSERT_TRUE(result.initialCondition());
  EXPECT_EQ("Initial model had 0 objects.", result.initialCondition()->logMessage());
  ASSERT_TRUE(result.finalCondition());
  EXPECT_EQ("Removed the 0 original objects, and added one new Timestep object.", result.finalCondition()->logMessage());

  // test with populated model
  openstudio::epmodel::Model model2;
  addTimestep(model2, 4);
  openstudio::IdfObject outputVariable(openstudio::IddObjectType::Output_Variable);
  outputVariable.setString(0, "*");
  outputVariable.setString(1, "Site Outdoor Air Drybulb Temperature");
  outputVariable.setString(2, "Hourly");
  ASSERT_TRUE(model2.addObject(outputVariable));
  EXPECT_EQ(2u, model2.numObjects());
  EXPECT_EQ(0u, script.arguments(model2).size());
  script.run(model2, runner, user_arguments);
  EXPECT_EQ(1u, model2.numObjects());
  result = runner.result();
  ASSERT_TRUE(result.stepResult());
  EXPECT_TRUE(result.stepResult()->value() == StepResult::Success);
  EXPECT_EQ(0u, result.stepErrors().size());
  EXPECT_EQ(0u, result.stepWarnings().size());
  EXPECT_EQ(0u, result.stepInfo().size());
  ASSERT_TRUE(result.initialCondition());
  EXPECT_EQ("Initial model had 2 objects.", result.initialCondition()->logMessage());
  ASSERT_TRUE(result.finalCondition());
  EXPECT_EQ("Removed the 2 original objects, and added one new Timestep object.", result.finalCondition()->logMessage());
}

class TestModelUserScript2 : public ModelMeasure
{
 public:
  virtual std::string name() const override {
    return "TestModelUserScript2";
  }

  virtual std::vector<OSArgument> arguments(const openstudio::epmodel::Model& model) const override {
    std::vector<OSArgument> result;

    OSArgument arg = makeChoiceArgumentOfWorkspaceObjects("timestep", IddObjectType::Timestep, model);
    result.push_back(arg);

    arg = OSArgument::makeDoubleArgument("multiplier", false);
    arg.setDefaultValue(0.8);
    result.push_back(arg);

    return result;
  }

  virtual bool run(openstudio::epmodel::Model& model, OSRunner& runner, const std::map<std::string, OSArgument>& user_arguments) const override {
    ModelMeasure::run(model, runner, user_arguments);  // initializes runner

    // calls runner.registerAttribute for 'timestep' and 'multiplier'
    if (!runner.validateUserArguments(arguments(model), user_arguments)) {
      return false;
    }

    // timestep argument value will be object handle
    Handle h = toUUID(runner.getStringArgumentValue("timestep", user_arguments));

    OptionalWorkspaceObject wo = model.getObject(h);
    if (!wo) {
      std::stringstream ss;
      ss << "Object " << toString(h) << " not found in model.";
      runner.registerError(ss.str());
      return false;
    }

    auto timestep = wo->optionalCast<openstudio::epmodel::Timestep>();
    if (!timestep) {
      std::stringstream ss;
      ss << wo->briefDescription() << " is not a Timestep.";
      runner.registerError(ss.str());
      return false;
    }

    runner.registerValue("timestep_handle", toString(timestep->handle()));
    const int originalValue = timestep->numberOfTimestepsPerHour();

    if (originalValue < 2) {
      std::stringstream ss;
      ss << "This measure only applies when there are at least 2 timesteps per hour. ";
      ss << timestep->briefDescription() << " has " << originalValue << ".";
      runner.registerAsNotApplicable(ss.str());
      return true;
    }

    double multiplier = runner.getDoubleArgumentValue("multiplier", user_arguments);

    if (multiplier < 0.0) {
      std::stringstream ss;
      ss << "The timestep multiplier must be greater than or equal to 0. ";
      ss << "Instead, it is " << toString(multiplier) << ".";
      runner.registerError(ss.str());
      return false;
    }

    int newValue = static_cast<int>(multiplier * originalValue);
    timestep->setNumberOfTimestepsPerHour(newValue);

    // register effects of this measure

    // human-readable
    std::stringstream ss;
    ss << "The timestep count of " << timestep->briefDescription() << " was " << originalValue << ".";
    runner.registerInitialCondition(ss.str());
    ss.str("");
    ss << "The timestep count of " << timestep->briefDescription();
    ss << " has been changed to " << newValue << ".";
    runner.registerFinalCondition(ss.str());
    ss.str("");

    // machine-readable
    runner.registerValue("timesteps_in", "Input Timesteps per Hour", originalValue);
    runner.registerValue("timesteps_out", "Output Timesteps per Hour", newValue);

    return true;
  }
};

TEST_F(MeasureFixture, UserScript_TestModelUserScript2) {
  TestModelUserScript2 script;
  EXPECT_EQ("TestModelUserScript2", script.name());

  openstudio::epmodel::Model model;

  // serialize ossrs
  openstudio::path fileDir = toPath("./OSResultOSSRs");
  openstudio::filesystem::create_directory(fileDir);

  std::vector<WorkflowStep> steps;
  steps.push_back(MeasureStep("dummy"));

  WorkflowJSON workflow;
  workflow.setWorkflowSteps(steps);

  // call with no arguments
  TestOSRunner runner(workflow);
  std::map<std::string, OSArgument> user_arguments;
  bool ok = script.run(model, runner, user_arguments);
  EXPECT_FALSE(ok);
  WorkflowStepResult result = runner.result();
  ASSERT_TRUE(result.stepResult());
  EXPECT_TRUE(result.stepResult()->value() == StepResult::Fail);
  EXPECT_EQ(2u, result.stepErrors().size());  // missing required and defaulted arguments
  EXPECT_EQ(0u, result.stepWarnings().size());
  EXPECT_EQ(0u, result.stepInfo().size());
  EXPECT_FALSE(result.initialCondition());
  EXPECT_FALSE(result.finalCondition());
  EXPECT_TRUE(result.stepValues().empty());

  // call with required argument, but no timestep object in model
  runner.reset();
  auto timestep = addTimestep(model, 6);
  OSArgumentVector definitions = script.arguments(model);
  user_arguments = runner.getUserInput(definitions);
  OSArgument arg = definitions[0];
  arg.setValue(toString(timestep.handle()));
  user_arguments["timestep"] = arg;
  timestep.remove();
  EXPECT_EQ(0u, model.numObjects());
  ok = script.run(model, runner, user_arguments);
  EXPECT_FALSE(ok);
  result = runner.result();
  ASSERT_TRUE(result.stepResult());
  EXPECT_TRUE(result.stepResult()->value() == StepResult::Fail);
  EXPECT_EQ(1u, result.stepErrors().size());  // object not in model
  EXPECT_EQ(0u, result.stepWarnings().size());
  EXPECT_EQ(0u, result.stepInfo().size());
  EXPECT_FALSE(result.initialCondition());
  EXPECT_FALSE(result.finalCondition());
  EXPECT_EQ(2u, result.stepValues().size());  // registers argument values

  // call properly using default multiplier, but timestep object is not applicable
  runner.reset();
  timestep = addTimestep(model, 1);
  definitions = script.arguments(model);
  user_arguments = runner.getUserInput(definitions);
  arg = definitions[0];
  arg.setValue(toString(timestep.handle()));
  user_arguments["timestep"] = arg;
  ok = script.run(model, runner, user_arguments);
  EXPECT_TRUE(ok);
  result = runner.result();
  ASSERT_TRUE(result.stepResult());
  EXPECT_TRUE(result.stepResult()->value() == StepResult::NA);
  EXPECT_EQ(0u, result.stepErrors().size());
  EXPECT_EQ(0u, result.stepWarnings().size());
  EXPECT_EQ(1u, result.stepInfo().size());  // Measure not applicable as called
  EXPECT_FALSE(result.initialCondition());
  EXPECT_FALSE(result.finalCondition());
  EXPECT_EQ(3u, result.stepValues().size());  // Registers argument values and timestep handle, then exits

  // call properly using default multiplier
  runner.reset();
  EXPECT_TRUE(timestep.setNumberOfTimestepsPerHour(10));
  ok = script.run(model, runner, user_arguments);
  EXPECT_TRUE(ok);
  result = runner.result();
  ASSERT_TRUE(result.stepResult());
  EXPECT_TRUE(result.stepResult()->value() == StepResult::Success);
  EXPECT_EQ(0u, result.stepErrors().size());
  EXPECT_EQ(0u, result.stepWarnings().size());
  EXPECT_EQ(0u, result.stepInfo().size());
  EXPECT_TRUE(result.initialCondition());  // describes original state
  EXPECT_TRUE(result.finalCondition());    // describes changes
  EXPECT_EQ(5u, result.stepValues().size());

  EXPECT_EQ(8, timestep.numberOfTimestepsPerHour());

  // call properly using different multiplier
  runner.reset();
  arg = definitions[1];
  arg.setValue(0.5);
  user_arguments["multiplier"] = arg;
  ok = script.run(model, runner, user_arguments);
  EXPECT_TRUE(ok);
  result = runner.result();
  ASSERT_TRUE(result.stepResult());
  EXPECT_TRUE(result.stepResult()->value() == StepResult::Success);
  EXPECT_EQ(0u, result.stepErrors().size());
  EXPECT_EQ(0u, result.stepWarnings().size());
  EXPECT_EQ(0u, result.stepInfo().size());
  EXPECT_TRUE(result.initialCondition());  // describes original state
  EXPECT_TRUE(result.finalCondition());    // describes changes
  EXPECT_EQ(5u, result.stepValues().size());

  EXPECT_EQ(4, timestep.numberOfTimestepsPerHour());
}

TEST_F(MeasureFixture, EPModelMeasureParity_RestoreTypedSpaceMeasureCoverage) {
  ADD_FAILURE() << "Temporary epmodel workflow reminder: UserScript_TestModelUserScript1 was reduced from canonical Space construction/removal "
                   "to generic IDF object mutation so the clean-break workflow target would compile. Restore this test to use epmodel::Space "
                   "once the typed Space creation/removal path is ready to carry the same measure-facing contract as canonical Model.";
}

TEST_F(MeasureFixture, EPModelMeasureParity_ResolveLightsDefinitionAbstraction) {
  ADD_FAILURE() << "Temporary epmodel workflow reminder: UserScript_TestModelUserScript2 used to exercise canonical LightsDefinition, "
                   "makeChoiceArgumentOfWorkspaceObjects, optionalCast<LightsDefinition>, wattsperSpaceFloorArea, quantity, and floorArea. "
                   "The current epmodel test uses a Timestep object only to keep the target compiling. Decide how IDD-backed epmodel should "
                   "represent this canonical load-definition measure pattern, then restore equivalent coverage.";
}

TEST_F(MeasureFixture, RegisterValueNames) {
  WorkflowJSON workflow;
  OSRunner runner(workflow);
  runner.registerValue("value", 0);
  runner.registerValue("ValueTwo", 1);
  runner.registerValue("VALUETHREE", 2);
  runner.registerValue("4ValueFour", 3);
  runner.registerValue("Value<Five>", 4);
  runner.registerValue("#V|a@l#u$e%F^i&v*e(V)a{l}u_e[F]i;v:e'V\"a,l<u.e>F\\i/v?e+V=", 5);
  runner.registerValue("Value&$@$Six", 6);
  runner.registerValue("Value____Seven", 7);
  std::vector<Attribute> attributes = runner.result().attributes();
  ASSERT_EQ(8u, attributes.size());
  EXPECT_EQ("value", attributes[0].name());
  EXPECT_EQ("value_two", attributes[1].name());
  EXPECT_EQ("valuethree", attributes[2].name());
  EXPECT_EQ("_4_value_four", attributes[3].name());
  EXPECT_EQ("value_five", attributes[4].name());
  EXPECT_EQ("v_a_l_u_e_f_i_v_e_v_a_l_u_e_f_i_v_e_v_a_l_u_e_f_i_v_e_v", attributes[5].name());
  EXPECT_EQ("value_six", attributes[6].name());
  EXPECT_EQ("value_seven", attributes[7].name());
}

class TestModelUserScriptDomain : public ModelMeasure
{
 public:
  virtual std::string name() const override {
    return "TestModelUserScriptDomain";
  }

  virtual std::vector<OSArgument> arguments(const openstudio::epmodel::Model& model) const override {
    std::vector<OSArgument> result;

    OSArgument arg = OSArgument::makeDoubleArgument("double_arg", true);
    arg.setMaxValue(10.0);
    result.push_back(arg);

    arg = OSArgument::makeIntegerArgument("int_arg", true);
    arg.setMinValue(0);
    result.push_back(arg);

    return result;
  }

  virtual bool run(openstudio::epmodel::Model& model, OSRunner& runner, const std::map<std::string, OSArgument>& user_arguments) const override {
    ModelMeasure::run(model, runner, user_arguments);  // initializes runner

    if (!runner.validateUserArguments(arguments(model), user_arguments)) {
      return false;
    }

    return true;
  }
};

TEST_F(MeasureFixture, UserScript_TestModelUserScriptDomain) {
  TestModelUserScriptDomain script;
  EXPECT_EQ("TestModelUserScriptDomain", script.name());

  openstudio::epmodel::Model model;

  std::vector<WorkflowStep> steps;
  steps.push_back(MeasureStep("dummy"));

  WorkflowJSON workflow;
  workflow.setWorkflowSteps(steps);

  TestOSRunner runner(workflow);
  OSArgumentVector definitions = script.arguments(model);
  std::map<std::string, OSArgument> user_arguments = runner.getUserInput(definitions);
  ASSERT_EQ(2, user_arguments.size());

  OSArgument& double_arg = user_arguments["double_arg"];
  OSArgument& int_arg = user_arguments["int_arg"];

  // call with a good value
  double_arg.setValue(-1.0);
  int_arg.setValue(1.0);
  EXPECT_TRUE(script.run(model, runner, user_arguments));
  WorkflowStepResult result = runner.result();
  ASSERT_TRUE(result.stepResult());
  EXPECT_EQ(StepResult::Success, result.stepResult()->value());
  EXPECT_EQ(0u, result.stepErrors().size());
  EXPECT_EQ(0u, result.stepWarnings().size());

  // Out of bound value for double_arg
  runner.reset();
  double_arg.setValue(100.0);
  EXPECT_FALSE(script.run(model, runner, user_arguments));
  result = runner.result();
  ASSERT_TRUE(result.stepResult());
  EXPECT_EQ(StepResult::Fail, result.stepResult()->value());
  ASSERT_EQ(1u, result.stepErrors().size());
  EXPECT_EQ(
    fmt::format("Double User argument 'double_arg' has a value '100' that is not in the domain [{}, 10].", std::numeric_limits<double>::lowest()),
    result.stepErrors()[0]);
  EXPECT_EQ(0u, result.stepWarnings().size());

  // Out of bound value for int_arg
  runner.reset();
  double_arg.setValue(1.0);
  int_arg.setValue(-3);
  EXPECT_FALSE(script.run(model, runner, user_arguments));
  result = runner.result();
  ASSERT_TRUE(result.stepResult());
  EXPECT_EQ(StepResult::Fail, result.stepResult()->value());
  ASSERT_EQ(1u, result.stepErrors().size());
  EXPECT_EQ("Integer User argument 'int_arg' has a value '-3' that is not in the domain [0, 2147483647].", result.stepErrors()[0]);
  EXPECT_EQ(0u, result.stepWarnings().size());
}

// Test for #5464 - Shouldn't throw an error when a separator is used in the arguments
class ModelMeasureWithSeparator : public ModelMeasure
{
 public:
  virtual std::string name() const override {
    return "ModelMeasureWithSeparator";
  }

  virtual std::vector<OSArgument> arguments(const openstudio::epmodel::Model& /*model*/) const override {
    std::vector<OSArgument> result;

    OSArgument arg = OSArgument::makeDoubleArgument("double_arg", true);
    arg.setMaxValue(10.0);
    result.push_back(arg);

    arg = OSArgument::makeSeparatorArgument("separator");
    result.push_back(arg);

    arg = OSArgument::makeIntegerArgument("int_arg", true);
    arg.setMinValue(0);
    result.push_back(arg);

    return result;
  }

  virtual bool run(openstudio::epmodel::Model& model, OSRunner& runner, const std::map<std::string, OSArgument>& user_arguments) const override {
    ModelMeasure::run(model, runner, user_arguments);  // initializes runner

    return runner.validateUserArguments(arguments(model), user_arguments);
  }
};

TEST_F(MeasureFixture, ModelMeasureWithSeparator) {
  ModelMeasureWithSeparator measure;
  EXPECT_EQ("ModelMeasureWithSeparator", measure.name());

  openstudio::epmodel::Model model;

  std::vector<WorkflowStep> steps;
  steps.push_back(MeasureStep("dummy"));

  WorkflowJSON workflow;
  workflow.setWorkflowSteps(steps);

  TestOSRunner runner(workflow);
  OSArgumentVector arguments = measure.arguments(model);
  std::map<std::string, OSArgument> argumentMap = convertOSArgumentVectorToMap(arguments);
  ASSERT_EQ(3, argumentMap.size());

  OSArgument& double_arg = argumentMap["double_arg"];
  OSArgument& int_arg = argumentMap["int_arg"];

  StringStreamLogSink sink;
  sink.setLogLevel(Fatal);

  // call with a good value
  double_arg.setValue(-1.0);
  int_arg.setValue(1.0);
  EXPECT_TRUE(measure.run(model, runner, argumentMap));

  EXPECT_EQ(0, sink.logMessages().size()) << sink.string();
  sink.resetStringStream();

  WorkflowStepResult result = runner.result();
  ASSERT_TRUE(result.stepResult());
  EXPECT_EQ(StepResult::Success, result.stepResult()->value());
  EXPECT_EQ(0u, result.stepErrors().size());
  EXPECT_EQ(0u, result.stepWarnings().size());

  // Out of bound value for int_arg
  runner.reset();
  double_arg.setValue(1.0);
  int_arg.setValue(-3);
  EXPECT_FALSE(measure.run(model, runner, argumentMap));

  EXPECT_EQ(0, sink.logMessages().size()) << sink.string();
  sink.resetStringStream();

  result = runner.result();
  ASSERT_TRUE(result.stepResult());
  EXPECT_EQ(StepResult::Fail, result.stepResult()->value());
  ASSERT_EQ(1u, result.stepErrors().size());
  EXPECT_EQ("Integer User argument 'int_arg' has a value '-3' that is not in the domain [0, 2147483647].", result.stepErrors()[0]);
  EXPECT_EQ(0u, result.stepWarnings().size());
}
