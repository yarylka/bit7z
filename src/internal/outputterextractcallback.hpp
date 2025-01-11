/*
 * bit7z - A C++ static library to interface with the 7-zip shared libraries.
 * Copyright (c) 2025 Valery Khadanionak - All Rights Reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef OUTPUTTEREXTRACTCALLBACK_HPP
#define OUTPUTTEREXTRACTCALLBACK_HPP

#include "internal/extractcallback.hpp"
#include "bitabstractarchiveoutputter.hpp"

namespace bit7z {

class OutputterExtractCallback final : public ExtractCallback {
    public:
        OutputterExtractCallback( const BitInputArchive& inputArchive,
                                  BitAbstractArchiveOutputter& outputter);

        OutputterExtractCallback( const OutputterExtractCallback& ) = delete;

        OutputterExtractCallback( OutputterExtractCallback&& ) = delete;

        auto operator=( const OutputterExtractCallback& )->OutputterExtractCallback & = delete;

        auto operator=( OutputterExtractCallback&& )->OutputterExtractCallback & = delete;

        ~OutputterExtractCallback() override = default;

    private:
        BitAbstractArchiveOutputter& m_outputter;
        CMyComPtr< ISequentialOutStream > m_outMemStream;

        void releaseStream() override;

        auto getOutStream( uint32_t index, ISequentialOutStream** outStream ) -> HRESULT override;
};

}  // namespace bit7z
#endif // OUTPUTTEREXTRACTCALLBACK_HPP
