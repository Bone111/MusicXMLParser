//
//  SheetView.h
//  Pods
//
//  Created by tanhui on 2017/8/7.
//
//

#import <UIKit/UIKit.h>

@class ScoreM;
@class DrawableNoteM;
@interface SheetView : UIView

@property(nonatomic,weak) UIScrollView* mParentView;

-(instancetype)initWithFrame:(CGRect)frame score:(ScoreM*)score;

-(void)updateCusor:(DrawableNoteM*)note;

-(void)clearResult;
@end
