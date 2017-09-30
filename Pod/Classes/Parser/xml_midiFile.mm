//
//  xml_midiFile.m
//  iOSMusic
//
//  Created by tanhui on 2017/7/10.
//  Copyright © 2017年 tanhui. All rights reserved.
//

#import "xml_midiFile.h"

#include "../../musicFramework/xml/XDoc.h"
#include "../../musicFramework/api/ApiCommon.h"
#include "../../musicFramework/api/ApiCommon.h"
#include "../../musicFramework/core/Document.h"
#include "../../musicFramework/core/Elements.h"
#include "../../musicFramework/core/Strings.h"
#include "../../musicFramework/utility/Utility.h"
#include "../../musicFramework/xml/XFactory.h"
#include "../../musicFramework/core/Elements.h"

//#include <MusicFramwork/xml/XDoc.h>
//#include <MusicFramwork/api/ApiCommon.h>
//#include <MusicFramwork/api/ApiCommon.h>
//#include <MusicFramwork/core/Document.h>
//#include <MusicFramwork/core/Elements.h>
//#include <MusicFramwork/core/Strings.h>
//#include <MusicFramwork/utility/Utility.h>
//#include <MusicFramwork/xml/XFactory.h>
//#include <MusicFramwork/core/Elements.h>
#include <stdio.h>
#import "PartM.h"
#import "MeasureM.h"

#import "NoteM.h"
#import "MeasureAttributeM.h"
#import "Constants.h"
#import "RestM.h"
#import "AccidM.h"

using namespace std;
using namespace mx::core;

@interface xml_midiFile () 
@property(nonatomic, strong) NSString* path;
@property(nonatomic, assign) NSInteger mTempo;


@end

@implementation xml_midiFile
-(id)initWithFile:(NSString*)path{
    if ([super init]) {
        self.path = path;
        self.mTempo = 120;
        self.mScore = [self parseXml];
        
    }
    return self;
}



