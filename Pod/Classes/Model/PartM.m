//
//  ScorePartWiseM.m
//  iOSMusic
//
//  Created by tanhui on 2017/7/11.
//  Copyright © 2017年 tanhui. All rights reserved.
//

#import "PartM.h"
#import "MeasureM.h"
#import "Constants.h"
#import "ScoreM.h"

@interface PartM ()
@end

@implementation PartM

-(instancetype)initWithName:(NSString*)name program:(NSInteger)program Measures:(NSArray*) measures staves:(NSInteger)staff{
    if ([super init]) {
        _mName = name;
        _mMeasures = measures;
        _mStavesNum = staff;
        _mProgram = program;
    }
    return self;
}

#pragma mark PUBLIC
-(void)drawRect:(CGRect)rect{
//    [self.mName drawAtPoint:CGPointMake(0, 10) withAttributes:@{NSFontAttributeName:[UIFont systemFontOfSize:15]}];
//    [self drawPartName];
//    CGContextConcatCTM(UIGraphicsGetCurrentContext(), CGAffineTransformMakeTranslation(0 , 0 ));
    // draw measures
    float horiWidth = 0.0;
    int line = 0;
    
    
    
    for (MeasureM* measure in self.mMeasures) {
        
        if (measure.mLine != line) {
            horiWidth  = 0;
            line = measure.mLine;
        }
        
        CGContextConcatCTM(UIGraphicsGetCurrentContext(), CGAffineTransformMakeTranslation(horiWidth , (measure.mLine -1)* (self.mScore.mPartLineHeight+PartLineMargin) ));
        
        [measure drawRect:rect];
        
        [self drawEndLine:measure.mWidth];
        [self drawLine:measure.mWidth];
        CGContextConcatCTM(UIGraphicsGetCurrentContext(), CGAffineTransformMakeTranslation(-horiWidth , -(measure.mLine -1)* (self.mScore.mPartLineHeight+PartLineMargin)  ));
        horiWidth += measure.mWidth;
        
        
    }
//    CGContextConcatCTM(UIGraphicsGetCurrentContext(), CGAffineTransformMakeTranslation(0, 0 ));
}


-(void)drawPartName {
    CGSize size = [self.mName sizeWithAttributes:@{NSFontAttributeName:[UIFont systemFontOfSize:15]}];
    [self.mName drawInRect:CGRectMake(0, 5, 30, 20) withAttributes:@{NSFontAttributeName:[UIFont systemFontOfSize:15]}];
}





-(void)drawEndLine:(double)width{
    int yend =  (int) (PartHeight + (PartHeight + PartMarin) * (self.mStavesNum -1));
    UIBezierPath *path = [UIBezierPath bezierPath];
    [path moveToPoint:CGPointMake(width, 0)];
    [path addLineToPoint:CGPointMake(width, yend)];
    [path setLineWidth:LineWidth];
    [path stroke];
}

-(void)drawLine:(double)width {
    for (NSInteger index = 0 , ytop = 0 ;index < self.mStavesNum ; index++){
        
        CGContextConcatCTM(UIGraphicsGetCurrentContext(), CGAffineTransformMakeTranslation(0, ytop));
        
        UIBezierPath *path = [UIBezierPath bezierPath];
        for (int line = 1, y = 0; line <= 5; line++) {
            [path moveToPoint:CGPointMake(0, y)];
            [path addLineToPoint:CGPointMake(width, y)];
            y += LineWidth + LineSpace;
        }
        [path stroke];
        [[UIColor blackColor] setStroke];
        
        CGContextConcatCTM(UIGraphicsGetCurrentContext(), CGAffineTransformMakeTranslation(0, -ytop));
        
        ytop += PartMarin + PartHeight;
    }
    
}
@end
