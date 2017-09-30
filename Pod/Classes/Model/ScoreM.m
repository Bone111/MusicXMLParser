//
//  ScoreM.m
//  iOSMusic
//
//  Created by tanhui on 2017/7/11.
//  Copyright © 2017年 tanhui. All rights reserved.
//

#import "ScoreM.h"
#import "MeasureM.h"
#import "DrawableNoteM.h"
#import "NoteM.h"
#import "Constants.h"

@implementation ScoreHeaderM

-(instancetype)initWithTitle:(NSString*) title workNumber:(NSString*)workNumber{
    if ([super init]) {
        _mWorkTitle = title;
        _mWorkNumber = workNumber;
    }
    return self;
}
@end

@implementation ScoreM
-(instancetype)initWithTitle:(NSString*) title workNumber:(NSString*) workNumber tempo:(NSInteger)tempo parts:(NSArray*)parts{
    if ([super init]) {
        _mHeader = [[ScoreHeaderM alloc]initWithTitle:title workNumber:workNumber];
        _mParts = parts;
        __weak typeof(self) _weakSelf = self;
        [_mParts enumerateObjectsUsingBlock:^(PartM* part, NSUInteger idx, BOOL * _Nonnull stop) {
            part.mScore = _weakSelf;
        }];
        _mTempo = tempo;
    }
    return self;
}

-(instancetype)init{
    return nil;
}

-(DrawableNoteM*)getLatestNoteByTicks:(double)currentTick{
    
    NSDictionary* selectDict = nil;
    for (int index = 0; index < self.mStartTimeInfo.count ; index++) {
        NSDictionary* dict = self.mStartTimeInfo[index];
        if (index == self.mStartTimeInfo.count -1) {
            selectDict = dict;
            break;
        }
        NSDictionary* nextDict = self.mStartTimeInfo[index+1];
        if ([[dict objectForKey:@"startTime"] doubleValue] <= currentTick && [[nextDict objectForKey:@"startTime"] doubleValue]> currentTick) {
            selectDict = dict;
            break;
        }
    }
    DrawableNoteM* data = [selectDict objectForKey:@"data"];
    return data ;
}

//-(DrawableNoteM*)getLatestNoteByTicks:(double)currentTick{
//    
//    NSInteger selectIndex = -1;
//    PartM* firstPart = self.mParts[0];
//    for (int measure_index = 0; measure_index < firstPart.mMeasures.count; measure_index ++) {
//        MeasureM* measures = firstPart.mMeasures[measure_index];
//        if (measure_index == firstPart.mMeasures.count-1) {
//            selectIndex = measure_index;
//            break;
//        }
//        MeasureM* nextMeasures = firstPart.mMeasures[measure_index+1];
//        if (measures.mStartTime <= currentTick && nextMeasures.mStartTime > currentTick) {
//            selectIndex = measure_index;
//            break;
//        }
//    }
//    if (selectIndex < 0) {
//        return nil;
//    }
//    double offset = CGFLOAT_MAX;
//    DrawableNoteM * select = nil;
//    for (NSInteger partIndex = 0; partIndex < self.mParts.count; partIndex++) {
//        MeasureM* measure = [self.mParts[partIndex] mMeasures][selectIndex];
//        for (DrawableNoteM* note in measure.mMeasureDatas) {
//            if (currentTick >= note.mStartTime && currentTick - note.mStartTime < offset ) {
//                offset = currentTick - note.mStartTime;
//                select = note;
//            }
//        }
//    }
//    return select;
//}

-(PartM*)getPianePart {
    for (PartM* part in self.mParts) {
        if (part.mProgram >=1 && part.mProgram <=8) {
            return part;
        }
    }
    return nil;
}

-(NSMutableArray*)getNotesByStartTime:(double)startTime {
    NSMutableArray* notes = @[].mutableCopy;
    PartM* pianoPart = [self getPianePart];
    MeasureM* select = nil;
    for (int measure_index = 0; measure_index < pianoPart.mMeasures.count; measure_index ++) {
        MeasureM* measures = pianoPart.mMeasures[measure_index];
        if (measure_index == pianoPart.mMeasures.count-1) {
            select = measures;
            break;
        }
        MeasureM* nextMeasures = pianoPart.mMeasures[measure_index+1];
        if (measures.mStartTime <= startTime && nextMeasures.mStartTime > startTime) {
            select = measures;
            break;
        }
    }
    for (DrawableNoteM* note in select.mMeasureDatas) {
        if ([note isKindOfClass:[NoteGroupM class]]) {
            NoteGroupM* noteGroup = (NoteGroupM*)note;
            if (note.mStartTime <= startTime && note.mStartTime + note.mDuration > startTime) {
                
                [notes addObjectsFromArray:[noteGroup notes]];
            }
        }
    }
    return notes;
}


-(NSInteger)mPartLineHeight{
    int staffNum = 0;
    for (PartM *part in self.mParts) {
        staffNum += part.mStavesNum;
    }
    _mPartLineHeight = ((staffNum -1) * PartMarin + staffNum * PartHeight);
    return _mPartLineHeight;
}

-(NSInteger)mTotalHeight{
    return self.mPartLineHeight * self.mLines + PartLineMargin * (self.mLines-1) + Part_Top_Margin * 2;
}

@end
