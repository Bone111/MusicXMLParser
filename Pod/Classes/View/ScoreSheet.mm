//
//  ScoreSheet.m
//  iOSMusic
//
//  Created by tanhui on 2017/7/11.
//  Copyright © 2017年 tanhui. All rights reserved.
//

#import "ScoreSheet.h"
#import "musicXML.h"
#import "Constants.h"
#import "MidiPlayer.h"
#import "DrawableNoteM.h"
#import "SheetView.h"
#import "PianoView.h"
#import "ResultDetailM.h"
#import "ResultDetailView.h"
#include "../../musicFramework/compare/ComparePooling.h"
//#include <MusicFramwork/compare/ComparePooling.h>

@implementation MidiResult
@end

@interface ScoreSheet ()<MidiPlayerDelegate>{
    std::vector<MidiSignal*> receives;
    ComparePooling* pool;
    dispatch_semaphore_t semaphore;
}
@property(nonatomic, strong) ScoreM* mScore;
@property(nonatomic, strong) SheetView* mSheetview;
@property(nonatomic, strong) PianoView* mPiano;
@property(nonatomic, assign) double mCurrentTick;
@property(nonatomic, assign) BOOL mIsPlaying;
@property(nonatomic, strong) NSTimer* mTimer;
@end

bool less_second(CNote* & m1, CNote* & m2) {
    return m1->mStartTime < m2->mStartTime;
}

@implementation ScoreSheet


-(instancetype)initWithFrame:(CGRect)frame score:(ScoreM*)score{
    if ([super initWithFrame:frame]) {
        _mScore = score;
        (void)[self mPiano];
        (void)[self mSheetview];
        semaphore = dispatch_semaphore_create(1);
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(scoreDidreceiveMidiOn:) name:ScoreDidReceiveMidiOnNotification object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(scoreDidreceiveMidiOff:) name:ScoreDidReceiveMidiOffNotification object:nil];
        receives = std::vector<MidiSignal*>();
        
        std::vector<CNote*>templates = [self getTempletesFromScore:score];
        sort(templates.begin(), templates.end(), less_second);
        pool = new ComparePooling(templates,Theta);
        pool->setMode(InstrumentMode_DoubleKey_YMH);
    }
    return self;
}

-(std::vector<CNote*>)getTempletesFromScore:(ScoreM*)score {
    std::vector<CNote*>templates = std::vector<CNote*>();
    NSInteger staffIndex = 0;
    for (int partIndex = 0; partIndex < score.mParts.count; partIndex++) {
        PartM* part = score.mParts[partIndex];
        if (part.mProgram > 8){
            continue;
        }
        for (int measureIndex = 0; measureIndex < part.mMeasures.count; measureIndex ++) {
            MeasureM* measure = part.mMeasures[measureIndex];
            for (DrawableNoteM* drawAble in measure.mMeasureDatas) {
                if ([drawAble isKindOfClass:[NoteGroupM class]]) {
                    NoteGroupM* group = (NoteGroupM*)drawAble;
                    for (NoteM* note in [group notes]) {
                        CNote* cnote = new CNote((int)(staffIndex + note.mStaffth),[note noteNumber],group.mStartTime,note.mDuration);
                        templates.push_back(cnote);
                    }
                }
            }
        }
        staffIndex += part.mStavesNum;
    }
    return templates;
}

#pragma mark MidiPlayerDelegate
-(void)midiPlayerDelegateIsPlaying:(BOOL)isplaying currentMS:(int)ms totalMS:(int)lenMs{
    self.mIsPlaying = isplaying;
    if (!isplaying) {
        [self playOver];
        return;
    }
    ms = ms - self.midiSecondOffset * 1000;
    if (ms <= 0)return;
    int tempo = [self.mPlayer getTempoMPQ];
    // ticks per ms
    double ticksPerMs = DivisionUnit* 1.0/tempo * 1000;
    double currentTicks = ms * ticksPerMs;
    self.mCurrentTick = currentTicks;
    DrawableNoteM* note = [self.mScore getLatestNoteByTicks:currentTicks];
    
    NSArray* pianoNotes = [self.mScore getNotesByStartTime:currentTicks];
    [self.mSheetview updateCusor:note];
    [self.mPiano updateNotes:pianoNotes];
}

-(void)scoreDidreceiveMidiOn:(NSNotification*)note {
    if(!self.mIsPlaying|| !self.mIsRecording){
        return;
    }
    NSDictionary* info = note.object;
    int channel = [info[@"channel"] intValue];
//    int channel = 0;
    int noteNum = [info[@"note"] intValue];
    //    int velocity = [info[@"velocity"] intValue];
    double ms = [info[@"ms"] doubleValue];
    
    double msPerDivision = [self.mPlayer getTempoMPQ]/1000.0/DivisionUnit;
    double ticks = ms / msPerDivision;
    
    [self addMidiSignal:channel tick:ticks number:noteNum type:EMidiSignalType::EMidiSignalTypeOn];
    [Log writefile:channel note:noteNum velocity:0 tick:ms remark:@"midiOn"];
//    CILog(@"channel = %d",channel);
}

-(void)addMidiSignal:(NSInteger)channel tick:(NSInteger)tick number:(NSInteger)number type:(EMidiSignalType)type{
    dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);
