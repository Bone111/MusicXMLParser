//
//  MidiPlayer.h
//  Pods
//
//  Created by tanhui on 2017/8/3.
//
//

#import <Foundation/Foundation.h>

#import "fmod_errors.h"
#import "fmod_common.h"

@protocol MidiPlayerDelegate <NSObject>

-(void)midiPlayerDelegateIsPlaying:(BOOL)isplaying currentMS:(int)ms totalMS:(int)lenMs;

@end

@interface MidiInfoRetM:NSObject
@property(nonatomic, assign) NSInteger mPrefixBeat;
@property(nonatomic, assign) NSInteger mPrefixBeatType;
@property(nonatomic, assign) NSInteger mTempo;
@end

@interface MidiPlayer : NSObject

@property(nonatomic, weak) id<MidiPlayerDelegate>delegate;

-(instancetype)initWithFile:(NSString*)path;

-(MidiInfoRetM*)prepareToPlay;

-(MidiInfoRetM*)prepareToPlay:(NSInteger)tempo;

-(void)play;

-(void)pause;

-(void)stop;

// ms per quarter
-(int)getTempoMPQ;

@end
