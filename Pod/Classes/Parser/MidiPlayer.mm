//
//  MidiPlayer.m
//  Pods
//
//  Created by tanhui on 2017/8/3.
//
//

#import "MidiPlayer.h"
#include "../../musicFramework/parseScore/MidiHandler.h"

//#include <MusicFramwork/parseScore/MidiHandler.h>
#import "fmod.hpp"

@implementation MidiInfoRetM
@end

@interface MidiPlayer () {
    FMOD::System	*system;
    FMOD::Sound    *sound1;
    FMOD::Channel  *channel;
    FMOD::ChannelGroup* group;
    NSTimer *timer;
    MidiInfo* mInfo;
}

@property(nonatomic, assign) MidiHandler* mHandler;
@property(nonatomic, strong) NSString* mInputPath;
@property(nonatomic, strong) NSString* mOutputPath;
@end

@implementation MidiPlayer

void ERRCHECK(FMOD_RESULT result){
    if (result != FMOD_OK){
        fprintf(stderr, "FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}


-(instancetype)initWithFile:(NSString*)path {
    if ([super init]) {
        MidiHandler* handler = new MidiHandler([path UTF8String]);
        self.mHandler = handler;
        self.mInputPath = path;
        
        NSString* fileName = [path lastPathComponent];
        
        if (![fileName hasSuffix:@".mid"]){
            fileName = [[fileName stringByDeletingPathExtension] stringByAppendingPathExtension:@"mid"];
        }
        self.mOutputPath = [[NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) firstObject] stringByAppendingPathComponent:fileName];
        system = NULL;
        sound1  = NULL;
        channel = NULL;
        group = NULL;
    }
    return self;
}


-(MidiInfoRetM*)prepareToPlay{
//    self.mHandler->setTempoValue(120);
    MidiInfoRetM* retM = [MidiInfoRetM new];
    mInfo = self.mHandler->save([self.mOutputPath UTF8String],true);
    [self prepareFmod];
    retM.mPrefixBeat = mInfo->mPrefixBeat;
    retM.mPrefixBeatType = mInfo->mPrefixBeatType;
    retM.mTempo = mInfo->mTempo;
    return retM;
}

-(MidiInfoRetM*)prepareToPlay:(NSInteger)tempo{
    if (tempo>=30 && tempo <= 120) {
        MidiInfoRetM* retM = [MidiInfoRetM new];
        self.mHandler->setTempoValue(tempo);
        mInfo = self.mHandler->save([self.mOutputPath UTF8String],true);
        retM.mPrefixBeat = mInfo->mPrefixBeat;
        retM.mPrefixBeatType = mInfo->mPrefixBeatType;
        retM.mTempo = mInfo->mTempo;
        [self prepareFmod];
        return retM;
    }
    return nil;
}

-(void)prepareFmod{
    FMOD_RESULT   result        = FMOD_OK;
    char          buffer[500]   = {0};
    unsigned int  version       = 0;
    
    /*
     Create a System object and initialize
     */
    result = FMOD::System_Create(&system);
    ERRCHECK(result);
    
    result = system->getVersion(&version);
    ERRCHECK(result);
    
    if (version < FMOD_VERSION)
    {
        fprintf(stderr, "You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
        exit(-1);
    }
    
    result = system->init(32, FMOD_INIT_NORMAL , NULL);
    ERRCHECK(result);
    
    // set up DLS file
    FMOD_CREATESOUNDEXINFO   soundExInfo;
    memset(&soundExInfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
    soundExInfo.cbsize   = sizeof(FMOD_CREATESOUNDEXINFO);
    char dlsName[500] = {0};
    
    NSString* dlsPath = [NSString stringWithFormat:@"%@/musicXML.bundle/gm.dls", [[NSBundle bundleForClass:self.class] resourcePath]];
    [dlsPath getCString:dlsName maxLength:500 encoding:NSASCIIStringEncoding];
    soundExInfo.dlsname  = dlsName;
    
    // midi one
    [self.mOutputPath getCString:buffer maxLength:500 encoding:NSASCIIStringEncoding];
    
    result = system->createSound(buffer,  FMOD_CREATESTREAM, &soundExInfo, &sound1);    
    ERRCHECK(result);
    result = sound1->setMode(FMOD_LOOP_OFF);
    ERRCHECK(result);
    result =  system->createChannelGroup(buffer, &group);
    ERRCHECK(result);
    
}


-(void)play {
    [self stop];
    FMOD_RESULT result = FMOD_OK;
    result = system->playSound(sound1, group, false, &channel);
    ERRCHECK(result);
//    channel->setPosition(9000, FMOD_TIMEUNIT_MS);
    timer = [NSTimer scheduledTimerWithTimeInterval:0.05 target:self selector:@selector(timerUpdate:) userInfo:nil repeats:YES];
    [[NSRunLoop currentRunLoop]addTimer:timer forMode:NSRunLoopCommonModes];
}

-(void)pause {
    bool pause = false;
    channel->getPaused(&pause);
    channel->setPaused(!pause);
}

-(void)stop{
    if (channel) {
        channel->stop();
    }
    NSError* error = nil;
    if(![[NSFileManager defaultManager]removeItemAtPath:self.mOutputPath error:&error]){
        
    }
}

- (void)timerUpdate:(NSTimer *)timer{
    unsigned int ms = 0;
    unsigned int lenms = 0;
    bool         playing = 0;
    FMOD_RESULT result = FMOD_OK;
    result = channel->isPlaying(&playing);
    
    result = channel->getPosition(&ms, FMOD_TIMEUNIT_MS);
    FMOD::Sound *currentsound = 0;
    channel->getCurrentSound(&currentsound);
    result = currentsound->getLength(&lenms, FMOD_TIMEUNIT_MS);
    
    unsigned int position = 0;
    channel->getPosition(&position, FMOD_TIMEUNIT_MS);
    std::cout<<"current position --"<<position<<std::endl;
    if (!playing){
        //播放结束
        [timer invalidate];
    }
    
    if(self.delegate && [self.delegate respondsToSelector:@selector(midiPlayerDelegateIsPlaying:currentMS:totalMS:)]) {
        [self.delegate midiPlayerDelegateIsPlaying:playing currentMS:ms totalMS:lenms];
    }
}

-(int)getTempoMPQ{
    return 60.0/ mInfo->mTempo * 1000000 + 0.5;
}

-(void)dealloc{
    delete self.mHandler;
     FMOD_RESULT result = FMOD_OK;

    if(sound1 != NULL){
        result = sound1->release();
    }
    if(system != NULL){
        result = system->close();
        result = system->release();
    }
    if(group != NULL){
        result = group->release();
    }
}
@end

