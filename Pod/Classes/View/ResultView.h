//
//  CIResultView.h
//  musicXML
//
//  Created by tanhui on 2017/9/1.
//  Copyright © 2017年 tanhuiya. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ResultView : UIView
@property (weak, nonatomic) IBOutlet UILabel *mrate;
@property (weak, nonatomic) IBOutlet UILabel *mLost;
@property (weak, nonatomic) IBOutlet UILabel *mError;
@property (weak, nonatomic) IBOutlet UILabel *mShort;
@property (weak, nonatomic) IBOutlet UILabel *mTimeout;
+ (instancetype)customXiBView;

@end
