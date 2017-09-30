//
//  ScoreSettingView.h
//  Pods
//
//  Created by tanhui on 2017/9/19.
//
//

#import <UIKit/UIKit.h>

@interface ScoreSettingView : UIView

-(void)setTempo:(int)tempo;
-(int)getTempo;

- (void)addTarget:(nullable id)target action:(SEL _Nullable )action ;

@property(nonatomic,assign)BOOL mConnected;

@end
