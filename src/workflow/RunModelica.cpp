/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OSWorkflow.hpp"
#include "../utilities/core/ApplicationPathHelpers.hpp"
#include "../utilities/core/Filesystem.hpp"
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <boost/process.hpp>
#include <fstream>
#include <thread>
#include <set>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string_view>
#include <vector>
#include <optional>

namespace openstudio {

REGISTER_LOGGER("openstudio.workflow.RunModelica");

namespace {
  // The Modelica compilers print lightweight XML-ish tags in their stdout to signal structured events.
  // Current tags:
  //   <Modelica-Error> ... </Modelica-Error>    Fatal errors detected while setting parameters or running simulate().
  //   <Modelica-Warn> ... </Modelica-Warn>      Non-fatal issues (eg, setParameterValue failure).
  //   <Modelica-ResultFile>path</Modelica-ResultFile>  Absolute result-file path when a run succeeds.
  // Each payload may span multiple lines; the parser below preserves newlines and trims outer whitespace before logging.
  // The reader loop feeds compiler stdout/stderr through parseModelicaTaggedOutput and logs the structured messages,
  // keeping raw stdout/stderr logs intact for debugging while still surfacing key events in OpenStudio logs.
  struct ModelicaCompilerOutput
  {
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
    std::optional<std::string> simulationResultFile;

    bool empty() const {
      return errors.empty() && warnings.empty() && !simulationResultFile.has_value();
    }
  };

  struct ModelicaTagParserState
  {
    bool collecting = false;
    bool needsNewline = false;
    std::string activeTag;
    std::string closingTag;
    std::string buffer;
  };

  std::string trimTagPayload(std::string_view view) {
    const auto start = view.find_first_not_of(" \t\r\n");
    if (start == std::string_view::npos) {
      return {};
    }
    const auto end = view.find_last_not_of(" \t\r\n");
    return std::string(view.substr(start, end - start + 1));
  }

  void recordCompilerSegment(const std::string& tag, std::string payload, ModelicaCompilerOutput& output) {
    auto message = trimTagPayload(payload);
    if (message.empty()) {
      message = std::move(payload);
    }
    if (tag == "Modelica-Error") {
      output.errors.push_back(std::move(message));
    } else if (tag == "Modelica-Warn") {
      output.warnings.push_back(std::move(message));
    } else if (tag == "Modelica-Simulation-ResultFile") {
      output.simulationResultFile = std::move(message);
    }
  }

  constexpr const char* kWorkflowLogChannel = "openstudio.workflow.OSWorkflow";

  void logCompilerOutput(const ModelicaCompilerOutput& output, bool echoingStdout) {
    if (!echoingStdout) {
      for (const auto& err : output.errors) {
        LOG_FREE(Error, kWorkflowLogChannel, "Modelica compiler reported error: " << err);
      }
      for (const auto& warn : output.warnings) {
        LOG_FREE(Warn, kWorkflowLogChannel, "Modelica compiler reported warning: " << warn);
      }
      if (output.simulationResultFile) {
        LOG_FREE(Info, kWorkflowLogChannel, "Modelica compiler produced simulation result file: " << *output.simulationResultFile);
      }
    }
  }

