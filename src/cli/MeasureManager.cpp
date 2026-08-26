/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "MeasureManager.hpp"
#include "../utilities/bcl/RemoteBCL.hpp"
#include "../utilities/bcl/BCLMeasure.hpp"
#include "../utilities/core/Checksum.hpp"
#include "../utilities/core/Filesystem.hpp"
#include "../utilities/core/FilesystemHelpers.hpp"
#include "../utilities/core/StringHelpers.hpp"
#include "../utilities/time/DateTime.hpp"
#include "../osversion/VersionTranslator.hpp"
#include "../energyplus/ForwardTranslator.hpp"
#include "../utilities/bcl/LocalBCL.hpp"
#include "../utilities/idf/ValidityEnums.hpp"
#include <utilities/idd/IddEnums.hxx>
#include "../measure/OSMeasure.hpp"
#include "../measure/ModelMeasure.hpp"
#include "../measure/EnergyPlusMeasure.hpp"
#include "../measure/ReportingMeasure.hpp"
#include "../measure/OSArgument.hpp"
#include "../measure/OSOutput.hpp"
#include "../measure/OSRunner.hpp"
#include "../measure/OSMeasureInfoGetter.hpp"
#include "../model/Model_Impl.hpp"  // For casting
#include "../../ruby/interpreter/RubyException.hpp"

#include <json/json.h>
#include <fmt/format.h>
#include <httplib.h>
#include <json/value.h>
#include <pugixml.hpp>

#include <sstream>
#include <utility>  // make_pair
#include <cstdio>

namespace openstudio {

namespace {

  std::string toJSONString(const Json::Value& json) {
    Json::StreamWriterBuilder builder;
    builder["indentation"] = "";
    builder["commentStyle"] = "None";
    return Json::writeString(builder, json);
  }

  std::string toJSONString(const std::string& s) {
    return toJSONString(Json::Value(s));
  }

  // This just participates in overload resolution, otherwise it's ambiguous since Json::Value and std::string are constructible from char *
  std::string toJSONString(const char* s) {
    return toJSONString(Json::Value(s));
  }

  Json::Value parseJsonBody(const std::string& body_str) {
    Json::Value result;
    if (!body_str.empty()) {
      Json::CharReaderBuilder reader;
      std::string errs;
      std::istringstream ss(body_str);
      Json::parseFromStream(reader, ss, &result, &errs);
    }
    return result;
  }

  template <typename T>
  boost::optional<T> get_field(const Json::Value& body, const std::string& field_name);

  template <>
  boost::optional<std::string> get_field(const Json::Value& body, const std::string& field_name) {
    if (body.isMember(field_name) && body[field_name].isString()) {
      return body[field_name].asString();
    }
    return boost::none;
  }

  template <>
  boost::optional<openstudio::path> get_field(const Json::Value& body, const std::string& field_name) {
    if (body.isMember(field_name) && body[field_name].isString()) {
      return openstudio::path(body[field_name].asString());
    }
    return boost::none;
  }

  template <>
  [[maybe_unused]] boost::optional<bool> get_field(const Json::Value& body, const std::string& field_name) {
    if (body.isMember(field_name) && body[field_name].isBool()) {
      return body[field_name].asBool();
    }
    return boost::none;
  }

  template <typename T>
  T get_field(const Json::Value& body, const std::string& field_name, const T& defaultValue);

  template <>
  std::string get_field(const Json::Value& body, const std::string& field_name, const std::string& defaultValue) {
    if (body.isMember(field_name) && body[field_name].isString()) {
      return body[field_name].asString();
    }
    return defaultValue;
  }

  template <>
  openstudio::path get_field(const Json::Value& body, const std::string& field_name, const openstudio::path& defaultValue) {
    if (body.isMember(field_name) && body[field_name].isString()) {
      return openstudio::path(body[field_name].asString());
    }
    return defaultValue;
  }

