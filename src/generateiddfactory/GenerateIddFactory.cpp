/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GenerateIddFactory.hpp"
#include "WriteEnums.hpp"

#include <iostream>
#include <iomanip>
#include <cmath>
#include <sstream>
#include <exception>

namespace openstudio {

IddFileFactoryDataVector constructIddFileObjects(const std::vector<std::string>& iddArgs) {
  IddFileFactoryDataVector result;
  // Construct one IddFileFactoryData object per Idd file input by the user. Constructor will
  // throw if it is unable to parse iddArg or is unable to validate the path or name.
  for (const std::string& iddArg : iddArgs) {
    result.push_back(IddFileFactoryData(iddArg));
  }
  return result;
}

void initializeOutFiles(GenerateIddFactoryOutFiles& outFiles, const std::vector<IddFileFactoryData>& iddFiles) {
  // start IddEnums.hxx
  outFiles.iddEnumsHxx.tempFile << "#ifndef UTILITIES_IDD_IDDENUMS_HXX" << '\n'
                                << "#define UTILITIES_IDD_IDDENUMS_HXX" << '\n'
                                << '\n'
                                << "#include <utilities/core/Enum.hpp>" << '\n'
                                << '\n'
                                << "#include <boost/optional.hpp>" << '\n'
                                << '\n'
                                << "#include <vector>" << '\n'
                                << "#include <set>" << '\n'
                                << '\n'
                                << "namespace openstudio {" << '\n';

  // start IddFieldEnums.hxx
  outFiles.iddFieldEnumsHxx.tempFile << "#ifndef UTILITIES_IDD_IDDFIELDENUMS_HXX" << '\n'
                                     << "#define UTILITIES_IDD_IDDFIELDENUMS_HXX" << '\n'
                                     << '\n'
                                     << "/** \\file IddFieldEnums.hxx" << '\n'
                                     << " *  IddFieldEnums.hxx includes one file per IddObjectType (excluding Catchall, UserCustom, " << '\n'
                                     << " *  and CommentOnly). Each file so included contains one or two OPENSTUDIO_ENUM macros that " << '\n'
                                     << " *  provide enum and string access to the non-extensible fields and extensible groups of " << '\n'
                                     << " *  the corresponding IddObjects. This file should not be included directly, but rather, " << '\n'
                                     << " *  used as a reference to help locate the individual field enum files that should be " << '\n'
                                     << " *  included in a particular source file. */" << '\n'
                                     << '\n';

  // start IddFieldEnums.ixx
  outFiles.iddFieldEnumsIxx.tempFile << "#ifndef UTILITIES_IDD_IDDFIELDENUMS_IXX" << '\n'
                                     << "#define UTILITIES_IDD_IDDFIELDENUMS_IXX" << '\n'
                                     << '\n';

  // write IddFactory.hxx
  outFiles.iddFactoryHxx.tempFile << R"hpp(#ifndef UTILITIES_IDD_IDDFACTORY_HXX
#define UTILITIES_IDD_IDDFACTORY_HXX

#include <utilities/UtilitiesAPI.hpp>

#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/IddFile.hpp>
#include <utilities/idd/IddEnums.hpp>
#include <utilities/idd/IddEnums.hxx>

#include <utilities/core/Compare.hpp>
#include <utilities/core/Logger.hpp>

#include <map>

namespace openstudio{

/** IddFactory is a Singleton can return \link IddObject IddObjects\endlink and \link IddFile
 *  IddFiles\endlink for the current version of EnergyPlus and OpenStudio. It can return \link IddFile
 *  IddFiles\endlink only (no link with other methods in this class, for instance, no
 *  by-IddObjectType access to individual \link IddObject IddObjects\endlink) for
 *  previous versions of OpenStudio, back to version 0.7.0. It also supports the default IddObject
 *  type, Catchall, which is provided to enable the display of IdfObjects with misspelled type
 *  names, and a CommentOnly object. Its primary function is to establish a single set of IDD schema
 *  across all of OpenStudio, thereby ensuring consistency and reducing file I-O.
 **/
class UTILITIES_API IddFactory  {

 public:

  static IddFactory& instance();

  IddFactory(const IddFactory& other) = delete;
  IddFactory(IddFactory&& other) = delete;
  IddFactory& operator=(const IddFactory&) = delete;
  IddFactory& operator=(IddFactory&&) = delete;

  /** @name Getters */
  //@{

  /** Get the file version. Throws if fileType == IddFileType::UserCustom or
   *  IddFileType::WholeFactory. */
  std::string getVersion(IddFileType fileType) const;

  /** Get the file header. Throws if fileType == IddFileType::UserCustom or
   *  IddFileType::WholeFactory. */
  std::string getHeader(IddFileType fileType) const;

  /** Return all \link IddObject IddObjects\endlink registered in factory. */
  std::vector<IddObject> objects() const;

  /** Return all \link IddObject IddObjects\endlink in IddFileType type. */
  std::vector<IddObject> getObjects(IddFileType fileType) const;

  /** Return all groups in the factory (e.g. "" and "Simulation Parameters"). */
  std::vector<std::string> groups() const;

  /** Return all groups in fileType. */
  std::vector<std::string> getGroups(IddFileType fileType) const;

  /** Return all \link IddObject IddObjects\endlink in group (e.g. "Simulation Parameters"). */
  std::vector<IddObject> getObjectsInGroup(const std::string& group) const;

  /** Return all \link IddObject IddObjects\endlink in group and fileType. */
  std::vector<IddObject> getObjectsInGroup(const std::string& group, IddFileType fileType) const;

  /** Return all \link IddObject IddObjects\endlink that match objectRegex. */
  std::vector<IddObject> getObjects(const boost::regex& objectRegex) const;

  /** Return all \link IddObject IddObjects\endlink that match objectRegex and are in fileType. */
  std::vector<IddObject> getObjects(const boost::regex& objectRegex, IddFileType fileType) const;

  /** Returns the version IddObject for fileType. Throws if fileType == IddFileType::UserCustom
   *  or IddFileType::WholeFactory. */
  IddObject getVersionObject(IddFileType fileType) const;

  /** Return the IddObject with .name() objectName, if it exists in the factory. */
  boost::optional<IddObject> getObject(const std::string& objectName) const;

  /** Return the IddObject corresponding to objectType. Returns false if type ==
   *  IddObjectType::UserCustom. */
  boost::optional<IddObject> getObject(IddObjectType objectType) const;

  /** Return all objects in the factory that are required. */
  std::vector<IddObject> requiredObjects() const;

  /** Return all objects in IddFile fileType that are required. */
  std::vector<IddObject> getRequiredObjects(IddFileType fileType) const;

  /** Return all objects in the factory that are unique. */
  std::vector<IddObject> uniqueObjects() const;

  /** Return all objects in IddFile fileType that are unique. */
  std::vector<IddObject> getUniqueObjects(IddFileType fileType) const;

  /** Return the (current) IddFile corresponding to type. */
  IddFile getIddFile(IddFileType fileType) const;

  /** Return the IddFile corresponding to type and version. Unless version is equal to
   *  VersionString(getVersion(fileType)), files are loaded from disk and returned as
   *  IddFileType::UserCustom, to distinguish them from the IDD information wrapped by
   *  the IddFactory. At this time, only IddFileType::OpenStudio files are supported,
   *  and only for valid version identifiers >= VersionString("0.7.0"). Returns false
   *  in all other cases. */
  boost::optional<IddFile> getIddFile(IddFileType fileType, const VersionString& version) const;

  //@}
  /** @name Queries */
  //@{

  /** Returns true if IddObject of objectType belongs to IddFile of fileType.
   *  IddObjectType::Catchall is in no \link IddFile IddFiles\endlink;
   *  IddObjectType::CommentOnly is in all \link IddFile IddFiles\endlink. */
  bool isInFile(IddObjectType objectType, IddFileType fileType) const;

  //@}
 private:

  IddFactory();
  ~IddFactory() = default;
)hpp";

  for (const IddFileFactoryData& iddFile : iddFiles) {
    outFiles.iddFactoryHxx.tempFile << "  void register" << iddFile.fileName() << "ObjectsInCallbackMap();" << '\n';
  }

  outFiles.iddFactoryHxx.tempFile << R"hpp(
  REGISTER_LOGGER("utilities.idd.IddFactory");

  using CreateIddObjectCallback = std::function<IddObject ()>;
  using IddObjectCallbackMap = std::map<IddObjectType,CreateIddObjectCallback>;
  IddObjectCallbackMap m_callbackMap;

  using IddObjectSourceFileMap = std::multimap<IddObjectType,IddFileType>;
  IddObjectSourceFileMap m_sourceFileMap;

  mutable std::map<VersionString,IddFile> m_osIddFiles;
};

} // openstudio

#endif //UTILITIES_IDD_IDDFACTORY_HXX
)hpp";

  // start IddFactory.cxx
  outFiles.iddFactoryCxx.tempFile << "#include <utilities/idd/IddFactory.hxx>" << '\n'
                                  << "#include <utilities/idd/IddEnums.hxx>" << '\n'
                                  << "#include <utilities/idd/IddRegex.hpp>" << '\n'
                                  << '\n'
                                  << "#include <utilities/core/Assert.hpp>" << '\n'
                                  << "#include <utilities/core/Compare.hpp>" << '\n'
                                  << "#include <utilities/core/Containers.hpp>" << '\n'
                                  << "#include <utilities/embedded_files.hxx>" << '\n'
                                  << '\n'
                                  << "#include <OpenStudio.hxx>" << '\n'
                                  << '\n'
                                  << "namespace openstudio {" << '\n'
                                  << '\n'
                                  << "IddObject createCatchallIddObject() {" << '\n'
                                  << '\n'
                                  << "  static const IddObject object;" << '\n'
                                  << '\n'
                                  << "  // Catchall is the type of IddObject returned by the default constructor." << '\n'
                                  << "  OS_ASSERT(object.type() == IddObjectType::Catchall);" << '\n'
                                  << "  return object;" << '\n'
                                  << "}" << '\n';

  // start other IddFactory cxx files
  for (const std::shared_ptr<IddFactoryOutFile>& cxxFile : outFiles.iddFactoryIddFileCxxs) {
    cxxFile->tempFile << "#include <utilities/idd/IddFactory.hxx>" << '\n'
                      << "#include <utilities/idd/IddEnums.hxx>" << '\n'
                      << '\n'
                      << "#include <utilities/core/Assert.hpp>" << '\n'
                      << "#include <utilities/core/Compare.hpp>" << '\n'
                      << '\n'
                      << '\n'
                      << "namespace openstudio {" << '\n';
  }

  std::cout << "IddFactory files initialized." << '\n' << '\n';
}

