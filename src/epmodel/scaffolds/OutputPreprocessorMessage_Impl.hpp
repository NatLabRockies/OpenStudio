/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTPREPROCESSORMESSAGE_IMPL_HPP
#define EPMODEL_OUTPUTPREPROCESSORMESSAGE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API OutputPreprocessorMessage_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~OutputPreprocessorMessage_Impl() override = default;

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

      std::vector<std::string> errorSeverityValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
