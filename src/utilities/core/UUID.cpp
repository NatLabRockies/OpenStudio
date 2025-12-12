/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "UUID.hpp"
#include "String.hpp"

#include <sstream>

#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/thread/tss.hpp>

namespace openstudio {

UUID::UUID() : boost::uuids::uuid(boost::uuids::nil_uuid()) {}

UUID::UUID(const boost::uuids::uuid& t_other) : boost::uuids::uuid(t_other) {}

UUID UUID::random_generate() {
  static thread_local boost::uuids::random_generator gen;
  return UUID(gen());
}

UUID UUID::string_generate(const std::string& t_str) {
  static thread_local boost::uuids::string_generator gen;
  return UUID(gen(t_str));
}

UUID createUUID() {
  return UUID::random_generate();
}

UUID toUUID(const std::string& str) {
  try {
    return UUID::string_generate(str);
  } catch (...) {
    return {};
  }
}

// Finds Version 4 uuid in a string including {}
const boost::regex& uuidInString() {
  static const boost::regex result("(\\{[a-f0-9]{8}-[a-f0-9]{4}-4[a-f0-9]{3}-[89aAbB][a-f0-9]{3}-[a-f0-9]{12}\\})");
  return result;
}

bool operator!=(const UUID& lhs, const UUID& rhs) {
  return static_cast<const boost::uuids::uuid&>(lhs) != static_cast<const boost::uuids::uuid&>(rhs);
}

bool operator<(const UUID& lhs, const UUID& rhs) {
  return static_cast<const boost::uuids::uuid&>(lhs) < static_cast<const boost::uuids::uuid&>(rhs);
}

bool operator==(const UUID& lhs, const UUID& rhs) {
  return static_cast<const boost::uuids::uuid&>(lhs) == static_cast<const boost::uuids::uuid&>(rhs);
}

bool operator>(const UUID& lhs, const UUID& rhs) {
  return static_cast<const boost::uuids::uuid&>(lhs) > static_cast<const boost::uuids::uuid&>(rhs);
}

std::string toString(const UUID& uuid) {
  std::stringstream ss;
  ss << '{';
  boost::uuids::operator<<(ss, uuid);
  ss << '}';
  return ss.str();
}

std::string createUniqueName(const std::string& prefix) {
  std::stringstream ss;
  if (!prefix.empty()) {
    ss << prefix << " ";
  }
  ss << toString(createUUID());
  return ss.str();
}

std::string removeBraces(const UUID& uuid) {
  std::stringstream ss;
  boost::uuids::operator<<(ss, uuid);
  return ss.str();
}

std::ostream& operator<<(std::ostream& os, const UUID& uuid) {
  os << toString(uuid);
  return os;
}

}  // namespace openstudio