//    CILog(@"channel --%d, %d",channel+1,number);
    receives.push_back(new MidiSignal((int)channel,tick,number,type));
    dispatch_semaphore_signal(semaphore);
}
-(void)scoreDidreceiveMidiOff:(NSNotification*)note {
    if(!self.mIsPlaying || !self.mIsRecording){
        return;
    }
    NSDictionary* info = note.object;
    int channel = [info[@"channel"] intValue];
//    int channel = 0;
    int noteNum = [info[@"note"] intValue];
    //    int velocity = [info[@"velocity"] intValue];
    double ms = [info[@"ms"] doubleValue];
    double msPerDivision = [self.mPlayer getTempoMPQ]/1000.0/DivisionUnit;
    double ticks = ms / msPerDivision;
    [self addMidiSignal:channel tick:ticks number:noteNum type:EMidiSignalType::EMidiSignalTypeOff];
    [Log writefile:channel note:noteNum velocity:0 tick:ticks remark:@"midiOff"];
}

-(void)playOver {
    __weak typeof(self) weakSelf = self;
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [weakSelf stopRecording];
        [weakSelf showResult];
    });
}

-(void)showResult{
    CResult* result = pool->getFinalResult();
    if(self.resultDelegate && [self.resultDelegate respondsToSelector:@selector(playerDidFinishWithResult:)]){
        MidiResult* oc_result = [MidiResult new];
        
        //            if(weakSelf.resultDelegate && [weakSelf.resultDelegate respondsToSelector:@selector(playerIsRecording)]){
        //                if ([weakSelf.resultDelegate playerIsRecording]){
        //                    [weakSelf.resultDelegate playerDidFinishWithResult:oc_result];
        [self showResultSymbols:result];
        //                }
        //            }
    }
}
-(void)showResultSymbols:(CResult*)result {
    NSMutableArray<ResultDetailM*>* errorNotes = @[].mutableCopy;
    
    for (auto iter = result->mResultNotes.cbegin(); iter != result->mResultNotes.cend(); iter ++) {
        ResultDetailM* resultM = [[ResultDetailM alloc]init];
        resultM.mStartTime =(*iter)->mStartTime;
        resultM.mStaffIndex =(*iter)->mStaffIndex;
        resultM.mNoteNumber = (*iter)->mNoteNumber;
        if ((*iter)->mType == ECNoteResultTypeError) {
            resultM.mErrorNumber = (*iter)->mErrorNumber;
            resultM.mErrorType = EResultErrorType_Error;
        }else if((*iter)->mType == ECNoteResultTypeLost){
            resultM.mErrorType = EResultErrorType_Lost;
        }
       [errorNotes addObject:resultM];
    }
    ResultDetailView* detailView = [[ResultDetailView alloc]initWithFrame:self.mSheetview.frame errorResults:errorNotes.copy score:self.mScore];
    [self.mSheetview.mParentView addSubview:detailView];
}



-(void)clearResult{
    [self.mSheetview clearResult];
}

-(void)reset{
    [self.mSheetview.mParentView setContentOffset:CGPointMake(0, 0)];
    UIScrollView* scrollView = self.mSheetview.mParentView;
    for (UIView* view in scrollView.subviews) {
        if ([view isKindOfClass:[ResultDetailView class]]) {
            [view removeFromSuperview];
        }
    }
}

-(void)beginRecording {
    pool->resetPool();
    self.mTimer = [NSTimer scheduledTimerWithTimeInterval:0.5 repeats:YES block:^(NSTimer * _Nonnull timer) {
        if ([self mIsPlaying]) {
            NSString* str = @"";
            for (int i = 0 ; i<receives.size(); i++) {
                MidiSignal* signal = receives[i];
                str = [str stringByAppendingFormat:@"\n note%d tick=%lf ; ",i,signal->mTimeStamp];
            }
//            CILog(@"%@ \n  currentTick**** %lf",str,[self getCurrentTicks]);
            std::vector<CNote*>ret = pool->receiveMidiSignals(receives, [self getCurrentTicks]);
//            CILog(@"返回 %lu 个note",ret.size());
            dispatch_semaphore_signal(semaphore);
            receives.clear();
            dispatch_semaphore_signal(semaphore);
        }
    }];
    [[NSRunLoop currentRunLoop]addTimer:self.mTimer forMode:NSRunLoopCommonModes];

}

-(void)stopRecording {
    [self.mTimer invalidate];
}

-(double)getCurrentTicks{
    return self.mCurrentTick;
}


-(void)setMPlayer:(MidiPlayer *)mPlayer{
    _mPlayer = mPlayer;
    mPlayer.delegate = self;
}


-(SheetView *)mSheetview{
    if (!_mSheetview) {
        _mSheetview = [[SheetView alloc]initWithFrame:CGRectMake(0, 0, self.frame.size.width ,self.mScore.mTotalHeight) score:self.mScore];
        UIScrollView* scrollview = [[UIScrollView alloc]initWithFrame:self.bounds];
        [scrollview addSubview:_mSheetview];
        _mSheetview.mParentView = scrollview;
        [self addSubview:scrollview];
        scrollview.contentSize = CGSizeMake(0 ,_mSheetview.frame.size.height);
    }
    return _mSheetview;
}

-(PianoView *)mPiano{
    if (!_mPiano) {
        _mPiano = [[PianoView alloc]init];
//        [self addSubview:_mPiano];
    }
    return _mPiano;
}

-(void)dealloc{
    [[NSNotificationCenter defaultCenter]removeObserver:self  name:ScoreDidReceiveMidiOnNotification object:nil];
    [[NSNotificationCenter defaultCenter]removeObserver:self  name:ScoreDidReceiveMidiOffNotification object:nil];
    delete pool;
    pool = NULL;
}
@end
