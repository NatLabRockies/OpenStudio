/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTPREPROCESSORMESSAGE_HPP
#define EPMODEL_OUTPUTPREPROCESSORMESSAGE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class OutputPreprocessorMessage_Impl;
  }

  class EPMODEL_API OutputPreprocessorMessage : public ModelObject
  {
   public:
    explicit OutputPreprocessorMessage(const Model& model);

    virtual ~OutputPreprocessorMessage() override = default;
    OutputPreprocessorMessage(const OutputPreprocessorMessage& other) = default;
    OutputPreprocessorMessage(OutputPreprocessorMessage&& other) = default;
    OutputPreprocessorMessage& operator=(const OutputPreprocessorMessage&) = default;
    OutputPreprocessorMessage& operator=(OutputPreprocessorMessage&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> errorSeverityValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to EnergyPlus Output:PreprocessorMessage fields.
    // - Field Mapping: All fields on this object are scalar alpha/choice fields in this pass (no relationship fields excluded).
    // - ForwardTranslator evidence: EP-only type (no OS forward source found in mapping appendix), so IDD-derived API is used.
    // - TODO(parity): Preserve scalar signatures if/when richer behavior is added later.

    boost::optional<std::string> preprocessorName() const;
    bool setPreprocessorName(const std::string& preprocessorName);
    void resetPreprocessorName();

    boost::optional<std::string> errorSeverity() const;
    bool setErrorSeverity(const std::string& errorSeverity);
    void resetErrorSeverity();

    boost::optional<std::string> messageLine1() const;
    bool setMessageLine1(const std::string& messageLine1);
    void resetMessageLine1();

    boost::optional<std::string> messageLine2() const;
    bool setMessageLine2(const std::string& messageLine2);
    void resetMessageLine2();

    boost::optional<std::string> messageLine3() const;
    bool setMessageLine3(const std::string& messageLine3);
    void resetMessageLine3();

    boost::optional<std::string> messageLine4() const;
    bool setMessageLine4(const std::string& messageLine4);
    void resetMessageLine4();

    boost::optional<std::string> messageLine5() const;
    bool setMessageLine5(const std::string& messageLine5);
    void resetMessageLine5();

    boost::optional<std::string> messageLine6() const;
    bool setMessageLine6(const std::string& messageLine6);
    void resetMessageLine6();

    boost::optional<std::string> messageLine7() const;
    bool setMessageLine7(const std::string& messageLine7);
    void resetMessageLine7();

    boost::optional<std::string> messageLine8() const;
    bool setMessageLine8(const std::string& messageLine8);
    void resetMessageLine8();

    boost::optional<std::string> messageLine9() const;
    bool setMessageLine9(const std::string& messageLine9);
    void resetMessageLine9();

    boost::optional<std::string> messageLine10() const;
    bool setMessageLine10(const std::string& messageLine10);
    void resetMessageLine10();

   protected:
    using ImplType = detail::OutputPreprocessorMessage_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit OutputPreprocessorMessage(std::shared_ptr<detail::OutputPreprocessorMessage_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