  ModelicaCompilerOutput parseModelicaTaggedOutput(std::string_view text, ModelicaTagParserState& state) {
    ModelicaCompilerOutput output;

    auto flushActiveTag = [&](const std::string& finalChunk) {
      if (!finalChunk.empty()) {
        if (!state.buffer.empty()) {
          state.buffer.append(finalChunk);
        } else {
          state.buffer = finalChunk;
        }
      }
      recordCompilerSegment(state.activeTag, state.buffer, output);
      state.collecting = false;
      state.needsNewline = false;
      state.activeTag.clear();
      state.closingTag.clear();
      state.buffer.clear();
    };

    size_t cursor = 0;
    while (cursor < text.size()) {
      if (state.collecting) {
        if (state.needsNewline && !state.buffer.empty()) {
          state.buffer.push_back('\n');
        }
        state.needsNewline = false;

        const auto closingPos = text.find(state.closingTag, cursor);
        if (closingPos == std::string::npos) {
          if (cursor < text.size()) {
            state.buffer.append(text.substr(cursor));
          }
          state.needsNewline = true;
          cursor = text.size();
          break;
        }

        if (closingPos > cursor) {
          state.buffer.append(text.substr(cursor, closingPos - cursor));
        }
        const size_t closingTagLen = state.closingTag.size();
        flushActiveTag({});
        cursor = closingPos + closingTagLen;
        continue;
      }

      const auto startPos = text.find('<', cursor);
      if (startPos == std::string::npos) {
        break;
      }
      const auto closePos = text.find('>', startPos);
      if (closePos == std::string::npos) {
        break;
      }

      auto tagNameView = text.substr(startPos + 1, closePos - startPos - 1);
      if (tagNameView.empty() || tagNameView.front() == '/') {
        cursor = closePos + 1;
        continue;
      }

      std::string tagName(tagNameView);
      std::string closingTag = "</" + tagName + ">";
      const size_t payloadStart = closePos + 1;
      const auto closingPos = text.find(closingTag, payloadStart);
      if (closingPos == std::string::npos) {
        state.collecting = true;
        state.activeTag = std::move(tagName);
        state.closingTag = std::move(closingTag);
        state.buffer.assign(text.substr(payloadStart));
        state.needsNewline = true;
        break;
      }

      std::string payload(text.substr(payloadStart, closingPos - payloadStart));
      recordCompilerSegment(tagName, std::move(payload), output);
      cursor = closingPos + closingTag.size();
    }

    return output;
  }

  ModelicaCompilerOutput finalizeModelicaTaggedOutput(ModelicaTagParserState& state) {
    ModelicaCompilerOutput output;
    if (state.collecting && !state.buffer.empty()) {
      recordCompilerSegment(state.activeTag, state.buffer, output);
    }
    state.collecting = false;
    state.needsNewline = false;
    state.activeTag.clear();
    state.closingTag.clear();
    state.buffer.clear();
    return output;
  }

  struct ModelicaSetup
  {
    std::vector<openstudio::path> files;
    std::vector<openstudio::path> searchPaths;
  };

  std::string_view compilerDisplayName(ModelicaCompilerType type) {
    switch (type) {
      case ModelicaCompilerType::OpenModelica:
        return "OpenModelica";
      case ModelicaCompilerType::Dymola:
        return "Dymola";
    }
    return "";
  }

  std::string modelicaStringLiteral(std::string_view raw) {
    std::string escaped;
    escaped.reserve(raw.size() * 2);
    for (const char ch : raw) {
      if (ch == '\\' || ch == '"') {
        escaped.push_back('\\');
      }
      escaped.push_back(ch);
    }
    return fmt::format("\"{}\"", escaped);
  }

  std::vector<openstudio::path> getModelicaPathEnvEntries() {
    std::vector<openstudio::path> result;
    const char* raw = std::getenv("MODELICAPATH");  // NOLINT
    if (!raw) {
      return result;
    }

#ifdef _WIN32
    constexpr char separator = ';';
#else
    constexpr char separator = ':';
#endif

    std::string pathList(raw);
    std::stringstream ss(pathList);
    std::string token;
    while (std::getline(ss, token, separator)) {
      if (token.empty()) {
        continue;
      }
      result.emplace_back(openstudio::toPath(token));
    }
    return result;
  }

  void dedupePaths(std::vector<openstudio::path>& paths) {
    std::set<std::string> seen;
    std::vector<openstudio::path> unique;
    unique.reserve(paths.size());

    for (const auto& path : paths) {
      if (path.empty()) {
        continue;
      }
      const auto absolutePath = boost::filesystem::absolute(path);
      const std::string& key = absolutePath.generic_string();
      if (seen.insert(key).second) {
        unique.push_back(absolutePath);
      }
    }

    paths = std::move(unique);
  }

