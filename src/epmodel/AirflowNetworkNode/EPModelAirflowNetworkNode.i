#ifndef EPMODEL_AirflowNetworkNode_I
#define EPMODEL_AirflowNetworkNode_I

#ifdef SWIGPYTHON
  %module openstudioepmodelairflownetworknode
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

EPMODELOBJECT_WRAP(AirflowNetworkDistributionNode, <epmodel/AirflowNetworkNode/AirflowNetworkDistributionNode.hpp>, 0, 1)

#endif
