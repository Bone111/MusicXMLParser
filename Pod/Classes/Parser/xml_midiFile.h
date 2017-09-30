//
//  xml_midiFile.h
//  iOSMusic
//
//  Created by tanhui on 2017/7/10.
//  Copyright © 2017年 tanhui. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ScoreM.h"

@class MeasureTimeM;

@interface xml_midiFile : NSObject

@property(nonatomic, strong) ScoreM* mScore;
-(id)initWithFile:(NSString*)path;


@end