  ModelicaSetup getModelicaSetup(const WorkflowJSON& workflowJSON, const boost::optional<openstudio::path>& finalSeedModelicaFile) {
    ModelicaSetup setup;

    auto addSearchPath = [&setup](const openstudio::path& dir) {
      if (dir.empty()) {
        return;
      }
      setup.searchPaths.push_back(dir);
    };

    auto addFileToLoad = [&setup, &addSearchPath](const openstudio::path& file) {
      if (file.empty()) {
        return;
      }
      const auto absoluteFile = boost::filesystem::absolute(file);
      setup.files.push_back(absoluteFile);
      addSearchPath(absoluteFile.parent_path());
    };

    const auto handleDirectory = [&addFileToLoad, &addSearchPath](const openstudio::path& dir) {
      const auto absoluteDir = boost::filesystem::absolute(dir);
      addSearchPath(absoluteDir);
      const auto packageMo = absoluteDir / toPath("package.mo");
      if (openstudio::filesystem::exists(packageMo)) {
        addFileToLoad(packageMo);
      }
    };

    for (const auto& envPath : getModelicaPathEnvEntries()) {
      addSearchPath(envPath);
    }

    for (const auto& packageSpec : workflowJSON.modelicaPackages()) {
      openstudio::path resolved;
      if (packageSpec.is_absolute()) {
        resolved = packageSpec;
      } else {
        if (auto located = workflowJSON.findFile(packageSpec)) {
          resolved = *located;
        }
      }

      if (resolved.empty()) {
        throw std::runtime_error(fmt::format("Modelica package '{}' could not be resolved", toString(packageSpec)));
      }

      if (!openstudio::filesystem::exists(resolved)) {
        throw std::runtime_error(fmt::format("Modelica package '{}' does not exist at '{}'", toString(packageSpec), resolved.generic_string()));
      }

      if (openstudio::filesystem::is_directory(resolved)) {
        handleDirectory(resolved);
      } else {
        addFileToLoad(resolved);
      }
    }

    if (finalSeedModelicaFile) {
      if (openstudio::filesystem::is_directory(*finalSeedModelicaFile)) {
        handleDirectory(*finalSeedModelicaFile);
      } else {
        addFileToLoad(*finalSeedModelicaFile);
      }
    } else if (auto seedModelicaFile = workflowJSON.seedModelicaFile()) {
      if (auto resolved = workflowJSON.findFile(seedModelicaFile.get())) {
        if (openstudio::filesystem::is_directory(*resolved)) {
          handleDirectory(*resolved);
        } else {
          addFileToLoad(*resolved);
        }
      }
    }

    dedupePaths(setup.files);
    dedupePaths(setup.searchPaths);

    return setup;
  }

  std::string buildDymolaSetModelicaPathCommand(const std::vector<openstudio::path>& searchPaths) {
#ifdef _WIN32
    constexpr const char* separatorLiteral = "\";\"";
#else
    constexpr const char* separatorLiteral = "\":\"";
#endif

    // Dymola reads MODELICAPATH directly, so build a single path string that can
    // be applied via Modelica.Utilities.System.setEnvironmentVariable before
    // loading any packages.

    std::string expression;
    for (const auto& searchPath : searchPaths) {
      if (expression.empty()) {
        expression = modelicaStringLiteral(searchPath.generic_string());
      } else {
        expression = fmt::format("{} + {} + {}", expression, separatorLiteral, modelicaStringLiteral(searchPath.generic_string()));
      }
    }

    if (expression.empty()) {
      expression = "\"\"";
    }

    return fmt::format("Modelica.Utilities.System.setEnvironmentVariable(\"MODELICAPATH\", {});\n", expression);
  }

  std::string buildSetModelicaPathCommand(ModelicaCompilerType compilerType, const std::vector<openstudio::path>& searchPaths) {
    switch (compilerType) {
      case ModelicaCompilerType::OpenModelica:
        return {};
      case ModelicaCompilerType::Dymola:
        return buildDymolaSetModelicaPathCommand(searchPaths);
    }
    return {};
  }

