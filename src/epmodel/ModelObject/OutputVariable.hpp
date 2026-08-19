/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTVARIABLE_HPP
#define EPMODEL_OUTPUTVARIABLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class OutputVariable_Impl;
  }

  /** \brief OutputVariable.
   *
   * \par EnergyPlus object
   * \epobject{input-for-output.html#outputvariable,Output:Variable}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::OutputVariable</code>. Key value, variable name, and reporting frequency are exposed. Model's schedule relationship and <code>exportToBCVTB()</code> setting are not available.
   *
   * \par Known limitations
   * Only the fields and relationships listed in this wrapper are available; broader Model-only helpers are not exposed.
   */
  class EPMODEL_API OutputVariable : public ModelObject
  {
   public:
    explicit OutputVariable(const std::string& variableName, const Model& model);

    virtual ~OutputVariable() override = default;
    OutputVariable(const OutputVariable& other) = default;
    OutputVariable(OutputVariable&& other) = default;
    OutputVariable& operator=(const OutputVariable&) = default;
    OutputVariable& operator=(OutputVariable&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> reportingFrequencyValues();
    std::string keyValue() const;
    bool isKeyValueDefaulted() const;
    bool setKeyValue(const std::string& keyValue);
    void resetKeyValue();

    // Variable Name
    std::string variableName() const;
    bool setVariableName(const std::string& variableName);

    // Reporting Frequency
    std::string reportingFrequency() const;
    bool isReportingFrequencyDefaulted() const;
    bool setReportingFrequency(const std::string& reportingFrequency);
    void resetReportingFrequency();

   protected:
    using ImplType = detail::OutputVariable_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit OutputVariable(std::shared_ptr<detail::OutputVariable_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
