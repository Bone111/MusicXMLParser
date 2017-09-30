//
//  Constants.h
//  iOSMusic
//
//  Created by tanhui on 2017/7/12.
//  Copyright © 2017年 tanhui. All rights reserved.
//

#ifndef Constants_h
#define Constants_h

#define Theta 10.0
#define DivisionUnit 32.0

#define Part_Left_Margin 10
#define Part_Top_Margin 60

#define LineSpace 5
#define LineWidth 1
#define PartHeight (4*LineSpace+5*LineWidth)
#define NoteHeight (LineSpace+LineWidth)
#define NoteWidth  (3 * LineSpace) / 2

#define PartMarin  (PartHeight + 10)

#define ScoreDidReceiveMidiOnNotification @"ScoreDidReceiveMidiOnNotification"
#define ScoreDidReceiveMidiOffNotification @"ScoreDidReceiveMidiOffNotification"

#ifdef DEBUG//﻿
#define CILog(format, ...) printf("\n[%s] %s [第%d行] %s\n", __TIME__, __FUNCTION__, __LINE__, [[NSString stringWithFormat:format, ## __VA_ARGS__] UTF8String]);
#else//﻿
#define CILog(...)
#endif


static int PartLineMargin = 60 ; // 换行的行间距

#endif /* Constants_h */
