//
// Copyright (C) 2013 OpenSim Ltd.
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

#ifndef __INET_TCPSEGMENTTRANSMITINFOLIST_H
#define __INET_TCPSEGMENTTRANSMITINFOLIST_H

#include "inet/transportlayer/tcp/flavours/TcpBaseAlg.h"

namespace inet {

namespace tcp {

class INET_API TcpSegmentTransmitInfoList
{
  public:
    class Item {
      protected:
        uint32_t beg; // segment [begin, end)
        uint32_t end;
        simtime_t firstSentTime; // time of first sending
        simtime_t lastSentTime; // time of last sending
        int transmitCount; // num of transmissions

      public:
        Item(uint32_t beg, uint32_t end, simtime_t firstTime, simtime_t lastTime, int transmits) : beg(beg), end(end), firstSentTime(firstTime), lastSentTime(lastTime), transmitCount(transmits) {}
        uint32_t getBeg() const { return beg; }
        uint32_t getEnd() const { return end; }
        simtime_t getFirstSentTime() const { return firstSentTime; }
        simtime_t getLastSentTime() const { return lastSentTime; }
        int getTransmitCount() const { return transmitCount; }

        friend class TcpSegmentTransmitInfoList;
    };
    typedef std::list<Item> TcpSegmentTransmitInfoItems;
    TcpSegmentTransmitInfoItems regions; // region[i].end == region[i+1].beg

  public:
    void set(uint32_t beg, uint32_t end, simtime_t sentTime); // [beg,end)

    /// returns pointer to Item, or nullptr if not found
    const Item *get(uint32_t seq) const;

    void clearTo(uint32_t endseg);
};

} // namespace tcp

} // namespace inet

#endif