-(NSMutableArray*)parseScorePartMeasures:(PartwisePartPtr)partwise staff:(int*)staff{
    NSMutableArray* measures= @[].mutableCopy;
    // 每个part最新的clef
//    int* partClefArr = new int[10];
    NSMutableDictionary* partClefs = @{}.mutableCopy;
    // 每个part指定一个divisions
    NSInteger divisions = 0;
    
    double currentStartTime = 1;
    
    for (auto measure_it = partwise->getPartwiseMeasureSet().cbegin(); measure_it != partwise->getPartwiseMeasureSet().cend(); measure_it++) {
        MeasureAttributesPtr attributes = (*measure_it)->getAttributes();
        MusicDataChoiceSet groupSetPtr = (*measure_it)->getMusicDataGroup()->getMusicDataChoiceSet();
        auto width = attributes->width.getValue();
        NSMutableArray* dataChoices = @[].mutableCopy;
        
        double measureStartTime = currentStartTime;
        
        NoteGroupM* noteGroup = [[NoteGroupM alloc]init];
        
        // 解析measure 中的 note
        for (auto choice_it = groupSetPtr.cbegin() ; choice_it != groupSetPtr.cend() ; choice_it ++) {
            
            auto choiceType = (*choice_it)->getChoice();
            if (choiceType == MusicDataChoice::Choice::properties) {
                auto choiceMeasureAttr = (*choice_it)->getProperties();
                EKeyMode mode_ = EKeyMode::EKeyMode_NONE;
                NSNumber *mBeates = nil , *mBeateType = nil ,*fifth_ = nil;
                
                MeasureKeyM* keyM = nil;
                MeasureTimeM* timeM = nil;
                // 获取divisions
                if (choiceMeasureAttr->getHasDivisions()){
                    divisions = choiceMeasureAttr->getDivisions()->getValue().getValue();
                }
                
                if (choiceMeasureAttr->getHasStaves()) {
                    *staff = choiceMeasureAttr->getStaves()->getValue().getValue();
                }
                if (choiceMeasureAttr->getTimeSet().size()){
                    TimePtr time  = *(choiceMeasureAttr->getTimeSet().cbegin());
                    TimeChoice::Choice choice = time->getTimeChoice()->getChoice();
                    if (!(int)choice){
                        TimeSignatureGroupPtr timeSignaturePtr = *(time->getTimeChoice()->getTimeSignatureGroupSet().cbegin());
                        std::string beats = timeSignaturePtr->getBeats()->getValue().getValue();
                        auto beat_types = timeSignaturePtr->getBeatType()->getValue().getValue();
                        NSString *oc_beat = [NSString stringWithCString:beats.c_str() encoding:[NSString defaultCStringEncoding]];
                        NSString *oc_beat_type =[NSString stringWithCString:beat_types.c_str() encoding:[NSString defaultCStringEncoding]];
                        mBeates = @([oc_beat intValue]);
                        mBeateType = @([oc_beat_type intValue]);
                        
                        timeM = [[MeasureTimeM alloc ]init];
                        timeM.mBeates = mBeates;
                        timeM.mBeateType = mBeateType;
                        
                    }
                }
                
                if (choiceMeasureAttr->getKeySet().size()) {
                    KeyPtr keyPtr = *(choiceMeasureAttr->getKeySet().cbegin());
                    auto fifth = keyPtr->getKeyChoice()->getTraditionalKey()->getFifths()->getValue().getValue();
                    auto mode = keyPtr->getKeyChoice()->getTraditionalKey()->getMode()->getValue().getValue();
                    fifth_ = @((int)fifth);
                    mode_ = (EKeyMode)mode;
                    keyM = [[MeasureKeyM alloc]initWithFifth:fifth_ mode:mode_];
                }
                
                // 遍历添加clef
                if (choiceMeasureAttr->getClefSet().size()) {
                    int i = 0;
                    for (auto clef_it = choiceMeasureAttr->getClefSet().cbegin();i<choiceMeasureAttr->getClefSet().size() && clef_it != choiceMeasureAttr->getClefSet().cend(); clef_it++ ,i++) {
                        MeasureAttributeM * attr = [[MeasureAttributeM alloc]init];
                        
                        ClefPtr clefPtr  = *clef_it;
                        int line = clefPtr->getLine()->getValue().getValue();
                        auto sign = clefPtr->getSign()->getValue();
                        NSInteger number = 1;
                        if (clefPtr->getAttributes()->hasNumber) {
                            number = clefPtr->getAttributes()->number.getValue();
                        }
                        EClef clef = EClef::EClef_None;
                        if (sign == ClefSign::g && line == 2) {
                            clef = EClef::EClef_TREBLE;
                        }else if (sign == ClefSign::f && line == 4){
                            clef = EClef::EClef_BASS;
                        }else{
                            NSAssert(FALSE, @"unsupported format");
                        }
                        
                        
                        ClefM * clefM = [[ClefM alloc]init];
                        clefM.mValue = clef;
                        
                        attr.mClef = clefM;
                        attr.mKey = keyM;
                        attr.mTime = timeM;
                        attr.mStaffth = number;
                        
                        // 设置measureStartTime
                        attr.mStartTime = currentStartTime - 1;
                        attr.mDuration = 0;
                        if (clefM){
                            attr.mDuration += DivisionUnit;
                        }
                        if (keyM){
                            attr.mDuration += DivisionUnit;
                        }
                        if (timeM){
                            attr.mDuration += 15;
                        }
                        attr.mPrevious = [partClefs objectForKey:@(number)];
                        [partClefs setObject:attr forKey:@(number)];
                        [dataChoices addObject:attr];
                    }
                }
                
                
            }else if (choiceType == MusicDataChoice::Choice::note){
                
                NoteM* noteM = [[NoteM alloc] init];
                auto choiceNote = (*choice_it)->getNote();
                
                auto normalChoice =  choiceNote->getNoteChoice()->getChoice();
                // 过滤 grace cur
                if (normalChoice != NoteChoice::Choice::normal){
                    continue;
                }
                
                auto noteTypeChoice =  choiceNote->getNoteChoice()->getNormalNoteGroup()->getFullNoteGroup()->getFullNoteTypeChoice()->getChoice();
                
                noteM.mChoice = (ENoteChoice)noteTypeChoice;
                
                if (choiceNote->getHasType()){
                    auto type = choiceNote->getType()->getValue();
                    noteM.mType = (ENoteType)type;
                }else if (choiceNote->getNoteChoice()->getNormalNoteGroup()->getFullNoteGroup()->getFullNoteTypeChoice()->getRest()->getAttributes()->measure == YesNo::yes){
                    noteM.mType = ENoteType::ENoteType_WHOLE;
                }else {
                    noteM.mType = ENoteType::ENoteType_None;
                }
                
                if(choiceNote->getHasNotehead()){
                    auto headType= choiceNote->getNotehead()->getValue();
                    noteM.mNoteHeadType = (ENoteHeadType)headType;
                }
                
                auto stem = choiceNote->getStem()->getValue();
                noteM.mStem = (ENoteStem)stem;
                if(choiceNote->getHasStaff()){
                    noteM.mStaffth = (NSInteger)choiceNote->getStaff()->getValue().getValue();
                }else{
                    noteM.mStaffth = 1;
                }
                if (choiceNote->getDotSet().size()){
                    noteM.mDotNum = choiceNote->getDotSet().size();
                }
                if (noteTypeChoice == FullNoteTypeChoice::Choice::pitch){
                    
                    auto pitch = choiceNote->getNoteChoice()->getNormalNoteGroup()->getFullNoteGroup()->getFullNoteTypeChoice()->getPitch();
                    auto step = pitch->getStep()->getValue();
                    auto actave = pitch->getOctave()->getValue().getValue();
                    noteM.mStep = (ENoteStep)(((int)step + 5)%7);
                    noteM.mOctave = (int)actave;
                    
                    auto duration = choiceNote->getNoteChoice()->getNormalNoteGroup()->getDuration()->getValue().getValue();
                    
                    // 处理accident
                    if (choiceNote->getHasAccidental()){
                        auto accidentValue = choiceNote->getAccidental()->getValue();
                        noteM.mAccid = (EAccidType)accidentValue;
                    }else {
                        noteM.mAccid = (EAccidType)EAccidType_None;
                    }
                    
                    noteM.mDuration = (duration * DivisionUnit / divisions) ;
                    // 添加noteGroup , if chord == true 加到上一个group
                    if (choiceNote->getNoteChoice()->getNormalNoteGroup()->getFullNoteGroup()->getHasChord()){
                        [noteGroup addNote:noteM];
                    }else {
                        noteGroup = [[NoteGroupM alloc]initWithNotes:@[noteM].mutableCopy];
                        // 设置notegroup 的 starttime
                        noteGroup.mStartTime = noteM.mStartTime = currentStartTime;
                        currentStartTime = currentStartTime + noteM.mDuration;
                        [dataChoices addObject:noteGroup];
                    }
                    
                    MeasureAttributeM* attr = [partClefs objectForKey:@(noteM.mStaffth)];
                    if(noteGroup.mStartTime < attr.mStartTime){
                        noteGroup.mCurrentAttr = noteM.mCurrentAttr = attr.mPrevious;
                    }else{
                        noteGroup.mCurrentAttr = noteM.mCurrentAttr = attr;
                    }
                    noteGroup.mDuration = noteM.mDuration  ;
                    noteGroup.mStaffth = noteM.mStaffth;
                    noteGroup.mStem = noteM.mStem;
                    noteGroup.mType = noteM.mType;
                    
                    // 解析beams
                    if (choiceNote->getBeamSet().size()) {
                        NSMutableArray* beamsArr = @[].mutableCopy;
                        int index = 1;
                        for (auto beam_it = choiceNote->getBeamSet().cbegin(); beam_it != choiceNote->getBeamSet().cend(); beam_it++,index++) {
                            BeamM* beamM = [[BeamM alloc]init];
                            auto beamValue = (int)(*beam_it)->getValue();
                            beamM.mValue = (EBeamType)beamValue;
                            beamM.mNumber = index;
                            [beamsArr addObject:beamM];
                        }
                        noteGroup.mBeams = beamsArr;
                    }
                    
                    // 解析notations 弧线
                    if (choiceNote->getNotationsSet().size()){
                        NSMutableArray* notationArr = @[].mutableCopy;
                        int index = 1;
                        for (auto notation_it = choiceNote->getNotationsSet().cbegin(); notation_it != choiceNote->getNotationsSet().cend(); notation_it++,index++) {
                            for (auto notationChoice_it = (*notation_it)->getNotationsChoiceSet().cbegin(); notationChoice_it !=(*notation_it)->getNotationsChoiceSet().cend();notationChoice_it++ ) {
                                // tie 和 slur 一起处理
                                if ((*notationChoice_it)->getChoice() == NotationsChoice::Choice::slur){
                                    auto slurPtr = (*notationChoice_it)->getSlur();
                                    ENotationType type = (ENotationType)slurPtr->getAttributes()->type;
                                    int number = slurPtr->getAttributes()->number.getValue();
                                    ENotationPlacement placement = ENotationPlacement::ENotationPlacement_Above;
                                    if(slurPtr->getAttributes()->hasPlacement){
                                        placement = (ENotationPlacement)slurPtr->getAttributes()->placement;
                                    }else if(slurPtr->getAttributes()->hasOrientation){
                                        placement = (ENotationPlacement)slurPtr->getAttributes()->orientation;
                                    }
                                    NotationM* notationM = [[NotationM alloc]initWithType:type number:number placement:placement];
                                    notationM.mChoice = ENotationChioce::ENotationChioce_Slur;
                                    [notationArr addObject:notationM];
                                }
                                if ((*notationChoice_it)->getChoice() == NotationsChoice::Choice::tied) {
                                    auto tiePtr = (*notationChoice_it)->getTied();
                                    ENotationType type = (ENotationType)tiePtr->getAttributes()->type;
                                    int number = tiePtr->getAttributes()->number.getValue();
                                    ENotationPlacement placement = ENotationPlacement::ENotationPlacement_Above;
                                    if(tiePtr->getAttributes()->hasPlacement){
                                        placement = (ENotationPlacement)tiePtr->getAttributes()->placement;
                                    }else if(tiePtr->getAttributes()->hasOrientation){
                                        placement = (ENotationPlacement)tiePtr->getAttributes()->orientation;
                                    }
                                    NotationM* notationM = [[NotationM alloc]initWithType:type number:number placement:placement];
                                    notationM.mChoice = ENotationChioce::ENotationChioce_Tie;
                                    [notationArr addObject:notationM];
                                }
                            }
                        }
                        noteGroup.mNotations = notationArr;
                    }
                    
                }else if (noteTypeChoice == FullNoteTypeChoice::Choice::rest){
                    // 类型为rest
                    RestM* rest = [[RestM alloc]init];
                    if (choiceNote->getHasType()){
                        auto type = choiceNote->getType()->getValue();
                        rest.mType = (ENoteType)type;
                    }else if (choiceNote->getNoteChoice()->getNormalNoteGroup()->getFullNoteGroup()->getFullNoteTypeChoice()->getRest()->getAttributes()->measure == YesNo::yes){
                        rest.mType = ENoteType::ENoteType_WHOLE;
                        rest.mHasMeasure = YES;
                    }else {
                        rest.mType = ENoteType::ENoteType_None;
                        rest.mHasMeasure = NO;
                    }
                    if(choiceNote->getHasStaff()){
                        rest.mStaffth = (NSInteger)choiceNote->getStaff()->getValue().getValue();
                    }else{
                        rest.mStaffth = 1;
                    }
                    auto duration = choiceNote->getNoteChoice()->getNormalNoteGroup()->getDuration()->getValue().getValue();
                    MeasureAttributeM* attr = [partClefs objectForKey:@(noteM.mStaffth)];
                    rest.mCurrentAttr = attr;
                    rest.mDuration = (duration * DivisionUnit / divisions) ;
                    // 设置rest 的startTime
                    rest.mStartTime =  currentStartTime;
                    currentStartTime = currentStartTime + rest.mDuration;
                    [dataChoices addObject:rest];
                }
            }else if (choiceType == MusicDataChoice::Choice::backup){
                BackupM* backup = [[BackupM alloc]init];
                auto choiceBackDuration = (*choice_it)->getBackup()->getDuration()->getValue().getValue();
                backup.mDuration = (choiceBackDuration * DivisionUnit / divisions);
                currentStartTime -= [backup mDuration];
//                backup.mStartTime = currentStartTime;
                [dataChoices addObject:backup];
            }else if (choiceType == MusicDataChoice::Choice::forward){
                ForwardM* forward = [[ForwardM alloc]init];
                auto choiceForwardDuration = (*choice_it)->getForward()->getDuration()->getValue().getValue();
                forward.mDuration = (choiceForwardDuration * DivisionUnit / divisions);
                forward.mStartTime = currentStartTime;
                currentStartTime += [forward mDuration];
                [dataChoices addObject:forward];
            }else if (choiceType == MusicDataChoice::Choice::sound) {
                if ((*choice_it)->getSound()->getAttributes()->hasTempo) {
                    auto tempo = (*choice_it)->getSound()->getAttributes()->tempo.getValue();
                    self.mTempo = tempo;
                }
            }else if (choiceType == MusicDataChoice::Choice::direction) {
                if ((*choice_it)->getDirection()->getSound()->getAttributes()->hasTempo) {
                    auto tempo = (*choice_it)->getDirection()->getSound()->getAttributes()->tempo.getValue();
                    self.mTempo = tempo;
                }
            }
        }
        MeasureM* measure = [[MeasureM alloc]initWithWidth:(float)width musicDataGroup:dataChoices staves:*staff];
        measure.mStartTime= measureStartTime;
        [measures addObject:measure];
    }
    return measures;
}

