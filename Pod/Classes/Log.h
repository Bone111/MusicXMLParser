//
//  Log.h
//  Pods
//
//  Created by tanhui on 2017/9/1.
//
//

#import <Foundation/Foundation.h>

@interface Log : NSObject
+ (void)clearTempLog ;
+ (void)saveLogFile;
+ (void)writefile:(int)midiEventChannel note:(int)midiEventNote velocity:(int)midiEventVelocity tick:(double)tick remark:(NSString*)remark;
@end
