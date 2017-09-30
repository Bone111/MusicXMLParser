//
//  NoteM.m
//  iOSMusic
//
//  Created by tanhui on 2017/7/12.
//  Copyright © 2017年 tanhui. All rights reserved.
//

#import "NoteM.h"
#import "Constants.h"
#import "AccidM.h"
#import "MeasureM.h"
@implementation BeamM
@end

@implementation ForwardM
@end

@implementation BackupM
@end

@implementation NotationM

-(instancetype)initWithType:(ENotationType)value number:(NSInteger)number placement:(ENotationPlacement)placement{
    if([super init]){
        self.mValue = value;
        self.mNumber = number;
        self.mPlacement = placement;
    }
    return self;
}

@end

@implementation NoteM

+(instancetype)allocWithLetter:(ENoteStep)step andOctave:(NSInteger)actave{
    NoteM* note = [[NoteM alloc]init];
    note.mStep = step;
    note.mOctave = actave;
    return note;
}

- (int)dist:(NoteM*)n {
    return (self.mOctave - [n mOctave]) * 7 + (self.mStep - [n mStep]);
}
+(NoteM*)min:(NoteM*)x with:(NoteM*)y{
    if ([x dist:y] < 0)
        return x;
    else
        return y;
}

-(BOOL)isEqual:(NoteM*)object{
    return [self dist:object] == 0;
}

+(NoteM*)max:(NoteM*)x with:(NoteM*)y{
    if ([x dist:y] > 0)
        return x;
    else
        return y;
}
 
- (NoteM*)add:(NSInteger)offset {
    int num = self.mOctave * 7 + self.mStep;
    num += offset;
    if (num < 0) {
        num = 0;
    }
    NoteM* note = [[NoteM alloc]init];
    note.mOctave = num/7;
    note.mStep = num%7;
    return note;
}


+(NoteM*)getTop:(EClef)clef{
    NoteM * note = [[NoteM alloc]init];
    if (clef == EClef_TREBLE){
        note.mStep = ENoteStep_E;
        note.mOctave = 5;
    }else {
        note.mStep = ENoteStep_G;
        note.mOctave = 3;
    }
    return note;
}


-(void)setMAccid:(EAccidType)mAccid{
    _mAccid = mAccid;
    switch (mAccid) {
        case EAccidType_Flat:
            _mAlter = -1;
            break;
        case EAccidType_Sharp:
            _mAlter = 1;
            break;
        case EAccidType_Natural:
            _mAlter = 0;
            break;
        default:
            break;
    }
}
-(int)noteNumber{
    int mStepMap[7] = {0,2,4,5,7,9,11};
    int num =  mStepMap[self.mStep] + (self.mOctave+1)* 12 + self.mAlter;
    return num;
}

@end


@interface NoteGroupM()
@property(nonatomic, strong) NSMutableArray* mNotes;
@property(nonatomic, assign) NSInteger mDotNum;
@property(nonatomic, strong) NSMutableArray * accidArr;
@end
@implementation NoteGroupM

-(instancetype)initWithNotes:(NSMutableArray*) notes{
    if (![notes count]) {
        return nil;
    }
    if ([super init]){
        _mNotes = notes.mutableCopy;
        for (NoteM* note in _mNotes) {
            _mDotNum += note.mDotNum;
        }
    }
    return self;
}

-(void)addNote:(NoteM*)note{
    [_mNotes addObject:note];
    
    _mNotes = [_mNotes sortedArrayUsingComparator:^NSComparisonResult(NoteM* note1, NoteM* note2) {
        return [note1 dist:note2]<0;
    }].mutableCopy;
    NoteM* previous = nil;
    self.mDotNum = 0;
    for (NoteM* note in self.mNotes) {
        if (previous && [note dist:previous]>=-1) {
            note.oppsiteSide = YES;
        }
        self.mDotNum += note.mDotNum;
        previous = note;
    }
}

-(NSArray*)notes{
    return self.mNotes;
}
-(double)drawWidth{
    return NoteWidth;
}