-(ScoreM*)parseScorePartWise:(ScorePartwisePtr)scorePartwise {
    // 获取score头部信息
    
    auto workTitle = scorePartwise->getScoreHeaderGroup()->getMovementTitle()->getValue().getValue();
    auto workNumber = scorePartwise->getScoreHeaderGroup()->getMovementNumber()->getValue().getValue();
    
    NSMutableDictionary* partNameDict = @{}.mutableCopy;
    auto partlist = scorePartwise->getScoreHeaderGroup()->getPartList();
    auto name = partlist->getScorePart()->getPartName()->getValue().getValue();
    auto partid = partlist->getScorePart()->getAttributes()->id.getValue();
    
    int instrument= 1;
    if ((*partlist).getScorePart()->getMidiDeviceInstrumentGroupSet().size()) {
        instrument = (*partlist->getScorePart()->getMidiDeviceInstrumentGroupSet().rbegin())->getMidiInstrument()->getMidiProgram()->getValue().getValue();
    }
    
    partNameDict[[self stringFromStringType:partid]] = @{@"name":[self stringFromStringType:name],
                                                         @"program":@(instrument)};
    auto it = scorePartwise->getPartwisePartSet().cbegin();
    NSMutableArray* parts = @[].mutableCopy;
    
    for (auto partname_it = partlist->getPartGroupOrScorePartSet().rbegin(); partname_it != partlist->getPartGroupOrScorePartSet().rend(); partname_it++) {
        auto choice = (*partname_it)->getChoice();
        if (choice == PartGroupOrScorePart::Choice::partGroup) {
            
        }else if(choice == PartGroupOrScorePart::Choice::scorePart){
            auto name = (*partname_it)->getScorePart()->getPartName()->getValue().getValue();
            auto partid = (*partname_it)->getScorePart()->getAttributes()->id.getValue();
            int instrument = 1;
            if ((*partname_it)->getScorePart()->getMidiDeviceInstrumentGroupSet().size()){
                instrument = (*(*partname_it)->getScorePart()->getMidiDeviceInstrumentGroupSet().rbegin())->getMidiInstrument()->getMidiProgram()->getValue().getValue();
            }
            partNameDict[[self stringFromStringType:partid]] = @{@"name":[self stringFromStringType:name],
                                                                 @"program":@(instrument)};
        }
    }
    for (NSInteger i = 0 ;  it != scorePartwise->getPartwisePartSet().cend() ; i++, it++) {
        auto partwise = (*it);
        std::string partNameID = "";
        if (partwise->getAttributes()->hasId) {
            partNameID = partwise->getAttributes()->id.getValue();
        }
        int staff = 1;
        
        NSMutableArray* measures = [self parseScorePartMeasures:partwise staff:&staff];
        
        NSDictionary* partName = [partNameDict objectForKey:[self stringFromStringType:partNameID]];
        PartM* part = [[PartM alloc]initWithName:partName[@"name"] program:[partName[@"program"] integerValue] Measures:measures  staves:staff];
        
        [parts addObject:part];
    }
    
    ScoreM * score = [[ScoreM alloc]initWithTitle:[self stringFromStringType:workTitle] workNumber:[self stringFromStringType:workNumber] tempo:self.mTempo parts:parts];
    [self processScore:score];
    [self processBeamInScore:score];
    [self processConflictMeasure:score];
    
    [self spliteMeasuresToMultiLine:score];
    
    return score;
}