  template <typename T, typename Formatter>
  std::string formatModelicaArray(const std::vector<T>& values, Formatter formatter) {
    std::string buffer = "{";
    bool first = true;
    for (const auto& value : values) {
      if (!first) {
        buffer.append(", ");
      }
      buffer.append(formatter(value));
      first = false;
    }
    buffer.push_back('}');
    return buffer;
  }

  openstudio::path createOpenModelicaScript(const WorkflowJSON& workflowJSON, const ModelicaSetup& setup, const measure::ModelicaParameters& params) {
    auto seedModelicaModel = workflowJSON.seedModelicaModel();
    // There is a check for seedModelicaModel, prior to reaching this point.
    // In other words, we shouldn't be trying to "runModelica" if there is no seed model.
    OS_ASSERT(seedModelicaModel);

    // Generate a temporary OpenModelica script (run.mos) that mirrors what the CLI achieves manually.
    constexpr auto mosPath = "run.mos";
    std::ofstream mosFile(mosPath);

    mosFile << "echo(false);\n";

    auto loadFile = [&mosFile](const openstudio::path& file) {
      mosFile << fmt::format(R"(
clearMessages();
res := loadFile("{0}");
if not res then
  err := getErrorString();
  if err == "" then
    print("<Modelica-Warn>OpenModelica loadFile(...) produced an unspecified error.</Modelica-Warn>\n");
  else
    print("<Modelica-Error>OpenModleica loadFile(...) error: " + err + "</Modelica-Error>\n");
  end if;
end if;
clearMessages();
                           )",
                             file.generic_string());
    };

    // Open Modelica does not seem to load some (all?) package out of MODELICAPATH.
    // This has been especially true for MBL.
    // This is a workaround. Look in the path for package.mo and load those
    for (const auto& searchPath : setup.searchPaths) {
      const auto packageMo = searchPath / toPath("package.mo");
      if (openstudio::filesystem::exists(packageMo)) {
        loadFile(packageMo);
      }
    }

    // Load every explicit file (seed model + auxiliary .mo files) provided by the setup.
    for (const auto& file : setup.files) {
      loadFile(file);
    }

    // Apply all parameters from the Measure so the upcoming simulation reflects user overrides.
    const auto allParams = params.getAllParameters();
    for (const auto& param : allParams) {
      mosFile << fmt::format(R"(
clearMessages();
res := setParameterValue({}, {}, {});
if not res then
  err := getErrorString();
  if err == "" then
    print("<Modelica-Warn>OpenModelica setParameterValue(...) produced an unspecified error.</Modelica-Warn>\n");
  else
    print("<Modelica-Error>OpenModleica setParameterValue(...) produced an error: " + err + "</Modelica-Error>\n");
  end if;
end if;
clearMessages();
                           )",
                             param.model(), param.key(), param.value());
    }

