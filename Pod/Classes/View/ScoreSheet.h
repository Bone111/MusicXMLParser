//
//  ScoreSheet.h
//  iOSMusic
//
//  Created by tanhui on 2017/7/11.
//  Copyright © 2017年 tanhui. All rights reserved.
//

#import <UIKit/UIKit.h>


@class ScoreM;
@class MidiPlayer;

@interface MidiResult : NSObject
@property(nonatomic, assign) NSInteger totalNotes;
@end



@protocol ShowResultDelegate <NSObject>
-(BOOL)playerIsRecording;
-(void)playerDidFinishWithResult:(MidiResult*)result;

@end


@interface ScoreSheet : UIView
@property(nonatomic, weak) id<ShowResultDelegate> resultDelegate;
@property(nonatomic, strong) MidiPlayer* mPlayer;
@property(nonatomic, assign)double midiSecondOffset;
@property(nonatomic, assign)BOOL mIsRecording;

-(instancetype)initWithFrame:(CGRect)frame score:(ScoreM*)score;
-(void)showResult;
-(void)beginRecording;
-(void)stopRecording;
-(void)reset;
-(void)clearResult;
@end
