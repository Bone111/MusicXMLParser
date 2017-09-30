//
//  CIViewController.m
//  musicXML
//
//  Created by tanhui on 2017/9/15.
//  Copyright © 2017年 tanhuiya. All rights reserved.
//

#import "CIViewController.h"
#import <musicXML/musicXML.h>
#import "ScoreViewController.h"

@interface CIViewController ()
@property(nonatomic,strong)NSArray* pathArr;
@end

@implementation CIViewController

static NSString* FilePathCell = @"FilePathCell";



- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    [self.navigationController setNavigationBarHidden:YES];
    
    NSArray* paths = [[NSBundle mainBundle] pathsForResourcesOfType:@"xml" inDirectory:@"Resource"];
    NSMutableArray* arr = @[].mutableCopy;
    for (NSString* path in paths) {
        NSString* name = [path lastPathComponent];
        [arr addObject:@{@"name":name,
                        @"path":path}];
    }
    self.pathArr = arr.copy;
    [self.tableView reloadData];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    UITableViewCell* cell = [tableView dequeueReusableCellWithIdentifier:FilePathCell];
    if (!cell) {
        cell = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:FilePathCell];
    }
    NSDictionary* dic = self.pathArr[indexPath.row];
    cell.textLabel.text = dic[@"name"];
    return cell;
}

-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return self.pathArr.count;
}
-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
//    if([[Connector defaultConnector] isConnected]){
        NSDictionary* dic = self.pathArr[indexPath.row];
        ScoreViewController* vc = [[ScoreViewController alloc]initWithFileName:dic[@"path"]];
        [self.navigationController pushViewController:vc animated:YES];
//    }else{
//        ConnectorViewController* connectVC = [[ConnectorViewController alloc]init];
//        [self.navigationController pushViewController:connectVC animated:YES];
//        
//    }
    
    
}
/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