    // Run simulation and look for errors
    mosFile << fmt::format(R"(
clearMessages();
res := simulate({}, stopTime=604800, stepSize=10);
resFile := res.resultFile;
messages := res.messages;
print("<Modelica-Messages>" + messages + "</Modelica-Messages>\n");
if regularFileExists(resFile) then
  print("Modelica simulation was successful\n");
  print("<Modelica-ResultFile>" + resFile + "</Modelica-ResultFile>\n");
else
  err := getErrorString();
  if err == "" then
    print("<Modelica-Error>The OpenModelica simulation completed, but did not produce a results file. The file `run/stdout-modelica` or --show-stdout may provide additional information.</Modelica-Error>\n");
  else
    print("<Modelica-Error>" + err + "</Modelica-Error>\n");
  end if;
end if;
clearMessages();
                           )",
                           *seedModelicaModel);
    mosFile.close();

    return mosPath;
  }

  [[maybe_unused]] openstudio::path createDymolaScript(const WorkflowJSON& workflowJSON, const ModelicaSetup& setup,
                                                       const measure::ModelicaParameters& params) {
    auto seedModelicaModel = workflowJSON.seedModelicaModel();
    OS_ASSERT(seedModelicaModel);

    constexpr auto mosPath = "run.mos";
    std::ofstream mosFile(mosPath);

    mosFile << buildSetModelicaPathCommand(ModelicaCompilerType::Dymola, setup.searchPaths);
    for (const auto& file : setup.files) {
      mosFile << fmt::format("openModel({});\n", modelicaStringLiteral(file.generic_string()));
    }

    const auto allParams = params.getAllParameters();
    std::vector<measure::ModelicaParameter> filtered;
    filtered.reserve(allParams.size());
    for (const auto& param : allParams) {
      if (param.model() == *seedModelicaModel) {
        filtered.push_back(param);
      }
    }

    // Dymola's simulateModel expects modifier names/values arrays; map the
    // ModelicaParameter collection into those two arrays before issuing the
    // simulateModel call.
    const auto finalNames = formatModelicaArray(filtered, [](const auto& p) { return modelicaStringLiteral(p.key()); });
    const auto finalValues = formatModelicaArray(filtered, [](const auto& p) { return p.value(); });
    mosFile << fmt::format("finalNames := {};\n", finalNames);
    mosFile << fmt::format("finalValues := {};\n", finalValues);
    mosFile << fmt::format("simulateModel({}, stopTime=604800, stepSize=10, finalNames=finalNames, finalValues=finalValues);\n",
                           modelicaStringLiteral(*seedModelicaModel));
    mosFile << "Modelica.Utilities.Streams.print(getLastError());\n";
    mosFile.close();

    return mosPath;
  }

  openstudio::path createModelicaScript(const WorkflowJSON& workflowJSON, const ModelicaSetup& setup, const measure::ModelicaParameters& params,
                                        ModelicaCompilerType compilerType) {
    switch (compilerType) {
      case ModelicaCompilerType::OpenModelica:
        return createOpenModelicaScript(workflowJSON, setup, params);
      case ModelicaCompilerType::Dymola:
        LOG_AND_THROW("This OpenStudio build only supports OpenModelica; set OS_MODELICA_COMPILER=openmodelica and ensure omc is installed.");
    }
    OS_ASSERT(false);
    return {};
  }

  std::string quoteCommandArgument(const std::string& arg) {
    std::string quoted;
    quoted.reserve(arg.size() + 2);
    quoted.push_back('"');
    for (const char ch : arg) {
      if (ch == '"') {
        quoted.push_back('\\');
      }
      quoted.push_back(ch);
    }
    quoted.push_back('"');
    return quoted;
  }

  std::string buildCommandLine(const ModelicaCompilerInfo& compiler, const openstudio::path& scriptPath) {
    std::vector<std::string> parts;
    parts.emplace_back(quoteCommandArgument(compiler.executable.string()));
    for (const auto& arg : compiler.defaultArgs) {
      parts.emplace_back(quoteCommandArgument(arg));
    }
    parts.emplace_back(quoteCommandArgument(scriptPath.string()));
    return fmt::format("{}", fmt::join(parts, " "));
  }
}  // namespace

