//
//  UIImage+music.m
//  Pods
//
//  Created by tanhui on 2017/7/21.
//
//

#import "UIImage+music.h"

@implementation UIImage (music)
+(UIImage*)imageForResource:(NSString*)path ofType:(NSString*)type inBundle:(NSBundle*)bundle {
    
    path = [NSString stringWithFormat:@"musicXML.bundle/%@",path];
    
    return [UIImage imageWithContentsOfFile:[bundle pathForResource:path ofType:type]];
}


@end
