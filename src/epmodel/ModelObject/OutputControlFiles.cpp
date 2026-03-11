/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/OutputControlFiles.hpp"
#include "ModelObject/OutputControlFiles_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OutputControl_Files_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

OutputControlFiles::OutputControlFiles(const Model& model) : ModelObject(OutputControlFiles::iddObjectType(), model) {
  bool ok = setOutputCSV(false);
  OS_ASSERT(ok);

  ok = setOutputMTR(true);
  OS_ASSERT(ok);

  ok = setOutputESO(true);
  OS_ASSERT(ok);

  ok = setOutputEIO(true);
  OS_ASSERT(ok);

  ok = setOutputTabular(true);
  OS_ASSERT(ok);

  ok = setOutputSQLite(true);
  OS_ASSERT(ok);

  ok = setOutputJSON(true);
  OS_ASSERT(ok);

  ok = setOutputAUDIT(true);
  OS_ASSERT(ok);

  ok = setOutputSpaceSizing(true);
  OS_ASSERT(ok);

  ok = setOutputZoneSizing(true);
  OS_ASSERT(ok);

  ok = setOutputSystemSizing(true);
  OS_ASSERT(ok);

  ok = setOutputDXF(true);
  OS_ASSERT(ok);

  ok = setOutputBND(true);
  OS_ASSERT(ok);

  ok = setOutputRDD(true);
  OS_ASSERT(ok);

  ok = setOutputMDD(true);
  OS_ASSERT(ok);

  ok = setOutputMTD(true);
  OS_ASSERT(ok);

  ok = setOutputSHD(true);
  OS_ASSERT(ok);

  ok = setOutputDFS(true);
  OS_ASSERT(ok);

  ok = setOutputGLHE(true);
  OS_ASSERT(ok);

  ok = setOutputDelightIn(true);
  OS_ASSERT(ok);

  ok = setOutputDelightELdmp(true);
  OS_ASSERT(ok);

  ok = setOutputDelightDFdmp(true);
  OS_ASSERT(ok);

  ok = setOutputEDD(true);
  OS_ASSERT(ok);

  ok = setOutputDBG(true);
  OS_ASSERT(ok);

  ok = setOutputPerfLog(true);
  OS_ASSERT(ok);

  ok = setOutputSLN(true);
  OS_ASSERT(ok);

  ok = setOutputSCI(true);
  OS_ASSERT(ok);

  ok = setOutputWRL(true);
  OS_ASSERT(ok);

  ok = setOutputScreen(true);
  OS_ASSERT(ok);

  ok = setOutputExtShd(true);
  OS_ASSERT(ok);

  ok = setOutputTarcog(true);
  OS_ASSERT(ok);

  ok = setOutputPlantComponentSizing(true);
  OS_ASSERT(ok);
}

