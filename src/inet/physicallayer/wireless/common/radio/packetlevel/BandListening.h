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

#ifndef __INET_BANDLISTENING_H
#define __INET_BANDLISTENING_H

#include "inet/common/Units.h"
#include "inet/physicallayer/wireless/common/base/packetlevel/ListeningBase.h"

namespace inet {
namespace physicallayer {

using namespace inet::units::values;

class INET_API BandListening : public ListeningBase
{
  protected:
    const Hz centerFrequency;
    const Hz bandwidth;

  public:
    BandListening(const IRadio *radio, simtime_t startTime, simtime_t endTime, Coord startPosition, Coord endPosition, Hz centerFrequency, Hz bandwidth);

    virtual std::ostream& printToStream(std::ostream& stream, int level, int evFlags = 0) const override;

    virtual Hz getCenterFrequency() const { return centerFrequency; }
    virtual Hz getBandwidth() const { return bandwidth; }
};

} // namespace physicallayer
} // namespace inet

#endif