void OSWorkflow::runModelica() {
  const auto curDirPath = boost::filesystem::current_path();
  try {
    auto runDirPath = workflowJSON.absoluteRunDir();
    boost::filesystem::current_path(runDirPath);
    // Switch into the workflow's run directory so every generated file is scoped to the current job.
    //PrepareRunDirResults runDirResults(runDirPath);
    LOG(Info, "Starting Modelica simulation in run directory: " << runDirPath);

    // Mirror the EnergyPlus workflow convention by capturing the solver output locally.
    std::ofstream stdout_ofs(openstudio::toString(runDirPath / "stdout-modelica"), std::ofstream::trunc);
    std::ofstream stderr_ofs(openstudio::toString(runDirPath / "stderr-modelica"), std::ofstream::trunc);

    state = State::Modelica;
    m_lastModelicaResultPath.reset();

    int result = 0;
    OS_ASSERT(workspace_);

    const auto compiler = getModelicaCompiler();
    LOG(Info, fmt::format("Using {} compiler at '{}'", compilerDisplayName(compiler.type), compiler.executable.generic_string()));
    const auto params = runner.modelicaParameters();
    const auto setup = getModelicaSetup(workflowJSON, m_latestModelicaFilePath);
    // The script encodes the files to load, parameter overrides, and the simulate command for the chosen compiler.
    const auto script_path = createModelicaScript(workflowJSON, setup, params, compiler.type);
    // Capture the exact command line so it can be logged/replayed, then feed it through the platform shell below.
    const auto cmd = buildCommandLine(compiler, script_path);

    const char* shellExe = nullptr;
    const char* shellArg = nullptr;
#ifdef _WIN32
    shellExe = "cmd.exe";
    shellArg = "/C";
#else
    shellExe = "/bin/sh";
    shellArg = "-c";
#endif

    // Spawn through the platform shell so that the command line mirrors what we log/print for reproduction while still
    // letting boost::process capture stdout/stderr for log files.
    std::optional<openstudio::path> detectedModelicaResultPath;

    detailedTimeBlock("Running Modelica", [this, shellExe, shellArg, &cmd, &result, &stdout_ofs, &stderr_ofs, &detectedModelicaResultPath] {
      namespace bp = boost::process;
      bp::ipstream stdout_is;
      bp::ipstream stderr_is;
      // Run the compiler command via the shell and hook up pipes so we can tee output to log files.
      bp::child c(shellExe, shellArg, cmd, bp::std_out > stdout_is, bp::std_err > stderr_is);

      ModelicaTagParserState stdoutTagState;
      ModelicaTagParserState stderrTagState;

      // Reads a stream line-by-line, mirroring output to disk while optionally echoing and extracting tagged payloads.
      auto reader = [this, &detectedModelicaResultPath](bp::ipstream& stream, std::ofstream& ofs, bool parseTaggedOutput,
                                                        ModelicaTagParserState& tagState, bool echo) {
        std::string line;
        while (std::getline(stream, line)) {
          if (!line.empty() && line.back() == '\r') {
            line.pop_back();
          }
          if (parseTaggedOutput) {
            const auto taggedOutput = parseModelicaTaggedOutput(line, tagState);
            if (!taggedOutput.empty()) {
              logCompilerOutput(taggedOutput, echo && m_show_stdout);
              if (taggedOutput.simulationResultFile) {
                detectedModelicaResultPath = openstudio::toPath(*taggedOutput.simulationResultFile);
              }
            }
          }
          if (ofs.is_open()) {
            ofs << line << '\n';
          }
          if (echo && m_show_stdout) {
            fmt::print("{}\n", line);
          }
        }
        if (parseTaggedOutput) {
          const auto trailingOutput = finalizeModelicaTaggedOutput(tagState);
          if (!trailingOutput.empty()) {
            logCompilerOutput(trailingOutput, echo && m_show_stdout);
            if (trailingOutput.simulationResultFile) {
              detectedModelicaResultPath = openstudio::toPath(*trailingOutput.simulationResultFile);
            }
          }
        }
      };

      std::thread stdoutThread(reader, std::ref(stdout_is), std::ref(stdout_ofs), true, std::ref(stdoutTagState), true);
      std::thread stderrThread(reader, std::ref(stderr_is), std::ref(stderr_ofs), false, std::ref(stderrTagState), false);
      c.wait();
      stdoutThread.join();
      stderrThread.join();
      result = c.exit_code();
    });

    if (detectedModelicaResultPath) {
      auto resolvedPath = *detectedModelicaResultPath;
      if (openstudio::filesystem::exists(resolvedPath)) {
        m_lastModelicaResultPath = openstudio::filesystem::canonical(resolvedPath);
      } else {
        LOG(Warn, "Modelica reported a result file at '" << resolvedPath << "', but it does not exist.");
        m_lastModelicaResultPath.reset();
      }
    } else {
      m_lastModelicaResultPath.reset();
    }

    LOG(Info, "Modelica returned '" << result << "'");
    if (result != 0) {
      LOG(Warn, "Modelica returned a non-zero exit code (" << result << "). Check the Modelica log");
    }

  } catch (const std::exception& e) {
    boost::filesystem::current_path(curDirPath);
    LOG_AND_THROW(e.what());
  }
}

}  // namespace openstudio
