/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTCONTROLFILES_HPP
#define EPMODEL_OUTPUTCONTROLFILES_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class OutputControlFiles_Impl;
}

class EPMODEL_API OutputControlFiles : public ModelObject
{
 public:
  explicit OutputControlFiles(const Model& model);

  virtual ~OutputControlFiles() override = default;
  OutputControlFiles(const OutputControlFiles& other) = default;
  OutputControlFiles(OutputControlFiles&& other) = default;
  OutputControlFiles& operator=(const OutputControlFiles&) = default;
  OutputControlFiles& operator=(OutputControlFiles&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model::OutputControlFiles scalar accessor names/signatures.
  // - Field Mapping: output* scalar APIs map directly to E+ OutputControl:Files yes/no fields.
  // - Field Mapping: E+ OutputControl:Files OutputEND has no openstudio::model scalar API; ForwardTranslator keeps it hardcoded to "Yes".
  // - ForwardTranslator evidence: ForwardTranslateOutputControlFiles.cpp writes these preserved output* APIs directly.
  // - TODO(parity): Keep scalar API stable while extending any non-scalar parity behavior in future passes.
  bool outputCSV() const;
  bool outputMTR() const;
  bool outputESO() const;
  bool outputEIO() const;
  bool outputTabular() const;
  bool outputSQLite() const;
  bool outputJSON() const;
  bool outputAUDIT() const;
  bool outputSpaceSizing() const;
  bool outputZoneSizing() const;
  bool outputSystemSizing() const;
  bool outputDXF() const;
  bool outputBND() const;
  bool outputRDD() const;
  bool outputMDD() const;
  bool outputMTD() const;
  bool outputSHD() const;
  bool outputDFS() const;
  bool outputGLHE() const;
  bool outputDelightIn() const;
  bool outputDelightELdmp() const;
  bool outputDelightDFdmp() const;
  bool outputEDD() const;
  bool outputDBG() const;
  bool outputPerfLog() const;
  bool outputSLN() const;
  bool outputSCI() const;
  bool outputWRL() const;
  bool outputScreen() const;
  bool outputExtShd() const;
  bool outputTarcog() const;
  bool outputPlantComponentSizing() const;

  bool setOutputCSV(bool outputCSV);
  bool setOutputMTR(bool outputMTR);
  bool setOutputESO(bool outputESO);
  bool setOutputEIO(bool outputEIO);
  bool setOutputTabular(bool outputTabular);
  bool setOutputSQLite(bool outputSQLite);
  bool setOutputJSON(bool outputJSON);
  bool setOutputAUDIT(bool outputAUDIT);
  bool setOutputSpaceSizing(bool outputSpaceSizing);
  bool setOutputZoneSizing(bool outputZoneSizing);
  bool setOutputSystemSizing(bool outputSystemSizing);
  bool setOutputDXF(bool outputDXF);
  bool setOutputBND(bool outputBND);
  bool setOutputRDD(bool outputRDD);
  bool setOutputMDD(bool outputMDD);
  bool setOutputMTD(bool outputMTD);
  bool setOutputSHD(bool outputSHD);
  bool setOutputDFS(bool outputDFS);
  bool setOutputGLHE(bool outputGLHE);
  bool setOutputDelightIn(bool outputDelightIn);
  bool setOutputDelightELdmp(bool outputDelightELdmp);
  bool setOutputDelightDFdmp(bool outputDelightDFdmp);
  bool setOutputEDD(bool outputEDD);
  bool setOutputDBG(bool outputDBG);
  bool setOutputPerfLog(bool outputPerfLog);
  bool setOutputSLN(bool outputSLN);
  bool setOutputSCI(bool outputSCI);
  bool setOutputWRL(bool outputWRL);
  bool setOutputScreen(bool outputScreen);
  bool setOutputExtShd(bool outputExtShd);
  bool setOutputTarcog(bool outputTarcog);
  bool setOutputPlantComponentSizing(bool outputPlantComponentSizing);

 protected:
  using ImplType = detail::OutputControlFiles_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit OutputControlFiles(std::shared_ptr<detail::OutputControlFiles_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
