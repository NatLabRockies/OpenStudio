/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/OutputPreprocessorMessage.hpp"
#include "ModelObject/OutputPreprocessorMessage_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Output_PreprocessorMessage_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

OutputPreprocessorMessage::OutputPreprocessorMessage(const Model& model) : ModelObject(OutputPreprocessorMessage::iddObjectType(), model) {}

OutputPreprocessorMessage::OutputPreprocessorMessage(std::shared_ptr<detail::OutputPreprocessorMessage_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType OutputPreprocessorMessage::iddObjectType() {
  return IddObjectType::Output_PreprocessorMessage;
}

std::vector<std::string> OutputPreprocessorMessage::errorSeverityValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Output_PreprocessorMessageFields::ErrorSeverity);
}

boost::optional<std::string> OutputPreprocessorMessage::preprocessorName() const {
  return getImpl<detail::OutputPreprocessorMessage_Impl>()->preprocessorName();
}

bool OutputPreprocessorMessage::setPreprocessorName(const std::string& preprocessorName) {
  return getImpl<detail::OutputPreprocessorMessage_Impl>()->setPreprocessorName(preprocessorName);
}

void OutputPreprocessorMessage::resetPreprocessorName() {
  getImpl<detail::OutputPreprocessorMessage_Impl>()->resetPreprocessorName();
}

boost::optional<std::string> OutputPreprocessorMessage::errorSeverity() const {
  return getImpl<detail::OutputPreprocessorMessage_Impl>()->errorSeverity();
}

bool OutputPreprocessorMessage::setErrorSeverity(const std::string& errorSeverity) {
  return getImpl<detail::OutputPreprocessorMessage_Impl>()->setErrorSeverity(errorSeverity);
}

void OutputPreprocessorMessage::resetErrorSeverity() {
  getImpl<detail::OutputPreprocessorMessage_Impl>()->resetErrorSeverity();
}

boost::optional<std::string> OutputPreprocessorMessage::messageLine1() const {
  return getImpl<detail::OutputPreprocessorMessage_Impl>()->messageLine1();
}

bool OutputPreprocessorMessage::setMessageLine1(const std::string& messageLine1) {
  return getImpl<detail::OutputPreprocessorMessage_Impl>()->setMessageLine1(messageLine1);
}

void OutputPreprocessorMessage::resetMessageLine1() {
  getImpl<detail::OutputPreprocessorMessage_Impl>()->resetMessageLine1();
}

boost::optional<std::string> OutputPreprocessorMessage::messageLine2() const {
  return getImpl<detail::OutputPreprocessorMessage_Impl>()->messageLine2();
}

bool OutputPreprocessorMessage::setMessageLine2(const std::string& messageLine2) {
  return getImpl<detail::OutputPreprocessorMessage_Impl>()->setMessageLine2(messageLine2);
}

void OutputPreprocessorMessage::resetMessageLine2() {
  getImpl<detail::OutputPreprocessorMessage_Impl>()->resetMessageLine2();
}

boost::optional<std::string> OutputPreprocessorMessage::messageLine3() const {
  return getImpl<detail::OutputPreprocessorMessage_Impl>()->messageLine3();
}

bool OutputPreprocessorMessage::setMessageLine3(const std::string& messageLine3) {
  return getImpl<detail::OutputPreprocessorMessage_Impl>()->setMessageLine3(messageLine3);
}

void OutputPreprocessorMessage::resetMessageLine3() {
  getImpl<detail::OutputPreprocessorMessage_Impl>()->resetMessageLine3();
}

boost::optional<std::string> OutputPreprocessorMessage::messageLine4() const {
  return getImpl<detail::OutputPreprocessorMessage_Impl>()->messageLine4();
}

bool OutputPreprocessorMessage::setMessageLine4(const std::string& messageLine4) {
  return getImpl<detail::OutputPreprocessorMessage_Impl>()->setMessageLine4(messageLine4);
}

void OutputPreprocessorMessage::resetMessageLine4() {
  getImpl<detail::OutputPreprocessorMessage_Impl>()->resetMessageLine4();
}

boost::optional<std::string> OutputPreprocessorMessage::messageLine5() const {
  return getImpl<detail::OutputPreprocessorMessage_Impl>()->messageLine5();
}

bool OutputPreprocessorMessage::setMessageLine5(const std::string& messageLine5) {
  return getImpl<detail::OutputPreprocessorMessage_Impl>()->setMessageLine5(messageLine5);
}

void OutputPreprocessorMessage::resetMessageLine5() {
  getImpl<detail::OutputPreprocessorMessage_Impl>()->resetMessageLine5();
}

boost::optional<std::string> OutputPreprocessorMessage::messageLine6() const {
  return getImpl<detail::OutputPreprocessorMessage_Impl>()->messageLine6();
}

