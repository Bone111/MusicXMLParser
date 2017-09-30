//
//  CIResultView.m
//  musicXML
//
//  Created by tanhui on 2017/9/1.
//  Copyright © 2017年 tanhuiya. All rights reserved.
//

#import "ResultView.h"

@implementation ResultView

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/
+ (instancetype)customXiBView{
    NSString *className = NSStringFromClass([self class]);
    return [[[NSBundle bundleForClass:[self class]] loadNibNamed:className owner:self options:nil] firstObject];
}


- (IBAction)close:(id)sender {
    [self removeFromSuperview];
}

@end