-(void)drawRect:(CGRect)rect{
    int ytop = 0;
    NoteM* topStaff = [NoteM getTop:self.mCurrentAttr.mClef.mValue];
    [self drawAccid:ytop];
    [self drawNotes:ytop topStaff:topStaff];
    [self drawStem:ytop topStaff:topStaff];
}

-(int)drawAccid:(int)ytop {
    int xpos = 0;
    AccidM *prev = nil;
    if (self.accidArr.count) {
        xpos -= [[self.accidArr firstObject] drawWidth];
    }
    for (int i = 0; i < [self.accidArr count]; i++) {
        AccidM *symbol = [self.accidArr objectAtIndex:i];
        if (prev != nil && abs([[symbol mNote] dist:[prev mNote]]) < 6) {
            xpos -= [prev drawWidth];
        }
        
        CGContextConcatCTM(UIGraphicsGetCurrentContext(), CGAffineTransformMakeTranslation(xpos, 0));
        
        [symbol drawRect:CGRectZero];
        
        CGContextConcatCTM(UIGraphicsGetCurrentContext(), CGAffineTransformMakeTranslation(-xpos, 0));
        
        prev = symbol;
    }
    return 0;
}

-(void)drawStem:(int)ytop topStaff:(NoteM*)topStaff{
    if (self.mNotations.count) {
        [self drawNotationCurv:ytop topStaff:topStaff];
    }
    if (self.mStem == ENoteStem_None)return;
    [self drawVerticalLine:ytop topStaff:topStaff];
    if (self.mBeams.count) {
        [self drawBeamStem:ytop topStaff:topStaff];
    }else{
        [self drawCurvyStem:ytop topStaff:topStaff];
    }
    
}

- (void)drawNotationCurv:(int)ytop topStaff:(NoteM*)topstaff {
    
    NoteM* topStaff = [NoteM getTop:self.mCurrentAttr.mClef.mValue];
    for (NotationM* notation in self.mNotations) {
        UIBezierPath *path = [UIBezierPath bezierPath];
        double x_ori = 0,y_ori = 0 ,x_des = 0,y_des = 0;
        
        
        if (notation.mEnd && notation.mValue == ENotationType_Begin) {
            NoteGroupM* next = notation.mEnd;
            // 不是同一行的暂不处理
            if (self.mMeasure.mLine != next.mMeasure.mLine ) {
                continue;
            }
            
            x_ori = NoteWidth * 0.5 + 1;;
            x_des = x_ori + (next.mDefaultX + next.mAjustDuration*0.5 - next.drawWidth* 0.5 ) - (self.mDefaultX + self.mAjustDuration*0.5 - self.drawWidth* 0.5 );
            
            if(self.mMeasure != next.mMeasure){
                x_des += (self.mMeasure.mWidth);
            }
            
            if (notation.mPlacement == ENotationPlacement_Above) {
                // 计算 y_ori
                y_ori = [topStaff dist:self.mTop]*NoteHeight/2 - NoteHeight;
                if (self.mStem == ENoteStem_UP && self.mBeams.count) {
                    y_ori = self.mStemEndY - NoteHeight;
                }
                // 计算 y_des
                y_des = [topStaff dist:next.mTop]* NoteHeight/2 - NoteHeight;
                if (next.mStem == ENoteStem_UP && next.mBeams.count) {
                    y_des = next.mStemEndY - NoteHeight;
                }
            }else if (notation.mPlacement == ENotationPlacement_Below) {
                y_ori = self.mStemStartY + NoteHeight * 2;
                y_des = next.mStemStartY + NoteHeight * 2;
            }
            
            if(self.mStaffth != next.mStaffth){
                if (self.mStaffth == 1 && next.mStaffth == 2) {
                    y_des += (PartMarin + PartHeight);
                }else if (self.mStaffth == 2 && next.mStaffth == 1){
                    y_des -= (PartMarin + PartHeight);
                }
            }
        }
        CGPoint controlP = CGPointZero;
        CGPoint controlP2 = CGPointZero;
        double off = (x_des-x_ori)* 0.3;
        if (notation.mPlacement == ENotationPlacement_Above) {
            controlP = CGPointMake((x_des+x_ori)*0.5,(y_ori+y_des)*0.5-off);
            controlP2 = CGPointMake((x_des+x_ori)*0.5,(y_ori+y_des)*0.5-off-2);
        }else{
            controlP = CGPointMake((x_des+x_ori)*0.5,(y_ori+y_des)*0.5 + off);
            controlP2 = CGPointMake((x_des+x_ori)*0.5,(y_ori+y_des)*0.5 + off + 2);
        }
        
        [path moveToPoint:CGPointMake(x_ori, y_ori)];
        [path addQuadCurveToPoint:CGPointMake( x_des, y_des) controlPoint:controlP];
        [path addQuadCurveToPoint:CGPointMake( x_ori, y_ori) controlPoint:controlP2];
        [path stroke];
        break;
    }
}