bool OutputPreprocessorMessage::setMessageLine6(const std::string& messageLine6) {
  return getImpl<detail::OutputPreprocessorMessage_Impl>()->setMessageLine6(messageLine6);
}

void OutputPreprocessorMessage::resetMessageLine6() {
  getImpl<detail::OutputPreprocessorMessage_Impl>()->resetMessageLine6();
}

boost::optional<std::string> OutputPreprocessorMessage::messageLine7() const {
  return getImpl<detail::OutputPreprocessorMessage_Impl>()->messageLine7();
}

bool OutputPreprocessorMessage::setMessageLine7(const std::string& messageLine7) {
  return getImpl<detail::OutputPreprocessorMessage_Impl>()->setMessageLine7(messageLine7);
}

void OutputPreprocessorMessage::resetMessageLine7() {
  getImpl<detail::OutputPreprocessorMessage_Impl>()->resetMessageLine7();
}

boost::optional<std::string> OutputPreprocessorMessage::messageLine8() const {
  return getImpl<detail::OutputPreprocessorMessage_Impl>()->messageLine8();
}

bool OutputPreprocessorMessage::setMessageLine8(const std::string& messageLine8) {
  return getImpl<detail::OutputPreprocessorMessage_Impl>()->setMessageLine8(messageLine8);
}

void OutputPreprocessorMessage::resetMessageLine8() {
  getImpl<detail::OutputPreprocessorMessage_Impl>()->resetMessageLine8();
}

boost::optional<std::string> OutputPreprocessorMessage::messageLine9() const {
  return getImpl<detail::OutputPreprocessorMessage_Impl>()->messageLine9();
}

bool OutputPreprocessorMessage::setMessageLine9(const std::string& messageLine9) {
  return getImpl<detail::OutputPreprocessorMessage_Impl>()->setMessageLine9(messageLine9);
}

void OutputPreprocessorMessage::resetMessageLine9() {
  getImpl<detail::OutputPreprocessorMessage_Impl>()->resetMessageLine9();
}

boost::optional<std::string> OutputPreprocessorMessage::messageLine10() const {
  return getImpl<detail::OutputPreprocessorMessage_Impl>()->messageLine10();
}

bool OutputPreprocessorMessage::setMessageLine10(const std::string& messageLine10) {
  return getImpl<detail::OutputPreprocessorMessage_Impl>()->setMessageLine10(messageLine10);
}

