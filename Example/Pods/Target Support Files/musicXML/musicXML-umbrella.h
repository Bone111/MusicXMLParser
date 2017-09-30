#ifdef __OBJC__
#import <UIKit/UIKit.h>
#else
#ifndef FOUNDATION_EXPORT
#if defined(__cplusplus)
#define FOUNDATION_EXPORT extern "C"
#else
#define FOUNDATION_EXPORT extern
#endif
#endif
#endif

#import "BleMidiParser.h"
#import "Connector.h"
#import "ConnectorViewController.h"
#import "UIImage+music.h"
#import "Constants.h"
#import "fmod.h"
#import "fmod_codec.h"
#import "fmod_common.h"
#import "fmod_dsp.h"
#import "fmod_dsp_effects.h"
#import "fmod_errors.h"
#import "fmod_ios.h"
#import "fmod_output.h"
#import "Log.h"
#import "AccidM.h"
#import "DrawableNoteM.h"
#import "DrawableProtocol.h"
#import "MeasureAttributeM.h"
#import "MeasureM.h"
#import "NoteM.h"
#import "PartM.h"
#import "RestM.h"
#import "ResultDetailM.h"
#import "ScoreM.h"
#import "musicXML.h"
#import "MidiPlayer.h"
#import "xml_midiFile.h"
#import "PianoView.h"
#import "ResultDetailView.h"
#import "ResultView.h"
#import "ScoreSettingView.h"
#import "ScoreSheet.h"
#import "ScoreViewController.h"
#import "SheetView.h"

FOUNDATION_EXPORT double musicXMLVersionNumber;
FOUNDATION_EXPORT const unsigned char musicXMLVersionString[];

