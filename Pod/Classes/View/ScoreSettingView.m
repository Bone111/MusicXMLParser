
//
//  ScoreSettingView.m
//  Pods
//
//  Created by tanhui on 2017/9/19.
//
//

#import "ScoreSettingView.h"
#import "UIImage+music.h"
#import "Connector.h"

@interface ScoreSettingView()
@property(nonatomic, weak) UILabel* mTempoLabel;
@property(nonatomic, weak) UILabel* mBleLabel;
@property(nonatomic, weak) UIButton* mBleBtn;
@property(nonatomic, weak) UISlider* mSlider;
@end

@implementation ScoreSettingView

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        [self setUp];
    }
    return self;
}

-(instancetype)initWithCoder:(NSCoder *)aDecoder{
    self = [super initWithCoder:aDecoder];
    if (self) {
        [self setUp];
    }
    return self;
}

-(void)setTempo:(int)tempo{
    self.mSlider.value = tempo;
    [self sliderValueChanged:self.mSlider];
}
-(int)getTempo{
    return (int)self.mSlider.value;
}

-(void)setUp{
//    self.backgroundColor = [UIColor whi];
    UILabel *tempoLabel = [[UILabel alloc]init];
    tempoLabel.font = [UIFont systemFontOfSize:15];
    tempoLabel.text = @"速度";
    UILabel *bleLabel = [[UILabel alloc]init];
    bleLabel.font = [UIFont systemFontOfSize:15];
    bleLabel.text = @"蓝牙";
    UIButton* bleBtn =  [[UIButton alloc]init];
    [bleBtn setContentMode:UIViewContentModeScaleAspectFit];
    [self addSubview:bleLabel];
    [self addSubview:tempoLabel];
    [self addSubview:bleBtn];
    self.mTempoLabel = tempoLabel;
    self.mBleBtn = bleBtn;
    self.mBleLabel = bleLabel;
    
    UISlider* slider = [[UISlider alloc]init];
    slider.minimumValue = 30;
    slider.maximumValue = 120;
    [self addSubview:slider];
    [slider addTarget:self action:@selector(sliderValueChanged:) forControlEvents:UIControlEventValueChanged];
    self.mSlider = slider;
    
    self.layer.cornerRadius = 4;
    self.clipsToBounds = YES;
    
}

-(void)addTarget:(nullable id)target action:(SEL _Nullable )action {
    [self.mBleBtn addTarget:target action:action forControlEvents:UIControlEventTouchUpInside];
}

-(void)setHidden:(BOOL)hidden{
    [super setHidden:hidden];
    self.mConnected = [[Connector defaultConnector]isConnected];
}

-(void)setMConnected:(BOOL)mConnected{
    _mConnected = mConnected;
    if(mConnected){
        [self.mBleBtn setImage:[UIImage imageForResource:@"on" ofType:@"png" inBundle:[NSBundle bundleForClass:[self class]]]  forState:UIControlStateNormal];
    }else{
        [self.mBleBtn setImage:[UIImage imageForResource:@"off" ofType:@"png" inBundle:[NSBundle bundleForClass:[self class]]]  forState:UIControlStateNormal];
        
    }
}

-(void)sliderValueChanged:(UISlider*)slider{
    self.mTempoLabel.text = [@"速度 " stringByAppendingFormat:@"%d",(int)slider.value];
}

-(void)layoutSubviews{
    [super layoutSubviews];
    
    self.mTempoLabel.frame = CGRectMake(10, 10, 100, 20);
    self.mSlider.frame = CGRectMake(self.frame.size.width - 90 -10, 15, 90, 10);
    self.mBleLabel.frame = CGRectMake(10, 30, 100, 20);
    self.mBleBtn.frame = CGRectMake(self.frame.size.width - 10 - 30, 30, 30, 30);
}

@end
