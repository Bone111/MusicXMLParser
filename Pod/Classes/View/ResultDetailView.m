//
//  ResultDetailView.m
//  FBSnapshotTestCase
//
//  Created by tanhui on 2017/9/21.
//

#import "ResultDetailView.h"
#import "ResultDetailM.h"
#import "DrawableNoteM.h"
#import "MeasureM.h"
#import "ScoreM.h"
#import "ScoreViewController.h"
#import "Constants.h"
#import "NoteM.h"
#import "PartM.h"

@interface ResultDetailView ()
@property(nonatomic,copy)NSArray<ResultDetailM*>* mResult;
@property(nonatomic,strong)ScoreM* mScore;
@end

@implementation ResultDetailView

-(instancetype)initWithFrame:(CGRect)frame errorResults:(NSArray<ResultDetailM*>*)results score:(ScoreM*)score{
    if ([self initWithFrame:frame]) {
        self.mResult = results;
        self.mScore = score;
        self.backgroundColor = [UIColor clearColor];
        [self setUp];
    }
    return self;
}

-(void)setUp{
    CGFloat clefY = Part_Top_Margin;
    int pianoPartH = 0;
    for (PartM *part in self.mScore.mParts) {
        if (part.mProgram <= 8) {
            pianoPartH = clefY;
            break;
        }
        clefY = clefY + (PartMarin + PartHeight) * part.mStavesNum;
    }
    
    NSMutableArray* startTimeArr = @[].mutableCopy;
    ResultDetailM* previous = nil;
    NSMutableArray* temp = nil;
    for (ResultDetailM* result in self.mResult) {
        if (result.mStartTime == previous.mStartTime && result.mStaffIndex == previous.mStaffIndex) {
            [temp addObject:result];
        }else{
            temp = @[result].mutableCopy;
            [startTimeArr addObject:temp];
        }
        previous = result;
    }
    
    for (NSMutableArray* arr in startTimeArr) {
        ResultDetailM* result = [arr firstObject];
        CGRect rect = [self getRectByStartTime:result.mStartTime staff:(int)result.mStaffIndex offset:pianoPartH];
        CircleView * a = [[CircleView alloc]initWithResultMs:arr.copy frame:rect];
        [self addSubview:a];
    }
}

-(CGRect)getRectByStartTime:(double)startTime  staff:(int)staffIndex offset:(double)yoffset{
    NoteGroupM* selectNote = nil;
    int tempStaff = 0;
    for (PartM* part in self.mScore.mParts){
        if(part.mProgram > 8){
            continue;
        }
        for (MeasureM* measure in part.mMeasures) {
            DrawableNoteM* lastNote = [measure.mMeasureDatas lastObject];
            if (startTime >= measure.mStartTime &&startTime <=  (lastNote.mStartTime + lastNote.mDuration) ){
                for (DrawableNoteM* note in measure.mMeasureDatas) {
                    if ([note isKindOfClass:[NoteGroupM class]]&&
                        (note.mStaffth + tempStaff == staffIndex) &&
                        startTime == note.mStartTime) {
                        selectNote = (NoteGroupM*)note;
                        break;
                    }
                }
            }
        }
        tempStaff += part.mStavesNum;
    }
    MeasureM*  measure = selectNote.mMeasure;
    double top = 0,end = 0;
    if (selectNote.mStem == ENoteStem_UP) {
        top = selectNote.mStemEndY - NoteHeight;
        end = selectNote.mStemStartY + NoteHeight;
    }else if (selectNote.mStem == ENoteStem_DOWN) {
        top = selectNote.mStemStartY - NoteHeight;
        end = selectNote.mStemEndY + NoteHeight;
    }else{
        top = selectNote.mStemStartY - NoteHeight;
        end = selectNote.mStemEndY + NoteHeight;
    }
    double x = selectNote.mMeasure.mStartX + selectNote.mDefaultX + selectNote.mAjustDuration * 0.5 + Part_Left_Margin - NoteWidth * 2;
    double partOffset = (measure.mLine - 1) * (self.mScore.mPartLineHeight + PartLineMargin) + (staffIndex - 1)*(PartMarin + PartHeight);
    return CGRectMake(x, partOffset + top + yoffset, 4* NoteWidth, end - top);
}