- (ScoreM*)parseXml {
    // Do any additional setup after loading the view, typically from a nib.
    mx::core::DocumentPtr mxDoc = mx::core::makeDocument();
    mx::xml::XDocPtr xmlDoc = mx::xml::XFactory::makeXDoc();
    // read a MusicXML file into the XML DOM structure
    xmlDoc->loadFile( [self.path UTF8String] );
    // create an ostream to receive any parsing messages
    std::stringstream parseMessages;
    // convert the XML DOM into MusicXML Classes
    bool isSuccess = mxDoc->fromXDoc( parseMessages, *xmlDoc );
    if( !isSuccess )
    {
        std::cout << "Parsing of the MusicXML document failed with the following message(s):" << std::endl;
        std::cout << parseMessages.str() << std::endl;
        return NULL;
    }
    
    // maybe the document was timewise document. if so, convert it to partwise
    if( mxDoc->getChoice() == mx::core::DocumentChoice::timewise )
    {
        mxDoc->convertContents();
    }
    
    // get the root
    auto scorePartwise = mxDoc->getScorePartwise();
    
    return [self parseScorePartWise:scorePartwise];
    
    
}

-(void)processBeamInScore:(ScoreM*)score {
    for (int scoreIndex = 0 ;scoreIndex < score.mParts.count; scoreIndex++){
        PartM* part = score.mParts[scoreIndex];
        for (int measureIndex = 0; measureIndex < part.mMeasures.count; measureIndex++) {
            MeasureM* measure = part.mMeasures[measureIndex];
            MeasureM* nextMeasure = nil;
            if(measureIndex < part.mMeasures.count - 1){
                nextMeasure = part.mMeasures[measureIndex+1];
            }
            [self processBeamInMeasure:measure];
            [self processNotationInMeasure:measure nextMeasure:nextMeasure];
        }
    }
}