void completeOutFiles(const IddFileFactoryDataVector& iddFiles, GenerateIddFactoryOutFiles& outFiles) {

  std::vector<std::pair<std::string, std::string>> filetypes{{"UserCustom", ""}, {"WholeFactory", ""}};
  for (const IddFileFactoryData& idd : iddFiles) {
    filetypes.emplace_back(idd.fileName(), "");
  }

  std::stringstream tempSS;
  writeDomain(tempSS, "IddFileType", filetypes, false);

  outFiles.iddEnumsHxx.tempFile << '\n' << "/** \\class IddFileType */" << '\n' << tempSS.str();
  tempSS.str("");

  std::vector<std::pair<std::string, std::string>> objtypes{{"Catchall", ""}, {"UserCustom", ""}};

  // loop through each IDD file
  for (const IddFileFactoryData& idd : iddFiles) {
    // write out an IddObjectType enum value for each object in the IDD file
    for (const StringPair& objectName : idd.objectNames()) {
      objtypes.emplace_back(objectName.first, objectName.second);
    }
  }

  objtypes.emplace_back("CommentOnly", "");
  writeDomain(tempSS, "IddObjectType", objtypes, false);

  outFiles.iddEnumsHxx.tempFile << '\n'
                                << "/** \\class IddObjectType */" << '\n'
                                << tempSS.str() << '\n'
                                << "}\n"
                                << "#endif // UTILITIES_IDD_IDDENUMS_HXX" << '\n';
  tempSS.str("");

  // complete and close IddFieldEnums.hxx
  outFiles.iddFieldEnumsHxx.tempFile << '\n' << "#endif // UTILITIES_IDD_IDDFIELDENUMS_HXX" << '\n';

  // complete and close IddFieldEnums.ixx
  outFiles.iddFieldEnumsIxx.tempFile << '\n' << "#endif // UTILITIES_IDD_IDDFIELDENUMS_IXX" << '\n';

  // complete and close IddFactory.cxx

  // create function for CommentOnly IddObject
  outFiles.iddFactoryCxx.tempFile << '\n'
                                  << "IddObject createCommentOnlyIddObject() {" << '\n'
                                  << '\n'
                                  << "  static const IddObject object = []{" << '\n'
                                  << "    // use C++11 statics and initialize on first use idiom to ensure static" << '\n'
                                  << "    // is initialized safely exactly once, eliminating need for mutexes" << '\n'
                                  << "    std::stringstream ss;" << '\n'
                                  << "    ss << \"CommentOnly; ! Autogenerated comment only object.\" << '\\n';" << '\n'
                                  << '\n'
                                  << "    IddObjectType objType(IddObjectType::CommentOnly);" << '\n'
                                  << "    OptionalIddObject oObj = IddObject::load(\"CommentOnly\"," << '\n'
                                  << "                                             \"\"," << '\n'
                                  << "                                             ss.str()," << '\n'
                                  << "                                             objType);" << '\n'
                                  << "    OS_ASSERT(oObj);" << '\n'
                                  << "    return *oObj;" << '\n'
                                  << "  }(); // immediately invoked lambda" << '\n'
                                  << '\n'
                                  << "  return object;" << '\n'
                                  << "}" << '\n'
                                  << '\n';

  // static instance as a Singleton
  outFiles.iddFactoryCxx.tempFile << R"cpp(IddFactory& IddFactory::instance() {
  static IddFactory instance;
  return instance;
}

)cpp";

  // constructor
  outFiles.iddFactoryCxx.tempFile << "IddFactory::IddFactory() {" << '\n' << '\n' << "  // initialize callback map" << '\n' << '\n';
  // register create functions in the callback map
  // Catchall
  outFiles.iddFactoryCxx.tempFile << "  m_callbackMap.insert(IddObjectCallbackMap::value_type(IddObjectType::Catchall,"
                                  << "createCatchallIddObject));" << '\n';
  // parsed objects
  for (const IddFileFactoryData& idd : iddFiles) {
    outFiles.iddFactoryCxx.tempFile << "  register" << idd.fileName() << "ObjectsInCallbackMap();" << '\n';
  }
  // CommentOnly
  outFiles.iddFactoryCxx.tempFile << "  m_callbackMap.insert(IddObjectCallbackMap::value_type(IddObjectType::CommentOnly,"
                                  << "createCommentOnlyIddObject));" << '\n'
                                  << '\n'
                                  << "  // instantiate IddObjectType to IddFileType multimap" << '\n'
                                  << '\n';
  // register IddObjectTypes with IddFileTypes
  for (const IddFileFactoryData& idd : iddFiles) {
    std::string fileName = idd.fileName();

    // register local objects
    for (const StringPair& objectName : idd.objectNames()) {
      outFiles.iddFactoryCxx.tempFile << "  m_sourceFileMap.insert(IddObjectSourceFileMap::value_type(IddObjectType::" << objectName.first
                                      << ",IddFileType::" << fileName << "));" << '\n';
    }

    // register imported objects
    for (unsigned i = 0, ni = idd.numIncludedFiles(); i < ni; ++i) {
      /* Included files are identified by name. Optionally, there may be a list of removed objects
         that should not be inherited by the composite file. */
      IddFileFactoryData::FileNameRemovedObjectsPair includedFileData = idd.includedFile(i);
      // Get the included file by name. Will throw if there is no match.
      IddFileFactoryData includedFile = getFile(includedFileData.first, iddFiles);

      std::vector<std::string> excludedObjects;
      for (const StringPair& objectName : includedFile.objectNames()) {

        // If objectName is in list of removed objects, do not add it to m_sourceFileMap,
        if (std::find(includedFileData.second.begin(), includedFileData.second.end(), objectName.first) != includedFileData.second.end()) {
          // and keep its name in case we need to write a warning.
          excludedObjects.push_back(objectName.first);
          continue;
        }

        // objectName is not to be removed, so add it to the composite file.
        outFiles.iddFactoryCxx.tempFile << "  m_sourceFileMap.insert(IddObjectSourceFileMap::value_type(IddObjectType::" << objectName.first
                                        << ",IddFileType::" << fileName << "));" << '\n';

      }  // foreach

      // Write warning if we did not encounter all of the objects that were to be removed.
      if (excludedObjects.size() != includedFileData.second.size()) {
        std::cout << "Warning: Did not encounter all 'objects to remove' while including file " << '\n'
                  << "'" << includedFileData.first << "' in file '" << fileName << "'." << '\n'
                  << "\\remove-object Tags      Objects Actually Removed " << '\n'
                  << "------------------------- -------------------------" << '\n';
        for (int x = 0, y = 0, nx = includedFileData.second.size(), ny = excludedObjects.size(); (x < nx) || (y < ny); ++x, ++y) {
          if (x < nx) {
            std::cout << std::setw(25) << includedFileData.second[x] << " ";
          } else {
            std::cout << std::setw(25) << " " << " ";
          }
          if (y < ny) {
            std::cout << std::setw(25) << excludedObjects[y] << '\n';
          } else {
            std::cout << std::setw(25) << " " << '\n';
          }
        }  // for
      }  // if

    }  // for

    // Register CommentOnly object for all files.
    outFiles.iddFactoryCxx.tempFile << "  m_sourceFileMap.insert(IddObjectSourceFileMap::value_type(IddObjectType::CommentOnly"
                                    << ",IddFileType::" << fileName << "));" << '\n';
  }
  outFiles.iddFactoryCxx.tempFile << '\n' << "}" << '\n';

  // version and header getters
  outFiles.iddFactoryCxx.tempFile << '\n'
                                  << "std::string IddFactory::getVersion(IddFileType fileType) const {" << '\n'
                                  << "  std::string result;" << '\n'
                                  << '\n'
                                  << "  switch (fileType.value()) {" << '\n';
  for (const IddFileFactoryData& idd : iddFiles) {
    outFiles.iddFactoryCxx.tempFile << "    case IddFileType::" << idd.fileName() << " :" << '\n'
                                    << "      result = \"" << idd.version() << "\";" << '\n'
                                    << "      break;" << '\n';
  }
  outFiles.iddFactoryCxx.tempFile << "    default :" << '\n'
                                  << "      LOG_AND_THROW(\"No version to return for IddFileType \" << fileType.valueDescription() << \".\");" << '\n'
                                  << "  } // switch" << '\n'
                                  << '\n'
                                  << "  return result;" << '\n'
                                  << "}" << '\n'
                                  << '\n'
                                  << "std::string IddFactory::getHeader(IddFileType fileType) const {" << '\n'
                                  << "  std::stringstream result;" << '\n'
                                  << "  switch (fileType.value()) {" << '\n';
  for (const IddFileFactoryData& idd : iddFiles) {
    outFiles.iddFactoryCxx.tempFile << "    case IddFileType::" << idd.fileName() << " :" << '\n' << "      result";
    std::stringstream headerStream(idd.header());
    std::string line;
    while (std::getline(headerStream, line)) {
      outFiles.iddFactoryCxx.tempFile << '\n' << "        << \"" << line << "\" << '\\n'";
    }
    // print information about included files
    for (unsigned i = 0, ni = idd.numIncludedFiles(); i < ni; ++i) {
      IddFileFactoryData::FileNameRemovedObjectsPair includedFileData = idd.includedFile(i);
      IddFileFactoryData includedFile = getFile(includedFileData.first, iddFiles);
      outFiles.iddFactoryCxx.tempFile << '\n'
                                      << "        << \"!\\n\"" << '\n'
                                      << "        << \"! **************************************************************************\\n\"" << '\n'
                                      << "        << \"! Includes File: '" << includedFile.fileName() << "'\\n\"" << '\n'
                                      << "        << \"!\\n\"" << '\n'
                                      << "        << \"! Contains all objects from " << includedFile.fileName() << " IDD_Version "
                                      << includedFile.version() << ", except: \\n\"" << '\n';
      for (const std::string& objectName : includedFileData.second) {
        outFiles.iddFactoryCxx.tempFile << "        << \"!   " << objectName << "\\n\"" << '\n';
      }
      outFiles.iddFactoryCxx.tempFile << "        << \"! **************************************************************************\\n\"";
    }
    outFiles.iddFactoryCxx.tempFile << ";" << '\n' << '\n' << "      break;" << '\n';
  }
  outFiles.iddFactoryCxx.tempFile << "    default :" << '\n'
                                  << "      LOG_AND_THROW(\"No header to return for IddFileType \" << fileType.valueDescription() << \".\");" << '\n'
                                  << "  } // switch" << '\n'
                                  << "  return result.str();" << '\n'
                                  << "}" << '\n';

  // object getters
  outFiles.iddFactoryCxx.tempFile
    << '\n'
    << "std::vector<IddObject> IddFactory::objects() const {" << '\n'
    << "  IddObjectVector result;" << '\n'
    << '\n'
    << "  for (IddObjectCallbackMap::const_iterator it = m_callbackMap.begin()," << '\n'
    << "       itEnd = m_callbackMap.end(); it != itEnd; ++it) {" << '\n'
    << "    result.push_back(it->second());" << '\n'
    << "  }" << '\n'
    << '\n'
    << "  return result;" << '\n'
    << "}" << '\n'
    << '\n'
    << "std::vector<IddObject> IddFactory::getObjects(IddFileType fileType) const {" << '\n'
    << "  IddObjectVector result;" << '\n'
    << '\n'
    << "  for(IddObjectCallbackMap::const_iterator it = m_callbackMap.begin()," << '\n'
    << "      itend = m_callbackMap.end(); it != itend; ++it) {" << '\n'
    << "    if (isInFile(it->first,fileType)) { " << '\n'
    << "      result.push_back(it->second()); " << '\n'
    << "    }" << '\n'
    << "  }" << '\n'
    << '\n'
    << "  return result;" << '\n'
    << "}" << '\n'
    << '\n'
    << "std::vector<std::string> IddFactory::groups() const {" << '\n'
    << "  StringSet result;" << '\n'
    << "  for (const IddObject& object : objects()) {" << '\n'
    << "    result.insert(object.group());" << '\n'
    << "  }" << '\n'
    << "  return StringVector(result.begin(),result.end());" << '\n'
    << "}" << '\n'
    << '\n'
    << "std::vector<std::string> IddFactory::getGroups(IddFileType fileType) const {" << '\n'
    << "  StringSet result;" << '\n'
    << "  for (const IddObject& object : getObjects(fileType)) {" << '\n'
    << "    result.insert(object.group());" << '\n'
    << "  }" << '\n'
    << "  return StringVector(result.begin(),result.end());" << '\n'
    << "}" << '\n'
    << '\n'
    << "std::vector<IddObject> IddFactory::getObjectsInGroup(const std::string& group) const {" << '\n'
    << "  IddObjectVector result;" << '\n'
    << "  for (const IddObject& object : objects()) {" << '\n'
    << "    if (istringEqual(object.group(),group)) {" << '\n'
    << "      result.push_back(object);" << '\n'
    << "    }" << '\n'
    << "  }" << '\n'
    << "  return result;" << '\n'
    << "}" << '\n'
    << '\n'
    << "std::vector<IddObject> IddFactory::getObjectsInGroup(const std::string& group, IddFileType fileType) const {" << '\n'
    << "  IddObjectVector result;" << '\n'
    << "  for (const IddObject& object : getObjects(fileType)) {" << '\n'
    << "    if (istringEqual(object.group(),group)) {" << '\n'
    << "      result.push_back(object);" << '\n'
    << "    }" << '\n'
    << "  }" << '\n'
    << "  return result;" << '\n'
    << "}" << '\n'
    << '\n'
    << "std::vector<IddObject> IddFactory::getObjects(const boost::regex& objectRegex) const {" << '\n'
    << "  IddObjectVector result;" << '\n'
    << '\n'
    << "  for (int value : IddObjectType::getValues()) {" << '\n'
    << "    IddObjectType candidate(value);" << '\n'
    << "    if (boost::regex_match(candidate.valueName(),objectRegex) || " << '\n'
    << "        boost::regex_match(candidate.valueDescription(),objectRegex))" << '\n'
    << "    {" << '\n'
    << "      if (OptionalIddObject object = getObject(candidate)) {" << '\n'
    << "        result.push_back(*object);" << '\n'
    << "      }" << '\n'
    << "    }" << '\n'
    << "  }" << '\n'
    << '\n'
    << "  return result;" << '\n'
    << "}" << '\n'
    << '\n'
    << "std::vector<IddObject> IddFactory::getObjects(const boost::regex& objectRegex," << '\n'
    << "                                                       IddFileType fileType) const " << '\n'
    << "{" << '\n'
    << "  IddObjectVector result;" << '\n'
    << '\n'
    << "  for (int value : IddObjectType::getValues()) {" << '\n'
    << "    IddObjectType candidate(value);" << '\n'
    << "    if (isInFile(candidate,fileType) && " << '\n'
    << "        (boost::regex_match(candidate.valueName(),objectRegex) || " << '\n'
    << "         boost::regex_match(candidate.valueDescription(),objectRegex)))" << '\n'
    << "    {" << '\n'
    << "      if (OptionalIddObject object = getObject(candidate)) {" << '\n'
    << "        result.push_back(*object);" << '\n'
    << "      }" << '\n'
    << "    }" << '\n'
    << "  }" << '\n'
    << '\n'
    << "  return result;" << '\n'
    << "}" << '\n'
    << '\n'
    << "IddObject IddFactory::getVersionObject(IddFileType fileType) const {" << '\n'
    << "  if (fileType == IddFileType::EnergyPlus) {" << '\n'
    << "    return getObject(IddObjectType(IddObjectType::Version)).get();" << '\n'
    << "  }" << '\n'
    << '\n'
    << "  if (fileType == IddFileType::OpenStudio) {" << '\n'
    << "    return getObject(IddObjectType(IddObjectType::OS_Version)).get();" << '\n'
    << "  }" << '\n'
    << '\n'
    << "  LOG_AND_THROW(\"Unable to identify unique version object for IddFileType \" << fileType.valueName() << \".\");" << '\n'
    << "  return IddObject();" << '\n'
    << "}" << '\n'
    << '\n'
    << "boost::optional<IddObject> IddFactory::getObject(const std::string& objectName) const" << '\n'
    << "{" << '\n'
    << "  OptionalIddObject result;" << '\n'
    << '\n'
    << "  // let IddObjectType OPENSTUDIO_ENUM handle the string processing" << '\n'
    << "  try {" << '\n'
    << "    IddObjectType objectType(objectName);" << '\n'
    << "    result = getObject(objectType);" << '\n'
    << "  }" << '\n'
    << "  catch (...) {}" << '\n'
    << '\n'
    << "  return result;" << '\n'
    << "}" << '\n'
    << '\n'
    << "boost::optional<IddObject> IddFactory::getObject(IddObjectType objectType) const" << '\n'
    << "{" << '\n'
    << "  OptionalIddObject result;" << '\n'
    << '\n'
    << "  IddObjectCallbackMap::const_iterator lookupPair;" << '\n'
    << "  lookupPair = m_callbackMap.find(objectType);" << '\n'
    << "  if (lookupPair != m_callbackMap.end()) { " << '\n'
    << "    result = lookupPair->second(); " << '\n'
    << "  }" << '\n'
    << "  else { " << '\n'
    << "    OS_ASSERT(objectType == IddObjectType::UserCustom); " << '\n'
    << "    LOG(Info,\"UserCustom objects are not available through the IddFactory. Please query your IddFile by IddObject.name().\");" << '\n'
    << "  }" << '\n'
    << '\n'
    << "  return result;" << '\n'
    << "}" << '\n';

  // required, unique, and required or unique objects
  outFiles.iddFactoryCxx.tempFile << '\n'
                                  << "std::vector<IddObject> IddFactory::requiredObjects() const {" << '\n'
                                  << '\n'
                                  << "  IddObjectVector result;" << '\n'
                                  << '\n'
                                  << "  for (IddObjectCallbackMap::const_iterator it = m_callbackMap.begin()," << '\n'
                                  << "    itEnd = m_callbackMap.end(); it != itEnd; ++it) {" << '\n'
                                  << "    const auto candidate = it->second();" << '\n'
                                  << "    if (candidate.properties().required) {" << '\n'
                                  << "      result.push_back(candidate);" << '\n'
                                  << "    }" << '\n'
                                  << "  }" << '\n'
                                  << '\n'
                                  << "  return result;" << '\n'
                                  << "}" << '\n'
                                  << '\n'
                                  << "std::vector<IddObject> IddFactory::getRequiredObjects(IddFileType fileType) const {" << '\n'
                                  << '\n'
                                  << "  IddObjectVector result; " << '\n'
                                  << '\n'
                                  << "  for(IddObjectCallbackMap::const_iterator it = m_callbackMap.begin()," << '\n'
                                  << "      itEnd = m_callbackMap.end(); it != itEnd; ++it) {" << '\n'
                                  << "    if (isInFile(it->first,fileType)) {" << '\n'
                                  << "      OptionalIddObject candidate = getObject(it->first);" << '\n'
                                  << "      if (candidate->properties().required) {" << '\n'
                                  << "        result.push_back(*candidate);" << '\n'
                                  << "      }" << '\n'
                                  << "    }" << '\n'
                                  << "  }" << '\n'
                                  << '\n'
                                  << "  return result;" << '\n'
                                  << "}" << '\n'
                                  << '\n'
                                  << "std::vector<IddObject> IddFactory::uniqueObjects() const {" << '\n'
                                  << '\n'
                                  << "  IddObjectVector result;" << '\n'
                                  << '\n'
                                  << "  for (IddObjectCallbackMap::const_iterator it = m_callbackMap.begin()," << '\n'
                                  << "    itEnd = m_callbackMap.end(); it != itEnd; ++it) {" << '\n'
                                  << "    const auto candidate = it->second();" << '\n'
                                  << "    if (candidate.properties().unique) {" << '\n'
                                  << "      result.push_back(candidate);" << '\n'
                                  << "    }" << '\n'
                                  << "  }" << '\n'
                                  << '\n'
                                  << "  return result;" << '\n'
                                  << "}" << '\n'
                                  << '\n'
                                  << "std::vector<IddObject> IddFactory::getUniqueObjects(IddFileType fileType) const {" << '\n'
                                  << '\n'
                                  << "  IddObjectVector result; " << '\n'
                                  << '\n'
                                  << "   for(IddObjectCallbackMap::const_iterator it = m_callbackMap.begin()," << '\n'
                                  << "      itEnd = m_callbackMap.end(); it != itEnd; ++it) {" << '\n'
                                  << "    if (isInFile(it->first,fileType)) {" << '\n'
                                  << "      OptionalIddObject candidate = getObject(it->first);" << '\n'
                                  << "      if (candidate->properties().unique) {" << '\n'
                                  << "        result.push_back(*candidate);" << '\n'
                                  << "      }" << '\n'
                                  << "    }" << '\n'
                                  << "  }" << '\n'
                                  << '\n'
                                  << "  return result;" << '\n'
                                  << '\n'
                                  << "}" << '\n';

  // iddFile getters
  outFiles.iddFactoryCxx.tempFile << '\n'
                                  << "IddFile IddFactory::getIddFile(IddFileType fileType) const {" << '\n'
                                  << "  IddFile result;" << '\n'
                                  << '\n'
                                  << "  if (fileType == IddFileType::UserCustom) {" << '\n'
                                  << "    return result; " << '\n'
                                  << "  }" << '\n'
                                  << '\n'
                                  << "  // Add the IddObjects." << '\n'
                                  << "  for(IddObjectCallbackMap::const_iterator it = m_callbackMap.begin()," << '\n'
                                  << "      itend = m_callbackMap.end(); it != itend; ++it) {" << '\n'
                                  << "    if (isInFile(it->first,fileType)) {" << '\n'
                                  << "      result.addObject(it->second());" << '\n'
                                  << "    }" << '\n'
                                  << "  }" << '\n'
                                  << '\n'
                                  << "  // Set the file version and header." << '\n'
                                  << "  try {" << '\n'
                                  << "    result.setVersion(getVersion(fileType));" << '\n'
                                  << "    result.setHeader(getHeader(fileType));" << '\n'
                                  << "  }" << '\n'
                                  << "  catch (...) {}" << '\n'
                                  << '\n'
                                  << "  return result;" << '\n'
                                  << "}" << '\n'
                                  << '\n'
                                  << "boost::optional<IddFile> IddFactory::getIddFile(IddFileType fileType, const VersionString& version) const {"
                                  << '\n'
                                  << "  OptionalIddFile result;" << '\n'
                                  << '\n'
                                  << "  if (fileType == IddFileType::UserCustom) {" << '\n'
                                  << "    return result; " << '\n'
                                  << "  }" << '\n'
                                  << '\n'
                                  << "  if (fileType == IddFileType::WholeFactory) {" << '\n'
                                  << "    LOG(Warn,\"Cannot return the WholeFactory IddFile by version.\");" << '\n'
                                  << "    return result;" << '\n'
                                  << "  }" << '\n'
                                  << '\n'
                                  << "  if (fileType == IddFileType::EnergyPlus) {" << '\n'
                                  << "    LOG(Warn,\"At this time, OpenStudio cannot return EnergyPlus IDD files by version.\");" << '\n'
                                  << "    return result;" << '\n'
                                  << "  }" << '\n'
                                  << '\n'
                                  << "  VersionString currentVersion(openStudioVersion());" << '\n'
                                  << "  OS_ASSERT(fileType == IddFileType::OpenStudio);" << '\n'
                                  << "  if (version == currentVersion) {" << '\n'
                                  << "    return getIddFile(fileType);" << '\n'
                                  << "  }" << '\n'
                                  << "  else {" << '\n'
                                  << "    std::map<VersionString, IddFile>::const_iterator it = m_osIddFiles.find(version);" << '\n'
                                  << "    if (it != m_osIddFiles.end()) {" << '\n'
                                  << "      return it->second;" << '\n'
                                  << "    }" << '\n'
                                  << "    std::string iddPath = \":/idd/versions\";" << '\n'
                                  << "    std::stringstream folderString;" << '\n'
                                  << "    folderString << version.major() << \"_\" << version.minor() << \"_\" << version.patch().get();" << '\n'
                                  << "    iddPath += \"/\" + folderString.str() + \"/OpenStudio.idd\";" << '\n'
                                  << "    if (::openstudio::embedded_files::hasFile(iddPath) && (version < currentVersion)) {" << '\n'
                                  << "      std::stringstream ss;" << '\n'
                                  << "      ss << ::openstudio::embedded_files::getFileAsString(iddPath);" << '\n'
                                  << "      result = IddFile::load(ss);" << '\n'
                                  << "    }" << '\n'
                                  << "    if (result) {" << '\n'
                                  << "      m_osIddFiles[version] = *result;" << '\n'
                                  << "    }" << '\n'
                                  << "  }" << '\n'
                                  << "  return result;" << '\n'
                                  << "}" << '\n';

  // query whether object is in file
  outFiles.iddFactoryCxx.tempFile << '\n'
                                  << "bool IddFactory::isInFile(IddObjectType objectType, IddFileType fileType) const {" << '\n'
                                  << "  typedef IddObjectSourceFileMap::const_iterator const_iterator;" << '\n'
                                  << "  std::pair<const_iterator,const_iterator> range;" << '\n'
                                  << "  range = m_sourceFileMap.equal_range(objectType);" << '\n'
                                  << "  for (const_iterator it = range.first; it != range.second; ++it) {" << '\n'
                                  << "    if ((it->second == fileType) || (fileType == IddFileType::WholeFactory)) {" << '\n'
                                  << "      return true;" << '\n'
                                  << "    }" << '\n'
                                  << "  }" << '\n'
                                  << '\n'
                                  << "  return false;" << '\n'
                                  << "}" << '\n';

  // Implementation for IddObjectType and IddFileType
  writeBuildStringVec(outFiles.iddFactoryCxx.tempFile, "IddObjectType", objtypes, false);
  writeBuildStringVec(outFiles.iddFactoryCxx.tempFile, "IddFileType", filetypes, false);

  // close out file
  outFiles.iddFactoryCxx.tempFile << '\n' << "} // openstudio" << '\n';

  // close out other IddFactory cxx files
  for (const std::shared_ptr<IddFactoryOutFile>& cxxFile : outFiles.iddFactoryIddFileCxxs) {
    cxxFile->tempFile << '\n' << "} // openstudio" << '\n';
  }

  outFiles.finalize();

  std::cout << "IddFactory files generated." << '\n';
}

IddFileFactoryData getFile(const std::string& fileName, const IddFileFactoryDataVector& iddFiles) {
  for (const IddFileFactoryData& idd : iddFiles) {
    if (idd.fileName() == fileName) {
      return idd;
    }
  }

  // unsuccessful search, throw an informative message
  std::stringstream ss;
  ss << "Unable to located included Idd file '" << fileName << "' in list of Idd files. " << "The available files are named:" << '\n';
  for (const IddFileFactoryData& idd : iddFiles) {
    ss << "  " << idd.fileName() << '\n';
  }
  throw std::runtime_error(ss.str().c_str());
}

}  // namespace openstudio
