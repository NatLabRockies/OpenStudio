/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTDOORAIRMIXER_IMPL_HPP
#define EPMODEL_OUTDOORAIRMIXER_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  class Node;

  namespace detail {

    class EPMODEL_API OutdoorAirMixer_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~OutdoorAirMixer_Impl() override = default;

      boost::optional<openstudio::epmodel::Node> mixedAirNode() const;
      boost::optional<openstudio::epmodel::Node> outdoorAirNode() const;
      boost::optional<openstudio::epmodel::Node> reliefAirNode() const;
      boost::optional<openstudio::epmodel::Node> returnAirNode() const;

      bool setMixedAirNode(const openstudio::epmodel::Node& node);
      bool setOutdoorAirNode(const openstudio::epmodel::Node& node);
      bool setReliefAirNode(const openstudio::epmodel::Node& node);
      bool setReturnAirNode(const openstudio::epmodel::Node& node);

     protected:
      void doCanonicalize(LoadContext& context) override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