-(void)processNotationInMeasure:(MeasureM*)measure nextMeasure:(MeasureM*)nextMeasure{
    for (int i = 0 ; i < measure.mMeasureDatas.count ; i ++ ) {
        DrawableNoteM* note = [measure.mMeasureDatas objectAtIndex:i];
        if ([note isKindOfClass:[NoteGroupM class]] && [[((NoteGroupM*)note) mNotations] count]) {
            NoteGroupM* noteGroup = (NoteGroupM*)note;
            NSMutableArray* consivesNoteGroup = @[].mutableCopy;
            for (NotationM* notation in noteGroup.mNotations) {
                if (notation.mValue == ENotationType_Begin) {
                    if (![consivesNoteGroup containsObject:noteGroup]) {
                        [consivesNoteGroup addObject:noteGroup];
                    }
                }
                int j = i;
                BOOL findEnd = NO;
                while (++j < measure.mMeasureDatas.count && !findEnd) {
                    
                    if ([[measure.mMeasureDatas objectAtIndex:j] isKindOfClass:[NoteGroupM class]]) {
                        NoteGroupM* noteFollow = (NoteGroupM*)[measure.mMeasureDatas objectAtIndex:j];
                        if (noteFollow.mNotations.count) {
                            for (NotationM* notationFollow in noteFollow.mNotations) {
                                // end && not Paired
                                if (notationFollow.mValue == ENotationType_End && notationFollow.mNumber == notation.mNumber) {
                                    if (![consivesNoteGroup containsObject:noteFollow]) {
                                        [consivesNoteGroup addObject:noteFollow];
                                    }
                                    findEnd = YES;
                                    break;
                                }
                            }

                        }
                        
                    }
                }
                if(!findEnd){
                    // 当前measure没有找到，找下一个measure
                    j = -1 ;
                    while (++j < nextMeasure.mMeasureDatas.count && !findEnd) {
                        
                        if ([[nextMeasure.mMeasureDatas objectAtIndex:j] isKindOfClass:[NoteGroupM class]]) {
                            NoteGroupM* noteFollow = (NoteGroupM*)[nextMeasure.mMeasureDatas objectAtIndex:j];
                            if (noteFollow.mNotations.count) {
                                for (NotationM* notationFollow in noteFollow.mNotations) {
                                    // end && not Paired
                                    if (notationFollow.mValue == ENotationType_End && notationFollow.mNumber == notation.mNumber) {
                                        if (![consivesNoteGroup containsObject:noteFollow]) {
                                            [consivesNoteGroup addObject:noteFollow];
                                        }
                                        findEnd = YES;
                                        break;
                                    }
                                }
                                
                            }
                            
                        }
                    }
                }
                notation.mEnd = [consivesNoteGroup lastObject];
            }
        }
    }
}

