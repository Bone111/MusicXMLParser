//
//  PartWiseMeasure.m
//  iOSMusic
//
//  Created by tanhui on 2017/7/11.
//  Copyright © 2017年 tanhui. All rights reserved.
//

#import "MeasureM.h"
#import "Constants.h"
#import "NoteM.h"
#import "RestM.h"
@interface MeasureM ()
@end

#define MeasureLeftMargin 10
@implementation MeasureM
-(instancetype)initWithWidth:(float)width musicDataGroup:(NSArray< DrawableNoteM*>*)musicDataGroup staves:(NSInteger)staff{
    if ([super init]) {
        _mMeasureDatas = musicDataGroup;
        _mWidth = width;
        _mStavesNum = staff;
        __weak typeof(self) _weakSelf = self;
        [musicDataGroup enumerateObjectsUsingBlock:^(DrawableNoteM * _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
            obj.mMeasure = _weakSelf;
        }];
    }
    return self;
}
-(UIColor *) randomColor {
    CGFloat hue = ( arc4random() % 256 / 256.0 );  //0.0 to 1.0
    CGFloat saturation = ( arc4random() % 128 / 256.0 ) + 0.5;  // 0.5 to 1.0,away from white
    CGFloat brightness = ( arc4random() % 128 / 256.0 ) + 0.5;  //0.5 to 1.0,away from black
    return [UIColor colorWithHue:hue saturation:saturation brightness:brightness alpha:1];
}
-(void)drawRect:(CGRect)rect{
    
    for (DrawableNoteM* musicData in self.mMeasureDatas) {
        // only draw property and notes
        
        int y_offset = 0;
        if (musicData.mStaffth != 1){
            y_offset += (PartMarin + PartHeight);
        }
        // 添加随机填充色
//        CGContextConcatCTM(UIGraphicsGetCurrentContext(), CGAffineTransformMakeTranslation(musicData.mDefaultX, y_offset));
//        UIBezierPath* path = [UIBezierPath bezierPathWithRect:CGRectMake(0, 0, musicData.mAjustDuration, 10)];
//        [[self randomColor]setFill];
//        [path fill];
//        [path stroke];
//        CGContextConcatCTM(UIGraphicsGetCurrentContext(), CGAffineTransformMakeTranslation(-(musicData.mDefaultX), -y_offset));
        
        if ([musicData isKindOfClass:[RestM class]] && ((RestM*)musicData).mHasMeasure) {
            // 处理 占整个measure的rest
            CGContextConcatCTM(UIGraphicsGetCurrentContext(), CGAffineTransformMakeTranslation(self.mWidth*0.5 , y_offset));
            [musicData drawRect:rect];
            CGContextConcatCTM(UIGraphicsGetCurrentContext(), CGAffineTransformMakeTranslation(-(self.mWidth*0.5), -y_offset));
        }else {
            CGContextConcatCTM(UIGraphicsGetCurrentContext(), CGAffineTransformMakeTranslation(musicData.mDefaultX+musicData.mAjustDuration*0.5 - [musicData drawWidth]*0.5, y_offset));
            
            [musicData drawRect:rect];
            
            CGContextConcatCTM(UIGraphicsGetCurrentContext(), CGAffineTransformMakeTranslation(-(musicData.mDefaultX+musicData.mAjustDuration*0.5 - [musicData drawWidth]*0.5), -y_offset));
        }
        
        
    }

}

-(double)mWidth{
    if (self.mWidthRatio) {
        return _mWidth*self.mWidthRatio;
    }
    return _mWidth;
}

-(void)setMeasureDatas:(NSArray< DrawableNoteM*>*)measureDatas{
    _mMeasureDatas = measureDatas;
}

@end