OutputControlFiles::OutputControlFiles(std::shared_ptr<detail::OutputControlFiles_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType OutputControlFiles::iddObjectType() {
  return IddObjectType::OutputControl_Files;
}

bool OutputControlFiles::outputCSV() const {
  return getImpl<detail::OutputControlFiles_Impl>()->outputCSV();
}

bool OutputControlFiles::outputMTR() const {
  return getImpl<detail::OutputControlFiles_Impl>()->outputMTR();
}

bool OutputControlFiles::outputESO() const {
  return getImpl<detail::OutputControlFiles_Impl>()->outputESO();
}

bool OutputControlFiles::outputEIO() const {
  return getImpl<detail::OutputControlFiles_Impl>()->outputEIO();
}

bool OutputControlFiles::outputTabular() const {
  return getImpl<detail::OutputControlFiles_Impl>()->outputTabular();
}

bool OutputControlFiles::outputSQLite() const {
  return getImpl<detail::OutputControlFiles_Impl>()->outputSQLite();
}

bool OutputControlFiles::outputJSON() const {
  return getImpl<detail::OutputControlFiles_Impl>()->outputJSON();
}

bool OutputControlFiles::outputAUDIT() const {
  return getImpl<detail::OutputControlFiles_Impl>()->outputAUDIT();
}

bool OutputControlFiles::outputSpaceSizing() const {
  return getImpl<detail::OutputControlFiles_Impl>()->outputSpaceSizing();
}

bool OutputControlFiles::outputZoneSizing() const {
  return getImpl<detail::OutputControlFiles_Impl>()->outputZoneSizing();
}

bool OutputControlFiles::outputSystemSizing() const {
  return getImpl<detail::OutputControlFiles_Impl>()->outputSystemSizing();
}

bool OutputControlFiles::outputDXF() const {
  return getImpl<detail::OutputControlFiles_Impl>()->outputDXF();
}

bool OutputControlFiles::outputBND() const {
  return getImpl<detail::OutputControlFiles_Impl>()->outputBND();
}

bool OutputControlFiles::outputRDD() const {
  return getImpl<detail::OutputControlFiles_Impl>()->outputRDD();
}

bool OutputControlFiles::outputMDD() const {
  return getImpl<detail::OutputControlFiles_Impl>()->outputMDD();
}

bool OutputControlFiles::outputMTD() const {
  return getImpl<detail::OutputControlFiles_Impl>()->outputMTD();
}

bool OutputControlFiles::outputSHD() const {
  return getImpl<detail::OutputControlFiles_Impl>()->outputSHD();
}

bool OutputControlFiles::outputDFS() const {
  return getImpl<detail::OutputControlFiles_Impl>()->outputDFS();
}

bool OutputControlFiles::outputGLHE() const {
  return getImpl<detail::OutputControlFiles_Impl>()->outputGLHE();
}

bool OutputControlFiles::outputDelightIn() const {
  return getImpl<detail::OutputControlFiles_Impl>()->outputDelightIn();
}

bool OutputControlFiles::outputDelightELdmp() const {
  return getImpl<detail::OutputControlFiles_Impl>()->outputDelightELdmp();
}

bool OutputControlFiles::outputDelightDFdmp() const {
  return getImpl<detail::OutputControlFiles_Impl>()->outputDelightDFdmp();
}

bool OutputControlFiles::outputEDD() const {
  return getImpl<detail::OutputControlFiles_Impl>()->outputEDD();
}

bool OutputControlFiles::outputDBG() const {
  return getImpl<detail::OutputControlFiles_Impl>()->outputDBG();
}

bool OutputControlFiles::outputPerfLog() const {
  return getImpl<detail::OutputControlFiles_Impl>()->outputPerfLog();
}

bool OutputControlFiles::outputSLN() const {
  return getImpl<detail::OutputControlFiles_Impl>()->outputSLN();
}

bool OutputControlFiles::outputSCI() const {
  return getImpl<detail::OutputControlFiles_Impl>()->outputSCI();
}

bool OutputControlFiles::outputWRL() const {
  return getImpl<detail::OutputControlFiles_Impl>()->outputWRL();
}

bool OutputControlFiles::outputScreen() const {
  return getImpl<detail::OutputControlFiles_Impl>()->outputScreen();
}

bool OutputControlFiles::outputExtShd() const {
  return getImpl<detail::OutputControlFiles_Impl>()->outputExtShd();
}

bool OutputControlFiles::outputTarcog() const {
  return getImpl<detail::OutputControlFiles_Impl>()->outputTarcog();
}

bool OutputControlFiles::outputPlantComponentSizing() const {
  return getImpl<detail::OutputControlFiles_Impl>()->outputPlantComponentSizing();
}

bool OutputControlFiles::setOutputCSV(bool outputCSV) {
  return getImpl<detail::OutputControlFiles_Impl>()->setOutputCSV(outputCSV);
}

bool OutputControlFiles::setOutputMTR(bool outputMTR) {
  return getImpl<detail::OutputControlFiles_Impl>()->setOutputMTR(outputMTR);
}

bool OutputControlFiles::setOutputESO(bool outputESO) {
  return getImpl<detail::OutputControlFiles_Impl>()->setOutputESO(outputESO);
}

bool OutputControlFiles::setOutputEIO(bool outputEIO) {
  return getImpl<detail::OutputControlFiles_Impl>()->setOutputEIO(outputEIO);
}

bool OutputControlFiles::setOutputTabular(bool outputTabular) {
  return getImpl<detail::OutputControlFiles_Impl>()->setOutputTabular(outputTabular);
}

bool OutputControlFiles::setOutputSQLite(bool outputSQLite) {
  return getImpl<detail::OutputControlFiles_Impl>()->setOutputSQLite(outputSQLite);
}

bool OutputControlFiles::setOutputJSON(bool outputJSON) {
  return getImpl<detail::OutputControlFiles_Impl>()->setOutputJSON(outputJSON);
}

bool OutputControlFiles::setOutputAUDIT(bool outputAUDIT) {
  return getImpl<detail::OutputControlFiles_Impl>()->setOutputAUDIT(outputAUDIT);
}

bool OutputControlFiles::setOutputSpaceSizing(bool outputSpaceSizing) {
  return getImpl<detail::OutputControlFiles_Impl>()->setOutputSpaceSizing(outputSpaceSizing);
}

bool OutputControlFiles::setOutputZoneSizing(bool outputZoneSizing) {
  return getImpl<detail::OutputControlFiles_Impl>()->setOutputZoneSizing(outputZoneSizing);
}

bool OutputControlFiles::setOutputSystemSizing(bool outputSystemSizing) {
  return getImpl<detail::OutputControlFiles_Impl>()->setOutputSystemSizing(outputSystemSizing);
}

bool OutputControlFiles::setOutputDXF(bool outputDXF) {
  return getImpl<detail::OutputControlFiles_Impl>()->setOutputDXF(outputDXF);
}

bool OutputControlFiles::setOutputBND(bool outputBND) {
  return getImpl<detail::OutputControlFiles_Impl>()->setOutputBND(outputBND);
}

bool OutputControlFiles::setOutputRDD(bool outputRDD) {
  return getImpl<detail::OutputControlFiles_Impl>()->setOutputRDD(outputRDD);
}

bool OutputControlFiles::setOutputMDD(bool outputMDD) {
  return getImpl<detail::OutputControlFiles_Impl>()->setOutputMDD(outputMDD);
}

bool OutputControlFiles::setOutputMTD(bool outputMTD) {
  return getImpl<detail::OutputControlFiles_Impl>()->setOutputMTD(outputMTD);
}

bool OutputControlFiles::setOutputSHD(bool outputSHD) {
  return getImpl<detail::OutputControlFiles_Impl>()->setOutputSHD(outputSHD);
}

bool OutputControlFiles::setOutputDFS(bool outputDFS) {
  return getImpl<detail::OutputControlFiles_Impl>()->setOutputDFS(outputDFS);
}

bool OutputControlFiles::setOutputGLHE(bool outputGLHE) {
  return getImpl<detail::OutputControlFiles_Impl>()->setOutputGLHE(outputGLHE);
}

bool OutputControlFiles::setOutputDelightIn(bool outputDelightIn) {
  return getImpl<detail::OutputControlFiles_Impl>()->setOutputDelightIn(outputDelightIn);
}

bool OutputControlFiles::setOutputDelightELdmp(bool outputDelightELdmp) {
  return getImpl<detail::OutputControlFiles_Impl>()->setOutputDelightELdmp(outputDelightELdmp);
}

bool OutputControlFiles::setOutputDelightDFdmp(bool outputDelightDFdmp) {
  return getImpl<detail::OutputControlFiles_Impl>()->setOutputDelightDFdmp(outputDelightDFdmp);
}

bool OutputControlFiles::setOutputEDD(bool outputEDD) {
  return getImpl<detail::OutputControlFiles_Impl>()->setOutputEDD(outputEDD);
}

bool OutputControlFiles::setOutputDBG(bool outputDBG) {
  return getImpl<detail::OutputControlFiles_Impl>()->setOutputDBG(outputDBG);
}

bool OutputControlFiles::setOutputPerfLog(bool outputPerfLog) {
  return getImpl<detail::OutputControlFiles_Impl>()->setOutputPerfLog(outputPerfLog);
}

bool OutputControlFiles::setOutputSLN(bool outputSLN) {
  return getImpl<detail::OutputControlFiles_Impl>()->setOutputSLN(outputSLN);
}

bool OutputControlFiles::setOutputSCI(bool outputSCI) {
  return getImpl<detail::OutputControlFiles_Impl>()->setOutputSCI(outputSCI);
}

bool OutputControlFiles::setOutputWRL(bool outputWRL) {
  return getImpl<detail::OutputControlFiles_Impl>()->setOutputWRL(outputWRL);
}

bool OutputControlFiles::setOutputScreen(bool outputScreen) {
  return getImpl<detail::OutputControlFiles_Impl>()->setOutputScreen(outputScreen);
}

bool OutputControlFiles::setOutputExtShd(bool outputExtShd) {
  return getImpl<detail::OutputControlFiles_Impl>()->setOutputExtShd(outputExtShd);
}

bool OutputControlFiles::setOutputTarcog(bool outputTarcog) {
  return getImpl<detail::OutputControlFiles_Impl>()->setOutputTarcog(outputTarcog);
}

bool OutputControlFiles::setOutputPlantComponentSizing(bool outputPlantComponentSizing) {
  return getImpl<detail::OutputControlFiles_Impl>()->setOutputPlantComponentSizing(outputPlantComponentSizing);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

namespace {

bool getYesNoFieldValue(const ModelObject_Impl& impl, const int fieldIndex) {
  if (const auto value = impl.getString(fieldIndex, true)) {
    return openstudio::istringEqual(*value, "Yes") || openstudio::istringEqual(*value, "True");
  }
  return false;
}

bool setYesNoFieldValue(ModelObject_Impl& impl, const int fieldIndex, const bool value) {
  const bool result = impl.setString(fieldIndex, value ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

}  // namespace

bool OutputControlFiles_Impl::outputCSV() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputCSV);
}

bool OutputControlFiles_Impl::outputMTR() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputMTR);
}

