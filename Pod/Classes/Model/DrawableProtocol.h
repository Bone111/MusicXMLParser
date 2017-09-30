//
//  DrawableProtocol.h
//  iOSMusic
//
//  Created by tanhui on 2017/7/12.
//  Copyright © 2017年 tanhui. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
@protocol DrawableProtocol <NSObject>


-(void)drawRect:(CGRect)rect;

-(double)drawWidth;

@end
