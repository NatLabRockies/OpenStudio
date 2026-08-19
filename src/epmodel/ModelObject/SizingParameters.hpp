/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SIZINGPARAMETERS_HPP
#define EPMODEL_SIZINGPARAMETERS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SizingParameters_Impl;
  }

  /** \brief SizingParameters.
   *
   * \par EnergyPlus object
   * \epobject{group-design-objects.html#sizingparameters,Sizing:Parameters}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::SizingParameters</code>. The heating factor, cooling factor, and averaging-window fields map directly to EnergyPlus.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API SizingParameters : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~SizingParameters() override = default;
    SizingParameters(const SizingParameters& other) = default;
    SizingParameters(SizingParameters&& other) = default;
    SizingParameters& operator=(const SizingParameters&) = default;
    SizingParameters& operator=(SizingParameters&&) = default;

    static IddObjectType iddObjectType();
    double heatingSizingFactor() const;
    bool isHeatingSizingFactorDefaulted() const;
    bool setHeatingSizingFactor(double heatingSizingFactor);
    void resetHeatingSizingFactor();

    double coolingSizingFactor() const;
    bool isCoolingSizingFactorDefaulted() const;
    bool setCoolingSizingFactor(double coolingSizingFactor);
    void resetCoolingSizingFactor();

    boost::optional<int> timestepsinAveragingWindow() const;
    bool setTimestepsinAveragingWindow(int timestepsinAveragingWindow);
    void resetTimestepsinAveragingWindow();

   protected:
    explicit SizingParameters(const Model& model);

    using ImplType = detail::SizingParameters_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SizingParameters(std::shared_ptr<detail::SizingParameters_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
