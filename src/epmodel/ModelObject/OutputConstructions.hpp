/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTCONSTRUCTIONS_HPP
#define EPMODEL_OUTPUTCONSTRUCTIONS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class OutputConstructions_Impl;
  }

  /** \brief OutputConstructions.
   *
   * \par EnergyPlus object
   * \epobject{input-for-output.html#outputconstructions,Output:Constructions}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::OutputConstructions</code>. The two report switches map directly to the EnergyPlus Details Type fields.
   *
   * \par Known limitations
   * Only the fields and relationships listed in this wrapper are available; broader Model-only helpers are not exposed.
   */
  class EPMODEL_API OutputConstructions : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~OutputConstructions() override = default;
    OutputConstructions(const OutputConstructions& other) = default;
    OutputConstructions(OutputConstructions&& other) = default;
    OutputConstructions& operator=(const OutputConstructions&) = default;
    OutputConstructions& operator=(OutputConstructions&&) = default;

    static IddObjectType iddObjectType();
    bool reportConstructions() const;
    bool setReportConstructions(bool reportConstructions);

    bool reportMaterials() const;
    bool setReportMaterials(bool reportMaterials);

   protected:
    explicit OutputConstructions(const Model& model);

    using ImplType = detail::OutputConstructions_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit OutputConstructions(std::shared_ptr<detail::OutputConstructions_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