bool OutputControlFiles_Impl::outputESO() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputESO);
}

bool OutputControlFiles_Impl::outputEIO() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputEIO);
}

bool OutputControlFiles_Impl::outputTabular() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputTabular);
}

bool OutputControlFiles_Impl::outputSQLite() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputSQLite);
}

bool OutputControlFiles_Impl::outputJSON() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputJSON);
}

bool OutputControlFiles_Impl::outputAUDIT() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputAUDIT);
}

bool OutputControlFiles_Impl::outputSpaceSizing() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputSpaceSizing);
}

bool OutputControlFiles_Impl::outputZoneSizing() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputZoneSizing);
}

bool OutputControlFiles_Impl::outputSystemSizing() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputSystemSizing);
}

bool OutputControlFiles_Impl::outputDXF() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputDXF);
}

bool OutputControlFiles_Impl::outputBND() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputBND);
}

bool OutputControlFiles_Impl::outputRDD() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputRDD);
}

bool OutputControlFiles_Impl::outputMDD() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputMDD);
}

bool OutputControlFiles_Impl::outputMTD() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputMTD);
}

bool OutputControlFiles_Impl::outputSHD() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputSHD);
}

bool OutputControlFiles_Impl::outputDFS() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputDFS);
}

bool OutputControlFiles_Impl::outputGLHE() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputGLHE);
}