  template <>
  bool get_field(const Json::Value& body, const std::string& field_name, const bool& defaultValue) {
    if (body.isMember(field_name) && body[field_name].isBool()) {
      return body[field_name].asBool();
    }
    return defaultValue;
  }

}  // namespace

MeasureManager::MeasureManager(ScriptEngineInstance& t_rubyEngine, ScriptEngineInstance& t_pythonEngine)
  : rubyEngine(t_rubyEngine), pythonEngine(t_pythonEngine) {
  // rubyEngine->exec("puts 'Hello from ruby'");
  // pythonEngine->exec("print('Hello from python')");
}
//   :
// #if USE_RUBY_ENGINE
//     rubyEngine(t_rubyEngine),
// #endif
// #if USE_PYTHON_ENGINE
//     pythonEngine(t_pythonEngine)
// #endif
// {
// }

Json::Value MeasureManager::internalState() const {
  Json::Value result(Json::objectValue);

  Json::Value osms(Json::arrayValue);
  for (const auto& [k, v] : m_osms) {
    Json::Value osmInfo(Json::objectValue);
    osmInfo["osm_path"] = k.generic_string();
    osmInfo["checksum"] = v.checksum;
    osms.append(std::move(osmInfo));
  }
  result["osms"] = std::move(osms);

  Json::Value idfs(Json::arrayValue);
  for (const auto& [k, v] : m_idfs) {
    Json::Value idfInfo(Json::objectValue);
    idfInfo["idf_path"] = k.generic_string();
    idfInfo["checksum"] = v.checksum;
    idfs.append(std::move(idfInfo));
  }
  result["idfs"] = std::move(idfs);

  // Json::Value measures(Json::arrayValue);
  auto& measures = result["measures"];
  measures = Json::arrayValue;
  for (const auto& [measureDirPath, bclMeasureInfo] : m_measures) {
    Json::Value mInfo(Json::objectValue);
    measures.append(bclMeasureInfo.measure.toJSON());
  }

  auto& measureInfos = result["measure_info"];
  measureInfos = Json::arrayValue;
  // Json::Value measureInfos(Json::arrayValue);
  for (const auto& [measureDirPath, bclMeasureInfo] : m_measures) {
    for (const auto& [osmOrIdfPath, measureInfo] : bclMeasureInfo.measureInfos) {
      Json::Value mInfo(Json::objectValue);
      mInfo["measureDirPath"] = measureDirPath.generic_string();
      mInfo["osm_path"] = osmOrIdfPath.generic_string();
      auto& args = mInfo["arguments"];
      for (const auto& arg : measureInfo.bclMeasureArguments()) {
        args.append(arg.toJSON());
      }

      measureInfos.append(std::move(mInfo));
    }
  }
  // result["measure_info"] = std::move(measureInfos);

  return result;
}

size_t MeasureManager::clearMeasureInfoForOsmorIdfPath(const openstudio::path& osmOrIdfPath) {
  size_t totalRemoved = 0;
  for (auto& [key, value] : m_measures) {
    totalRemoved += value.measureInfos.erase(osmOrIdfPath);
  }
  return totalRemoved;
}

boost::optional<OSMInfo> MeasureManager::getModel(const openstudio::path& osmPath, bool force_reload) {

  if (!openstudio::filesystem::is_regular_file(osmPath)) {
    fmt::print("Model '{}' does not exist\n", osmPath.generic_string());
    m_osms.erase(osmPath);
    clearMeasureInfoForOsmorIdfPath(osmPath);
    return boost::none;
  }

  OSMInfo current;
  current.checksum = openstudio::checksum(osmPath);

  if (!force_reload) {
    auto it = m_osms.find(osmPath);
    if (it != m_osms.end()) {
      auto& cached = it->second;
      if (current.checksum == cached.checksum) {
        fmt::print("Using cached model {}\n", osmPath.generic_string());
        return cached;
      } else {
        fmt::print("Checksum of cached model does not match current checksum for '{}'\n", osmPath.generic_string());
      }
    }
  }

  clearMeasureInfoForOsmorIdfPath(osmPath);

  fmt::print("Attempting to load model '{}'\n", osmPath.generic_string());
  openstudio::osversion::VersionTranslator vt;
  if (auto model_ = vt.loadModel(osmPath)) {
    fmt::print("Successfully loaded model '{}'\n", osmPath.generic_string());
    current.model = std::move(*model_);
    openstudio::energyplus::ForwardTranslator ft;
    current.workspace = ft.translateModel(current.model);
    auto [it, ok] = m_osms.insert_or_assign(osmPath, std::move(current));
    return it->second;
  }

  fmt::print("Failed to load model '{}'\n", osmPath.generic_string());
  m_osms.erase(osmPath);

  return boost::none;
}

boost::optional<IDFInfo> MeasureManager::getIdf(const openstudio::path& idfPath, bool force_reload) {

  if (!openstudio::filesystem::is_regular_file(idfPath)) {
    fmt::print("Idf '{}' does not exist\n", idfPath.generic_string());
    m_idfs.erase(idfPath);
    clearMeasureInfoForOsmorIdfPath(idfPath);
    return boost::none;
  }

  IDFInfo current;
  current.checksum = openstudio::checksum(idfPath);

  if (!force_reload) {
    auto it = m_idfs.find(idfPath);
    if (it != m_idfs.end()) {
      auto& cached = it->second;
      if (current.checksum == cached.checksum) {
        fmt::print("Using cached workspace {}\n", idfPath.generic_string());
        return cached;
      } else {
        fmt::print("Checksum of cached workspace does not match current checksum for '{}'\n", idfPath.generic_string());
      }
    }
  }

  clearMeasureInfoForOsmorIdfPath(idfPath);

  fmt::print("Attempting to load idf '{}'\n", idfPath.generic_string());
  if (auto workspace_ = openstudio::Workspace::load(idfPath, openstudio::IddFileType::EnergyPlus)) {
    fmt::print("Successfully loaded idf '{}'\n", idfPath.generic_string());

    if (workspace_->isValid(openstudio::StrictnessLevel::Draft)) {
      current.workspace = std::move(*workspace_);
      auto [it, ok] = m_idfs.insert_or_assign(idfPath, std::move(current));
      return it->second;
    } else {
      fmt::print("Workspace loaded from '{}' is not valid to Draft StrictnessLevel\n", idfPath.generic_string());
    }
  } else {
    fmt::print("Failed to load idf '{}'\n", idfPath.generic_string());
  }

  m_idfs.erase(idfPath);

  return boost::none;
}

boost::optional<BCLMeasure> MeasureManager::getMeasure(const openstudio::path& measureDirPath, bool force_reload) {

  const auto& measureDirPathStr = measureDirPath.string();

  // check if measure exists on disk
  if (!openstudio::filesystem::is_directory(measureDirPath)) {
    fmt::print("Measure '{}' does not exist.\n", measureDirPathStr);
    m_measures.erase(measureDirPath);
    return boost::none;
  }
  if (!openstudio::filesystem::is_regular_file(measureDirPath / "measure.xml")) {
    fmt::print("Measure directory '{}' exists but does not have a measure.xml.\n", measureDirPathStr);
    m_measures.erase(measureDirPath);
    return boost::none;
  }

  BCLMeasureInfo* measureInfo_ = nullptr;
  if (!force_reload) {
    auto it = m_measures.find(measureDirPath);
    if (it != m_measures.end()) {
      measureInfo_ = &(it->second);
      fmt::print("Using cached measure {}\n", measureDirPath.generic_string());
    }
  }

  if (!measureInfo_) {
    m_measures.erase(measureDirPath);

    // load from disk
    fmt::print("Attempting to load measure '{}'\n", measureDirPathStr);

    boost::optional<BCLMeasure> measure_ = openstudio::BCLMeasure::load(measureDirPath);

    if (!measure_) {
      fmt::print("Failed to load measure '{}'\n", measureDirPathStr);
      return boost::none;
    }
    fmt::print("Successfully loaded measure '{}'\n", measureDirPathStr);
    auto [it, ok] = m_measures.insert({measureDirPath, BCLMeasureInfo{std::move(*measure_)}});
    measureInfo_ = &(it->second);
  }

  auto& measure = measureInfo_->measure;

  // see if there are updates, want to make sure to perform both checks so do outside of conditional
  bool file_updates = measure.checkForUpdatesFiles();  // checks if any files have been updated
  bool xml_updates = measure.checkForUpdatesXML();     // only checks if xml as loaded has been changed since last save

  auto readmeInPath = measureDirPath / "README.md.erb";
  auto readmeOutPath = measureDirPath / "README.md";

  const bool hasReadmeIn = openstudio::filesystem::is_regular_file(readmeInPath);
  const bool hasReadmeOut = openstudio::filesystem::is_regular_file(readmeOutPath);
  const bool readme_out_of_date = hasReadmeIn && !hasReadmeOut;

  // TODO: try catch like in measure_manager.rb?
  bool missing_fields = measure.missingRequiredFields();

  if (file_updates || xml_updates || missing_fields || readme_out_of_date) {
    fmt::print("Changes detected, updating '{}'\n", measureDirPathStr);

    // Clear cache before calling getMeasureInfo
    measureInfo_->measureInfos.clear();

    openstudio::measure::OSMeasureInfo info = getMeasureInfo(measureDirPath, measure, openstudio::path{});
    info.update(measure);

    if (hasReadmeIn) {
      if (hasReadmeOut) {
        openstudio::filesystem::remove(readmeOutPath);
      }
      ScriptObject measureInfoBindingObject;
      try {
        measureInfoBindingObject = rubyEngine->eval("OpenStudio::Measure::RubyMeasureInfoBinding.new()");
      } catch (const RubyException& e) {
        auto msg = fmt::format("Failed to instantiate a RubyMeasureInfoBinding: {}\nlocation={}", e.what(), e.location());
        fmt::print(stderr, "{}\n", msg);
        LOG_AND_THROW(msg);
      }
      auto* measureInfoBindingPtr = rubyEngine->getAs<openstudio::measure::MeasureInfoBinding*>(measureInfoBindingObject);
      measureInfoBindingPtr->setMeasureInfo(info);
      const bool result = measureInfoBindingPtr->renderFile(readmeInPath.generic_string());
      if (result) {
        // check for file updates again
        file_updates = measure.checkForUpdatesFiles();
      } else {
        fmt::print(stderr, "Failed to generate the README.md via ERB\n");
      }
    }

    // Save the xml file with changes triggered by checkForUpdatesFiles() / checkForUpdatesXML() above
    measure.save();
  }

  return measure;
}

openstudio::measure::OSMeasureInfo MeasureManager::getMeasureInfo(const openstudio::path& measureDirPath, const BCLMeasure& measure,
                                                                  const openstudio::path& osmOrIdfPath, const boost::optional<model::Model>& model_,
                                                                  const boost::optional<Workspace>& workspace_) {

  if (!m_measures.contains(measureDirPath)) {
    LOG_AND_THROW("Measure isn't recorded in m_measures, that should NOT happen");
  }
  auto& bclMeasureInfo = m_measures.at(measureDirPath);
  auto it2 = bclMeasureInfo.measureInfos.find(osmOrIdfPath);
  if (it2 != bclMeasureInfo.measureInfos.end()) {
    fmt::print("Using cached OSMeasureInfo for '{}', '{}'\n", measureDirPath.generic_string(), osmOrIdfPath.generic_string());
    return it2->second;
  }

  auto scriptPath_ = measure.primaryScriptPath();
  if (!scriptPath_) {
    throw std::runtime_error(
      fmt::format("Unable to locate primary Ruby script path for BCLMeasure '{}' located at '{}'", measure.name(), measureDirPath.generic_string()));
  }

  auto getOrCreateModel = [this, &model_, &osmOrIdfPath]() -> openstudio::model::Model {
    if (model_) {
      // model should already have been cloned in the endpoint, so no need to do it twice
      return *model_;  // _->clone(true).cast<openstudio::model::Model>();
    } else if (!osmOrIdfPath.empty()) {
      // TODO: not sure we want to keep this here or not..
      if (auto osmInfo_ = getModel(osmOrIdfPath)) {
        return osmInfo_->model.clone().cast<openstudio::model::Model>();
      } else {
        LOG_AND_THROW("Failed to load the Model at " << osmOrIdfPath);
      }
    } else {
      return {};
    }
  };

  auto getOrCreateWorkspace = [this, &workspace_, &osmOrIdfPath]() -> openstudio::Workspace {
    if (workspace_) {
      return *workspace_;  // ->clone(true);
    } else if (!osmOrIdfPath.empty()) {
      if (auto idfInfo_ = getIdf(osmOrIdfPath)) {
        return idfInfo_->workspace.clone();
      } else {
        LOG_AND_THROW("Failed to load the Model at " << osmOrIdfPath);
      }
    } else {
      return {openstudio::StrictnessLevel::Draft, openstudio::IddFileType::EnergyPlus};
    }
  };

  ScriptEngineInstance* thisEngine = nullptr;
  const MeasureLanguage measureLanguage = measure.measureLanguage();
  if (measureLanguage == MeasureLanguage::Ruby) {
    thisEngine = &rubyEngine;
  } else if (measureLanguage == MeasureLanguage::Python) {
    thisEngine = &pythonEngine;
  }

  std::string className = (*thisEngine)->inferMeasureClassName(*scriptPath_);
  fmt::print("className={}\n", className);
  if (className.empty()) {
    // TODO: could also just fallback on trusting the BCLXML is up to date with respect to the class name and use BCLMeasure::className()
    auto msg = fmt::format("Failed to infer measure name from '{}'", scriptPath_->generic_string());
    fmt::print(stderr, "{}\n", msg);
    return openstudio::measure::OSMeasureInfo(msg);
  }
  ScriptObject measureScriptObject = (*thisEngine)->loadMeasure(*scriptPath_, className);
  if (measureScriptObject.empty()) {
    auto msg = fmt::format("Failed to load measure '{}' from '{}'\n", className, scriptPath_->generic_string());
    fmt::print(stderr, "{}\n", msg);
    return openstudio::measure::OSMeasureInfo(msg);
  }

  MeasureType measureType;

  std::string name;
  std::string description;
  std::string taxonomy;
  std::string modelerDescription;

  std::vector<measure::OSArgument> arguments;
  std::vector<measure::OSOutput> outputs;

  try {
    auto* osMeasurePtr = (*thisEngine)->getAs<openstudio::measure::OSMeasure*>(measureScriptObject);
    measureType = osMeasurePtr->measureType();
    fmt::print("measureType={}\n", measureType.valueName());

    if (measureType == MeasureType::ModelMeasure) {
      auto* measurePtr = static_cast<openstudio::measure::ModelMeasure*>(osMeasurePtr);
      name = measurePtr->name();
      description = measurePtr->description();
      taxonomy = measurePtr->taxonomy();
      modelerDescription = measurePtr->modeler_description();

      auto model = getOrCreateModel();
      arguments = measurePtr->arguments(model);
      outputs = measurePtr->outputs();

    } else if (measureType == MeasureType::EnergyPlusMeasure) {
      auto* measurePtr = static_cast<openstudio::measure::EnergyPlusMeasure*>(osMeasurePtr);
      name = measurePtr->name();
      description = measurePtr->description();
      taxonomy = measurePtr->taxonomy();
      modelerDescription = measurePtr->modeler_description();

      auto workspace = getOrCreateWorkspace();
      arguments = measurePtr->arguments(workspace);
      outputs = measurePtr->outputs();
    } else if (measureType == MeasureType::ReportingMeasure) {
      auto* measurePtr = static_cast<openstudio::measure::ReportingMeasure*>(osMeasurePtr);
      name = measurePtr->name();
      description = measurePtr->description();
      taxonomy = measurePtr->taxonomy();
      modelerDescription = measurePtr->modeler_description();

      // TODO: for ruby at least, need to try the arity... model was added later, at 3.0.0
      const int numArgs = (*thisEngine)->numberOfArguments(measureScriptObject, "arguments");
      // fmt::print("numArgs={}\n", numArgs);
      if (numArgs == 0) {
        auto msg = fmt::format("Reporting Measure at '{}' is using the old format where the 'arguments' method does not take model. "
                               " Please consider updating this to `def arguments(model)`.",
                               scriptPath_->generic_string());
        fmt::print("{}\n", msg);
        if (measureLanguage == MeasureLanguage::Ruby) {
          auto patchArgumentsCmd = fmt::format(R"ruby(
module {0}Extensions
  def arguments(model)
    super()
  end
end

class {0}
  prepend {0}Extensions # the only change to above: prepend instead of include
end
)ruby",
                                               className);
          rubyEngine->exec(patchArgumentsCmd);
          arguments = measurePtr->arguments(openstudio::model::Model{});
          rubyEngine->exec(fmt::format("Object.send(:remove_const, :{}Extensions)", className));
        } else {
          auto msg =
            fmt::format("Wrong number of parameters for method `arguments`in measure '{}' from '{}'\n", className, scriptPath_->generic_string());
          fmt::print(stderr, "{}\n", msg);
          return openstudio::measure::OSMeasureInfo(msg);
        }
      } else {
        auto model = getOrCreateModel();
        arguments = measurePtr->arguments(model);
      }
      outputs = measurePtr->outputs();

    } else {
      throw std::runtime_error("Unknown");
    }
  } catch (const std::exception& e) {
    auto msg = fmt::format("Failed to query information from measure '{}' from '{}': {}\n", className, scriptPath_->generic_string(), e.what());
    fmt::print(stderr, "{}\n", msg);
    return openstudio::measure::OSMeasureInfo(msg);
  }