- (void)drawBeamStem:(int)ytop topStaff:(NoteM*)topstaff {
    int i = 0;
    for (BeamM* beam in self.mBeams) {
        
        UIBezierPath *path = [UIBezierPath bezierPath];
        [path setLineWidth:LineWidth*3];
        double x_ori = 0,y_ori = 0 ,x_des = 0,y_des = 0;
        if (beam.mValue == EBeamType_Begin && beam.mEnd) {
            
            if (self.mStem == ENoteStem_UP) {
                y_ori =  i * LineWidth*5 + self.mStemEndY;
                x_ori = NoteWidth+1;
                y_des =  i * LineWidth*5 + beam.mEnd.mStemEndY;
                x_des = x_ori + (beam.mEnd.mDefaultX + beam.mEnd.mAjustDuration*0.5 - beam.mEnd.drawWidth* 0.5 ) - (self.mDefaultX + self.mAjustDuration*0.5 - self.drawWidth* 0.5 );
                if (self.mStem != beam.mEnd.mStem) {
                    y_des -= (PartMarin + PartHeight);
                    x_des -= [self drawWidth];
                }
            }else if(self.mStem == ENoteStem_DOWN){
                y_des =  - i * LineWidth*5 + beam.mEnd.mStemEndY;
                y_ori = - i * LineWidth*5 + self.mStemEndY;
                x_ori = 1;
                x_des = x_ori + (beam.mEnd.mDefaultX + beam.mEnd.mAjustDuration*0.5 - beam.mEnd.drawWidth* 0.5 ) - (self.mDefaultX + self.mAjustDuration*0.5 - self.drawWidth* 0.5 );
                if (self.mStem != beam.mEnd.mStem) {
                    y_des += PartMarin + PartHeight;
                    x_des += [self drawWidth];
                }
            }
            
        }if (beam.mValue == EBeamType_End_BACK){
            if (self.mStem == ENoteStem_UP) {
                y_ori =  i * LineWidth*5 + self.mStemEndY;
                x_ori = NoteWidth+1;
                x_des = x_ori -NoteWidth*0.5;
                y_des = y_ori;
                
            }else if(self.mStem == ENoteStem_DOWN){
                y_ori =  - i * LineWidth*5 + self.mStemEndY;
                x_ori = 1;
                y_des = y_ori;
                x_des = x_ori-NoteWidth*0.5;
            }
        }
        [path moveToPoint:CGPointMake(x_ori, y_ori)];
        [path addLineToPoint:CGPointMake( x_des, y_des)];
        [path stroke];
        i++;
    }
}

