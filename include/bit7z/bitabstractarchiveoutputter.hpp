/*
 * bit7z - A C++ static library to interface with the 7-zip shared libraries.
 * Copyright (c) 2025 Valery Khadanionak - All Rights Reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef BITABSTRACTARCHIVEOUTPUTTER_HPP
#define BITABSTRACTARCHIVEOUTPUTTER_HPP

#include "bitabstractarchiveoutput.hpp"

namespace bit7z
{

    /**
     * @brief The BitAbstractArchiveOutputter abstract class represents a generic archive outputter.
     */
    class BitAbstractArchiveOutputter
    {
    public:
        BitAbstractArchiveOutputter() = default;

        BitAbstractArchiveOutputter( const BitAbstractArchiveOutputter& ) = delete;

        BitAbstractArchiveOutputter( BitAbstractArchiveOutputter&& ) = delete;

        auto operator=( const BitAbstractArchiveOutputter& ) -> BitAbstractArchiveOutputter & = delete;

        auto operator=( BitAbstractArchiveOutputter&& ) -> BitAbstractArchiveOutputter & = delete;

        virtual ~BitAbstractArchiveOutputter() = default;

        /**
        * @return pointer to the archive output for the specified archive item
        */
        virtual auto GetOutput( uint32_t index, const tstring& path, BitAbstractArchiveOutput** ppOutput ) -> HRESULT = 0;

        /**
        * @brief Set operation result for current archive output
        */
        virtual void FinishOperation( bool success ) = 0;

        /**
        * @brief Release a pointer to the archive output obtained in a previous GetOutput call
        */
        virtual void ReleaseOutput() = 0;
    };

} // namespace bit7z
#endif // BITABSTRACTARCHIVEOUTPUTTER_HPP
