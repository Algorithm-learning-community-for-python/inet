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

package inet.tutorials.protocol;

import inet.protocolelement.acknowledgement.Resending;
import inet.protocolelement.checksum.FcsHeaderChecker;
import inet.protocolelement.checksum.FcsHeaderInserter;
import inet.protocolelement.common.InterpacketGapInserter;
import inet.protocolelement.ordering.Reordering;
import inet.protocolelement.ordering.SequenceNumbering;
import inet.protocolelement.transceiver.PacketReceiver;
import inet.protocolelement.transceiver.PacketTransmitter;
import inet.queueing.queue.PacketQueue;
import inet.queueing.server.InstantServer;
import inet.queueing.sink.PassivePacketSink;
import inet.queueing.source.ActivePacketSource;

module ClientHost7
{
    parameters:
        @display("i=device/pc");
    gates:
        output out;
    submodules:
        app: ActivePacketSource {
            @display("p=150,100");
        }
        queue: PacketQueue {
            @display("p=150,200");
        }
        server: InstantServer {
            @display("p=150,300");
        }
        sequenceNumbering: SequenceNumbering {
            @display("p=150,400");
        }
        resending: Resending {
            @display("p=150,500");
        }
        fcsInserter: FcsHeaderInserter {
            @display("p=150,600");
        }
        InterpacketGapInserter: InterpacketGapInserter {
            @display("p=150,700");
        }
        transmitter: PacketTransmitter {
            @display("p=150,800");
        }
    connections:
        app.out --> queue.in;
        queue.out --> server.in;
        server.out --> sequenceNumbering.in;
        sequenceNumbering.out --> resending.in;
        resending.out --> fcsInserter.in;
        fcsInserter.out --> InterpacketGapInserter.in;
        InterpacketGapInserter.out --> transmitter.in;
        transmitter.out --> out;
}

module ServerHost7
{
    parameters:
        @display("i=device/pc");
    gates:
        input in;
    submodules:
        app: PassivePacketSink {
            @display("p=150,100");
        }
        reordering: Reordering {
            @display("p=150,200");
        }
        fcsChecker: FcsHeaderChecker {
            @display("p=150,300");
        }
        receiver: PacketReceiver {
            @display("p=150,400");
        }
    connections:
        in --> receiver.in;
        receiver.out --> fcsChecker.in;
        fcsChecker.out --> reordering.in;
        reordering.out --> app.in;
}

network Network7
{
    submodules:
        client: ClientHost7 {
            @display("p=100,100");
        }
        server: ServerHost7 {
            @display("p=200,100");
        }
    connections allowunconnected:
        client.out --> { delay = 1us; ber = 1E-5; } --> server.in;
}