- (void)drawCurvyStem:(int)ytop topStaff:(NoteM*)topstaff {
    UIBezierPath *path = [UIBezierPath bezierPath];
    [path setLineWidth:1];
    
    int xstart = 0;
    if (self.mStem == ENoteStem_DOWN)
        xstart = LineSpace/4 ;
    else
        xstart = LineSpace/4 + NoteWidth;
    
    double curX_offset = LineSpace-1,curY_offset = NoteHeight*2;
    
    if (self.mStem == ENoteStem_UP) {
        int ystem = self.mStemEndY;
        
        if (self.mType == ENoteType_EIGTHTH ||
            self.mType == ENoteType_SIXTEENTH ||
//            duration == Triplet ||
            self.mType == ENoteType_TIRTH_SECOND) {
            
            [path moveToPoint:CGPointMake(xstart, ystem)];
            [path addCurveToPoint:CGPointMake(xstart + curX_offset,
                                              ystem + curY_offset)
                    controlPoint1:CGPointMake(xstart,
                                              ystem + LineSpace)
                    controlPoint2:CGPointMake(xstart + LineSpace*2,
                                              ystem + NoteHeight*1.5)
             ];
            
            [path moveToPoint:CGPointMake(xstart, ystem+3)];
            [path addCurveToPoint:CGPointMake(xstart + curX_offset,
                                              ystem + curY_offset)
                    controlPoint1:CGPointMake(xstart,
                                              ystem + LineSpace)
                    controlPoint2:CGPointMake(xstart + LineSpace*2,
                                              ystem + NoteHeight*1.5)
             ];
        }
        ystem += NoteHeight;
        
        if (self.mType == ENoteType_SIXTEENTH ||
            self.mType == ENoteType_TIRTH_SECOND) {
            
            [path moveToPoint:CGPointMake(xstart, ystem)];
            [path addCurveToPoint:CGPointMake(xstart + curX_offset,
                                              ystem + curY_offset)
                    controlPoint1:CGPointMake(xstart,
                                              ystem + LineSpace)
                    controlPoint2:CGPointMake(xstart + LineSpace*2,
                                              ystem + NoteHeight*1.5)
             ];
            
            [path moveToPoint:CGPointMake(xstart, ystem+3)];
            [path addCurveToPoint:CGPointMake(xstart + curX_offset,
                                              ystem + curY_offset)
                    controlPoint1:CGPointMake(xstart,
                                              ystem + LineSpace)
                    controlPoint2:CGPointMake(xstart + LineSpace*2,
                                              ystem + NoteHeight*1.5)
             ];
            
        }
        
        ystem += NoteHeight;
        if (self.mType == ENoteType_TIRTH_SECOND) {
            [path moveToPoint:CGPointMake(xstart, ystem)];
            [path addCurveToPoint:CGPointMake(xstart + curX_offset,
                                              ystem + curY_offset)
                    controlPoint1:CGPointMake(xstart,
                                              ystem + LineSpace)
                    controlPoint2:CGPointMake(xstart + LineSpace*2,
                                              ystem + NoteHeight*1.5)
             ];
            
            [path moveToPoint:CGPointMake(xstart, ystem+3)];
            [path addCurveToPoint:CGPointMake(xstart + curX_offset,
                                              ystem + curY_offset)
                    controlPoint1:CGPointMake(xstart,
                                              ystem + LineSpace)
                    controlPoint2:CGPointMake(xstart + LineSpace*2,
                                              ystem + NoteHeight*1.5)
             ];
        }
    }
    
    else if (self.mStem == ENoteStem_DOWN) {
        int ystem = self.mStemEndY;
        
        if (self.mType == ENoteType_EIGTHTH |
//            duration == Triplet ||
            self.mType == ENoteType_SIXTEENTH ||
            self.mType == ENoteType_TIRTH_SECOND) {
            
            [path moveToPoint:CGPointMake(xstart, ystem)];
            [path addCurveToPoint:CGPointMake(xstart + LineSpace,
                                              ystem - NoteHeight*2 )
                    controlPoint1:CGPointMake(xstart,
                                              ystem - LineSpace)
                    controlPoint2:CGPointMake(xstart + LineSpace*2,
                                              ystem - NoteHeight*1.5)
             ];
            [path moveToPoint:CGPointMake(xstart, ystem-3)];
            [path addCurveToPoint:CGPointMake(xstart + LineSpace,
                                              ystem - NoteHeight*2 )
                    controlPoint1:CGPointMake(xstart,
                                              ystem - LineSpace)
                    controlPoint2:CGPointMake(xstart + LineSpace*2,
                                              ystem - NoteHeight*1.5)
             ];
        }
        ystem -= NoteHeight;
        
        if (self.mType == ENoteType_SIXTEENTH ||
            self.mType == ENoteType_TIRTH_SECOND) {
            
            [path moveToPoint:CGPointMake(xstart, ystem)];
            [path addCurveToPoint:CGPointMake(xstart + LineSpace,
                                              ystem - NoteHeight*2 )
                    controlPoint1:CGPointMake(xstart,
                                              ystem - LineSpace)
                    controlPoint2:CGPointMake(xstart + LineSpace*2,
                                              ystem - NoteHeight*1.5)
             ];
            [path moveToPoint:CGPointMake(xstart, ystem-3)];
            [path addCurveToPoint:CGPointMake(xstart + LineSpace,
                                              ystem - NoteHeight*2 )
                    controlPoint1:CGPointMake(xstart,
                                              ystem - LineSpace)
                    controlPoint2:CGPointMake(xstart + LineSpace*2,
                                              ystem - NoteHeight*1.5)
             ];
        }
        
        ystem -= NoteHeight;
        if (self.mType == ENoteType_TIRTH_SECOND) {
            [path moveToPoint:CGPointMake(xstart, ystem)];
            [path addCurveToPoint:CGPointMake(xstart + LineSpace,
                                              ystem - NoteHeight*2 )
                    controlPoint1:CGPointMake(xstart,
                                              ystem - LineSpace)
                    controlPoint2:CGPointMake(xstart + LineSpace*2,
                                              ystem - NoteHeight*1.5)
             ];
            [path moveToPoint:CGPointMake(xstart, ystem-3)];
            [path addCurveToPoint:CGPointMake(xstart + LineSpace,
                                              ystem - NoteHeight*2 )
                    controlPoint1:CGPointMake(xstart,
                                              ystem - LineSpace)
                    controlPoint2:CGPointMake(xstart + LineSpace*2,
                                              ystem - NoteHeight*1.5)
             ];
        }
    }
    [path stroke];
}

