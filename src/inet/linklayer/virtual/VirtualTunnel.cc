//
// Copyright (C) 2020 OpenSim Ltd.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//


#include "inet/applications/common/SocketTag_m.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/packet/Packet.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include "inet/linklayer/common/VlanTag_m.h"
#include "inet/linklayer/virtual/VirtualTunnel.h"
#include "inet/networklayer/contract/IInterfaceTable.h"

namespace inet {

Define_Module(VirtualTunnel);

void VirtualTunnel::initialize(int stage)
{
    if (stage == INITSTAGE_LOCAL) {
        vlanId = par("vlanId");
        networkInterface = getContainingNicModule(this);
        const char *protocolAsString = par("protocol");
        if (*protocolAsString != '\0')
            protocol = Protocol::findProtocol(protocolAsString);
    }
    else if (stage == INITSTAGE_NETWORK_INTERFACE_CONFIGURATION) {
        auto interfaceTable = getModuleFromPar<IInterfaceTable>(par("interfaceTableModule"), this);
        realNetworkInterface = CHK(interfaceTable->findInterfaceByName(par("realInterface")));
        const char *addressString = par("address");
        MacAddress address;
        if (!strcmp(addressString, "auto"))
            address = MacAddress::generateAutoAddress();
        else if (!strcmp(addressString, "copy"))
            address = realNetworkInterface->getMacAddress();
        else
            address = MacAddress(addressString);
        networkInterface->setMacAddress(address);
        networkInterface->setInterfaceToken(address.formInterfaceIdentifier());
        networkInterface->setBroadcast(realNetworkInterface->isBroadcast());
        networkInterface->setMulticast(realNetworkInterface->isMulticast());
        networkInterface->setPointToPoint(realNetworkInterface->isPointToPoint());
    }
    else if (stage == INITSTAGE_LINK_LAYER) {
        // KLUDGE: depends on other interface
        if (!strcmp(par("address"), "copy"))
            networkInterface->setMacAddress(realNetworkInterface->getMacAddress());
        socket.setCallback(this);
        socket.setOutputGate(gate("upperLayerOut"));
        socket.setNetworkInterface(realNetworkInterface);
        socket.bind(networkInterface->getMacAddress(), MacAddress(), nullptr, vlanId);
    }
}

void VirtualTunnel::handleMessage(cMessage *message)
{
    if (socket.belongsToSocket(message))
        socket.processMessage(message);
    else {
        auto packet = check_and_cast<Packet *>(message);
        if (vlanId != -1)
            packet->addTagIfAbsent<VlanReq>()->setVlanId(vlanId);
        if (protocol != nullptr)
            packet->addTagIfAbsent<DispatchProtocolReq>()->setProtocol(protocol);
        socket.send(packet);
    }
}

void VirtualTunnel::socketDataArrived(EthernetSocket *socket, Packet *packet)
{
    packet->removeTag<SocketInd>();
    packet->getTagForUpdate<InterfaceInd>()->setInterfaceId(networkInterface->getInterfaceId());
    send(packet, "upperLayerOut");
}

void VirtualTunnel::socketErrorArrived(EthernetSocket *socket, Indication *indication)
{
    throw cRuntimeError("Invalid operation");
}

} // namespace inet