-(void)processBeamInMeasure:(MeasureM*)measure {
    for (int i = 0 ; i < measure.mMeasureDatas.count ; i ++ ) {
        DrawableNoteM* note = [measure.mMeasureDatas objectAtIndex:i];
        if ([note isKindOfClass:[NoteGroupM class]] && [[((NoteGroupM*)note) mBeams] count]) {
            NoteGroupM* noteGroup = (NoteGroupM*)note;
            NSMutableArray* consivesNoteGroup = @[].mutableCopy;
            for (BeamM* beam in noteGroup.mBeams) {
                if (beam.mValue == EBeamType_Begin){
                    if (![consivesNoteGroup containsObject:noteGroup]) {
                        [consivesNoteGroup addObject:noteGroup];
                    }
                    int j = i;
                    BOOL findEnd = NO;
                    while (++j < measure.mMeasureDatas.count && !findEnd) {
                        if ([[measure.mMeasureDatas objectAtIndex:j] isKindOfClass:[NoteGroupM class]]) {
                            NoteGroupM* noteFollow = (NoteGroupM*)[measure.mMeasureDatas objectAtIndex:j];
                            if (noteFollow.mBeams.count){
                                for (BeamM* beamFollow in noteFollow.mBeams) {
                                    // continue && not Paired
                                    if (beamFollow.mValue == EBeamType_Continue && beamFollow.mNumber == beam.mNumber) {
                                        if (![consivesNoteGroup containsObject:noteFollow]) {
                                            [consivesNoteGroup addObject:noteFollow];
                                        }
                                    }
                                    // end && not Paired
                                    if (beamFollow.mValue == EBeamType_End && beamFollow.mNumber == beam.mNumber) {
                                        if (![consivesNoteGroup containsObject:noteFollow]) {
                                            [consivesNoteGroup addObject:noteFollow];
                                        }
                                        findEnd = YES;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    beam.mEnd = [consivesNoteGroup lastObject];
                }
            }
            if (consivesNoteGroup.count>2) {
                [self lineUpNoteGroups:consivesNoteGroup];
            }else if (consivesNoteGroup.count == 2) {
                [self closeNoteGroups:consivesNoteGroup];
            }
            
        }
    }
}

-(void)closeNoteGroups:(NSMutableArray<NoteGroupM*>*)noteGroups {
    NoteGroupM* firstGroup = [noteGroups firstObject];
    NoteGroupM* lastGroup = [noteGroups lastObject];
    /* Bring the stem ends closer together */
    int distance = abs(firstGroup.mStemEndY - lastGroup.mStemEndY);
    if (firstGroup.mStemEndY < lastGroup.mStemEndY) {
        firstGroup.mStemEndY += distance/2;
    }
    else {
        lastGroup.mStemEndY += distance/2;
    }
}
-(void)lineUpNoteGroups:(NSMutableArray<NoteGroupM*>*)noteGroups {
    NoteGroupM* firstGroup = noteGroups[0];
    NoteGroupM* lastGroup = [noteGroups lastObject];
    double firstEndY = 0,lastEndY = 0;

    if (firstGroup.mStem == lastGroup.mStem){
        if (firstGroup.mStem == ENoteStem_UP) {
            int top = [firstGroup mStemEndY];
            for (NoteGroupM* note in noteGroups) {
                top = top < [note mStemEndY] ? top : [note mStemEndY];
            }
            if (top == [firstGroup mStemEndY] && top - lastGroup.mStemEndY <= -2*NoteHeight) {
                firstGroup.mStemEndY = top;
                lastGroup.mStemEndY = top + 2 * NoteHeight;
            }else if  (top == [lastGroup mStemEndY] && top - firstGroup.mStemEndY <= -2*NoteHeight) {
                firstGroup.mStemEndY = top + 2 * NoteHeight;
                lastGroup.mStemEndY = top;
            }else {
                firstGroup.mStemEndY = top;
                lastGroup.mStemEndY = top;
            }
        }else {
            int bottom = [firstGroup mStemEndY];
            for (NoteGroupM* note in noteGroups) {
                bottom = bottom > [note mStemEndY]? bottom : [note mStemEndY];
            }
            if (bottom == [firstGroup mStemEndY] && bottom - [lastGroup mStemEndY] >= 2*NoteHeight) {
                lastGroup.mStemEndY = bottom - 2*NoteHeight;
            }else if  (bottom == [lastGroup mStemEndY] && bottom - [firstGroup mStemEndY] >= 2*NoteHeight) {
                firstGroup.mStemEndY = bottom - 2*NoteHeight;
            }else {
                firstGroup.mStemEndY = bottom;
                lastGroup.mStemEndY = bottom;
            }
        }
        firstEndY = firstGroup.mStemEndY;
        lastEndY = lastGroup.mStemEndY;
        /* All middle stems have the same end */
        for (int i = 1; i < [noteGroups count]-1; i++) {
            NoteGroupM * note = noteGroups[i];
            note.mStemEndY = (note.mDefaultX - firstGroup.mDefaultX)/(lastGroup.mDefaultX - firstGroup.mDefaultX) * (lastEndY - firstEndY) + firstEndY;
        }
    }else {
        int firstStaffBottom  = 0,secondStaffTop = 0;
        for (NoteGroupM* note in noteGroups) {
            if (note.mStem == ENoteStem_UP) {
                if(!secondStaffTop || secondStaffTop > [note mStemEndY]){
                    secondStaffTop = [note mStemEndY];
                }
            }else if(note.mStem == ENoteStem_DOWN) {
                if(!firstStaffBottom || firstStaffBottom < [note mStemEndY]){
                    firstStaffBottom = [note mStemEndY];
                }
            }
        }
        if(firstGroup.mStem == ENoteStem_UP){
            int middle = (secondStaffTop + firstStaffBottom + (PartHeight + PartMarin))* 0.5;
            firstGroup.mStemEndY = middle + NoteHeight - (PartMarin + PartHeight) ;
            lastGroup.mStemEndY = middle - NoteHeight;
            
            firstEndY = firstGroup.mStemEndY;
            lastEndY = lastGroup.mStemEndY - (PartHeight + PartMarin);
            for (int i = 1; i < [noteGroups count]-1; i++) {
                NoteGroupM * note = noteGroups[i];
                if (note.mStem == ENoteStem_UP) {
                    note.mStemEndY = (note.mDefaultX - firstGroup.mDefaultX)/(lastGroup.mDefaultX - firstGroup.mDefaultX) * (lastEndY - firstEndY) + firstEndY;
                }else{
                    note.mStemEndY = (note.mDefaultX - firstGroup.mDefaultX)/(lastGroup.mDefaultX - firstGroup.mDefaultX) * (lastEndY  - firstEndY) + firstEndY + (PartHeight + PartMarin);
                }
            }
        }else{
            int middle = (secondStaffTop + firstStaffBottom + (PartHeight + PartMarin))* 0.5;
            firstGroup.mStemEndY = middle - NoteHeight;
            lastGroup.mStemEndY = middle + NoteHeight - (PartMarin + PartHeight)  ;
            
            firstEndY = firstGroup.mStemEndY;
            lastEndY = lastGroup.mStemEndY + PartHeight + PartMarin;
            
            for (int i = 1; i < [noteGroups count]-1; i++) {
                NoteGroupM * note = noteGroups[i];
                if (note.mStem == ENoteStem_DOWN) {
                    note.mStemEndY = (note.mDefaultX - firstGroup.mDefaultX)/(lastGroup.mDefaultX - firstGroup.mDefaultX) * (lastEndY - firstEndY) + firstEndY;
                }else{
                    note.mStemEndY = (note.mDefaultX+[note drawWidth] - firstGroup.mDefaultX)/(lastGroup.mDefaultX+[note drawWidth] - firstGroup.mDefaultX) * (lastEndY  - firstEndY) + firstEndY - (PartHeight + PartMarin);
                }
            }
        }
    }
}

-(void)processScore:(ScoreM*)score {
    NSMutableDictionary* maxWidth = @{}.mutableCopy;
    for (int i = 0; i < score.mParts.count; i++) {
        PartM* part = score.mParts[i];
        
        NSMutableDictionary* partWidth = @{}.mutableCopy;
        DrawableNoteM* lastNote = nil;
        for (int indexM = 0 ; indexM < part.mMeasures.count; indexM ++) {
            MeasureM* measure = part.mMeasures[indexM];
            for (int indexMD = 0; indexMD < measure.mMeasureDatas.count; indexMD++) {
                DrawableNoteM* data = measure.mMeasureDatas[indexMD];
                if ([data isKindOfClass:[BackupM class]]) {
                    continue;
                }
                if([data isKindOfClass:[RestM class]] && ((RestM*)data).mHasMeasure ){
                    continue;
                }
                [partWidth setObject:@(data.mDuration) forKey:@(data.mStartTime)];
                lastNote = data;
                
                if ([maxWidth objectForKey:@(data.mStartTime)] && [[maxWidth objectForKey:@(data.mStartTime)] doubleValue] > data.mDuration) {
                }else{
                    [maxWidth setObject:@(data.mDuration) forKey:@(data.mStartTime)];
                }
                
            }
        }
    }
    
    
    
    NSArray* startTimeArr = maxWidth.allKeys;
    startTimeArr = [startTimeArr sortedArrayUsingComparator:^NSComparisonResult(NSNumber* obj1, NSNumber* obj2) {
        return [obj1 compare:obj2];
    }];
    // starttime => defaultX
    NSMutableDictionary* xArr = @{}.mutableCopy;
    NSNumber* lastKey = nil;
    for(int indexKey = 0 ;indexKey < startTimeArr.count ;indexKey++){
        NSNumber* key = startTimeArr[indexKey];
        // fix width
        double width = [[maxWidth objectForKey:key] doubleValue];
        if (width < DivisionUnit){
            [maxWidth setObject:@(DivisionUnit* 0.8) forKey:key];
        }else if (width >= DivisionUnit* 1.5){
            [maxWidth setObject:@(width*0.7) forKey:key];
        }else if (width >= DivisionUnit* 2){
            [maxWidth setObject:@(DivisionUnit * 1.5) forKey:key];
        }
        double defaultX = 0;
        if ([key integerValue]<= 0) {
        }else {
            defaultX = [[xArr objectForKey:lastKey] doubleValue] + [[maxWidth objectForKey:lastKey] doubleValue];
        }
        [xArr setObject:@(defaultX) forKey:key];
        lastKey = key;
    }
    
    // set global DefaultX and adjustDuration
    for(int indexP = 0; indexP < score.mParts.count; indexP++) {
        PartM* part = score.mParts[indexP];
        for(int indexM = 0; indexM < part.mMeasures.count; indexM ++) {
            MeasureM* measure = part.mMeasures[indexM];
            DrawableNoteM* lastMeasureData = nil;
            for(int indexMD = 0; indexMD < measure.mMeasureDatas.count; indexMD ++) {
                DrawableNoteM* data = measure.mMeasureDatas[indexMD];
                data.mDefaultX = [[xArr objectForKey:@(data.mStartTime)] doubleValue];
                data.mAjustDuration = [[maxWidth objectForKey:@(data.mStartTime)]doubleValue];
                if (lastMeasureData.mStartTime < data.mStartTime || !lastMeasureData){
                    lastMeasureData = data;
                }
            }
            measure.mWidth = lastMeasureData.mDefaultX + [[maxWidth objectForKey:@(lastMeasureData.mStartTime)] doubleValue] - measure.mMeasureDatas[0].mDefaultX;
        }
    }

    // align measure width
    for(int measureIndex = 0; measureIndex < [[score.mParts[0] mMeasures]count]; measureIndex++) {
        MeasureM * measureMax = [score.mParts[0] mMeasures][measureIndex];
        for (int i = 0; i < score.mParts.count; i++) {
            MeasureM * measure = [score.mParts[i] mMeasures][measureIndex];
            if (measure.mWidth > measureMax.mWidth) {
                measureMax.mWidth = measure.mWidth;
            }
        }
    }
    PartM* partMax = score.mParts[0];
    for(int i = 1;i<score.mParts.count;i++){
        PartM* part = score.mParts[i];
        for(int measureIndex = 0; measureIndex < [[part mMeasures]count]; measureIndex++) {
            MeasureM * measure = [part mMeasures][measureIndex];
            measure.mWidth = [[partMax mMeasures][measureIndex] mWidth];
        }
    }
    
    
    NSMutableDictionary* startTimeNoteMap = @{}.mutableCopy;
    // set relative DefaultX
    for(int indexP = 0; indexP < score.mParts.count; indexP++) {
        PartM* part = score.mParts[indexP];
        double measurePreX = 0;
        for(int indexM = 0; indexM < part.mMeasures.count; indexM ++) {
            MeasureM* measure = part.mMeasures[indexM];
            for(int indexMD = 0; indexMD < measure.mMeasureDatas.count; indexMD ++) {
                DrawableNoteM* data = measure.mMeasureDatas[indexMD];
                data.mDefaultX = [[xArr objectForKey:@(data.mStartTime)] doubleValue] - measurePreX;
                
                if(![startTimeNoteMap objectForKey:@(data.mStartTime)]){
                    [startTimeNoteMap setObject:data forKey:@(data.mStartTime)];
                }
            }
            measurePreX += measure.mWidth;
        }
    }
    
    NSMutableArray* startTimeInfoArr = @[].mutableCopy;
    [startTimeNoteMap enumerateKeysAndObjectsUsingBlock:^(NSNumber* startTime, DrawableNoteM* data, BOOL * _Nonnull stop) {
        [startTimeInfoArr addObject:@{
                                      @"startTime":startTime,
                                      @"data":data,
                                      //                                      @"width":[maxWidth objectForKey:key],
                                      }];
    }];
    [startTimeInfoArr sortUsingComparator:^NSComparisonResult(NSDictionary* obj1, NSDictionary* obj2) {
        return (NSComparisonResult)([obj1[@"startTime"]doubleValue] > [obj2[@"startTime"]doubleValue]);
    }];
    score.mStartTimeInfo = startTimeInfoArr.copy;


}


-(void)processConflictMeasure:(ScoreM*)score {
    for (int scoreIndex = 0 ;scoreIndex < score.mParts.count; scoreIndex++){
        PartM* part = score.mParts[scoreIndex];
        for (int measureIndex = 0; measureIndex < part.mMeasures.count; measureIndex++) {
            MeasureM* measure = part.mMeasures[measureIndex];
            for (int i = 0 ; i < measure.mMeasureDatas.count ; i ++ ) {
                DrawableNoteM* note1 = [measure.mMeasureDatas objectAtIndex:i];
                for (int j = i+1 ; j < measure.mMeasureDatas.count ; j ++ ) {
                    DrawableNoteM* note2 = [measure.mMeasureDatas objectAtIndex:j];
                    if ([note1 isKindOfClass:[NoteGroupM class]]&&
                        [note2 isKindOfClass:[NoteGroupM class]]&&
                        [note1 mStaffth] == [note2 mStaffth]&&
                        [note1 mStartTime] == [note2 mStartTime]){
                        NoteGroupM* first = (NoteGroupM*)note1;
                        NoteGroupM* second = (NoteGroupM*)note2;

                        if (first.mStem == ENoteStem_UP &&
                            second.mStem == ENoteStem_DOWN){
                            int dist = [[first getBottomNote] dist:[second getTopNote]];
                            if (dist >= -2 &&dist < 2) {
                                [first setOffset:6];
                            }else if(dist < -2) {
                                [second setOffset:-6];
                            }
                        }
                    }
                }
            }
        }
    }
}

-(void)spliteMeasuresToMultiLine:(ScoreM*)score {
    
    // scale measures
    NSInteger screenWidth = [UIScreen mainScreen].bounds.size.width;
    NSInteger mainWidth = screenWidth - 2 * Part_Left_Margin;
    for (int partIndex = 0;partIndex < score.mParts.count; partIndex++){
        int lineNumer = 1;
        PartM* part = score.mParts[partIndex];
        double tempWidth = 0;
        int previosLineIndex = 0;
        for (int measureIndex = 0; measureIndex < part.mMeasures.count; measureIndex++) {
            MeasureM* measure = part.mMeasures[measureIndex];
            measure.mMeasureIndex = measureIndex;
            if (measure.mWidth * 0.5 + tempWidth > mainWidth) {
                // 该measure 换行 将之前的measure 设置 rate
                double rate = mainWidth / tempWidth;
                for (int j = measureIndex-1;j>= previosLineIndex ;j--){
                    MeasureM* temp = part.mMeasures[j];
                    temp.mWidthRatio = rate;
                }
                lineNumer++;
                measure.mLine = lineNumer;
                tempWidth = measure.mWidth;
                previosLineIndex = measureIndex;
            }else {
                
                tempWidth += measure.mWidth;
                measure.mLine = lineNumer;
            }
        }
        if (tempWidth > mainWidth){
            // 最后一行要缩小
            double rate = mainWidth / tempWidth;
            for (int j = (int)part.mMeasures.count-1;j>= previosLineIndex ;j--){
                MeasureM* temp = part.mMeasures[j];
                temp.mWidthRatio = rate;
            }
        }
        score.mLines = lineNumer;
    }

    
    // 计算每个measure的startX
    for (int partIndex = 0;partIndex < score.mParts.count; partIndex++){
        PartM* part = score.mParts[partIndex];
        double startX = 0;
        int line = 1;
        for (int measureIndex = 0; measureIndex < part.mMeasures.count; measureIndex++) {
            MeasureM* measure = part.mMeasures[measureIndex];
            if (measure.mLine != line) {
                line++;
                startX = 0;
            }
            measure.mStartX = startX;
            startX += measure.mWidth;
        }
    }
}

-(NSString*)stringFromStringType:(std::string)text{
    return [NSString stringWithCString:text.c_str()
                                             encoding:[NSString defaultCStringEncoding]];
}

@end