  if (name.empty()) {
    name = className;
  }

  if (measureLanguage == MeasureLanguage::Ruby) {
    rubyEngine->exec(fmt::format("Object.send(:remove_const, :{})", className));
  }

  openstudio::measure::OSMeasureInfo info(measureType, className, name, description, taxonomy, modelerDescription, arguments, outputs);
  auto [it, ok] = bclMeasureInfo.measureInfos.insert({osmOrIdfPath, std::move(info)});
  return it->second;
}

void MeasureManager::reset() {
  m_osms.clear();
  m_idfs.clear();
  m_measures.clear();
}

MeasureManagerServer::~MeasureManagerServer() {
  close();
}

MeasureManagerServer::MeasureManagerServer(unsigned port, ScriptEngineInstance& rubyEngine, ScriptEngineInstance& pythonEngine)
  : m_measureManager(rubyEngine, pythonEngine),
    m_url(fmt::format("http://localhost:{}/", port)),
    m_port(port),
    my_measures_dir(openstudio::filesystem::home_path() / "OpenStudio/Measures") {

#if (defined(_WIN32) || defined(_WIN64))
  // localhost May be slower on Windows due to DNS resolution delays: https://github.com/yhirose/cpp-httplib/#performance-note-for-local-connections
  m_host = "127.0.0.1";
#else
  // Works for 127.0.0.1, 0.0.0.0 and localhost on TCP4
  m_host = "127.0.0.1";
#endif

  m_server = std::make_unique<httplib::Server>();
  // Single-threaded pool ensures serial execution — Ruby/Python engines are not thread-safe
  m_server->new_task_queue = [] { return new httplib::ThreadPool(1, 1); };
  m_server->Get(".*", [this](const httplib::Request& req, httplib::Response& res) { handle_get(req, res); });
  m_server->Post(".*", [this](const httplib::Request& req, httplib::Response& res) { handle_post(req, res); });
}

