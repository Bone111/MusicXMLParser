// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../api/PrintData.h"
#include "../api/PositionData.h"
#include "../api/DurationData.h"
#include "../api/PitchData.h"
#include "../api/NoteAttachmentData.h"

#include <vector>


namespace mx
{
    namespace api
    {
    	enum class NoteType
    	{
    		normal,
    		grace,
    		cue
    	};

        enum class Beam
        {
            unspecified,
            begin,
            end,
            extend,
            forwardBroken,
            backwardBroken
        };
        
        enum class Stem
    	{
    		unspecified,
    		up,
    		down,
    		none,
            both
    	};

    	class NoteData
    	{
    	public:

            NoteData();
            
    		bool isRest;                        // if isRest is true then isUnpitched can be ignored
            bool isMeasureRest;                 // only valid if isRest is true
            bool isUnpitched;                   // only relevant if isRest is false
            bool isDisplayStepOctaveSpecified;  // MusicXML can optionally specify display step and octave for rests and unpitched notes
            
            // This does *not* indicate the presence of absence of a <chord> tag.  Instead isChord
            // denotes whether or not the note is a member of a chord.  This is translated from/to
            // MusicXML's <chord> usage rules (the first note of a chord does *not* have a <chord>
            // tag, but subsequent chord notes do have the tag).
            bool isChord;
            
            // This is separate from the tie curves themselves. This
            // states that the note should be tied but noteAttachment.curve
            // items are needed to draw the ties visibly
            bool isTieStart;
            bool isTieStop;
            
            NoteType noteType;            // normal, cue, grace
            PitchData pitchData;          // step, alter, octave, accidental, etc
            int userRequestedVoiceNumber;
            Stem stem;
            
            // the location of the note, timewise, within the measure
            // denominated in ticksPerQuarter as defined by ScoreData
            int tickTimePosition;
            DurationData durationData;
            
            std::vector<Beam> beams;
            PositionData positionData;
            PrintData printData;
            
            NoteAttachmentData noteAttachmentData;

            // these strings will be stuffed into the editorial <footnote> element
            // preceded by the string ##misc-data##. for example if you have the
            // strings Bob, Cat, Hello then we will get:
            // <footnote print-object="no">##misc-data##Bob,Cat,Hello</footnote>
            // similarly when parsing if we see ##misc-data## in this element, it
            // will be parsed into these strings. do not use commas in your misc
            // data strings as these are the delimiter
            std::vector<std::string> miscData;
    	};
        
        
        MXAPI_EQUALS_BEGIN( NoteData )
        MXAPI_EQUALS_MEMBER( isRest )
        MXAPI_EQUALS_MEMBER( isMeasureRest )
        MXAPI_EQUALS_MEMBER( isUnpitched )
        MXAPI_EQUALS_MEMBER( isDisplayStepOctaveSpecified )
        MXAPI_EQUALS_MEMBER( isChord )
        MXAPI_EQUALS_MEMBER( isTieStart )
        MXAPI_EQUALS_MEMBER( isTieStop )
        MXAPI_EQUALS_MEMBER( noteType )
        MXAPI_EQUALS_MEMBER( pitchData )
        MXAPI_EQUALS_MEMBER( userRequestedVoiceNumber )
        MXAPI_EQUALS_MEMBER( stem )
        MXAPI_EQUALS_MEMBER( tickTimePosition )
        MXAPI_EQUALS_MEMBER( durationData )
        MXAPI_EQUALS_MEMBER( beams )
        MXAPI_EQUALS_MEMBER( positionData )
        MXAPI_EQUALS_MEMBER( printData )
        MXAPI_EQUALS_MEMBER( noteAttachmentData )
        MXAPI_EQUALS_MEMBER( miscData )
        MXAPI_EQUALS_END;
        MXAPI_NOT_EQUALS_AND_VECTORS( NoteData );
    }
}