-(void)setOffset:(double)xOff{
    self.mDefaultX += xOff;
}


-(NSInteger)mStemEndY{
    if (!_mStemEndY){
        NoteM* topStaff = [NoteM getTop:self.mCurrentAttr.mClef.mValue];
        if (self.mStem == ENoteStem_UP) {
            _mStemEndY =  [topStaff dist:self.mTop]* NoteHeight/2  - 3*NoteHeight;
        }else if (self.mStem == ENoteStem_DOWN){
            _mStemEndY =  [topStaff dist:self.mBottom]* NoteHeight/2 + NoteHeight + 3*NoteHeight;
        }else if (self.mStem == ENoteStem_None){
            _mStemEndY = [topStaff dist:self.mBottom]* NoteHeight/2 + NoteHeight;
        }
    }
    return _mStemEndY;
}

-(NSInteger)mStemStartY{
    if (!_mStemStartY) {
        NoteM* topStaff = [NoteM getTop:self.mCurrentAttr.mClef.mValue];
        if (self.mStem == ENoteStem_UP) {
            _mStemStartY =  [topStaff dist:self.mBottom] * NoteHeight/2 + NoteHeight/3
            ;
        }else if (self.mStem == ENoteStem_DOWN){
            _mStemStartY = [topStaff dist:self.mTop] * NoteHeight/2 + NoteHeight - NoteHeight/3;
        }else if (self.mStem == ENoteStem_None){
            _mStemStartY = [topStaff dist:self.mTop] * NoteHeight/2;
        }
    }
    return _mStemStartY;

}

-(NoteM *)mTop{
    if(!_mTop){
        _mTop = self.mNotes[0];
        for (NoteM* note in self.mNotes) {
            if ((note.mStep + note.mOctave * 7)>(_mTop.mStep + _mTop.mOctave * 7)) {
                _mTop = note;
            }
        }
    }
    return _mTop;
}