bool MeasureManagerServer::open() {
  return m_server->bind_to_port(m_host, static_cast<int>(m_port));
}

bool MeasureManagerServer::close() {
  m_server->stop();
  return true;
}

void MeasureManagerServer::unknown_endpoint(const httplib::Request& req, httplib::Response& res) {
  res.status = httplib::StatusCode::NotFound_404;
  res.set_content(toJSONString(fmt::format("Error, unknown path '{}'", req.path)), "application/json");
}

void MeasureManagerServer::handle_get(const httplib::Request& req, httplib::Response& res) {
  const std::string& uri = req.path;

  if (uri == "/") {
    handle_request(req, res, Json::Value{}, &MeasureManagerServer::status);
    return;
  }

  // Cpprestsdk has it's own json implementation.....
  if (uri == "/internal_state") {
    handle_request(req, res, Json::Value{}, &MeasureManagerServer::internal_state);
    return;
  }

  unknown_endpoint(req, res);
}

void MeasureManagerServer::handle_post(const httplib::Request& req, httplib::Response& res) {
  const std::string& uri = req.path;

  if (uri == "/reset") {
    handle_request(req, res, Json::Value{}, &MeasureManagerServer::reset);
    return;
  }

  if (uri == "/set") {
    // curl -H "Content-Type: application/json" -X POST  --data '{"my_measures_dir": "/Users/julien/OpenStudio/Measures"}' http://localhost:8090/set
    auto body = parseJsonBody(req.body);
    handle_request(req, res, body, &MeasureManagerServer::set);
    return;
  }

  if (uri == "/download_bcl_measure") {
    auto body = parseJsonBody(req.body);
    handle_request(req, res, body, &MeasureManagerServer::download_bcl_measure);
    return;
  }

  // TODO: for testing only, remove
  if (uri == "/get_model") {
    auto body = parseJsonBody(req.body);
    handle_request(req, res, body, &MeasureManagerServer::get_model);
    return;
  }

  if (uri == "/bcl_measures") {
    handle_request(req, res, Json::Value{}, &MeasureManagerServer::bcl_measures);
    return;
  }

  if (uri == "/update_measures") {
    auto body = parseJsonBody(req.body);
    handle_request(req, res, body, &MeasureManagerServer::update_measures);
    return;
  }

  if (uri == "/compute_arguments") {
    auto body = parseJsonBody(req.body);
    handle_request(req, res, body, &MeasureManagerServer::compute_arguments);
    return;
  }

  if (uri == "/create_measure") {
    auto body = parseJsonBody(req.body);
    handle_request(req, res, body, &MeasureManagerServer::create_measure);
    return;
  }

  if (uri == "/duplicate_measure") {
    auto body = parseJsonBody(req.body);
    handle_request(req, res, body, &MeasureManagerServer::duplicate_measure);
    return;
  }

  unknown_endpoint(req, res);
}

