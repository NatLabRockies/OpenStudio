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
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

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
    bool setOutputCSV(bool outputCSV);

    bool outputMTR() const;
    bool setOutputMTR(bool outputMTR);

    bool outputESO() const;
    bool setOutputESO(bool outputESO);

    bool outputEIO() const;
    bool setOutputEIO(bool outputEIO);

    bool outputTabular() const;
    bool setOutputTabular(bool outputTabular);

    bool outputSQLite() const;
    bool setOutputSQLite(bool outputSQLite);

    bool outputJSON() const;
    bool setOutputJSON(bool outputJSON);

    bool outputAUDIT() const;
    bool setOutputAUDIT(bool outputAUDIT);

    bool outputSpaceSizing() const;
    bool setOutputSpaceSizing(bool outputSpaceSizing);

    bool outputZoneSizing() const;
    bool setOutputZoneSizing(bool outputZoneSizing);

    bool outputSystemSizing() const;
    bool setOutputSystemSizing(bool outputSystemSizing);

    bool outputDXF() const;
    bool setOutputDXF(bool outputDXF);

    bool outputBND() const;
    bool setOutputBND(bool outputBND);

    bool outputRDD() const;
    bool setOutputRDD(bool outputRDD);

    bool outputMDD() const;
    bool setOutputMDD(bool outputMDD);

    bool outputMTD() const;
    bool setOutputMTD(bool outputMTD);

    bool outputSHD() const;
    bool setOutputSHD(bool outputSHD);

    bool outputDFS() const;
    bool setOutputDFS(bool outputDFS);

    bool outputGLHE() const;
    bool setOutputGLHE(bool outputGLHE);

    bool outputDelightIn() const;
    bool setOutputDelightIn(bool outputDelightIn);

    bool outputDelightELdmp() const;
    bool setOutputDelightELdmp(bool outputDelightELdmp);

    bool outputDelightDFdmp() const;
    bool setOutputDelightDFdmp(bool outputDelightDFdmp);

    bool outputEDD() const;
    bool setOutputEDD(bool outputEDD);

    bool outputDBG() const;
    bool setOutputDBG(bool outputDBG);

    bool outputPerfLog() const;
    bool setOutputPerfLog(bool outputPerfLog);

    bool outputSLN() const;
    bool setOutputSLN(bool outputSLN);

    bool outputSCI() const;
    bool setOutputSCI(bool outputSCI);

    bool outputWRL() const;
    bool setOutputWRL(bool outputWRL);

    bool outputScreen() const;
    bool setOutputScreen(bool outputScreen);

    bool outputExtShd() const;
    bool setOutputExtShd(bool outputExtShd);

    bool outputTarcog() const;
    bool setOutputTarcog(bool outputTarcog);

    bool outputPlantComponentSizing() const;
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