@end

@implementation CircleView

-(instancetype)initWithResultMs:(NSArray<ResultDetailM*>*)resultMs frame:(CGRect)frame{
    if ([super initWithFrame:frame]) {
        self.detailMArr = resultMs;
        self.backgroundColor = [UIColor clearColor];
        UILongPressGestureRecognizer* longGes = [[UILongPressGestureRecognizer alloc]initWithTarget:self action:@selector(showMessage:)];
        [self addGestureRecognizer:longGes];
    }
    return self;
}

-(void)drawRect:(CGRect)rect{
    UIBezierPath* bPath = [UIBezierPath bezierPathWithOvalInRect:rect];
    ResultDetailM* first = [self.detailMArr firstObject];
    if(first.mErrorType == EResultErrorType_Lost){
        [[UIColor greenColor]set];
    }else{
        [[UIColor redColor]set];
    }
    [bPath setLineWidth:2.0];
    [bPath stroke];
}

-(void)showMessage:(UIGestureRecognizer*)ges {
    CGPoint point = [ges locationInView:[UIApplication sharedApplication].keyWindow];
    ScoreViewController* parentVC = [self findViewController:self];
    ErrorListViewController* popVc = [[ErrorListViewController alloc]init];
    popVc.detailMList = self.detailMArr;
    popVc.view.backgroundColor = [UIColor whiteColor];
    popVc.modalPresentationStyle = UIModalPresentationPopover;
    popVc.preferredContentSize = CGSizeMake(100, 100);

    UIPopoverPresentationController* popPresent = popVc.popoverPresentationController;
    popPresent.sourceRect = self.bounds;
    popPresent.sourceView = self;
    if (point.y < [UIScreen mainScreen].bounds.size.height * 0.5) {
        popPresent.permittedArrowDirections = UIPopoverArrowDirectionUp;
    }else{
        popPresent.permittedArrowDirections = UIPopoverArrowDirectionDown;
    }
    popPresent.delegate = parentVC;
    [parentVC presentViewController:popVc animated:YES completion:nil];
}


- (ScoreViewController *)findViewController:(UIView *)sourceView{
    id target = sourceView;
    while (target) {
        target = ((UIResponder *)target).nextResponder;
        if ([target isKindOfClass:[ScoreViewController class]]) {
            break;
        }
    }
    return (ScoreViewController*)target;
}

@end

@implementation ErrorListViewController
-(void)viewDidLoad{
    [super viewDidLoad];
    self.tableView.tableFooterView = [UIView new];
}
-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return self.detailMList.count;
}
-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    NSString* cellStr = @"errorCellIdentifier";
    ResultDetailM* detailM = self.detailMList[indexPath.row];
    UITableViewCell* cell = [tableView dequeueReusableCellWithIdentifier:cellStr];
    if (!cell) {
        cell = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:cellStr];
        cell.textLabel.font = [UIFont systemFontOfSize:12];
        cell.selectionStyle = UITableViewCellSelectionStyleNone;
    }
    NSString* tip = nil;
    if (detailM.mErrorType == EResultErrorType_Lost) {
        tip = [NSString stringWithFormat:@"%ld 漏键",detailM.mNoteNumber];
    }else if (detailM.mErrorType == EResultErrorType_Error) {
        tip = [NSString stringWithFormat:@"错键%ld 应为%ld",detailM.mErrorNumber,detailM.mNoteNumber];
    }
    cell.textLabel.text = tip;
    return cell;
}
-(void)setDetailMList:(NSArray<ResultDetailM *> *)detailMList{
    _detailMList = detailMList;
    [self.tableView reloadData];
}
-(CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath{
    return 30;
}
@end
