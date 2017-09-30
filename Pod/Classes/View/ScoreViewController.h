//
//  CIScoreViewController.h
//  musicXML
//
//  Created by tanhui on 2017/9/15.
//  Copyright © 2017年 tanhuiya. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef enum : NSUInteger {
    EPlayStateNone,
    EPlayStatePlaying,
    EPlayStateStop,
} EPlayState;

@interface ScoreViewController : UIViewController<UIPopoverPresentationControllerDelegate>

-(instancetype)initWithFileName:(NSString*)filePath;

@end
