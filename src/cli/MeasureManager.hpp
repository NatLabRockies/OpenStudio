/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef MEASUREMANAGER_H
#define MEASUREMANAGER_H

#include "../utilities/core/Logger.hpp"
#include "../utilities/core/Path.hpp"
#include "../utilities/core/ThreadSafeDeque.hpp"
#include "../scriptengine/ScriptEngine.hpp"

#include "../model/Model.hpp"
#include "../utilities/idf/Workspace.hpp"
#include "../measure/OSMeasureInfoGetter.hpp"
#include "../utilities/bcl/BCLMeasure.hpp"

#include <httplib.h>

#include <future>
#include <map>
#include <string>
#include <thread>

namespace Json {
class Value;
}

namespace openstudio {

struct OSMInfo
{
  std::string checksum;
  openstudio::model::Model model;
  openstudio::Workspace workspace;
};

struct IDFInfo
{
  std::string checksum;
  openstudio::Workspace workspace;
};

struct BCLMeasureInfo
{
  explicit BCLMeasureInfo(openstudio::BCLMeasure t_measure) : measure(std::move(t_measure)) {}
  openstudio::BCLMeasure measure;
  // Map of osmPath to measureInfo
  std::map<openstudio::path, openstudio::measure::OSMeasureInfo> measureInfos;
};

class MeasureManager
{
 public:
  MeasureManager(ScriptEngineInstance& t_rubyEngine, ScriptEngineInstance& t_pythonEngine);

  boost::optional<OSMInfo> getModel(const openstudio::path& osmPath, bool force_reload = false);
  boost::optional<IDFInfo> getIdf(const openstudio::path& idfPath, bool force_reload = false);
  boost::optional<BCLMeasure> getMeasure(const openstudio::path& measureDirPath, bool force_reload = false);
  openstudio::measure::OSMeasureInfo getMeasureInfo(const openstudio::path& measureDirPath, const BCLMeasure& measure,
                                                    const openstudio::path& osmOrIdfPath = "",
                                                    const boost::optional<model::Model>& model_ = boost::none,
                                                    const boost::optional<Workspace>& workspace_ = boost::none);

  //  boost::optional<openstudio::measure::OSMeasureInfo> getMeasureInfo(const openstudio::path& measureDirPath, const openstudio::BCLMeasure& measure,
  //                                                                     const boost::optional<model::Model>& model,
  //                                                                     const boost::optional<Workspace>& workspace);

  // getMeasureInfo;
  // computeArguments
  // getMeasureHash;
  Json::Value internalState() const;

  std::size_t clearMeasureInfoForOsmorIdfPath(const openstudio::path& osmOrIdfPath);

  void reset();

 private:
  REGISTER_LOGGER("MeasureManager");
  //#if USE_RUBY_ENGINE
  ScriptEngineInstance& rubyEngine;
  //#endif
  //#if USE_PYTHON_ENGINE
  ScriptEngineInstance& pythonEngine;
  //#endif

  std::map<openstudio::path, OSMInfo> m_osms;
  std::map<openstudio::path, IDFInfo> m_idfs;
  std::map<openstudio::path, BCLMeasureInfo> m_measures;
};

class MeasureManagerServer
{
 public:
  explicit MeasureManagerServer(unsigned port, ScriptEngineInstance& rubyEngine, ScriptEngineInstance& pythonEngine);

  bool open();
  bool close();
  void do_tasks_forever();

 protected:
 private:
  struct ResponseType
  {
    int status_code;
    std::string body;
  };

  // Request handlers
  ResponseType status(const Json::Value& body);
  ResponseType internal_state(const Json::Value& body);
  ResponseType reset(const Json::Value& body);
  ResponseType set(const Json::Value& body);
  ResponseType download_bcl_measure(const Json::Value& body);
  ResponseType get_model(const Json::Value& body);
  ResponseType bcl_measures(const Json::Value& body);
  ResponseType compute_arguments(const Json::Value& body);
  ResponseType create_measure(const Json::Value& body);
  ResponseType duplicate_measure(const Json::Value& body);
  ResponseType update_measures(const Json::Value& body);

  // Generally request handler, to ensure the work is done on the main thread.
  // See commit message at https://github.com/NREL/OpenStudio/commit/3c4a1c32fd096ca183c5668e2aafe99ac6564fb4#diff-9785c162dbb96e5fdead1b101c7a2d639460e0bdb0d95c8ff21be7a451a8f377
  using memRequestHandlerFunPtr = ResponseType (MeasureManagerServer::*)(const Json::Value& body);
  void handle_request(const httplib::Request& req, httplib::Response& res, const Json::Value& body, memRequestHandlerFunPtr request_handler);

  void handle_get(const httplib::Request& req, httplib::Response& res);
  void handle_post(const httplib::Request& req, httplib::Response& res);

  // Helper to return a 404 error
  static void unknown_endpoint(const httplib::Request& req, httplib::Response& res);

  // Print the request to the console (stdout if Ok, stderr otherwise)
  // [2024-11-14T10:21:46+01:00] "POST /reset HTTP/1.1" 200
  // [2024-11-14T10:22:09+01:00] "GET /dsd HTTP/1.1" 400
  static void print_feedback(const httplib::Request& req, int status_code);

  MeasureManager m_measureManager;
  httplib::Server m_server;
  std::thread m_serverThread;
  ThreadSafeDeque<std::packaged_task<ResponseType()>> tasks;

  std::string m_url;
  unsigned m_port;
  std::string m_host;
  openstudio::path my_measures_dir;
};

}  // namespace openstudio

#endif  // MEASUREMANAGER_H
