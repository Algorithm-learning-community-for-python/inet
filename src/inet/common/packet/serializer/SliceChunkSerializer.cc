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

#include "inet/common/packet/serializer/SliceChunkSerializer.h"

#include "inet/common/packet/chunk/SliceChunk.h"
#include "inet/common/packet/serializer/ChunkSerializerRegistry.h"

namespace inet {

Register_Serializer(SliceChunk, SliceChunkSerializer);

void SliceChunkSerializer::serialize(MemoryOutputStream& stream, const Ptr<const Chunk>& chunk, b offset, b length) const
{
    const auto& sliceChunk = staticPtrCast<const SliceChunk>(chunk);
    Chunk::serialize(stream, sliceChunk->getChunk(), sliceChunk->getOffset() + offset, length == b(-1) ? sliceChunk->getLength() - offset : length);
}

const Ptr<Chunk> SliceChunkSerializer::deserialize(MemoryInputStream& stream, const std::type_info& typeInfo) const
{
    throw cRuntimeError("Invalid operation");
}

} // namespace

