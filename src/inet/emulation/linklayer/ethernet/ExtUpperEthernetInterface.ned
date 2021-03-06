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

package inet.emulation.linklayer.ethernet;

import inet.emulation.common.ExtInterface;
import inet.linklayer.contract.IEtherMac;
import inet.linklayer.contract.IEthernetInterface;

//
// This module provides an Ethernet network interface suitable for emulation.
// The upper part of the network interface is realized in the real world using
// a real TAP device of the host computer which is running the simulation.
//
module ExtUpperEthernetInterface extends ExtInterface like IEthernetInterface
{
    parameters:
        bool csmacdSupport = default(false);  // by default CSMA/CD is turned off, so only point-to-point duplex links are supported.
        double bitrate @unit(bps) = default(nan bps);
    gates:
        input cutthroughIn @loose;
        output cutthroughOut @loose;
        inout phys @labels(EtherFrame);
    submodules:
        tap: ExtEthernetTapDevice {
            parameters:
                @display("p=300,100");
        }
        mac: <default(csmacdSupport ? "EthernetCsmaMac" : "EthernetMac")> like IEtherMac {
            parameters:
                queue.packetCapacity = 10000;
                @display("p=300,200");
        }
    connections allowunconnected:
        tap.lowerLayerOut --> { @display("m=s"); } --> mac.upperLayerIn;
        tap.lowerLayerIn <-- { @display("m=s"); } <-- mac.upperLayerOut;
        mac.phys <--> { @display("m=s"); } <--> phys;
}