bool OutputControlFiles_Impl::outputDelightIn() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputDelightIn);
}

bool OutputControlFiles_Impl::outputDelightELdmp() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputDelightELdmp);
}

bool OutputControlFiles_Impl::outputDelightDFdmp() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputDelightDFdmp);
}

bool OutputControlFiles_Impl::outputEDD() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputEDD);
}

bool OutputControlFiles_Impl::outputDBG() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputDBG);
}

bool OutputControlFiles_Impl::outputPerfLog() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputPerfLog);
}

bool OutputControlFiles_Impl::outputSLN() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputSLN);
}

bool OutputControlFiles_Impl::outputSCI() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputSCI);
}

bool OutputControlFiles_Impl::outputWRL() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputWRL);
}

bool OutputControlFiles_Impl::outputScreen() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputScreen);
}

bool OutputControlFiles_Impl::outputExtShd() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputExtShd);
}

bool OutputControlFiles_Impl::outputTarcog() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputTarcog);
}

bool OutputControlFiles_Impl::outputPlantComponentSizing() const {
  return getYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputPlantComponentSizing);
}

bool OutputControlFiles_Impl::setOutputCSV(bool outputCSV) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputCSV, outputCSV);
}

bool OutputControlFiles_Impl::setOutputMTR(bool outputMTR) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputMTR, outputMTR);
}