-(NoteM *)mBottom{
    if (!_mBottom) {
        _mBottom = self.mNotes[0];
        for (NoteM* note in self.mNotes) {
            if ((note.mStep + note.mOctave * 7)<(_mBottom.mStep + _mBottom.mOctave * 7)) {
                _mBottom = note;
            }
        }
    }
    return _mBottom;
}

-(NoteM*)getTopNote{
    return self.mTop;
}
-(NoteM*)getBottomNote{
    return self.mBottom;
}

-(NSMutableArray *)accidArr{
    if (!_accidArr) {
        _accidArr = @[].mutableCopy;
        for (NoteM* note in self.mNotes) {
            if (note.mAccid != EAccidType_None) {
                AccidM* accid = [[AccidM alloc]initWithType:note.mAccid andNote:note andClef:note.mCurrentAttr.mClef.mValue];
                [_accidArr addObject:accid];
            }
        }
    }
    return _accidArr;
}

-(void)drawVerticalLine:(int)ytop topStaff:(NoteM*)topstaff {
    int xstart = 0;
    
    if (self.mStem == ENoteStem_DOWN){
        xstart = LineSpace/4 ;
    }
    else{
        xstart = LineSpace/4 + NoteWidth;
    }
    
    UIBezierPath *path = [UIBezierPath bezierPath];
    [path moveToPoint:CGPointMake(xstart, self.mStemStartY)];
    [path addLineToPoint:CGPointMake(xstart, self.mStemEndY)];
    [path stroke];
    
//    if (self.mStem == ENoteStem_UP) {
//        int y1 = ytop + [topstaff dist:self.mBottom] * NoteHeight/2
//        + NoteHeight/4; 
////        NoteM* end = [self.mTop calculateEnd];
//        int ystem = ytop + [topstaff dist:self.mTop] * NoteHeight/2
//        + NoteHeight/4 + self.mEndY;
//        
//        UIBezierPath *path = [UIBezierPath bezierPath];
//        [path moveToPoint:CGPointMake(xstart, y1)];
//        [path addLineToPoint:CGPointMake(xstart, ystem)];
//        [path stroke];
//    }
//    else if (self.mStem == ENoteStem_DOWN) {
//        int y1 = ytop + [topstaff dist:self.mTop] * NoteHeight/2
//        + NoteHeight - NoteHeight/2;
////        NoteM* end = [self.mBottom calculateEnd];
//        int ystem =ytop + [topstaff dist:self.mBottom] * NoteHeight/2
//        + NoteHeight - NoteHeight/2 + self.mEndY;
//        
//        UIBezierPath *path = [UIBezierPath bezierPath];
//        [path moveToPoint:CGPointMake(xstart, y1)];
//        [path addLineToPoint:CGPointMake(xstart, ystem)];
//        [path stroke];
//    }
}