MeasureManagerServer::ResponseType MeasureManagerServer::status([[maybe_unused]] const Json::Value& body) {
  Json::Value result;
  result["status"] = "running";
  result["my_measures_dir"] = my_measures_dir.generic_string();
  return {httplib::StatusCode::OK_200, toJSONString(result)};
}

MeasureManagerServer::ResponseType MeasureManagerServer::internal_state([[maybe_unused]] const Json::Value& body) {
  Json::Value result;
  result["status"] = "running";
  result["my_measures_dir"] = my_measures_dir.generic_string();

  auto internalState = m_measureManager.internalState();
  for (const auto& key : internalState.getMemberNames()) {
    result[key] = internalState[key];
  }

  return {httplib::StatusCode::OK_200, toJSONString(result)};
}

MeasureManagerServer::ResponseType MeasureManagerServer::reset([[maybe_unused]] const Json::Value& body) {
  m_measureManager.reset();
  return {httplib::StatusCode::OK_200, toJSONString("Resetting internal state")};
}

MeasureManagerServer::ResponseType MeasureManagerServer::set(const Json::Value& body) {
  if (auto p_ = get_field<openstudio::path>(body, "my_measures_dir")) {
    if (!openstudio::filesystem::is_directory(*p_)) {
      // Issue an error message
      return {httplib::StatusCode::BadRequest_400,
              toJSONString(fmt::format("Error, my_measures_dir '{}' is a not a valid directory", p_->generic_string()))};
    }
    this->my_measures_dir = std::move(*p_);
    return {httplib::StatusCode::OK_200, toJSONString(Json::Value{})};
  } else {
    return {httplib::StatusCode::BadRequest_400, toJSONString("Missing the my_measures_dir in the post data")};
  }
}

