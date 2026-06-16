/*
 * bit7z - A C++ static library to interface with the 7-zip shared libraries.
 * Copyright (c) 2025 Valery Khadanionak - All Rights Reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef BITABSTRACTARCHIVEOUTPUT_HPP
#define BITABSTRACTARCHIVEOUTPUT_HPP

namespace bit7z
{

    /**
     * @brief The BitAbstractArchiveOutput abstract class represents a generic archive output.
     */
    class BitAbstractArchiveOutput
    {
    public:
        virtual ~BitAbstractArchiveOutput() = default;

        /**
         * @return the output buffer to extract file.
         */
        BIT7Z_NODISCARD virtual auto GetBuffer() -> std::vector< byte_t >& = 0;
    };

} // namespace bit7z
#endif // BITABSTRACTARCHIVEOUTPUT_HPP
