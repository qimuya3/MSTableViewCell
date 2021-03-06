//
//  MSSTableView.h
//  MSSTableView
//
//  Created by Marshal on 26/12/13.
//  Copyright (c) 2013 Marshal. All rights reserved.
//

#import <UIKit/UIKit.h>

/** 
 *  MSSTableView is a custom table view class extended from UITableView class. This class provides a single-level hierarchical
 *  structure for your contents. In order to minimalize the effectiveness of the table view, the default insertion and remove 
 *  mechanism of UITableView (insertRowsAtIndexPaths:withRowAnimation: and deleteRowsAtIndexPaths:withRowAnimation:) is used.
 *  Main rows of your table view, which can be expandable or not must be instances of MSSTableViewCell class. Subrows can be
 *  instances of any class that is extended from UITableViewCell.
 */

@class MSSTableView;

@class MSSTableViewCell;

#pragma mark - MSSTableViewDelegate

@protocol MSSTableViewDelegate <UITableViewDataSource, UITableViewDelegate>

@required

/**
 * Returns the number of the subrows for the expandable row at the given index path.
 *
 *  @param tableView The instance of MSSTableView class.
 *
 *  @param indexPath The index path of the expandable row. It is the value for the expandable row before expanding.
 *
 *  @return The number of the subrows.
 */
- (NSInteger)tableView:(MSSTableView *)tableView numberOfSubRowsAtIndexPath:(NSIndexPath *)indexPath;

/**
 * Returns the instance of UITableViewCell object for the cell at the given indexPath.
 *
 *  @param tableView The instance of MSSTableView class.
 *
 *  @param indexPath The index path for the subrow. It has three properties that shows the exact position of the subrow cell.
 *                      These properties are named as section, row and subrow, all of which refers to the index of the object 
 *                      at the content array defined as data source of the table view.
 *
 *  @return The instance for the cell of subrow at the given indexPath.
 *
 *  @discussion In order to implement MSSTableView class efficiently, your content for the data source of the table view should
 *                  be designed as:
 *                      
 *                                  contentArray[[(Section0)[row0,subrow1,subrow2,...],[row1,subrow1,subrow2,...],
 *                                  [row2, subrow1,subrow2,...],...],[(Section1)[...],[...],[...], ...],...]
 *
 *                  and indexPath for any subrow is formatted as below:
 *
 *                                  Section0-row1-subrow2 => NSIndexPath section = 0 / row = 1 / subrow = 2 (Third element of
 *                                                                                     the first element of the content array.)
 *
 *                 For further information, please check the sample table view[@ViewController] in the project.
 */
- (UITableViewCell *)tableView:(MSSTableView *)tableView cellForSubRowAtIndexPath:(NSIndexPath *)indexPath;

@optional

/*
 * Asks the delegate for the height to use for a row at the given indexPath.
 *
 *  @param tableView The instance of MSSTableView class.
 *
 *  @param indexPath The indexPath for the subrow. It has three properties that shows the exact position of the subrow cell.
 *                      These properties are named as section, row and subrow, all of which refers to the index of the object
 *                      at the content array defined as data source of the table view.
 *
 *  @return A nonnegative floating-point value that specifies the height (in points) that row should be.
 *
 *  @discussion The indexPath value refers to the exact location explained in the discussion section of tableView:cellForSubRowAtIndexPath:
 *                  delegate method. You should adjust height value accordingly. Default value is 44.0 points.
 */
- (CGFloat)tableView:(MSSTableView *)tableView heightForSubRowAtIndexPath:(NSIndexPath *)indexPath;

/**
 * Tells the delegate that the specified subrow is now selected.
 *
 *  @param tableView The instance of MSSTableView class.
 *
 *  @param indexPath The indexPath for the subrow. It has three properties that shows the exact position of the 
 *   subrow cell. These properties are named as section, row and subrow, all of which refers to the index of the
 *   object at the content array defined as data source of the table view.
 */
- (void)tableView:(MSSTableView *)tableView didSelectSubRowAtIndexPath:(NSIndexPath *)indexPath;

/**
 * Asks the delegate whether the subrows of the cell at the given index path should be expanded initially.
 *
 *  @param tableView The instance of MSSTableView class.
 *
 *  @param indexPath The index path of the row which subrows to be expanded while loading the data into the tableview.
 *
 *  @return The boolean value indicating the initial expandability of the row at the given index path.
 */
- (BOOL)tableView:(MSSTableView *)tableView shouldExpandSubRowsOfCellAtIndexPath:(NSIndexPath *)indexPath;

@end


@interface MSSTableView : UITableView

/**
 * The delegate for the MSSTableViewDelegate protocol.
 *
 *  @discussion You must set only this protocol for the delegation and the datasource of MSSTableView instance.
 */
@property (nonatomic, weak) id <MSSTableViewDelegate> MSSTableViewDelegate;

/**
 * 设置展开一行或者多行
 */
@property (nonatomic, assign) BOOL shouldExpandOnlyOneCell;

/**
 * Reload data for table view while collapsing already expanded index paths.
 *
 *  @discussion It is requested to scroll to a specific position after reload data, use refreshDataWithScrollingToIndexPath: method. This method does not change scroll 
 *      position.
 */
- (void)refreshData;

/**
 * Relaod data and scroll to the given index path while collapsing already expanded index paths.
 *
 *  @param indexPath The index path which the table view should be scrolled to. DO NOT set subrow property.
 */
- (void)refreshDataWithScrollingToIndexPath:(NSIndexPath *)indexPath;

/**
 * 对indexPath扩展
 */
- (void)collapseCurrentlyExpandedIndexPaths;
/**
 *  获取被选中cell的IndexPath
 */
@property (nonatomic ,strong) NSIndexPath *selectedIndexPath;

@end

#pragma mark - NSIndexPath (MSSTableView)

@interface NSIndexPath (MSSTableView)

/**
 * Subrow number of the indexPath for any cell object.
 */
@property (nonatomic, assign) NSInteger subRow;

/**
 *  根据subrow,row,section获取NSIndexPath
 *
 */
+ (NSIndexPath *)indexPathForSubRow:(NSInteger)subrow inRow:(NSInteger)row inSection:(NSInteger)section;

@end