MeasureManagerServer::ResponseType MeasureManagerServer::download_bcl_measure(const Json::Value& body) {  // NOLINT
  if (auto uid_ = get_field<std::string>(body, "uid")) {
    const RemoteBCL r;
    if (auto bclMeasure_ = r.getMeasure(*uid_)) {
      return {httplib::StatusCode::OK_200, toJSONString(bclMeasure_->toJSON())};
    } else {
      return {httplib::StatusCode::BadRequest_400, toJSONString(fmt::format("Cannot find measure with uid='{}'", *uid_))};
    }
  } else {
    fmt::print("Missing the uid in the post data\n");
    return {httplib::StatusCode::BadRequest_400, toJSONString("Missing the uid in the post data")};
  }
}

MeasureManagerServer::ResponseType MeasureManagerServer::get_model(const Json::Value& body) {
  if (auto osmPath_ = get_field<openstudio::path>(body, "osm_path")) {
    auto osmInfo_ = m_measureManager.getModel(*osmPath_);
    if (osmInfo_) {
      return {httplib::StatusCode::OK_200, toJSONString(fmt::format("OK, loaded model with checksum {}", osmInfo_->checksum))};
    } else {
      return {httplib::StatusCode::BadRequest_400, toJSONString(fmt::format("Wrong osm path: '{}'", osmPath_->generic_string()))};
    }
  } else {
    return {httplib::StatusCode::BadRequest_400, toJSONString("The 'osm_path' (string/path) must be in the post data")};
  }
}

MeasureManagerServer::ResponseType MeasureManagerServer::bcl_measures([[maybe_unused]] const Json::Value& body) {
  const bool force_reload = false;  // Not supposed to mess with the BCL Measures!
  auto& localBCL = openstudio::LocalBCL::instance();
  Json::Value result(Json::arrayValue);
  for (auto& measure : localBCL.measures()) {
    auto measureDir = measure.directory();
    if (boost::optional<BCLMeasure> measure_ = m_measureManager.getMeasure(measureDir, force_reload)) {
      result.append(measure_->toJSON());
    } else {
      fmt::print("Directory '{}' is not a measure\n", measureDir.generic_string());
    }
  }

  return {httplib::StatusCode::OK_200, toJSONString(result)};
}

MeasureManagerServer::ResponseType MeasureManagerServer::update_measures(const Json::Value& body) {
  auto measuresDir = get_field<openstudio::path>(body, "measures_dir", my_measures_dir);
  const bool force_reload = get_field<bool>(body, "force_reload", false);

  // Scan the directory for measures
  Json::Value result(Json::arrayValue);
  for (const auto& dirEnt : openstudio::filesystem::directory_iterator{measuresDir}) {
    if (openstudio::filesystem::is_directory(dirEnt)) {
      const auto& measureDir = dirEnt.path();
      if (boost::optional<BCLMeasure> measure_ = m_measureManager.getMeasure(measureDir, force_reload)) {
        result.append(measure_->toJSON());
      } else {
        fmt::print("Directory '{}' is not a measure\n", measureDir.generic_string());
      }
    }
  }

  return {httplib::StatusCode::OK_200, toJSONString(result)};
}

MeasureManagerServer::ResponseType MeasureManagerServer::compute_arguments(const Json::Value& body) {
  openstudio::path measureDir;
  if (boost::optional<openstudio::path> p_ = get_field<openstudio::path>(body, "measure_dir")) {  // Not passing a default value => optional
    measureDir = std::move(*p_);
  } else {
    return {httplib::StatusCode::BadRequest_400, toJSONString("The 'measure_dir' (string) must be in the post data")};
  }

  // NOTE: this endpoint expects an OSM (even if it's an EnergyPlusMeasure), NOT an OSM or IDF like the CLI --compute_arguments flag does
  const openstudio::path osmPath = get_field<openstudio::path>(body, "osm_path", {});  // defaults to an empty path
  bool has_valid_osm_path = false;
  if (!osmPath.empty()) {
    if (osmPath.extension() != ".osm") {
      auto msg =
        fmt::format("For /compute_arguments endpoint, parameter 'osm_path' must always be an '.osm' file, not '{}'", osmPath.generic_string());
      fmt::print(stderr, "{}\n", msg);
      return {httplib::StatusCode::BadRequest_400, toJSONString(msg)};
    }
    has_valid_osm_path = true;
  }

  const bool force_reload = get_field<bool>(body, "force_reload", false);

  auto measure_ = m_measureManager.getMeasure(measureDir, force_reload);
  if (!measure_) {
    auto msg = fmt::format("Cannot load measure at '{}'", measureDir.generic_string());
    fmt::print(stderr, "{}\n", msg);
    return {httplib::StatusCode::BadRequest_400, toJSONString(msg)};
  }

  boost::optional<model::Model> model_;
  boost::optional<Workspace> workspace_;

  if (has_valid_osm_path) {
    if (auto osmInfo_ = m_measureManager.getModel(osmPath, force_reload)) {
      // Clone and keep handles
      model_ = osmInfo_->model.clone(true).cast<openstudio::model::Model>();
      workspace_ = osmInfo_->workspace.clone(true);
    } else {
      auto msg = fmt::format("Cannot load model at '{}'", osmPath.generic_string());
      fmt::print(stderr, "{}\n", msg);
      return {httplib::StatusCode::BadRequest_400, toJSONString(msg)};
    }
  }

  const openstudio::measure::OSMeasureInfo info = m_measureManager.getMeasureInfo(measureDir, *measure_, osmPath, model_, workspace_);
  if (auto errorString_ = info.error()) {
    return {httplib::StatusCode::OK_200, toJSONString(*errorString_)};
  }

  // TODO: maybe I should write an OSMeasureInfo::toJSON() method, but that'd be duplicating the code in BCLMeasure (BCLXML to be exact).
  // So since the only thing that's different is the OSArgument (OSMeasureInfo) versus BCLMeasureArgument (BCLMeasure), we just override
  auto result = measure_->toJSON();
  if (has_valid_osm_path) {
    auto& arguments = result["arguments"];
    arguments.clear();
    for (const measure::OSArgument& argument : info.arguments()) {
      arguments.append(argument.toJSON());
    }
  }

  return {httplib::StatusCode::OK_200, toJSONString(result)};
}

