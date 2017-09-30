//
//  Log.m
//  Pods
//
//  Created by tanhui on 2017/9/1.
//
//

#import "Log.h"
#import "Constants.h"

@implementation Log

+ (void)clearTempLog {
    NSArray *paths  = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,NSUserDomainMask,YES);
    NSString *homePath = [paths objectAtIndex:0];
    NSString *filePath = [homePath stringByAppendingPathComponent:@"tempFile"];
    [@"" writeToFile:filePath atomically:YES encoding:NSUTF8StringEncoding error:nil];
}

+ (void)saveLogFile{
    NSArray *paths  = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,NSUserDomainMask,YES);
    NSString *homePath = [paths objectAtIndex:0];
    NSString *filePath = [homePath stringByAppendingPathComponent:@"tempFile"];
    
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setDateFormat:@"yyyy-MM-dd HH:mm:ss"];
    NSString *datestr = [dateFormatter stringFromDate:[NSDate date]];
    NSString *destPath = [homePath stringByAppendingPathComponent:datestr];
    
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSError* error = nil;
    [fileManager copyItemAtPath:filePath toPath:destPath error:&error];
    
    [self clearTempLog];
}

+ (void)writefile:(int)midiEventChannel note:(int)midiEventNote velocity:(int)midiEventVelocity tick:(double)tick remark:(NSString*)remark{
    
    NSString* string = [NSString stringWithFormat:@"%@;channel=%d;starttime=%lf;notenumber=%d;\n",remark,midiEventChannel,tick,midiEventNote];
//    CILog(@"receive Processed note as :%@",string);
    NSArray *paths  = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,NSUserDomainMask,YES);
    NSString *homePath = [paths objectAtIndex:0];
    
    
    NSString *filePath = [homePath stringByAppendingPathComponent:@"tempFile"];
    
    NSFileManager *fileManager = [NSFileManager defaultManager];
    
    if(![fileManager fileExistsAtPath:filePath]) //如果不存在
    {
        [string writeToFile:filePath atomically:YES encoding:NSUTF8StringEncoding error:nil];
        return;
    }
    
    NSFileHandle *fileHandle = [NSFileHandle fileHandleForUpdatingAtPath:filePath];
    
    [fileHandle seekToEndOfFile];  //将节点跳到文件的末
    
    NSData* stringData  = [string dataUsingEncoding:NSUTF8StringEncoding];
    
    [fileHandle writeData:stringData]; //追加写入数据
    
    [fileHandle closeFile];
}

@end
