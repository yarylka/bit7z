// This is an open source non - commercial project.Dear PVS - Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

/*
 * bit7z - A C++ static library to interface with the 7-zip shared libraries.
 * Copyright (c) 2025 Valery Khadanionak - All Rights Reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "internal/outputterextractcallback.hpp"
#include "internal/cbufferoutstream.hpp"
#include "internal/stringutil.hpp"
#include "internal/util.hpp"

using namespace std;
using namespace NWindows;

namespace bit7z {

OutputterExtractCallback::OutputterExtractCallback( const BitInputArchive& inputArchive,
                                                    BitAbstractArchiveOutputter& outputter)
    : ExtractCallback( inputArchive ),
      m_outputter( outputter ) {}

void OutputterExtractCallback::releaseStream() {
    m_outMemStream.Release();
    m_outputter.ReleaseOutput();
}

auto OutputterExtractCallback::finishOperation( OperationResult operationResult ) -> HRESULT {
    const HRESULT result = operationResult != OperationResult::Success ? E_FAIL : S_OK;
    if (m_outMemStream == nullptr ) {
        return result;
    }

    m_outputter.FinishOperation( result == S_OK );
    releaseStream();
    return result;
}

auto OutputterExtractCallback::getOutStream( uint32_t index, ISequentialOutStream** outStream ) -> HRESULT {
    if ( isItemFolder( index ) ) {
        return S_OK;
    }

    const BitPropVariant prop = itemProperty( index, BitProperty::Path );
    tstring fullPath;

    if ( prop.isEmpty() ) {
        fullPath = kEmptyFileAlias;
    }
    else if ( prop.isString() ) {
        if ( !mHandler.retainDirectories() ) {
            fullPath = path_to_tstring( fs::path{ prop.getNativeString() }.filename() );
        }
        else {
            fullPath = prop.getString();
        }
    } else {
        return E_FAIL;
    }

    if ( mHandler.fileCallback() ) {
        mHandler.fileCallback()( fullPath );
    }

    BitAbstractArchiveOutput* pOutput = nullptr;
    const HRESULT hr = m_outputter.GetOutput(index, fullPath, &pOutput);
    if ( hr != S_OK ) {
        return hr;
    }

    if ( pOutput == nullptr ) {
        return S_OK;
    }

    auto& outBuffer = pOutput->GetBuffer();
    outBuffer.clear();

    auto outStreamLoc = bit7z::make_com< CBufferOutStream, ISequentialOutStream >( outBuffer );
    m_outMemStream = outStreamLoc;
    *outStream = outStreamLoc.Detach();
    return S_OK;
}

} // namespace bit7z
