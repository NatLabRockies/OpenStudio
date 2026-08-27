/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULEFILE_HPP
#define EPMODEL_SCHEDULEFILE_HPP

#include "EPModelAPI.hpp"
#include "Schedule/Schedule.hpp"
#include "../../utilities/core/Path.hpp"
#include "../../utilities/filetypes/CSVFile.hpp"
#include <utilities/core/Deprecated.hpp>

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {

namespace epmodel {

  class Model;

  namespace detail {
    class ScheduleFile_Impl;
  }

  /** \brief Reads schedule values from an external text file.
   *
   * \par EnergyPlus object
   * \epobject{group-schedules.html#schedulefile,Schedule:File}
   *
   * \par Important behavior
   * The string overload of <code>setMinutesperItem()</code> returns false for
   * text that is not an integer.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::ScheduleFile</code>.
   *
   * - <b>Not yet available:</b> The constructors that accept an
   *   <code>ExternalFile</code> or a file path.
   * - <b>Not yet available:</b> <code>externalFile()</code>,
   *   <code>csvFile()</code>, <code>translatedFilePath()</code>, and the
   *   <code>translateFileWithRelativePath()</code> getter, default query,
   *   setter, and reset methods.
   * - <b>Changed:</b> <code>setMinutesperItem(const std::string&)</code> is
   *   deprecated in OpenStudio Model but is not marked deprecated in EPModel.
   *
   * \par Known limitations
   * EPModel does not provide a typed file/path relationship for this object.
   * Callers can edit the EnergyPlus scalar fields, but must use lower-level
   * object access to supply or inspect the <code>File Name</code> field.
   */
  class EPMODEL_API ScheduleFile : public Schedule
  {
   public:
    // explicit ScheduleFile(const ExternalFile& externalfile, int column = 1, int rowsToSkip = 0); // FIXME: how do we maintain this?
    explicit ScheduleFile(const Model& model, int column = 1, int rowsToSkip = 0); // new ctor
    explicit ScheduleFile(const Model& model, const openstudio::path& filePath, int column = 1, int rowsToSkip = 0, bool translateFileWithRelativePath = false); // old ctor

    virtual ~ScheduleFile() override = default;
    ScheduleFile(const ScheduleFile& other) = default;
    ScheduleFile(ScheduleFile&& other) = default;
    ScheduleFile& operator=(const ScheduleFile&) = default;
    ScheduleFile& operator=(ScheduleFile&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> columnSeparatorValues();
    static std::vector<std::string> minutesperItemValues();

    std::string fileName() const;
    bool setFileName(std::string fileName);

    int columnNumber() const;
    bool setColumnNumber(int columnNumber);

    int rowstoSkipatTop() const;
    bool setRowstoSkipatTop(int rowstoSkipatTop);

    boost::optional<int> numberofHoursofData() const;
    bool isNumberofHoursofDataDefaulted() const;
    bool setNumberofHoursofData(int numberofHours);

    std::string columnSeparator() const;
    bool isColumnSeparatorDefaulted() const;
    bool setColumnSeparator(const std::string& columnSeparator);
    void resetColumnSeparator();

    bool interpolatetoTimestep() const;
    bool isInterpolatetoTimestepDefaulted() const;
    bool setInterpolatetoTimestep(bool interpolatetoTimestep);
    void resetInterpolatetoTimestep();

    int minutesperItem() const;
    bool isMinutesperItemDefaulted() const;
    bool setMinutesperItem(const std::string& minutesperItem);
    bool setMinutesperItem(int minutesperItem);
    void resetMinutesperItem();

    bool adjustScheduleforDaylightSavings() const;
    bool isAdjustScheduleforDaylightSavingsDefaulted() const;
    bool setAdjustScheduleforDaylightSavings(bool adjustScheduleforDaylightSavings);
    void resetAdjustScheduleforDaylightSavings();

    openstudio::TimeSeries timeSeries() const;
    static boost::optional<ScheduleFile> fromTimeSeries(const openstudio::TimeSeries& timeSeries, Model& model);

    // Extra setters/getters
    boost::optional<CSVFile> csvFile() const;
    OS_DEPRECATED(4, 0, 0) bool translateFileWithRelativePath() const;
    OS_DEPRECATED(4, 0, 0) bool isTranslateFileWithRelativePathDefaulted() const;
    OS_DEPRECATED(4, 0, 0) bool setTranslateFileWithRelativePath(bool translateFileWithRelativePath);
    OS_DEPRECATED(4, 0, 0) void resetTranslateFileWithRelativePath();
    openstudio::path translatedFilePath() const;

   protected:
    using ImplType = detail::ScheduleFile_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ScheduleFile(std::shared_ptr<detail::ScheduleFile_Impl> impl);

   private:
    REGISTER_LOGGER("openstudio.epmodel.ScheduleFile");
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
