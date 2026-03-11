/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTCONTROLFILES_IMPL_HPP
#define EPMODEL_OUTPUTCONTROLFILES_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API OutputControlFiles_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~OutputControlFiles_Impl() override = default;

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
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
