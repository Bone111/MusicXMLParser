// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once
#include "../utility/Throw.h"

#define MX_THROW_XNULL MX_THROW( "The internal object is null. This probably means that XDoc has gone out of scope causing all of its children to be destroyed." );