MeasureManagerServer::ResponseType MeasureManagerServer::create_measure(const Json::Value& body) {
  static const std::array<std::string, 7> requiredParams = {
    "measure_dir", "display_name", "class_name", "taxonomy_tag", "measure_type", "description", "modeler_description",
  };
  for (const auto& requiredParam : requiredParams) {
    if (!body.isMember(requiredParam) || !body[requiredParam].isString()) {
      auto msg = fmt::format("The '{}' (string) must be in the post data.", requiredParam);
      fmt::print("{}\n", msg);
      return {httplib::StatusCode::BadRequest_400, toJSONString(msg)};
    }
  }

  MeasureType measureType = MeasureType::ModelMeasure;
  auto measureTypeString = get_field<std::string>(body, "measure_type", "ModelMeasure");
  try {
    measureType = MeasureType(measureTypeString);
  } catch (const std::exception& e) {
    auto msg = fmt::format("Couldn't convert '{}' to a MeasureType: {}", measureTypeString, e.what());
    fmt::print("{}\n", msg);
    return {httplib::StatusCode::BadRequest_400, toJSONString(msg)};
  }

  MeasureLanguage measureLanguage = MeasureLanguage::Ruby;
  if (auto measureLanguageString_ = get_field<std::string>(body, "measure_language")) {
    try {
      measureLanguage = MeasureLanguage(*measureLanguageString_);
    } catch (const std::exception& e) {
      auto msg = fmt::format("Couldn't convert '{}' to a MeasureLanguage: {}", *measureLanguageString_, e.what());
      fmt::print("{}\n", msg);
      return {httplib::StatusCode::BadRequest_400, toJSONString(msg)};
    }
  }

  const openstudio::path measureDir = get_field<openstudio::path>(body, "measure_dir", "");
  // This is throwy when the directory already exists
  if (openstudio::filesystem::is_directory(measureDir)) {
    auto msg = fmt::format("The directory already exists at '{}'.", measureDir.generic_string());
    fmt::print("{}\n", msg);
    return {httplib::StatusCode::BadRequest_400, toJSONString(msg)};
  }
  const BCLMeasure measure(get_field<std::string>(body, "display_name", "DisplayName"), get_field<std::string>(body, "class_name", "ClassName"),
                           measureDir, get_field<std::string>(body, "taxonomy_tag", "taxonomy.tag"), measureType,
                           get_field<std::string>(body, "description", "Description"),
                           get_field<std::string>(body, "modeler_description", "ModelerDescription"), measureLanguage);

  if (boost::optional<BCLMeasure> measure_ = m_measureManager.getMeasure(measureDir, true)) {
    return {httplib::StatusCode::OK_200, toJSONString(measure_->toJSON())};
  } else {
    fmt::print("Failed to update measure after creation, this shouldn't happen.");
    return {httplib::StatusCode::BadRequest_400, toJSONString(measure.toJSON())};
  }
}