-(void)drawNotes:(int)ytop topStaff:(NoteM*)topStaff{
    UIBezierPath *path;
    
    for (NoteM* note in self.mNotes) {
        int ynote = [topStaff dist:note] * NoteHeight/2;
        int xnote = LineSpace/4;
        /* Draw rotated ellipse.  You must first translate (0,0)
         * to the center of the ellipse.
         */
        int x_offset = xnote;
        
        if (note.oppsiteSide) {
            if (note.mStem == ENoteStem_UP) {
                x_offset += NoteWidth;
            }else{
                x_offset -= NoteWidth;
            }
        }
        
        UIColor *color = [UIColor blackColor];
        if(note.mNoteHeadType == ENoteHeadType_x){
            CGContextConcatCTM(UIGraphicsGetCurrentContext(), CGAffineTransformMakeTranslation(1,ynote));
            path = [UIBezierPath bezierPath];
            [path setLineWidth:LineWidth];
            [color setStroke];
            [path moveToPoint:CGPointZero];
            [path addLineToPoint:CGPointMake(NoteWidth, LineSpace)];
            [path moveToPoint:CGPointMake(0, LineSpace)];
            [path addLineToPoint:CGPointMake(NoteWidth, 0)];
            [path stroke];
            CGContextConcatCTM(UIGraphicsGetCurrentContext(), CGAffineTransformMakeTranslation(-1,-ynote));
        }else{
            CGContextConcatCTM(UIGraphicsGetCurrentContext(), CGAffineTransformMakeTranslation(x_offset,(ynote )));
            CGContextRotateCTM(UIGraphicsGetCurrentContext(),  -20 * M_PI / 180);
            
            if (note.mType == ENoteType_WHOLE ||
                note.mType == ENoteType_HALF) {
                path = [UIBezierPath bezierPath];
                [path setLineWidth:1];
                [color setStroke];
                [path appendPath:[UIBezierPath bezierPathWithOvalInRect:CGRectMake(-NoteWidth/6.33, NoteWidth/5.73, NoteWidth, NoteHeight-1)]];
                [path appendPath:[UIBezierPath bezierPathWithOvalInRect:CGRectMake(-NoteWidth/6.33, NoteWidth/5.73 + 1, NoteWidth, NoteHeight-2)]];
                [path appendPath:[UIBezierPath bezierPathWithOvalInRect:CGRectMake(-NoteWidth/6.33, NoteWidth/5.73 + 1, NoteWidth, NoteHeight-3)]];

                [path stroke];
            }
            else {
                path = [UIBezierPath bezierPath];
                [path setLineWidth:LineWidth];
                [color setFill];
                [path appendPath:[UIBezierPath bezierPathWithOvalInRect:CGRectMake(-NoteWidth/6.33, NoteWidth/5.73, NoteWidth, NoteHeight-1)]];
                [path fill];
            }
            path = [UIBezierPath bezierPath];
            
            [path setLineWidth:LineWidth];
            [[UIColor blackColor] setStroke];
            [path appendPath:[UIBezierPath bezierPathWithOvalInRect:CGRectMake(-NoteWidth/6.33, NoteWidth/5.73, NoteWidth, NoteHeight-1)]];
            [path stroke];
            CGContextRotateCTM(UIGraphicsGetCurrentContext(),  20 * M_PI / 180);
            CGContextConcatCTM(UIGraphicsGetCurrentContext(), CGAffineTransformMakeTranslation(-x_offset,-(ynote )));
        }
        
        
        /* Draw horizontal lines if note is above/below the staff */
        path = [UIBezierPath bezierPath];
        [path setLineWidth:LineWidth];
        [[UIColor blackColor] setStroke];
        NoteM *top = [topStaff add:1];
        int dist = [note dist:top];
        int y = ytop;
        
        if (dist >= 2) {
            for (int i = 2; i <= dist; i += 2) {
                y -= NoteHeight;
                
                [path moveToPoint:CGPointMake(xnote - LineSpace/3.0, y)];
                [path addLineToPoint:CGPointMake(xnote + NoteWidth + LineSpace/3.0, y) ];
                
            }
        }
        
        NoteM *bottom = [top add:(-8)];
        y = ytop + (LineSpace + LineWidth) * 4 ;
        dist = [bottom dist:note];
        if (dist >= 2) {
            for (int i = 2; i <= dist; i+= 2) {
                y += NoteHeight;
                [path moveToPoint:CGPointMake(xnote - LineSpace/3.0, y) ];
                [path addLineToPoint:CGPointMake(xnote + NoteWidth + LineSpace/3.0, y) ];
            }
        }
        [path stroke];
        
        /* End drawing horizontal lines */
    }
    
    /* Draw a dot if this is a dotted duration. */
    if (self.mDotNum) {
        int xnote = LineSpace/4;
        int ynote = [topStaff dist:self.mTop] * NoteHeight/2;
        UIBezierPath *path = [UIBezierPath bezierPath];
        [path setLineWidth:LineWidth];
        [[UIColor blackColor] setFill];
        [[UIColor blackColor] setStroke];
        for (int i = 0; i<self.mDotNum; i++) {
            [path appendPath:[UIBezierPath bezierPathWithOvalInRect:CGRectMake(xnote + NoteWidth + LineSpace/3, ynote + LineSpace/3, 3, 3)]];
            ynote += NoteHeight;
        }
        [path fill];
    }
}





@end
