//
//  SheetView.m
//  Pods
//
//  Created by tanhui on 2017/8/7.
//
//

#import "SheetView.h"
#import "Constants.h"
#import "NoteM.h"
#import "ScoreM.h"
#import "PartM.h"
#import "MeasureM.h"

@interface SheetView ()
@property(nonatomic, strong) ScoreM* mScore;
@property(nonatomic , strong)CAShapeLayer* iconLayer;

@property(nonatomic,strong) NSArray* mLostNotes;
@property(nonatomic,strong) NSArray* mErrortNotes;
@property(nonatomic,strong) NSArray* mShortNotes;
@property(nonatomic,strong) NSArray* mLongNotes;


@end


@implementation SheetView
-(void)drawStartBar:(NSInteger)line{
    CGContextConcatCTM(UIGraphicsGetCurrentContext(), CGAffineTransformMakeTranslation(Part_Left_Margin , (line -1)* (self.mScore.mPartLineHeight+PartLineMargin) + Part_Top_Margin));
    UIBezierPath *path = [UIBezierPath bezierPath];
    [path moveToPoint:CGPointMake(0, 0)];
    [path addLineToPoint:CGPointMake(0, self.mScore.mPartLineHeight )];
    [path setLineWidth:LineWidth];
    [path stroke];
    CGContextConcatCTM(UIGraphicsGetCurrentContext(), CGAffineTransformMakeTranslation(-Part_Left_Margin , -(line -1)* (self.mScore.mPartLineHeight+PartLineMargin)-Part_Top_Margin ));
}

// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
    UIBezierPath *path = [UIBezierPath bezierPathWithRect:rect];
    [[UIColor whiteColor] setFill];
    [path fill];
    [[UIColor blackColor] setFill];
    // 绘制title
    CGSize sizeTitle = [self.mScore.mHeader.mWorkTitle sizeWithAttributes:@{NSFontAttributeName:[UIFont systemFontOfSize:20]}];
    [self.mScore.mHeader.mWorkTitle drawAtPoint:CGPointMake(CGRectGetMidX(rect)-sizeTitle.width*0.5, 10) withAttributes:@{NSFontAttributeName:[UIFont systemFontOfSize:20]}];
    // draw start Bar
    CGFloat clefY = Part_Top_Margin;
    // 设置partHeight
    for (int line = 1; line <= self.mScore.mLines; line++) {
        [self drawStartBar:line ];
    }
    // 绘制五线谱
    int pianoPartH = 0;
    for (PartM *part in self.mScore.mParts) {
        CGContextConcatCTM(UIGraphicsGetCurrentContext(), CGAffineTransformMakeTranslation(Part_Left_Margin , clefY ));
        [part drawRect:rect];
        CGContextConcatCTM(UIGraphicsGetCurrentContext(), CGAffineTransformMakeTranslation(-Part_Left_Margin , -clefY ));
        if (part.mProgram <= 8) {
            pianoPartH = clefY;
        }
        clefY = clefY + (PartMarin + PartHeight) * part.mStavesNum;
    }
}

-(void)clearResult{
    self.mLostNotes = nil;
    self.mErrortNotes = nil;
    self.mShortNotes = nil;
    self.mLongNotes = nil;
    [self setNeedsDisplay];
}

-(void)updateCusor:(DrawableNoteM*)note{
    MeasureM* measure = note.mMeasure;
    double X = measure.mStartX + note.mDefaultX + Part_Left_Margin;
    double Y = (measure.mLine - 1) * (self.mScore.mPartLineHeight + PartLineMargin) + Part_Top_Margin;
    UIBezierPath* path = [UIBezierPath bezierPathWithRect:CGRectMake(X, Y, note.mAjustDuration, self.mScore.mPartLineHeight)];
    self.iconLayer.path = path.CGPath;
    
    if (Y > self.mParentView.frame.size.height * 0.3) {
        self.mParentView.contentOffset = CGPointMake(0, Y-self.mParentView.frame.size.height * 0.3);
    }
}


-(instancetype)initWithFrame:(CGRect)frame score:(ScoreM*)score{
    if ([super initWithFrame:frame]) {
        _mScore = score;
    }
    return self;
}
-(CAShapeLayer *)iconLayer{
    if (!_iconLayer) {
        _iconLayer = [CAShapeLayer layer];
        _iconLayer.fillColor = [UIColor colorWithRed:122/255.0 green:122/255.0 blue:122/255.0 alpha:0.5].CGColor;
        [self.layer addSublayer:_iconLayer];
    }
    return _iconLayer;
}
@end