void OutputPreprocessorMessage::resetMessageLine10() {
  getImpl<detail::OutputPreprocessorMessage_Impl>()->resetMessageLine10();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<std::string> OutputPreprocessorMessage_Impl::preprocessorName() const {
  return getString(openstudio::Output_PreprocessorMessageFields::PreprocessorName, true);
}

bool OutputPreprocessorMessage_Impl::setPreprocessorName(const std::string& preprocessorName) {
  return setString(openstudio::Output_PreprocessorMessageFields::PreprocessorName, preprocessorName);
}

void OutputPreprocessorMessage_Impl::resetPreprocessorName() {
  OS_ASSERT(setString(openstudio::Output_PreprocessorMessageFields::PreprocessorName, ""));
}

boost::optional<std::string> OutputPreprocessorMessage_Impl::errorSeverity() const {
  return getString(openstudio::Output_PreprocessorMessageFields::ErrorSeverity, true);
}

bool OutputPreprocessorMessage_Impl::setErrorSeverity(const std::string& errorSeverity) {
  return setString(openstudio::Output_PreprocessorMessageFields::ErrorSeverity, errorSeverity);
}

void OutputPreprocessorMessage_Impl::resetErrorSeverity() {
  OS_ASSERT(setString(openstudio::Output_PreprocessorMessageFields::ErrorSeverity, ""));
}

boost::optional<std::string> OutputPreprocessorMessage_Impl::messageLine1() const {
  return getString(openstudio::Output_PreprocessorMessageFields::MessageLine1, true);
}

bool OutputPreprocessorMessage_Impl::setMessageLine1(const std::string& messageLine1) {
  return setString(openstudio::Output_PreprocessorMessageFields::MessageLine1, messageLine1);
}

void OutputPreprocessorMessage_Impl::resetMessageLine1() {
  OS_ASSERT(setString(openstudio::Output_PreprocessorMessageFields::MessageLine1, ""));
}

boost::optional<std::string> OutputPreprocessorMessage_Impl::messageLine2() const {
  return getString(openstudio::Output_PreprocessorMessageFields::MessageLine2, true);
}

bool OutputPreprocessorMessage_Impl::setMessageLine2(const std::string& messageLine2) {
  return setString(openstudio::Output_PreprocessorMessageFields::MessageLine2, messageLine2);
}

void OutputPreprocessorMessage_Impl::resetMessageLine2() {
  OS_ASSERT(setString(openstudio::Output_PreprocessorMessageFields::MessageLine2, ""));
}

boost::optional<std::string> OutputPreprocessorMessage_Impl::messageLine3() const {
  return getString(openstudio::Output_PreprocessorMessageFields::MessageLine3, true);
}

bool OutputPreprocessorMessage_Impl::setMessageLine3(const std::string& messageLine3) {
  return setString(openstudio::Output_PreprocessorMessageFields::MessageLine3, messageLine3);
}

void OutputPreprocessorMessage_Impl::resetMessageLine3() {
  OS_ASSERT(setString(openstudio::Output_PreprocessorMessageFields::MessageLine3, ""));
}

boost::optional<std::string> OutputPreprocessorMessage_Impl::messageLine4() const {
  return getString(openstudio::Output_PreprocessorMessageFields::MessageLine4, true);
}

bool OutputPreprocessorMessage_Impl::setMessageLine4(const std::string& messageLine4) {
  return setString(openstudio::Output_PreprocessorMessageFields::MessageLine4, messageLine4);
}

void OutputPreprocessorMessage_Impl::resetMessageLine4() {
  OS_ASSERT(setString(openstudio::Output_PreprocessorMessageFields::MessageLine4, ""));
}

boost::optional<std::string> OutputPreprocessorMessage_Impl::messageLine5() const {
  return getString(openstudio::Output_PreprocessorMessageFields::MessageLine5, true);
}

bool OutputPreprocessorMessage_Impl::setMessageLine5(const std::string& messageLine5) {
  return setString(openstudio::Output_PreprocessorMessageFields::MessageLine5, messageLine5);
}

void OutputPreprocessorMessage_Impl::resetMessageLine5() {
  OS_ASSERT(setString(openstudio::Output_PreprocessorMessageFields::MessageLine5, ""));
}

boost::optional<std::string> OutputPreprocessorMessage_Impl::messageLine6() const {
  return getString(openstudio::Output_PreprocessorMessageFields::MessageLine6, true);
}

bool OutputPreprocessorMessage_Impl::setMessageLine6(const std::string& messageLine6) {
  return setString(openstudio::Output_PreprocessorMessageFields::MessageLine6, messageLine6);
}

void OutputPreprocessorMessage_Impl::resetMessageLine6() {
  OS_ASSERT(setString(openstudio::Output_PreprocessorMessageFields::MessageLine6, ""));
}

boost::optional<std::string> OutputPreprocessorMessage_Impl::messageLine7() const {
  return getString(openstudio::Output_PreprocessorMessageFields::MessageLine7, true);
}

bool OutputPreprocessorMessage_Impl::setMessageLine7(const std::string& messageLine7) {
  return setString(openstudio::Output_PreprocessorMessageFields::MessageLine7, messageLine7);
}

void OutputPreprocessorMessage_Impl::resetMessageLine7() {
  OS_ASSERT(setString(openstudio::Output_PreprocessorMessageFields::MessageLine7, ""));
}

boost::optional<std::string> OutputPreprocessorMessage_Impl::messageLine8() const {
  return getString(openstudio::Output_PreprocessorMessageFields::MessageLine8, true);
}

bool OutputPreprocessorMessage_Impl::setMessageLine8(const std::string& messageLine8) {
  return setString(openstudio::Output_PreprocessorMessageFields::MessageLine8, messageLine8);
}

void OutputPreprocessorMessage_Impl::resetMessageLine8() {
  OS_ASSERT(setString(openstudio::Output_PreprocessorMessageFields::MessageLine8, ""));
}

boost::optional<std::string> OutputPreprocessorMessage_Impl::messageLine9() const {
  return getString(openstudio::Output_PreprocessorMessageFields::MessageLine9, true);
}

bool OutputPreprocessorMessage_Impl::setMessageLine9(const std::string& messageLine9) {
  return setString(openstudio::Output_PreprocessorMessageFields::MessageLine9, messageLine9);
}

void OutputPreprocessorMessage_Impl::resetMessageLine9() {
  OS_ASSERT(setString(openstudio::Output_PreprocessorMessageFields::MessageLine9, ""));
}

boost::optional<std::string> OutputPreprocessorMessage_Impl::messageLine10() const {
  return getString(openstudio::Output_PreprocessorMessageFields::MessageLine10, true);
}

bool OutputPreprocessorMessage_Impl::setMessageLine10(const std::string& messageLine10) {
  return setString(openstudio::Output_PreprocessorMessageFields::MessageLine10, messageLine10);
}

void OutputPreprocessorMessage_Impl::resetMessageLine10() {
  OS_ASSERT(setString(openstudio::Output_PreprocessorMessageFields::MessageLine10, ""));
}

std::vector<std::string> OutputPreprocessorMessage_Impl::errorSeverityValues() const {
  return openstudio::epmodel::OutputPreprocessorMessage::errorSeverityValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
