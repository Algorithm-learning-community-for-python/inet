//
// Copyright (C) 2014 OpenSim Ltd.
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

#ifndef __INET_ILAYEREDERRORMODEL_H
#define __INET_ILAYEREDERRORMODEL_H

#include "inet/physicallayer/wireless/common/analogmodel/bitlevel/LayeredTransmission.h"
#include "inet/physicallayer/wireless/common/contract/packetlevel/ISnir.h"

namespace inet {

namespace physicallayer {

/**
 * The layered error model computes the erroneous bits, symbols, or samples
 * based on the SNIR and a simplified model of the signal processing.
 */
class INET_API ILayeredErrorModel : public IPrintableObject
{
  public:
    /**
     * Computes the packet domain representation at the receiver using a simplified
     * model for the underlying domains. This result includes all potential
     * errors that were not corrected by the underlying domains.
     */
    virtual const IReceptionPacketModel *computePacketModel(const LayeredTransmission *transmission, const ISnir *snir) const = 0;

    /**
     * Computes the bit domain representation at the receiver using a simplified
     * model for the underlying domains. This result includes all potential
     * errors that were not corrected by the underlying domains.
     */
    virtual const IReceptionBitModel *computeBitModel(const LayeredTransmission *transmission, const ISnir *snir) const = 0;

    /**
     * Computes the symbol domain representation at the receiver using a simplified
     * model for the underlying domains. This result includes all potential
     * errors that were not corrected by the underlying domains.
     */
    virtual const IReceptionSymbolModel *computeSymbolModel(const LayeredTransmission *transmission, const ISnir *snir) const = 0;

    /**
     * Computes the sample domain representation at the receiver using a simplified
     * model for the underlying domains. This result includes all potential
     * errors that were not corrected by the underlying domains.
     */
    virtual const IReceptionSampleModel *computeSampleModel(const LayeredTransmission *transmission, const ISnir *snir) const = 0;
};

} // namespace physicallayer

} // namespace inet

#endif