MeasureManagerServer::ResponseType MeasureManagerServer::duplicate_measure(const Json::Value& body) {
  // Required parameters:
  openstudio::path oldMeasureDir;
  if (auto oldMeasureDir_ = get_field<openstudio::path>(body, "old_measure_dir")) {
    oldMeasureDir = std::move(*oldMeasureDir_);
  } else {
    return {httplib::StatusCode::BadRequest_400, toJSONString("The 'old_measure_dir' (string) must be in the post data")};
  }

  openstudio::path newMeasureDir;
  if (auto newMeasureDir_ = get_field<openstudio::path>(body, "measure_dir")) {
    newMeasureDir = std::move(*newMeasureDir_);
  } else {
    return {httplib::StatusCode::BadRequest_400, toJSONString("The 'measure_dir' (string) must be in the post data")};
  }

  const bool force_reload = get_field<bool>(body, "force_reload", false);

  boost::optional<BCLMeasure> oldMeasure_ = m_measureManager.getMeasure(oldMeasureDir, force_reload);
  if (!oldMeasure_) {
    auto msg = fmt::format("Cannot load measure at '{}'.", oldMeasureDir.generic_string());
    fmt::print("{}\n", msg);
    return {httplib::StatusCode::BadRequest_400, toJSONString(msg)};
  }

  auto& oldMeasure = *oldMeasure_;

  auto newMeasure_ = oldMeasure.clone(newMeasureDir);
  if (!newMeasure_) {
    auto msg = fmt::format("Cannot copy measure from '{}' to {}'", oldMeasureDir.generic_string(), newMeasureDir.generic_string());
    fmt::print("{}\n", msg);
    return {httplib::StatusCode::BadRequest_400, toJSONString(msg)};
  }
  auto& newMeasure = *newMeasure_;
  // Force updating the UID
  newMeasure.changeUID();
  newMeasure.incrementVersionId();

  if (auto val_ = get_field<std::string>(body, "display_name")) {
    newMeasure.setDisplayName(*val_);
  }
  if (auto val_ = get_field<std::string>(body, "class_name")) {
    newMeasure.setName(openstudio::toUnderscoreCase(*val_));
    newMeasure.setClassName(*val_);
  }
  if (auto val_ = get_field<std::string>(body, "taxonomy_tag")) {
    newMeasure.setTaxonomyTag(*val_);
  }

  // Changing the measure Language is not supported!
  auto newMeasureLanguage = oldMeasure.measureLanguage();
  // if (body.has_field("measure_language") && body.at("measure_language").is_string()) {
  //   auto measureLanguageString = body.at("measure_type").as_string();
  //   try {
  //     newMeasureLanguage = MeasureLanguage(measureLanguageString);
  //     newMeasure.setMeasureLanguage(measureLanguage);
  //   } catch (...) {
  //     fmt::print("Couldn't convert '{}' to a MeasureLanguage", measureLanguageString);
  //   }
  // }

  // Changing the measure Type should maybe not be supported either, the method signatures will be wrong and it might be missing
  // energyPlusOutputRequests
  auto newMeasureType = oldMeasure.measureType();
  if (auto measureTypeString_ = get_field<std::string>(body, "measure_type")) {
    try {
      newMeasureType = MeasureType(*measureTypeString_);
      newMeasure.setMeasureType(newMeasureType);
    } catch (...) {
      fmt::print("Couldn't convert '{}' to a MeasureType", *measureTypeString_);
    }
  }

  if (auto val_ = get_field<std::string>(body, "description")) {
    newMeasure.setDescription(*val_);
  }

  if (auto val_ = get_field<std::string>(body, "modeler_description")) {
    newMeasure.setModelerDescription(*val_);
  }

  newMeasure.updateMeasureScript(oldMeasure.measureType(), newMeasureType, oldMeasure.measureLanguage(), newMeasureLanguage, oldMeasure.className(),
                                 newMeasure.className(), newMeasure.displayName(), newMeasure.description(), newMeasure.modelerDescription());
  newMeasure.updateMeasureTests(oldMeasure.className(), newMeasure.className());

  fmt::print("Cloned the {} {} with class name '{}' from '{}' to '{}'\n", oldMeasure.measureLanguage().valueName(),
             oldMeasure.measureType().valueName(), oldMeasure.className(),
             openstudio::toString(openstudio::filesystem::canonical(oldMeasure.directory())),
             openstudio::toString(openstudio::filesystem::canonical(newMeasure.directory())));

  newMeasure.checkForUpdatesFiles();
  newMeasure.checkForUpdatesXML();
  newMeasure.save();

  if (boost::optional<BCLMeasure> measure_ = m_measureManager.getMeasure(newMeasureDir, true)) {
    return {httplib::StatusCode::OK_200, toJSONString(measure_->toJSON())};
  } else {
    fmt::print("Failed to update measure after duplication, this shouldn't happen.");
    return {httplib::StatusCode::BadRequest_400, toJSONString(newMeasure.toJSON())};
  }
}

void MeasureManagerServer::handle_request(const httplib::Request& req, httplib::Response& res, const Json::Value& body,
                                          memRequestHandlerFunPtr request_handler) {

  int status_code = httplib::StatusCode::Created_201;
  try {
    auto result = (this->*request_handler)(body);
    status_code = result.status_code;
    res.status = status_code;
    res.set_content(result.body, "application/json");
  } catch (const std::exception& e) {
    constexpr auto msg = "MeasureManager Server encountered an error:\n\"{}\"\n";
    fmt::print(msg, e.what());
    status_code = httplib::StatusCode::InternalServerError_500;
    res.status = status_code;
    res.set_content(fmt::format(msg, e.what()), "text/plain");
  }
}

void MeasureManagerServer::do_tasks_forever() {
  fmt::print("MeasureManager Ready\n");
  fmt::print("Accepting requests on: {}\n", m_url);
  std::fflush(stdout);

  // Print the request to the console (stdout if Ok, stderr otherwise)
  // [2024-11-14T10:21:46+01:00] "POST /reset HTTP/1.1" 200 (OK)
  // [2024-11-14T10:22:09+01:00] "GET /dsd HTTP/1.1" 404 (Not Found)
  m_server->set_logger([](const httplib::Request& req, const httplib::Response& res) {
    fmt::print(res.status == httplib::StatusCode::OK_200 ? stdout : stderr, "[{}] \"{} {} {}\" {} ({})\n",
               openstudio::DateTime::now().toXsdDateTime(), req.method, req.path, req.version, res.status, httplib::status_message(res.status));
  });
  m_server->set_error_logger([](const httplib::Error& err, const httplib::Request* req) {
    if (req) {
      fmt::print(stderr, "error_logger: [{}] \"{} {} {}\" {} ({})\n", openstudio::DateTime::now().toXsdDateTime(), req->method, req->path,
                 req->version, static_cast<int>(err), httplib::to_string(err));
    } else {
      fmt::print(stderr, "[{}] MeasureManager Server encountered an error: {} ({})\n", openstudio::DateTime::now().toXsdDateTime(),
                 static_cast<int>(err), httplib::to_string(err));
    }
  });

  m_server->listen_after_bind();
}

}  // namespace openstudio
