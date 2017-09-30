//
//  ScoreM.h
//  iOSMusic
//
//  Created by tanhui on 2017/7/11.
//  Copyright © 2017年 tanhui. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PartM.h"
@class DrawableNoteM;
@interface ScoreHeaderM : NSObject
@property(nonatomic, strong ,readonly) NSString* mWorkTitle;
@property(nonatomic, strong ,readonly) NSString* mWorkNumber;
-(instancetype)initWithTitle:(NSString*) title workNumber:(NSString*)workNumber;
@end

@interface ScoreM : NSObject
@property(nonatomic, strong) ScoreHeaderM* mHeader;
@property(nonatomic, strong ) NSArray* mParts;
@property(nonatomic, assign) double mWidth;
@property(nonatomic, assign) NSInteger mLines;
@property(nonatomic, copy ) NSArray* mStartTimeInfo;

@property(nonatomic, assign) NSInteger mPartLineHeight;
@property(nonatomic, assign) NSInteger mTotalHeight;

@property(nonatomic, assign,readonly) NSInteger mTempo;


-(instancetype)initWithTitle:(NSString*) title workNumber:(NSString*) workNumber tempo:(NSInteger)tempo parts:(NSArray*)parts;
-(DrawableNoteM*)getLatestNoteByTicks:(double)currentTick ;

-(NSMutableArray*)getNotesByStartTime:(double)startTime ;

@end
