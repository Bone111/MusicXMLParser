//
//  CIScoreViewController.m
//  musicXML
//
//  Created by tanhui on 2017/9/15.
//  Copyright © 2017年 tanhuiya. All rights reserved.
//

#import "ScoreViewController.h"
#import <musicXML/musicXML.h>
#import "ResultView.h"
#import "UIImage+music.h"
#import "ScoreSettingView.h"

@interface ScoreViewController ()<ShowResultDelegate>
@property (weak, nonatomic) IBOutlet UIView *mHudTopView;
@property (weak, nonatomic) IBOutlet UIView *mHudBottomView;
@property (weak, nonatomic) IBOutlet UIButton *mPlayOrPauseBtn;
@property (copy, nonatomic) NSString* mFilePath;
@property(nonatomic, strong) MidiPlayer* mPlayer;
@property(nonatomic, strong) ScoreSheet* mSheet;
@property(nonatomic, assign) EPlayState mState;
@property(nonatomic, weak) ScoreM* mScore;
@property(nonatomic, assign) BOOL mIsRecording;

@property (weak, nonatomic) IBOutlet ScoreSettingView *mSettingView;
@property(nonatomic, strong) UILabel* mCountLabel;
@property(nonatomic, strong) Connector* mConnector;

@property (weak, nonatomic) IBOutlet UIButton *mModeBtn;
@property (weak, nonatomic) IBOutlet UIButton *mSettingBtn;
@property (weak, nonatomic) IBOutlet UIButton *mResetBtn;
@property (weak, nonatomic) IBOutlet UIButton *mBackBtn;
@end

@implementation ScoreViewController
#pragma mark - UIPopoverPresentationControllerDelegate


// Called on the delegate when the popover controller will dismiss the popover. Return NO to prevent the dismissal of the view.
- (BOOL)popoverPresentationControllerShouldDismissPopover:(UIPopoverPresentationController *)popoverPresentationController {
    NSLog(@"%@",NSStringFromSelector(_cmd));
    return YES;
}
-(UIModalPresentationStyle)adaptivePresentationStyleForPresentationController:(UIPresentationController *)controller{
    return UIModalPresentationNone;
}

-(instancetype)initWithFileName:(NSString*)filePath{
    NSBundle* bundle = [NSBundle bundleForClass:[self class]];
    self = [self initWithNibName:NSStringFromClass([self class]) bundle:bundle];
    if (self) {
        self.mFilePath = filePath;
    }
    return self;
}

-(instancetype)init{
    return nil;
}

-(void)dealloc{
    
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    xml_midiFile* file = [[xml_midiFile alloc]initWithFile:self.mFilePath];
    MidiPlayer* player = [[MidiPlayer alloc] initWithFile:self.mFilePath];
    self.mPlayer = player;
    CGRect rect = [UIScreen mainScreen].bounds;
    ScoreSheet* sheet = [[ScoreSheet alloc]initWithFrame:rect score:file.mScore];
    UITapGestureRecognizer* tap = [[UITapGestureRecognizer alloc]initWithTarget:self action:@selector(touch)];
    [sheet addGestureRecognizer:tap];
    sheet.mPlayer = player;
    sheet.resultDelegate = self;
    self.mSheet = sheet;
    [self.view insertSubview:sheet atIndex:0];
    [self.mSettingView setTempo:(int)file.mScore.mTempo];
    [self.mSettingView addTarget:self action:@selector(blueToothDidSwitch:)];
    self.mScore = file.mScore;
    
    [self.mModeBtn setImage:[UIImage imageForResource:@"listen" ofType:@"png" inBundle:[NSBundle bundleForClass:[self class]]]  forState:UIControlStateNormal];
    [self.mSettingBtn setImage:[UIImage imageForResource:@"setting" ofType:@"png" inBundle:[NSBundle bundleForClass:[self class]]]  forState:UIControlStateNormal];
    [self.mResetBtn setImage:[UIImage imageForResource:@"reset" ofType:@"png" inBundle:[NSBundle bundleForClass:[self class]]]  forState:UIControlStateNormal];
    [self.mBackBtn setImage:[UIImage imageForResource:@"back" ofType:@"png" inBundle:[NSBundle bundleForClass:[self class]]]  forState:UIControlStateNormal];
    [self.mPlayOrPauseBtn setImage:[UIImage imageForResource:@"play" ofType:@"png" inBundle:[NSBundle bundleForClass:[self class]]]  forState:UIControlStateNormal];
}

-(void)blueToothDidSwitch:(id)sender {
    if(!self.mSettingView.mConnected){
        __weak typeof(self) _weakSelf = self;
        [self presentViewController:[[ConnectorViewController alloc]initWithSuccessBlock:^{
            _weakSelf.mSettingView.mConnected = YES;
            _weakSelf.mIsRecording = YES;
        } error:^{
            _weakSelf.mSettingView.mConnected = NO;
        }] animated:YES completion:nil];
    }else{
        [[Connector defaultConnector]cancelConnection];
        self.mSettingView.mConnected = NO;
    }
}

- (IBAction)back:(id)sender {
    [self.mPlayer stop];
    [self.navigationController popViewControllerAnimated:YES];
}

-(void)touch{
    if (self.mHudTopView.hidden) {
        self.mHudTopView.hidden = NO;
        self.mHudBottomView.hidden = NO;
        
    }else{
        self.mHudTopView.hidden = YES;
        self.mHudBottomView.hidden = YES;
        self.mSettingView.hidden = YES;
    }
}