bool OutputControlFiles_Impl::setOutputESO(bool outputESO) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputESO, outputESO);
}

bool OutputControlFiles_Impl::setOutputEIO(bool outputEIO) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputEIO, outputEIO);
}

bool OutputControlFiles_Impl::setOutputTabular(bool outputTabular) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputTabular, outputTabular);
}

bool OutputControlFiles_Impl::setOutputSQLite(bool outputSQLite) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputSQLite, outputSQLite);
}

bool OutputControlFiles_Impl::setOutputJSON(bool outputJSON) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputJSON, outputJSON);
}

bool OutputControlFiles_Impl::setOutputAUDIT(bool outputAUDIT) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputAUDIT, outputAUDIT);
}

bool OutputControlFiles_Impl::setOutputSpaceSizing(bool outputSpaceSizing) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputSpaceSizing, outputSpaceSizing);
}

bool OutputControlFiles_Impl::setOutputZoneSizing(bool outputZoneSizing) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputZoneSizing, outputZoneSizing);
}

bool OutputControlFiles_Impl::setOutputSystemSizing(bool outputSystemSizing) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputSystemSizing, outputSystemSizing);
}

bool OutputControlFiles_Impl::setOutputDXF(bool outputDXF) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputDXF, outputDXF);
}

bool OutputControlFiles_Impl::setOutputBND(bool outputBND) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputBND, outputBND);
}

bool OutputControlFiles_Impl::setOutputRDD(bool outputRDD) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputRDD, outputRDD);
}

bool OutputControlFiles_Impl::setOutputMDD(bool outputMDD) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputMDD, outputMDD);
}

bool OutputControlFiles_Impl::setOutputMTD(bool outputMTD) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputMTD, outputMTD);
}

bool OutputControlFiles_Impl::setOutputSHD(bool outputSHD) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputSHD, outputSHD);
}

bool OutputControlFiles_Impl::setOutputDFS(bool outputDFS) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputDFS, outputDFS);
}

bool OutputControlFiles_Impl::setOutputGLHE(bool outputGLHE) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputGLHE, outputGLHE);
}

bool OutputControlFiles_Impl::setOutputDelightIn(bool outputDelightIn) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputDelightIn, outputDelightIn);
}

bool OutputControlFiles_Impl::setOutputDelightELdmp(bool outputDelightELdmp) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputDelightELdmp, outputDelightELdmp);
}

bool OutputControlFiles_Impl::setOutputDelightDFdmp(bool outputDelightDFdmp) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputDelightDFdmp, outputDelightDFdmp);
}

bool OutputControlFiles_Impl::setOutputEDD(bool outputEDD) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputEDD, outputEDD);
}

bool OutputControlFiles_Impl::setOutputDBG(bool outputDBG) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputDBG, outputDBG);
}

bool OutputControlFiles_Impl::setOutputPerfLog(bool outputPerfLog) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputPerfLog, outputPerfLog);
}

bool OutputControlFiles_Impl::setOutputSLN(bool outputSLN) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputSLN, outputSLN);
}

bool OutputControlFiles_Impl::setOutputSCI(bool outputSCI) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputSCI, outputSCI);
}

bool OutputControlFiles_Impl::setOutputWRL(bool outputWRL) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputWRL, outputWRL);
}

bool OutputControlFiles_Impl::setOutputScreen(bool outputScreen) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputScreen, outputScreen);
}

bool OutputControlFiles_Impl::setOutputExtShd(bool outputExtShd) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputExtShd, outputExtShd);
}

bool OutputControlFiles_Impl::setOutputTarcog(bool outputTarcog) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputTarcog, outputTarcog);
}

bool OutputControlFiles_Impl::setOutputPlantComponentSizing(bool outputPlantComponentSizing) {
  return setYesNoFieldValue(*this, openstudio::OutputControl_FilesFields::OutputPlantComponentSizing, outputPlantComponentSizing);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
