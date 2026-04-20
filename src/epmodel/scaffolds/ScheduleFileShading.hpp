/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULEFILESHADING_HPP
#define EPMODEL_SCHEDULEFILESHADING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ScheduleFileShading_Impl;
  }

  class EPMODEL_API ScheduleFileShading : public ModelObject
  {
   public:
    explicit ScheduleFileShading(const Model& model);

    virtual ~ScheduleFileShading() override = default;
    ScheduleFileShading(const ScheduleFileShading& other) = default;
    ScheduleFileShading(ScheduleFileShading&& other) = default;
    ScheduleFileShading& operator=(const ScheduleFileShading&) = default;
    ScheduleFileShading& operator=(ScheduleFileShading&&) = default;

    static IddObjectType iddObjectType();

    /** @name File Name field accessors
   *  Schema Alignment Notes:
   *  - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
   *  - Field Mapping: fileName maps directly to EnergyPlus Schedule:File:Shading field File Name.
   *  - TODO(parity): Revisit API layering only if future model-counterpart parity is introduced.
   */
    //@{
    std::string fileName() const;
    bool setFileName(const std::string& fileName);
    //@}

   protected:
    using ImplType = detail::ScheduleFileShading_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ScheduleFileShading(std::shared_ptr<detail::ScheduleFileShading_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