// play or pause
- (IBAction)play:(id)sender {
    
    if (self.mState == EPlayStateNone ) {
        [self.mSheet clearResult];
        
        [self.mConnector prepareRecording];
        MidiInfoRetM* retInfo = [self.mPlayer prepareToPlay:[self.mSettingView getTempo]];
        [self.mPlayer play];
        [Log clearTempLog];
        double ticksPers = DivisionUnit* 1.0/[self.mPlayer getTempoMPQ] * 1000000;
        
        double secodePerdot = DivisionUnit/double(retInfo.mPrefixBeatType/4.0)/ticksPers;
        __block int numDot = retInfo.mPrefixBeat;
        self.mSheet.midiSecondOffset = numDot * secodePerdot;
        
        __weak typeof(self) weakSelf = self;
        NSTimer* timer = [NSTimer timerWithTimeInterval:secodePerdot repeats:YES block:^(NSTimer * _Nonnull timer) {
            if (--numDot<0) {
                weakSelf.mCountLabel.hidden = YES;
                [timer invalidate];
                [weakSelf.mSheet beginRecording];
                if (weakSelf.mIsRecording){
                    // recording should after invoking play method
                    [weakSelf.mConnector beginRecording];
                }
            }else{
                weakSelf.mCountLabel.hidden = NO;
                weakSelf.mCountLabel.text = [NSString stringWithFormat:@"%d",numDot+1];
            }
        }];
        [[NSRunLoop mainRunLoop]addTimer:timer forMode:NSRunLoopCommonModes];
        [timer fire];
        self.mState =EPlayStatePlaying;
    }else if (self.mState == EPlayStatePlaying || self.mState == EPlayStateStop){
        [self.mPlayer pause];
        if (self.mIsRecording){
            [self.mConnector stopRecording];
        }
        [self.mSheet showResult];
        [self.mSheet stopRecording];
        self.mState = self.mState == EPlayStateStop? EPlayStatePlaying :EPlayStateStop;
    }
    
}

//-(void)scheduleInfo:(NSTimer*)timer{
//    NSDictionary* userInfo = [timer userInfo];
//    NSInteger u

//}
- (IBAction)reset:(id)sender {
    [self.mPlayer stop];
    self.mState = EPlayStateNone;
    [self.mSheet reset];
}
- (IBAction)changeMode:(UIButton*)btn {
    
    if (self.mState == EPlayStateNone) {
        if(self.mSettingView.mConnected){
            self.mIsRecording = !self.mIsRecording;
        }else{
            __weak typeof(self) weakSelf = self;
            UIAlertController* alertVC = [UIAlertController alertControllerWithTitle:nil message:@"请先连接蓝牙" preferredStyle:UIAlertControllerStyleAlert];
            [alertVC addAction:[UIAlertAction actionWithTitle:@"取消" style:UIAlertActionStyleCancel handler:nil]];
            [alertVC addAction:[UIAlertAction actionWithTitle:@"去连接" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
                [weakSelf blueToothDidSwitch:nil];
            }]];
            [self presentViewController:alertVC animated:YES completion:nil];
        }
    }
}
- (IBAction)setting:(id)sender {
    self.mSettingView.hidden = !self.mSettingView.isHidden;
}

-(void)setMIsRecording:(BOOL)mIsRecording{
    _mIsRecording = mIsRecording;
    self.mSheet.mIsRecording = mIsRecording;
    if (mIsRecording) {
        [self.mModeBtn setImage:[UIImage imageForResource:@"jiucuo" ofType:@"png" inBundle:[NSBundle bundleForClass:[self class]]]  forState:UIControlStateNormal];
    }else{
        [self.mModeBtn setImage:[UIImage imageForResource:@"listen" ofType:@"png" inBundle:[NSBundle bundleForClass:[self class]]]  forState:UIControlStateNormal];
    }
}

#pragma mark Delegates 
-(BOOL)playerIsRecording{
    return self.mIsRecording;
}
-(void)playerDidFinishWithResult:(MidiResult *)result{
    if (!self.mIsRecording ) {
        return;
    }
//    [Log saveLogFile];
}


#pragma mark getter

-(UILabel *)mCountLabel{
    if (!_mCountLabel) {
        _mCountLabel = [[UILabel alloc]initWithFrame:CGRectMake(0 ,0,200,100)];
        _mCountLabel.center = self.view.center;
        _mCountLabel.textAlignment = NSTextAlignmentCenter;
        _mCountLabel.backgroundColor = UIColor.clearColor;
        _mCountLabel.textColor = [UIColor redColor];
        _mCountLabel.hidden = YES;
        _mCountLabel.font = [UIFont boldSystemFontOfSize:50];
        [self.view addSubview:_mCountLabel];
    }
    return _mCountLabel;
}

-(Connector *)mConnector{
    if(!_mConnector){
        _mConnector = [Connector defaultConnector];
    }
    return _mConnector;
}

-(void)setMState:(EPlayState)mState{
    _mState = mState;
    if (mState == EPlayStateStop || mState == EPlayStateNone) {
        [self.mPlayOrPauseBtn setImage:[UIImage imageForResource:@"play" ofType:@"png" inBundle:[NSBundle bundleForClass:[self class]]]  forState:UIControlStateNormal];
    }else if(mState == EPlayStatePlaying){
        [self.mPlayOrPauseBtn setImage:[UIImage imageForResource:@"pause" ofType:@"png" inBundle:[NSBundle bundleForClass:[self class]]]  forState:UIControlStateNormal];
    }
}

////设置样式
//- (UIStatusBarStyle)preferredStatusBarStyle {
//    return UIStatusBarStyleLightContent;
//}
//
//设置是否隐藏
- (BOOL)prefersStatusBarHidden {
    //    [super prefersStatusBarHidden];
    return YES;
}

@end
